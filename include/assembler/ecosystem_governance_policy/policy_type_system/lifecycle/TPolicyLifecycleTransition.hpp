#pragma once

#include <cstdint>
#include "TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyLifecycleTransition.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyLifecycleTransition describes an intended lifecycle state change as data. It exists to make lifecycle movement reviewable without creating an orchestration engine.
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
 *   - Uses TPolicyLifecycleState as endpoints.
 *   - May be referenced by snapshots and later TPolicy aggregate validation.
 *   - Remains separate from observation, which may later record that a transition happened.
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
 *   TPolicyLifecycleTransition does not execute transitions, does not lock or synchronize, does not replace policies, and does not record audit evidence.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

enum class TPolicyLifecycleTransitionKind : std::uint8_t
{
    unknown = 0,
    publish = 1,
    activate = 2,
    suspend = 3,
    resume = 4,
    mark_pending_replacement = 5,
    begin_retirement = 6,
    complete_retirement = 7,
    invalidate = 8
};

struct TPolicyLifecycleTransition final
{
    TPolicyLifecycleState from{TPolicyLifecycleState::unknown};
    TPolicyLifecycleState to{TPolicyLifecycleState::unknown};
    TPolicyLifecycleTransitionKind kind{TPolicyLifecycleTransitionKind::unknown};

    constexpr TPolicyLifecycleTransition() noexcept = default;

    constexpr TPolicyLifecycleTransition(
        TPolicyLifecycleState fromState,
        TPolicyLifecycleState toState,
        TPolicyLifecycleTransitionKind transitionKind) noexcept
        : from(fromState), to(toState), kind(transitionKind)
    {
    }

    [[nodiscard]] constexpr bool IsKnownTransition() const noexcept
    {
        return IsKnown(from) && IsKnown(to) && kind != TPolicyLifecycleTransitionKind::unknown;
    }

    [[nodiscard]] constexpr bool ChangesState() const noexcept
    {
        return IsKnownTransition() && from != to;
    }
};

[[nodiscard]] constexpr bool IsConservativeLifecycleTransition(TPolicyLifecycleTransition transition) noexcept
{
    if (!transition.IsKnownTransition()) return false;

    switch (transition.kind)
    {
        case TPolicyLifecycleTransitionKind::publish:
            return transition.from == TPolicyLifecycleState::draft && transition.to == TPolicyLifecycleState::available;
        case TPolicyLifecycleTransitionKind::activate:
            return transition.from == TPolicyLifecycleState::available && transition.to == TPolicyLifecycleState::active;
        case TPolicyLifecycleTransitionKind::suspend:
            return transition.from == TPolicyLifecycleState::active && transition.to == TPolicyLifecycleState::suspended;
        case TPolicyLifecycleTransitionKind::resume:
            return transition.from == TPolicyLifecycleState::suspended && transition.to == TPolicyLifecycleState::active;
        case TPolicyLifecycleTransitionKind::mark_pending_replacement:
            return transition.from == TPolicyLifecycleState::active && transition.to == TPolicyLifecycleState::pending_replacement;
        case TPolicyLifecycleTransitionKind::begin_retirement:
            return (transition.from == TPolicyLifecycleState::available ||
                    transition.from == TPolicyLifecycleState::active ||
                    transition.from == TPolicyLifecycleState::suspended ||
                    transition.from == TPolicyLifecycleState::pending_replacement) &&
                   transition.to == TPolicyLifecycleState::retiring;
        case TPolicyLifecycleTransitionKind::complete_retirement:
            return transition.from == TPolicyLifecycleState::retiring && transition.to == TPolicyLifecycleState::retired;
        case TPolicyLifecycleTransitionKind::invalidate:
            return !IsTerminal(transition.from) && transition.to == TPolicyLifecycleState::invalid;
        case TPolicyLifecycleTransitionKind::unknown:
        default:
            return false;
    }
}


} // namespace assembler::ecosystem_governance::policy_type_system
