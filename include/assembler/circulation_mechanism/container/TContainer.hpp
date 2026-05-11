#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/slot/TSlot.hpp"
#include "TContainerSlotLayoutView.hpp"
#include "TContainerStateView.hpp"
#include "TContainerTimeRange.hpp"
#include "TContainerTimeRangeView.hpp"
#include "TContainerView.hpp"
#include "TContainerOperationResult.hpp"
#include "TContainerStateTransitionReport.hpp"

/*
    TContainer.hpp

    Delivery:
        CME-CONTAINER-PROD-W01 — Production Residency And Shape Contract

    Current responsibility:
        Defines a production-grade fixed-shape container that owns a uniform
        array of slots and container-level state/time-range metadata.

    Production capabilities:
        - fixed number of slots,
        - uniform slot payload capacity,
        - slot lookup by one-based TSlotIndex,
        - payload placement into slot,
        - container-level occupancy counters,
        - time range update/clear,
        - state transitions guarded by TContainerState transition contract,
        - dispatch readiness counting,
        - reset to default_empty when empty/released,
        - read-only container views,
        - transition reports.

    Explicit non-ownership:
        - Does not become a message broker.
        - Does not perform registry storage.
        - Does not calculate access references.
        - Does not execute bridge transfer.
        - Does not own receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {

template <std::size_t SlotCount, std::size_t SlotCapacityBytes>
class TContainer final {
public:
    static_assert(SlotCount > 0U, "TContainer SlotCount must be greater than zero.");
    static_assert(SlotCapacityBytes > 0U, "TContainer SlotCapacityBytes must be greater than zero.");
    using slot_type = TSlot<SlotCapacityBytes>;

    constexpr explicit TContainer(TContainerId id) noexcept : id_(id) {
        for (std::size_t i = 0; i < SlotCount; ++i) {
            slots_[i] = slot_type{TSlotIndex::from_raw(static_cast<std::uint64_t>(i + 1U))};
        }
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return id_.is_valid(); }
    [[nodiscard]] constexpr TContainerId id() const noexcept { return id_; }
    [[nodiscard]] constexpr TContainerState state() const noexcept { return state_; }
    [[nodiscard]] constexpr std::uint32_t occupied_slots() const noexcept { return occupied_slots_; }
    [[nodiscard]] constexpr std::uint32_t dispatch_ready_slots() const noexcept { return dispatch_ready_slots_; }
    [[nodiscard]] constexpr TContainerTimeRange time_range() const noexcept { return time_range_; }
    [[nodiscard]] constexpr std::size_t slot_count() const noexcept { return SlotCount; }
    [[nodiscard]] constexpr std::size_t slot_capacity() const noexcept { return SlotCapacityBytes; }

    [[nodiscard]] constexpr slot_type* try_get_slot(TSlotIndex index) noexcept {
        if (!index.is_valid() || index.one_based() > SlotCount) return nullptr;
        return &slots_[index.zero_based_or(0)];
    }

    [[nodiscard]] constexpr const slot_type* try_get_slot(TSlotIndex index) const noexcept {
        if (!index.is_valid() || index.one_based() > SlotCount) return nullptr;
        return &slots_[index.zero_based_or(0)];
    }

    constexpr TContainerOperationResult transition_to(TContainerState next) noexcept {
        const auto before = state_;
        if (!is_valid()) return {TContainerOperationStatus::rejected_invalid_container, before, state_};
        if (!can_transition(state_, next)) return {TContainerOperationStatus::rejected_invalid_transition, before, state_};
        state_ = next;
        return {TContainerOperationStatus::accepted, before, state_};
    }

    constexpr TContainerOperationResult place_payload(TSlotIndex index, const std::uint8_t* data, std::uint32_t size, std::int64_t timestamp) noexcept {
        const auto before = state_;
        auto* slot = try_get_slot(index);
        if (!is_valid()) return {TContainerOperationStatus::rejected_invalid_container, before, state_};
        if (!slot) return {TContainerOperationStatus::rejected_invalid_slot_index, before, state_};
        if (!data || size == 0U || size > SlotCapacityBytes) return {TContainerOperationStatus::rejected_payload_invalid, before, state_};
        if (!slot->place_payload(data, size)) return {TContainerOperationStatus::rejected_slot_occupied, before, state_};
        ++occupied_slots_;
        time_range_.include(timestamp);
        if (state_ == TContainerState::default_empty || state_ == TContainerState::ingress_ready || state_ == TContainerState::ingress_round_member) {
            state_ = TContainerState::receiving;
        }
        return {TContainerOperationStatus::accepted, before, state_};
    }

    constexpr TContainerOperationResult seal_slot(TSlotIndex index) noexcept {
        const auto before = state_;
        auto* slot = try_get_slot(index);
        if (!slot) return {TContainerOperationStatus::rejected_invalid_slot_index, before, state_};
        if (!slot->seal()) return {TContainerOperationStatus::rejected_invalid_transition, before, state_};
        return {TContainerOperationStatus::accepted, before, state_};
    }

    constexpr TContainerOperationResult mark_slot_dispatch_ready(TSlotIndex index) noexcept {
        const auto before = state_;
        auto* slot = try_get_slot(index);
        if (!slot) return {TContainerOperationStatus::rejected_invalid_slot_index, before, state_};
        if (!slot->mark_dispatch_ready()) return {TContainerOperationStatus::rejected_invalid_transition, before, state_};
        ++dispatch_ready_slots_;
        if (state_ == TContainerState::receiving || state_ == TContainerState::filled_or_closed) {
            state_ = TContainerState::dispatch_candidate;
        }
        return {TContainerOperationStatus::accepted, before, state_};
    }

    constexpr TContainerOperationResult close_for_dispatch() noexcept {
        const auto before = state_;
        if (occupied_slots_ == 0U) return {TContainerOperationStatus::rejected_not_dispatch_ready, before, state_};
        if (state_ == TContainerState::receiving) {
            state_ = TContainerState::filled_or_closed;
            return {TContainerOperationStatus::accepted, before, state_};
        }
        return transition_to(TContainerState::dispatch_candidate);
    }

    constexpr TContainerOperationResult release_slot(TSlotIndex index) noexcept {
        const auto before = state_;
        auto* slot = try_get_slot(index);
        if (!slot) return {TContainerOperationStatus::rejected_invalid_slot_index, before, state_};
        const bool was_occupied = slot->occupied();
        const bool was_dispatch_ready = slot->state() == TSlotState::dispatch_ready || slot->state() == TSlotState::dispatch_exposed;
        if (!slot->release()) return {TContainerOperationStatus::rejected_invalid_transition, before, state_};
        if (was_occupied && occupied_slots_ > 0U) --occupied_slots_;
        if (was_dispatch_ready && dispatch_ready_slots_ > 0U) --dispatch_ready_slots_;
        if (occupied_slots_ == 0U) state_ = TContainerState::dispatch_completed;
        return {TContainerOperationStatus::accepted, before, state_};
    }

    constexpr TContainerOperationResult reset_to_default_empty() noexcept {
        const auto before = state_;
        if (occupied_slots_ != 0U) return {TContainerOperationStatus::rejected_not_empty, before, state_};
        for (auto& slot : slots_) {
            if (slot.state() == TSlotState::released || slot.state() == TSlotState::recyclable) {
                slot.recycle_to_empty();
            }
        }
        time_range_.clear();
        dispatch_ready_slots_ = 0U;
        state_ = TContainerState::default_empty;
        return {TContainerOperationStatus::accepted, before, state_};
    }

    [[nodiscard]] constexpr TContainerView view() const noexcept {
        return TContainerView{
            TContainerStateView{id_, state_},
            TContainerSlotLayoutView{static_cast<std::uint32_t>(SlotCount), static_cast<std::uint32_t>(SlotCapacityBytes)},
            TContainerTimeRangeView{time_range_},
            occupied_slots_,
            dispatch_ready_slots_
        };
    }

    [[nodiscard]] constexpr TContainerStateTransitionReport transition_report(TContainerOperationResult result) const noexcept {
        return TContainerStateTransitionReport{id_, result.before, result.after, result.accepted()};
    }

private:
    TContainerId id_{TContainerId::invalid()};
    TContainerState state_{TContainerState::default_empty};
    std::array<slot_type, SlotCount> slots_{};
    std::uint32_t occupied_slots_{0};
    std::uint32_t dispatch_ready_slots_{0};
    TContainerTimeRange time_range_{};
};
} // namespace circulation_mechanism
} // namespace assembler
