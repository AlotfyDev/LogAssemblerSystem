#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseId.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseId is the primitive identity token for a policy-local clause.
 *   A clause is not a full policy object; it is a governing content unit inside
 *   a future TPolicy aggregate and inside the future structural policy graph.
 *   This identifier allows clause-bearing structures, clause sets, diagnostics,
 *   safe-point participation, graph nodes, and future views to refer to a
 *   clause without depending on the final TPolicy aggregate or policy graph.
 *
 * Why this file exists in W02:
 *   The Policy Object taxonomy requires every policy object to contain clauses
 *   structurally. W02 introduces the clause layer as a dependency that later
 *   replacement, lifecycle, graph, traversal, aggregate, assignment, and
 *   registry waves may reference. This file supplies the smallest clause
 *   identity primitive required before richer clause structure is introduced.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClauseKind classifies the semantic content family of a clause.
 *   - TPolicyClauseRole describes how the clause participates in policy meaning.
 *   - TPolicyClauseStatus reports primitive clause-level validity/readiness.
 *   - TPolicyClause composes this identifier with kind, role, and owner policy
 *     identity.
 *   - TPolicyClauseSet and TPolicyClauseView expose collections and read-only
 *     views without creating TPolicy.
 *
 * Relationship to future waves:
 *   - W03 safe-point and replacement structures may identify clause
 *     participation through TPolicyClauseId.
 *   - W07 policy graph nodes may wrap or point to TPolicyClauseId.
 *   - W08 traversal foundations must not treat this identifier as a traversal
 *     cursor; traversal remains a separate channel-based layer.
 *   - W09 TPolicy will compose clause structures rather than replacing this
 *     primitive.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseId is not a clause body, not a clause truth evaluator, not a
 *   graph node by itself, not a traversal step, not a realization binding, and
 *   not a target reference. It carries identity only.
 *
 * Current implementation note:
 *   W02 intentionally uses a compact numeric value object. Richer scoped or
 *   graph-backed clause identity can be added later without changing the
 *   architectural role of this file.
 */
struct TPolicyClauseId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyClauseId() noexcept = default;
    explicit constexpr TPolicyClauseId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyClauseId Invalid() noexcept { return TPolicyClauseId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyClauseId lhs, TPolicyClauseId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyClauseId lhs, TPolicyClauseId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyClauseId lhs, TPolicyClauseId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
