#pragma once
#include <cstdint>

/*
    TWaitingListState.hpp

    Delivery:
        CME-WAITING-LIST-PROD-W01 — Production Eligibility And Ordering Contract

    Responsibility:
        Defines production waiting-list lifecycle states.
*/
namespace assembler {
namespace circulation_mechanism {

enum class TWaitingListState : std::uint8_t {
    empty,
    accepting_candidates,
    ready_for_round,
    locked_by_round,
    draining_to_precalculator,
    cleared,
    eviction_candidate_selection,
    invariant_violation
};
[[nodiscard]] constexpr bool accepts_candidates(TWaitingListState s) noexcept {
    return s == TWaitingListState::empty || s == TWaitingListState::accepting_candidates || s == TWaitingListState::cleared;
}
[[nodiscard]] constexpr bool is_locked(TWaitingListState s) noexcept {
    return s == TWaitingListState::locked_by_round || s == TWaitingListState::draining_to_precalculator;
}
} // namespace circulation_mechanism
} // namespace assembler
