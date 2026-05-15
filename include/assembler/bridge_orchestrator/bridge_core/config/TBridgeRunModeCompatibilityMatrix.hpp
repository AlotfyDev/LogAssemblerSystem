#pragma once
#include "assembler/communication_context/bridge_core/config/TBridgeRunMode.hpp"
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocationProfile.hpp"

namespace assembler::communication_context
{
    struct TBridgeRunModeCompatibilityMatrix final
    {
        [[nodiscard]] static constexpr bool supports_model_step(TBridgeRunMode mode) noexcept
        {
            return mode == TBridgeRunMode::manual_step
                || mode == TBridgeRunMode::bounded_model_run
                || mode == TBridgeRunMode::single_pass_model_run
                || mode == TBridgeRunMode::diagnostic_dry_run;
        }

        [[nodiscard]] static constexpr bool supports_invocation(
            TBridgeRunMode mode,
            TBridgeEndpointInvocationProfile profile) noexcept
        {
            return supports_model_step(mode) && profile.invocation_allowed;
        }
    };
}
