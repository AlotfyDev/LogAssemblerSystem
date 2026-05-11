#pragma once
#include "TBundleAgentId.hpp"
#include "TSlotsContainerBundleAgentConfig.hpp"
#include "TBundleTopologyView.hpp"
#include "TBundleScalingPlan.hpp"
#include "TBundleScalingReport.hpp"
#include "TDefaultEmptyContainerProfileReport.hpp"
#include "assembler/circulation_mechanism/state/TBundleAgentState.hpp"
#include "assembler/circulation_mechanism/state/TSafePointState.hpp"

/*
    TSlotsContainerBundleAgent.hpp

    Delivery:
        CME-BUNDLE-AGENT-PROD-W01 — Production Topology And Scaling Contract

    Current responsibility:
        Production-grade owner of container-family topology and uniform shape.

    Production capabilities:
        - validates initial topology
        - exposes topology view
        - provides default empty container shape
        - plans horizontal scaling
        - plans vertical scaling
        - enforces max container count
        - enforces safe point requirements for profile-changing operations
        - applies accepted scaling plan to its own topology state
        - increments topology generation on accepted changes
        - emits scaling reports

    Explicit non-ownership:
        - Does not allocate registry storage.
        - Does not reset concrete containers.
        - Does not add containers to waiting lists.
        - Does not calculate references.
        - Does not execute bridge/read-side behavior.
*/
namespace assembler {
namespace circulation_mechanism {

class TSlotsContainerBundleAgent final {
public:
    constexpr TSlotsContainerBundleAgent() noexcept = default;

    constexpr TSlotsContainerBundleAgent(TBundleAgentId id, TSlotsContainerBundleAgentConfig config) noexcept
        : id_(id), config_(config), shape_(config.initial_shape)
    {
        if (id_.is_valid() && config_.is_valid()) {
            state_ = TBundleAgentState::stable;
            generation_ = 1U;
        } else {
            state_ = TBundleAgentState::invariant_violation;
        }
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return id_.is_valid() && config_.is_valid() && shape_.is_valid() && generation_ > 0U;
    }

    [[nodiscard]] constexpr TBundleTopologyView topology_view() const noexcept {
        return TBundleTopologyView{id_, config_.family_id, state_, shape_, config_.max_container_count, generation_};
    }

    [[nodiscard]] constexpr TDefaultEmptyContainerProfileReport default_empty_profile_report() const noexcept {
        return TDefaultEmptyContainerProfileReport{id_, config_.family_id, shape_, is_valid()};
    }

    [[nodiscard]] constexpr TBundleScalingPlan plan_horizontal_scaling(std::uint32_t target_container_count, TSafePointState safe_point_state) const noexcept {
        if (!is_valid()) return {TScalingDirectionKind::horizontal, shape_, TBundleScalingStatus::rejected_invalid_agent, false};
        if (target_container_count == 0U) return {TScalingDirectionKind::horizontal, shape_, TBundleScalingStatus::rejected_zero_container_count, false};
        if (target_container_count > config_.max_container_count) return {TScalingDirectionKind::horizontal, shape_, TBundleScalingStatus::rejected_exceeds_max_containers, false};
        if (target_container_count == shape_.active_container_count) return {TScalingDirectionKind::none, shape_, TBundleScalingStatus::rejected_same_topology, false};
        const bool safe_required = config_.horizontal_scaling_requires_safe_point;
        if (safe_required && safe_point_state != TSafePointState::available) {
            return {TScalingDirectionKind::horizontal, shape_, TBundleScalingStatus::rejected_safe_point_required, true};
        }
        auto target = shape_;
        target.active_container_count = target_container_count;
        return {TScalingDirectionKind::horizontal, target, TBundleScalingStatus::accepted, safe_required};
    }

    [[nodiscard]] constexpr TBundleScalingPlan plan_vertical_scaling(std::uint32_t target_slots_per_container, TSafePointState safe_point_state) const noexcept {
        if (!is_valid()) return {TScalingDirectionKind::vertical, shape_, TBundleScalingStatus::rejected_invalid_agent, false};
        if (target_slots_per_container == 0U) return {TScalingDirectionKind::vertical, shape_, TBundleScalingStatus::rejected_zero_slot_capacity, false};
        if (target_slots_per_container == shape_.slots_per_container) return {TScalingDirectionKind::none, shape_, TBundleScalingStatus::rejected_same_topology, false};
        const bool safe_required = config_.vertical_scaling_requires_safe_point;
        if (safe_required && safe_point_state != TSafePointState::available) {
            return {TScalingDirectionKind::vertical, shape_, TBundleScalingStatus::rejected_safe_point_required, true};
        }
        auto target = shape_;
        target.slots_per_container = target_slots_per_container;
        return {TScalingDirectionKind::vertical, target, TBundleScalingStatus::accepted, safe_required};
    }

    constexpr TBundleScalingReport apply_scaling_plan(TBundleScalingPlan plan) noexcept {
        const auto before = generation_;
        if (!plan.accepted()) {
            return TBundleScalingReport{id_, config_.family_id, plan, before, generation_};
        }
        if (!plan.target_shape.is_valid()) {
            plan.status = TBundleScalingStatus::rejected_invalid_profile;
            return TBundleScalingReport{id_, config_.family_id, plan, before, generation_};
        }
        shape_ = plan.target_shape;
        state_ = TBundleAgentState::profile_switch_applied;
        ++generation_;
        return TBundleScalingReport{id_, config_.family_id, plan, before, generation_};
    }

private:
    TBundleAgentId id_{TBundleAgentId::invalid()};
    TSlotsContainerBundleAgentConfig config_{};
    TContainerFamilyShape shape_{};
    TBundleAgentState state_{TBundleAgentState::uninitialized};
    std::uint64_t generation_{0};
};
} // namespace circulation_mechanism
} // namespace assembler
