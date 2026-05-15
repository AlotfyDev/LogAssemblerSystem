#pragma once
#include "assembler/communication_context/integration_boundaries/runtime/TBoundaryHandoffRuntimeReport.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryAdmissionPolicy.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryRuntimeContext.hpp"
#include "assembler/communication_context/integration_boundaries/runtime/TIntegrationBoundaryRuntimeView.hpp"

/**
 * @file TBoundaryHandoffRuntime.hpp
 * @brief Minimal boundary handoff runtime coordinator.
 */
namespace assembler::communication_context {
    struct TBoundaryHandoffRuntime final {
        std::size_t accepted_count{0u};
        std::size_t completed_count{0u};
        std::size_t failed_count{0u};
        bool ready{true};

        [[nodiscard]] constexpr bool can_admit(TIntegrationBoundaryRuntimeContext context) const noexcept {
            return ready && TIntegrationBoundaryAdmissionPolicy::admits(context);
        }

        [[nodiscard]] constexpr TIntegrationBoundaryRuntimeView view() const noexcept {
            return {accepted_count, completed_count, failed_count, ready, "integration_boundary_runtime"};
        }
    };
}
