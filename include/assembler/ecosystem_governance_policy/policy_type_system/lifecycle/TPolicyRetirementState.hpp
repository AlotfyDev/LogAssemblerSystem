#pragma once

#include <cstdint>
#include "TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyRetirementState.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyRetirementState provides a retirement-facing interpretation of policy lifecycle without turning retirement into deletion, registry removal, or target shutdown.
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
 *   - Complements activation and suspension helper states.
 *   - Can be used by lifecycle views and later registry-readiness checks.
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
 *   TPolicyRetirementState does not delete policies, remove registry entries, terminate targets, or perform persistence cleanup.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

enum class TPolicyRetirementState : std::uint8_t
{
    unknown = 0,
    not_retired = 1,
    retiring = 2,
    retired = 3,
    retirement_blocked = 4
};

[[nodiscard]] constexpr bool IsRetired(TPolicyRetirementState state) noexcept
{
    return state == TPolicyRetirementState::retired;
}

[[nodiscard]] constexpr bool IsRetirementPath(TPolicyRetirementState state) noexcept
{
    return state == TPolicyRetirementState::retiring || state == TPolicyRetirementState::retired;
}

[[nodiscard]] constexpr TPolicyRetirementState ToRetirementState(TPolicyLifecycleState lifecycle) noexcept
{
    switch (lifecycle)
    {
        case TPolicyLifecycleState::retiring: return TPolicyRetirementState::retiring;
        case TPolicyLifecycleState::retired: return TPolicyRetirementState::retired;
        case TPolicyLifecycleState::available:
        case TPolicyLifecycleState::active:
        case TPolicyLifecycleState::suspended:
        case TPolicyLifecycleState::pending_replacement:
            return TPolicyRetirementState::not_retired;
        case TPolicyLifecycleState::draft:
        case TPolicyLifecycleState::invalid:
            return TPolicyRetirementState::retirement_blocked;
        case TPolicyLifecycleState::unknown:
        default:
            return TPolicyRetirementState::unknown;
    }
}


} // namespace assembler::ecosystem_governance::policy_type_system
