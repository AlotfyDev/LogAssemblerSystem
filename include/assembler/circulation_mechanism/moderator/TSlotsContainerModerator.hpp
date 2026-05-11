#pragma once
#include "TModeratorId.hpp"
#include "TSlotsContainerModeratorConfig.hpp"
#include "TModeratorReadinessView.hpp"
#include "TModeratedContainerView.hpp"
#include "TContainerResetPlan.hpp"
#include "TContainerResetReport.hpp"
#include "assembler/circulation_mechanism/ids/TContainerId.hpp"
#include "assembler/circulation_mechanism/ids/TContainerRegistryIndex.hpp"
#include "assembler/circulation_mechanism/state/TModeratorState.hpp"
#include "assembler/circulation_mechanism/state/TContainerState.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"

/*
    TSlotsContainerModerator.hpp

    Delivery:
        CME-MODERATOR-PROD-W01 — Production Reset And Readiness Contract

    Current responsibility:
        Production-grade per-container moderation contract for readiness and reset planning.

    Production capabilities:
        - binds moderator to container id + registry index,
        - exposes read-only readiness view,
        - validates reset preconditions,
        - rejects reset without safe point when required,
        - rejects reset for active containers,
        - produces reset plans and reports,
        - exposes ingress-ready view without waiting-list admission.

    Explicit non-ownership:
        - Does not own BundleAgent topology.
        - Does not own container storage.
        - Does not mutate registry.
        - Does not calculate access refs.
        - Does not add to waiting lists.
*/
namespace assembler {
namespace circulation_mechanism {

class TSlotsContainerModerator final {
public:
    constexpr TSlotsContainerModerator() noexcept = default;

    constexpr TSlotsContainerModerator(
        TModeratorId id,
        TContainerId container_id,
        TContainerRegistryIndex registry_index,
        TSlotsContainerModeratorConfig config) noexcept
        : id_(id), container_id_(container_id), registry_index_(registry_index), config_(config)
    {
        state_ = is_valid() ? TModeratorState::idle : TModeratorState::invariant_violation;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && container_id_.is_valid() && registry_index_.is_valid() && config_.is_valid();
    }

    [[nodiscard]] constexpr TModeratorReadinessView readiness_view(TContainerState container_state, TSafePointState safe_point_state) const noexcept {
        return TModeratorReadinessView{id_, container_id_, registry_index_, state_, container_state, safe_point_state};
    }

    [[nodiscard]] constexpr TModeratedContainerView moderated_container_view(TContainerState container_state, TSafePointState safe_point_state) const noexcept {
        return TModeratedContainerView{readiness_view(container_state, safe_point_state)};
    }

    [[nodiscard]] constexpr TContainerResetPlan plan_reset(TContainerState container_state, TSafePointState safe_point_state) const noexcept {
        if (!id_.is_valid()) return {TModerationStatus::rejected_invalid_moderator, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (!container_id_.is_valid()) return {TModerationStatus::rejected_invalid_container, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (!registry_index_.is_valid()) return {TModerationStatus::rejected_invalid_registry_index, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (!config_.is_valid()) return {TModerationStatus::rejected_invalid_profile, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (unsafe_active_container(container_state)) return {TModerationStatus::rejected_container_active, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (!reset_eligible(container_state)) return {TModerationStatus::rejected_container_not_reset_eligible, container_id_, registry_index_, container_state, container_state, safe_point_state};
        if (config_.reset_requires_safe_point && !can_claim(safe_point_state)) return {TModerationStatus::rejected_no_safe_point, container_id_, registry_index_, container_state, container_state, safe_point_state};
        return {TModerationStatus::accepted, container_id_, registry_index_, container_state, TContainerState::default_empty, safe_point_state};
    }

    [[nodiscard]] constexpr TContainerResetReport reset_report(TContainerState container_state, TSafePointState safe_point_state, bool applied) const noexcept {
        return TContainerResetReport{id_, plan_reset(container_state, safe_point_state), applied};
    }

private:
    TModeratorId id_{TModeratorId::invalid()};
    TContainerId container_id_{TContainerId::invalid()};
    TContainerRegistryIndex registry_index_{TContainerRegistryIndex::invalid()};
    TSlotsContainerModeratorConfig config_{};
    TModeratorState state_{TModeratorState::uninitialized};
};
} // namespace circulation_mechanism
} // namespace assembler
