#pragma once
#include <cstdint>
#include <limits>
#include "TCapacityProfileId.hpp"
#include "TCapacityGenerationId.hpp"
#include "TCapacityProfileStatus.hpp"
#include "TCapacityIssueKind.hpp"
#include "TCapacityValidationResult.hpp"

/*
    TUniformContainerCapacityProfile.hpp

    Current responsibility:
        Defines a production-grade uniform container capacity and slot layout profile.

    Production capabilities:
        - profile and generation identity.
        - slots-per-container contract.
        - payload capacity units per slot.
        - total-units calculation.
        - compatibility comparison.
        - validation with issue classification.
        - overflow-risk guard.

    Architectural role:
        Every active container in a container family must match this profile.

    Explicit non-ownership:
        - Does not allocate slots.
        - Does not resize containers.
        - Does not execute profile switch.
*/

namespace assembler {
namespace circulation_mechanism {

struct TUniformContainerCapacityProfile final
{
    TCapacityProfileId profile_id{};
    TCapacityGenerationId generation_id{};
    TCapacityProfileStatus status{TCapacityProfileStatus::undefined};
    std::uint32_t slots_per_container{0};
    std::uint32_t slot_payload_capacity_units{0};

    [[nodiscard]] constexpr bool ids_valid() const noexcept
    {
        return profile_id.is_valid() && generation_id.is_valid();
    }

    [[nodiscard]] constexpr bool dimensions_valid() const noexcept
    {
        return slots_per_container > 0U && slot_payload_capacity_units > 0U;
    }

    [[nodiscard]] constexpr bool status_valid() const noexcept
    {
        return status != TCapacityProfileStatus::undefined && status != TCapacityProfileStatus::invalid;
    }

    [[nodiscard]] constexpr bool multiplication_safe() const noexcept
    {
        return slot_payload_capacity_units == 0U
            || slots_per_container <= (std::numeric_limits<std::uint64_t>::max() / slot_payload_capacity_units);
    }

    [[nodiscard]] constexpr std::uint64_t total_units_per_container() const noexcept
    {
        return static_cast<std::uint64_t>(slots_per_container) * static_cast<std::uint64_t>(slot_payload_capacity_units);
    }

    [[nodiscard]] constexpr bool compatible_with(TUniformContainerCapacityProfile other) const noexcept
    {
        return slots_per_container == other.slots_per_container
            && slot_payload_capacity_units == other.slot_payload_capacity_units;
    }

    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (!generation_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_generation_id);
        if (!status_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (slots_per_container == 0U) return rejected_capacity(TCapacityIssueKind::invalid_slot_count);
        if (slot_payload_capacity_units == 0U) return rejected_capacity(TCapacityIssueKind::invalid_payload_capacity);
        if (!multiplication_safe()) return rejected_capacity(TCapacityIssueKind::overflow_risk);
        return accepted_capacity();
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler
