#pragma once

#include <cstdint>
#include "TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySuspensionState.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicySuspensionState provides a focused view of whether policy lifecycle currently represents suspension or suspension eligibility concerns.
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
 *   - Complements TPolicyActivationState and TPolicyRetirementState.
 *   - Can be surfaced by TPolicyLifecycleView.
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
 *   TPolicySuspensionState does not suspend targets, stop dispatchers, pause material circulation, or implement operational control.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

enum class TPolicySuspensionState : std::uint8_t
{
    unknown = 0,
    not_suspended = 1,
    suspended = 2,
    suspension_blocked = 3
};

[[nodiscard]] constexpr bool IsSuspended(TPolicySuspensionState state) noexcept
{
    return state == TPolicySuspensionState::suspended;
}

[[nodiscard]] constexpr TPolicySuspensionState ToSuspensionState(TPolicyLifecycleState lifecycle) noexcept
{
    switch (lifecycle)
    {
        case TPolicyLifecycleState::suspended: return TPolicySuspensionState::suspended;
        case TPolicyLifecycleState::available:
        case TPolicyLifecycleState::active:
        case TPolicyLifecycleState::pending_replacement:
            return TPolicySuspensionState::not_suspended;
        case TPolicyLifecycleState::draft:
        case TPolicyLifecycleState::retiring:
        case TPolicyLifecycleState::retired:
        case TPolicyLifecycleState::invalid:
            return TPolicySuspensionState::suspension_blocked;
        case TPolicyLifecycleState::unknown:
        default:
            return TPolicySuspensionState::unknown;
    }
}


} // namespace assembler::ecosystem_governance::policy_type_system
