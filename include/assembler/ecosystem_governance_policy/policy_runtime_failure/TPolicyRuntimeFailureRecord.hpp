
#pragma once

#include "assembler/ecosystem_governance/policy_runtime_failure/TPolicyRuntimeFailureKind.hpp"
#include "assembler/ecosystem_governance/policy_runtime_failure/TPolicyRuntimeFailureSeverity.hpp"
#include <string>
#include <utility>

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
 *   Carries one runtime failure observation. It is intentionally reference-based
 *   and string-based at this foundation stage so that it can be attached to
 *   readiness reports, sessions, execution plans, engine skeletons, persistence
 *   boundaries, and audit export boundaries without depending on concrete
 *   runtime systems.
 */
struct TPolicyRuntimeFailureRecord final
{
    std::string failure_id{};
    TPolicyRuntimeFailureKind kind{TPolicyRuntimeFailureKind::unknown};
    TPolicyRuntimeFailureSeverity severity{TPolicyRuntimeFailureSeverity::warning};
    std::string policy_ref{};
    std::string assignment_ref{};
    std::string target_ref{};
    std::string session_ref{};
    std::string plan_ref{};
    std::string engine_ref{};
    std::string reason{};
    std::string trace_ref{};

    [[nodiscard]] bool valid() const noexcept
    {
        return !failure_id.empty() && kind != TPolicyRuntimeFailureKind::none;
    }

    [[nodiscard]] bool blocks_progression() const noexcept
    {
        return blocks_recovery_progression(severity) || kind == TPolicyRuntimeFailureKind::direct_target_invocation_attempted;
    }

    static TPolicyRuntimeFailureRecord make(std::string id,
                                            TPolicyRuntimeFailureKind failure_kind,
                                            TPolicyRuntimeFailureSeverity failure_severity,
                                            std::string why = {})
    {
        TPolicyRuntimeFailureRecord record{};
        record.failure_id = std::move(id);
        record.kind = failure_kind;
        record.severity = failure_severity;
        record.reason = std::move(why);
        return record;
    }
};

} // namespace assembler::ecosystem_governance::policy_runtime_failure
