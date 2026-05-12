#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/policy_realizer/TPolicyRealizerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineConfig.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineResult.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngineView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlan.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationEngine.hpp
 * Wave: EG-POL-W24_PolicyRealizationEngine_Skeleton
 * Domain: ecosystem_governance / policy_type_system / realization_engine
 *
 * Architectural boundary:
 *   W24 introduces the Policy Realization Engine Skeleton after W23 introduced
 *   the guarded Policy Realization Execution Plan. This wave is deliberately
 *   named "engine skeleton" rather than "executor": it may coordinate, inspect,
 *   gate, and report on pre-execution realization artifacts, but it must not
 *   execute policies, invoke targets, mutate target state, schedule runtime
 *   work, perform material circulation, bind communication endpoints, run add-ons,
 *   parse sources, persist registry data, or emit telemetry/logging output.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary.
 *   - W06 supplies descriptor-only realization binding and target-kind language.
 *   - W09 supplies TPolicy as semantic governing aggregate, not executor.
 *   - W10 supplies non-executing assignment basics.
 *   - W12/W13 supply family/scope and target-capability foundations.
 *   - W14 supplies family-target compatibility reports.
 *   - W15 supplies assignment lifecycle and conflict vocabulary.
 *   - W16/W17 supply publication and registry-versioning views.
 *   - W18 supplies realization contracts, contexts, requests, failures, and traces.
 *   - W19 supplies runtime readiness gates and reports.
 *   - W20 supplies non-executing runtime plans.
 *   - W21 supplies the TPolicyRealizer interface and result vocabulary.
 *   - W22 supplies realization session lifecycle scope.
 *   - W23 supplies guarded realization execution-plan artifacts.
 *
 * Relationship to Phase A architecture:
 *   Phase A states: Assigned != Active != Runtime-Ready != Realized != Executed.
 *   W24 can inspect a complete execution plan and can produce an engine result,
 *   but that result is only governance evidence for a later executor/engine wave.
 *   It must not claim target mutation, downstream success, external side effects,
 *   persistence, telemetry, or actual execution.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, a production runtime execution
 *   engine, direct target invocation, target mutation, material circulation
 *   behavior, communication binding, add-on execution, source parsing, persistent
 *   registry storage, telemetry, logging, or database persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation records the complete architectural responsibility while the
 *   implementation remains a compact foundation block for compile-smoke use.
 *
 * File responsibility:
 *   TPolicyRealizationEngine is the non-executing engine skeleton introduced in W24. It coordinates inspection of a W23 execution plan and produces an engine result. It can validate identity, authority evidence, trace, step budget, and plan readiness, but it does not execute steps, invoke targets, schedule work, or mutate anything.
 */
class TPolicyRealizationEngine final
{
public:
    TPolicyRealizationEngineConfig config{};
    TPolicyRealizationEngineStatus status{TPolicyRealizationEngineStatus::unknown};
    TPolicyRealizerId default_realizer_id{};
    std::uint64_t inspected_plan_count{0};
    std::vector<TPolicyRealizationEngineIssue> issues{};
    std::string note{};

    TPolicyRealizationEngine() = default;
    explicit TPolicyRealizationEngine(TPolicyRealizationEngineConfig c) : config(std::move(c))
    {
        status = config.IsUsableForInspection() ? TPolicyRealizationEngineStatus::configured : TPolicyRealizationEngineStatus::blocked;
    }

    [[nodiscard]] bool IsConfigured() const noexcept { return config.IsUsableForInspection() && !policy_type_system::IsBlocking(status); }

    [[nodiscard]] TPolicyRealizationEngineView View() const noexcept
    {
        return TPolicyRealizationEngineView{config.engine_id, status, config.max_plan_steps, inspected_plan_count, config.require_authority_evidence, config.require_trace};
    }

