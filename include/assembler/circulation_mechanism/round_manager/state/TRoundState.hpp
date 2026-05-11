#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TRoundState : std::uint8_t {
    idle, collecting_candidates, open, locked, draining, closing, closed, completed, aborted, invariant_violation
};
[[nodiscard]] constexpr bool round_accepts_candidates(TRoundState s) noexcept {
    return s == TRoundState::collecting_candidates || s == TRoundState::open;
}
[[nodiscard]] constexpr bool round_membership_fixed(TRoundState s) noexcept {
    return s == TRoundState::locked || s == TRoundState::draining || s == TRoundState::closing || s == TRoundState::closed || s == TRoundState::completed;
}
[[nodiscard]] constexpr bool round_closed_or_completed(TRoundState s) noexcept {
    return s == TRoundState::closed || s == TRoundState::completed;
}
[[nodiscard]] constexpr bool can_transition(TRoundState from, TRoundState to) noexcept {
    if (from == to) return true;
    switch(from) {
        case TRoundState::idle: return to == TRoundState::collecting_candidates || to == TRoundState::aborted;
        case TRoundState::collecting_candidates: return to == TRoundState::open || to == TRoundState::aborted || to == TRoundState::invariant_violation;
        case TRoundState::open: return to == TRoundState::locked || to == TRoundState::closing || to == TRoundState::aborted || to == TRoundState::invariant_violation;
        case TRoundState::locked: return to == TRoundState::draining || to == TRoundState::closing || to == TRoundState::aborted || to == TRoundState::invariant_violation;
        case TRoundState::draining: return to == TRoundState::closing || to == TRoundState::closed || to == TRoundState::aborted || to == TRoundState::invariant_violation;
        case TRoundState::closing: return to == TRoundState::closed || to == TRoundState::aborted || to == TRoundState::invariant_violation;
        case TRoundState::closed: return to == TRoundState::completed || to == TRoundState::aborted;
        case TRoundState::invariant_violation: return to == TRoundState::aborted;
        default: return false;
    }
}
} // namespace circulation_mechanism
} // namespace assembler
