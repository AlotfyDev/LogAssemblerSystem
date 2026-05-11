#pragma once

#include "TSafePointIssueKind.hpp"

/*
    TSafePointGuardResult.hpp

    Responsibility:
        Carries safe-point guard/claim validation result.

    Non-ownership:
        Does not execute the protected operation.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSafePointGuardResult final
{
    bool accepted{false};
    TSafePointIssueKind issue{TSafePointIssueKind::none};

    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted; }
};

[[nodiscard]] constexpr TSafePointGuardResult accepted_safe_point() noexcept
{
    return TSafePointGuardResult{true, TSafePointIssueKind::none};
}

[[nodiscard]] constexpr TSafePointGuardResult rejected_safe_point(TSafePointIssueKind issue) noexcept
{
    return TSafePointGuardResult{false, issue};
}

} // namespace circulation_mechanism
} // namespace assembler
