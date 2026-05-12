#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseRole.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseRole describes how a clause participates in policy meaning.
 *   Kind answers what semantic family the clause belongs to; role answers how
 *   the clause participates in the policy constitution. The split prevents a
 *   directive, parameter, or fallback clause from being overloaded with graph,
 *   traversal, replacement, or evaluation behavior too early.
 *
 * Why this file exists in W02:
 *   Clause roles let the clause layer remain expressive while still avoiding
 *   premature traversal, truth evaluation, or realization mechanics. The system
 *   can distinguish primary governing clauses, fallback clauses, refinement
 *   clauses, and dormant clauses without creating a full policy graph yet.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClause stores a role value.
 *   - TPolicyClauseView exposes role for diagnostics and future aggregate
 *     views.
 *   - TPolicyClauseSet can later preserve role-based ordering or selection
 *     without becoming a traversal engine.
 *
 * Relationship to future waves:
 *   - W03 may use role to identify replacement participation.
 *   - W07 graph relations may reference role when building structural clause
 *     relations.
 *   - W08 traversal foundation must remain separate from clause role.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseRole is not a graph edge, not a traversal relation, not an
 *   evaluation result, and not a target invocation directive. It is only a
 *   policy-local participation classifier.
 */
enum class TPolicyClauseRole : std::uint8_t
{
    unspecified = 0,
    primary,
    supporting,
    refinement,
    fallback,
    override_marker,
    exclusion_marker,
    dormant,
    diagnostic_only
};

[[nodiscard]] constexpr bool IsSpecified(TPolicyClauseRole role) noexcept
{
    return role != TPolicyClauseRole::unspecified;
}

[[nodiscard]] constexpr bool IsDormant(TPolicyClauseRole role) noexcept
{
    return role == TPolicyClauseRole::dormant;
}

} // namespace assembler::ecosystem_governance::policy_type_system
