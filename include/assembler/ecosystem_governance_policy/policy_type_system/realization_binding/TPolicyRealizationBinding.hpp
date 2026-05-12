#pragma once

#include <cstdint>
#include "TPolicyRealizationDescriptor.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementEligibility.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyTraceRef.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRealizationBinding.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyRealizationBinding is the primary W06 carrier describing that a
 *   policy is associated with a realization mechanism descriptor and optional
 *   target-kind expectation. It preserves the architecture's three-way split:
 *   policy object carries governing content, realization mechanism enacts later,
 *   and external target object remains outside policy ownership.
 *
 * Why this file exists in W06:
 *   The Policy Object taxonomy requires realization-mechanism binding in
 *   execution-policy families. W06 introduces the binding as a non-executable,
 *   reviewable C++ value type after identity, clauses, replacement, lifecycle,
 *   and observation foundations exist.
 *
 * Relationship to previous waves:
 *   - W01 provides TPolicyId and TPolicyFamilyId for the policy subject.
 *   - W03 provides TPolicyReplacementEligibility to record whether binding
 *     replacement is structurally allowed.
 *   - W04 provides lifecycle state to describe lifecycle admissibility.
 *   - W05 provides TPolicyTraceRef for traceability without telemetry export.
 *
 * Relationship to other files in this wave:
 *   - TPolicyRealizationDescriptor provides binding/mechanism/target-kind data.
 *   - TPolicyRealizationBindingView exposes a read-only view of this binding.
 *
 * Relationship to future waves:
 *   - W07 policy graph may include a realization mechanism binding node derived
 *     from this carrier.
 *   - W09 TPolicy may aggregate this binding with identity, clauses, lifecycle,
 *     replacement, observation, graph, and traversal foundation structures.
 *   - W10 assignment may connect this binding to assignment context.
 *
 * Explicit non-responsibilities:
 *   TPolicyRealizationBinding does not execute the policy, does not call a
 *   target, does not own target object lifecycle, does not open communication
 *   sessions, does not perform material circulation, and does not implement a
 *   policy realizer or executor.
 *
 * Current implementation note:
 *   W06 provides compact state and descriptor carriers only. The opening comment
 *   documents the full intended architecture even though the current code is a
 *   foundation block.
 */
struct TPolicyRealizationBinding final
{
    TPolicyId policy_id{};
    TPolicyFamilyId family_id{};
    TPolicyRealizationDescriptor descriptor{};
    TPolicyLifecycleState lifecycle_state{TPolicyLifecycleState::unknown};
    TPolicyReplacementEligibility replacement_eligibility{TPolicyReplacementEligibility::unknown};
    TPolicyTraceRef trace{};
    std::uint32_t binding_flags{0};

    constexpr TPolicyRealizationBinding() noexcept = default;

    constexpr TPolicyRealizationBinding(
        TPolicyId policy,
        TPolicyFamilyId family,
        TPolicyRealizationDescriptor realization_descriptor,
        TPolicyLifecycleState lifecycle = TPolicyLifecycleState::unknown,
        TPolicyReplacementEligibility replacement = TPolicyReplacementEligibility::unknown,
        TPolicyTraceRef trace_ref = {},
        std::uint32_t flags = 0) noexcept
        : policy_id(policy), family_id(family), descriptor(realization_descriptor), lifecycle_state(lifecycle), replacement_eligibility(replacement), trace(trace_ref), binding_flags(flags) {}

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return policy_id.IsValid() && family_id.IsValid() && descriptor.IsStructurallyComplete();
    }

    [[nodiscard]] constexpr bool HasTargetKind() const noexcept { return descriptor.HasTargetKind(); }
    [[nodiscard]] constexpr bool HasTrace() const noexcept { return trace.IsPresent(); }
    [[nodiscard]] constexpr bool AllowsReplacement() const noexcept { return IsReplacementAllowed(replacement_eligibility); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
