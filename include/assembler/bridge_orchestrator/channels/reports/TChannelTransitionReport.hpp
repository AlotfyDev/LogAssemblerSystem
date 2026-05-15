#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"

/**
 * @file TChannelTransitionReport.hpp
 * @brief Evidence report for a channel lifecycle transition.
 */
namespace assembler::communication_context {
    struct TChannelTransitionReport final {
        TChannelStatus before{TChannelStatus::unknown};
        TChannelStatus after{TChannelStatus::unknown};
        bool accepted{false};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return before != TChannelStatus::unknown && after != TChannelStatus::unknown; }
        [[nodiscard]] constexpr bool succeeded() const noexcept { return is_valid() && accepted; }
    };
}
