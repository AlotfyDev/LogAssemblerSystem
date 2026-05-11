#pragma once

#include "TReportDescriptor.hpp"

/*
    TOperationalReport.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Defines a production-grade operational report wrapper.

    Production capabilities:
        - Wraps a validated operational report descriptor.
        - Provides constexpr validity helpers.
        - Preserves that operational reports are evidence only.

    Explicit non-ownership:
        - Does not execute the operation it reports.
        - Does not prove downstream success.
        - Does not trigger recovery.
*/

namespace assembler {
namespace circulation_mechanism {


struct TOperationalReport final
{
    TReportDescriptor descriptor{};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return descriptor.is_valid()
            && descriptor.kind() == TReportKind::operational
            && descriptor.validate().accepted;
    }

    [[nodiscard]] constexpr bool is_complete() const noexcept
    {
        return descriptor.is_complete();
    }
};

} // namespace circulation_mechanism
} // namespace assembler
