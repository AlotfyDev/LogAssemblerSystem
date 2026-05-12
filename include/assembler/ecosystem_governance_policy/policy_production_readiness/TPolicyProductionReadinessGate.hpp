#pragma once

#include <string>
#include <vector>
#include <utility>
#include <cstddef>
#include "TPolicyProductionReadinessGateId.hpp"
#include "TPolicyProductionReadinessGateStatus.hpp"
#include "TPolicyProductionReadinessCriterion.hpp"
#include "TPolicyProductionReadinessReport.hpp"

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines the production readiness gate aggregate. It groups a
 *   named gate id, criteria, report, covered waves, and deferred decisions into
 *   the final non-executing gate that closes the EG-POL wave sequence.
 *
 * Relationship to prior waves:
 *   This is the production-hardening gate over W01-W33. It must preserve all
 *   prior boundaries: policy objects do not own targets, compatibility is not
 *   assignment, assignment is not realization, readiness is not execution,
 *   persistence/audit boundaries do not implement storage/export, and compliance
 *   reports do not execute behavior.
 *
 * Full intended picture:
 *   Future production workflows may instantiate a gate, attach criteria, attach
 *   evidence, review blockers, and decide whether a production milestone can
 *   proceed. The class here is intentionally plain and non-invasive.
 *
 * Explicit non-responsibilities:
 *   This file does not run test suites, enforce deployment, mutate policies,
 *   activate assignments, call targets, invoke a realizer, perform recovery,
 *   persist reports, or export telemetry.
 */
struct TPolicyProductionReadinessGate
{
    TPolicyProductionReadinessGateId id;
    std::string title;
    TPolicyProductionReadinessGateStatus status{TPolicyProductionReadinessGateStatus::draft};
    std::vector<TPolicyProductionReadinessCriterion> criteria;
    std::vector<std::string> covered_waves;
    std::vector<std::string> known_deferred_decisions;
    TPolicyProductionReadinessReport report;

    [[nodiscard]] std::size_t criterion_count() const noexcept { return criteria.size(); }
    [[nodiscard]] bool has_missing_required_criteria() const noexcept
    {
        for (const auto& criterion : criteria)
        {
            if (criterion.missing_required()) { return true; }
        }
        return false;
    }
    [[nodiscard]] bool is_ready() const noexcept
    {
        return !has_missing_required_criteria() && !report.has_blockers() &&
               (status == TPolicyProductionReadinessGateStatus::passed ||
                status == TPolicyProductionReadinessGateStatus::passed_with_warnings ||
                status == TPolicyProductionReadinessGateStatus::conditional_pass);
    }
    void add_criterion(TPolicyProductionReadinessCriterion criterion)
    {
        criteria.push_back(std::move(criterion));
    }
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
