#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostSurface.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;
using namespace assembler::ecosystem_governance::policy_type_system::policy_object_host;
using namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object;

int main()
{
    TCompletedPolicyObject completed;
    completed.id = TCompletedPolicyObjectId{"completed.validation.validator.v1"};
    completed.governance_bundle_id = semantic_delivery::TPolicyBundleDtoId{"bundle.validation.v1"};
    completed.semantic_payload_ref = semantic_delivery::TPolicySemanticPayloadRef{"validation_clause_set", "payload.validation.clauses"};
    completed.target_realization_map_id = target_realization::TPolicyTargetRealizationMapId{"map.validator.validation"};
    completed.policy_family_ref = "validation_policy_family";
    completed.target_kind_ref = "log_level_api.validator";
    completed.domain_ref = "log_level_api";
    completed.status = TCompletedPolicyObjectStatus::completed;

    TPolicyObjectHostSurface host;
    host.descriptor.host_id = TPolicyObjectHostId{"host.log_level_api.validator.main"};
    host.descriptor.domain_ref = "log_level_api";
    host.descriptor.target_ref = "validator.main";
    host.descriptor.target_kind_ref = "log_level_api.validator";
    host.descriptor.host_surface_kind = "policy_object_host";
    host.descriptor.status = TPolicyObjectHostStatus::available;
    host.descriptor.accepted_policy_families.push_back("validation_policy_family");
    host.update_safe_point(TPolicyObjectHostSafePointFlag::open("safe_point.validator.idle", "validator idle"));

    auto admission = host.admit(completed);
    assert(admission.passed());
    host.stage_if_admitted(admission);

    auto view = host.view();
    assert(view.valid());
    assert(view.safe_point_open());
    assert(view.has_pending_assignment());
    assert(view.can_switch_now());
    assert(view.accepted_family_count() == 1U);
    assert(host.report.healthy());

    return 0;
}
