#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObjectIssue.hpp
 *
 * Architectural role:
 *   Defines lightweight diagnostic issue records for completion failures or readiness blockers.
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

struct TCompletedPolicyObjectIssue
{
    std::string code;
    std::string message;
    bool blocking{false};

    [[nodiscard]] bool empty() const noexcept { return code.empty() && message.empty(); }

    static TCompletedPolicyObjectIssue blocking_issue(std::string code, std::string message)
    {
        TCompletedPolicyObjectIssue issue;
        issue.code = std::move(code);
        issue.message = std::move(message);
        issue.blocking = true;
        return issue;
    }
};
}
