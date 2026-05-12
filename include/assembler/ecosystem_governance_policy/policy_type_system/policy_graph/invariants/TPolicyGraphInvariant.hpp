#pragma once

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphInvariant.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / invariants
 *
 * Full architectural responsibility:
 *   TPolicyGraphInvariant classifies structural checks required for a valid policy object graph, including root uniqueness, identity presence, clause presence, safe-point presence, lifecycle presence, realization-binding presence, observation presence, and structural edge sanity.
 *
 * Why this file exists in W07:
 *   W07 must provide graph constitution rules without building TPolicy or traversal. This enum names the invariant families that a report can evaluate and future implementation can expand.
 *
 * Relationship to previous waves:
 *   Previous waves define mandatory semantic elements. This file turns those semantic requirements into structural graph invariant categories.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphInvariantReport records pass/fail state for these invariant families. TPolicyGraph and TPolicyGraphView provide the material over which invariants are assessed.
 *
 * Relationship to future waves:
 *   W08 traversal foundation must not reinterpret these invariants as traversal readiness. W09 TPolicy may use invariant reports to decide aggregate structural validity.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphInvariant is not a runtime validator engine, not a policy evaluator, not clause truth evaluation, not a replacement algorithm, not realization execution, and not traversal orchestration.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
enum class TPolicyGraphInvariant
{
    unknown = 0,
    single_root_required = 1,
    identity_structure_required = 2,
    clause_presence_required = 3,
    safe_point_presence_required = 4,
    lifecycle_structure_required = 5,
    realization_binding_required = 6,
    observation_structure_required = 7,
    edge_endpoint_validity_required = 8,
    graph_identity_required = 9,
    target_kind_descriptor_optional = 10,
    applicability_structure_optional = 11
};

[[nodiscard]] constexpr bool IsRequiredPolicyGraphInvariant(TPolicyGraphInvariant invariant) noexcept
{
    return invariant == TPolicyGraphInvariant::single_root_required ||
           invariant == TPolicyGraphInvariant::identity_structure_required ||
           invariant == TPolicyGraphInvariant::clause_presence_required ||
           invariant == TPolicyGraphInvariant::safe_point_presence_required ||
           invariant == TPolicyGraphInvariant::lifecycle_structure_required ||
           invariant == TPolicyGraphInvariant::realization_binding_required ||
           invariant == TPolicyGraphInvariant::observation_structure_required ||
           invariant == TPolicyGraphInvariant::edge_endpoint_validity_required ||
           invariant == TPolicyGraphInvariant::graph_identity_required;
}

} // namespace assembler::ecosystem_governance::policy_type_system
