#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTransitionId.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: transitions
 *
 * Full architectural responsibility:
 *   TPolicyTransitionId is the primitive identity token for a channel-to-channel transition. It lets transitions be referenced without reducing them to graph edges or relation ids.
 *
 * Why this file exists in W08:
 *   Transition is the foundational movement concept between sequence channels. A distinct id preserves the difference between movement, relation semantics, and structural graph adjacency.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicyTransition carries this id and separately references source channel, relation, and target channel.
 *
 * Relationship to future waves:
 *   Future traversal orchestration may use transition ids for path composition, diagnostics, or execution traces. W09 TPolicy may expose transition ids safely.
 *
 * Explicit non-responsibilities:
 *   TPolicyTransitionId is not a relation id, not a graph edge id, not an execution step id, not a scheduler tick, and not an invocation handle.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyTransitionId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyTransitionId() noexcept = default;
    explicit constexpr TPolicyTransitionId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyTransitionId Invalid() noexcept { return TPolicyTransitionId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyTransitionId lhs, TPolicyTransitionId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyTransitionId lhs, TPolicyTransitionId rhs) noexcept { return !(lhs == rhs); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
