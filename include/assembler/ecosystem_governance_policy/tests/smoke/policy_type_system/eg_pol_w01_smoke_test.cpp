#include <cassert>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicySource.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyProvenance.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyStatus.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyIssue.hpp>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyResult.hpp>

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;

    constexpr TPolicyId policyId{1};
    constexpr TPolicyFamilyId familyId{10};
    constexpr TPolicyVersion v1{1, 0, 0};
    constexpr TPolicyVersion v2{1, 1, 0};
    constexpr TPolicyProvenance provenance{TPolicySource::built_in, 42, 84};
    constexpr TPolicyResult ok = TPolicyResult::Success();
    constexpr TPolicyResult bad = TPolicyResult::Failure(TPolicyStatus::invalid, 7);

    static_assert(policyId.IsValid(), "policy id should be valid");
    static_assert(familyId.IsValid(), "family id should be valid");
    static_assert(v1 < v2, "version comparison should work");
    static_assert(IsSpecified(TPolicyScope::component), "scope should be specified");
    static_assert(IsSpecified(TPolicySource::built_in), "source should be specified");
    static_assert(provenance.HasSource(), "provenance should have source");
    static_assert(provenance.HasSourceToken(), "provenance should have source token");
    static_assert(provenance.HasEvidenceToken(), "provenance should have evidence token");
    static_assert(ok.Ok(), "success result should be ok");
    static_assert(!bad.Ok(), "failure result should not be ok");
    static_assert(bad.issue.HasIssue(), "failure result should contain issue");

    assert(policyId.value == 1);
    assert(familyId.value == 10);
    assert(v2.major == 1);
    return 0;
}
