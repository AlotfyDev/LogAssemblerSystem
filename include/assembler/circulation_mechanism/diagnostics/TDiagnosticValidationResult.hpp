#pragma once

#include "TDiagnosticIssue.hpp"

/*
    TDiagnosticValidationResult.hpp

    Responsibility:
        Carries result of diagnostic contract validation.

    Non-ownership:
        Does not execute diagnostics or recovery.
*/

namespace assembler {
namespace circulation_mechanism {


struct TDiagnosticValidationResult final
{
    bool accepted{false};
    TDiagnosticIssue issue{};

    [[nodiscard]] constexpr bool rejected() const noexcept
    {
        return !accepted;
    }
};

[[nodiscard]] constexpr TDiagnosticValidationResult accepted_diagnostic_contract() noexcept
{
    return TDiagnosticValidationResult{true, TDiagnosticIssue::none()};
}

[[nodiscard]] constexpr TDiagnosticValidationResult rejected_diagnostic_contract(TDiagnosticIssue issue) noexcept
{
    return TDiagnosticValidationResult{false, issue};
}

} // namespace circulation_mechanism
} // namespace assembler
