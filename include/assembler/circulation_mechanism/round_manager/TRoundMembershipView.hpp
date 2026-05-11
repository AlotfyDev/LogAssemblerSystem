#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
namespace assembler {
namespace circulation_mechanism {

template <std::size_t Capacity>
struct TRoundMembershipView final {
    std::array<TContainerRegistryIndex, Capacity> members{};
    std::uint32_t count{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return count <= Capacity; }
    [[nodiscard]] constexpr const TContainerRegistryIndex* try_get(std::uint32_t idx) const noexcept {
        return idx < count ? &members[idx] : nullptr;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
