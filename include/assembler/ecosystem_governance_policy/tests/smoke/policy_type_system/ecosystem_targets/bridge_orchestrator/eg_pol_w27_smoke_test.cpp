#include <cassert>
#include <iostream>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/communication_context/TCommunicationContextPolicySurface.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    auto surface = TCommunicationContextPolicySurface::Default();
    assert(surface.IsStructurallyComplete());

    auto report = surface.Inspect();
    assert(report.IsPositive());
    assert(report.described_surfaces == 10);
    assert(report.capability_profiles == 10);
    assert(report.compatibility_rules == 5);

    TPolicyFamilyProfile communication_family{};
    communication_family.family_id = TPolicyFamilyId{27};
    communication_family.kind = TPolicyFamilyKind::communication;
    communication_family.canonical_name = "communication_context_policy_family";
    communication_family.default_scope = TPolicyScope::component;
    communication_family.AddAllowedScope(TPolicyScope::domain);
    communication_family.AddAllowedScope(TPolicyScope::component);
    communication_family.AddAllowedScope(TPolicyScope::boundary);
    communication_family.safe_replacement_expected = true;
    communication_family.observation_expected = true;

    auto compatibility = surface.Evaluate(communication_family, TCommunicationContextPolicySurfaceKind::binding_declaration);
    assert(compatibility.policy_family_kind == TPolicyFamilyKind::communication);
    assert(compatibility.target_kind == TPolicyTargetKind::communication_boundary_surface);
    assert(!compatibility.IsBlocking());

    const auto* descriptor = surface.registry_view.Find(TCommunicationContextPolicySurfaceKind::bridge_core);
    assert(descriptor != nullptr);
    assert(descriptor->descriptor.IsDescriptorOnly());
    assert(descriptor->descriptor.RequiresReplacementDiscipline());

    std::cout << "EG-POL-W27 smoke test passed\n";
    return 0;
}
