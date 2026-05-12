#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostAdmission.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostSurfaceReport.hpp
 *
 * Architectural role:
 *   Defines a report for host-surface health, admission result, evidence references, and host-surface issues.
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

struct TPolicyObjectHostSurfaceReport
{
    TPolicyObjectHostId host_id;
    TPolicyObjectHostStatus status{TPolicyObjectHostStatus::unknown};
    TPolicyObjectHostAdmission last_admission;
    std::vector<TPolicyObjectHostIssue> issues;
    std::vector<std::string> evidence_refs;

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return last_admission.has_blocking_issue();
    }

    [[nodiscard]] bool healthy() const noexcept
    {
        return host_accepts_assignment(status) && !has_blocking_issue();
    }

    void add_issue(TPolicyObjectHostIssue issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }

    void add_evidence_ref(std::string ref)
    {
        if (!ref.empty()) evidence_refs.push_back(std::move(ref));
    }
};
}
