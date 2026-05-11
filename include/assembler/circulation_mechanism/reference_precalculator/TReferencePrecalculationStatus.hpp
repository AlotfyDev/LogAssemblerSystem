#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TReferencePrecalculationStatus : std::uint8_t {
    uninitialized, ready, replenishing, ingress_refs_ready, dispatch_refs_ready,
    waiting_for_candidates, invalidating_refs, supply_interrupted, invariant_violation
};
} // namespace circulation_mechanism
} // namespace assembler
