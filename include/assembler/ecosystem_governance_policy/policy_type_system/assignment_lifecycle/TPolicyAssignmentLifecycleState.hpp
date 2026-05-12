#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentLifecycleState.hpp

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
 *   TPolicyAssignmentLifecycleState defines the governed lifecycle states of a
 *   policy assignment relation. It separates assignment states such as proposed,
 *   compatibility pending, ready for activation, active, suspended, pending
 *   replacement, revoked, retired, invalid, quarantined, deferred, and expired.
 *   These states describe governance eligibility only; even active does not
 *   execute the policy or mutate a target.
 */
enum class TPolicyAssignmentLifecycleState : std::uint8_t
{
    unknown = 0,
    draft = 1,
    proposed = 2,
    compatibility_pending = 3,
    compatibility_failed = 4,
    authority_pending = 5,
    authority_rejected = 6,
    conflict_pending = 7,
    conflict_blocked = 8,
    ready_for_activation = 9,
    active = 10,
    suspended = 11,
    pending_replacement = 12,
    replaced = 13,
    revoked = 14,
    retired = 15,
    invalid = 16,
    quarantined = 17,
    deferred = 18,
    expired = 19
};

[[nodiscard]] constexpr bool IsTerminal(TPolicyAssignmentLifecycleState state) noexcept
{
    return state == TPolicyAssignmentLifecycleState::compatibility_failed ||
           state == TPolicyAssignmentLifecycleState::authority_rejected ||
           state == TPolicyAssignmentLifecycleState::conflict_blocked ||
           state == TPolicyAssignmentLifecycleState::replaced ||
           state == TPolicyAssignmentLifecycleState::revoked ||
           state == TPolicyAssignmentLifecycleState::retired ||
           state == TPolicyAssignmentLifecycleState::invalid ||
           state == TPolicyAssignmentLifecycleState::expired;
}

[[nodiscard]] constexpr bool MayGovern(TPolicyAssignmentLifecycleState state) noexcept
{
    return state == TPolicyAssignmentLifecycleState::active ||
           state == TPolicyAssignmentLifecycleState::pending_replacement;
}

[[nodiscard]] constexpr bool MayPlanRealization(TPolicyAssignmentLifecycleState state) noexcept
{
    return state == TPolicyAssignmentLifecycleState::ready_for_activation ||
           state == TPolicyAssignmentLifecycleState::active ||
           state == TPolicyAssignmentLifecycleState::pending_replacement;
}

} // namespace assembler::ecosystem_governance::policy_type_system
