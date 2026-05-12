#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostIssue.hpp
 *
 * Architectural role:
 *   Defines diagnostic issues for host-surface admission, host visibility, or safe-point readiness failures.
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

struct TPolicyObjectHostIssue
{
    std::string code;
    std::string message;
    bool blocking{false};

    [[nodiscard]] bool empty() const noexcept { return code.empty() && message.empty(); }

    static TPolicyObjectHostIssue blocking_issue(std::string code, std::string message)
    {
        TPolicyObjectHostIssue issue;
        issue.code = std::move(code);
        issue.message = std::move(message);
        issue.blocking = true;
        return issue;
    }
};
}
