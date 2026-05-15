#pragma once
#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"

namespace assembler::communication_context
{
    struct TBridgeCoreReadinessPolicy final
    {
        template <std::size_t PlanCapacity>
        [[nodiscard]] static constexpr TBridgeCoreIssue check_ready(const TBridge<PlanCapacity>& bridge) noexcept
        {
            if (!bridge.is_valid())
            {
                return TBridgeCoreIssue::fatal(bridge.status, "bridge.readiness.invalid", "bridge is invalid", bridge.correlation);
            }

            if (!bridge.config.is_valid())
            {
                return TBridgeCoreIssue::fatal(bridge.status, "bridge.readiness.config_invalid", "bridge config is invalid", bridge.correlation);
            }

            if (!bridge.protocol.is_valid())
            {
                return TBridgeCoreIssue::fatal(bridge.status, "bridge.readiness.protocol_invalid", "bridge protocol is invalid", bridge.correlation);
            }

            if (!bridge.is_ready() && !bridge.is_running())
            {
                return TBridgeCoreIssue::block(bridge.status, "bridge.readiness.not_runnable", "bridge is not ready or running", bridge.correlation);
            }

            return TBridgeCoreIssue::none();
        }
    };
}
