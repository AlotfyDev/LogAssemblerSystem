#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TRoundAdmissionDecisionKind : std::uint8_t {
    accepted,
    rejected_invalid_round,
    rejected_invalid_index,
    rejected_state_not_eligible,
    rejected_round_closed,
    rejected_duplicate,
    rejected_membership_full,
    rejected_wrong_round_kind
};
} // namespace circulation_mechanism
} // namespace assembler
