#pragma once

#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TPolicySafePointSwitchPlan.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TPolicySafePointSwitchRequest.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TPolicySafePointSwitchResult.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSurface.hpp"

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TDomainPolicyAssigner.hpp
 *
 * Architectural role:
 *   Defines the aggregate domain-local assigner. It can plan and apply assignment-port metadata switches only through W38 host surfaces at declared safe points.
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

struct TDomainPolicyAssigner
{
    TDomainPolicyAssignerId assigner_id;
    std::string domain_ref;
    TDomainPolicyAssignerStatus status{TDomainPolicyAssignerStatus::declared};
    TDomainPolicyAssignerReport report;

    [[nodiscard]] TDomainPolicyAssignerView view() const noexcept
    {
        return TDomainPolicyAssignerView{&assigner_id, &domain_ref, status, &report};
    }

    [[nodiscard]] TPolicySafePointSwitchPlan plan_switch(const policy_object_host::TPolicyObjectHostSurface& host,
                                                         TPolicySafePointSwitchRequest request) const
    {
        TPolicySafePointSwitchPlan plan;
        plan.request = std::move(request);
        plan.previous_completed_policy_object_id = host.assignment_port.current_completed_policy_object_id;
        plan.next_completed_policy_object_id = host.assignment_port.pending_completed_policy_object_id;
        plan.safe_point_used = host.assignment_port.safe_point_flag;

        if (!assigner_can_evaluate(status))
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_host_not_ready;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("assigner_not_ready", "domain policy assigner is not ready to evaluate switch"));
            return plan;
        }
        if (assigner_id != plan.request.assigner_id)
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_incompatible_host;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("assigner_id_mismatch", "switch request assigner id does not match assigner"));
            return plan;
        }
        if (host.descriptor.host_id != plan.request.host_id)
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_incompatible_host;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("host_id_mismatch", "switch request host id does not match host surface"));
            return plan;
        }
        if (!domain_ref.empty() && host.descriptor.domain_ref != domain_ref)
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_incompatible_host;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("domain_mismatch", "host domain does not match assigner domain"));
            return plan;
        }
        if (plan.request.require_existing_current && !host.assignment_port.has_current_assignment())
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_no_pending_policy;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("current_assignment_missing", "switch requires an existing current assignment"));
            return plan;
        }
        if (host.assignment_port.pending_completed_policy_object_id.empty())
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_no_pending_policy;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("pending_assignment_missing", "host has no pending completed policy object"));
            return plan;
        }
        if (!plan.request.pending_completed_policy_object_id.empty() &&
            host.assignment_port.pending_completed_policy_object_id != plan.request.pending_completed_policy_object_id)
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_incompatible_host;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("pending_assignment_mismatch", "request pending completed policy object does not match host staged policy object"));
            return plan;
        }
        if (!host.assignment_port.safe_point_flag.declared)
        {
            plan.decision = TPolicySafePointSwitchDecision::rejected_safe_point_closed;
            plan.add_issue(TDomainPolicyAssignerIssue::blocking_issue("safe_point_not_declared", "host has not declared a safe point"));
            return plan;
        }
        if (!host.assignment_port.safe_point_flag.usable())
        {
            plan.decision = TPolicySafePointSwitchDecision::deferred_until_safe_point;
            plan.add_issue(TDomainPolicyAssignerIssue::warning("safe_point_closed", "host safe point is declared but not currently open"));
            return plan;
        }

        plan.decision = TPolicySafePointSwitchDecision::allowed;
        plan.next_completed_policy_object_id = host.assignment_port.pending_completed_policy_object_id;
        return plan;
    }

    TPolicySafePointSwitchResult apply_switch(policy_object_host::TPolicyObjectHostSurface& host,
                                              const TPolicySafePointSwitchPlan& plan)
    {
        TPolicySafePointSwitchResult result;
        result.host_id = host.descriptor.host_id;
        result.decision = plan.decision;
        result.previous_completed_policy_object_id = host.assignment_port.current_completed_policy_object_id;
        result.safe_point_ref = plan.safe_point_used.safe_point_ref;
        result.issues = plan.issues;
        result.evidence_refs = plan.evidence_refs;

        if (!plan.switch_allowed())
        {
            report.assigner_id = assigner_id;
            report.status = TDomainPolicyAssignerStatus::switch_rejected;
            report.last_switch_result = result;
            return result;
        }

        host.assignment_port.current_completed_policy_object_id = plan.next_completed_policy_object_id;
        host.assignment_port.pending_completed_policy_object_id = completed_policy_object::TCompletedPolicyObjectId{};
        result.active_completed_policy_object_id = host.assignment_port.current_completed_policy_object_id;
        result.decision = plan.decision;

        status = TDomainPolicyAssignerStatus::switch_completed;
        report.assigner_id = assigner_id;
        report.status = status;
        report.last_switch_result = result;
        return result;
    }
};
}
