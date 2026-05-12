#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/realization_session/TPolicyRealizationSession.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyRealizationSessionOpenRequest request{};
    request.open_request_id = 1;
    request.realization_request.request_id = 2;
    request.realization_request.request_kind = TPolicyRealizationRequestKind::runtime_realization;
    request.realization_request.contract_id = TPolicyRealizationContractId{3};
    request.realization_request.context_id = TPolicyRealizationContextId{4};
    request.realization_request.requested_mode = TPolicyRealizationMode::descriptive_only;
    request.realization_request.readiness_report_id = 5;
    request.realization_request.trace_id = 6;
    request.readiness_report = TPolicyRuntimeReadinessReport::Ready(TPolicyRealizationContractId{3});
    request.readiness_report.trace.readiness_report_id = 5;
    request.readiness_report.trace.trace_ref.value = 6;
    request.authority_evidence_id = 7;
    request.trace_id = 6;

    TPolicyRealizationSession session = CreatePolicyRealizationSession(TPolicyRealizationSessionId{9}, request, TPolicyRealizerId{10});
    assert(session.IsValidSession());
    assert(session.IsOpen());
    assert(session.HasRealizer());
    assert(session.View().IsValidView());

    TPolicyRealizationSessionResult result = session.ValidateForInspection();
    assert(result.IsPositive());
    assert(!result.HasBlockingIssue());

    return 0;
}
