
#pragma once

#include <string>

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
 *   Defines stable failure categories for runtime-readiness, realization,
 *   session, plan, engine, persistence-boundary, audit-export-boundary, and
 *   ecosystem-target failure reporting. These categories are classification
 *   terms only and do not imply automatic repair.
 */
enum class TPolicyRuntimeFailureKind
{
    none,
    unknown,
    policy_invalid,
    assignment_not_active,
    compatibility_failed,
    target_kind_unknown,
    target_capability_missing,
    authority_missing,
    conflict_blocking,
    publication_invalid,
    registry_inconsistent,
    realization_contract_missing,
    runtime_readiness_failed,
    runtime_plan_invalid,
    realization_session_failed,
    execution_plan_blocked,
    realization_engine_failed,
    persistence_boundary_failed,
    audit_export_boundary_failed,
    ecosystem_target_incompatible,
    recovery_forbidden,
    direct_target_invocation_attempted
};

inline const char* to_string(TPolicyRuntimeFailureKind kind) noexcept
{
    switch (kind)
    {
    case TPolicyRuntimeFailureKind::none: return "none";
    case TPolicyRuntimeFailureKind::unknown: return "unknown";
    case TPolicyRuntimeFailureKind::policy_invalid: return "policy_invalid";
    case TPolicyRuntimeFailureKind::assignment_not_active: return "assignment_not_active";
    case TPolicyRuntimeFailureKind::compatibility_failed: return "compatibility_failed";
    case TPolicyRuntimeFailureKind::target_kind_unknown: return "target_kind_unknown";
    case TPolicyRuntimeFailureKind::target_capability_missing: return "target_capability_missing";
    case TPolicyRuntimeFailureKind::authority_missing: return "authority_missing";
    case TPolicyRuntimeFailureKind::conflict_blocking: return "conflict_blocking";
    case TPolicyRuntimeFailureKind::publication_invalid: return "publication_invalid";
    case TPolicyRuntimeFailureKind::registry_inconsistent: return "registry_inconsistent";
    case TPolicyRuntimeFailureKind::realization_contract_missing: return "realization_contract_missing";
    case TPolicyRuntimeFailureKind::runtime_readiness_failed: return "runtime_readiness_failed";
    case TPolicyRuntimeFailureKind::runtime_plan_invalid: return "runtime_plan_invalid";
    case TPolicyRuntimeFailureKind::realization_session_failed: return "realization_session_failed";
    case TPolicyRuntimeFailureKind::execution_plan_blocked: return "execution_plan_blocked";
    case TPolicyRuntimeFailureKind::realization_engine_failed: return "realization_engine_failed";
    case TPolicyRuntimeFailureKind::persistence_boundary_failed: return "persistence_boundary_failed";
    case TPolicyRuntimeFailureKind::audit_export_boundary_failed: return "audit_export_boundary_failed";
    case TPolicyRuntimeFailureKind::ecosystem_target_incompatible: return "ecosystem_target_incompatible";
    case TPolicyRuntimeFailureKind::recovery_forbidden: return "recovery_forbidden";
    case TPolicyRuntimeFailureKind::direct_target_invocation_attempted: return "direct_target_invocation_attempted";
    }
    return "unknown";
}

} // namespace assembler::ecosystem_governance::policy_runtime_failure
