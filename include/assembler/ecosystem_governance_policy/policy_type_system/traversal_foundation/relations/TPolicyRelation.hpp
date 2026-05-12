#pragma once

#include "TPolicyRelationId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRelation.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: relations
 *
 * Full architectural responsibility:
 *   TPolicyRelation represents the semantic constituent through which traversal connectivity is mediated. It preserves relation-bearing meaning without executing branch, merge, return, or readiness behavior.
 *
 * Why this file exists in W08:
 *   The traversal foundation requires Relation as a first-class semantic constituent so transitions are not treated as empty adjacency. W08 records relation kind and identity only.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicyTransition references TPolicyRelationId. TPolicyTraversalFoundationView may expose relation arrays alongside channels and transitions.
 *
 * Relationship to future waves:
 *   Future orchestration may define concrete semantics for precedence, branch, merge, return, readiness-gated, and replacement-sensitive relations.
 *
 * Explicit non-responsibilities:
 *   TPolicyRelation is not a graph edge, not a transition, not a traversal engine, not a branch algorithm, not a merge algorithm, and not a scheduler.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicyRelationKind
{
    unknown = 0,
    precedence = 1,
    branch = 2,
    merge = 3,
    return_continuation = 4,
    readiness_gate = 5,
    replacement_sensitive = 6,
    extension = 7
};

[[nodiscard]] constexpr bool IsKnownPolicyRelationKind(TPolicyRelationKind kind) noexcept
{
    return kind != TPolicyRelationKind::unknown;
}

struct TPolicyRelation final
{
    TPolicyRelationId relation_id{};
    TPolicyRelationKind kind{TPolicyRelationKind::unknown};
    bool required{false};

    constexpr TPolicyRelation() noexcept = default;
    constexpr TPolicyRelation(TPolicyRelationId id, TPolicyRelationKind k, bool is_required = false) noexcept
        : relation_id(id), kind(k), required(is_required) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return relation_id.IsValid() && IsKnownPolicyRelationKind(kind);
    }

    [[nodiscard]] constexpr bool IsMergeLike() const noexcept
    {
        return kind == TPolicyRelationKind::merge;
    }

    [[nodiscard]] constexpr bool IsBranchLike() const noexcept
    {
        return kind == TPolicyRelationKind::branch;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
