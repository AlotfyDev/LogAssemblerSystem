#pragma once

#include <cstdint>

/*
    TReportEvidenceKind.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Classifies the evidence semantics of a report.

    Production capabilities:
        - Stable report vocabulary.
        - constexpr-friendly classification support.
        - No runtime action or recovery behavior.

    Explicit non-ownership:
        - Does not execute behavior.
        - Does not export telemetry.
        - Does not mutate component state.
        - Does not prove downstream success.
*/

namespace assembler {
namespace circulation_mechanism {


enum class TReportEvidenceKind : std::uint8_t
{
    action_attempted,
        action_completed,
        transition_observed,
        diagnostic_detected,
        invariant_checked,
        boundary_observed,
        readiness_evaluated
};

} // namespace circulation_mechanism
} // namespace assembler
