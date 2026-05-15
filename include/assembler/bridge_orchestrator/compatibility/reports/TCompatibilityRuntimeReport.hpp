#pragma once
#include "assembler/communication_context/compatibility/matrix/TCompatibilityMatrix.hpp"
#include "assembler/communication_context/compatibility/reports/TCompatibilityDimensionCoverageReport.hpp"

/**
 * @file TCompatibilityRuntimeReport.hpp
 * @brief Multi-dimensional ASCC compatibility runtime report.
 */
namespace assembler::communication_context {
    template <std::size_t MatrixCapacity>
    struct TCompatibilityRuntimeReport final {
        TCompatibilityMatrix<MatrixCapacity> matrix{};
        TCompatibilityDimensionCoverageReport coverage{};
        bool runtime_valid{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return runtime_valid && coverage.is_valid(); }
        [[nodiscard]] constexpr bool compatible() const noexcept { return is_valid() && matrix.compatible(); }
        [[nodiscard]] constexpr bool fully_covered_and_compatible() const noexcept { return compatible() && coverage.full_component_coverage(); }
    };
}
