#include <cassert>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentTransitionKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentConflictKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentConflict.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentResolution.hpp"
#include "assembler/ecosystem_governance/policy_type_system/assignment_lifecycle/TPolicyAssignmentLifecycleView.hpp"

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;

    static_assert(MayGovern(TPolicyAssignmentLifecycleState::active), "active may govern");
    static_assert(MayPlanRealization(TPolicyAssignmentLifecycleState::ready_for_activation), "ready may plan");
    static_assert(IsTerminal(TPolicyAssignmentLifecycleState::revoked), "revoked is terminal");
    static_assert(RequiresRevalidation(TPolicyAssignmentTransitionKind::activate_assignment), "activation requires validation");

    auto warning = TPolicyAssignmentConflict::Warning(
        TPolicyAssignmentConflictKind::scope_overlap_conflict,
        "assignment-A",
        "narrower scope review required");
    assert(!warning.BlocksActivation());

    auto blocking = TPolicyAssignmentConflict::Blocking(
        TPolicyAssignmentConflictKind::target_capability_conflict,
        "assignment-B",
        "required target capability is missing");
    assert(blocking.BlocksActivation());

    TPolicyAssignmentLifecycleView blocked_view{
        "assignment-B",
        "policy-X",
        "target-Y",
        TPolicyAssignmentLifecycleState::ready_for_activation,
        TPolicyAssignmentTransitionKind::accept_compatibility,
        TPolicyAssignmentResolution::Unresolved(blocking, "must resolve capability conflict"),
        std::vector<TPolicyAssignmentConflict>{blocking},
        "compat-report-1",
        "authority-1",
        "audit-1"
    };
    assert(blocked_view.HasBlockingConflict());
    assert(!blocked_view.ReadyForActivation());

    TPolicyAssignmentLifecycleView clear_view{
        "assignment-A",
        "policy-X",
        "target-Y",
        TPolicyAssignmentLifecycleState::ready_for_activation,
        TPolicyAssignmentTransitionKind::clear_conflict,
        TPolicyAssignmentResolution::Cleared("no blocking conflict remains"),
        std::vector<TPolicyAssignmentConflict>{warning},
        "compat-report-2",
        "authority-2",
        "audit-2"
    };
    assert(!clear_view.HasBlockingConflict());
    assert(clear_view.ReadyForActivation());

    return 0;
}
