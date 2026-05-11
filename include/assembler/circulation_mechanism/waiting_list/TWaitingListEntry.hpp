#pragma once
#include <cstdint>
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"

/*
    TWaitingListEntry.hpp

    Delivery:
        CME-WAITING-LIST-PROD-W01 — Production Eligibility And Ordering Contract

    Responsibility:
        Carries an eligible container registry index and admission metadata.

    Production capabilities:
        - index-only candidate, no payload storage.
        - observed container state.
        - FIFO sequence.
        - optional generation metadata.
        - validity helper.

    Non-ownership:
        Does not own container, slot, envelope, reference, bridge, or receiver lifecycle.
*/
namespace assembler {
namespace circulation_mechanism {

struct TWaitingListEntry final {
    TContainerRegistryIndex container_index{};
    TContainerState observed_container_state{TContainerState::default_empty};
    std::uint64_t fifo_sequence{0};
    std::uint64_t registry_generation{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return container_index.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
