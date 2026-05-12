#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_type_system/realization_execution_plan/TPolicyExecutionPlan.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyExecutionPlan plan{};
    plan.plan_id = TPolicyExecutionPlanId{23};
    plan.status = TPolicyExecutionPlanStatus::planned;
    plan.session_id = TPolicyRealizationSessionId{22};
    plan.runtime_plan_id = TPolicyRuntimePlanId{20};
    plan.realizer_id = TPolicyRealizerId{21};
    plan.realization_request_id = 1800;
    plan.readiness_report_id = 1900;
    plan.authority_evidence_id = 500;
    plan.trace_id = 700;
    plan.AddGuard(TPolicyExecutionGuard{TPolicyExecutionGuardKind::contract_guard, true, true, "contract present"});
    TPolicyExecutionStep step{};
    step.step_id = 1;
    step.order = 1;
    step.kind = TPolicyExecutionStepKind::verify_readiness;
    step.description = "verify readiness before any future executor inspection";
    step.guard_set.Add(TPolicyExecutionGuard{TPolicyExecutionGuardKind::readiness_guard, true, true, "readiness positive"});
    plan.AddStep(step);
    assert(plan.IsStructurallyValid());
    assert(plan.MayBeSubmittedToFutureExecutorInspection());
    auto view = plan.View();
    assert(view.IsInspectable());
    auto report = plan.ValidateForFutureExecutorInspection();
    assert(report.MayProceedToFutureExecutorInspection());
    std::cout << "EG-POL-W23 smoke test passed\n";
    return 0;
}
