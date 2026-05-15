#pragma once
#include <cstddef>
#include "assembler/communication_context/diagnostics/severity/TDiagnosticSeverity.hpp"

/**
 * @file TDiagnosticRuntimeReport.hpp
 * @brief Component-level diagnostic runtime report.
 */
namespace assembler::communication_context {
    struct TDiagnosticRuntimeReport final {
        std::size_t accepted_records{0u};
        std::size_t rejected_records{0u};
        std::size_t failure_count{0u};
        TDiagnosticSeverity highest_severity{TDiagnosticSeverity::none};
        std::size_t enabled_source_count{0u};

        [[nodiscard]] constexpr bool clean() const noexcept {
            return failure_count == 0u
                && !is_failure_diagnostic_severity(highest_severity);
        }
    };
}
