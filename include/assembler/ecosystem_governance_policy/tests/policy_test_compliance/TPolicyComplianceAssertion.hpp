#pragma once

#include <string>
#include "TPolicyComplianceDimension.hpp"
#include "TPolicyComplianceOutcome.hpp"
#include "TPolicyComplianceSeverity.hpp"

namespace assembler::ecosystem_governance::policy_test_compliance
{
/*
 * Wave: EG-POL-W33_Policy_Test_And_Compliance_Suite
 * Domain: ecosystem_governance / policy_test_compliance
 *
 * Architectural role:
 *   This header belongs to the production-hardening test and compliance suite.
 *   The suite describes compliance dimensions, assertions, negative tests,
 *   suite-level reports, and anti-collapse expectations across W01-W32.
 *
 * Relationship to prior waves:
 *   W01-W11 define the policy object and registry basics. W12-W17 add family,
 *   target capability, compatibility, assignment lifecycle, source/publication,
 *   and registry versioning. W18-W24 add realization contracts, runtime
 *   readiness, runtime plans, realizer interfaces, sessions, execution plans,
 *   and engine skeletons. W25-W29 add ecosystem target surfaces. W30-W32 add
 *   persistence, audit-export, failure, recovery, and quarantine boundaries.
 *
 * Full intended picture:
 *   Future tooling may consume these descriptors to build a real test runner,
 *   compliance dashboard, CI validation step, or production readiness gate. The
 *   types here deliberately remain plain C++17 value objects so they can be used
 *   by many environments without coupling this wave to any execution framework.
 *
 * Explicit non-responsibilities:
 *   This file does not run tests, invoke policies, mutate assignments, call
 *   targets, perform recovery, persist reports, emit telemetry, implement CI,
 *   access filesystems, call networks, bind communication context, or execute
 *   add-ons. It is a descriptive foundation only.
 */

/* A single declarative compliance assertion. */
struct TPolicyComplianceAssertion{std::string assertion_id;std::string subject;TPolicyComplianceDimension dimension=TPolicyComplianceDimension::anti_collapse;TPolicyComplianceOutcome expected_outcome=TPolicyComplianceOutcome::pass;TPolicyComplianceSeverity severity=TPolicyComplianceSeverity::blocking;std::string statement;std::string rationale;[[nodiscard]] bool is_blocking() const noexcept{return severity==TPolicyComplianceSeverity::blocking||severity==TPolicyComplianceSeverity::critical||severity==TPolicyComplianceSeverity::forbidden;}};

} // namespace assembler::ecosystem_governance::policy_test_compliance
