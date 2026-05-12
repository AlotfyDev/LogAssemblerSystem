#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyLifecycleState.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyLifecycleState provides the canonical lifecycle vocabulary for policy objects. It answers what state a policy is in, without recording why that state was reached and without acting on targets.
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
 *   - TPolicyLifecycleMarker names a state occurrence.
 *   - TPolicyLifecycleTransition uses states as from/to endpoints.
 *   - TPolicyLifecycleSnapshot and TPolicyLifecycleView expose current state.
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
 *   TPolicyLifecycleState is not TPolicyStatus, not observation, not audit, not assignment status, not registry status, not realization status, and not a traversal state.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

enum class TPolicyLifecycleState : std::uint8_t
{
    unknown = 0,
    draft = 1,
    available = 2,
    active = 3,
    suspended = 4,
    pending_replacement = 5,
    retiring = 6,
    retired = 7,
    invalid = 8
};

[[nodiscard]] constexpr bool IsKnown(TPolicyLifecycleState state) noexcept
{
    return state != TPolicyLifecycleState::unknown;
}

[[nodiscard]] constexpr bool IsTerminal(TPolicyLifecycleState state) noexcept
{
    return state == TPolicyLifecycleState::retired || state == TPolicyLifecycleState::invalid;
}

[[nodiscard]] constexpr bool IsUsableForAssignment(TPolicyLifecycleState state) noexcept
{
    return state == TPolicyLifecycleState::available || state == TPolicyLifecycleState::active;
}

[[nodiscard]] constexpr bool IsRuntimeActive(TPolicyLifecycleState state) noexcept
{
    return state == TPolicyLifecycleState::active || state == TPolicyLifecycleState::pending_replacement;
}


} // namespace assembler::ecosystem_governance::policy_type_system
