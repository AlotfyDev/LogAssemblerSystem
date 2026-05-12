#pragma once

#include <cstdint>
#include "TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyActivationState.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyActivationState isolates the activation-facing interpretation of lifecycle. It allows later policy assignment or realization layers to ask whether a policy may be activated without making lifecycle itself execute anything.
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
 *   - Derived from TPolicyLifecycleState.
 *   - Used by TPolicyLifecycleView to expose activation-safe questions.
 *   - Remains separate from suspension and retirement state helpers.
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
 *   TPolicyActivationState does not activate policy, invoke realization mechanisms, call targets, schedule work, or record audit evidence.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

enum class TPolicyActivationState : std::uint8_t
{
    unknown = 0,
    inactive = 1,
    activatable = 2,
    active = 3,
    activation_blocked = 4
};

[[nodiscard]] constexpr bool IsActive(TPolicyActivationState state) noexcept
{
    return state == TPolicyActivationState::active;
}

[[nodiscard]] constexpr bool CanActivate(TPolicyActivationState state) noexcept
{
    return state == TPolicyActivationState::activatable;
}

[[nodiscard]] constexpr TPolicyActivationState ToActivationState(TPolicyLifecycleState lifecycle) noexcept
{
    switch (lifecycle)
    {
        case TPolicyLifecycleState::available: return TPolicyActivationState::activatable;
        case TPolicyLifecycleState::active: return TPolicyActivationState::active;
        case TPolicyLifecycleState::suspended: return TPolicyActivationState::inactive;
        case TPolicyLifecycleState::draft:
        case TPolicyLifecycleState::pending_replacement:
        case TPolicyLifecycleState::retiring:
        case TPolicyLifecycleState::retired:
        case TPolicyLifecycleState::invalid:
            return TPolicyActivationState::activation_blocked;
        case TPolicyLifecycleState::unknown:
        default:
            return TPolicyActivationState::unknown;
    }
}


} // namespace assembler::ecosystem_governance::policy_type_system
