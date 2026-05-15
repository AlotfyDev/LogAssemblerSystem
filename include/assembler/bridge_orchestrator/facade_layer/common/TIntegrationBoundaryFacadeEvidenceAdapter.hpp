#pragma once
#include "assembler/communication_context/facade_layer/managerial/TAsccIntegrationBoundaryReadinessView.hpp"

/**
 * @file TIntegrationBoundaryFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for integration boundary runtime evidence.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryFacadeEvidenceAdapter final {
        [[nodiscard]] static constexpr TAsccIntegrationBoundaryReadinessView to_readiness_view(
            TIntegrationBoundaryRuntimeView view,
            TBoundaryHandoffRuntimeReport report) noexcept
        {
            return {
                view.ready() ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked,
                view,
                report,
                "integration boundary readiness"
            };
        }
    };
}
