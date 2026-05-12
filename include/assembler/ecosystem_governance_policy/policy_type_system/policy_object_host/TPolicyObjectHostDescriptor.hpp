#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSafePointFlag.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostDescriptor.hpp
 *
 * Architectural role:
 *   Defines the host surface descriptor: domain, target, target kind, accepted families, safe-point state, and evidence expectations.
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

struct TPolicyObjectHostDescriptor
{
    TPolicyObjectHostId host_id;
    std::string domain_ref;
    std::string target_ref;
    std::string target_kind_ref;
    std::string host_surface_kind;
    TPolicyObjectHostStatus status{TPolicyObjectHostStatus::unknown};
    TPolicyObjectHostSafePointFlag safe_point_flag;
    std::vector<std::string> accepted_policy_families;
    std::vector<std::string> required_completed_policy_evidence;

    [[nodiscard]] bool has_identity() const noexcept
    {
        return !host_id.empty() && !domain_ref.empty() && !target_ref.empty() && !target_kind_ref.empty();
    }

    [[nodiscard]] bool has_acceptance_profile() const noexcept
    {
        return !accepted_policy_families.empty();
    }

    [[nodiscard]] bool can_admit_for_later_assignment() const noexcept
    {
        return has_identity() && has_acceptance_profile() && host_accepts_assignment(status);
    }
};
}
