#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/ecosystem_targets/system_wide/TSystemWidePolicyIntegrationSkeleton.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    auto skeleton = TSystemWidePolicyIntegrationSkeleton::DefaultDemo();
    assert(skeleton.IsStructurallyComplete());
    auto report = skeleton.Inspect();
    assert(report.IsPositive());
    assert(report.target_slices_present == 4);
    assert(report.plan_steps >= 6);
    assert(skeleton.ids.HasPolicyRegistryAndAssignment());
    assert(skeleton.ids.HasReadinessPathRefs());
    assert(skeleton.ids.HasRealizerRef());
    return 0;
}
