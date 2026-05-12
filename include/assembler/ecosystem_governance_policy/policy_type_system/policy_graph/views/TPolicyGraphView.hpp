#pragma once

#include <cstddef>
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraphId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/nodes/TPolicyGraphNode.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/edges/TPolicyGraphEdge.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphView.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / views
 *
 * Full architectural responsibility:
 *   TPolicyGraphView is a lightweight read-only view over structural policy graph material. It exposes graph identity, node array, edge array, and counts without granting mutation or traversal execution authority.
 *
 * Why this file exists in W07:
 *   W07 needs a view surface so later TPolicy and diagnostics can inspect graph constitution safely. The view is deliberately structural and read-only.
 *
 * Relationship to previous waves:
 *   Previous waves provide semantic data that nodes may reference. This view does not inspect or evaluate those underlying semantic objects.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraph can produce this view. Node and edge carriers are exposed as const arrays. Invariant reports may be derived from this view later.
 *
 * Relationship to future waves:
 *   W08 traversal foundation may read graph structure through a view, but it must introduce its own sequence channel vocabulary. W09 TPolicy may expose this view as part of policy introspection.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphView is not a traversal cursor, not a mutable graph builder, not a registry view, not a communication view, not an audit log, and not a target or mechanism view.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphView final
{
    TPolicyGraphId graph_id{};
    const TPolicyGraphNode* nodes{nullptr};
    std::size_t node_count{0};
    const TPolicyGraphEdge* edges{nullptr};
    std::size_t edge_count{0};

    constexpr TPolicyGraphView() noexcept = default;

    constexpr TPolicyGraphView(
        TPolicyGraphId graph,
        const TPolicyGraphNode* node_begin,
        std::size_t nodes_size,
        const TPolicyGraphEdge* edge_begin,
        std::size_t edges_size) noexcept
        : graph_id(graph), nodes(node_begin), node_count(nodes_size), edges(edge_begin), edge_count(edges_size) {}

    [[nodiscard]] constexpr bool IsEmpty() const noexcept { return node_count == 0 && edge_count == 0; }
    [[nodiscard]] constexpr bool HasGraphId() const noexcept { return graph_id.IsValid(); }
    [[nodiscard]] constexpr bool HasNodes() const noexcept { return nodes != nullptr && node_count > 0; }
    [[nodiscard]] constexpr bool HasEdges() const noexcept { return edges != nullptr && edge_count > 0; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
