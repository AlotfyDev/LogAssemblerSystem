#pragma once
#include "assembler/communication_context/bridge_core/execution/TBridgeEndpointInvocationProfile.hpp"
#include "assembler/communication_context/protocols/invocation/TProtocolStepInvocationDescriptor.hpp"

/**
 * @file TProtocolStepExecutionPolicy.hpp
 * @brief Policy deciding whether a protocol step remains model-only or may attempt invocation.
 */
namespace assembler::communication_context {
    struct TProtocolStepExecutionPolicy final {
        [[nodiscard]] static constexpr bool can_execute_model_only(TProtocolStepInvocationDescriptor descriptor) noexcept {
            return descriptor.is_valid();
        }
        [[nodiscard]] static constexpr bool can_attempt_invocation(TProtocolStepInvocationDescriptor descriptor, TBridgeEndpointInvocationProfile profile) noexcept {
            return descriptor.can_attempt_invocation() && profile.is_valid() && profile.invocation_allowed;
        }
    };
}
