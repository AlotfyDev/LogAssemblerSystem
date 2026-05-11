#pragma once

#include <cstdint>

/*
    TDiagnosticIssueKind.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines specific diagnostic issue kinds.

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


enum class TDiagnosticIssueKind : std::uint8_t
{
    none,
        invalid_identity,
        invalid_view,
        invalid_report,
        invariant_violation,
        state_mismatch,
        reference_stale,
        reference_direction_mismatch,
        safe_point_unavailable,
        unsafe_transition,
        profile_incompatible,
        boundary_assumption_broken,
        eviction_blocked,
        capacity_insufficient,
        mutable_internal_exposure,
        downstream_proof_claim,
        unknown
};

} // namespace circulation_mechanism
} // namespace assembler
