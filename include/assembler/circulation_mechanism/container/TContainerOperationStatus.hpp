#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TContainerOperationStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_invalid_container,
    rejected_invalid_slot_index,
    rejected_slot_occupied,
    rejected_payload_invalid,
    rejected_invalid_transition,
    rejected_not_dispatch_ready,
    rejected_not_empty,
    rejected_capacity_mismatch
};
} // namespace circulation_mechanism
} // namespace assembler
