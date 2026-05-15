#pragma once
#include "assembler/communication_context/facade_layer/common/TCompatibilityFacadeEvidenceAdapter.hpp"

/**
 * @file TAsccCompatibilityAdmissionPolicy.hpp
 * @brief Managerial facade policy for ASCC compatibility admission.
 */
namespace assembler::communication_context {
    struct TAsccCompatibilityAdmissionPolicy final {
        template <std::size_t MatrixCapacity>
        [[nodiscard]] static constexpr TAsccCompatibilityReadinessView<MatrixCapacity> admit(TCompatibilityRuntimeReport<MatrixCapacity> report) noexcept {
            return TCompatibilityFacadeEvidenceAdapter::to_readiness_view(report);
        }
    };
}
