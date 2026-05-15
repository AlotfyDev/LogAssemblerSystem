#pragma once
#include "assembler/communication_context/facade_layer/common/TObligationFacadeEvidenceAdapter.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccObligationReadinessView.hpp"

/**
 * @file TAsccObligationAdmissionPolicy.hpp
 * @brief Managerial facade policy for ASCC obligation admission.
 */
namespace assembler::communication_context {
    struct TAsccObligationAdmissionPolicy final {
        [[nodiscard]] static constexpr TAsccObligationReadinessView admit(TObligationReport surface_report, TObligationRuntimeView runtime_view) noexcept {
            return TObligationFacadeEvidenceAdapter::to_readiness_view(surface_report, runtime_view);
        }
    };
}
