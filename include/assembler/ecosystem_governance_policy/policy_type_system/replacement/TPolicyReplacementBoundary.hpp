#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicySafePointId.hpp"
#include "TPolicySafePointKind.hpp"
#include "TPolicyReplacementEligibility.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyReplacementBoundary.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicyReplacementBoundary represents a policy-level boundary at which
 *   replacement may be considered structurally safe, structurally blocked, or
 *   pending further governance. It binds a policy identity to a safe point and
 *   records the safe point kind and replacement eligibility state.
 *
 * Why this file exists in W03:
 *   The policy taxonomy requires safe replacement semantics as a foundational
 *   element. A boundary object is needed before the system can express
 *   replacement rules, replacement plans, graph safe-point nodes, lifecycle-safe
 *   transitions, or policy aggregate validation.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePointId names the structural safe point.
 *   - TPolicySafePointKind classifies the boundary anchor.
 *   - TPolicyReplacementEligibility records whether replacement is currently
 *     structurally eligible at this boundary.
 *   - TPolicyReplacementRule and TPolicyReplacementPlan use this boundary as a
 *     building block.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may determine when lifecycle state aligns with a boundary.
 *   - W05 observation may record boundary checks.
 *   - W07 graph structure may expose boundaries as safe point nodes or edges.
 *   - W09 TPolicy may include a boundary set as part of replacement semantics.
 *
 * Explicit non-responsibilities:
 *   This file does not implement live replacement, hot swapping, target object
 *   mutation, locking, graph traversal, or policy assignment. It is structural
 *   metadata only.
 *
 * Current implementation note:
 *   W03 intentionally keeps the boundary compact. Later waves may attach
 *   lifecycle state constraints, observation references, or graph-node links.
 */
struct TPolicyReplacementBoundary final
{
    using priority_type = std::uint32_t;

    TPolicyId policy_id{};
    TPolicySafePointId safe_point_id{};
    TPolicySafePointKind kind{TPolicySafePointKind::unknown};
    TPolicyReplacementEligibility eligibility{TPolicyReplacementEligibility::unknown};
    priority_type priority{0};

    constexpr TPolicyReplacementBoundary() noexcept = default;

    constexpr TPolicyReplacementBoundary(
        TPolicyId policyId,
        TPolicySafePointId safePointId,
        TPolicySafePointKind safePointKind,
        TPolicyReplacementEligibility replacementEligibility = TPolicyReplacementEligibility::unknown,
        priority_type boundaryPriority = 0) noexcept
        : policy_id(policyId),
          safe_point_id(safePointId),
          kind(safePointKind),
          eligibility(replacementEligibility),
          priority(boundaryPriority)
    {
    }

    [[nodiscard]] constexpr bool HasPolicy() const noexcept { return policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasSafePoint() const noexcept { return safe_point_id.IsValid(); }
    [[nodiscard]] constexpr bool IsClassified() const noexcept { return IsKnown(kind); }
    [[nodiscard]] constexpr bool IsEligible() const noexcept { return IsReplacementAllowed(eligibility); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasPolicy() && HasSafePoint() && IsClassified();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
