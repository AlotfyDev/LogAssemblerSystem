#pragma once
#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/execution/TBridgeAdapterPortInvocationPolicy.hpp"
#include "assembler/communication_context/bridge_core/reports/TBridgeExecutionReport.hpp"

namespace assembler::communication_context
{
    struct TBridgeStepExecutor final
    {
        template <std::size_t PlanCapacity>
        [[nodiscard]] static constexpr TBridgeExecutionReport execute_model_step(
            TBridge<PlanCapacity>& bridge,
            TBridgeEndpointInvocationProfile invocation_profile =
                TBridgeEndpointInvocationProfile::model_only_profile()) noexcept
        {
            const auto model_report = bridge.step_model_report();

            const auto invocation = TBridgeAdapterPortInvocationPolicy::preflight(
                invocation_profile,
                bridge.protocol.kind,
                bridge.correlation,
                "bridge_model_step");

            return TBridgeExecutionReport{model_report, invocation};
        }
    };
}
