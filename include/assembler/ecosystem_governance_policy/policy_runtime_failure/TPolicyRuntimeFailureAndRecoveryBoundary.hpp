
#pragma once

#include "assembler/ecosystem_governance/policy_runtime_failure/TPolicyRecoveryReport.hpp"
#include <string>
#include <utility>
#include <vector>

namespace assembler::ecosystem_governance::policy_runtime_failure
{
/*
 * Wave: EG-POL-W32_Policy_Runtime_Failure_And_Recovery
 * Domain: ecosystem_governance / policy_runtime_failure
 *
 * Architectural boundary:
 *   W32 continues Phase F — Production Hardening by defining the runtime failure
 *   and recovery vocabulary for policy realization. The wave describes how a
 *   policy realization, readiness, session, runtime plan, execution plan, engine
 *   skeleton, or ecosystem target integration may report failure and propose
 *   recovery without directly repairing, rolling back, retrying, quarantining,
 *   mutating targets, or executing runtime behavior.
 *
 *   This wave is explicitly non-executing and non-recovering. It does not invoke
 *   targets, execute a policy, perform rollback, modify assignments, reopen
 *   sessions, retry add-ons, write persistent state, emit telemetry, or alter
 *   material circulation / communication context behavior. It only defines
 *   C++17 value types and descriptors for failure classification, recovery plan
 *   description, quarantine status, and recovery review reports.
 *
 * Relationship to prior waves:
 *   - W01-W11 define policy object identity, clauses, replacement, lifecycle,
 *     observation, realization binding, graph structure, TPolicy, assignment,
 *     and registry basics.
 *   - W12-W17 add family/scope, target capabilities, compatibility, assignment
 *     lifecycle, source/publication, and registry versioning views.
 *   - W18-W24 add realization contracts, runtime readiness, runtime plan,
 *     realizer-facing interfaces, realization sessions, execution plans, and
 *     realization engine skeletons while avoiding target invocation.
 *   - W25-W29 define ecosystem target surfaces and system-wide integration
 *     skeletons.
 *   - W30-W31 define persistence and audit export boundaries as descriptions,
 *     not storage or exporters.
 *
 * Relationship to Phase A architecture:
 *   Phase A requires failures, recovery, replacement, rollback, authority,
 *   compatibility, registry, observation, and runtime readiness to remain
 *   traceable and non-collapsed. W32 preserves those separations by making
 *   runtime failure and recovery a governed descriptive layer, not a runtime
 *   repair engine.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyExecutor, production runtime execution,
 *   target invocation, target mutation, material circulation behavior,
 *   communication binding, add-on execution, persistence, telemetry export,
 *   logging, source parsing, registry storage, or automatic recovery.
 *
 * Current implementation posture:
 *   The code is a conservative header-only C++17 foundation. The opening
 *   documentation records the full architectural intention while the code remains
 *   compact enough for compile-smoke validation.
 */

/*
 * File responsibility:
 *   Facade for runtime failure and recovery boundary review. It groups failure
 *   records, proposed recovery plans, quarantine status, and report creation.
 *   It does not recover anything.
 */
struct TPolicyRuntimeFailureAndRecoveryBoundary final
{
    std::string boundary_id{};
    std::string boundary_name{};
    bool requires_authority_for_recovery{true};
    bool allows_automatic_recovery{false};
    std::vector<TPolicyRuntimeFailureRecord> failures{};
    std::vector<TPolicyRecoveryPlan> plans{};

    [[nodiscard]] bool valid() const noexcept
    {
        return !boundary_id.empty();
    }

    [[nodiscard]] bool automation_forbidden() const noexcept
    {
        return !allows_automatic_recovery;
    }

    void record_failure(TPolicyRuntimeFailureRecord failure)
    {
        failures.push_back(std::move(failure));
    }

    void propose_plan(TPolicyRecoveryPlan plan)
    {
        plans.push_back(std::move(plan));
    }

    TPolicyRecoveryReport review_last_plan(std::string report_id = {}) const
    {
        if (plans.empty())
        {
            TPolicyRecoveryPlan empty{};
            empty.status = TPolicyRecoveryPlanStatus::deferred;
            TPolicyRecoveryReport report = TPolicyRecoveryReport::from_plan(std::move(report_id), std::move(empty));
            report.issues.push_back("no_recovery_plan_available");
            return report;
        }
        TPolicyRecoveryReport report = TPolicyRecoveryReport::from_plan(std::move(report_id), plans.back());
        if (!valid())
        {
            report.issues.push_back("invalid_runtime_failure_recovery_boundary");
            report.accepted_for_review = false;
        }
        if (requires_authority_for_recovery && plans.back().authority_ref.empty())
        {
            report.issues.push_back("recovery_authority_missing");
        }
        if (automation_forbidden())
        {
            report.recommendations.push_back("manual_governance_review_required");
        }
        return report;
    }
};

} // namespace assembler::ecosystem_governance::policy_runtime_failure
