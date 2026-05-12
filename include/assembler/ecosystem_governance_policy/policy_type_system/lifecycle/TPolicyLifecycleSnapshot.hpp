#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicyLifecycleMarker.hpp"
#include "TPolicyActivationState.hpp"
#include "TPolicySuspensionState.hpp"
#include "TPolicyRetirementState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyLifecycleSnapshot.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyLifecycleSnapshot captures the lifecycle-facing state of a policy at a point in policy-type-system representation. It composes the raw lifecycle marker with activation, suspension, and retirement interpretations.
 *
 * Why this file exists in W04:
 *   The Policy Object model requires lifecycle/state capability as a mandatory
 *   structural slot. W04 isolates lifecycle from observation/audit so that
 *   policy state can be represented without accidentally becoming evidence,
 *   telemetry, logging, assignment workflow, or runtime execution.
 *
 * Relationship to previous waves:
 *   - W01 provides policy identity primitives used to associate lifecycle data
 *     with a policy identity.
 *   - W02 defines clauses; lifecycle does not evaluate or execute them.
 *   - W03 defines safe points and replacement discipline; lifecycle may later
 *     interact with replacement eligibility, but it does not perform hot-swap
 *     algorithms in this wave.
 *
 * Relationship to other files in this wave:
 *   - Wraps TPolicyLifecycleMarker.
 *   - Uses activation, suspension, and retirement helper states.
 *   - Is consumed by TPolicyLifecycleView for safe read-only exposure.
 *
 * Relationship to future waves:
 *   - W05 observation/audit may record lifecycle evidence, but it remains a
 *     separate ownership layer.
 *   - W06 realization binding may depend on lifecycle admissibility, but it
 *     remains descriptive rather than executable.
 *   - W07 policy graph may represent lifecycle/state structure as graph nodes.
 *   - W09 TPolicy will aggregate lifecycle state with identity, clauses,
 *     replacement, observation, realization binding, and graph structure.
 *
 * Explicit non-responsibilities:
 *   TPolicyLifecycleSnapshot is not an observation event, not a registry snapshot, not a persistence record, and not a runtime scheduler snapshot.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

struct TPolicyLifecycleSnapshot final
{
    TPolicyLifecycleMarker marker{};
    TPolicyActivationState activation{TPolicyActivationState::unknown};
    TPolicySuspensionState suspension{TPolicySuspensionState::unknown};
    TPolicyRetirementState retirement{TPolicyRetirementState::unknown};

    constexpr TPolicyLifecycleSnapshot() noexcept = default;

    explicit constexpr TPolicyLifecycleSnapshot(TPolicyLifecycleMarker lifecycleMarker) noexcept
        : marker(lifecycleMarker),
          activation(ToActivationState(lifecycleMarker.state)),
          suspension(ToSuspensionState(lifecycleMarker.state)),
          retirement(ToRetirementState(lifecycleMarker.state))
    {
    }

    [[nodiscard]] constexpr TPolicyId PolicyId() const noexcept { return marker.policy_id; }
    [[nodiscard]] constexpr TPolicyLifecycleState State() const noexcept { return marker.state; }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept { return marker.IsStructurallyUsable(); }
    [[nodiscard]] constexpr bool IsActive() const noexcept { return activation == TPolicyActivationState::active; }
    [[nodiscard]] constexpr bool IsSuspended() const noexcept { return suspension == TPolicySuspensionState::suspended; }
    [[nodiscard]] constexpr bool IsRetired() const noexcept { return retirement == TPolicyRetirementState::retired; }
};


} // namespace assembler::ecosystem_governance::policy_type_system
