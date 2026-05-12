#pragma once

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphEdgeKind.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / edges
 *
 * Full architectural responsibility:
 *   TPolicyGraphEdgeKind classifies legal structural edge families in the policy graph constitution, including root-to-identity, root-to-clause, clause-to-clause, root-to-safe-point, clause-to-safe-point, lifecycle, realization binding, target-kind, observation, and applicability relations.
 *
 * Why this file exists in W07:
 *   W07 needs edge-kind vocabulary to validate graph constitution without introducing W08 traversal semantics.
 *
 * Relationship to previous waves:
 *   The prior semantic waves define what edge endpoints may refer to. This enum does not own those endpoint objects; it only classifies structural linkage.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphEdge uses this kind. TPolicyGraphInvariant uses it to detect required structural relations.
 *
 * Relationship to future waves:
 *   W08 traversal will introduce Transition and Relation as separate concepts. This enum must remain a structural edge classifier.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphEdgeKind is not a traversal relation kind, not a protocol step, not execution order, not graph traversal permission, and not a scheduler decision.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicyGraphEdgeKind
{
    unknown = 0,
    root_to_identity = 1,
    root_to_clause = 2,
    clause_to_clause = 3,
    root_to_safe_point = 4,
    clause_to_safe_point = 5,
    root_to_lifecycle = 6,
    lifecycle_structural = 7,
    root_to_realization_binding = 8,
    realization_binding_to_target_kind = 9,
    root_to_observation = 10,
    root_to_applicability = 11,
    extension = 12
};

[[nodiscard]] constexpr bool IsRootAnchoredPolicyGraphEdgeKind(TPolicyGraphEdgeKind kind) noexcept
{
    return kind == TPolicyGraphEdgeKind::root_to_identity ||
           kind == TPolicyGraphEdgeKind::root_to_clause ||
           kind == TPolicyGraphEdgeKind::root_to_safe_point ||
           kind == TPolicyGraphEdgeKind::root_to_lifecycle ||
           kind == TPolicyGraphEdgeKind::root_to_realization_binding ||
           kind == TPolicyGraphEdgeKind::root_to_observation ||
           kind == TPolicyGraphEdgeKind::root_to_applicability;
}

[[nodiscard]] constexpr bool IsKnownPolicyGraphEdgeKind(TPolicyGraphEdgeKind kind) noexcept
{
    return kind != TPolicyGraphEdgeKind::unknown;
}

} // namespace assembler::ecosystem_governance::policy_type_system
