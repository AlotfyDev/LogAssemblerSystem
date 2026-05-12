#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicySafePointId.hpp"
#include "TPolicyReplacementEligibility.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyReplacementPlan.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicyReplacementPlan is a structural plan descriptor for replacing one
 *   policy with another under governed safe replacement semantics. It connects
 *   current policy identity, candidate replacement policy identity, selected
 *   safe point identity, optional rule token, and eligibility status.
 *
 * Why this file exists in W03:
 *   The policy model requires pending replacement awareness and safe replacement
 *   discipline. A plan object allows later lifecycle, observation, graph, and
 *   TPolicy aggregate layers to speak about intended replacement without
 *   executing the replacement.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePointId identifies the selected replacement anchor.
 *   - TPolicyReplacementEligibility records whether the plan is structurally
 *     eligible, pending, blocked, or review-required.
 *   - TPolicyReplacementRule may be referenced by rule_token.
 *   - TPolicyReplacementView exposes a read-only projection of this plan.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may attach pending replacement state to a plan.
 *   - W05 observation may audit creation, review, acceptance, or cancellation.
 *   - W07 graph invariants may check whether the chosen safe point exists.
 *   - W09 TPolicy may expose replacement plans as part of policy state.
 *
 * Explicit non-responsibilities:
 *   TPolicyReplacementPlan does not perform replacement, does not mutate a
 *   registry, does not assign a policy, does not call a target object, and does
 *   not guarantee runtime safety by itself.
 *
 * Current implementation note:
 *   W03 keeps plan content compact. Later waves may add timestamps, lifecycle
 *   markers, reviewer identity, graph references, and observation evidence.
 */
struct TPolicyReplacementPlan final
{
    using plan_token_type = std::uint64_t;
    using rule_token_type = std::uint64_t;

    plan_token_type plan_token{0};
    TPolicyId current_policy_id{};
    TPolicyId replacement_policy_id{};
    TPolicySafePointId selected_safe_point_id{};
    rule_token_type rule_token{0};
    TPolicyReplacementEligibility eligibility{TPolicyReplacementEligibility::unknown};

    constexpr TPolicyReplacementPlan() noexcept = default;

    constexpr TPolicyReplacementPlan(
        plan_token_type token,
        TPolicyId currentPolicyId,
        TPolicyId replacementPolicyId,
        TPolicySafePointId safePointId,
        TPolicyReplacementEligibility replacementEligibility = TPolicyReplacementEligibility::unknown,
        rule_token_type governingRuleToken = 0) noexcept
        : plan_token(token),
          current_policy_id(currentPolicyId),
          replacement_policy_id(replacementPolicyId),
          selected_safe_point_id(safePointId),
          rule_token(governingRuleToken),
          eligibility(replacementEligibility)
    {
    }

    [[nodiscard]] constexpr bool HasPlanToken() const noexcept { return plan_token != 0; }
    [[nodiscard]] constexpr bool HasCurrentPolicy() const noexcept { return current_policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasReplacementPolicy() const noexcept { return replacement_policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasSelectedSafePoint() const noexcept { return selected_safe_point_id.IsValid(); }
    [[nodiscard]] constexpr bool HasRuleToken() const noexcept { return rule_token != 0; }
    [[nodiscard]] constexpr bool IsEligible() const noexcept { return IsReplacementAllowed(eligibility); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasPlanToken() && HasCurrentPolicy() && HasReplacementPolicy() && HasSelectedSafePoint();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
