#pragma once
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationInvocationContext.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationInvocationResult.hpp"

/**
 * @file TObligationInvocationReport.hpp
 * @brief Evidence report for one ASCC obligation invocation.
 */
namespace assembler::communication_context {
    struct TObligationInvocationReport final {
        TObligationInvocationContext context{};
        TObligationInvocationResult result{};
        TObligationReport surface_report{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return context.is_valid(); }
        [[nodiscard]] constexpr bool succeeded() const noexcept { return is_valid() && result.succeeded() && surface_report.is_satisfied(); }
    };
}
