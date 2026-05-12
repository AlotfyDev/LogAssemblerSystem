#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlan.hpp"
#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSession.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSessionId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionGuard.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlanId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlanStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlanView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionStep.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyExecutionPlan.hpp
 * Wave: EG-POL-W23_PolicyRealizationExecutionPlan
 * Domain: ecosystem_governance / policy_type_system / realization_execution_plan
 *
 * Architectural boundary:
 *   W23 introduces the Policy Realization Execution Plan model after W22
 *   introduced PolicyRealizationSession. The execution plan is still a
 *   governed pre-execution artifact: it may decompose a realization session,
 *   runtime plan, readiness evidence, and realizer identity into guarded
 *   execution-intent steps for later inspection by a future executor/engine.
 *   It is not the executor, not target invocation, not target mutation, not a
 *   scheduler, not material circulation behavior, not communication binding,
 *   and not add-on execution.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary.
 *   - W06 supplies descriptor-only realization binding and target-kind language.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12/W13 supply family/scope and target capability foundations.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16/W17 supply source/publication and registry-versioning views.
 *   - W18 supplies realization contract/context/request/failure/trace carriers.
 *   - W19 supplies runtime readiness gates and reports.
 *   - W20 supplies non-executing runtime plans.
 *   - W21 supplies the TPolicyRealizer interface and result vocabulary.
 *   - W22 supplies realization session lifecycle scope.
 *
 * Relationship to Phase A architecture:
 *   Phase A states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W23 adds one more pre-execution planning layer. An execution plan may be
 *   complete and guard-satisfied, but that means only that a future executor
 *   may inspect it. It must not claim execution, target mutation, downstream
 *   success, or external side effects.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, a runtime execution engine,
 *   direct target invocation, target mutation, material circulation behavior,
 *   communication binding, add-on execution, source parsing, persistent
 *   registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete architectural responsibility while the
 *   implementation remains a compact foundation block for compile-smoke use.
 *
 * File responsibility:
 *   TPolicyExecutionPlan aggregates a guarded, ordered, non-executing realization execution plan. It binds a W22 session, a W20 runtime plan, realizer identity, guards, steps, issues, authority evidence, and trace into an inspectable plan artifact for a future executor. It never executes policy behavior and never invokes targets.
 */
struct TPolicyExecutionPlan final
{
    TPolicyExecutionPlanId plan_id{};
    TPolicyExecutionPlanStatus status{TPolicyExecutionPlanStatus::draft};
    TPolicyRealizationSessionId session_id{};
    TPolicyRuntimePlanId runtime_plan_id{};
    TPolicyRealizerId realizer_id{};
    std::uint64_t realization_request_id{0};
    std::uint64_t readiness_report_id{0};
    std::uint64_t authority_evidence_id{0};
    std::uint64_t trace_id{0};
    TPolicyExecutionGuardSet guard_set{};
    TPolicyExecutionStepSet step_set{};
    std::vector<TPolicyExecutionIssue> issues{};
    std::string note{};

    [[nodiscard]] bool HasIdentity() const noexcept { return plan_id.IsValid(); }
    [[nodiscard]] bool HasSession() const noexcept { return session_id.IsValid(); }
    [[nodiscard]] bool HasRuntimePlan() const noexcept { return runtime_plan_id.IsValid(); }
    [[nodiscard]] bool HasRealizer() const noexcept { return realizer_id.IsValid(); }
    [[nodiscard]] bool HasAuthorityEvidence() const noexcept { return authority_evidence_id != 0; }
    [[nodiscard]] bool HasTrace() const noexcept { return trace_id != 0; }

