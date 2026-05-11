#pragma once
#include <cstdint>

/*
    TContainerRegistryOperationStatus.hpp

    Delivery:
        CME-CONTAINER-REGISTRY-PROD-W01 — Production Indexed Storage Contract

    Responsibility:
        Classifies registry operation results.
*/

namespace assembler {
namespace circulation_mechanism {

enum class TContainerRegistryOperationStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_uninitialized,
    rejected_invalid_index,
    rejected_slot_occupied,
    rejected_slot_empty,
    rejected_registry_full,
    rejected_rebuild_locked,
    rejected_invariant_violation
};
} // namespace circulation_mechanism
} // namespace assembler
