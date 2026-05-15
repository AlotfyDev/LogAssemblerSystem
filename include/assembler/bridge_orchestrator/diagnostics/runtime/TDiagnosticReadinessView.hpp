#pragma once
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRuntimeReport.hpp"

/**
 * @file TDiagnosticReadinessView.hpp
 * @brief Runtime readiness projection for ASCC diagnostics.
 */
namespace assembler::communication_context {
    struct TDiagnosticReadinessView final {
        TDiagnosticRuntimeReport runtime_report{};
        bool policy_valid{false};
        bool collector_valid{false};
        bool sources_registered{false};

        [[nodiscard]] constexpr bool ready() const noexcept {
            return policy_valid && collector_valid && sources_registered;
        }
    };
}
