#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include "TWaitingListEntry.hpp"
#include "TWaitingListState.hpp"
#include "TWaitingListAdmissionStatus.hpp"
#include "TIngressWaitingListView.hpp"
#include "TIngressWaitingListRegistrationReport.hpp"

/*
    TIngressWaitingList.hpp

    Delivery:
        CME-WAITING-LIST-PROD-W01 — Production Eligibility And Ordering Contract

    Responsibility:
        Production-grade fixed-capacity waiting list storing eligible container registry indices.

    Production capabilities:
        - index-only entry storage,
        - FIFO sequence assignment,
        - duplicate rejection,
        - full rejection,
        - locked rejection,
        - state eligibility validation,
        - lock/drain/clear lifecycle,
        - front access for ReferencePrecalculator,
        - read-only view,
        - registration reports.

    Anti-collapse:
        This class never stores envelopes or payloads.
*/
namespace assembler {
namespace circulation_mechanism {

template <std::size_t Capacity>
class TIngressWaitingList final {
public:
    static_assert(Capacity > 0U, "Waiting list capacity must be greater than zero.");

    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ >= Capacity; }
    [[nodiscard]] constexpr std::uint32_t size() const noexcept { return size_; }
    [[nodiscard]] constexpr std::uint32_t capacity() const noexcept { return static_cast<std::uint32_t>(Capacity); }
    [[nodiscard]] constexpr TWaitingListState state() const noexcept { return state_; }

    [[nodiscard]] constexpr const TWaitingListEntry* try_peek_front() const noexcept {
        return size_ > 0U ? &entries_[0] : nullptr;
    }

    [[nodiscard]] constexpr const TWaitingListEntry* try_get(std::uint32_t zero_based_index) const noexcept {
        return zero_based_index < size_ ? &entries_[zero_based_index] : nullptr;
    }

    [[nodiscard]] constexpr TIngressWaitingListView view() const noexcept {
        return TIngressWaitingListView{state_, size_, static_cast<std::uint32_t>(Capacity), sequence_};
    }

    constexpr TIngressWaitingListRegistrationReport try_push(TWaitingListEntry entry) noexcept {
        if (is_locked(state_)) {
            return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::rejected_locked, size_};
        }
        if (!entry.is_valid()) {
            return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::rejected_invalid_index, size_};
        }
        if (!ingress_waiting_list_eligible(entry.observed_container_state)) {
            return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::rejected_ineligible_state, size_};
        }
        if (contains_index(entry.container_index)) {
            return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::rejected_duplicate, size_};
        }
        if (full()) {
            return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::rejected_full, size_};
        }
        entry.fifo_sequence = ++sequence_;
        entries_[size_] = entry;
        ++size_;
        state_ = TWaitingListState::accepting_candidates;
        return TIngressWaitingListRegistrationReport{entry, TWaitingListAdmissionStatus::accepted, size_};
    }

    constexpr bool lock_for_round() noexcept {
        if (size_ == 0U) {
            state_ = TWaitingListState::empty;
            return false;
        }
        state_ = TWaitingListState::locked_by_round;
        return true;
    }

    constexpr bool mark_draining_to_precalculator() noexcept {
        if (state_ != TWaitingListState::locked_by_round) {
            return false;
        }
        state_ = TWaitingListState::draining_to_precalculator;
        return true;
    }

    constexpr void clear() noexcept {
        for (auto& entry : entries_) {
            entry = TWaitingListEntry{};
        }
        size_ = 0U;
        state_ = TWaitingListState::cleared;
    }


private:
    [[nodiscard]] constexpr bool contains_index(TContainerRegistryIndex index) const noexcept {
        for (std::uint32_t i = 0; i < size_; ++i) {
            if (entries_[i].container_index == index) {
                return true;
            }
        }
        return false;
    }

protected:
    std::array<TWaitingListEntry, Capacity> entries_{};
    std::uint32_t size_{0};
    std::uint64_t sequence_{0};
    TWaitingListState state_{TWaitingListState::empty};

};
} // namespace circulation_mechanism
} // namespace assembler
