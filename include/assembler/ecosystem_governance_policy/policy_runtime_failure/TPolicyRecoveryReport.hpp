
#pragma once

#include "assembler/ecosystem_governance/policy_runtime_failure/TPolicyRecoveryPlan.hpp"
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
 *   Provides a review report for a proposed recovery plan. It records findings
 *   and recommendations without executing any recommendation.
 */
struct TPolicyRecoveryReport final
{
    std::string report_id{};
    TPolicyRecoveryPlan plan{};
    std::vector<std::string> issues{};
    std::vector<std::string> recommendations{};
    bool accepted_for_review{false};

    [[nodiscard]] bool valid() const noexcept
    {
        return !report_id.empty() && plan.valid();
    }

    [[nodiscard]] bool blocks_progression() const noexcept
    {
        return !accepted_for_review || plan.has_blocking_failure() || plan.quarantine.blocks_runtime_progression();
    }

    static TPolicyRecoveryReport from_plan(std::string id, TPolicyRecoveryPlan recovery_plan)
    {
        TPolicyRecoveryReport report{};
        report.report_id = std::move(id);
        report.plan = std::move(recovery_plan);
        report.accepted_for_review = report.plan.can_be_reviewed();
        if (!report.plan.valid())
        {
            report.issues.push_back("invalid_recovery_plan");
        }
        if (report.plan.has_blocking_failure())
        {
            report.issues.push_back("blocking_failure_present");
        }
        if (report.plan.quarantine.blocks_runtime_progression())
        {
            report.issues.push_back("subject_is_quarantined");
        }
        return report;
    }
};

} // namespace assembler::ecosystem_governance::policy_runtime_failure
