#pragma once

#include "TReportContractIssueKind.hpp"

/*
    TReportValidationResult.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Carries validation result for a report contract.

    Explicit non-ownership:
        - Does not emit reports.
        - Does not recover.
        - Does not mutate runtime state.
*/

namespace assembler {
namespace circulation_mechanism {


struct TReportValidationResult final
{
    bool accepted{false};
    TReportContractIssueKind issue{TReportContractIssueKind::unknown};

    [[nodiscard]] constexpr bool rejected() const noexcept
    {
        return !accepted;
    }
};

[[nodiscard]] constexpr TReportValidationResult accepted_report_contract() noexcept
{
    return TReportValidationResult{true, TReportContractIssueKind::none};
}

[[nodiscard]] constexpr TReportValidationResult rejected_report_contract(TReportContractIssueKind issue) noexcept
{
    return TReportValidationResult{false, issue};
}

} // namespace circulation_mechanism
} // namespace assembler
