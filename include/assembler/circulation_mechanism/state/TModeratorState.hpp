#pragma once

    #include <cstdint>

    /*
        TModeratorState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TModeratorState` and its production transition contract helpers.

        Semantic role:
            Per-container moderator operational state.

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


    enum class TModeratorState : std::uint8_t
    {
        uninitialized,
        idle,
        observing,
        preparing,
        resetting,
        ready_exposed,
        safe_point_confirmed,
        moderation_blocked,
        invariant_violation
    };


[[nodiscard]] constexpr bool is_active(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::observing:
        case TModeratorState::preparing:
        case TModeratorState::resetting:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool can_apply_reset(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::safe_point_confirmed:
        case TModeratorState::resetting:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_ready(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::ready_exposed:
        case TModeratorState::safe_point_confirmed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_blocked(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::moderation_blocked:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::invariant_violation:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TModeratorState state) noexcept
{
    switch (state)
    {
        case TModeratorState::invariant_violation:
        case TModeratorState::moderation_blocked:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TModeratorState from_state, TModeratorState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TModeratorState::idle:
            return to_state == TModeratorState::observing || to_state == TModeratorState::preparing || to_state == TModeratorState::invariant_violation;
        case TModeratorState::observing:
            return to_state == TModeratorState::preparing || to_state == TModeratorState::ready_exposed || to_state == TModeratorState::moderation_blocked || to_state == TModeratorState::invariant_violation;
        case TModeratorState::preparing:
            return to_state == TModeratorState::safe_point_confirmed || to_state == TModeratorState::resetting || to_state == TModeratorState::moderation_blocked || to_state == TModeratorState::invariant_violation;
        case TModeratorState::resetting:
            return to_state == TModeratorState::ready_exposed || to_state == TModeratorState::idle || to_state == TModeratorState::invariant_violation;
        case TModeratorState::ready_exposed:
            return to_state == TModeratorState::observing || to_state == TModeratorState::idle || to_state == TModeratorState::invariant_violation;
        case TModeratorState::safe_point_confirmed:
            return to_state == TModeratorState::resetting || to_state == TModeratorState::ready_exposed || to_state == TModeratorState::invariant_violation;
        case TModeratorState::moderation_blocked:
            return to_state == TModeratorState::observing || to_state == TModeratorState::invariant_violation;
        case TModeratorState::invariant_violation:
            return false;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool can_expose_readiness(TModeratorState state) noexcept
{
    return state == TModeratorState::ready_exposed || state == TModeratorState::safe_point_confirmed;
}


[[nodiscard]] constexpr bool can_plan_reset(TModeratorState state) noexcept
{
    return state == TModeratorState::idle || state == TModeratorState::observing || state == TModeratorState::safe_point_confirmed;
}

} // namespace circulation_mechanism
} // namespace assembler
