#include <cassert>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssigner.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSurface.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;
using namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner;
using namespace assembler::ecosystem_governance::policy_type_system::policy_object_host;
using namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object;

int main()
{
    TPolicyObjectHostSurface host;
    host.descriptor.host_id = TPolicyObjectHostId{"host.log_level_api.validator.main"};
    host.descriptor.domain_ref = "log_level_api";
    host.descriptor.target_ref = "validator.main";
    host.descriptor.target_kind_ref = "log_level_api.validator";
    host.descriptor.host_surface_kind = "policy_object_host";
    host.descriptor.status = TPolicyObjectHostStatus::safe_point_open;
    host.descriptor.accepted_policy_families.push_back("validation_policy_family");
    host.update_safe_point(TPolicyObjectHostSafePointFlag::open("safe_point.validator.idle", "validator idle"));
    host.assignment_port.host_id = host.descriptor.host_id;
    host.assignment_port.current_completed_policy_object_id = TCompletedPolicyObjectId{"completed.validation.validator.v1"};
    host.assignment_port.stage(TCompletedPolicyObjectId{"completed.validation.validator.v2"});

    TDomainPolicyAssigner assigner;
    assigner.assigner_id = TDomainPolicyAssignerId{"assigner.log_level_api.main"};
    assigner.domain_ref = "log_level_api";
    assigner.status = TDomainPolicyAssignerStatus::ready;

    TPolicySafePointSwitchRequest request;
    request.assigner_id = assigner.assigner_id;
    request.host_id = host.descriptor.host_id;
    request.expected_current_completed_policy_object_id = host.assignment_port.current_completed_policy_object_id;
    request.pending_completed_policy_object_id = host.assignment_port.pending_completed_policy_object_id;
    request.domain_ref = "log_level_api";
    request.target_ref = "validator.main";
    request.reason = "policy upgrade smoke test";
    request.require_existing_current = true;

    auto plan = assigner.plan_switch(host, request);
    assert(plan.switch_allowed());
    auto result = assigner.apply_switch(host, plan);
    assert(result.applied());
    assert(host.assignment_port.current_completed_policy_object_id.value == "completed.validation.validator.v2");
    assert(host.assignment_port.pending_completed_policy_object_id.empty());
    assert(assigner.view().healthy());

    return 0;
}
