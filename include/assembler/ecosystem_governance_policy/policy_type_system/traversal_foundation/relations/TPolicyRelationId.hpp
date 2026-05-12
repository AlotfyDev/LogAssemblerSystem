#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRelationId.hpp
 * Wave: EG-POL-W08_Traversal_Foundation_Types
 * Domain: ecosystem_governance / policy_type_system / traversal_foundation
 * Subdomain: relations
 *
 * Full architectural responsibility:
 *   TPolicyRelationId is the primitive identity token for a relation that semantically mediates connectivity between traversal channels.
 *
 * Why this file exists in W08:
 *   The traversal foundation treats connectors as passing through Relation rather than being empty lines. Relation identity is needed before transitions can reference relation-bearing connectivity safely.
 *
 * Relationship to previous waves:
 *   W01 through W06 provide policy identity, clauses, replacement, lifecycle,
 *   observation/audit, and realization-binding descriptors. W07 provides the
 *   structural policy graph. W08 must stand after those layers while remaining
 *   only a traversal-foundation vocabulary layer.
 *
 * Relationship to other files in this wave:
 *   TPolicyRelation uses this id. TPolicyTransition references a relation id instead of treating a transition as a naked source-to-target edge.
 *
 * Relationship to future waves:
 *   Future orchestration may attach richer relation semantics to this identity. W09 TPolicy may expose relation ids through traversal views.
 *
 * Explicit non-responsibilities:
 *   TPolicyRelationId is not a graph edge id, not a transition id, not a traversal instruction, not a branch selector, and not an execution handle.
 *
 * Current implementation note:
 *   W08 intentionally provides compact C++17 value objects and classification helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyRelationId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyRelationId() noexcept = default;
    explicit constexpr TPolicyRelationId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyRelationId Invalid() noexcept { return TPolicyRelationId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyRelationId lhs, TPolicyRelationId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyRelationId lhs, TPolicyRelationId rhs) noexcept { return !(lhs == rhs); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
