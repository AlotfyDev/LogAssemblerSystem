#pragma once
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/ids/TRoundId.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TAccessRefScope final {
    TContainerRegistryIndex container_index{};
    TSlotIndex slot_index{};
    TRoundId round_id{};
    std::uint64_t registry_generation{0};
    std::uint64_t profile_generation{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return container_index.is_valid() && slot_index.is_valid() && round_id.is_valid()
            && registry_generation > 0U && profile_generation > 0U;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
