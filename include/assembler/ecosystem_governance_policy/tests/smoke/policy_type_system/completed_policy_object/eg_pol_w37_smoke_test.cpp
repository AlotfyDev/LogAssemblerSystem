#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObject.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectCompletionReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectDomainViewSet.hpp"

using namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object;
using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TCompletedPolicyObject object;
    object.id = TCompletedPolicyObjectId{"completed.validation.validator.v1"};
    object.governance_bundle_id = semantic_delivery::TPolicyBundleDtoId{"bundle.validation.v1"};
    object.semantic_payload_ref = semantic_delivery::TPolicySemanticPayloadRef{"validation_clause_set", "payload.validation.clauses"};
    object.target_realization_map_id = target_realization::TPolicyTargetRealizationMapId{"map.validator.validation"};
    object.policy_family_ref = "validation_policy_family";
    object.target_kind_ref = "log_level_api.validator";
    object.domain_ref = "log_level_api";
    object.status = TCompletedPolicyObjectStatus::completed;
    object.add_evidence_ref(TCompletedPolicyObjectEvidenceRef{"evidence.semantic.delivery.ok"});

    assert(object.has_identity());
    assert(object.has_domain_binding());
    assert(object.ready_for_host_assignment());

    TCompletedPolicyObjectView view{&object};
    assert(view.valid());
    assert(view.ready_for_host_assignment());
    assert(view.evidence_count() == 1U);

    TCompletedPolicyObjectCompletionReport report;
    report.completed_policy_object_id = object.id;
    report.status = object.status;
    assert(report.passed());

    TDomainCompletedPolicyObjectView domain_view;
    domain_view.domain_ref = "log_level_api";
    domain_view.add(view);
    assert(domain_view.size() == 1U);
    assert(domain_view.ready_count() == 1U);

    TCompletedPolicyObjectDomainViewSet set;
    set.add(domain_view);
    assert(set.size() == 1U);
    assert(set.total_ready_count() == 1U);

    return 0;
}
