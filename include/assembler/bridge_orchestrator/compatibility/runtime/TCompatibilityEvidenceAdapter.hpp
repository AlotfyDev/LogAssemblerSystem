#pragma once
#include "assembler/communication_context/compatibility/reports/TCompatibilityRuntimeReport.hpp"

/**
 * @file TCompatibilityEvidenceAdapter.hpp
 * @brief Internal compatibility evidence adapter.
 */
namespace assembler::communication_context {
    struct TCompatibilityEvidenceAdapter final {
        template <std::size_t MatrixCapacity>
        [[nodiscard]] static constexpr bool evidence_passed(TCompatibilityRuntimeReport<MatrixCapacity> report) noexcept {
            return report.compatible();
        }
    };
}
