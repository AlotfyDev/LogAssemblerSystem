
#pragma once

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
 *   Describes the lifecycle of a recovery plan as an artifact. It is not the
 *   lifecycle of an executed recovery action.
 */
enum class TPolicyRecoveryPlanStatus
{
    draft,
    proposed,
    authority_required,
    ready_for_review,
    approved_for_consideration,
    rejected,
    deferred,
    blocked,
    non_recoverable
};

inline const char* to_string(TPolicyRecoveryPlanStatus status) noexcept
{
    switch (status)
    {
    case TPolicyRecoveryPlanStatus::draft: return "draft";
    case TPolicyRecoveryPlanStatus::proposed: return "proposed";
    case TPolicyRecoveryPlanStatus::authority_required: return "authority_required";
    case TPolicyRecoveryPlanStatus::ready_for_review: return "ready_for_review";
    case TPolicyRecoveryPlanStatus::approved_for_consideration: return "approved_for_consideration";
    case TPolicyRecoveryPlanStatus::rejected: return "rejected";
    case TPolicyRecoveryPlanStatus::deferred: return "deferred";
    case TPolicyRecoveryPlanStatus::blocked: return "blocked";
    case TPolicyRecoveryPlanStatus::non_recoverable: return "non_recoverable";
    }
    return "unknown";
}

} // namespace assembler::ecosystem_governance::policy_runtime_failure
