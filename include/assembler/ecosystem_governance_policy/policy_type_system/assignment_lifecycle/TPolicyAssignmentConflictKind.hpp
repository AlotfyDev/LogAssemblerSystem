#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentConflictKind.hpp

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
 *   TPolicyAssignmentConflictKind classifies conflicts that may block or
 *   qualify assignment activation. It names same-family, scope-overlap,
 *   clause, lifecycle, replacement, priority, authority, target-capability,
 *   registry-version, fallback, realization, and boundary conflicts. It does
 *   not resolve conflicts or make incompatible assignments compatible.
 */
enum class TPolicyAssignmentConflictKind : std::uint8_t
{
    none = 0,
    same_family_conflict = 1,
    scope_overlap_conflict = 2,
    clause_conflict = 3,
    lifecycle_conflict = 4,
    replacement_conflict = 5,
    priority_conflict = 6,
    authority_conflict = 7,
    target_capability_conflict = 8,
    registry_version_conflict = 9,
    fallback_conflict = 10,
    realization_conflict = 11,
    boundary_conflict = 12,
    custom = 255
};

enum class TPolicyAssignmentConflictSeverity : std::uint8_t
{
    info = 0,
    warning = 1,
    blocking = 2,
    critical = 3,
    forbidden = 4
};

[[nodiscard]] constexpr bool BlocksActivation(TPolicyAssignmentConflictSeverity severity) noexcept
{
    return severity == TPolicyAssignmentConflictSeverity::blocking ||
           severity == TPolicyAssignmentConflictSeverity::critical ||
           severity == TPolicyAssignmentConflictSeverity::forbidden;
}

} // namespace assembler::ecosystem_governance::policy_type_system
