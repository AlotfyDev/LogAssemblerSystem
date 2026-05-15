#pragma once
#include <string_view>
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationRuntimeView.hpp"

/**
 * @file TAsccObligationReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC obligations.
 */
namespace assembler::communication_context {
    struct TAsccObligationReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TObligationReport surface_report{};
        TObligationRuntimeView runtime_view{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown; }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status == TAsccComponentReadinessStatus::ready && surface_report.is_satisfied() && runtime_view.ready(); }
    };
}
