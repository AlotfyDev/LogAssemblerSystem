#pragma once
#include <string_view>
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TBoundaryHandoffRuntimeReport.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryRuntimeView.hpp"

/**
 * @file TAsccIntegrationBoundaryReadinessView.hpp
 * @brief Managerial facade readiness view for ASCC integration boundary runtime.
 */
namespace assembler::communication_context {
    struct TAsccIntegrationBoundaryReadinessView final {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TIntegrationBoundaryRuntimeView runtime_view{};
        TBoundaryHandoffRuntimeReport last_report{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown && runtime_view.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && status == TAsccComponentReadinessStatus::ready && runtime_view.ready(); }
    };
}
