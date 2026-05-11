#pragma once
#include "TCirculationDiagnosticExportReportId.hpp"
#include "TCirculationDiagnosticExportIssueKind.hpp"
#include "../export_boundary/TCirculationDiagnosticExportMediumKind.hpp"

/*
    TCirculationDiagnosticExportReport.hpp

    Responsibility:
        Evidence report for diagnostic export boundary validation.

    Non-ownership:
        Does not export records.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

struct TCirculationDiagnosticExportReport final {
    TCirculationDiagnosticExportReportId report_id{};
    TCirculationDiagnosticExportMediumKind medium{TCirculationDiagnosticExportMediumKind::none};
    TCirculationDiagnosticExportIssueKind issue{TCirculationDiagnosticExportIssueKind::none};
    std::uint32_t record_count{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return report_id.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid() && issue == TCirculationDiagnosticExportIssueKind::none && record_count > 0U;
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
