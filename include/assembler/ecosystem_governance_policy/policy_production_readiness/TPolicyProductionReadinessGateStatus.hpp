#pragma once

#include <string>

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines the lifecycle/status vocabulary of a production
 *   readiness gate. It tells whether the gate is draft, open, evaluating,
 *   passed, conditional, blocked, failed, or closed.
 *
 * Relationship to prior waves:
 *   The status vocabulary consumes the non-executing discipline established by
 *   W18-W24 and the compliance orientation of W33. A gate may acknowledge prior
 *   readiness evidence, but a status value must never become runtime execution.
 *
 * Full intended picture:
 *   A future production readiness authority may aggregate many gates and decide
 *   whether policy-governance implementation can progress toward production.
 *   This enum is the shared status language for that aggregation.
 *
 * Explicit non-responsibilities:
 *   This file does not run validation, run tests, deploy software, perform
 *   rollback, mutate assignments, or call policy targets.
 */
enum class TPolicyProductionReadinessGateStatus
{
    unknown,
    draft,
    open,
    evaluating,
    passed,
    passed_with_warnings,
    conditional_pass,
    deferred,
    blocked,
    failed,
    closed
};

inline const char* to_string(TPolicyProductionReadinessGateStatus status) noexcept
{
    switch (status)
    {
        case TPolicyProductionReadinessGateStatus::draft: return "draft";
        case TPolicyProductionReadinessGateStatus::open: return "open";
        case TPolicyProductionReadinessGateStatus::evaluating: return "evaluating";
        case TPolicyProductionReadinessGateStatus::passed: return "passed";
        case TPolicyProductionReadinessGateStatus::passed_with_warnings: return "passed_with_warnings";
        case TPolicyProductionReadinessGateStatus::conditional_pass: return "conditional_pass";
        case TPolicyProductionReadinessGateStatus::deferred: return "deferred";
        case TPolicyProductionReadinessGateStatus::blocked: return "blocked";
        case TPolicyProductionReadinessGateStatus::failed: return "failed";
        case TPolicyProductionReadinessGateStatus::closed: return "closed";
        default: return "unknown";
    }
}

} // namespace assembler::ecosystem_governance::policy_production_readiness
