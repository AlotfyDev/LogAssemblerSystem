#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_type_system/realization_engine/TPolicyRealizationEngine.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyRealizationEngine engine = TPolicyRealizationEngine::CreateConfigured(TPolicyRealizationEngineId{24}, 10, "w24-smoke");
    assert(engine.IsConfigured());

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
    step.description = "verify readiness before engine skeleton inspection";
    step.guard_set.Add(TPolicyExecutionGuard{TPolicyExecutionGuardKind::readiness_guard, true, true, "readiness positive"});
    plan.AddStep(step);

    assert(plan.MayBeSubmittedToFutureExecutorInspection());
    assert(engine.CanInspectPlan(plan));
    auto result = engine.InspectPlan(plan);
    assert(result.MayProceedToFutureExecutor());
    assert(engine.View().IsInspectable());
    std::cout << "EG-POL-W24 smoke test passed\n";
    return 0;
}
