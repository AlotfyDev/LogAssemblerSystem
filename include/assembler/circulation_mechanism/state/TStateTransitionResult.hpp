#pragma once

#include "TStateTransitionIssueKind.hpp"

/*
    TStateTransitionResult.hpp

    Delivery:
        CME-STATE-PROD-W01 — Production Transition Contract

    Responsibility:
        Generic transition result carrier used by state contract helpers.

    Non-ownership:
        This result does not execute transitions or mutate component state.
*/

namespace assembler {
namespace circulation_mechanism {

struct TStateTransitionResult final
{
    bool accepted{false};
    TStateTransitionIssueKind issue{TStateTransitionIssueKind::none};

    [[nodiscard]] constexpr bool rejected() const noexcept
    {
        return !accepted;
    }
};

[[nodiscard]] constexpr TStateTransitionResult accepted_transition() noexcept
{
    return TStateTransitionResult{true, TStateTransitionIssueKind::none};
}

[[nodiscard]] constexpr TStateTransitionResult rejected_transition(TStateTransitionIssueKind issue) noexcept
{
    return TStateTransitionResult{false, issue};
}

} // namespace circulation_mechanism
} // namespace assembler
