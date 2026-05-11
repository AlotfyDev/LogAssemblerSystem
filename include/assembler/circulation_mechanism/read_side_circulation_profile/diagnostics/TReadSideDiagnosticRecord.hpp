#pragma once

#include "TReadSideDiagnosticId.hpp"
#include "TReadSideDiagnosticKind.hpp"
#include "TReadSideDiagnosticSeverity.hpp"

    /*
        TReadSideDiagnosticRecord.hpp

        Delivery:
            CME-RSCP-PROD-W04 — Diagnostics And Addon Boundary Integration

        Current responsibility:
            Production-grade read-side diagnostic record.

        Production capabilities:
            - identifies diagnostic record,
            - classifies condition kind,
            - classifies severity,
            - provides issue/no-issue helpers,
            - provides blocking severity helper.

        Architectural role:
            Diagnostics describe read-side profile conditions. They do not execute
            recovery and do not invoke addon behavior.

        Explicit non-ownership:
            - Does not retry.
            - Does not release.
            - Does not persist.
            - Does not export telemetry.
            - Does not invoke addon behavior.
    */
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideDiagnosticRecord final {
    TReadSideDiagnosticId diagnostic_id{};
    TReadSideDiagnosticKind kind{TReadSideDiagnosticKind::none};
    TReadSideDiagnosticSeverity severity{TReadSideDiagnosticSeverity::info};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return diagnostic_id.is_valid();
    }

    [[nodiscard]] constexpr bool has_issue() const noexcept {
        return kind != TReadSideDiagnosticKind::none;
    }

    [[nodiscard]] constexpr bool is_error_or_worse() const noexcept {
        return severity == TReadSideDiagnosticSeverity::error
            || severity == TReadSideDiagnosticSeverity::critical
            || severity == TReadSideDiagnosticSeverity::fatal;
    }

    [[nodiscard]] constexpr bool blocks_integration() const noexcept {
        return has_issue() && is_error_or_worse();
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
