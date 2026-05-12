#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyReplacementEligibility.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicyReplacementEligibility describes whether a replacement candidate or
 *   replacement boundary is structurally eligible from the policy-type-system
 *   perspective. It is a carrier for replacement readiness meaning, not a live
 *   runtime gate, not a lock, and not a scheduler decision.
 *
 * Why this file exists in W03:
 *   Safe replacement semantics require more than a safe point identity. The
 *   model needs a small vocabulary for unknown, eligible, ineligible, pending,
 *   blocked, and review-required states before replacement rules or plans can
 *   express discipline.
 *
 * Relationship to other files in this wave:
 *   - TPolicyReplacementBoundary may report eligibility at a boundary.
 *   - TPolicyReplacementRule may require eligibility before a plan is usable.
 *   - TPolicyReplacementPlan exposes its current structural eligibility through
 *     this enum.
 *   - TPolicyReplacementView reads this value without mutating replacement
 *     structures.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may refine eligibility using lifecycle state.
 *   - W05 observation may audit eligibility transitions.
 *   - W09 TPolicy validation may combine eligibility with graph invariants.
 *
 * Explicit non-responsibilities:
 *   TPolicyReplacementEligibility does not perform replacement, does not check
 *   threads, does not wait for quiescence, does not traverse a policy graph,
 *   and does not claim that a target component has accepted a new policy.
 *
 * Current implementation note:
 *   W03 keeps this as an enum. Later waves may introduce rich eligibility
 *   reports without changing this enum's role as a compact state vocabulary.
 */
enum class TPolicyReplacementEligibility : std::uint8_t
{
    unknown = 0,
    eligible = 1,
    ineligible = 2,
    pending = 3,
    blocked = 4,
    requires_manual_review = 5
};

[[nodiscard]] constexpr bool IsReplacementAllowed(TPolicyReplacementEligibility value) noexcept
{
    return value == TPolicyReplacementEligibility::eligible;
}

[[nodiscard]] constexpr bool IsReplacementBlocked(TPolicyReplacementEligibility value) noexcept
{
    return value == TPolicyReplacementEligibility::ineligible || value == TPolicyReplacementEligibility::blocked;
}

} // namespace assembler::ecosystem_governance::policy_type_system
