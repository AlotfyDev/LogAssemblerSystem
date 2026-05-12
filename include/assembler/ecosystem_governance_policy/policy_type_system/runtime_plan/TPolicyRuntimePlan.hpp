#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContextId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationRequest.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationTrace.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanStep.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRuntimePlan.hpp

 * Wave: EG-POL-W20_Policy_Runtime_Plan
 * Domain: ecosystem_governance / policy_type_system / runtime_plan
 *
 * Architectural boundary:
 *   W20 implements the Policy Runtime Plan model that follows W18 Realization
 *   Contract Foundation and W19 Runtime Readiness Model. It is derived from
 *   EG-POL-ARCH-007_Realization_Contracts_And_Runtime_Readiness and guarded by
 *   EG-POL-ARCH-008_Compliance_And_Validation_Matrix. A runtime plan is a
 *   pre-execution, non-mutating plan artifact: it may describe ordered steps
 *   a future realizer could consume, but it is not TPolicyRealizer, not
 *   TPolicyExecutor, not target invocation, not runtime mutation, not scheduler
 *   behavior, not material circulation, not communication binding, and not
 *   add-on execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity, family, version, scope, source, issue, and result vocabulary.
 *   - W06 supplies target-kind and realization-binding descriptors while preserving descriptor-only semantics.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12 supplies policy-family and scope foundations.
 *   - W13 supplies target-capability contracts.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict states.
 *   - W16 and W17 supply policy source/publication and registry-versioning views.
 *   - W18 supplies realization contracts, realization contexts, requests, preconditions, failures, and traces.
 *   - W19 supplies runtime admission, readiness gates, readiness issues, readiness reports, and readiness evaluators.
 *
 * Relationship to Phase A architecture:
 *   The architecture states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W20 sits after runtime-ready and before any realizer interface. It can
 *   express a plan for later realization consideration, but that plan remains
 *   descriptive. Passing readiness and creating a plan does not execute policy
 *   behavior and does not prove target mutation, downstream success, or external
 *   side effects.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyRealizer, TPolicyExecutor, runtime
 *   execution engine, target invocation, target mutation, material circulation
 *   behavior, communication binding, add-on execution, source parsing,
 *   persistent registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a compact set of value carriers
 *   and structural helpers.
 * File responsibility:
 *   TPolicyRuntimePlan aggregates the non-executing runtime-plan artifact. It
 *   references the realization contract, realization context, realization
 *   request, runtime readiness report, trace, planned steps, and issues. It is
 *   a plan carrier only: it may be ready for a future realizer to inspect, but
 *   it never invokes targets, mutates state, schedules work, or executes policy.
 */

struct TPolicyRuntimePlan final
{
    TPolicyRuntimePlanId plan_id{};
    TPolicyRuntimePlanStatus status{TPolicyRuntimePlanStatus::draft};
    TPolicyRealizationContractId contract_id{};
    TPolicyRealizationContextId context_id{};
    TPolicyRealizationRequest request{};
    TPolicyRuntimeReadinessReport readiness_report{};
    TPolicyRealizationTrace trace{};
    TPolicyRuntimePlanStepSet step_set{};
    TPolicyRuntimePlanIssueSet issue_set{};
    std::uint64_t authority_evidence_id{0};
    std::string recommendation{};
    std::string note{};

    [[nodiscard]] bool HasIdentity() const noexcept { return plan_id.IsValid(); }
    [[nodiscard]] bool HasContract() const noexcept { return contract_id.IsValid(); }
    [[nodiscard]] bool HasContext() const noexcept { return context_id.IsValid(); }
    [[nodiscard]] bool HasAuthorityEvidence() const noexcept { return authority_evidence_id != 0; }
    [[nodiscard]] bool HasTrace() const noexcept { return trace.trace_ref.IsValid(); }
    [[nodiscard]] bool HasPositiveReadiness() const noexcept { return readiness_report.MayProceedToRealizationPlanning(); }
    [[nodiscard]] bool HasBlockingIssues() const noexcept { return issue_set.HasBlockingIssue(); }

    [[nodiscard]] bool IsStructurallyValid() const noexcept
    {
        return HasIdentity() && HasContract() && HasContext() && request.IsValidRequest();
    }

    [[nodiscard]] bool IsPlanReady() const noexcept
    {
        return ::assembler::ecosystem_governance::policy_type_system::IsPositive(status) &&
               IsStructurallyValid() &&
               HasPositiveReadiness() &&
               step_set.AllRequiredSatisfied() &&
               !HasBlockingIssues();
    }

    [[nodiscard]] bool MayBeSubmittedToFutureRealizer() const noexcept
    {
        return IsPlanReady() && HasAuthorityEvidence() && HasTrace();
    }

    void AddStep(TPolicyRuntimePlanStep step) { step_set.Add(std::move(step)); }

    void AddIssue(TPolicyRuntimePlanIssue issue)
    {
        if (issue.IsForbidden()) status = TPolicyRuntimePlanStatus::forbidden;
        else if (issue.IsBlocking() && !::assembler::ecosystem_governance::policy_type_system::IsBlocking(status)) status = TPolicyRuntimePlanStatus::blocked;
        issue_set.Add(std::move(issue));
    }

    [[nodiscard]] static TPolicyRuntimePlan FromReadiness(TPolicyRuntimePlanId id,
                                                          const TPolicyRuntimeReadinessReport& readiness,
                                                          const TPolicyRealizationRequest& request)
    {
        TPolicyRuntimePlan plan;
        plan.plan_id = id;
        plan.status = readiness.MayProceedToRealizationPlanning()
                        ? TPolicyRuntimePlanStatus::plan_ready
                        : TPolicyRuntimePlanStatus::blocked;
        plan.contract_id = readiness.contract_id;
        plan.context_id = request.context_id;
        plan.request = request;
        plan.readiness_report = readiness;
        plan.trace = readiness.trace;
        plan.authority_evidence_id = request.authority_evidence_id;
        plan.recommendation = readiness.MayProceedToRealizationPlanning()
                            ? "runtime plan may be prepared for future realizer inspection"
                            : "runtime plan blocked by readiness report";
        if (!readiness.MayProceedToRealizationPlanning())
        {
            plan.AddIssue(TPolicyRuntimePlanIssue::Blocking(TPolicyRuntimePlanIssueKind::readiness_not_positive,
                                                            "readiness report does not permit realization planning"));
        }
        return plan;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
