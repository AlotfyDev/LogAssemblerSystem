#include <cassert>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCompatibilityReport.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyTargetCapabilityDescriptor assignment;
    assignment.capability_id = TPolicyTargetCapabilityId{1};
    assignment.kind = TPolicyTargetCapabilityKind::accepts_policy_assignment;
    assignment.target_kind = TPolicyTargetKind::dispatcher;
    assignment.strength = TPolicyTargetCapabilityStrength::required;
    assignment.mutability = TPolicyTargetCapabilityMutability::read_only;
    assignment.canonical_name = "accepts_policy_assignment";

    TPolicyTargetCapabilityDescriptor readiness;
    readiness.capability_id = TPolicyTargetCapabilityId{2};
    readiness.kind = TPolicyTargetCapabilityKind::supports_readiness_check;
    readiness.target_kind = TPolicyTargetKind::dispatcher;
    readiness.strength = TPolicyTargetCapabilityStrength::required;
    readiness.mutability = TPolicyTargetCapabilityMutability::read_only;
    readiness.canonical_name = "supports_readiness_check";

    assert(assignment.IsValid());
    assert(readiness.IsValid());
    assert(readiness.IsRequired());
    assert(readiness.IsDescriptorOnly());
    assert(IsRealizationRelatedCapability(readiness.kind));

    TPolicyTargetCapabilitySet set;
    set.Add(assignment);
    set.Add(readiness);

    assert(!set.IsEmpty());
    assert(set.Contains(TPolicyTargetCapabilityKind::accepts_policy_assignment));
    assert(set.ContainsValid(TPolicyTargetCapabilityKind::supports_readiness_check));

    std::vector<TPolicyTargetCapabilityKind> required{
        TPolicyTargetCapabilityKind::accepts_policy_assignment,
        TPolicyTargetCapabilityKind::supports_readiness_check
    };
    assert(set.Satisfies(required));
    assert(set.Missing(required).empty());

    std::vector<TPolicyTargetCapabilityKind> missing_required{
        TPolicyTargetCapabilityKind::accepts_policy_assignment,
        TPolicyTargetCapabilityKind::has_safe_replacement_point
    };
    auto missing = set.Missing(missing_required);
    assert(missing.size() == 1);
    assert(missing.front() == TPolicyTargetCapabilityKind::has_safe_replacement_point);

    auto ok = TPolicyTargetCompatibilityReport::Compatible(TPolicyTargetKind::dispatcher);
    assert(ok.IsPositive());
    assert(!ok.IsBlocking());

    auto bad = TPolicyTargetCompatibilityReport::Missing(TPolicyTargetKind::dispatcher, missing);
    assert(!bad.IsPositive());
    assert(bad.IsBlocking());
    assert(bad.HasMissingCapabilities());

    return 0;
}
