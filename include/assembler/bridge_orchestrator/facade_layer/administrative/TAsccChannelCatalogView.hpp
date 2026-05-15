#pragma once
#include <array>
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/channels/profiles/TChannelProfile.hpp"

/**
 * @file TAsccChannelCatalogView.hpp
 * @brief Administrative facade catalog for supported ASCC channel profiles.
 */
namespace assembler::communication_context {
    template <std::size_t Capacity>
    struct TAsccChannelCatalogView final {
        std::array<TChannelProfileKind, Capacity> profile_kinds{};
        std::array<TChannelDirection, Capacity> directions{};
        std::size_t profile_count{0u};
        std::size_t direction_count{0u};
        std::string_view catalog_name{"ascc_channel_catalog"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return profile_count <= Capacity && direction_count <= Capacity && !catalog_name.empty(); }
        constexpr bool add_profile(TChannelProfileKind kind) noexcept { if (profile_count >= Capacity || kind == TChannelProfileKind::unknown) return false; profile_kinds[profile_count++] = kind; return true; }
        constexpr bool add_direction(TChannelDirection direction) noexcept { if (direction_count >= Capacity || direction == TChannelDirection::unknown) return false; directions[direction_count++] = direction; return true; }
    };
}
