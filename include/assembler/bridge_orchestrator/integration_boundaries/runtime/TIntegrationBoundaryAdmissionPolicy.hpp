#pragma once
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryMaterialClassifier.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryRuntimeContext.hpp"

/**
 * @file TIntegrationBoundaryAdmissionPolicy.hpp
 * @brief Admission policy for ASCC integration boundary handoff.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryAdmissionPolicy final {
        [[nodiscard]] static constexpr bool admits(TIntegrationBoundaryRuntimeContext context) noexcept {
            return context.is_valid() && TIntegrationBoundaryMaterialClassifier::accepts_material(context.request);
        }
    };
}
