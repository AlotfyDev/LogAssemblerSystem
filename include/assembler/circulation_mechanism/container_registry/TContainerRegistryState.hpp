#pragma once
#include <cstdint>

/*
    TContainerRegistryState.hpp

    Delivery:
        CME-CONTAINER-REGISTRY-PROD-W01 — Production Indexed Storage Contract

    Responsibility:
        Defines registry lifecycle state.
*/

namespace assembler {
namespace circulation_mechanism {

enum class TContainerRegistryState : std::uint8_t {
    uninitialized,
    initialized,
    active,
    rebuild_pending,
    locked_for_profile_switch,
    invariant_violation
};
} // namespace circulation_mechanism
} // namespace assembler
