#pragma once
#include "TCirculationDiagnosticExportBoundaryId.hpp"
#include "TCirculationDiagnosticExportMediumKind.hpp"
#include "TCirculationDiagnosticExportStatus.hpp"

/*
    TCirculationDiagnosticExportBoundaryDescriptor.hpp

    Current responsibility:
        Descriptor for diagnostic export boundary contract.

    Non-ownership:
        Does not implement file/telemetry/callback export.
*/
namespace assembler {
namespace circulation_mechanism {
namespace diagnostic_export {

struct TCirculationDiagnosticExportBoundaryDescriptor final {
    TCirculationDiagnosticExportBoundaryId boundary_id{};
    TCirculationDiagnosticExportMediumKind medium{TCirculationDiagnosticExportMediumKind::none};
    TCirculationDiagnosticExportStatus status{TCirculationDiagnosticExportStatus::undefined};
    bool external_runtime_required{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return boundary_id.is_valid() && medium != TCirculationDiagnosticExportMediumKind::none;
    }

    [[nodiscard]] constexpr bool ready(bool external_runtime_available) const noexcept {
        return is_valid()
            && status == TCirculationDiagnosticExportStatus::ready
            && (!external_runtime_required || external_runtime_available);
    }
};
} // namespace diagnostic_export
} // namespace circulation_mechanism
} // namespace assembler
