#pragma once
#include "TCirculationDiagnosticSourceKind.hpp"
#include "TCirculationDiagnosticKind.hpp"
#include "TCirculationDiagnosticSeverity.hpp"

/*
    TCirculationDiagnosticRecord.hpp

    Current responsibility:
        Unified diagnostic record for core, PreBridge, ReadSide, and boundary diagnostics.

    Production capabilities:
        - source classification
        - kind classification
        - severity classification
        - issue/no-issue helpers
        - blocking severity helper

    Explicit non-ownership:
        - Does not execute recovery.
        - Does not export itself.
        - Does not mutate runtime.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

struct TCirculationDiagnosticRecord final {
    TCirculationDiagnosticSourceKind source{TCirculationDiagnosticSourceKind::unknown};
    TCirculationDiagnosticKind kind{TCirculationDiagnosticKind::none};
    TCirculationDiagnosticSeverity severity{TCirculationDiagnosticSeverity::info};
    std::uint64_t sequence{0};

    [[nodiscard]] constexpr bool has_issue() const noexcept {
        return kind != TCirculationDiagnosticKind::none;
    }

    [[nodiscard]] constexpr bool is_error_or_worse() const noexcept {
        return severity == TCirculationDiagnosticSeverity::error
            || severity == TCirculationDiagnosticSeverity::critical
            || severity == TCirculationDiagnosticSeverity::fatal;
    }

    [[nodiscard]] constexpr bool blocks_readiness() const noexcept {
        return has_issue() && is_error_or_worse();
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
