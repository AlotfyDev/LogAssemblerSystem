#pragma once

#include <cstdint>
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKindDescriptor.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyAssignmentTargetRef.hpp
 * Wave: EG-POL-W10_Policy_Assignment_Basics
 * Domain: ecosystem_governance / policy_type_system / assignment
 *
 * Full architectural responsibility:
 *   TPolicyAssignmentTargetRef is a non-owning descriptor for the target context
 *   to which a policy assignment is directed. It combines the target-kind
 *   descriptor from W06 with an opaque external target token and an optional
 *   assignment surface code. It describes the assignment target boundary without
 *   storing a pointer, invoking a target, or claiming ownership over a target.
 *
 * Why this file exists in W10:
 *   Assignment must connect a TPolicy to something outside the policy object.
 *   The W06 target-kind descriptor intentionally refused to become a concrete
 *   target reference. W10 adds the assignment-level reference that can name the
 *   external target context opaquely while preserving target non-ownership.
 *
 * Relationship to previous waves:
 *   - W06 provides TPolicyTargetKindDescriptor as target-kind expectation.
 *   - W09 provides TPolicy as the assignable semantic aggregate.
 *   - W01 provides identity primitives for the policy side of the relation.
 *
 * Relationship to other files in this wave:
 *   - TPolicyAssignment embeds this target reference.
 *   - TPolicyAssignmentView exposes it read-only.
 *   - TPolicyAssignmentResult can report failures when this reference is
 *     incomplete.
 *
 * Relationship to future waves:
 *   - Future realizer/executor layers may resolve this target reference using
 *     their own domain-specific rules. That resolution is not W10 authority.
 *   - Policy registries may catalog assignments by target kind or target token.
 *
 * Explicit non-responsibilities:
 *   This file is not a target pointer, not a target handle with lifetime
 *   authority, not a communication participant, not a material circulation
 *   component, and not a permission to invoke any target.
 *
 * Current implementation note:
 *   The opaque token is a numeric placeholder. It is intentionally not a raw
 *   pointer. Later integration layers may map it to domain-specific references.
 */
struct TPolicyAssignmentTargetRef final
{
    TPolicyTargetKindDescriptor target_kind{};
    std::uint64_t external_target_token{0};
    std::uint64_t assignment_surface_code{0};

    constexpr TPolicyAssignmentTargetRef() noexcept = default;

    constexpr TPolicyAssignmentTargetRef(
        TPolicyTargetKindDescriptor descriptor,
        std::uint64_t target_token,
        std::uint64_t surface_code = 0) noexcept
        : target_kind(descriptor),
          external_target_token(target_token),
          assignment_surface_code(surface_code) {}

    [[nodiscard]] constexpr bool HasTargetToken() const noexcept
    {
        return external_target_token != 0;
    }

    [[nodiscard]] constexpr bool HasSurfaceCode() const noexcept
    {
        return assignment_surface_code != 0;
    }

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return target_kind.IsStructurallyComplete() && HasTargetToken();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
