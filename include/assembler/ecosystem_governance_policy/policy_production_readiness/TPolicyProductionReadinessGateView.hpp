#pragma once

#include <cstddef>
#include "TPolicyProductionReadinessGateId.hpp"
#include "TPolicyProductionReadinessGateStatus.hpp"

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines a small read-only view of a production readiness gate.
 *   It allows downstream review surfaces to inspect identity, status, issue
 *   count, and missing-criteria count without receiving ownership of the full
 *   gate aggregate.
 *
 * Relationship to prior waves:
 *   Views were used throughout W01-W33 to preserve boundaries between core
 *   artifacts and consuming tools. This view continues that pattern for the
 *   final production readiness gate.
 *
 * Full intended picture:
 *   Future dashboards, compliance reviews, or release notes may consume the view
 *   without depending on the full gate object.
 *
 * Explicit non-responsibilities:
 *   This file does not evaluate the gate, run tests, persist reports, export
 *   audit data, mutate policy state, or grant release authority.
 */
struct TPolicyProductionReadinessGateView
{
    TPolicyProductionReadinessGateId id;
    TPolicyProductionReadinessGateStatus status{TPolicyProductionReadinessGateStatus::unknown};
    std::size_t criteria_count{0};
    std::size_t issue_count{0};
    bool has_blockers{false};
    bool has_missing_required_criteria{false};
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
