#pragma once
#include <cstdint>
namespace assembler {
namespace circulation_mechanism {

enum class TBundleScalingStatus : std::uint8_t {
    not_requested,
    accepted,
    rejected_invalid_agent,
    rejected_invalid_profile,
    rejected_zero_container_count,
    rejected_zero_slot_capacity,
    rejected_same_topology,
    rejected_safe_point_required,
    rejected_exceeds_max_containers,
    rejected_below_active_floor
};
} // namespace circulation_mechanism
} // namespace assembler
