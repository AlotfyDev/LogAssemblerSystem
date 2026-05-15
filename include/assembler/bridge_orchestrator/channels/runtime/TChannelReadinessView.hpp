#pragma once
#include <string_view>
#include "assembler/communication_context/channels/topology/TChannel.hpp"

/**
 * @file TChannelReadinessView.hpp
 * @brief Runtime readiness projection for an ASCC channel.
 */
namespace assembler::communication_context {
    struct TChannelReadinessView final {
        TChannel channel{};
        bool source_ready{false};
        bool target_ready{false};
        bool binding_ready{false};
        bool roles_compatible{false};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return channel.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && source_ready && target_ready && binding_ready && roles_compatible; }
    };
}
