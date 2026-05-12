#include <cassert>

#include "assembler/ecosystem_governance/policy_type_system/assignment/TPolicyAssignment.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment/TPolicyAssignmentResult.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment/TPolicyAssignmentView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicy.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyBuildRequest request{};
    request.policy_id = TPolicyId{1001};
    request.family_id = TPolicyFamilyId{2002};
    request.version = TPolicyVersion{1, 0, 0};
    request.scope = TPolicyScope::component;
    request.source = TPolicySource::test;
    request.provenance = TPolicyProvenance{TPolicySource::test, 3003, 4004};

    TPolicy policy = TPolicy::FromRequest(request);

    TPolicyAssignmentTargetRef target{
        TPolicyTargetKindDescriptor{TPolicyTargetKind::dispatcher, 7007, 8008},
        9009,
        1010};

    TPolicyAssignment assignment = TPolicyAssignment::FromPolicy(
        TPolicyAssignmentId{5005},
        policy,
        target,
        TPolicyAssignmentStatus::ready);

    assert(assignment.HasAssignmentIdentity());
    assert(assignment.HasPolicyIdentity());
    assert(assignment.HasTargetReference());
    assert(assignment.IsStructurallyComplete());
    assert(assignment.IsUsableAssignment());

    TPolicyAssignmentView view{assignment};
    assert(view.IsPresent());
    assert(view.IsStructurallyComplete());
    assert(view.IsUsable());
    assert(view.policy_id == TPolicyId{1001});

    auto result = TPolicyAssignmentResult::FromAssignment(assignment);
    assert(result.IsValid());
    assert(!result.HasIssue());
    assert(result.view.assignment_id == TPolicyAssignmentId{5005});

    TPolicyAssignment incomplete{};
    auto bad = TPolicyAssignmentResult::FromAssignment(incomplete);
    assert(!bad.IsValid());
    assert(bad.HasIssue());
    assert((bad.issue.code & TPolicyAssignmentResult::missing_assignment_id) != 0u);
    assert((bad.issue.code & TPolicyAssignmentResult::missing_policy_identity) != 0u);
    assert((bad.issue.code & TPolicyAssignmentResult::missing_target_reference) != 0u);

    TPolicyAssignment from_view = TPolicyAssignment::FromPolicyView(
        TPolicyAssignmentId{6006},
        policy.View(),
        target,
        TPolicyAssignmentStatus::active);

    assert(from_view.policy_id == TPolicyId{1001});
    assert(from_view.IsUsableAssignment());

    return 0;
}
