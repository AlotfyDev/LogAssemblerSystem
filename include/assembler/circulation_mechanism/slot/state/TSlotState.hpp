#pragma once

#include <cstdint>

/*
    TSlotState.hpp

    Local dependency copy for CME-SLOT-PROD-W01.

    Responsibility:
        Defines slot-local lifecycle state and transition contract.
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
    return state == TSlotState::empty;
}

[[nodiscard]] constexpr bool is_ingress_writable(TSlotState state) noexcept
{
    return state == TSlotState::empty || state == TSlotState::reserved_for_ingress;
}

[[nodiscard]] constexpr bool is_resident(TSlotState state) noexcept
{
    return state == TSlotState::occupied
        || state == TSlotState::sealed
        || state == TSlotState::dispatch_ready
        || state == TSlotState::dispatch_exposed;
}

[[nodiscard]] constexpr bool is_dispatch_ready(TSlotState state) noexcept
{
    return state == TSlotState::sealed || state == TSlotState::dispatch_ready;
}

[[nodiscard]] constexpr bool is_released(TSlotState state) noexcept
{
    return state == TSlotState::released || state == TSlotState::recyclable;
}

[[nodiscard]] constexpr bool is_terminal(TSlotState state) noexcept
{
    return state == TSlotState::faulted;
}

[[nodiscard]] constexpr bool is_error(TSlotState state) noexcept
{
    return state == TSlotState::faulted;
}

[[nodiscard]] constexpr bool can_transition(TSlotState from_state, TSlotState to_state) noexcept
{
    if (from_state == to_state) return true;

    switch (from_state)
    {
        case TSlotState::empty:
            return to_state == TSlotState::reserved_for_ingress || to_state == TSlotState::occupied || to_state == TSlotState::faulted;
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
