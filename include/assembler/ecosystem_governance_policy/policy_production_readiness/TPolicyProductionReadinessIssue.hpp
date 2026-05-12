#pragma once

#include <string>
#include <utility>
#include "TPolicyProductionReadinessSeverity.hpp"

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines a production readiness issue. An issue is a descriptive
 *   artifact explaining why a gate is clean, warning-bearing, deferred, blocked,
 *   or failed. It is intentionally separate from remediation and execution.
 *
 * Relationship to prior waves:
 *   Issues may reference concerns found by W33 compliance checks, W32 failure
 *   descriptors, W31 audit-export boundary review, W30 persistence-boundary
 *   review, or W18-W24 realization/readiness gates.
 *
 * Full intended picture:
 *   A future readiness gate report may collect issues from many sources and use
 *   their severity to decide production readiness status.
 *
 * Explicit non-responsibilities:
 *   This file does not perform the check that discovered the issue, remediate the
 *   issue, mutate runtime state, or write issue data to a store.
 */
struct TPolicyProductionReadinessIssue
{
    std::string code;
    std::string message;
    std::string subject_ref;
    TPolicyProductionReadinessSeverity severity{TPolicyProductionReadinessSeverity::info};

    TPolicyProductionReadinessIssue() = default;
    TPolicyProductionReadinessIssue(std::string c,
                                    std::string m,
                                    TPolicyProductionReadinessSeverity s)
        : code(std::move(c)), message(std::move(m)), severity(s) {}

    [[nodiscard]] bool blocks_readiness() const noexcept { return is_blocking(severity); }
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
