#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TPolicySafePointSwitchResult.hpp"

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TDomainPolicyAssignerReport.hpp
 *
 * Architectural role:
 *   Defines the domain assigner report, combining status, last switch result, issues, and evidence references.
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

struct TDomainPolicyAssignerReport
{
    TDomainPolicyAssignerId assigner_id;
    TDomainPolicyAssignerStatus status{TDomainPolicyAssignerStatus::unknown};
    TPolicySafePointSwitchResult last_switch_result;
    std::vector<TDomainPolicyAssignerIssue> issues;
    std::vector<std::string> evidence_refs;

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return last_switch_result.has_blocking_issue();
    }

    [[nodiscard]] bool healthy() const noexcept
    {
        return assigner_can_evaluate(status) && !has_blocking_issue();
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
