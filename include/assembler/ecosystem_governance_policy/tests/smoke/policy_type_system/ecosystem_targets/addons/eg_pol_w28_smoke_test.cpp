#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/addons/TAddonPolicyTargets.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyProfile.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    auto targets = TAddonPolicyTargets::Default();
    assert(targets.IsStructurallyComplete());
    auto report = targets.Inspect();
    assert(report.IsPositive());

    TPolicyFamilyProfile addon_family{};
    addon_family.kind = TPolicyFamilyKind::addon;
    addon_family.family_id = TPolicyFamilyId{2801};
    addon_family.canonical_name = "addon_policy_family";
    addon_family.default_scope = TPolicyScope::component;
    addon_family.allowed_scopes = {TPolicyScope::component, TPolicyScope::instance, TPolicyScope::boundary};

    auto compatibility = targets.Evaluate(addon_family, TAddonPolicyTargetKind::database_adapter);
    assert(compatibility.IsPositive());
    assert(targets.registry_view.Has(TAddonPolicyTargetKind::thin_c_abi_adapter));
    assert(IsDestinationFacingAddonTarget(TAddonPolicyTargetKind::database_adapter));
    assert(IsBoundaryAddonTarget(TAddonPolicyTargetKind::thin_c_abi_adapter));
    return 0;
}
