#pragma once
#include <cstdint>

/*
    TSlotAccessStatus.hpp

    Delivery:
        CME-SLOT-PROD-W01 — Production Residency And Access Contract

    Responsibility:
        Classifies results of slot residency/access operations.
*/

namespace assembler {
namespace circulation_mechanism {


enum class TSlotAccessStatus : std::uint8_t
{
    not_attempted,
    accepted,
    rejected_invalid_slot,
    rejected_not_writable,
    rejected_empty_payload,
    rejected_no_payload_resident,
    rejected_not_dispatch_ready,
    rejected_not_exposed,
    rejected_invalid_transition,
    rejected_faulted
};

} // namespace circulation_mechanism
} // namespace assembler
