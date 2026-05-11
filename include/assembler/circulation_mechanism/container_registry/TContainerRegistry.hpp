#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "TContainerRegistryState.hpp"
#include "TContainerStorageKind.hpp"
#include "TContainerRegistryView.hpp"
#include "TContainerRegistryCapacityView.hpp"
#include "TContainerRegistryGenerationView.hpp"
#include "TContainerRegistryOperationResult.hpp"
#include "TContainerRegistryInvariantReport.hpp"
#include "TRegistryProfileSwitchReport.hpp"

/*
    TContainerRegistry.hpp

    Delivery:
        CME-CONTAINER-REGISTRY-PROD-W01 — Production Indexed Storage Contract

    Current responsibility:
        Production-grade fixed-capacity indexed registry for container-like values.

    Production capabilities:
        - explicit initialization,
        - one-based index validation,
        - fixed-capacity storage ownership,
        - insert/assign into explicit index,
        - insert into first free slot,
        - remove/clear slot,
        - checked mutable/const resolution,
        - active-count tracking,
        - generation tracking,
        - compact rebuild,
        - registry/capacity/generation views,
        - invariant report,
        - profile switch report.

    Explicit non-ownership:
        - Does not create container semantics.
        - Does not calculate references.
        - Does not manage waiting lists.
        - Does not execute bridge or receiver behavior.
*/

namespace assembler {
namespace circulation_mechanism {


template <typename TValue, std::size_t Capacity>
class TContainerRegistry final {
public:
    using value_type = TValue;
    static constexpr std::size_t k_capacity = Capacity;
    static_assert(Capacity > 0U, "TContainerRegistry capacity must be greater than zero.");

    constexpr TContainerRegistry() noexcept = default;

    constexpr void initialize() noexcept {
        state_ = TContainerRegistryState::initialized;
        active_count_ = 0U;
        generation_ = 1U;
        for (auto& occupied : occupied_) {
            occupied = false;
        }
    }

    [[nodiscard]] constexpr bool is_initialized() const noexcept { return state_ != TContainerRegistryState::uninitialized; }
    [[nodiscard]] constexpr std::uint32_t capacity() const noexcept { return static_cast<std::uint32_t>(Capacity); }
    [[nodiscard]] constexpr std::uint32_t active_count() const noexcept { return active_count_; }
    [[nodiscard]] constexpr std::uint64_t generation() const noexcept { return generation_; }
    [[nodiscard]] constexpr bool full() const noexcept { return active_count_ == Capacity; }

    [[nodiscard]] constexpr bool contains(TContainerRegistryIndex index) const noexcept {
        return index.is_valid() && index.one_based() <= Capacity;
    }

    [[nodiscard]] constexpr bool is_occupied(TContainerRegistryIndex index) const noexcept {
        return contains(index) && occupied_[index.zero_based_or(0)];
    }

    constexpr TContainerRegistryOperationResult assign(TContainerRegistryIndex index, const value_type& value) noexcept {
        const auto before = generation_;
        if (!is_initialized()) return {TContainerRegistryOperationStatus::rejected_uninitialized, index, before, generation_};
        if (!contains(index)) return {TContainerRegistryOperationStatus::rejected_invalid_index, index, before, generation_};
        const auto pos = index.zero_based_or(0);
        if (!occupied_[pos]) {
            ++active_count_;
        }
        storage_[pos] = value;
        occupied_[pos] = true;
        state_ = TContainerRegistryState::active;
        ++generation_;
        return {TContainerRegistryOperationStatus::accepted, index, before, generation_};
    }

    constexpr TContainerRegistryOperationResult insert_first_free(const value_type& value) noexcept {
        const auto before = generation_;
        if (!is_initialized()) return {TContainerRegistryOperationStatus::rejected_uninitialized, TContainerRegistryIndex::invalid(), before, generation_};
        if (full()) return {TContainerRegistryOperationStatus::rejected_registry_full, TContainerRegistryIndex::invalid(), before, generation_};
        for (std::size_t i = 0; i < Capacity; ++i) {
            if (!occupied_[i]) {
                return assign(TContainerRegistryIndex::from_raw(static_cast<std::uint64_t>(i + 1U)), value);
            }
        }
        return {TContainerRegistryOperationStatus::rejected_registry_full, TContainerRegistryIndex::invalid(), before, generation_};
    }

