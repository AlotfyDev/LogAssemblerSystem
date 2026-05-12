#pragma once

#include <cstdint>
#include "TPolicyGraphEdgeId.hpp"
#include "TPolicyGraphEdgeKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraphId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/nodes/TPolicyGraphNodeId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphEdge.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / edges
 *
 * Full architectural responsibility:
 *   TPolicyGraphEdge is the structural connector carrier between policy graph nodes. It records source node, target node, and edge kind while preserving the rule that structural edges are not traversal instructions.
 *
 * Why this file exists in W07:
 *   The graph-structure draft defines structural edge taxonomy separately from deferred traversal semantics. W07 provides the edge carrier needed to build a structural graph before W08 traversal foundations.
 *
 * Relationship to previous waves:
 *   Previous waves define the semantic endpoint concepts that graph nodes may wrap. This file only connects node identifiers and does not inspect policy content.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphNode supplies source and target identities. TPolicyGraphInvariant uses edges to check required root-to-structure relations. TPolicyGraphView exposes edges read-only.
 *
 * Relationship to future waves:
 *   W08 will introduce Transition and Relation as traversal-foundation concepts. This structural edge must remain separate from those runtime-adjacent concepts.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphEdge is not a traversal transition, not a semantic relation object from W08, not an execution step, not a communication binding, not a bridge protocol frame, and not a scheduler decision.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphEdge final
{
    TPolicyGraphId graph_id{};
    TPolicyGraphEdgeId edge_id{};
    TPolicyGraphEdgeKind kind{TPolicyGraphEdgeKind::unknown};
    TPolicyGraphNodeId source_node_id{};
    TPolicyGraphNodeId target_node_id{};
    std::uint32_t flags{0};

    constexpr TPolicyGraphEdge() noexcept = default;

    constexpr TPolicyGraphEdge(
        TPolicyGraphId graph,
        TPolicyGraphEdgeId edge,
        TPolicyGraphEdgeKind edge_kind,
        TPolicyGraphNodeId source,
        TPolicyGraphNodeId target,
        std::uint32_t edge_flags = 0) noexcept
        : graph_id(graph), edge_id(edge), kind(edge_kind), source_node_id(source), target_node_id(target), flags(edge_flags) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return graph_id.IsValid() && edge_id.IsValid() && IsKnownPolicyGraphEdgeKind(kind) && source_node_id.IsValid() && target_node_id.IsValid();
    }

    [[nodiscard]] constexpr bool IsRootAnchored() const noexcept { return IsRootAnchoredPolicyGraphEdgeKind(kind); }
    [[nodiscard]] constexpr bool IsSelfEdge() const noexcept { return source_node_id == target_node_id; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
