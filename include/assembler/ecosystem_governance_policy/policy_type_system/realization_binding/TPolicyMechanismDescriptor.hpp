#pragma once

#include <cstdint>
#include "TPolicyRealizationMode.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyMechanismDescriptor.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyMechanismDescriptor describes the mechanism family that may later
 *   realize a policy. It is a descriptive carrier for mechanism identity, mode,
 *   family, and revision hints. It is not the mechanism object and does not
 *   execute policy behavior.
 *
 * Why this file exists in W06:
 *   The Policy Object taxonomy says a policy object is assigned a realization
 *   mechanism and that the mechanism acts on an external target object. W06
 *   needs a descriptor for that mechanism assignment without introducing the
 *   realizer or importing target component code.
 *
 * Relationship to previous waves:
 *   - W01 provides policy identity primitives that can be associated with this
 *     descriptor through a binding.
 *   - W02 clauses are the content a mechanism may later realize, but this file
 *     does not inspect them.
 *   - W03 replacement structures may later constrain mechanism replacement.
 *   - W04 lifecycle may later constrain whether a mechanism descriptor is active.
 *   - W05 observation can record descriptor-selection evidence.
 *
 * Relationship to other files in this wave:
 *   - TPolicyRealizationDescriptor includes this mechanism descriptor.
 *   - TPolicyRealizationBinding combines this mechanism descriptor with a policy
 *     identity and an optional target-kind descriptor.
 *
 * Relationship to future waves:
 *   - W07 graph structure may represent this as the payload of a mechanism
 *     binding node.
 *   - W09 TPolicy may validate that a descriptor is structurally complete.
 *
 * Explicit non-responsibilities:
 *   TPolicyMechanismDescriptor is not an executor, not a callable, not a function
 *   pointer, not a service locator entry, not a dependency-injection handle, and
 *   not a bridge or port binding.
 *
 * Current implementation note:
 *   W06 uses numeric descriptor fields. Later waves may introduce richer names,
 *   catalogs, or registry-backed descriptors while preserving non-execution.
 */
struct TPolicyMechanismDescriptor final
{
    std::uint64_t mechanism_family_code{0};
    std::uint64_t mechanism_revision{0};
    TPolicyRealizationMode mode{TPolicyRealizationMode::unknown};
    std::uint32_t capability_flags{0};

    constexpr TPolicyMechanismDescriptor() noexcept = default;

    constexpr TPolicyMechanismDescriptor(
        std::uint64_t family,
        std::uint64_t revision,
        TPolicyRealizationMode realization_mode,
        std::uint32_t flags = 0) noexcept
        : mechanism_family_code(family), mechanism_revision(revision), mode(realization_mode), capability_flags(flags) {}

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return mechanism_family_code != 0 && IsKnown(mode);
    }

    [[nodiscard]] constexpr bool HasCapability(std::uint32_t mask) const noexcept
    {
        return (capability_flags & mask) == mask;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
