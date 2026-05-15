#pragma once
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationInvocationContext.hpp"

/**
 * @file TObligationInvocationPolicy.hpp
 * @brief Permission policy for ASCC obligation invocation.
 */
namespace assembler::communication_context {
    struct TObligationInvocationPolicy final {
        [[nodiscard]] static constexpr TObligationReport can_invoke(TObligationInvocationContext context) noexcept {
            return context.is_valid()
                ? TObligationReport::satisfied(TObligationSide::binding, context.operation_name, context.correlation)
                : TObligationReport::incomplete(TObligationSide::binding, "obligation_invocation", "invalid invocation context");
        }
    };
}
