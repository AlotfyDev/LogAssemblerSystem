#pragma once

#include <string>
#include <utility>
#include <vector>
#include "TPolicyAssignmentLifecycleState.hpp"
#include "TPolicyAssignmentTransitionKind.hpp"
#include "TPolicyAssignmentResolution.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentLifecycleView.hpp

 * Wave: EG-POL-W15_Assignment_Lifecycle_And_Conflict
 * Domain: ecosystem_governance / policy_type_system / assignment_lifecycle
 *
 * Architectural boundary:
 *   W15 implements the first assignment lifecycle and conflict vocabulary layer
 *   derived from EG-POL-ARCH-004_Assignment_Lifecycle_And_Conflict_Model. It
 *   follows W10 Assignment Basics, W12 Policy Family And Scope, W13 Target
 *   Capability Contracts, and W14 Family Target Compatibility Matrix. The wave
 *   remains descriptive and non-executing: it defines lifecycle states,
 *   transition vocabulary, conflict carriers, resolution carriers, and views
 *   without activating assignments, invoking targets, realizing policies, or
 *   mutating runtime components.
 *
 * Relationship to prior waves:
 *   - W01 supplies policy identity and scope primitives.
 *   - W04 supplies policy-object lifecycle vocabulary; W15 defines lifecycle
 *     for the assignment relation, not for the policy object itself.
 *   - W06 supplies target-kind and realization-binding descriptors while
 *     preserving the descriptor-only boundary.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics; W15 extends assignment with
 *     lifecycle, conflict, and resolution structure.
 *   - W11 supplies registry basics; W15 may reference registry readiness later
 *     but does not become a registry or service locator.
 *   - W12, W13, and W14 supply family/scope, target capabilities, and
 *     compatibility reports that are preconditions for assignment activation.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-004 states that assignment lifecycle is distinct from
 *   compatibility, realization, target ownership, and runtime mutation. This
 *   wave implements the first C++17 value vocabulary for those rules while
 *   preserving the non-execution boundary.
 *
 * Explicit non-responsibilities:
 *   This file does not implement authority roles, source publication, registry
 *   versioning, realization contracts, runtime readiness, TPolicyRealizer,
 *   TPolicyExecutor, target invocation, material circulation behavior,
 *   communication binding, add-on execution, telemetry, logging, or
 *   persistence.
 *
 * Current implementation posture:
 *   The current code is a conservative C++17 header-only foundation. The
 *   opening documentation describes the complete architectural responsibility,
 *   while the code intentionally remains a small set of value carriers and
 *   structural helpers.
 * File responsibility:
 *   TPolicyAssignmentLifecycleView exposes a read-only snapshot of an
 *   assignment relation's lifecycle state, last transition, detected conflicts,
 *   resolution state, and key evidence references. It is designed for review,
 *   reporting, and later compliance checks. It does not mutate assignment
 *   state, activate assignments, resolve conflicts, invoke targets, or realize
 *   policy behavior.
 */
struct TPolicyAssignmentLifecycleView final
{
    std::string assignment_ref{};
    std::string policy_ref{};
    std::string target_ref{};
    TPolicyAssignmentLifecycleState state{TPolicyAssignmentLifecycleState::unknown};
    TPolicyAssignmentTransitionKind last_transition{TPolicyAssignmentTransitionKind::none};
    TPolicyAssignmentResolution resolution{};
    std::vector<TPolicyAssignmentConflict> conflicts{};
    std::string compatibility_report_ref{};
    std::string authority_ref{};
    std::string audit_ref{};

    [[nodiscard]] bool HasBlockingConflict() const noexcept
    {
        for (const auto& conflict : conflicts)
        {
            if (conflict.BlocksActivation())
            {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool MayGovern() const noexcept
    {
        return assembler::ecosystem_governance::policy_type_system::MayGovern(state) &&
               !HasBlockingConflict();
    }

    [[nodiscard]] bool ReadyForActivation() const noexcept
    {
        return state == TPolicyAssignmentLifecycleState::ready_for_activation &&
               !HasBlockingConflict() &&
               resolution.AllowsActivation();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
