#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphEdgeId.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / edges
 *
 * Full architectural responsibility:
 *   TPolicyGraphEdgeId identifies a structural relation edge inside a policy graph. It allows the graph to distinguish one structural connector from another without turning connectivity into traversal order.
 *
 * Why this file exists in W07:
 *   The graph-structure draft requires structural edge taxonomy and explicitly states that structural edges are not traversal instructions. W07 introduces edge identity to support that separation.
 *
 * Relationship to previous waves:
 *   Previous waves provide semantic elements that edges may relate: clauses, safe points, lifecycle structure, realization binding, target-kind descriptors, observation, and dormant applicability.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphEdge uses this id. TPolicyGraphInvariantReport may cite it when reporting structural errors.
 *
 * Relationship to future waves:
 *   W08 traversal foundation will introduce transitions and relations, but those are separate from structural edges. W09 TPolicy may expose edge ids through graph views.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphEdgeId is not a transition id, not a relation id, not a traversal cursor, not an execution step, and not a bridge or communication binding.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphEdgeId final
{
    using value_type = std::uint64_t;
    value_type value{0};

    constexpr TPolicyGraphEdgeId() noexcept = default;
    explicit constexpr TPolicyGraphEdgeId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyGraphEdgeId Invalid() noexcept { return TPolicyGraphEdgeId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyGraphEdgeId lhs, TPolicyGraphEdgeId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyGraphEdgeId lhs, TPolicyGraphEdgeId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyGraphEdgeId lhs, TPolicyGraphEdgeId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
