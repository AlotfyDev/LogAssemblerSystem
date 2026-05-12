#pragma once

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines severity levels for production readiness issues.
 *   Severity expresses the strength of a readiness concern without executing a
 *   test runner, deployment process, policy realizer, or target operation.
 *
 * Relationship to prior waves:
 *   W33 established compliance severity vocabulary. W34 narrows that concern to
 *   production gate review and ensures blocking or forbidden issues remain
 *   visible before any production use is considered.
 *
 * Full intended picture:
 *   Future readiness gates can aggregate multiple issues and compute whether a
 *   gate should pass, pass conditionally, defer, block, or fail.
 *
 * Explicit non-responsibilities:
 *   This enum does not decide remediation, execute rollback, enforce policy,
 *   persist state, or emit telemetry.
 */
enum class TPolicyProductionReadinessSeverity
{
    info,
    notice,
    warning,
    blocking,
    critical,
    forbidden
};

inline bool is_blocking(TPolicyProductionReadinessSeverity severity) noexcept
{
    return severity == TPolicyProductionReadinessSeverity::blocking ||
           severity == TPolicyProductionReadinessSeverity::critical ||
           severity == TPolicyProductionReadinessSeverity::forbidden;
}

} // namespace assembler::ecosystem_governance::policy_production_readiness
