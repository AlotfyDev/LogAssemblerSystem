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

/* Names descriptive categories of compliance test cases. */
enum class TPolicyComplianceTestKind{positive_contract,negative_anti_collapse,boundary_guard,dependency_order,compile_smoke,integration_skeleton,production_gate,regression_case,deferred_decision_check};
inline const char* to_string(TPolicyComplianceTestKind v) noexcept{switch(v){case TPolicyComplianceTestKind::positive_contract:return "positive_contract";case TPolicyComplianceTestKind::negative_anti_collapse:return "negative_anti_collapse";case TPolicyComplianceTestKind::boundary_guard:return "boundary_guard";case TPolicyComplianceTestKind::dependency_order:return "dependency_order";case TPolicyComplianceTestKind::compile_smoke:return "compile_smoke";case TPolicyComplianceTestKind::integration_skeleton:return "integration_skeleton";case TPolicyComplianceTestKind::production_gate:return "production_gate";case TPolicyComplianceTestKind::regression_case:return "regression_case";case TPolicyComplianceTestKind::deferred_decision_check:return "deferred_decision_check";}return "unknown";}

} // namespace assembler::ecosystem_governance::policy_test_compliance
