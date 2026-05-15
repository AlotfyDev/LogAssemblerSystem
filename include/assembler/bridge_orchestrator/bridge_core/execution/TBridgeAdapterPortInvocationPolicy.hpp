#pragma once
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocation.hpp"
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocationProfile.hpp"

namespace assembler::communication_context
{
    struct TBridgeAdapterPortInvocationPolicy final
    {
        [[nodiscard]] static constexpr bool allows_invocation(TBridgeEndpointInvocationProfile profile) noexcept
        {
            return profile.is_valid() && profile.invocation_allowed;
        }

        [[nodiscard]] static constexpr TBridgeEndpointInvocation preflight(
            TBridgeEndpointInvocationProfile profile,
            TBridgeProtocolKind protocol,
            TCorrelationToken correlation = TCorrelationToken::invalid(),
            std::string_view operation = "adapter_port_invocation") noexcept
        {
            if (!allows_invocation(profile))
            {
                return {protocol, TBridgeEndpointInvocationStatus::blocked, TBridgeResult::success(correlation), correlation, operation, "endpoint invocation is disabled by profile"};
            }

            return {protocol, TBridgeEndpointInvocationStatus::allowed, TBridgeResult::success(correlation), correlation, operation, "endpoint invocation is allowed by profile"};
        }
    };
}
