#pragma once

    #include <cstdint>

    /*
        TReferenceSupplyState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TReferenceSupplyState` and its production transition contract helpers.

        Semantic role:
            ReferencePrecalculator next-ref supply state.

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


    enum class TReferenceSupplyState : std::uint8_t
    {
        ready,
        replenishing,
        ingress_refs_ready,
        dispatch_refs_ready,
        waiting_for_candidates,
        invalidating_refs,
        supply_interrupted,
        invariant_violation
    };


[[nodiscard]] constexpr bool has_supply(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::ready:
        case TReferenceSupplyState::ingress_refs_ready:
        case TReferenceSupplyState::dispatch_refs_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_replenishing(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::replenishing:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_waiting(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::waiting_for_candidates:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_invalidating(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::invalidating_refs:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::invariant_violation:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TReferenceSupplyState state) noexcept
{
    switch (state)
    {
        case TReferenceSupplyState::supply_interrupted:
        case TReferenceSupplyState::invariant_violation:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TReferenceSupplyState from_state, TReferenceSupplyState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TReferenceSupplyState::ready:
            return to_state == TReferenceSupplyState::replenishing || to_state == TReferenceSupplyState::ingress_refs_ready || to_state == TReferenceSupplyState::dispatch_refs_ready || to_state == TReferenceSupplyState::waiting_for_candidates || to_state == TReferenceSupplyState::invalidating_refs || to_state == TReferenceSupplyState::supply_interrupted || to_state == TReferenceSupplyState::invariant_violation;
        case TReferenceSupplyState::replenishing:
            return to_state == TReferenceSupplyState::ready || to_state == TReferenceSupplyState::ingress_refs_ready || to_state == TReferenceSupplyState::dispatch_refs_ready || to_state == TReferenceSupplyState::waiting_for_candidates || to_state == TReferenceSupplyState::supply_interrupted || to_state == TReferenceSupplyState::invariant_violation;
        case TReferenceSupplyState::ingress_refs_ready:
            return to_state == TReferenceSupplyState::ready || to_state == TReferenceSupplyState::replenishing || to_state == TReferenceSupplyState::invalidating_refs || to_state == TReferenceSupplyState::supply_interrupted;
        case TReferenceSupplyState::dispatch_refs_ready:
            return to_state == TReferenceSupplyState::ready || to_state == TReferenceSupplyState::replenishing || to_state == TReferenceSupplyState::invalidating_refs || to_state == TReferenceSupplyState::supply_interrupted;
        case TReferenceSupplyState::waiting_for_candidates:
            return to_state == TReferenceSupplyState::replenishing || to_state == TReferenceSupplyState::supply_interrupted || to_state == TReferenceSupplyState::invariant_violation;
        case TReferenceSupplyState::invalidating_refs:
            return to_state == TReferenceSupplyState::ready || to_state == TReferenceSupplyState::waiting_for_candidates || to_state == TReferenceSupplyState::invariant_violation;
        case TReferenceSupplyState::supply_interrupted:
            return to_state == TReferenceSupplyState::replenishing || to_state == TReferenceSupplyState::invariant_violation;
        case TReferenceSupplyState::invariant_violation:
            return false;
            default:
                return false;
        }
    }

    } // namespace circulation_mechanism
} // namespace assembler
