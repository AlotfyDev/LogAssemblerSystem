#pragma once

#include <cstdint>
#include "TPolicyAssignment.hpp"
#include "TPolicyAssignmentView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentResult.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignmentResult reports whether a policy assignment object is
 *   structurally acceptable as a representation. It carries primitive status,
 *   issue information, and a read-only assignment view so callers can inspect
 *   the relation without executing it.
 *
 * Why this file exists in W10:
 *   Assignment must be reviewable and testable. A result carrier is needed to
 *   explain incomplete assignment id, missing policy identity, missing target
 *   reference, or unusable assignment status without introducing exceptions,
 *   logging frameworks, registry persistence, or runtime execution.
 *
 * Relationship to previous waves:
 *   - W01 primitive TPolicyStatus/TPolicyIssue are reused for compact reporting.
 *   - W09 policy validation remains separate from assignment result; this file
 *     validates the assignment relation, not the full policy constitution.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignment is the subject of this result.
 *   - TPolicyAssignmentView is embedded for read-only reporting.
 *
 * Relationship to future waves:
 *   - W11 registry basics may use this result when accepting registry-facing
 *     assignment descriptors.
 *   - Future diagnostics may translate this result into audit evidence, but the
 *     result itself is not an audit exporter.
 *
 * Explicit non-responsibilities:
 *   TPolicyAssignmentResult does not execute assignment, does not invoke a
 *   target, does not register a policy, does not persist audit records, and does
 *   not open communication or material circulation paths.
 *
 * Current implementation note:
 *   The missing mask uses stable bit positions so smoke tests and later review
 *   layers can reason about incomplete assignments without string diagnostics.
 */
struct TPolicyAssignmentResult final
{
    enum missing_bits : TPolicyIssue::code_type
    {
        missing_assignment_id = 1u,
        missing_policy_identity = 2u,
        missing_target_reference = 4u,
        unusable_status = 8u
    };

    TPolicyStatus status{TPolicyStatus::unknown};
    TPolicyIssue issue{};
    TPolicyAssignmentView view{};

    constexpr TPolicyAssignmentResult() noexcept = default;

    [[nodiscard]] static constexpr TPolicyAssignmentResult FromAssignment(const TPolicyAssignment& assignment) noexcept
    {
        TPolicyAssignmentResult result{};
        result.view = TPolicyAssignmentView{assignment};
        const auto mask = MissingMask(assignment);
        result.status = mask == 0u ? TPolicyStatus::valid : TPolicyStatus::incomplete;
        result.issue = TPolicyIssue{result.status, mask};
        return result;
    }

    [[nodiscard]] static constexpr TPolicyIssue::code_type MissingMask(const TPolicyAssignment& assignment) noexcept
    {
        return (assignment.HasAssignmentIdentity() ? 0u : missing_assignment_id) |
               (assignment.HasPolicyIdentity() ? 0u : missing_policy_identity) |
               (assignment.HasTargetReference() ? 0u : missing_target_reference) |
               (policy_type_system::IsUsable(assignment.status) ? 0u : unusable_status);
    }

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return status == TPolicyStatus::valid;
    }

    [[nodiscard]] constexpr bool HasIssue() const noexcept
    {
        return issue.HasIssue();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
