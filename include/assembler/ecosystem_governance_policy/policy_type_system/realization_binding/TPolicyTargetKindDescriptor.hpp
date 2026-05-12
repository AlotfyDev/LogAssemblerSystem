#pragma once

#include <cstdint>
#include "TPolicyTargetKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetKindDescriptor.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyTargetKindDescriptor describes the expected category of external
 *   target for a realization mechanism. It may record a target-kind, surface
 *   code, and compatibility family without naming or owning a concrete target
 *   instance.
 *
 * Why this file exists in W06:
 *   The structural policy graph allows a Realization Mechanism Binding Node to
 *   point to a Target-Kind Descriptor Node. W06 provides the C++ foundation for
 *   that descriptor while preserving the rule that target objects stay outside
 *   policy ownership.
 *
 * Relationship to previous waves:
 *   - W01 identity enables traceability of policies that use target-kind data.
 *   - W03 replacement may later constrain target-kind descriptor changes.
 *   - W04 lifecycle may later decide when a target-kind expectation is usable.
 *   - W05 observation may record the evidence for target-kind selection.
 *
 * Relationship to other files in this wave:
 *   - TPolicyRealizationBinding optionally embeds this descriptor.
 *   - TPolicyRealizationBindingView exposes it without exposing target instances.
 *
 * Relationship to future waves:
 *   - W07 graph structure may formalize this descriptor as a graph node.
 *   - W10 assignment may relate this descriptor to an actual assignment target,
 *     while keeping that target external to the policy object.
 *
 * Explicit non-responsibilities:
 *   TPolicyTargetKindDescriptor is not a target pointer, not a target handle, not
 *   a component reference, not a communication participant, and not a permission
 *   to invoke anything.
 *
 * Current implementation note:
 *   W06 uses target kind plus numeric surface/compatibility codes. Richer target
 *   descriptors may be derived later without changing this file's ownership.
 */
struct TPolicyTargetKindDescriptor final
{
    TPolicyTargetKind kind{TPolicyTargetKind::unknown};
    std::uint64_t target_surface_code{0};
    std::uint64_t compatibility_family_code{0};

    constexpr TPolicyTargetKindDescriptor() noexcept = default;

    constexpr TPolicyTargetKindDescriptor(
        TPolicyTargetKind target_kind,
        std::uint64_t surface = 0,
        std::uint64_t compatibility_family = 0) noexcept
        : kind(target_kind), target_surface_code(surface), compatibility_family_code(compatibility_family) {}

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return IsKnown(kind);
    }

    [[nodiscard]] constexpr bool HasSurface() const noexcept
    {
        return target_surface_code != 0;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
