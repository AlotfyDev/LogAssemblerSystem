#pragma once
#include "assembler/communication_context/compatibility/reports/TCompatibilityRuntimeReport.hpp"

/**
 * @file TCompatibilityAdmissionPolicy.hpp
 * @brief Policy deciding whether compatibility evidence permits ASCC component admission.
 */
namespace assembler::communication_context {
    struct TCompatibilityAdmissionPolicy final {
        template <std::size_t MatrixCapacity>
        [[nodiscard]] static constexpr bool admits(TCompatibilityRuntimeReport<MatrixCapacity> report) noexcept {
            return report.compatible();
        }
    };
}
