#pragma once

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObjectStatus.hpp
 *
 * Architectural role:
 *   Defines completion lifecycle vocabulary for completed policy object creation and readiness for later host assignment.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantic bundles as DTOs. W36 lets a target declare realization capabilities and semantic-to-target mapping rules. W37 introduces the completed policy object as the first carrier that combines governance semantic identity with target realization-map evidence. This follows ARCH-009: Policy Object completion precedes assignment, and assignment later occurs through a target-owned host at a declared safe point.
 *
 * Full intended picture:
 *   A domain will receive a governance semantic bundle, validate it against target capability declarations and target realization maps, then produce a completed policy object. Domain-facing views can then expose completed policy objects for later host assignment, safe-point switching, audit, and readiness reporting.
 *
 * Explicit non-responsibilities:
 *   This file does not assign a policy to a target, host a policy object, perform safe-point switching, invoke a realizer, mutate target state, persist policy records, or run production execution. 
 */

enum class TCompletedPolicyObjectStatus
{
    unknown = 0,
    draft,
    semantic_received,
    target_map_attached,
    completion_pending,
    completed,
    completion_failed,
    deprecated,
    forbidden
};

[[nodiscard]] constexpr bool is_completed_status(TCompletedPolicyObjectStatus status) noexcept
{
    return status == TCompletedPolicyObjectStatus::completed;
}

[[nodiscard]] constexpr bool is_terminal_negative(TCompletedPolicyObjectStatus status) noexcept
{
    return status == TCompletedPolicyObjectStatus::completion_failed ||
           status == TCompletedPolicyObjectStatus::forbidden;
}
}
