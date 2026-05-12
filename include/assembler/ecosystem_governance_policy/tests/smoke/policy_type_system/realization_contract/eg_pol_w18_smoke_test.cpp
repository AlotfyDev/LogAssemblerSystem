#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContract.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContractView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationContext.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationFailure.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationPrecondition.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationRequest.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_contract/TPolicyRealizationTrace.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyRealizationContract contract{};
    contract.contract_id.value = 18;
    contract.contract_kind = TPolicyRealizationContractKind::runtime_capable_realization;
    contract.policy_family_kind = TPolicyFamilyKind::runtime_coordination;
    contract.target_kind = TPolicyTargetKind::dispatcher;
    contract.expected_realization_mode = TPolicyRealizationMode::external_mechanism;
    contract.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_readiness_check);
    contract.required_capabilities.push_back(TPolicyTargetCapabilityKind::supports_policy_realization_surface);

    TPolicyRealizationPrecondition p{};
    p.kind = TPolicyRealizationPreconditionKind::compatibility_positive;
    p.status = TPolicyRealizationPreconditionStatus::satisfied;
    contract.required_preconditions.Add(p);

    assert(contract.IsValidContract());
    assert(contract.RequiresRuntimeReadiness());
    assert(contract.HasCapabilityRequirements());

    const auto view = TPolicyRealizationContractView::FromContract(contract);
    assert(view.IsUsableView());
    assert(view.required_capability_count == 2);

    TPolicyRealizationFailure failure{};
    failure.kind = TPolicyRealizationFailureKind::missing_capability;
    failure.severity = TPolicyRealizationFailureSeverity::blocking;
    assert(failure.BlocksReadiness());

    TPolicyRealizationRequest request{};
    request.request_id = 1;
    request.request_kind = TPolicyRealizationRequestKind::runtime_realization;
    request.contract_id = contract.contract_id;
    request.context_id.value = 100;
    request.requested_mode = TPolicyRealizationMode::external_mechanism;
    request.authority_evidence_id = 7;
    request.trace_id = 9;
    assert(request.IsValidRequest());
    assert(request.IsRuntimeRequest());
    assert(!request.IsPlanningOnly());

    return 0;
}
