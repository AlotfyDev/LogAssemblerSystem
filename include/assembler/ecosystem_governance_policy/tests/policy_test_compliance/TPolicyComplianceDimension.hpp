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

/* Names the validation dimensions covered by the suite. */
enum class TPolicyComplianceDimension{policy_identity,policy_family,policy_clause,replacement,lifecycle,observation,target_kind,target_capability,compatibility,assignment_lifecycle,authority,source_publication,registry_versioning,realization_contract,runtime_readiness,runtime_plan,realizer_interface,realization_session,execution_plan,realization_engine,ecosystem_target,persistence_boundary,audit_export_boundary,failure_recovery,anti_collapse,production_gate};
inline const char* to_string(TPolicyComplianceDimension v) noexcept{switch(v){case TPolicyComplianceDimension::policy_identity:return "policy_identity";case TPolicyComplianceDimension::policy_family:return "policy_family";case TPolicyComplianceDimension::policy_clause:return "policy_clause";case TPolicyComplianceDimension::replacement:return "replacement";case TPolicyComplianceDimension::lifecycle:return "lifecycle";case TPolicyComplianceDimension::observation:return "observation";case TPolicyComplianceDimension::target_kind:return "target_kind";case TPolicyComplianceDimension::target_capability:return "target_capability";case TPolicyComplianceDimension::compatibility:return "compatibility";case TPolicyComplianceDimension::assignment_lifecycle:return "assignment_lifecycle";case TPolicyComplianceDimension::authority:return "authority";case TPolicyComplianceDimension::source_publication:return "source_publication";case TPolicyComplianceDimension::registry_versioning:return "registry_versioning";case TPolicyComplianceDimension::realization_contract:return "realization_contract";case TPolicyComplianceDimension::runtime_readiness:return "runtime_readiness";case TPolicyComplianceDimension::runtime_plan:return "runtime_plan";case TPolicyComplianceDimension::realizer_interface:return "realizer_interface";case TPolicyComplianceDimension::realization_session:return "realization_session";case TPolicyComplianceDimension::execution_plan:return "execution_plan";case TPolicyComplianceDimension::realization_engine:return "realization_engine";case TPolicyComplianceDimension::ecosystem_target:return "ecosystem_target";case TPolicyComplianceDimension::persistence_boundary:return "persistence_boundary";case TPolicyComplianceDimension::audit_export_boundary:return "audit_export_boundary";case TPolicyComplianceDimension::failure_recovery:return "failure_recovery";case TPolicyComplianceDimension::anti_collapse:return "anti_collapse";case TPolicyComplianceDimension::production_gate:return "production_gate";}return "unknown";}

} // namespace assembler::ecosystem_governance::policy_test_compliance
