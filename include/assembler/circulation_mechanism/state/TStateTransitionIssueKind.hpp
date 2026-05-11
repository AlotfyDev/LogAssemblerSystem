#pragma once

#include <cstdint>

/*
    TStateTransitionIssueKind.hpp

    Delivery:
        CME-STATE-PROD-W01 — Production Transition Contract

    Responsibility:
        Classifies why a transition may be rejected.
*/

namespace assembler {
namespace circulation_mechanism {

enum class TStateTransitionIssueKind : std::uint8_t
{
    none,
    same_state,
    invalid_transition,
    terminal_state,
    error_state,
    unknown_state_family
};
} // namespace circulation_mechanism
} // namespace assembler
