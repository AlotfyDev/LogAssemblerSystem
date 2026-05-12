#pragma once

#include <cstdint>
#include "TPolicyRealizationBindingId.hpp"
#include "TPolicyMechanismDescriptor.hpp"
#include "TPolicyTargetKindDescriptor.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationDescriptor.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationDescriptor packages the descriptive realization metadata
 *   for a policy binding: binding identity, mechanism descriptor, optional
 *   target-kind descriptor, and descriptor-level flags. It is the reviewable
 *   description of how realization is expected to be connected later.
 *
 * Why this file exists in W06:
 *   W06 must provide realization binding semantics without creating a realizer
 *   or invoking target objects. This descriptor acts as the safe, non-executable
 *   carrier that later TPolicy, graph nodes, assignments, and registries may
 *   reference.
 *
 * Relationship to previous waves:
 *   - W01 policy identity gives the subject that may use this descriptor.
 *   - W03 replacement structures may later evaluate whether this descriptor may
 *     be replaced.
 *   - W04 lifecycle state may later condition descriptor activation.
 *   - W05 observation may refer to descriptor selection or review events.
 *
 * Relationship to other files in this wave:
 *   - TPolicyMechanismDescriptor supplies mechanism family and mode.
 *   - TPolicyTargetKindDescriptor supplies expected target class.
 *   - TPolicyRealizationBinding uses this descriptor as its binding payload.
 *
 * Relationship to future waves:
 *   - W07 policy graph may attach this descriptor to realization-binding nodes.
 *   - W09 TPolicy may validate descriptor completeness.
 *   - W10 policy assignment may pair this descriptor with assignment metadata.
 *
 * Explicit non-responsibilities:
 *   TPolicyRealizationDescriptor is not an execution plan, not a traversal path,
 *   not a communication binding, not an endpoint binding, not a target instance,
 *   and not evidence that realization has completed.
 *
 * Current implementation note:
 *   W06 keeps this descriptor simple and constexpr-friendly. Later waves can add
 *   richer descriptor validation while preserving the non-execution boundary.
 */
struct TPolicyRealizationDescriptor final
{
    TPolicyRealizationBindingId binding_id{};
    TPolicyMechanismDescriptor mechanism{};
    TPolicyTargetKindDescriptor target_kind{};
    std::uint32_t descriptor_flags{0};

    constexpr TPolicyRealizationDescriptor() noexcept = default;

    constexpr TPolicyRealizationDescriptor(
        TPolicyRealizationBindingId id,
        TPolicyMechanismDescriptor mech,
        TPolicyTargetKindDescriptor target = {},
        std::uint32_t flags = 0) noexcept
        : binding_id(id), mechanism(mech), target_kind(target), descriptor_flags(flags) {}

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return binding_id.IsValid() && mechanism.IsStructurallyComplete();
    }

    [[nodiscard]] constexpr bool HasTargetKind() const noexcept
    {
        return target_kind.IsStructurallyComplete();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
