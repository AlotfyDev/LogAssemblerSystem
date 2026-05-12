#pragma once

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TPolicySafePointSwitchDecision.hpp
 *
 * Architectural role:
 *   Defines the decision vocabulary for safe-point switch planning, including allowed, deferred, rejected, and forbidden outcomes.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantics as DTOs. W36 lets the target declare realization capabilities and semantic-to-target mappings. W37 defines completed policy objects. W38 defines the target-owned Policy Object Host Surface and its assignment port. W39 introduces the domain-local PolicyAssigner and safe-point switch model that coordinates completed-policy-object switching only through host-declared safe points.
 *
 * Full intended picture:
 *   Governance provides semantics, the target completes the policy object, the target-owned host stages it, and the domain-local assigner decides whether a safe-point switch is allowed. The assigner writes only assignment-port metadata in this foundation wave; it does not execute runtime behavior.
 *
 * Explicit non-responsibilities:
 *   This file does not invoke targets, mutate functional object behavior, execute policy logic, call a realizer, persist assignment state, export audit, or bypass host safe-point rules. 
 */

enum class TPolicySafePointSwitchDecision
{
    unknown = 0,
    allowed,
    allowed_with_warning,
    deferred_until_safe_point,
    rejected_no_pending_policy,
    rejected_host_not_ready,
    rejected_safe_point_closed,
    rejected_incompatible_host,
    forbidden
};

[[nodiscard]] constexpr bool decision_allows_switch(TPolicySafePointSwitchDecision decision) noexcept
{
    return decision == TPolicySafePointSwitchDecision::allowed ||
           decision == TPolicySafePointSwitchDecision::allowed_with_warning;
}

[[nodiscard]] constexpr bool decision_is_rejection(TPolicySafePointSwitchDecision decision) noexcept
{
    return decision == TPolicySafePointSwitchDecision::rejected_no_pending_policy ||
           decision == TPolicySafePointSwitchDecision::rejected_host_not_ready ||
           decision == TPolicySafePointSwitchDecision::rejected_safe_point_closed ||
           decision == TPolicySafePointSwitchDecision::rejected_incompatible_host ||
           decision == TPolicySafePointSwitchDecision::forbidden;
}
}
