#pragma once

#include <cstdint>
#include "TDiagnosticIssue.hpp"

/*
    TDiagnosticCollector.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines a minimal non-owning collector contract for diagnostic counting.

    Production capabilities:
        - Count accepted diagnostic issues.
        - Track highest severity.
        - Stay header-only and allocation-free.
        - Avoid logging/export/recovery behavior.

    Architectural role:
        Collector is an in-memory diagnostic aggregation contract, not a logging
        framework and not telemetry export.

    Explicit non-ownership:
        - Does not persist diagnostics.
        - Does not export telemetry.
        - Does not execute recovery.
        - Does not call bridge/read-side.
*/

namespace assembler {
namespace circulation_mechanism {


class TDiagnosticCollector final
{
public:
    constexpr TDiagnosticCollector() noexcept = default;

    constexpr bool accept(TDiagnosticIssue issue) noexcept
    {
        if (!issue.is_valid() || !issue.has_issue())
        {
            return false;
        }

        ++issue_count_;
        if (static_cast<std::uint8_t>(issue.severity()) > static_cast<std::uint8_t>(highest_severity_))
        {
            highest_severity_ = issue.severity();
        }
        return true;
    }

    [[nodiscard]] constexpr std::uint32_t issue_count() const noexcept
    {
        return issue_count_;
    }

    [[nodiscard]] constexpr TDiagnosticSeverity highest_severity() const noexcept
    {
        return highest_severity_;
    }

    [[nodiscard]] constexpr bool has_errors() const noexcept
    {
        return is_error_or_worse(highest_severity_);
    }

private:
    std::uint32_t issue_count_{0};
    TDiagnosticSeverity highest_severity_{TDiagnosticSeverity::trace};
};

} // namespace circulation_mechanism
} // namespace assembler
