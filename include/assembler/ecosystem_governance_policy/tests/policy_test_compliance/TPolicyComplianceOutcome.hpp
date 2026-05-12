#pragma once

#include <string>

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

/* Defines non-executing outcome terms for checks and suite cases. */
enum class TPolicyComplianceOutcome{not_evaluated,pass,pass_with_warnings,conditional_pass,deferred,fail,blocked,critical_failure,forbidden};
inline bool is_positive(TPolicyComplianceOutcome v) noexcept{return v==TPolicyComplianceOutcome::pass||v==TPolicyComplianceOutcome::pass_with_warnings||v==TPolicyComplianceOutcome::conditional_pass;}
inline const char* to_string(TPolicyComplianceOutcome v) noexcept{switch(v){case TPolicyComplianceOutcome::not_evaluated:return "not_evaluated";case TPolicyComplianceOutcome::pass:return "pass";case TPolicyComplianceOutcome::pass_with_warnings:return "pass_with_warnings";case TPolicyComplianceOutcome::conditional_pass:return "conditional_pass";case TPolicyComplianceOutcome::deferred:return "deferred";case TPolicyComplianceOutcome::fail:return "fail";case TPolicyComplianceOutcome::blocked:return "blocked";case TPolicyComplianceOutcome::critical_failure:return "critical_failure";case TPolicyComplianceOutcome::forbidden:return "forbidden";}return "unknown";}

} // namespace assembler::ecosystem_governance::policy_test_compliance
