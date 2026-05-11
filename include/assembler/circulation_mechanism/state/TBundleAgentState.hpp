#pragma once

    #include <cstdint>

    /*
        TBundleAgentState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TBundleAgentState` and its production transition contract helpers.

        Semantic role:
            Bundle topology and capacity profile state.

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


    enum class TBundleAgentState : std::uint8_t
    {
        uninitialized,
        stable,
        horizontal_scaling_pending,
        vertical_scaling_pending,
        waiting_for_safe_point,
        profile_switch_ready,
        profile_switch_applied,
        invariant_violation
    };


[[nodiscard]] constexpr bool is_stable(TBundleAgentState state) noexcept
{
    switch (state)
    {
        case TBundleAgentState::stable:
        case TBundleAgentState::profile_switch_applied:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_scaling_pending(TBundleAgentState state) noexcept
{
    switch (state)
    {
        case TBundleAgentState::horizontal_scaling_pending:
        case TBundleAgentState::vertical_scaling_pending:
        case TBundleAgentState::waiting_for_safe_point:
        case TBundleAgentState::profile_switch_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool requires_safe_point(TBundleAgentState state) noexcept
{
    switch (state)
    {
        case TBundleAgentState::vertical_scaling_pending:
        case TBundleAgentState::waiting_for_safe_point:
        case TBundleAgentState::profile_switch_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TBundleAgentState state) noexcept
{
    switch (state)
    {
        case TBundleAgentState::invariant_violation:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TBundleAgentState state) noexcept
{
    switch (state)
    {
        case TBundleAgentState::invariant_violation:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TBundleAgentState from_state, TBundleAgentState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TBundleAgentState::stable:
            return to_state == TBundleAgentState::horizontal_scaling_pending || to_state == TBundleAgentState::vertical_scaling_pending || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::horizontal_scaling_pending:
            return to_state == TBundleAgentState::profile_switch_applied || to_state == TBundleAgentState::waiting_for_safe_point || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::vertical_scaling_pending:
            return to_state == TBundleAgentState::waiting_for_safe_point || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::waiting_for_safe_point:
            return to_state == TBundleAgentState::profile_switch_ready || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::profile_switch_ready:
            return to_state == TBundleAgentState::profile_switch_applied || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::profile_switch_applied:
            return to_state == TBundleAgentState::stable || to_state == TBundleAgentState::invariant_violation;
        case TBundleAgentState::invariant_violation:
            return false;
            default:
                return false;
        }
    }

    } // namespace circulation_mechanism
} // namespace assembler
