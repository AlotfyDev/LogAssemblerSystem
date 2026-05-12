#pragma once

#include <array>
#include <cstddef>
#include "TPolicyGraphId.hpp"
#include "nodes/TPolicyGraphNode.hpp"
#include "edges/TPolicyGraphEdge.hpp"
#include "views/TPolicyGraphView.hpp"
#include "invariants/TPolicyGraphInvariantReport.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraph.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / root
 *
 * Full architectural responsibility:
 *   TPolicyGraph is the W07 aggregate for structural graph constitution only. It owns bounded arrays of structural nodes and structural edges, exposes a read-only view, and provides minimal structural checks aligned with the Policy Object Graph Structure doctrine.
 *
 * Why this file exists in W07:
 *   W07 is the first wave allowed to introduce policy graph structure after primitives, clauses, replacement, lifecycle, observation, and realization binding foundations exist. This file gathers those structural carriers without creating TPolicy or traversal.
 *
 * Relationship to previous waves:
 *   Previous waves contribute semantic objects that may be represented by graph nodes. TPolicyGraph references them through node carriers rather than owning their full behavior.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphId identifies the graph; TPolicyGraphNode and TPolicyGraphEdge hold structure; TPolicyGraphInvariantReport describes structural evidence; TPolicyGraphView exposes read-only access.
 *
 * Relationship to future waves:
 *   W08 traversal foundation will introduce sequence channels and transitions separately. W09 TPolicy will be the first wave allowed to aggregate this graph with the rest of the policy object.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraph is not TPolicy, not a traversal graph, not a traversal engine, not a policy executor, not a realization mechanism, not a target owner, not an assignment, and not a registry.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraph final
{
    static constexpr std::size_t max_nodes = 32;
    static constexpr std::size_t max_edges = 64;

    TPolicyGraphId graph_id{};
    std::array<TPolicyGraphNode, max_nodes> nodes{};
    std::array<TPolicyGraphEdge, max_edges> edges{};
    std::size_t node_count{0};
    std::size_t edge_count{0};

    constexpr TPolicyGraph() noexcept = default;
    explicit constexpr TPolicyGraph(TPolicyGraphId id) noexcept : graph_id(id) {}

    [[nodiscard]] constexpr bool CanAddNode() const noexcept { return node_count < max_nodes; }
    [[nodiscard]] constexpr bool CanAddEdge() const noexcept { return edge_count < max_edges; }

    constexpr bool AddNode(const TPolicyGraphNode& node) noexcept
    {
        if (!CanAddNode() || !node.IsValid() || node.graph_id != graph_id)
        {
            return false;
        }
        nodes[node_count++] = node;
        return true;
    }

    constexpr bool AddEdge(const TPolicyGraphEdge& edge) noexcept
    {
        if (!CanAddEdge() || !edge.IsValid() || edge.graph_id != graph_id)
        {
            return false;
        }
        edges[edge_count++] = edge;
        return true;
    }

    [[nodiscard]] constexpr TPolicyGraphView View() const noexcept
    {
        return TPolicyGraphView{graph_id, nodes.data(), node_count, edges.data(), edge_count};
    }

    [[nodiscard]] constexpr std::size_t CountNodesOfKind(TPolicyGraphNodeKind kind) const noexcept
    {
        std::size_t count = 0;
        for (std::size_t i = 0; i < node_count; ++i)
        {
            if (nodes[i].kind == kind)
            {
                ++count;
            }
        }
        return count;
    }

    [[nodiscard]] constexpr std::size_t CountEdgesOfKind(TPolicyGraphEdgeKind kind) const noexcept
    {
        std::size_t count = 0;
        for (std::size_t i = 0; i < edge_count; ++i)
        {
            if (edges[i].kind == kind)
            {
                ++count;
            }
        }
        return count;
    }

    [[nodiscard]] constexpr bool HasSingleRoot() const noexcept
    {
        return CountNodesOfKind(TPolicyGraphNodeKind::policy_root) == 1;
    }

    [[nodiscard]] constexpr bool HasMinimumRequiredNodeKinds() const noexcept
    {
        return HasSingleRoot() &&
               CountNodesOfKind(TPolicyGraphNodeKind::identity_structure) >= 1 &&
               CountNodesOfKind(TPolicyGraphNodeKind::clause) >= 1 &&
               CountNodesOfKind(TPolicyGraphNodeKind::safe_point) >= 1 &&
               CountNodesOfKind(TPolicyGraphNodeKind::lifecycle_state) >= 1 &&
               CountNodesOfKind(TPolicyGraphNodeKind::realization_binding) >= 1 &&
               CountNodesOfKind(TPolicyGraphNodeKind::observation_audit) >= 1;
    }

    [[nodiscard]] constexpr bool HasMinimumRequiredRootEdges() const noexcept
    {
        return CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_identity) >= 1 &&
               CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_clause) >= 1 &&
               CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_safe_point) >= 1 &&
               CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_lifecycle) >= 1 &&
               CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_realization_binding) >= 1 &&
               CountEdgesOfKind(TPolicyGraphEdgeKind::root_to_observation) >= 1;
    }

    [[nodiscard]] constexpr bool IsStructurallyValidMinimum() const noexcept
    {
        return graph_id.IsValid() && HasMinimumRequiredNodeKinds() && HasMinimumRequiredRootEdges();
    }

    [[nodiscard]] constexpr TPolicyGraphInvariantReport ReportMinimumValidity() const noexcept
    {
        return TPolicyGraphInvariantReport{graph_id, TPolicyGraphInvariant::single_root_required, IsStructurallyValidMinimum()};
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
