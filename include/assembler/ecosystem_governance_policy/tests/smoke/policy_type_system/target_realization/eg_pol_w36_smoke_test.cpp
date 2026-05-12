#include <cassert>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMap.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationDeclarationReport.hpp"

using namespace assembler::ecosystem_governance::policy_type_system::target_realization;

int main()
{
    TPolicyTargetCapabilityDeclaration cap;
    cap.id = TPolicyTargetCapabilityDeclarationId{"cap.validation.accept"};
    cap.target_kind_ref = "log_level_api.validator";
    cap.capability_name = "accept_validation_semantics";
    cap.capability_kind = TPolicyTargetRealizationCapabilityKind::readiness_probe;
    cap.required_for_completion = true;
    assert(cap.is_well_formed());

    TPolicySemanticToTargetMappingRule rule;
    rule.semantic_part_name = "validation_clause_set";
    rule.target_capability_name = "accept_validation_semantics";
    rule.realization_contract_ref = "contract.validation.v1";
    rule.mandatory = true;
    assert(rule.is_well_formed());

    TPolicyTargetRealizationMap map;
    map.id = TPolicyTargetRealizationMapId{"map.validator.validation"};
    map.target_kind_ref = "log_level_api.validator";
    map.policy_family_ref = "validation_policy_family";
    map.status = TPolicyTargetRealizationMapStatus::compatible;
    map.add_capability(cap);
    map.add_mapping_rule(rule);
    assert(map.has_identity());
    assert(map.has_capability("accept_validation_semantics"));
    assert(map.mapping_rules_are_satisfied());
    assert(map.is_ready_for_completion());

    TPolicyTargetRealizationMapView view{&map};
    assert(view.valid());
    assert(view.capability_count() == 1);
    assert(view.mapping_rule_count() == 1);
    assert(view.ready_for_completion());

    TPolicyTargetRealizationDeclarationReport report;
    report.map_id = map.id;
    report.status = map.status;
    assert(report.passed());

    return 0;
}
