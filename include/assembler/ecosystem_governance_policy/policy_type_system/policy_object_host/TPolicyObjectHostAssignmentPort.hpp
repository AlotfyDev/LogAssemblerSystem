#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSafePointFlag.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostAssignmentPort.hpp
 *
 * Architectural role:
 *   Defines the host assignment port metadata, including current and pending completed-policy-object IDs and safe-point readiness. It stages only; it does not switch.
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

struct TPolicyObjectHostAssignmentPort
{
    TPolicyObjectHostId host_id;
    completed_policy_object::TCompletedPolicyObjectId current_completed_policy_object_id;
    completed_policy_object::TCompletedPolicyObjectId pending_completed_policy_object_id;
    TPolicyObjectHostSafePointFlag safe_point_flag;
    std::string assignment_slot_ref;

    [[nodiscard]] bool has_current_assignment() const noexcept { return !current_completed_policy_object_id.empty(); }
    [[nodiscard]] bool has_pending_assignment() const noexcept { return !pending_completed_policy_object_id.empty(); }
    [[nodiscard]] bool can_switch_now() const noexcept { return has_pending_assignment() && safe_point_flag.usable(); }

    void stage(completed_policy_object::TCompletedPolicyObjectId id)
    {
        if (!id.empty()) pending_completed_policy_object_id = std::move(id);
    }
};
}
