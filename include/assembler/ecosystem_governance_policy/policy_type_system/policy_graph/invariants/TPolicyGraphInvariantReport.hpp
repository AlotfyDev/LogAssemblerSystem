#pragma once

#include <cstdint>
#include "TPolicyGraphInvariant.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraphId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/nodes/TPolicyGraphNodeId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/edges/TPolicyGraphEdgeId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphInvariantReport.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / invariants
 *
 * Full architectural responsibility:
 *   TPolicyGraphInvariantReport records structural evidence about whether a policy graph satisfies one invariant family. It supports later review, diagnostics, and TPolicy aggregate construction without becoming a logging framework or validation engine.
 *
 * Why this file exists in W07:
 *   The graph-structure draft requires minimum structural invariants for policy-object graphs. W07 provides a compact report carrier so invariants can be expressed and smoke-tested while detailed validation remains later work.
 *
 * Relationship to previous waves:
 *   Previous waves provide the semantic requirements that the invariant references. W07 reports do not execute policy content or lifecycle behavior.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphInvariant names the invariant. Node and edge ids identify the structural subject when relevant. TPolicyGraphView may expose reports later.
 *
 * Relationship to future waves:
 *   W09 TPolicy may aggregate invariant reports into policy validation results. W10 assignment and W11 registry may reject structurally invalid policies, but this file does not implement those workflows.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphInvariantReport is not TPolicyResult, not a policy registry record, not an audit trail, not telemetry, not a traversal readiness result, and not a runtime validator.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphInvariantReport final
{
    TPolicyGraphId graph_id{};
    TPolicyGraphInvariant invariant{TPolicyGraphInvariant::unknown};
    bool satisfied{false};
    TPolicyGraphNodeId subject_node_id{};
    TPolicyGraphEdgeId subject_edge_id{};
    std::uint32_t evidence_flags{0};

    constexpr TPolicyGraphInvariantReport() noexcept = default;

    constexpr TPolicyGraphInvariantReport(
        TPolicyGraphId graph,
        TPolicyGraphInvariant invariant_kind,
        bool is_satisfied,
        TPolicyGraphNodeId node = {},
        TPolicyGraphEdgeId edge = {},
        std::uint32_t flags = 0) noexcept
        : graph_id(graph), invariant(invariant_kind), satisfied(is_satisfied), subject_node_id(node), subject_edge_id(edge), evidence_flags(flags) {}

    [[nodiscard]] constexpr bool IsKnown() const noexcept { return invariant != TPolicyGraphInvariant::unknown; }
    [[nodiscard]] constexpr bool IsRequired() const noexcept { return IsRequiredPolicyGraphInvariant(invariant); }
    [[nodiscard]] constexpr bool IsFailure() const noexcept { return IsRequired() && !satisfied; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
