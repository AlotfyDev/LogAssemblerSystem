#pragma once
#include "TCapacityIssueKind.hpp"

/*
    TCapacityValidationResult.hpp

    Responsibility:
        Carries result of validating a capacity profile or scaling plan.
*/

namespace assembler {
namespace circulation_mechanism {

struct TCapacityValidationResult final
{
    bool accepted{false};
    TCapacityIssueKind issue{TCapacityIssueKind::none};

    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted; }
};

[[nodiscard]] constexpr TCapacityValidationResult accepted_capacity() noexcept
{
    return TCapacityValidationResult{true, TCapacityIssueKind::none};
}

[[nodiscard]] constexpr TCapacityValidationResult rejected_capacity(TCapacityIssueKind issue) noexcept
{
    return TCapacityValidationResult{false, issue};
}
} // namespace circulation_mechanism
} // namespace assembler
