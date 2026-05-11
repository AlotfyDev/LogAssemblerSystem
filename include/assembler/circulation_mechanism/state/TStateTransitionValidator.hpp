#pragma once

#include "TStateTransitionResult.hpp"
#include "TSlotState.hpp"
#include "TContainerState.hpp"
#include "TRoundState.hpp"
#include "TModeratorState.hpp"
#include "TBundleAgentState.hpp"
#include "TReferenceValidityState.hpp"
#include "TReferenceSupplyState.hpp"
#include "TSafePointState.hpp"
#include "TDispatchExposureState.hpp"

/*
    TStateTransitionValidator.hpp

    Delivery:
        CME-STATE-PROD-W01 — Production Transition Contract

    Responsibility:
        Provides constexpr transition validation overloads for all foundational
        state families.

    Non-ownership:
        Validation does not execute the transition. It only states whether a
        transition is allowed by the state contract.
*/

namespace assembler {
namespace circulation_mechanism {


[[nodiscard]] constexpr TStateTransitionResult validate_transition(TSlotState from_state, TSlotState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TContainerState from_state, TContainerState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TRoundState from_state, TRoundState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TModeratorState from_state, TModeratorState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TBundleAgentState from_state, TBundleAgentState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TReferenceValidityState from_state, TReferenceValidityState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TReferenceSupplyState from_state, TReferenceSupplyState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TSafePointState from_state, TSafePointState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

[[nodiscard]] constexpr TStateTransitionResult validate_transition(TDispatchExposureState from_state, TDispatchExposureState to_state) noexcept
{
    if (from_state == to_state)
    {
        return accepted_transition();
    }

    if (is_error(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::error_state);
    }

    if (is_terminal(from_state))
    {
        return rejected_transition(TStateTransitionIssueKind::terminal_state);
    }

    return can_transition(from_state, to_state)
        ? accepted_transition()
        : rejected_transition(TStateTransitionIssueKind::invalid_transition);
}

} // namespace circulation_mechanism
} // namespace assembler
