#pragma once
#include "TCirculationDiagnosticExportBoundaryDescriptor.hpp"
#include "../collector/TCirculationDiagnosticSnapshot.hpp"
#include "../reports/TCirculationDiagnosticExportIssueKind.hpp"

/*
    TCirculationDiagnosticExportPolicy.hpp

    Current responsibility:
        Evaluates whether diagnostic snapshot may be exported through a declared boundary.

    Non-ownership:
        Does not perform export.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

struct TCirculationDiagnosticExportPolicy final {
    template <std::size_t Capacity>
    [[nodiscard]] static constexpr TCirculationDiagnosticExportIssueKind validate(
        TCirculationDiagnosticSnapshot<Capacity> snapshot,
        TCirculationDiagnosticExportBoundaryDescriptor boundary,
        bool external_runtime_available) noexcept
    {
        if (!boundary.is_valid()) return TCirculationDiagnosticExportIssueKind::boundary_invalid;
        if (!boundary.ready(external_runtime_available)) return TCirculationDiagnosticExportIssueKind::boundary_not_ready;
        if (snapshot.empty()) return TCirculationDiagnosticExportIssueKind::snapshot_empty;
        return TCirculationDiagnosticExportIssueKind::none;
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
