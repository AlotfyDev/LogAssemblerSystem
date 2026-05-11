#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TRoundLifecycleStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_invalid_round,
    rejected_invalid_transition,
    rejected_empty_membership,
    rejected_not_locked,
    rejected_not_draining
};
} // namespace circulation_mechanism
} // namespace assembler
