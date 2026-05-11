#pragma once
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TReferenceCandidate final {
    TContainerRegistryIndex container_index{};
    TContainerState observed_container_state{TContainerState::default_empty};
    std::uint64_t registry_generation{0};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return container_index.is_valid() && registry_generation > 0U; }
};
} // namespace circulation_mechanism
} // namespace assembler
