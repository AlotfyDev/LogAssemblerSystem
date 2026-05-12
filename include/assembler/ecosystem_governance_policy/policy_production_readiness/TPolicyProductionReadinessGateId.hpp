#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines the stable identifier for a production readiness gate.
 *   A gate identity allows reports, criteria, evidence references, and review
 *   decisions to refer to the same non-executing production gate without
 *   confusing it with a runtime engine, a CI job, a registry entry, or a target.
 *
 * Relationship to prior waves:
 *   W30 introduced persistence-boundary descriptors, W31 introduced audit-export
 *   boundary descriptors, W32 introduced runtime failure/recovery boundaries,
 *   and W33 introduced the test/compliance suite. W34 uses those notions as
 *   review inputs but does not depend on their concrete execution.
 *
 * Full intended picture:
 *   Future implementation may use this id to index named production gates such
 *   as architecture compliance, compile readiness, negative compliance tests,
 *   integration smoke checks, and known-decision review. The id remains a plain
 *   value object to preserve portability.
 *
 * Explicit non-responsibilities:
 *   This file does not evaluate readiness, execute tests, persist reports, call
 *   targets, mutate policies, invoke a realizer, or trigger deployment. It only
 *   names a production readiness gate.
 */
struct TPolicyProductionReadinessGateId
{
    std::string value;

    TPolicyProductionReadinessGateId() = default;
    explicit TPolicyProductionReadinessGateId(std::string v) : value(std::move(v)) {}
    [[nodiscard]] bool empty() const noexcept { return value.empty(); }
};

inline bool operator==(const TPolicyProductionReadinessGateId& a,
                       const TPolicyProductionReadinessGateId& b) noexcept
{
    return a.value == b.value;
}

inline bool operator!=(const TPolicyProductionReadinessGateId& a,
                       const TPolicyProductionReadinessGateId& b) noexcept
{
    return !(a == b);
}

} // namespace assembler::ecosystem_governance::policy_production_readiness
