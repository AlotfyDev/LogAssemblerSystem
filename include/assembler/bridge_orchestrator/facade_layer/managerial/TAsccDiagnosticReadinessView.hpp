#pragma once
#include <string_view>
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"

/**
 * @file TAsccDiagnosticReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC diagnostics.
 */
namespace assembler::communication_context {
    struct TAsccDiagnosticReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TDiagnosticRuntimeReport runtime_report{};
        bool collector_valid{false};
        bool policy_valid{false};
        bool sources_registered{false};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept {
            return status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept {
            return is_valid()
                && status == TAsccComponentReadinessStatus::ready
                && collector_valid
                && policy_valid
                && sources_registered;
        }
    };
}
