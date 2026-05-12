#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationMode.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationMode names the descriptive mode by which a policy may be
 *   realized later. It records how the binding expects realization to be shaped,
 *   while explicitly avoiding execution, invocation, or target ownership.
 *
 * Why this file exists in W06:
 *   The policy model distinguishes the policy object from the realization
 *   mechanism. A compact mode vocabulary is required before a binding descriptor
 *   can state whether realization is external, local, injected, delegated,
 *   method-surface-based, or currently unresolved.
 *
 * Relationship to previous waves:
 *   - W01 identity gives the policy subject that may be bound.
 *   - W02 clauses provide the governing content that may be realized.
 *   - W03 replacement may later restrict mode changes.
 *   - W04 lifecycle may later restrict when a binding mode is active.
 *   - W05 observation may record mode-selection evidence.
 *
 * Relationship to other files in this wave:
 *   - TPolicyRealizationBinding and TPolicyRealizationDescriptor contain this
 *     mode to describe the binding.
 *   - TPolicyRealizationBindingView exposes this mode safely.
 *
 * Relationship to future waves:
 *   - W07 graph structure may include a realization-binding node annotated by
 *     this mode.
 *   - W09 TPolicy may validate that a mode is compatible with policy family.
 *
 * Explicit non-responsibilities:
 *   TPolicyRealizationMode is not an executor type, not a dispatch strategy,
 *   not a function pointer category, not a runtime scheduler, and not evidence
 *   that a policy has been applied.
 *
 * Current implementation note:
 *   W06 uses an enum so later waves can reason about binding shape without
 *   importing realizer or target implementation.
 */
enum class TPolicyRealizationMode : std::uint8_t
{
    unknown = 0,
    external_mechanism = 1,
    local_mechanism = 2,
    injected_callable_family = 3,
    delegated_executor_path = 4,
    bound_method_surface = 5,
    descriptive_only = 6
};

[[nodiscard]] constexpr bool IsKnown(TPolicyRealizationMode mode) noexcept
{
    return mode != TPolicyRealizationMode::unknown;
}

[[nodiscard]] constexpr bool RequiresExternalMechanism(TPolicyRealizationMode mode) noexcept
{
    return mode == TPolicyRealizationMode::external_mechanism ||
           mode == TPolicyRealizationMode::delegated_executor_path ||
           mode == TPolicyRealizationMode::bound_method_surface;
}

} // namespace assembler::ecosystem_governance::policy_type_system
