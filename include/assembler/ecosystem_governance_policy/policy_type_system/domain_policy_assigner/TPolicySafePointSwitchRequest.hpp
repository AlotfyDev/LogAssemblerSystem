#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostId.hpp"

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TPolicySafePointSwitchRequest.hpp
 *
 * Architectural role:
 *   Defines the request carrier for asking a domain assigner to plan a completed-policy-object switch through a target host.
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

struct TPolicySafePointSwitchRequest
{
    TDomainPolicyAssignerId assigner_id;
    policy_object_host::TPolicyObjectHostId host_id;
    completed_policy_object::TCompletedPolicyObjectId expected_current_completed_policy_object_id;
    completed_policy_object::TCompletedPolicyObjectId pending_completed_policy_object_id;
    std::string domain_ref;
    std::string target_ref;
    std::string reason;
    bool require_existing_current{false};

    [[nodiscard]] bool has_identity() const noexcept
    {
        return !assigner_id.empty() && !host_id.empty() && !pending_completed_policy_object_id.empty();
    }

    [[nodiscard]] bool has_domain_context() const noexcept
    {
        return !domain_ref.empty() && !target_ref.empty();
    }
};
}
