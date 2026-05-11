#pragma once

#include <cstdint>

/*
    TDiagnosticSeverity.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines diagnostic severity.

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


enum class TDiagnosticSeverity : std::uint8_t
{
    trace,
        info,
        warning,
        error,
        critical,
        fatal
};

} // namespace circulation_mechanism
} // namespace assembler
