#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseId.hpp>
#include "TPolicySafePointId.hpp"
#include "TPolicySafePointKind.hpp"
#include "TPolicyReplacementEligibility.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySafePoint.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicySafePoint is the primitive structural carrier for a safe replacement
 *   anchor inside a policy. A safe point may belong to the policy globally or
 *   may be associated with a particular clause identity. It represents the
 *   policy-side notion of where replacement discipline can be evaluated.
 *
 * Why this file exists in W03:
 *   The Policy Object Graph Structure requires one or more Safe Point Nodes for
 *   a valid policy graph. Before the graph layer exists, W03 needs a semantic
 *   carrier that can name and classify safe points and relate them to policy and
 *   clause identities.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePointId identifies the safe point.
 *   - TPolicySafePointKind classifies the anchor.
 *   - TPolicyReplacementEligibility records structural replacement readiness.
 *   - TPolicyReplacementBoundary may wrap this safe point as a boundary.
 *   - TPolicyReplacementRule and TPolicyReplacementPlan may reference it.
 *
 * Relationship to previous waves:
 *   - W01 provides TPolicyId for owner policy identity.
 *   - W02 provides TPolicyClauseId for optional clause-specific safe points.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may map safe point availability to lifecycle state.
 *   - W07 graph structure may turn safe points into Safe Point Nodes.
 *   - W08 traversal foundation may treat safe points as metadata, not channel
 *     movement.
 *   - W09 TPolicy will aggregate safe points as part of replacement semantics.
 *
 * Explicit non-responsibilities:
 *   TPolicySafePoint does not execute replacement, does not own target objects,
 *   does not synchronize threads, does not traverse a graph, and does not carry
 *   observation/audit evidence.
 *
 * Current implementation note:
 *   W03 uses a compact carrier with optional clause association. Richer
 *   replacement-sensitive policy families may extend around this carrier later.
 */
struct TPolicySafePoint final
{
    using ordinal_type = std::uint32_t;

    TPolicySafePointId id{};
    TPolicyId policy_id{};
    TPolicyClauseId clause_id{};
    TPolicySafePointKind kind{TPolicySafePointKind::unknown};
    TPolicyReplacementEligibility eligibility{TPolicyReplacementEligibility::unknown};
    ordinal_type ordinal{0};

    constexpr TPolicySafePoint() noexcept = default;

    constexpr TPolicySafePoint(
        TPolicySafePointId safePointId,
        TPolicyId ownerPolicyId,
        TPolicySafePointKind safePointKind,
        TPolicyReplacementEligibility replacementEligibility = TPolicyReplacementEligibility::unknown,
        ordinal_type safePointOrdinal = 0,
        TPolicyClauseId relatedClauseId = TPolicyClauseId{}) noexcept
        : id(safePointId),
          policy_id(ownerPolicyId),
          clause_id(relatedClauseId),
          kind(safePointKind),
          eligibility(replacementEligibility),
          ordinal(safePointOrdinal)
    {
    }

    [[nodiscard]] constexpr bool HasIdentity() const noexcept { return id.IsValid(); }
    [[nodiscard]] constexpr bool HasOwnerPolicy() const noexcept { return policy_id.IsValid(); }
    [[nodiscard]] constexpr bool IsClauseBound() const noexcept { return clause_id.IsValid(); }
    [[nodiscard]] constexpr bool IsClassified() const noexcept { return IsKnown(kind); }
    [[nodiscard]] constexpr bool IsEligible() const noexcept { return IsReplacementAllowed(eligibility); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasIdentity() && HasOwnerPolicy() && IsClassified();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
