#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseStatus.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseStatus is the primitive status vocabulary for a clause as a
 *   policy-local structural element. It allows the clause layer to report
 *   whether a clause is structurally absent, incomplete, valid, dormant,
 *   unsupported, or conflicting without creating a full validation report or a
 *   policy aggregate.
 *
 * Why this file exists in W02:
 *   Clause objects and clause sets need small status semantics before later
 *   waves introduce lifecycle, observation, graph invariants, assignment, or
 *   registry reporting. This file keeps W02 self-contained and prevents clause
 *   validation from being confused with policy execution.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClause may carry a status.
 *   - TPolicyClauseView exposes status.
 *   - TPolicyClauseSet may derive coarse validity from member statuses.
 *
 * Relationship to future waves:
 *   - W07 graph invariant reports may translate clause statuses into graph
 *     findings.
 *   - W09 TPolicy validation reports may compose clause status information.
 *   - W05 observation may record clause-related evidence, but this status enum
 *     is not itself an audit trail.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseStatus is not lifecycle state, not applicability result, not
 *   clause truth, not traversal readiness, and not target execution status.
 */
enum class TPolicyClauseStatus : std::uint8_t
{
    unknown = 0,
    absent,
    incomplete,
    valid,
    dormant,
    unsupported,
    conflicting,
    invalid
};

[[nodiscard]] constexpr bool IsUsable(TPolicyClauseStatus status) noexcept
{
    return status == TPolicyClauseStatus::valid || status == TPolicyClauseStatus::dormant;
}

[[nodiscard]] constexpr bool IsFailure(TPolicyClauseStatus status) noexcept
{
    return status == TPolicyClauseStatus::unsupported || status == TPolicyClauseStatus::conflicting || status == TPolicyClauseStatus::invalid;
}

} // namespace assembler::ecosystem_governance::policy_type_system
