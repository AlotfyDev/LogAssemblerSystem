#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include "TPolicyComplianceAssertion.hpp"
#include "TPolicyComplianceTestKind.hpp"

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

/* A non-executing test case descriptor. */
struct TPolicyComplianceTestCase{std::string test_case_id;std::string title;TPolicyComplianceTestKind kind=TPolicyComplianceTestKind::negative_anti_collapse;TPolicyComplianceOutcome expected_outcome=TPolicyComplianceOutcome::pass;std::vector<TPolicyComplianceAssertion> assertions;std::vector<std::string> tags;std::string description;[[nodiscard]] std::size_t assertion_count() const noexcept{return assertions.size();}[[nodiscard]] bool has_assertions() const noexcept{return !assertions.empty();}};

} // namespace assembler::ecosystem_governance::policy_test_compliance
