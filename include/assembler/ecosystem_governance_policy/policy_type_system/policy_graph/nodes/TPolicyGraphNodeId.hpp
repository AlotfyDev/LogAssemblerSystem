#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphNodeId.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / nodes
 *
 * Full architectural responsibility:
 *   TPolicyGraphNodeId identifies a structural node inside a bounded policy graph. It lets root, identity, clause, safe-point, lifecycle, realization-binding, observation, applicability, and target-kind nodes be referenced without turning them into traversal steps or runtime objects.
 *
 * Why this file exists in W07:
 *   The graph-structure draft requires node taxonomy before traversal. W07 introduces node identity so the graph can be assembled and validated structurally while keeping W08 traversal separate.
 *
 * Relationship to previous waves:
 *   Previous waves define the semantic content that certain nodes may reference. TPolicyGraphNodeId does not replace TPolicyClauseId, TPolicySafePointId, or TPolicyRealizationBindingId; it identifies the graph node that may wrap or point to those concepts.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphNode uses this identifier. TPolicyGraphEdge uses it as source and target. TPolicyGraphInvariantReport may mention missing or invalid node identities.
 *
 * Relationship to future waves:
 *   W08 traversal may later map channels over structural nodes, but this identifier must not become a cursor. W09 TPolicy may expose nodes through TPolicyGraphView.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphNodeId is not a policy id, not a content id, not an edge id, not a traversal cursor, not a runtime state handle, and not a target object reference.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphNodeId final
{
    using value_type = std::uint64_t;
    value_type value{0};

    constexpr TPolicyGraphNodeId() noexcept = default;
    explicit constexpr TPolicyGraphNodeId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyGraphNodeId Invalid() noexcept { return TPolicyGraphNodeId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyGraphNodeId lhs, TPolicyGraphNodeId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyGraphNodeId lhs, TPolicyGraphNodeId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyGraphNodeId lhs, TPolicyGraphNodeId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
