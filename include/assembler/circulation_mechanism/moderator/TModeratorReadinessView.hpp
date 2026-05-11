#pragma once
#include "TModeratorId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TModeratorState.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"

/*
    TModeratorReadinessView.hpp

    Responsibility:
        Read-only projection of per-container moderation readiness.

    Non-ownership:
        Does not add container to waiting list and does not mutate container.
*/
namespace assembler {
namespace circulation_mechanism {

struct TModeratorReadinessView final {
    TModeratorId moderator_id{};
    TContainerId container_id{};
    TContainerRegistryIndex registry_index{};
    TModeratorState moderator_state{TModeratorState::uninitialized};
    TContainerState container_state{TContainerState::default_empty};
    TSafePointState safe_point_state{TSafePointState::unavailable};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return moderator_id.is_valid() && container_id.is_valid() && registry_index.is_valid();
    }
    [[nodiscard]] constexpr bool safe_point_available() const noexcept {
        return can_claim(safe_point_state);
    }
    [[nodiscard]] constexpr bool can_expose_ingress_ready() const noexcept {
        return is_valid() && can_expose_readiness(moderator_state) && ingress_ready_candidate(container_state);
    }
    [[nodiscard]] constexpr bool can_plan_reset() const noexcept {
        return is_valid() && ::assembler::circulation_mechanism::can_plan_reset(moderator_state) && reset_eligible(container_state);
    }
};
} // namespace circulation_mechanism
} // namespace assembler
