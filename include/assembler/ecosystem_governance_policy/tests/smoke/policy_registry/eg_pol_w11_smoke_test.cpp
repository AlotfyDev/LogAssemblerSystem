#include <cassert>

#include "assembler/ecosystem_governance/policy_registry/TPolicyRegistry.hpp"
#include "assembler/ecosystem_governance/policy_registry/TPolicyRegistryEntryDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicy.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicyBuildRequest.hpp"

using namespace assembler::ecosystem_governance;
using namespace assembler::ecosystem_governance::policy_type_system;
using namespace assembler::ecosystem_governance::policy_registry;

int main()
{
    TPolicyBuildRequest request{};
    request.policy_id = TPolicyId{1001};
    request.family_id = TPolicyFamilyId{21};
    request.version = TPolicyVersion{1, 0, 0};
    request.scope = TPolicyScope::component;
    request.source = TPolicySource{7};

    TPolicy policy{request};
    auto snapshot = policy.Snapshot();
    auto descriptor = TPolicyRegistryEntryDescriptor::FromSnapshot(
        TPolicyRegistryEntryId{501}, snapshot, TPolicyRegistryEntryStatus::registered);

    TPolicyRegistry<4> registry{};
    assert(registry.Empty());
    assert(registry.AddDescriptor(descriptor));
    assert(!registry.Empty());
    assert(registry.Size() == 1);

    auto by_id = registry.Lookup(TPolicyRegistryLookupKey::ByPolicyId(TPolicyId{1001}));
    assert(by_id.IsFound());
    assert(by_id.descriptor.entry_id == TPolicyRegistryEntryId{501});

    auto by_family = registry.Lookup(TPolicyRegistryLookupKey::ByFamilyVersion(TPolicyFamilyId{21}, TPolicyVersion{1, 0, 0}, TPolicyScope::component));
    assert(by_family.IsFound());

    auto missing = registry.Lookup(TPolicyRegistryLookupKey::ByPolicyId(TPolicyId{9999}));
    assert(!missing.IsFound());

    auto view = registry.View();
    assert(view.Size() == 1);
    assert(view.Capacity() == 4);
    return 0;
}
