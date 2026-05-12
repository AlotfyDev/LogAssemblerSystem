#pragma once

#include "TPolicyAssignment.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentView.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignmentView is the read-only projection over an assignment record.
 *   It exposes assignment identity, policy identity, target reference, status,
 *   and structural completeness without granting mutation authority over the
 *   assignment, policy aggregate, or target context.
 *
 * Why this file exists in W10:
 *   Assignment records must be inspectable by later registry, governance, and
 *   validation layers without making those layers mutate assignment state or
 *   resolve target instances. W10 therefore introduces a compact view alongside
 *   the assignment value carrier.
 *
 * Relationship to previous waves:
 *   - W09 TPolicyView is policy-facing. TPolicyAssignmentView is relation-facing.
 *   - W06 target-kind descriptors remain descriptive when viewed through this
 *     file.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignment produces or can be represented by this view.
 *   - TPolicyAssignmentResult may contain this view later if richer reporting is
 *     needed.
 *
 * Relationship to future waves:
 *   - W11 registry basics may expose this view in lookup results or registry
 *     entry descriptors.
 *
 * Explicit non-responsibilities:
 *   TPolicyAssignmentView does not mutate, assign, execute, register, invoke,
 *   traverse, schedule, or resolve target objects.
 *
 * Current implementation note:
 *   The view is a by-value copy-safe projection in W10. Later waves may add
 *   pointer-backed views if necessary, but the view must remain read-only.
 */
struct TPolicyAssignmentView final
{
    TPolicyAssignmentId assignment_id{};
    TPolicyId policy_id{};
    TPolicyFamilyId family_id{};
    TPolicyVersion version{};
    TPolicyAssignmentTargetRef target_ref{};
    TPolicyAssignmentStatus status{TPolicyAssignmentStatus::unknown};
    bool structurally_complete{false};

    constexpr TPolicyAssignmentView() noexcept = default;

    explicit constexpr TPolicyAssignmentView(const TPolicyAssignment& assignment) noexcept
        : assignment_id(assignment.assignment_id),
          policy_id(assignment.policy_id),
          family_id(assignment.family_id),
          version(assignment.version),
          target_ref(assignment.target_ref),
          status(assignment.status),
          structurally_complete(assignment.IsStructurallyComplete()) {}

    [[nodiscard]] constexpr bool IsPresent() const noexcept
    {
        return assignment_id.IsValid();
    }

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return structurally_complete;
    }

    [[nodiscard]] constexpr bool IsUsable() const noexcept
    {
        return structurally_complete && policy_type_system::IsUsable(status);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
