#pragma once
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"

/**
 * @file TBoundaryHandoffRuntimeReport.hpp
 * @brief Runtime evidence report for an integration boundary handoff.
 */
namespace assembler::communication_context {
    struct TBoundaryHandoffRuntimeReport final {
        TBoundaryHandoffRequest request{};
        TReadinessView readiness{};
        TBoundaryHandoffResult accept_result{};
        TBoundaryHandoffResult final_result{};
        bool lifecycle_completed{false};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return request.is_valid(); }
        [[nodiscard]] constexpr bool succeeded() const noexcept { return is_valid() && lifecycle_completed && final_result.completed(); }
    };
}
