#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TPolicySafePointSwitchDecision.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostId.hpp"

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TPolicySafePointSwitchResult.hpp
 *
 * Architectural role:
 *   Defines the switch result carrier after applying metadata changes to a host assignment port; it does not imply runtime target mutation.
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

struct TPolicySafePointSwitchResult
{
    policy_object_host::TPolicyObjectHostId host_id;
    TPolicySafePointSwitchDecision decision{TPolicySafePointSwitchDecision::unknown};
    completed_policy_object::TCompletedPolicyObjectId previous_completed_policy_object_id;
    completed_policy_object::TCompletedPolicyObjectId active_completed_policy_object_id;
    std::string safe_point_ref;
    std::vector<TDomainPolicyAssignerIssue> issues;
    std::vector<std::string> evidence_refs;

    [[nodiscard]] bool applied() const noexcept
    {
        return decision_allows_switch(decision) && !active_completed_policy_object_id.empty();
    }

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return false;
    }

    void add_issue(TDomainPolicyAssignerIssue issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }

    void add_evidence_ref(std::string ref)
    {
        if (!ref.empty()) evidence_refs.push_back(std::move(ref));
    }
};
}
