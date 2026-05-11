#pragma once
#include <cstdint>
#include "TCapacityProfileId.hpp"
#include "TScalingDirectionKind.hpp"
#include "TCapacityValidationResult.hpp"

/*
    TVerticalScalingProfile.hpp

    Responsibility:
        Describes and validates a family-wide slots-per-container scaling plan.
*/
namespace assembler {
namespace circulation_mechanism {

struct TVerticalScalingProfile final
{
    TCapacityProfileId profile_id{};
    std::uint32_t current_slots_per_container{0};
    std::uint32_t target_slots_per_container{0};

    [[nodiscard]] constexpr bool changes_capacity() const noexcept { return current_slots_per_container != target_slots_per_container; }
    [[nodiscard]] constexpr bool is_expansion() const noexcept { return target_slots_per_container > current_slots_per_container; }
    [[nodiscard]] constexpr bool is_reduction() const noexcept { return target_slots_per_container < current_slots_per_container; }
    [[nodiscard]] constexpr TScalingDirectionKind direction() const noexcept
    {
        return changes_capacity() ? TScalingDirectionKind::vertical : TScalingDirectionKind::none;
    }
    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (target_slots_per_container == 0U) return rejected_capacity(TCapacityIssueKind::invalid_slot_count);
        return accepted_capacity();
    }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler
