#pragma once

#include "TPolicyAssignmentId.hpp"
#include "TPolicyAssignmentStatus.hpp"
#include "TPolicyAssignmentTargetRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicy.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_core/TPolicyView.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignment.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignment is the basic non-executing relation that associates a
 *   policy identity with an external target context. It records assignment id,
 *   policy id/family/version, target reference, and assignment status. It may be
 *   constructed from a TPolicy or TPolicyView, but it deliberately stores only
 *   policy identity and target reference material, not the full policy object.
 *
 * Why this file exists in W10:
 *   After W09 introduced the TPolicy aggregate, the next safe layer is the
 *   assignment relation. Assignment is necessary so a policy can become directed
 *   toward a consuming target context without making the policy itself an
 *   executor and without making the target object part of policy ownership.
 *
 * Relationship to previous waves:
 *   - W01 identity primitives identify assigned policy material.
 *   - W06 target-kind descriptors describe expected target kind.
 *   - W09 TPolicy/TPolicyView provide the source identity for assignment.
 *   - W03/W04/W05 remain policy semantics; assignment does not absorb them.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignmentId identifies this assignment relation.
 *   - TPolicyAssignmentTargetRef describes the non-owning target context.
 *   - TPolicyAssignmentStatus classifies the assignment relation state.
 *   - TPolicyAssignmentView provides read-only projection.
 *   - TPolicyAssignmentResult reports construction or validation outcome.
 *
 * Relationship to future waves:
 *   - W11 policy registry basics may catalog policy assignments or registry
 *     descriptors that point to assignments.
 *   - A future realization layer may consume assignment records, but must keep
 *     execution outside this type.
 *
 * Explicit non-responsibilities:
 *   TPolicyAssignment does not execute a policy, does not realize a policy,
 *   does not own the target, does not invoke the target, does not traverse the
 *   policy graph, does not register itself globally, does not open
 *   communication bindings, and does not control material circulation.
 *
 * Current implementation note:
 *   W10 is intentionally a value-carrier layer. It records structural assignment
 *   information and basic completeness checks. It is not a runtime assignment
 *   workflow engine.
 */
struct TPolicyAssignment final
{
    TPolicyAssignmentId assignment_id{};
    TPolicyId policy_id{};
    TPolicyFamilyId family_id{};
    TPolicyVersion version{};
    TPolicyAssignmentTargetRef target_ref{};
    TPolicyAssignmentStatus status{TPolicyAssignmentStatus::unknown};

    constexpr TPolicyAssignment() noexcept = default;

    constexpr TPolicyAssignment(
        TPolicyAssignmentId assignment,
        TPolicyId policy,
        TPolicyFamilyId family,
        TPolicyVersion policy_version,
        TPolicyAssignmentTargetRef target,
        TPolicyAssignmentStatus assignment_status = TPolicyAssignmentStatus::drafted) noexcept
        : assignment_id(assignment),
          policy_id(policy),
          family_id(family),
          version(policy_version),
          target_ref(target),
          status(assignment_status) {}

    [[nodiscard]] static TPolicyAssignment FromPolicy(
        TPolicyAssignmentId assignment,
        const TPolicy& policy,
        TPolicyAssignmentTargetRef target,
        TPolicyAssignmentStatus assignment_status = TPolicyAssignmentStatus::drafted) noexcept
    {
        return TPolicyAssignment{
            assignment,
            policy.PolicyId(),
            policy.FamilyId(),
            policy.Version(),
            target,
            assignment_status};
    }

    [[nodiscard]] static constexpr TPolicyAssignment FromPolicyView(
        TPolicyAssignmentId assignment,
        TPolicyView view,
        TPolicyAssignmentTargetRef target,
        TPolicyAssignmentStatus assignment_status = TPolicyAssignmentStatus::drafted) noexcept
    {
        return TPolicyAssignment{
            assignment,
            view.snapshot.policy_id,
            view.snapshot.family_id,
            view.snapshot.version,
            target,
            assignment_status};
    }

    [[nodiscard]] constexpr bool HasAssignmentIdentity() const noexcept
    {
        return assignment_id.IsValid();
    }

    [[nodiscard]] constexpr bool HasPolicyIdentity() const noexcept
    {
        return policy_id.IsValid() && family_id.IsValid() && !version.IsZero();
    }

    [[nodiscard]] constexpr bool HasTargetReference() const noexcept
    {
        return target_ref.IsStructurallyComplete();
    }

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return HasAssignmentIdentity() && HasPolicyIdentity() && HasTargetReference();
    }

    [[nodiscard]] constexpr bool IsUsableAssignment() const noexcept
    {
        return IsStructurallyComplete() && IsUsable(status);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
