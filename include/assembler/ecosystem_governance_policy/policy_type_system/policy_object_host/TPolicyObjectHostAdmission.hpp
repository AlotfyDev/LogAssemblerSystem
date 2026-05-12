#pragma once

#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObject.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostIssue.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostAdmission.hpp
 *
 * Architectural role:
 *   Defines a non-mutating admission result for checking whether a completed policy object can be staged into a specific host surface.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantics as DTOs. W36 lets a target declare capability and semantic-to-target realization mapping. W37 completes a policy object by joining governance semantics with target realization evidence. W38 introduces the target-owned host surface that can later receive a completed policy object for safe-point-aware assignment.
 *
 * Full intended picture:
 *   A functional target composes a TPolicyObjectHost-like surface. The host declares safe-point visibility, admissible completed-policy criteria, current assignment slot metadata, and host evidence. Later W39 Domain PolicyAssigner will use this host surface to switch completed policy objects only at host-declared safe points.
 *
 * Explicit non-responsibilities:
 *   This file does not perform assignment switching, choose a policy, invoke a realizer, mutate target behavior, execute runtime policy logic, persist host state, or export audit records. 
 */

struct TPolicyObjectHostAdmission
{
    TPolicyObjectHostId host_id;
    completed_policy_object::TCompletedPolicyObjectId completed_policy_object_id;
    bool accepted{false};
    std::vector<TPolicyObjectHostIssue> issues;

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return false;
    }

    [[nodiscard]] bool passed() const noexcept
    {
        return accepted && !host_id.empty() && !completed_policy_object_id.empty() && !has_blocking_issue();
    }

    void add_issue(TPolicyObjectHostIssue issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }

    static TPolicyObjectHostAdmission evaluate(const TPolicyObjectHostDescriptor& host,
                                               const completed_policy_object::TCompletedPolicyObject& object)
    {
        TPolicyObjectHostAdmission result;
        result.host_id = host.host_id;
        result.completed_policy_object_id = object.id;

        if (!host.can_admit_for_later_assignment())
        {
            result.add_issue(TPolicyObjectHostIssue::blocking_issue("host_not_admissible", "host descriptor is incomplete or not accepting assignment"));
            return result;
        }
        if (!object.ready_for_host_assignment())
        {
            result.add_issue(TPolicyObjectHostIssue::blocking_issue("completed_policy_not_ready", "completed policy object is not ready for host assignment"));
            return result;
        }
        if (object.domain_ref != host.domain_ref)
        {
            result.add_issue(TPolicyObjectHostIssue::blocking_issue("domain_mismatch", "completed policy object domain does not match host domain"));
            return result;
        }
        if (object.target_kind_ref != host.target_kind_ref)
        {
            result.add_issue(TPolicyObjectHostIssue::blocking_issue("target_kind_mismatch", "completed policy object target kind does not match host target kind"));
            return result;
        }

        bool family_allowed = false;
        for (const auto& family : host.accepted_policy_families)
            if (family == object.policy_family_ref) { family_allowed = true; break; }
        if (!family_allowed)
        {
            result.add_issue(TPolicyObjectHostIssue::blocking_issue("policy_family_not_accepted", "host does not accept this policy family"));
            return result;
        }

        result.accepted = true;
        return result;
    }
};
}
