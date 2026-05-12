#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentId.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignmentId is the primitive identity token for a policy assignment
 *   record. It identifies the relation by which a policy is associated with a
 *   policy-consuming target context without identifying, owning, or invoking the
 *   target itself. It exists so assignment material can be traced, viewed,
 *   diagnosed, and later cataloged independently from the TPolicy aggregate and
 *   independently from the target object.
 *
 * Why this file exists in W10:
 *   W10 is the first wave after the TPolicy aggregate where assignment may be
 *   represented. The policy object can now exist as a complete semantic
 *   governing aggregate, so the next dependency-safe step is to model the
 *   assignment relation that points a policy toward an external target context.
 *   That relation needs its own identity before statuses, target references,
 *   views, results, or registry entries are introduced.
 *
 * Relationship to previous waves:
 *   - W01 TPolicyId identifies the policy being assigned.
 *   - W09 TPolicy/TPolicyView provide the policy aggregate or read-only policy
 *     surface referenced by an assignment.
 *   - W06 target-kind descriptors help describe what kind of target context is
 *     expected, but do not become assignment identity.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignment uses this identifier as its stable assignment identity.
 *   - TPolicyAssignmentView exposes it read-only.
 *   - TPolicyAssignmentResult may report whether an assignment object was
 *     structurally accepted.
 *
 * Relationship to future waves:
 *   - W11 policy registry basics may index assignment-facing descriptors by
 *     this id or link policy registry entries to assignment records.
 *   - Later governance/reporting layers may use this id for audit and review.
 *
 * Explicit non-responsibilities:
 *   This file does not assign policies by itself, does not store policies, does
 *   not own target objects, does not invoke realization mechanisms, does not
 *   execute policy logic, and does not represent communication bindings.
 *
 * Current implementation note:
 *   W10 intentionally keeps the id as a compact numeric value object. Richer
 *   generation, namespace, or provenance-backed assignment identities can be
 *   added later without changing the semantic role of this type.
 */
struct TPolicyAssignmentId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyAssignmentId() noexcept = default;
    explicit constexpr TPolicyAssignmentId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyAssignmentId Invalid() noexcept { return TPolicyAssignmentId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyAssignmentId lhs, TPolicyAssignmentId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyAssignmentId lhs, TPolicyAssignmentId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyAssignmentId lhs, TPolicyAssignmentId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
