#pragma once

#include "TDiagnosticSeverity.hpp"
#include "TDiagnosticCategory.hpp"
#include "TDiagnosticIssueKind.hpp"

/*
    TDiagnosticClassifiers.hpp

    Responsibility:
        Provides constexpr classification helpers for diagnostic severities and
        issue kinds.

    Non-ownership:
        Does not emit, store, log, or recover diagnostics.
*/

namespace assembler {
namespace circulation_mechanism {


[[nodiscard]] constexpr bool is_error_or_worse(TDiagnosticSeverity severity) noexcept
{
    return severity == TDiagnosticSeverity::error
        || severity == TDiagnosticSeverity::critical
        || severity == TDiagnosticSeverity::fatal;
}

[[nodiscard]] constexpr bool is_terminal_severity(TDiagnosticSeverity severity) noexcept
{
    return severity == TDiagnosticSeverity::fatal;
}

[[nodiscard]] constexpr bool is_invariant_category(TDiagnosticCategory category) noexcept
{
    return category == TDiagnosticCategory::invariant_violation;
}

[[nodiscard]] constexpr bool is_boundary_category(TDiagnosticCategory category) noexcept
{
    return category == TDiagnosticCategory::boundary_assumption_failure
        || category == TDiagnosticCategory::integration_issue;
}

[[nodiscard]] constexpr bool is_reference_issue(TDiagnosticIssueKind issue) noexcept
{
    return issue == TDiagnosticIssueKind::reference_stale
        || issue == TDiagnosticIssueKind::reference_direction_mismatch;
}

[[nodiscard]] constexpr bool is_safety_issue(TDiagnosticIssueKind issue) noexcept
{
    return issue == TDiagnosticIssueKind::safe_point_unavailable
        || issue == TDiagnosticIssueKind::unsafe_transition;
}

} // namespace circulation_mechanism
} // namespace assembler
