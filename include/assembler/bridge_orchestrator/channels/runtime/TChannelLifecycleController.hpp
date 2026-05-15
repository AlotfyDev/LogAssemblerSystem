#pragma once
#include "assembler/communication_context/channels/reports/TChannelTransitionReport.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"

/**
 * @file TChannelLifecycleController.hpp
 * @brief Runtime helper for controlled ASCC channel lifecycle transitions.
 */
namespace assembler::communication_context {
    struct TChannelLifecycleController final {
        [[nodiscard]] static constexpr TChannelTransitionReport activate(const TChannel& channel) noexcept {
            const bool ok = channel.is_valid() && channel.status == TChannelStatus::declared;
            return {channel.status, TChannelStatus::active, ok, channel.correlation, ok ? "channel activated" : "channel activation rejected"};
        }
        [[nodiscard]] static constexpr TChannelTransitionReport suspend(const TChannel& channel) noexcept {
            const bool ok = channel.is_valid() && channel.status == TChannelStatus::active;
            return {channel.status, TChannelStatus::suspended, ok, channel.correlation, ok ? "channel suspended" : "channel suspension rejected"};
        }
        [[nodiscard]] static constexpr TChannelTransitionReport retire(const TChannel& channel) noexcept {
            const bool ok = channel.is_valid() && channel.status != TChannelStatus::retired;
            return {channel.status, TChannelStatus::retired, ok, channel.correlation, ok ? "channel retired" : "channel retirement rejected"};
        }
    };
}
