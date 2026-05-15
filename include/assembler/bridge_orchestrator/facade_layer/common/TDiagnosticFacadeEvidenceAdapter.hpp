#pragma once
#include "assembler/communication_context/diagnostics/runtime/TDiagnosticRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccDiagnosticReadinessView.hpp"

/**
 * @file TDiagnosticFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for diagnostic runtime evidence.
 */
namespace assembler::communication_context {
    struct TDiagnosticFacadeEvidenceAdapter final {
        [[nodiscard]] static constexpr TAsccDiagnosticReadinessView to_readiness_view(
            TDiagnosticRuntimeReport report,
            bool collector_valid,
            bool policy_valid,
            bool sources_registered) noexcept
        {
            const bool ready = collector_valid && policy_valid && sources_registered;
            return TAsccDiagnosticReadinessView{
                ready ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked,
                report,
                collector_valid,
                policy_valid,
                sources_registered,
                "diagnostic readiness"
            };
        }
    };
}
