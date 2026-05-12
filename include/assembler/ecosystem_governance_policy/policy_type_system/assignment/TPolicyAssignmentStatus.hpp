#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentStatus.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignmentStatus classifies the structural state of a policy
 *   assignment record. It tells whether an assignment relation is unknown,
 *   drafted, structurally ready, active as a representation, suspended,
 *   pending replacement, rejected, or retired. It does not express whether the
 *   policy has been executed or whether a target component accepted behavior.
 *
 * Why this file exists in W10:
 *   Assignment basics require status vocabulary before result and view carriers
 *   can be meaningful. Since lifecycle status belongs to the policy object and
 *   not to the assignment relation, W10 needs assignment-specific status terms
 *   that do not collapse assignment into policy lifecycle.
 *
 * Relationship to previous waves:
 *   - W04 policy lifecycle classifies the policy object's lifecycle state.
 *   - W10 assignment status classifies the relation between a policy and a
 *     target context. These must remain separate.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignment stores this status.
 *   - TPolicyAssignmentResult reports this status.
 *   - TPolicyAssignmentView exposes this status without mutation.
 *
 * Relationship to future waves:
 *   - W11 registry basics may classify registry entries using assignment status
 *     but must not treat status as executable scheduling state.
 *
 * Explicit non-responsibilities:
 *   This enum does not run lifecycle transitions, does not execute policy, does
 *   not model target readiness, does not model bridge/session state, and does
 *   not replace TPolicyLifecycleState.
 *
 * Current implementation note:
 *   The values are deliberately conservative. Later waves may refine status
 *   transitions, but W10 only needs reviewable structural assignment states.
 */
enum class TPolicyAssignmentStatus : std::uint8_t
{
    unknown = 0,
    drafted,
    ready,
    active,
    suspended,
    pending_replacement,
    rejected,
    retired
};

[[nodiscard]] constexpr bool IsUsable(TPolicyAssignmentStatus status) noexcept
{
    return status == TPolicyAssignmentStatus::ready ||
           status == TPolicyAssignmentStatus::active ||
           status == TPolicyAssignmentStatus::suspended ||
           status == TPolicyAssignmentStatus::pending_replacement;
}

[[nodiscard]] constexpr bool IsTerminal(TPolicyAssignmentStatus status) noexcept
{
    return status == TPolicyAssignmentStatus::rejected || status == TPolicyAssignmentStatus::retired;
}

} // namespace assembler::ecosystem_governance::policy_type_system
