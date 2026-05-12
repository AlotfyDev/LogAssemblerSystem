#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicySafePointKind.hpp"
#include "TPolicyReplacementEligibility.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyReplacementRule.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicyReplacementRule is a primitive policy-local rule descriptor for how
 *   replacement should be disciplined. It names the policy whose replacement is
 *   being governed, the safe point kind expected, whether manual review is
 *   required, and the minimum structural eligibility required before a plan can
 *   be considered usable.
 *
 * Why this file exists in W03:
 *   Safe replacement semantics require more than safe point identity. A rule
 *   layer is needed so later TPolicy validation can express replacement
 *   discipline without prematurely implementing runtime hot swap, scheduler
 *   integration, graph traversal, or target mutation.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePointKind expresses what kind of safe point the rule expects.
 *   - TPolicyReplacementEligibility expresses the minimum eligible state.
 *   - TPolicyReplacementPlan may reference a rule token to indicate which rule
 *     family governs the plan.
 *   - TPolicyReplacementView can expose rule meaning read-only.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may refine rule activation state.
 *   - W05 observation may audit rule evaluation evidence.
 *   - W07 graph invariants may verify that required safe point kinds exist.
 *   - W09 TPolicy will aggregate replacement rules with other policy semantics.
 *
 * Explicit non-responsibilities:
 *   TPolicyReplacementRule does not execute replacement, does not select a
 *   target component, does not perform traversal, does not enforce concurrency,
 *   and does not decide policy assignment.
 *
 * Current implementation note:
 *   W03 represents rule identity as a numeric token rather than introducing a
 *   full rule id type. That keeps the wave minimal and leaves room for richer
 *   rule catalogs later.
 */
struct TPolicyReplacementRule final
{
    using rule_token_type = std::uint64_t;

    rule_token_type rule_token{0};
    TPolicyId policy_id{};
    TPolicySafePointKind required_safe_point_kind{TPolicySafePointKind::unknown};
    TPolicyReplacementEligibility required_eligibility{TPolicyReplacementEligibility::eligible};
    bool requires_manual_review{false};
    bool allows_pending_replacement{true};

    constexpr TPolicyReplacementRule() noexcept = default;

    constexpr TPolicyReplacementRule(
        rule_token_type token,
        TPolicyId ownerPolicyId,
        TPolicySafePointKind safePointKind,
        TPolicyReplacementEligibility eligibility = TPolicyReplacementEligibility::eligible,
        bool manualReview = false,
        bool pendingAllowed = true) noexcept
        : rule_token(token),
          policy_id(ownerPolicyId),
          required_safe_point_kind(safePointKind),
          required_eligibility(eligibility),
          requires_manual_review(manualReview),
          allows_pending_replacement(pendingAllowed)
    {
    }

    [[nodiscard]] constexpr bool HasRuleToken() const noexcept { return rule_token != 0; }
    [[nodiscard]] constexpr bool HasPolicy() const noexcept { return policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasRequiredSafePointKind() const noexcept { return IsKnown(required_safe_point_kind); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasRuleToken() && HasPolicy() && HasRequiredSafePointKind();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
