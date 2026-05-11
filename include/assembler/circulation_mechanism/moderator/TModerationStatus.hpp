#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TModerationStatus : std::uint8_t {
    not_attempted,
    accepted,
    rejected_invalid_moderator,
    rejected_invalid_container,
    rejected_invalid_registry_index,
    rejected_invalid_profile,
    rejected_no_safe_point,
    rejected_container_active,
    rejected_container_not_reset_eligible,
    rejected_invariant
};
} // namespace circulation_mechanism
} // namespace assembler
