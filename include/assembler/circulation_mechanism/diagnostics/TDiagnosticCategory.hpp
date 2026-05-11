#pragma once

#include <cstdint>

/*
    TDiagnosticCategory.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines broad diagnostic categories.

    Production capabilities:
        - Stable diagnostic vocabulary.
        - constexpr-friendly classification.
        - No logging/recovery/export behavior.

    Explicit non-ownership:
        - Does not execute recovery.
        - Does not mutate runtime state.
        - Does not export telemetry.
        - Does not own bridge/read-side lifecycle.
*/

namespace assembler {
namespace circulation_mechanism {


enum class TDiagnosticCategory : std::uint8_t
{
    invariant_violation,
        state_mismatch,
        reference_fault,
        safe_point_violation,
        profile_failure,
        boundary_assumption_failure,
        eviction_event,
        operational_report,
        diagnostic_only,
        capacity_issue,
        read_side_issue,
        integration_issue
};

} // namespace circulation_mechanism
} // namespace assembler
