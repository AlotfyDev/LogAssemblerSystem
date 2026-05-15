#pragma once
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"

/**
 * @file TBoundaryHandoffLifecycleController.hpp
 * @brief Lifecycle helper for boundary handoff status transitions.
 */
namespace assembler::communication_context {
    struct TBoundaryHandoffLifecycleController final {
        [[nodiscard]] static constexpr bool can_complete(TBoundaryHandoffResult result) noexcept { return result.accepted(); }
        [[nodiscard]] static constexpr bool is_terminal(TBoundaryHandoffResult result) noexcept { return result.completed() || result.failed() || result.deferred(); }
    };
}
