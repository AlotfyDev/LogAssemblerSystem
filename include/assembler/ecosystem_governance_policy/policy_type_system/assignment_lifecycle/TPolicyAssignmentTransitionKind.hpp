#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentTransitionKind.hpp

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
 *   TPolicyAssignmentTransitionKind names the governed transitions that move an
 *   assignment relation between lifecycle states. It allows later lifecycle
 *   reports and audit records to explain whether an assignment was proposed,
 *   compatibility-checked, activated, suspended, resumed, replaced, revoked,
 *   retired, invalidated, quarantined, or expired. It is transition vocabulary,
 *   not a state machine engine.
 */
enum class TPolicyAssignmentTransitionKind : std::uint8_t
{
    none = 0,
    propose_assignment = 1,
    request_compatibility_check = 2,
    reject_for_incompatibility = 3,
    accept_compatibility = 4,
    request_authority = 5,
    reject_authority = 6,
    accept_authority = 7,
    request_conflict_check = 8,
    block_for_conflict = 9,
    clear_conflict = 10,
    activate_assignment = 11,
    suspend_assignment = 12,
    resume_assignment = 13,
    mark_pending_replacement = 14,
    complete_replacement = 15,
    revoke_assignment = 16,
    retire_assignment = 17,
    invalidate_assignment = 18,
    quarantine_assignment = 19,
    expire_assignment = 20
};

[[nodiscard]] constexpr bool RequiresRevalidation(TPolicyAssignmentTransitionKind transition) noexcept
{
    return transition == TPolicyAssignmentTransitionKind::resume_assignment ||
           transition == TPolicyAssignmentTransitionKind::mark_pending_replacement ||
           transition == TPolicyAssignmentTransitionKind::complete_replacement ||
           transition == TPolicyAssignmentTransitionKind::activate_assignment;
}

} // namespace assembler::ecosystem_governance::policy_type_system
