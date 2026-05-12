#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include "TPolicyProductionReadinessGateStatus.hpp"
#include "TPolicyProductionReadinessIssue.hpp"
#include "TPolicyProductionReadinessEvidenceRef.hpp"

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines the production readiness report. A report aggregates
 *   gate status, issues, evidence references, and review notes into a single
 *   descriptive artifact.
 *
 * Relationship to prior waves:
 *   W33 compliance reports, W32 failure/recovery reports, W31 audit-export
 *   boundary reports, and W30 persistence boundary reports may all feed into a
 *   W34 production readiness report.
 *
 * Full intended picture:
 *   Future production review tooling may use this report to block or approve
 *   progression toward a production integration milestone. This header provides
 *   a portable carrier, not the approval system itself.
 *
 * Explicit non-responsibilities:
 *   This file does not execute gates, run tests, write files, persist state,
 *   mutate targets, invoke realizers, or deploy anything.
 */
struct TPolicyProductionReadinessReport
{
    TPolicyProductionReadinessGateStatus status{TPolicyProductionReadinessGateStatus::unknown};
    std::vector<TPolicyProductionReadinessIssue> issues;
    std::vector<TPolicyProductionReadinessEvidenceRef> evidence;
    std::vector<std::string> notes;

    [[nodiscard]] std::size_t issue_count() const noexcept { return issues.size(); }
    [[nodiscard]] bool has_blockers() const noexcept
    {
        for (const auto& issue : issues)
        {
            if (issue.blocks_readiness()) { return true; }
        }
        return false;
    }

    void add_issue(const TPolicyProductionReadinessIssue& issue)
    {
        issues.push_back(issue);
        if (issue.blocks_readiness()) { status = TPolicyProductionReadinessGateStatus::blocked; }
    }
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
