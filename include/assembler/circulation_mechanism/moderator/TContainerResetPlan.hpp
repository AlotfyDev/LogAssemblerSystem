#pragma once
#include "TModerationStatus.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"

/*
    TContainerResetPlan.hpp

    Responsibility:
        Describes a moderator-approved or rejected reset plan.

    Production capabilities:
        - validates container state,
        - validates safe point availability,
        - records before/after state,
        - never executes actual container mutation by itself.
*/
namespace assembler {
namespace circulation_mechanism {

struct TContainerResetPlan final {
    TModerationStatus status{TModerationStatus::not_attempted};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TContainerState before{TContainerState::default_empty};
    TContainerState after{TContainerState::default_empty};
    TSafePointState safe_point_state{TSafePointState::unavailable};

    [[nodiscard]] constexpr bool accepted() const noexcept { return status == TModerationStatus::accepted; }
    [[nodiscard]] constexpr bool rejected() const noexcept { return !accepted(); }
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return container_id.is_valid() && registry_index.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
