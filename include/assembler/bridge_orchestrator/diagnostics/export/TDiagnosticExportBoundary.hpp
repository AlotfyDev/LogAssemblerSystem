#pragma once
#include <string_view>
#include "assembler/communication_context/diagnostics/snapshots/TDiagnosticSnapshot.hpp"

/**
 * @file TDiagnosticExportBoundary.hpp
 * @brief Optional boundary contract for exporting diagnostic evidence.
 *
 * This is a contract boundary only. It does not implement file IO, network IO,
 * logging framework integration, telemetry export, or persistence.
 */
namespace assembler::communication_context {
    struct TDiagnosticExportBoundary final {
        std::string_view export_family{"diagnostic_export_boundary"};
        bool export_enabled{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return !export_family.empty();
        }

        [[nodiscard]] constexpr bool can_export(TDiagnosticSnapshot snapshot) const noexcept {
            return is_valid() && export_enabled && snapshot.is_valid();
        }
    };
}
