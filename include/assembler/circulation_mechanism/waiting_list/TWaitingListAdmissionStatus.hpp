#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TWaitingListAdmissionStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_invalid_index,
    rejected_ineligible_state,
    rejected_duplicate,
    rejected_full,
    rejected_locked,
    rejected_invalid_state
};
} // namespace circulation_mechanism
} // namespace assembler
