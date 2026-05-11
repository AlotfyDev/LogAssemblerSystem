#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TIngressPlacementStatus : std::uint8_t {
    not_attempted, accepted, rejected_invalid_ingress, rejected_closed, rejected_invalid_ref,
    rejected_wrong_ref_direction, rejected_boundary_mismatch, rejected_payload_not_ready,
    rejected_slot_not_writable, rejected_target_missing, rejected_target_failed, blocked_by_invariant
};
} // namespace circulation_mechanism
} // namespace assembler
