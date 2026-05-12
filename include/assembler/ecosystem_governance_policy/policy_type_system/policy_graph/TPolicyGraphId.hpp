#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphId.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / root
 *
 * Full architectural responsibility:
 *   TPolicyGraphId is the primitive identity token for a structural policy graph. It identifies the bounded graph constitution that belongs to a future TPolicy without forcing the aggregate, traversal foundation, assignment workflow, or registry into existence.
 *
 * Why this file exists in W07:
 *   The Policy Object graph-structure draft requires a bounded graph around a single policy root. W07 starts with graph identity so nodes, edges, invariants, views, and the future policy aggregate can refer to one graph consistently.
 *
 * Relationship to previous waves:
 *   W01 provides TPolicyId, but a policy identifier and graph identifier are deliberately separate. W02 through W06 provide content, replacement, lifecycle, observation, and realization concepts that may be represented inside the graph but do not replace graph identity.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphNode and TPolicyGraphEdge use this identifier to remain graph-scoped. TPolicyGraphView uses it to expose a read-only graph reference.
 *
 * Relationship to future waves:
 *   W08 traversal foundation may refer to a graph but must not treat TPolicyGraphId as a traversal cursor or channel identity. W09 TPolicy may carry or expose graph identity as part of its aggregate view.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphId is not TPolicyId, not a graph node, not a traversal channel, not a registry entry, and not an execution handle. It carries graph identity only.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphId final
{
    using value_type = std::uint64_t;
    value_type value{0};

    constexpr TPolicyGraphId() noexcept = default;
    explicit constexpr TPolicyGraphId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyGraphId Invalid() noexcept { return TPolicyGraphId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyGraphId lhs, TPolicyGraphId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyGraphId lhs, TPolicyGraphId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyGraphId lhs, TPolicyGraphId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
