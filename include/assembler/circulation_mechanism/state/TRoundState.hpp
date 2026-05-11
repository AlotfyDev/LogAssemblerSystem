#pragma once

    #include <cstdint>

    /*
        TRoundState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TRoundState` and its production transition contract helpers.

        Semantic role:
            Lifecycle state for ingress or dispatch round context.

        Production capabilities:
            - Closed enum vocabulary.
            - constexpr classification helpers.
            - constexpr transition eligibility.
            - terminal/error/active/readiness category helpers where applicable.
            - no runtime allocation.
            - no component behavior execution.

        Non-ownership:
            - Does not mutate runtime objects.
            - Does not execute actual slot/container/round/reference/dispatch behavior.
            - Does not own bridge or read-side lifecycle.
            - Does not perform logging or diagnostics export.

        Anti-collapse:
            The state enum and helper functions form a transition contract.
            They do not replace the behavior-owning component.
    */

    namespace assembler {
namespace circulation_mechanism {


    enum class TRoundState : std::uint8_t
    {
        idle,
        collecting_candidates,
        open,
        locked,
        draining,
        closing,
        closed,
        completed,
        aborted,
        invariant_violation
    };


[[nodiscard]] constexpr bool accepts_candidates(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::collecting_candidates:
        case TRoundState::open:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool membership_fixed(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::locked:
        case TRoundState::draining:
        case TRoundState::closing:
        case TRoundState::closed:
        case TRoundState::completed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_active(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::collecting_candidates:
        case TRoundState::open:
        case TRoundState::locked:
        case TRoundState::draining:
        case TRoundState::closing:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_closed(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::closed:
        case TRoundState::completed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::completed:
        case TRoundState::aborted:
        case TRoundState::invariant_violation:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::aborted:
        case TRoundState::invariant_violation:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool creates_safe_point(TRoundState state) noexcept
{
    switch (state)
    {
        case TRoundState::closed:
        case TRoundState::completed:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TRoundState from_state, TRoundState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TRoundState::idle:
            return to_state == TRoundState::collecting_candidates || to_state == TRoundState::aborted;
        case TRoundState::collecting_candidates:
            return to_state == TRoundState::open || to_state == TRoundState::aborted || to_state == TRoundState::invariant_violation;
        case TRoundState::open:
            return to_state == TRoundState::locked || to_state == TRoundState::closing || to_state == TRoundState::aborted || to_state == TRoundState::invariant_violation;
        case TRoundState::locked:
            return to_state == TRoundState::draining || to_state == TRoundState::closing || to_state == TRoundState::aborted || to_state == TRoundState::invariant_violation;
        case TRoundState::draining:
            return to_state == TRoundState::closing || to_state == TRoundState::closed || to_state == TRoundState::aborted || to_state == TRoundState::invariant_violation;
        case TRoundState::closing:
            return to_state == TRoundState::closed || to_state == TRoundState::aborted || to_state == TRoundState::invariant_violation;
        case TRoundState::closed:
            return to_state == TRoundState::completed || to_state == TRoundState::aborted;
        case TRoundState::completed:
            return false;
        case TRoundState::aborted:
            return false;
        case TRoundState::invariant_violation:
            return to_state == TRoundState::aborted;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool round_accepts_candidates(TRoundState state) noexcept
{
    return state == TRoundState::collecting_candidates || state == TRoundState::open;
}

[[nodiscard]] constexpr bool round_membership_fixed(TRoundState state) noexcept
{
    return state == TRoundState::locked || state == TRoundState::draining || state == TRoundState::closing || state == TRoundState::closed || state == TRoundState::completed;
}

[[nodiscard]] constexpr bool round_closed_or_completed(TRoundState state) noexcept
{
    return state == TRoundState::closed || state == TRoundState::completed;
}

[[nodiscard]] constexpr bool round_release_ready(TRoundState state) noexcept
{
    return state == TRoundState::closed || state == TRoundState::completed || state == TRoundState::aborted;
}

} // namespace circulation_mechanism
} // namespace assembler
