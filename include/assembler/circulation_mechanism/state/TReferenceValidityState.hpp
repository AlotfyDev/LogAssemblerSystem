#pragma once

    #include <cstdint>

    /*
        TReferenceValidityState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TReferenceValidityState` and its production transition contract helpers.

        Semantic role:
            Validity lifecycle state of an access reference.

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


    enum class TReferenceValidityState : std::uint8_t
    {
        prepared,
        issued,
        consumed,
        expired,
        invalidated,
        stale_detected,
        blocked_by_state
    };


[[nodiscard]] constexpr bool is_usable(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::issued:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_prepared(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::prepared:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_consumed(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::consumed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_invalid(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::expired:
        case TReferenceValidityState::invalidated:
        case TReferenceValidityState::stale_detected:
        case TReferenceValidityState::blocked_by_state:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::consumed:
        case TReferenceValidityState::expired:
        case TReferenceValidityState::invalidated:
        case TReferenceValidityState::stale_detected:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TReferenceValidityState state) noexcept
{
    switch (state)
    {
        case TReferenceValidityState::stale_detected:
        case TReferenceValidityState::blocked_by_state:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TReferenceValidityState from_state, TReferenceValidityState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TReferenceValidityState::prepared:
            return to_state == TReferenceValidityState::issued || to_state == TReferenceValidityState::invalidated || to_state == TReferenceValidityState::expired;
        case TReferenceValidityState::issued:
            return to_state == TReferenceValidityState::consumed || to_state == TReferenceValidityState::expired || to_state == TReferenceValidityState::invalidated || to_state == TReferenceValidityState::blocked_by_state || to_state == TReferenceValidityState::stale_detected;
        case TReferenceValidityState::consumed:
            return false;
        case TReferenceValidityState::expired:
            return to_state == TReferenceValidityState::stale_detected;
        case TReferenceValidityState::invalidated:
            return to_state == TReferenceValidityState::stale_detected;
        case TReferenceValidityState::stale_detected:
            return false;
        case TReferenceValidityState::blocked_by_state:
            return to_state == TReferenceValidityState::invalidated || to_state == TReferenceValidityState::stale_detected;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool reference_released(TReferenceValidityState state) noexcept
{
    return state == TReferenceValidityState::consumed || state == TReferenceValidityState::expired || state == TReferenceValidityState::invalidated;
}

} // namespace circulation_mechanism
} // namespace assembler
