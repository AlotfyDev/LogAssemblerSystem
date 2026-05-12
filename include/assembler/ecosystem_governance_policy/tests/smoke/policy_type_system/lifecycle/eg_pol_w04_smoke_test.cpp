#include <cassert>

#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleState.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyActivationState.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicySuspensionState.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyRetirementState.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleMarker.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleTransition.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleSnapshot.hpp>
#include <assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleView.hpp>

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;

    static_assert(IsKnown(TPolicyLifecycleState::active), "active state is known");
    static_assert(!IsTerminal(TPolicyLifecycleState::active), "active state is not terminal");
    static_assert(IsTerminal(TPolicyLifecycleState::retired), "retired state is terminal");
    static_assert(IsUsableForAssignment(TPolicyLifecycleState::available), "available can be assigned");

    constexpr TPolicyId policyId{42};
    constexpr TPolicyLifecycleMarker marker{policyId, TPolicyLifecycleState::active, 7};
    static_assert(marker.IsStructurallyUsable(), "marker is structurally usable");

    constexpr TPolicyLifecycleSnapshot snapshot{marker};
    static_assert(snapshot.IsActive(), "snapshot is active");
    static_assert(!snapshot.IsRetired(), "snapshot is not retired");

    constexpr TPolicyLifecycleView view{snapshot};
    static_assert(view.IsActive(), "view exposes active lifecycle");
    static_assert(view.CanBeAssigned(), "active policy can remain assignment-visible");

    constexpr TPolicyLifecycleTransition publish{
        TPolicyLifecycleState::draft,
        TPolicyLifecycleState::available,
        TPolicyLifecycleTransitionKind::publish};
    static_assert(IsConservativeLifecycleTransition(publish), "draft to available publish is conservative");

    constexpr TPolicyLifecycleTransition invalidTransition{
        TPolicyLifecycleState::retired,
        TPolicyLifecycleState::active,
        TPolicyLifecycleTransitionKind::activate};
    static_assert(!IsConservativeLifecycleTransition(invalidTransition), "retired cannot activate directly");

    assert(view.PolicyId().IsValid());
    assert(view.State() == TPolicyLifecycleState::active);

    return 0;
}
