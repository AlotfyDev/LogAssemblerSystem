
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
 *   Defines proposed recovery action kinds. These names describe what a future
 *   governed recovery workflow may consider. They do not perform rollback,
 *   retry, quarantine, reassignment, or target mutation.
 */
enum class TPolicyRecoveryActionKind
{
    none,
    inspect_only,
    defer,
    request_authority_review,
    request_compatibility_recheck,
    request_assignment_suspension,
    request_assignment_revocation,
    request_replacement_review,
    request_rollback_review,
    request_quarantine,
    request_runtime_readiness_recheck,
    request_audit_export,
    request_persistence_snapshot,
    mark_non_recoverable
};

inline const char* to_string(TPolicyRecoveryActionKind kind) noexcept
{
    switch (kind)
    {
    case TPolicyRecoveryActionKind::none: return "none";
    case TPolicyRecoveryActionKind::inspect_only: return "inspect_only";
    case TPolicyRecoveryActionKind::defer: return "defer";
    case TPolicyRecoveryActionKind::request_authority_review: return "request_authority_review";
    case TPolicyRecoveryActionKind::request_compatibility_recheck: return "request_compatibility_recheck";
    case TPolicyRecoveryActionKind::request_assignment_suspension: return "request_assignment_suspension";
    case TPolicyRecoveryActionKind::request_assignment_revocation: return "request_assignment_revocation";
    case TPolicyRecoveryActionKind::request_replacement_review: return "request_replacement_review";
    case TPolicyRecoveryActionKind::request_rollback_review: return "request_rollback_review";
    case TPolicyRecoveryActionKind::request_quarantine: return "request_quarantine";
    case TPolicyRecoveryActionKind::request_runtime_readiness_recheck: return "request_runtime_readiness_recheck";
    case TPolicyRecoveryActionKind::request_audit_export: return "request_audit_export";
    case TPolicyRecoveryActionKind::request_persistence_snapshot: return "request_persistence_snapshot";
    case TPolicyRecoveryActionKind::mark_non_recoverable: return "mark_non_recoverable";
    }
    return "unknown";
}

} // namespace assembler::ecosystem_governance::policy_runtime_failure
