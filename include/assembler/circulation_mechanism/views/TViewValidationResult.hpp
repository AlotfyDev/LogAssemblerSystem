#pragma once

#include "TViewContractIssueKind.hpp"

/*
    TViewValidationResult.hpp

    Delivery:
        CME-VIEWS-PROD-W01 — Production Read-Only Projection Contract

    Current responsibility:
        Carries the result of validating a read-only view descriptor.

    Production capabilities:
        - accepted/rejected signal.
        - issue kind.
        - constexpr helpers.

    Non-ownership:
        - Does not mutate the view.
        - Does not log or report externally.
        - Does not create diagnostics collector state.
*/

namespace assembler {
namespace circulation_mechanism {


struct TViewValidationResult final
{
    bool accepted{false};
    TViewContractIssueKind issue{TViewContractIssueKind::unknown};

    [[nodiscard]] constexpr bool rejected() const noexcept
    {
        return !accepted;
    }
};

[[nodiscard]] constexpr TViewValidationResult accepted_view_contract() noexcept
{
    return TViewValidationResult{true, TViewContractIssueKind::none};
}

[[nodiscard]] constexpr TViewValidationResult rejected_view_contract(TViewContractIssueKind issue) noexcept
{
    return TViewValidationResult{false, issue};
}

} // namespace circulation_mechanism
} // namespace assembler
