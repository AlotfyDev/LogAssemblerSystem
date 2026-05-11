#pragma once
#include <cstdint>
#include "TContainerFamilyShape.hpp"
#include "TBundleScalingStatus.hpp"
#include "assembler/circulation_mechanism/capacity/TScalingDirectionKind.hpp"

/*
    TBundleScalingPlan.hpp

    Responsibility:
        Describes a proposed topology/capacity shape change.

    Production capabilities:
        - horizontal scaling plan
        - vertical scaling plan
        - target family shape
        - accepted/rejected status
        - safe-point requirement flag

    Non-ownership:
        Does not apply the plan by itself.
*/
namespace assembler {
namespace circulation_mechanism {

struct TBundleScalingPlan final {
    TScalingDirectionKind direction{TScalingDirectionKind::none};
    TContainerFamilyShape target_shape{};
    TBundleScalingStatus status{TBundleScalingStatus::not_requested};
    bool safe_point_required{false};

    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TBundleScalingStatus::accepted; }
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted(); }
};
} // namespace circulation_mechanism
} // namespace assembler
