#pragma once

    #include <cstdint>

    /*
        TDispatchExposureState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TDispatchExposureState` and its production transition contract helpers.

        Semantic role:
            Dispatcher output exposure lifecycle state.

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


    enum class TDispatchExposureState : std::uint8_t
    {
        ready,
        awaiting_dispatch_ref,
        exposing,
        passive_exposed,
        bridge_observed,
        bridge_consumed,
        release_pending,
        closed,
        boundary_assumption_broken
    };


[[nodiscard]] constexpr bool is_ready(TDispatchExposureState state) noexcept
{
    switch (state)
    {
        case TDispatchExposureState::ready:
        case TDispatchExposureState::awaiting_dispatch_ref:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_exposed(TDispatchExposureState state) noexcept
{
    switch (state)
    {
        case TDispatchExposureState::passive_exposed:
        case TDispatchExposureState::bridge_observed:
        case TDispatchExposureState::bridge_consumed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_release_related(TDispatchExposureState state) noexcept
{
    switch (state)
    {
        case TDispatchExposureState::bridge_consumed:
        case TDispatchExposureState::release_pending:
        case TDispatchExposureState::closed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TDispatchExposureState state) noexcept
{
    switch (state)
    {
        case TDispatchExposureState::closed:
        case TDispatchExposureState::boundary_assumption_broken:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TDispatchExposureState state) noexcept
{
    switch (state)
    {
        case TDispatchExposureState::boundary_assumption_broken:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TDispatchExposureState from_state, TDispatchExposureState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TDispatchExposureState::ready:
            return to_state == TDispatchExposureState::awaiting_dispatch_ref || to_state == TDispatchExposureState::exposing || to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::awaiting_dispatch_ref:
            return to_state == TDispatchExposureState::exposing || to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::exposing:
            return to_state == TDispatchExposureState::passive_exposed || to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::passive_exposed:
            return to_state == TDispatchExposureState::bridge_observed || to_state == TDispatchExposureState::bridge_consumed || to_state == TDispatchExposureState::release_pending || to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::bridge_observed:
            return to_state == TDispatchExposureState::bridge_consumed || to_state == TDispatchExposureState::release_pending || to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::bridge_consumed:
            return to_state == TDispatchExposureState::release_pending || to_state == TDispatchExposureState::closed;
        case TDispatchExposureState::release_pending:
            return to_state == TDispatchExposureState::closed || to_state == TDispatchExposureState::boundary_assumption_broken;
        case TDispatchExposureState::closed:
            return false;
        case TDispatchExposureState::boundary_assumption_broken:
            return false;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool exposure_release_ready(TDispatchExposureState state) noexcept
{
    return state == TDispatchExposureState::bridge_consumed || state == TDispatchExposureState::release_pending || state == TDispatchExposureState::closed;
}

[[nodiscard]] constexpr bool exposure_clear_for_eviction(TDispatchExposureState state) noexcept
{
    return state == TDispatchExposureState::closed || state == TDispatchExposureState::release_pending || state == TDispatchExposureState::bridge_consumed;
}

} // namespace circulation_mechanism
} // namespace assembler
