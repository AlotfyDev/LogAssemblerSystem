#pragma once
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocation.hpp"
#include "assembler/communication_context/bridge_core/reports/TBridgeCoreStepReport.hpp"

namespace assembler::communication_context
{
    struct TBridgeExecutionReport final
    {
        TBridgeCoreStepReport model_step{};
        TBridgeEndpointInvocation endpoint_invocation{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return model_step.is_valid();
        }

        [[nodiscard]] constexpr bool model_succeeded() const noexcept
        {
            return model_step.succeeded();
        }

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return model_step.completed();
        }
    };
}
