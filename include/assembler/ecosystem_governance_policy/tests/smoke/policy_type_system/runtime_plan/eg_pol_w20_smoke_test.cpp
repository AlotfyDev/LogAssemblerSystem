#include "assembler/ecosystem_governance/policy_type_system/runtime_plan/TPolicyRuntimePlanView.hpp"

#include <cassert>

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyRealizationRequest request;
    request.request_id = 2001;
    request.request_kind = TPolicyRealizationRequestKind::realization_plan;
    request.contract_id = TPolicyRealizationContractId{18};
    request.context_id = TPolicyRealizationContextId{19};
    request.requested_mode = TPolicyRealizationMode::local_mechanism;
    request.authority_evidence_id = 77;
    request.trace_id = 88;

    auto readiness = TPolicyRuntimeReadinessReport::Ready(TPolicyRealizationContractId{18});
    readiness.trace.trace_ref = TPolicyRealizationTraceRef{88};
    readiness.trace.policy_id = TPolicyId{1};
    readiness.trace.policy_version = TPolicyVersion{1,0,0};
    readiness.trace.contract_id = TPolicyRealizationContractId{18};
    readiness.trace.context_id = TPolicyRealizationContextId{19};

    auto plan = TPolicyRuntimePlan::FromReadiness(TPolicyRuntimePlanId{20}, readiness, request);
    plan.AddStep(TPolicyRuntimePlanStep{1, TPolicyRuntimePlanStepKind::verify_contract, true, true, 18, "verify contract", "contract identity is present"});
    plan.AddStep(TPolicyRuntimePlanStep{2, TPolicyRuntimePlanStepKind::verify_runtime_readiness, true, true, 18, "verify readiness", "runtime readiness is positive"});
    plan.AddStep(TPolicyRuntimePlanStep{3, TPolicyRuntimePlanStepKind::submit_to_future_realizer, false, true, 0, "submit to future realizer", "descriptive only; no execution"});

    assert(plan.IsStructurallyValid());
    assert(plan.HasPositiveReadiness());
    assert(plan.IsPlanReady());
    assert(plan.MayBeSubmittedToFutureRealizer());

    auto view = TPolicyRuntimePlanView::FromPlan(plan);
    assert(view.IsPositive());
    assert(view.step_count == 3);
    assert(view.issue_count == 0);
    return 0;
}
