#pragma once

#include "TDiagnosticIssue.hpp"

/*
    TInvariantViolationReport.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Current responsibility:
        Defines a production-grade invariant violation evidence carrier.

    Production capabilities:
        - Wraps a diagnostic issue.
        - Requires invariant category.
        - Records whether operation should be blocked.
        - Does not recover automatically.

    Explicit non-ownership:
        - Does not repair invariants.
        - Does not log/export.
        - Does not mutate runtime state.
*/

namespace assembler {
namespace circulation_mechanism {


struct TInvariantViolationReport final
{
    TDiagnosticIssue issue{};
    bool block_operation{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return issue.is_valid() && issue.is_invariant();
    }

    [[nodiscard]] constexpr bool should_block() const noexcept
    {
        return is_valid() && block_operation;
    }
};

} // namespace circulation_mechanism
} // namespace assembler
