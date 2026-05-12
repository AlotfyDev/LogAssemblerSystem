#include <cstdint>
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBinding.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBindingView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationResult.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyStatus.hpp"

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    TPolicyMechanismDescriptor mechanism{77, 3, TPolicyRealizationMode::external_mechanism, 0x03u};
    if (!mechanism.IsStructurallyComplete()) { return 1; }
    if (!mechanism.HasCapability(0x01u)) { return 2; }

    TPolicyTargetKindDescriptor target{TPolicyTargetKind::dispatcher, 88, 99};
    if (!target.IsStructurallyComplete()) { return 3; }
    if (!target.HasSurface()) { return 4; }

    TPolicyRealizationDescriptor descriptor{TPolicyRealizationBindingId{42}, mechanism, target, 0x01u};
    if (!descriptor.IsStructurallyComplete()) { return 5; }
    if (!descriptor.HasTargetKind()) { return 6; }

    TPolicyRealizationBinding binding{
        TPolicyId{1001},
        TPolicyFamilyId{2002},
        descriptor,
        TPolicyLifecycleState::available,
        TPolicyReplacementEligibility::eligible,
        TPolicyTraceRef{55},
        0x01u};

    if (!binding.IsStructurallyComplete()) { return 7; }
    if (!binding.HasTargetKind()) { return 8; }
    if (!binding.HasTrace()) { return 9; }
    if (!binding.AllowsReplacement()) { return 10; }

    TPolicyRealizationBindingView view{&binding};
    if (!view.IsStructurallyComplete()) { return 11; }
    if (view.PolicyId() != TPolicyId{1001}) { return 12; }
    if (view.BindingId() != TPolicyRealizationBindingId{42}) { return 13; }
    if (view.Mode() != TPolicyRealizationMode::external_mechanism) { return 14; }
    if (view.TargetKind() != TPolicyTargetKind::dispatcher) { return 15; }
    if (view.LifecycleState() != TPolicyLifecycleState::available) { return 16; }
    if (view.ReplacementEligibility() != TPolicyReplacementEligibility::eligible) { return 17; }

    TPolicyRealizationResult result{TPolicyResult::Success(), TPolicyRealizationBindingId{42}, view.Mode(), view.TargetKind(), 0};
    if (!result.Succeeded()) { return 18; }
    if (result.Failed()) { return 19; }

    constexpr TPolicyRealizationBindingView empty{};
    if (empty.IsPresent()) { return 20; }
    if (empty.IsStructurallyComplete()) { return 21; }

    return 0;
}
