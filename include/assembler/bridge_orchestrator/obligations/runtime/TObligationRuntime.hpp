#pragma once
#include "assembler/communication_context/obligations/runtime/TObligationInvocationPolicy.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationInvocationReport.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationRuntimeView.hpp"

/**
 * @file TObligationRuntime.hpp
 * @brief Minimal obligation runtime coordinator for ASCC obligation invocation evidence.
 */
namespace assembler::communication_context {
    struct TObligationRuntime final {
        std::size_t invocation_count{0u};
        std::size_t failed_invocations{0u};
        bool ready{true};

        [[nodiscard]] constexpr TObligationRuntimeView view() const noexcept {
            return TObligationRuntimeView{invocation_count, failed_invocations, ready, "obligation_runtime"};
        }

        [[nodiscard]] constexpr TObligationReport preflight(TObligationInvocationContext context) const noexcept {
            return TObligationInvocationPolicy::can_invoke(context);
        }
    };
}
