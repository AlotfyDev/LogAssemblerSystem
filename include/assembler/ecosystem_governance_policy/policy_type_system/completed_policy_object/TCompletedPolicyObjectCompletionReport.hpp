#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObjectCompletionReport.hpp
 *
 * Architectural role:
 *   Defines a report for the completion process, including missing semantic parts, missing target mappings, and blocking issues.
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

struct TCompletedPolicyObjectCompletionReport
{
    TCompletedPolicyObjectId completed_policy_object_id;
    TCompletedPolicyObjectStatus status{TCompletedPolicyObjectStatus::unknown};
    std::vector<std::string> missing_semantic_parts;
    std::vector<std::string> missing_target_mappings;
    std::vector<TCompletedPolicyObjectIssue> issues;

    [[nodiscard]] bool passed() const noexcept
    {
        return is_completed_status(status) && missing_semantic_parts.empty() &&
               missing_target_mappings.empty() && !has_blocking_issue();
    }

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return false;
    }

    void add_missing_semantic_part(std::string part)
    {
        if (!part.empty()) missing_semantic_parts.push_back(std::move(part));
    }

    void add_missing_target_mapping(std::string mapping)
    {
        if (!mapping.empty()) missing_target_mappings.push_back(std::move(mapping));
    }

    void add_issue(TCompletedPolicyObjectIssue issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }
};
}
