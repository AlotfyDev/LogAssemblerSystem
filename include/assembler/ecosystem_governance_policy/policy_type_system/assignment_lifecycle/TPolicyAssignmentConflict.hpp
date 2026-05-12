#pragma once

#include <string>
#include <utility>
#include "TPolicyAssignmentConflictKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentConflict.hpp

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
 *   TPolicyAssignmentConflict is the value carrier that records a conflict
 *   detected during assignment lifecycle review. It captures conflict kind,
 *   severity, subject references, and a human-readable explanation so later
 *   assignment lifecycle views and compliance reports can block activation or
 *   request governance review without executing the policy.
 */
struct TPolicyAssignmentConflict final
{
    TPolicyAssignmentConflictKind kind{TPolicyAssignmentConflictKind::none};
    TPolicyAssignmentConflictSeverity severity{TPolicyAssignmentConflictSeverity::info};
    std::string primary_assignment_ref{};
    std::string related_assignment_ref{};
    std::string message{};

    [[nodiscard]] bool BlocksActivation() const noexcept
    {
        return assembler::ecosystem_governance::policy_type_system::BlocksActivation(severity);
    }

    [[nodiscard]] static TPolicyAssignmentConflict Blocking(
        TPolicyAssignmentConflictKind conflict_kind,
        std::string primary_ref,
        std::string note)
    {
        return TPolicyAssignmentConflict{
            conflict_kind,
            TPolicyAssignmentConflictSeverity::blocking,
            std::move(primary_ref),
            {},
            std::move(note)
        };
    }

    [[nodiscard]] static TPolicyAssignmentConflict Warning(
        TPolicyAssignmentConflictKind conflict_kind,
        std::string primary_ref,
        std::string note)
    {
        return TPolicyAssignmentConflict{
            conflict_kind,
            TPolicyAssignmentConflictSeverity::warning,
            std::move(primary_ref),
            {},
            std::move(note)
        };
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
