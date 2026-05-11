#pragma once

    #include <cstdint>

    /*
        TContainerState.hpp

        Delivery:
            CME-STATE-PROD-W01 — Production Transition Contract

        Current responsibility:
            Defines `TContainerState` and its production transition contract helpers.

        Semantic role:
            Whole-container operational and cycle-participation state.

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


    enum class TContainerState : std::uint8_t
    {
        default_empty,
        ingress_ready,
        ingress_round_member,
        receiving,
        filled_or_closed,
        dispatch_candidate,
        dispatch_round_member,
        dispatch_exposed,
        dispatch_completed,
        reset_pending,
        under_moderation,
        inactive,
        evicted,
        faulted
    };


[[nodiscard]] constexpr bool is_empty_or_ready(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::default_empty:
        case TContainerState::ingress_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_ingress_related(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::ingress_ready:
        case TContainerState::ingress_round_member:
        case TContainerState::receiving:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_dispatch_related(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::dispatch_candidate:
        case TContainerState::dispatch_round_member:
        case TContainerState::dispatch_exposed:
        case TContainerState::dispatch_completed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_reset_related(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::reset_pending:
        case TContainerState::under_moderation:
        case TContainerState::default_empty:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_active(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::ingress_ready:
        case TContainerState::ingress_round_member:
        case TContainerState::receiving:
        case TContainerState::filled_or_closed:
        case TContainerState::dispatch_candidate:
        case TContainerState::dispatch_round_member:
        case TContainerState::dispatch_exposed:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_terminal(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::inactive:
        case TContainerState::evicted:
        case TContainerState::faulted:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool is_error(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::faulted:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool can_join_ingress_round(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::default_empty:
        case TContainerState::ingress_ready:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool can_join_dispatch_round(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::dispatch_candidate:
            return true;
        default:
            return false;
    }
}

[[nodiscard]] constexpr bool requires_safe_point_for_reset(TContainerState state) noexcept
{
    switch (state)
    {
        case TContainerState::dispatch_completed:
        case TContainerState::reset_pending:
            return true;
        default:
            return false;
    }
}


    [[nodiscard]] constexpr bool can_transition(TContainerState from_state, TContainerState to_state) noexcept
    {
        if (from_state == to_state)
        {
            return true;
        }

        switch (from_state)
        {
        case TContainerState::default_empty:
            return to_state == TContainerState::ingress_ready || to_state == TContainerState::inactive || to_state == TContainerState::faulted;
        case TContainerState::ingress_ready:
            return to_state == TContainerState::ingress_round_member || to_state == TContainerState::inactive || to_state == TContainerState::faulted;
        case TContainerState::ingress_round_member:
            return to_state == TContainerState::receiving || to_state == TContainerState::filled_or_closed || to_state == TContainerState::faulted;
        case TContainerState::receiving:
            return to_state == TContainerState::filled_or_closed || to_state == TContainerState::faulted;
        case TContainerState::filled_or_closed:
            return to_state == TContainerState::dispatch_candidate || to_state == TContainerState::reset_pending || to_state == TContainerState::faulted;
        case TContainerState::dispatch_candidate:
            return to_state == TContainerState::dispatch_round_member || to_state == TContainerState::evicted || to_state == TContainerState::faulted;
        case TContainerState::dispatch_round_member:
            return to_state == TContainerState::dispatch_exposed || to_state == TContainerState::dispatch_completed || to_state == TContainerState::faulted;
        case TContainerState::dispatch_exposed:
            return to_state == TContainerState::dispatch_completed || to_state == TContainerState::faulted;
        case TContainerState::dispatch_completed:
            return to_state == TContainerState::reset_pending || to_state == TContainerState::evicted || to_state == TContainerState::faulted;
        case TContainerState::reset_pending:
            return to_state == TContainerState::under_moderation || to_state == TContainerState::faulted;
        case TContainerState::under_moderation:
            return to_state == TContainerState::default_empty || to_state == TContainerState::faulted;
        case TContainerState::inactive:
            return to_state == TContainerState::default_empty;
        case TContainerState::evicted:
            return false;
        case TContainerState::faulted:
            return false;
            default:
                return false;
        }
    }

    
[[nodiscard]] constexpr bool ingress_waiting_list_eligible(TContainerState state) noexcept
{
    return state == TContainerState::default_empty || state == TContainerState::ingress_ready;
}

[[nodiscard]] constexpr bool dispatch_waiting_list_eligible(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_candidate || state == TContainerState::dispatch_round_member;
}

[[nodiscard]] constexpr bool ingress_round_eligible(TContainerState state) noexcept
{
    return state == TContainerState::default_empty || state == TContainerState::ingress_ready;
}

[[nodiscard]] constexpr bool dispatch_round_eligible(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_candidate;
}

[[nodiscard]] constexpr bool reset_eligible(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_completed || state == TContainerState::reset_pending;
}

[[nodiscard]] constexpr bool unsafe_active_container(TContainerState state) noexcept
{
    return state == TContainerState::ingress_round_member || state == TContainerState::receiving || state == TContainerState::dispatch_round_member || state == TContainerState::dispatch_exposed;
}

[[nodiscard]] constexpr bool container_release_ready(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_completed || state == TContainerState::reset_pending;
}

[[nodiscard]] constexpr bool container_active_in_ingress(TContainerState state) noexcept
{
    return state == TContainerState::ingress_round_member || state == TContainerState::receiving;
}

[[nodiscard]] constexpr bool container_active_in_dispatch(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_round_member || state == TContainerState::dispatch_exposed;
}

[[nodiscard]] constexpr bool container_eviction_state_candidate(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_candidate || state == TContainerState::dispatch_completed || state == TContainerState::reset_pending || state == TContainerState::inactive;
}


[[nodiscard]] constexpr bool ingress_ready_candidate(TContainerState state) noexcept
{
    return state == TContainerState::default_empty || state == TContainerState::ingress_ready;
}


[[nodiscard]] constexpr bool ingress_reference_candidate(TContainerState state) noexcept
{
    return state == TContainerState::default_empty || state == TContainerState::ingress_ready || state == TContainerState::ingress_round_member || state == TContainerState::receiving;
}

[[nodiscard]] constexpr bool dispatch_reference_candidate(TContainerState state) noexcept
{
    return state == TContainerState::dispatch_candidate || state == TContainerState::dispatch_round_member;
}

} // namespace circulation_mechanism
} // namespace assembler
