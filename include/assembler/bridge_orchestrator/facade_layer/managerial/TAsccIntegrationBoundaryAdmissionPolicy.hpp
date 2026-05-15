#pragma once
#include "assembler/communication_context/facade_layer/common/TIntegrationBoundaryFacadeEvidenceAdapter.hpp"

/**
 * @file TAsccIntegrationBoundaryAdmissionPolicy.hpp
 * @brief Managerial facade policy for integration boundary admission.
 */
namespace assembler::communication_context {
    struct TAsccIntegrationBoundaryAdmissionPolicy final {
        [[nodiscard]] static constexpr TAsccIntegrationBoundaryReadinessView admit(
            TIntegrationBoundaryRuntimeView view,
            TBoundaryHandoffRuntimeReport report) noexcept
        {
            return TIntegrationBoundaryFacadeEvidenceAdapter::to_readiness_view(view, report);
        }
    };
}
