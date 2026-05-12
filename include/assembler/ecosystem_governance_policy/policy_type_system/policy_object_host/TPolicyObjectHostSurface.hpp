#pragma once

#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObject.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostAdmission.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostAssignmentPort.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSurfaceReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostView.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostSurface.hpp
 *
 * Architectural role:
 *   Defines the aggregate target-owned host surface that joins descriptor, assignment-port metadata, and reporting while remaining non-executing and non-mutating with respect to target behavior.
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

struct TPolicyObjectHostSurface
{
    TPolicyObjectHostDescriptor descriptor;
    TPolicyObjectHostAssignmentPort assignment_port;
    TPolicyObjectHostSurfaceReport report;

    [[nodiscard]] TPolicyObjectHostView view() const noexcept
    {
        return TPolicyObjectHostView{&descriptor, &assignment_port};
    }

    [[nodiscard]] TPolicyObjectHostAdmission admit(const completed_policy_object::TCompletedPolicyObject& object)
    {
        auto admission = TPolicyObjectHostAdmission::evaluate(descriptor, object);
        report.host_id = descriptor.host_id;
        report.status = descriptor.status;
        report.last_admission = admission;
        return admission;
    }

    void update_safe_point(TPolicyObjectHostSafePointFlag flag)
    {
        descriptor.safe_point_flag = flag;
        assignment_port.safe_point_flag = std::move(flag);
    }

    void stage_if_admitted(const TPolicyObjectHostAdmission& admission)
    {
        if (admission.passed())
        {
            assignment_port.host_id = descriptor.host_id;
            assignment_port.stage(admission.completed_policy_object_id);
        }
    }
};
}
