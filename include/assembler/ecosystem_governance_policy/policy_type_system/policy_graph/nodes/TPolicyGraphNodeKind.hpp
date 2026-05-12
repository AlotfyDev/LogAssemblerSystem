#pragma once

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphNodeKind.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / nodes
 *
 * Full architectural responsibility:
 *   TPolicyGraphNodeKind classifies the structural role of a node in the policy graph constitution. It mirrors the approved graph taxonomy: root, identity, clause, safe point, lifecycle/state, realization binding, target-kind descriptor, observation/audit, applicability, and extension nodes.
 *
 * Why this file exists in W07:
 *   W07 needs an explicit node-kind vocabulary so graph invariants can verify structural validity without running traversal or realization logic.
 *
 * Relationship to previous waves:
 *   W01 through W06 introduced semantic layers that may be represented by node kinds. This enum connects those layers structurally without absorbing their ownership.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphNode carries this kind. TPolicyGraphInvariant uses it when checking minimum graph validity.
 *
 * Relationship to future waves:
 *   W08 traversal foundation may later build channels over or around graph nodes, but kind classification remains structural. W09 TPolicy aggregate can expose node-kind views safely.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphNodeKind is not a traversal state, not lifecycle state, not realization mode, not target kind, and not an executor dispatch code.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicyGraphNodeKind
{
    unknown = 0,
    policy_root = 1,
    identity_structure = 2,
    clause = 3,
    safe_point = 4,
    lifecycle_state = 5,
    realization_binding = 6,
    target_kind_descriptor = 7,
    observation_audit = 8,
    applicability = 9,
    extension = 10
};

[[nodiscard]] constexpr bool IsMandatoryPolicyGraphNodeKind(TPolicyGraphNodeKind kind) noexcept
{
    return kind == TPolicyGraphNodeKind::policy_root ||
           kind == TPolicyGraphNodeKind::identity_structure ||
           kind == TPolicyGraphNodeKind::clause ||
           kind == TPolicyGraphNodeKind::safe_point ||
           kind == TPolicyGraphNodeKind::lifecycle_state ||
           kind == TPolicyGraphNodeKind::realization_binding ||
           kind == TPolicyGraphNodeKind::observation_audit;
}

[[nodiscard]] constexpr bool IsOptionalPolicyGraphNodeKind(TPolicyGraphNodeKind kind) noexcept
{
    return kind == TPolicyGraphNodeKind::target_kind_descriptor ||
           kind == TPolicyGraphNodeKind::applicability ||
           kind == TPolicyGraphNodeKind::extension;
}

[[nodiscard]] constexpr bool IsKnownPolicyGraphNodeKind(TPolicyGraphNodeKind kind) noexcept
{
    return kind != TPolicyGraphNodeKind::unknown;
}

} // namespace assembler::ecosystem_governance::policy_type_system
