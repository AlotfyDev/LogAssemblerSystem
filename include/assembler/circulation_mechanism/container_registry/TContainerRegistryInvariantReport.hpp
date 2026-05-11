#pragma once
#include <cstdint>
#include "TContainerRegistryState.hpp"

namespace assembler {
namespace circulation_mechanism {

struct TContainerRegistryInvariantReport final {
    bool initialized{false};
    bool active_count_within_capacity{false};
    bool occupied_count_matches_active_count{false};
    bool generation_valid{false};
    TContainerRegistryState state{TContainerRegistryState::uninitialized};

    [[nodiscard]] constexpr bool passed() const noexcept {
        return initialized && active_count_within_capacity && occupied_count_matches_active_count && generation_valid;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
