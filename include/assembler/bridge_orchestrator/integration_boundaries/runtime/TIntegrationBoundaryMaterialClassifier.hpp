#pragma once
#include <string_view>
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"

/**
 * @file TIntegrationBoundaryMaterialClassifier.hpp
 * @brief Classifies boundary handoff material for admission.
 */
namespace assembler::communication_context {
    struct TIntegrationBoundaryMaterialClassifier final {
        [[nodiscard]] static constexpr bool accepts_material(TBoundaryHandoffRequest request, std::string_view expected_kind = {}) noexcept {
            return request.is_valid() && (expected_kind.empty() || request.material_kind == expected_kind);
        }
    };
}
