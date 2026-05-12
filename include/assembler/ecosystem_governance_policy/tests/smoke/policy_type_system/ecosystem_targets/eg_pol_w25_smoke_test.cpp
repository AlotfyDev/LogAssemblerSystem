#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/log_level_api/TLogLevelApiPolicyTargets.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    auto targets = TLogLevelApiPolicyTargets::Default();
    assert(targets.IsStructurallyComplete());

    auto report = targets.Inspect();
    assert(report.Passed());
    assert(report.target_count == 6);
    assert(report.profile_count == 6);
    assert(report.compatibility_rule_count == 3);

    TPolicyFamilyProfile preparation_family{};
    preparation_family.family_id = TPolicyFamilyId{25};
    preparation_family.kind = TPolicyFamilyKind::preparation;
    preparation_family.canonical_name = "log_level_api_preparation_policy_family";
    preparation_family.default_scope = TPolicyScope::component;
    preparation_family.AddAllowedScope(TPolicyScope::component);
    preparation_family.AddAllowedScope(TPolicyScope::domain);
    preparation_family.AddAllowedScope(TPolicyScope::boundary);
    preparation_family.observation_expected = true;

    auto compatibility = targets.Evaluate(preparation_family, TLogLevelApiPolicyTargetKind::content_validator);
    assert(compatibility.policy_family_kind == TPolicyFamilyKind::preparation);
    assert(compatibility.target_kind == TPolicyTargetKind::log_level_api_component);
    assert(!compatibility.IsBlocking());

    const auto* descriptor = targets.registry_view.Find(TLogLevelApiPolicyTargetKind::metadata_injector);
    assert(descriptor != nullptr);
    assert(descriptor->IsDescriptorOnly());
    std::cout << "EG-POL-W25 smoke test passed\n";
    return 0;
}
