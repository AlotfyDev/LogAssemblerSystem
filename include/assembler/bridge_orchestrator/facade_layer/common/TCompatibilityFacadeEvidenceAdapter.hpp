#pragma once
#include "assembler/communication_context/compatibility/reports/TCompatibilityRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccCompatibilityReadinessView.hpp"

/**
 * @file TCompatibilityFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for compatibility runtime evidence.
 */
namespace assembler::communication_context {
    struct TCompatibilityFacadeEvidenceAdapter final {
        template <std::size_t MatrixCapacity>
        [[nodiscard]] static constexpr TAsccCompatibilityReadinessView<MatrixCapacity> to_readiness_view(TCompatibilityRuntimeReport<MatrixCapacity> report) noexcept {
            return {report.compatible() ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, report, "compatibility readiness"};
        }
    };
}
