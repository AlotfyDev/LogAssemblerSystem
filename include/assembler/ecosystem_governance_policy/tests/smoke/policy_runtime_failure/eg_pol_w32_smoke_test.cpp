
#include "assembler/ecosystem_governance/policy_runtime_failure/TPolicyRuntimeFailureAndRecoveryBoundary.hpp"
#include <cassert>
#include <string>

using namespace assembler::ecosystem_governance::policy_runtime_failure;

int main()
{
    TPolicyRuntimeFailureRecord failure = TPolicyRuntimeFailureRecord::make(
        "failure-001",
        TPolicyRuntimeFailureKind::runtime_readiness_failed,
        TPolicyRuntimeFailureSeverity::blocking,
        "runtime readiness failed before realization");
    assert(failure.valid());
    assert(failure.blocks_progression());

    TPolicyRecoveryAction action = TPolicyRecoveryAction::propose(
        "action-001",
        TPolicyRecoveryActionKind::request_runtime_readiness_recheck,
        "assignment-001",
        "recheck after compatibility evidence is refreshed");
    assert(action.valid());
    assert(action.may_be_considered_without_execution());

    TPolicyRecoveryPlan plan{};
    plan.plan_id = "recovery-plan-001";
    plan.status = TPolicyRecoveryPlanStatus::proposed;
    plan.assignment_ref = "assignment-001";
    plan.authority_ref = "authority-001";
    plan.add_failure(failure);
    plan.add_action(action);
    assert(plan.valid());
    assert(plan.has_blocking_failure());
    assert(plan.requires_authority());

    TPolicyRuntimeFailureAndRecoveryBoundary boundary{};
    boundary.boundary_id = "runtime-failure-boundary-001";
    boundary.record_failure(failure);
    boundary.propose_plan(plan);
    auto report = boundary.review_last_plan("report-001");
    assert(report.valid());
    assert(report.blocks_progression());
    assert(!report.issues.empty());
    return 0;
}
