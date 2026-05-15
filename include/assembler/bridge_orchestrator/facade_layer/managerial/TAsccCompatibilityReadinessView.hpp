#pragma once
#include <string_view>
#include "assembler/communication_context/compatibility/reports/TCompatibilityRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"

/**
 * @file TAsccCompatibilityReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC compatibility.
 */
namespace assembler::communication_context {
    template <std::size_t MatrixCapacity>
    struct TAsccCompatibilityReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TCompatibilityRuntimeReport<MatrixCapacity> runtime_report{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown && runtime_report.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status == TAsccComponentReadinessStatus::ready && runtime_report.compatible(); }
    };
}
