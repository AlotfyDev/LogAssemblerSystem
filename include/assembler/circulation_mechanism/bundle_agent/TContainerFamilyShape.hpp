#pragma once
#include <cstdint>
#include "assembler/circulation_mechanism/capacity/TCapacityProfileId.hpp"

/*
    TContainerFamilyShape.hpp

    Responsibility:
        Describes the uniform shape shared by all active containers in one family.

    Production capabilities:
        - active container count
        - slots per container
        - slot payload capacity units
        - capacity profile id
        - validation and total capacity helpers

    Non-ownership:
        Does not allocate containers and does not mutate registry storage.
*/
namespace assembler {
namespace circulation_mechanism {

struct TContainerFamilyShape final {
    TCapacityProfileId capacity_profile_id{};
    std::uint32_t active_container_count{0};
    std::uint32_t slots_per_container{0};
    std::uint32_t slot_payload_capacity_units{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return capacity_profile_id.is_valid()
            && active_container_count > 0U
            && slots_per_container > 0U
            && slot_payload_capacity_units > 0U;
    }

    [[nodiscard]] constexpr std::uint64_t total_slots() const noexcept {
        return static_cast<std::uint64_t>(active_container_count) * static_cast<std::uint64_t>(slots_per_container);
    }

    [[nodiscard]] constexpr std::uint64_t total_payload_units() const noexcept {
        return total_slots() * static_cast<std::uint64_t>(slot_payload_capacity_units);
    }

    [[nodiscard]] constexpr bool same_layout_as(TContainerFamilyShape other) const noexcept {
        return slots_per_container == other.slots_per_container
            && slot_payload_capacity_units == other.slot_payload_capacity_units;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