    void AddIssue(TPolicyRealizationEngineIssue issue)
    {
        if (issue.severity == TPolicyRealizationEngineIssueSeverity::forbidden) status = TPolicyRealizationEngineStatus::forbidden;
        else if (issue.IsBlocking() && !policy_type_system::IsBlocking(status)) status = TPolicyRealizationEngineStatus::blocked;
        issues.push_back(std::move(issue));
    }

    [[nodiscard]] bool HasBlockingIssue() const noexcept
    {
        if (policy_type_system::IsBlocking(status)) return true;
        for (const auto& issue : issues) if (issue.IsBlocking()) return true;
        return false;
    }

    [[nodiscard]] bool CanInspectPlan(const TPolicyExecutionPlan& plan) const noexcept
    {
        if (!IsConfigured()) return false;
        if (!plan.IsStructurallyValid()) return false;
        if (!plan.MayBeSubmittedToFutureExecutorInspection()) return false;
        if (config.require_authority_evidence && !plan.HasAuthorityEvidence()) return false;
        if (config.require_trace && !plan.HasTrace()) return false;
        if (!config.allow_forbidden_plans && plan.status == TPolicyExecutionPlanStatus::forbidden) return false;
        if (config.max_plan_steps != 0 && plan.step_set.steps.size() > config.max_plan_steps) return false;
        return true;
    }

    [[nodiscard]] TPolicyRealizationEngineResult InspectPlan(const TPolicyExecutionPlan& plan)
    {
        TPolicyRealizationEngineResult result{};
        result.plan_id = plan.plan_id;
        result.engine_status = status;
        result.trace.trace_ref.value = plan.trace_id;

        if (!config.HasIdentity())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::missing_engine_id, "engine skeleton is missing identity"));
            return result;
        }
        if (!config.HasStepBudget())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::engine_not_configured, "engine skeleton is missing step budget"));
            return result;
        }
        if (!plan.HasIdentity())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::missing_execution_plan, "execution plan is missing identity"));
            return result;
        }
        if (config.max_plan_steps != 0 && plan.step_set.steps.size() > config.max_plan_steps)
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::step_budget_exceeded, "execution plan exceeds engine skeleton step budget"));
            return result;
        }
        if (config.require_authority_evidence && !plan.HasAuthorityEvidence())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::missing_authority_evidence, "execution plan lacks authority evidence"));
            return result;
        }
        if (config.require_trace && !plan.HasTrace())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::missing_trace, "execution plan lacks trace"));
            return result;
        }
        if (plan.status == TPolicyExecutionPlanStatus::forbidden && !config.allow_forbidden_plans)
        {
            result.kind = TPolicyRealizationEngineResultKind::forbidden;
            result.issues.push_back(TPolicyRealizationEngineIssue::Forbidden(TPolicyRealizationEngineIssueKind::forbidden_plan, "execution plan is forbidden"));
            return result;
        }
        if (!plan.MayBeSubmittedToFutureExecutorInspection())
        {
            result.kind = TPolicyRealizationEngineResultKind::blocked;
            result.issues.push_back(TPolicyRealizationEngineIssue::Blocking(TPolicyRealizationEngineIssueKind::execution_plan_not_ready, "execution plan is not ready for engine inspection"));
            return result;
        }

        ++inspected_plan_count;
        status = TPolicyRealizationEngineStatus::accepted_for_future_execution;
        result.kind = TPolicyRealizationEngineResultKind::accepted_for_engine_review;
        result.engine_status = status;
        result.recommendation = "plan accepted by non-executing engine skeleton for future executor review";
        return result;
    }

    [[nodiscard]] static TPolicyRealizationEngine CreateConfigured(TPolicyRealizationEngineId id, std::uint64_t max_steps, std::string label = {})
    {
        TPolicyRealizationEngineConfig cfg{};
        cfg.engine_id = id;
        cfg.max_plan_steps = max_steps;
        cfg.label = std::move(label);
        return TPolicyRealizationEngine{std::move(cfg)};
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
