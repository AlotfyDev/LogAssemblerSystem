#include "assembler/ecosystem_governance/policy_type_system/runtime_readiness/TPolicyRuntimeReadinessEvaluator.hpp"

#include <cassert>
#include <cstdint>

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyRealizationContract contract;
    contract.contract_id = TPolicyRealizationContractId{19};
    contract.contract_kind = TPolicyRealizationContractKind::runtime_capable_realization;
    contract.policy_family_kind = TPolicyFamilyKind::admission;
    contract.target_kind = TPolicyTargetKind::dispatcher;
    contract.expected_realization_mode = TPolicyRealizationMode::local_mechanism;

    TPolicyRuntimeAdmission admission;
    admission.assignment_state = TPolicyAssignmentLifecycleState::active;
    admission.compatibility_report = TPolicyFamilyCompatibilityReport::Compatible(TPolicyFamilyKind::admission, TPolicyTargetKind::dispatcher);
    admission.contract_id = contract.contract_id;
    admission.publication_satisfied = true;
    admission.authority_satisfied = true;
    admission.conflict_clear = true;
    admission.not_quarantined = true;
    admission.trace_available = true;

    TPolicyRuntimeReadinessEvaluator evaluator;
    auto report = evaluator.Evaluate(admission, contract);
    assert(report.IsPositive());
    assert(report.MayProceedToRealizationPlanning());
    assert(report.gate_set.Count() == 8);
    return 0;
}