    [[nodiscard]] bool IsStructurallyValid() const noexcept
    {
        return HasIdentity() && HasSession() && HasRuntimePlan() && realization_request_id != 0 && readiness_report_id != 0;
    }

    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        if (policy_type_system::IsBlocking(status)) return true;
        for (const auto& issue : issues) if (issue.IsBlocking()) return true;
        return false;
    }

    [[nodiscard]] bool GuardsSatisfied() const noexcept { return guard_set.AllRequiredSatisfied() && step_set.AllRequiredSatisfied(); }

    [[nodiscard]] bool MayBeSubmittedToFutureExecutorInspection() const noexcept
    {
        return IsStructurallyValid() &&
               HasRealizer() &&
               HasAuthorityEvidence() &&
               HasTrace() &&
               GuardsSatisfied() &&
               !HasBlockingIssue() &&
               policy_type_system::IsPositive(status);
    }

    void AddGuard(TPolicyExecutionGuard guard) { guard_set.Add(std::move(guard)); }
    void AddStep(TPolicyExecutionStep step) { step_set.Add(std::move(step)); }

    void AddIssue(TPolicyExecutionIssue issue)
    {
        if (issue.severity == TPolicyExecutionIssueSeverity::forbidden) status = TPolicyExecutionPlanStatus::forbidden;
        else if (issue.IsBlocking() && !policy_type_system::IsBlocking(status)) status = TPolicyExecutionPlanStatus::blocked;
        issues.push_back(std::move(issue));
    }

    [[nodiscard]] TPolicyExecutionPlanView View() const noexcept
    {
        return TPolicyExecutionPlanView{plan_id, status, session_id, runtime_plan_id, realizer_id, trace_id, static_cast<std::uint64_t>(step_set.steps.size())};
    }

    [[nodiscard]] TPolicyExecutionReport ValidateForFutureExecutorInspection() const
    {
        TPolicyExecutionReport report{};
        report.plan_id = plan_id;
        report.status = status;
        report.issues = issues;
        report.recommendation = MayBeSubmittedToFutureExecutorInspection()
            ? "execution plan may be inspected by a future executor"
            : "execution plan is not ready for future executor inspection";
        if (!IsStructurallyValid())
        {
            report.status = TPolicyExecutionPlanStatus::blocked;
            report.issues.push_back(TPolicyExecutionIssue::Blocking(TPolicyExecutionIssueKind::missing_plan_id, "execution plan is missing required identity/session/runtime-plan/request/readiness evidence"));
        }
        return report;
    }

    [[nodiscard]] static TPolicyExecutionPlan FromSessionAndRuntimePlan(TPolicyExecutionPlanId id,
                                                                        const TPolicyRealizationSession& session,
                                                                        const TPolicyRuntimePlan& runtime_plan)
    {
        TPolicyExecutionPlan plan{};
        plan.plan_id = id;
        plan.status = session.IsOpen() && runtime_plan.MayBeSubmittedToFutureRealizer()
                        ? TPolicyExecutionPlanStatus::planned
                        : TPolicyExecutionPlanStatus::blocked;
        plan.session_id = session.id;
        plan.runtime_plan_id = runtime_plan.plan_id;
        plan.realizer_id = session.realizer_id;
        plan.realization_request_id = session.realization_request_id;
        plan.readiness_report_id = session.readiness_report_id;
        plan.authority_evidence_id = session.authority_evidence_id;
        plan.trace_id = session.trace_id;
        plan.note = "created from realization session and runtime plan; non-executing";
        plan.AddGuard(TPolicyExecutionGuard{TPolicyExecutionGuardKind::session_guard, true, session.IsOpen(), "session must be open"});
        plan.AddGuard(TPolicyExecutionGuard{TPolicyExecutionGuardKind::runtime_plan_guard, true, runtime_plan.MayBeSubmittedToFutureRealizer(), "runtime plan must be ready for realizer inspection"});
        plan.AddGuard(TPolicyExecutionGuard{TPolicyExecutionGuardKind::no_direct_target_invocation_guard, true, true, "direct target invocation is forbidden"});
        if (!session.IsOpen()) plan.AddIssue(TPolicyExecutionIssue::Blocking(TPolicyExecutionIssueKind::missing_session, "session is not open"));
        if (!runtime_plan.MayBeSubmittedToFutureRealizer()) plan.AddIssue(TPolicyExecutionIssue::Blocking(TPolicyExecutionIssueKind::missing_runtime_plan, "runtime plan is not ready"));
        return plan;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
