#pragma once
#include <cstdint>
#include "TContainerRegistryState.hpp"
#include "TContainerStorageKind.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryView final {
    TContainerRegistryState state{TContainerRegistryState::uninitialized};
    TContainerStorageKind storage_kind{TContainerStorageKind::fixed_array};
    std::uint32_t capacity{0};
    std::uint32_t active_count{0};
    std::uint64_t generation{0};

    [[nodiscard]] constexpr bool is_initialized() const noexcept {
        return state != TContainerRegistryState::uninitialized;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return is_initialized() && capacity > 0U && active_count <= capacity && generation > 0U;
    }

    [[nodiscard]] constexpr bool contains(TContainerRegistryIndex index) const noexcept {
        return index.is_valid() && index.one_based() <= capacity;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
