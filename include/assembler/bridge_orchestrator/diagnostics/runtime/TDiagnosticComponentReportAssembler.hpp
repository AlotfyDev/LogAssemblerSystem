#pragma once
#include "assembler/communication_context/diagnostics/reports/TDiagnosticReport.hpp"

/**
 * @file TDiagnosticComponentReportAssembler.hpp
 * @brief Assembles component-level diagnostic reports from bounded diagnostic records.
 */
namespace assembler::communication_context {
    struct TDiagnosticComponentReportAssembler final {
        template <std::size_t Capacity>
        [[nodiscard]] static constexpr TDiagnosticReport<Capacity> passthrough(TDiagnosticReport<Capacity> report) noexcept {
            return report;
        }
    };
}
