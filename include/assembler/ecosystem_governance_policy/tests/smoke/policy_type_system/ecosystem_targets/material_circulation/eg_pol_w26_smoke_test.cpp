#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/material_circulation/TMaterialCirculationPolicyTargets.hpp"

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;
    auto targets = TMaterialCirculationPolicyTargets::DefaultMaterialCirculationTargets();
    assert(targets.IsStructurallyComplete());
    assert(targets.registry_view.Has(TMaterialCirculationPolicyTargetKind::dispatcher));
    auto report = targets.Inspect();
    assert(report.IsPositive());
    assert(report.described_targets >= 7);
    assert(report.compatibility_rules >= 5);
    const auto* dispatcher = targets.registry_view.Find(TMaterialCirculationPolicyTargetKind::dispatcher);
    assert(dispatcher != nullptr);
    assert(dispatcher->IsReadyForCompatibility());
    assert(dispatcher->descriptor.RequiresReplacementDiscipline());
    return 0;
}
