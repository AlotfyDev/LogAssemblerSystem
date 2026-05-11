#pragma once
#include <cstdint>
#include "TCapacityProfileId.hpp"
#include "TScalingDirectionKind.hpp"
#include "TCapacityValidationResult.hpp"

/*
    THorizontalScalingProfile.hpp

    Responsibility:
        Describes and validates a container-count scaling plan.
*/
namespace assembler {
namespace circulation_mechanism {

struct THorizontalScalingProfile final
{
    TCapacityProfileId profile_id{};
    std::uint32_t current_container_count{0};
    std::uint32_t target_container_count{0};

    [[nodiscard]] constexpr bool is_expansion() const noexcept { return target_container_count > current_container_count; }
    [[nodiscard]] constexpr bool is_reduction() const noexcept { return target_container_count < current_container_count; }
    [[nodiscard]] constexpr TScalingDirectionKind direction() const noexcept
    {
        return current_container_count == target_container_count ? TScalingDirectionKind::none : TScalingDirectionKind::horizontal;
    }
    [[nodiscard]] constexpr TCapacityValidationResult validate() const noexcept
    {
        if (!profile_id.is_valid()) return rejected_capacity(TCapacityIssueKind::invalid_profile_id);
        if (target_container_count == 0U) return rejected_capacity(TCapacityIssueKind::invalid_container_count);
        return accepted_capacity();
    }
    [[nodiscard]] constexpr bool is_valid() const noexcept { return validate().accepted; }
};
} // namespace circulation_mechanism
} // namespace assembler
