#include <cassert>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyProfile.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopeCompatibility.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyFamilyProfile profile;
    profile.family_id = TPolicyFamilyId{42};
    profile.kind = TPolicyFamilyKind::dispatch;
    profile.canonical_name = "dispatcher_policy_family";
    profile.default_scope = TPolicyScope::component;
    profile.AddAllowedScope(TPolicyScope::component);
    profile.AddAllowedScope(TPolicyScope::mechanism);
    profile.safe_replacement_expected = true;
    profile.runtime_realization_expected = true;

    assert(profile.IsValid());
    assert(profile.AllowsScope(TPolicyScope::component));
    assert(!profile.AllowsScope(TPolicyScope::domain));
    assert(profile.IsRuntimeSensitive());

    TPolicyFamilyView view{&profile};
    assert(view.IsValid());
    assert(view.FamilyId() == TPolicyFamilyId{42});
    assert(view.RequiresSafeReplacement());
    assert(view.ExpectsRuntimeRealization());

    TPolicyScopePath policy_scope{TPolicyScope::component, {"system", "material_circulation", "dispatcher"}};
    TPolicyScopePath target_scope{TPolicyScope::component, {"system", "material_circulation", "dispatcher", "instance_001"}};
    auto compatibility = CheckScopePathCompatibility(policy_scope, target_scope);
    assert(compatibility.IsPositive());
    assert(!compatibility.IsBlocking());

    TPolicyScopePath wrong_target{TPolicyScope::component, {"system", "log_level_api", "validator"}};
    auto bad = CheckScopePathCompatibility(policy_scope, wrong_target);
    assert(!bad.IsPositive());
    assert(bad.IsBlocking());

    return 0;
}
