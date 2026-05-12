#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseKind.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseKind classifies the semantic kind of a policy-local clause.
 *   The taxonomy describes clauses as units such as execution directives,
 *   constraints, parameters, preferences, fallback directives, and replacement-
 *   related directives. This enum preserves that semantic vocabulary without
 *   converting clause kinds into executable behavior.
 *
 * Why this file exists in W02:
 *   Policy clauses must be present structurally before replacement, lifecycle,
 *   observation, realization binding, graph structure, traversal, and TPolicy
 *   aggregate can be built. W02 needs a small, stable kind vocabulary so later
 *   waves can distinguish clause content families without inventing their own
 *   local classification schemes.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClause stores a kind value.
 *   - TPolicyClauseView exposes kind without exposing mutable clause internals.
 *   - TPolicyClauseSet may count or filter by kind in later extensions.
 *
 * Relationship to future waves:
 *   - W03 may connect replacement-related clauses to safe-point structures.
 *   - W07 may use this kind when constructing clause graph nodes.
 *   - W08 must not turn clause kind into traversal behavior.
 *   - W09 may expose clause kind through TPolicyView.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseKind does not evaluate clause truth, does not select a branch,
 *   does not invoke a mechanism, and does not define target behavior. It is a
 *   semantic classifier only.
 */
enum class TPolicyClauseKind : std::uint8_t
{
    unknown = 0,
    directive,
    constraint,
    parameter,
    preference,
    fallback,
    replacement_directive,
    metadata_hint,
    lifecycle_hint,
    observation_hint
};

[[nodiscard]] constexpr bool IsSpecified(TPolicyClauseKind kind) noexcept
{
    return kind != TPolicyClauseKind::unknown;
}

[[nodiscard]] constexpr bool IsReplacementRelated(TPolicyClauseKind kind) noexcept
{
    return kind == TPolicyClauseKind::replacement_directive;
}

} // namespace assembler::ecosystem_governance::policy_type_system
