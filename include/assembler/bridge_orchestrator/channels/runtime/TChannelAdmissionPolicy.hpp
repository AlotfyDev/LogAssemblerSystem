#pragma once
#include "assembler/communication_context/channels/runtime/TChannelReadinessView.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"

/**
 * @file TChannelAdmissionPolicy.hpp
 * @brief Managerial runtime policy for admitting a channel into ASCC operation.
 */
namespace assembler::communication_context {
    struct TChannelAdmissionPolicy final {
        [[nodiscard]] static constexpr TChannelReadinessView admit(TChannel channel, bool source_ready, bool target_ready, bool binding_ready) noexcept {
            return TChannelReadinessView{channel, source_ready, target_ready, binding_ready, channel.has_compatible_roles(), "channel admission"};
        }
    };
}
