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
 *   This header defines one production readiness criterion. Criteria represent
 *   expected conditions such as architecture compliance, compile-suite success,
 *   integration smoke coverage, negative compliance coverage, failure-boundary
 *   review, and deferred-decision disclosure.
 *
 * Relationship to prior waves:
 *   W33 describes compliance assertions and test cases. W34 wraps such inputs in
 *   production readiness criteria, without becoming a test runner or CI pipeline.
 *
 * Full intended picture:
 *   Future readiness gates may contain multiple criteria, each of which can be
 *   marked required or advisory and linked to evidence references.
 *
 * Explicit non-responsibilities:
 *   This file does not run criteria, fetch evidence, write reports, invoke
 *   policies, mutate targets, or grant production approval by itself.
 */
struct TPolicyProductionReadinessCriterion
{
    std::string name;
    std::string description;
    bool required{true};
    bool satisfied{false};

    TPolicyProductionReadinessCriterion() = default;
    TPolicyProductionReadinessCriterion(std::string n, std::string d, bool req = true)
        : name(std::move(n)), description(std::move(d)), required(req) {}

    [[nodiscard]] bool missing_required() const noexcept { return required && !satisfied; }
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
