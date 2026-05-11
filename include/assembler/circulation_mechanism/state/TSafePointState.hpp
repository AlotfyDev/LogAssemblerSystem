#pragma once

    #include <cstdint>

    /*
        TSafePointState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TSafePointState` and its production transition contract helpers.

        Semantic role:
            Safe-point availability and consumption state.

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


    enum class TSafePointState : std::uint8_t
    {
        unavailable,
        pending,
        available,
        claimed,
        consumed,
        expired,
        violated
    };


[[nodiscard]] constexpr bool can_claim(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::available:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_claimed(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::claimed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_consumed(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::consumed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_unavailable(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::unavailable:
        case TSafePointState::pending:
        case TSafePointState::expired:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::consumed:
        case TSafePointState::expired:
        case TSafePointState::violated:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TSafePointState state) noexcept
{
    switch (state)
    {
        case TSafePointState::violated:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TSafePointState from_state, TSafePointState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TSafePointState::unavailable:
            return to_state == TSafePointState::pending || to_state == TSafePointState::available || to_state == TSafePointState::violated;
        case TSafePointState::pending:
            return to_state == TSafePointState::available || to_state == TSafePointState::unavailable || to_state == TSafePointState::violated;
        case TSafePointState::available:
            return to_state == TSafePointState::claimed || to_state == TSafePointState::expired || to_state == TSafePointState::violated;
        case TSafePointState::claimed:
            return to_state == TSafePointState::consumed || to_state == TSafePointState::expired || to_state == TSafePointState::violated;
        case TSafePointState::consumed:
            return false;
        case TSafePointState::expired:
            return to_state == TSafePointState::violated;
        case TSafePointState::violated:
            return false;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool safe_point_available(TSafePointState state) noexcept
{
    return state == TSafePointState::available || state == TSafePointState::claimed;
}

} // namespace circulation_mechanism
} // namespace assembler
