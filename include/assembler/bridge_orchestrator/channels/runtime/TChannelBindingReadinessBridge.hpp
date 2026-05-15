#pragma once
#include "assembler/communication_context/channels/topology/TChannel.hpp"

/**
 * @file TChannelBindingReadinessBridge.hpp
 * @brief Bridges channel policy/profile compatibility with binding readiness evidence.
 */
namespace assembler::communication_context {
    struct TChannelBindingReadinessBridge final {
        [[nodiscard]] static constexpr bool binding_satisfies_channel(TChannel channel, bool binding_ready) noexcept {
            return channel.is_valid() && channel.binding_policy.is_compatible_with(channel.profile) && binding_ready;
        }
    };
}