    constexpr TContainerRegistryOperationResult remove(TContainerRegistryIndex index) noexcept {
        const auto before = generation_;
        if (!is_initialized()) return {TContainerRegistryOperationStatus::rejected_uninitialized, index, before, generation_};
        if (!contains(index)) return {TContainerRegistryOperationStatus::rejected_invalid_index, index, before, generation_};
        const auto pos = index.zero_based_or(0);
        if (!occupied_[pos]) return {TContainerRegistryOperationStatus::rejected_slot_empty, index, before, generation_};
        storage_[pos] = value_type{};
        occupied_[pos] = false;
        --active_count_;
        ++generation_;
        if (active_count_ == 0U) state_ = TContainerRegistryState::initialized;
        return {TContainerRegistryOperationStatus::accepted, index, before, generation_};
    }

    [[nodiscard]] constexpr value_type* try_get(TContainerRegistryIndex index) noexcept {
        if (!is_occupied(index)) return nullptr;
        return &storage_[index.zero_based_or(0)];
    }

    [[nodiscard]] constexpr const value_type* try_get(TContainerRegistryIndex index) const noexcept {
        if (!is_occupied(index)) return nullptr;
        return &storage_[index.zero_based_or(0)];
    }

    constexpr TContainerRegistryOperationResult rebuild_compact() noexcept {
        const auto before = generation_;
        if (!is_initialized()) return {TContainerRegistryOperationStatus::rejected_uninitialized, TContainerRegistryIndex::invalid(), before, generation_};
        state_ = TContainerRegistryState::rebuild_pending;

        std::array<value_type, Capacity> new_storage{};
        std::array<bool, Capacity> new_occupied{};
        std::size_t cursor = 0U;
        for (std::size_t i = 0; i < Capacity; ++i) {
            if (occupied_[i]) {
                new_storage[cursor] = storage_[i];
                new_occupied[cursor] = true;
                ++cursor;
            }
        }
        storage_ = new_storage;
        occupied_ = new_occupied;
        active_count_ = static_cast<std::uint32_t>(cursor);
        ++generation_;
        state_ = active_count_ > 0U ? TContainerRegistryState::active : TContainerRegistryState::initialized;
        return {TContainerRegistryOperationStatus::accepted, TContainerRegistryIndex::invalid(), before, generation_};
    }

    [[nodiscard]] constexpr TContainerRegistryView view() const noexcept {
        return TContainerRegistryView{state_, TContainerStorageKind::fixed_array, static_cast<std::uint32_t>(Capacity), active_count_, generation_};
    }

    [[nodiscard]] constexpr TContainerRegistryCapacityView capacity_view() const noexcept {
        return TContainerRegistryCapacityView{static_cast<std::uint32_t>(Capacity), active_count_};
    }

    [[nodiscard]] constexpr TContainerRegistryGenerationView generation_view() const noexcept {
        return TContainerRegistryGenerationView{generation_};
    }

    [[nodiscard]] constexpr std::uint32_t diagnostic_occupied_count() const noexcept {
        std::uint32_t count = 0U;
        for (bool occupied : occupied_) {
            if (occupied) ++count;
        }
        return count;
    }

    [[nodiscard]] constexpr TContainerRegistryInvariantReport invariant_report() const noexcept {
        return TContainerRegistryInvariantReport{
            is_initialized(),
            active_count_ <= Capacity,
            diagnostic_occupied_count() == active_count_,
            generation_ > 0U,
            state_
        };
    }

    [[nodiscard]] constexpr TRegistryProfileSwitchReport profile_switch_report(std::uint64_t before, std::uint64_t after, bool accepted) const noexcept {
        return TRegistryProfileSwitchReport{before, after, accepted};
    }

private:
    std::array<value_type, Capacity> storage_{};
    std::array<bool, Capacity> occupied_{};
    TContainerRegistryState state_{TContainerRegistryState::uninitialized};
    std::uint32_t active_count_{0};
    std::uint64_t generation_{0};
};

} // namespace circulation_mechanism
} // namespace assembler
