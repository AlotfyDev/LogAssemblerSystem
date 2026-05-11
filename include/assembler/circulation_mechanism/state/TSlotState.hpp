#pragma once

    #include <cstdint>

    /*
        TSlotState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TSlotState` and its production transition contract helpers.

        Semantic role:
            Slot-local lifecycle state for a bounded placement/access position inside a container.

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


    enum class TSlotState : std::uint8_t
    {
        empty,
        reserved_for_ingress,
        occupied,
        sealed,
        dispatch_ready,
        dispatch_exposed,
        released,
        recyclable,
        faulted
    };


[[nodiscard]] constexpr bool is_empty(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::empty:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_ingress_writable(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::empty:
        case TSlotState::reserved_for_ingress:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_resident(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::occupied:
        case TSlotState::sealed:
        case TSlotState::dispatch_ready:
        case TSlotState::dispatch_exposed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_dispatch_ready(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::sealed:
        case TSlotState::dispatch_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_exposed(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::dispatch_exposed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_released(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::released:
        case TSlotState::recyclable:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::faulted:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TSlotState state) noexcept
{
    switch (state)
    {
        case TSlotState::faulted:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TSlotState from_state, TSlotState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TSlotState::empty:
            return to_state == TSlotState::reserved_for_ingress || to_state == TSlotState::faulted;
        case TSlotState::reserved_for_ingress:
            return to_state == TSlotState::occupied || to_state == TSlotState::empty || to_state == TSlotState::faulted;
        case TSlotState::occupied:
            return to_state == TSlotState::sealed || to_state == TSlotState::released || to_state == TSlotState::faulted;
        case TSlotState::sealed:
            return to_state == TSlotState::dispatch_ready || to_state == TSlotState::released || to_state == TSlotState::faulted;
        case TSlotState::dispatch_ready:
            return to_state == TSlotState::dispatch_exposed || to_state == TSlotState::released || to_state == TSlotState::faulted;
        case TSlotState::dispatch_exposed:
            return to_state == TSlotState::released || to_state == TSlotState::faulted;
        case TSlotState::released:
            return to_state == TSlotState::recyclable || to_state == TSlotState::empty || to_state == TSlotState::faulted;
        case TSlotState::recyclable:
            return to_state == TSlotState::empty || to_state == TSlotState::faulted;
        case TSlotState::faulted:
            return false;
            default:
                return false;
        }
    }

    } // namespace circulation_mechanism
} // namespace assembler
