#pragma once

#include <cstdint>

/*
    TDiagnosticResolutionHint.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines non-executing resolution hints for diagnostics.

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


enum class TDiagnosticResolutionHint : std::uint8_t
{
    none,
        reject_operation,
        invalidate_reference,
        wait_for_safe_point,
        rebuild_view,
        emit_report,
        defer_to_read_side,
        defer_to_bridge,
        manual_review,
        fix_configuration
};

} // namespace circulation_mechanism
} // namespace assembler
