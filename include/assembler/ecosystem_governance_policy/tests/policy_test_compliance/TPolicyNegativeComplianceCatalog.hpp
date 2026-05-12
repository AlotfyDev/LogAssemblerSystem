#pragma once

#include <string>
#include <vector>
#include "TPolicyComplianceTestCase.hpp"

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

/* Named anti-collapse negative cases. The catalog is declarative only. */
struct TPolicyNegativeComplianceCatalog{
static TPolicyComplianceTestCase policy_must_not_own_target(){TPolicyComplianceTestCase tc;tc.test_case_id="EG-POL-W33-NEG-001";tc.title="Policy object must not own target";tc.assertions.push_back({"ASSERT-NO-TARGET-OWNERSHIP","policy",TPolicyComplianceDimension::anti_collapse,TPolicyComplianceOutcome::pass,TPolicyComplianceSeverity::forbidden,"A policy object must not own a concrete target instance.","Target ownership belongs outside TPolicy and outside assignment descriptors."});tc.tags={"anti_collapse","target_ownership"};return tc;}
static TPolicyComplianceTestCase assignment_must_not_invoke_target(){TPolicyComplianceTestCase tc;tc.test_case_id="EG-POL-W33-NEG-002";tc.title="Assignment must not invoke target";tc.assertions.push_back({"ASSERT-ASSIGNMENT-NON-EXECUTION","assignment",TPolicyComplianceDimension::assignment_lifecycle,TPolicyComplianceOutcome::pass,TPolicyComplianceSeverity::forbidden,"A policy assignment must remain a governed relation and must not invoke target behavior.","Assignment activation is not realization and not execution."});tc.tags={"anti_collapse","assignment","target_invocation"};return tc;}
static TPolicyComplianceTestCase registry_must_not_be_service_locator(){TPolicyComplianceTestCase tc;tc.test_case_id="EG-POL-W33-NEG-003";tc.title="Registry must not become service locator";tc.assertions.push_back({"ASSERT-REGISTRY-NOT-LOCATOR","registry",TPolicyComplianceDimension::registry_versioning,TPolicyComplianceOutcome::pass,TPolicyComplianceSeverity::critical,"Policy registry must not return uncontrolled runtime target handles or behave as a service locator.","Registry is catalog and versioning infrastructure, not dependency injection."});tc.tags={"anti_collapse","registry"};return tc;}
static TPolicyComplianceTestCase realizer_must_consume_readiness(){TPolicyComplianceTestCase tc;tc.test_case_id="EG-POL-W33-NEG-004";tc.title="Realizer must consume readiness and compatibility";tc.assertions.push_back({"ASSERT-REALIZER-GATED","realizer",TPolicyComplianceDimension::realizer_interface,TPolicyComplianceOutcome::pass,TPolicyComplianceSeverity::blocking,"A realizer must consume compatibility, assignment, contract, and runtime readiness evidence before any runtime action is considered.","The realizer must not invent compatibility or bypass readiness gates."});tc.tags={"anti_collapse","realizer","runtime_readiness"};return tc;}
};

} // namespace assembler::ecosystem_governance::policy_test_compliance
