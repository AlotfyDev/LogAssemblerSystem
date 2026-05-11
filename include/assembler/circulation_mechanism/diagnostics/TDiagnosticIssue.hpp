#pragma once

#include "TDiagnosticIssueId.hpp"
#include "TDiagnosticCategory.hpp"
#include "TDiagnosticIssueKind.hpp"
#include "TDiagnosticSeverity.hpp"
#include "TDiagnosticResolutionHint.hpp"
#include "TDiagnosticClassifiers.hpp"

/*
    TDiagnosticIssue.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines immutable diagnostic issue contract.

    Production capabilities:
        - Issue identity.
        - Category, kind, severity, and resolution hint.
        - Validation helpers.
        - Severity classification helpers.
        - Non-executing resolution guidance.

    Architectural role:
        A diagnostic issue classifies an observed condition. It is not hidden
        control flow and not recovery execution.

    Explicit non-ownership:
        - Does not recover.
        - Does not retry.
        - Does not log/export.
        - Does not mutate runtime components.
*/

namespace assembler {
namespace circulation_mechanism {


class TDiagnosticIssue final
{
public:
    constexpr TDiagnosticIssue() noexcept = default;

    constexpr TDiagnosticIssue(
        TDiagnosticIssueId id,
        TDiagnosticCategory category,
        TDiagnosticIssueKind kind,
        TDiagnosticSeverity severity,
        TDiagnosticResolutionHint hint = TDiagnosticResolutionHint::none) noexcept
        : id_(id), category_(category), kind_(kind), severity_(severity), hint_(hint)
    {
    }

    [[nodiscard]] static constexpr TDiagnosticIssue none() noexcept
    {
        return TDiagnosticIssue{TDiagnosticIssueId::invalid(), TDiagnosticCategory::diagnostic_only, TDiagnosticIssueKind::none, TDiagnosticSeverity::trace};
    }

    [[nodiscard]] static constexpr TDiagnosticIssue invariant(
        TDiagnosticIssueId id,
        TDiagnosticIssueKind kind,
        TDiagnosticSeverity severity = TDiagnosticSeverity::error) noexcept
    {
        return TDiagnosticIssue{id, TDiagnosticCategory::invariant_violation, kind, severity, TDiagnosticResolutionHint::reject_operation};
    }

    [[nodiscard]] constexpr TDiagnosticIssueId id() const noexcept { return id_; }
    [[nodiscard]] constexpr TDiagnosticCategory category() const noexcept { return category_; }
    [[nodiscard]] constexpr TDiagnosticIssueKind kind() const noexcept { return kind_; }
    [[nodiscard]] constexpr TDiagnosticSeverity severity() const noexcept { return severity_; }
    [[nodiscard]] constexpr TDiagnosticResolutionHint hint() const noexcept { return hint_; }

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return kind_ == TDiagnosticIssueKind::none || id_.is_valid();
    }

    [[nodiscard]] constexpr bool has_issue() const noexcept
    {
        return kind_ != TDiagnosticIssueKind::none;
    }

    [[nodiscard]] constexpr bool is_error() const noexcept
    {
        return is_error_or_worse(severity_);
    }

    [[nodiscard]] constexpr bool is_invariant() const noexcept
    {
        return category_ == TDiagnosticCategory::invariant_violation;
    }

private:
    TDiagnosticIssueId id_{TDiagnosticIssueId::invalid()};
    TDiagnosticCategory category_{TDiagnosticCategory::diagnostic_only};
    TDiagnosticIssueKind kind_{TDiagnosticIssueKind::none};
    TDiagnosticSeverity severity_{TDiagnosticSeverity::trace};
    TDiagnosticResolutionHint hint_{TDiagnosticResolutionHint::none};
};

static_assert(!std::is_aggregate<TDiagnosticIssue>::value,
    "TDiagnosticIssue must not expose mutable aggregate fields.");

} // namespace circulation_mechanism
} // namespace assembler
