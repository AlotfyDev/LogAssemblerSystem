#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicyLifecycleState.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyLifecycleMarker.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyLifecycleMarker is a lightweight structural marker that associates a policy identity with a lifecycle state and an optional sequence marker. It names policy lifecycle position without becoming an audit event.
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
 *   - Uses TPolicyLifecycleState as its state vocabulary.
 *   - Can be embedded in TPolicyLifecycleSnapshot.
 *   - Can be exposed through TPolicyLifecycleView.
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
 *   TPolicyLifecycleMarker is not an observation record, not audit evidence, not a timestamped event log, and not a transition executor.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

struct TPolicyLifecycleMarker final
{
    using sequence_type = std::uint64_t;

    TPolicyId policy_id{};
    TPolicyLifecycleState state{TPolicyLifecycleState::unknown};
    sequence_type sequence{0};

    constexpr TPolicyLifecycleMarker() noexcept = default;

    constexpr TPolicyLifecycleMarker(
        TPolicyId ownerPolicyId,
        TPolicyLifecycleState lifecycleState,
        sequence_type markerSequence = 0) noexcept
        : policy_id(ownerPolicyId), state(lifecycleState), sequence(markerSequence)
    {
    }

    [[nodiscard]] constexpr bool HasPolicy() const noexcept { return policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasState() const noexcept { return IsKnown(state); }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept { return HasPolicy() && HasState(); }
};


} // namespace assembler::ecosystem_governance::policy_type_system
