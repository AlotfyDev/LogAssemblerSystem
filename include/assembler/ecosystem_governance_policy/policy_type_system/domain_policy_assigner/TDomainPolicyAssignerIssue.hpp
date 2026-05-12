#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TDomainPolicyAssignerIssue.hpp
 *
 * Architectural role:
 *   Defines issue diagnostics emitted by the domain policy assigner when switch planning or application fails.
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

struct TDomainPolicyAssignerIssue
{
    std::string code;
    std::string message;
    bool blocking{false};

    [[nodiscard]] bool empty() const noexcept { return code.empty() && message.empty(); }

    static TDomainPolicyAssignerIssue blocking_issue(std::string code, std::string message)
    {
        TDomainPolicyAssignerIssue issue;
        issue.code = std::move(code);
        issue.message = std::move(message);
        issue.blocking = true;
        return issue;
    }

    static TDomainPolicyAssignerIssue warning(std::string code, std::string message)
    {
        TDomainPolicyAssignerIssue issue;
        issue.code = std::move(code);
        issue.message = std::move(message);
        issue.blocking = false;
        return issue;
    }
};
}
