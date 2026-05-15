#pragma once
#include "assembler/communication_context/facade_layer/common/TDiagnosticFacadeEvidenceAdapter.hpp"

/**
 * @file TAsccDiagnosticAdmissionPolicy.hpp
 * @brief Managerial facade policy for ASCC diagnostic subsystem admission.
 */
namespace assembler::communication_context {
    struct TAsccDiagnosticAdmissionPolicy final {
        [[nodiscard]] static constexpr TAsccDiagnosticReadinessView admit(
            TDiagnosticRuntimeReport report,
            bool collector_valid,
            bool policy_valid,
            bool sources_registered) noexcept
        {
            return TDiagnosticFacadeEvidenceAdapter::to_readiness_view(
                report,
                collector_valid,
                policy_valid,
                sources_registered);
        }
    };
}
