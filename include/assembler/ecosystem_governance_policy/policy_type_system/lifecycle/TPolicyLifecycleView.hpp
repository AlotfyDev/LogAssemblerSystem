#pragma once

#include "TPolicyLifecycleSnapshot.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyLifecycleView.hpp
 * Wave: EG-POL-W04_Policy_Lifecycle
 * Domain: ecosystem_governance / policy_type_system / lifecycle
 *
 * Full architectural responsibility:
 *   TPolicyLifecycleView is the read-only surface for lifecycle state. It allows later aggregates and diagnostics to expose lifecycle information without handing out mutable lifecycle internals.
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
 *   - Wraps TPolicyLifecycleSnapshot.
 *   - Provides lifecycle-facing convenience queries.
 *   - Remains the lifecycle counterpart to later observation views, not a replacement for them.
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
 *   TPolicyLifecycleView does not mutate lifecycle, does not emit audit records, does not perform assignment, and does not execute realization.
 *
 * Current implementation note:
 *   W04 intentionally provides compact C++17 value types and enums. The opening
 *   documentation records the full intended architecture even where the current
 *   code is only a foundation block for later waves.
 */

class TPolicyLifecycleView final
{
public:
    constexpr TPolicyLifecycleView() noexcept = default;

    explicit constexpr TPolicyLifecycleView(TPolicyLifecycleSnapshot snapshot) noexcept
        : snapshot_(snapshot)
    {
    }

    [[nodiscard]] constexpr TPolicyId PolicyId() const noexcept { return snapshot_.PolicyId(); }
    [[nodiscard]] constexpr TPolicyLifecycleState State() const noexcept { return snapshot_.State(); }
    [[nodiscard]] constexpr bool IsKnown() const noexcept { return policy_type_system::IsKnown(snapshot_.State()); }
    [[nodiscard]] constexpr bool IsActive() const noexcept { return snapshot_.IsActive(); }
    [[nodiscard]] constexpr bool IsSuspended() const noexcept { return snapshot_.IsSuspended(); }
    [[nodiscard]] constexpr bool IsRetired() const noexcept { return snapshot_.IsRetired(); }
    [[nodiscard]] constexpr bool IsTerminal() const noexcept { return policy_type_system::IsTerminal(snapshot_.State()); }
    [[nodiscard]] constexpr bool CanBeAssigned() const noexcept { return IsUsableForAssignment(snapshot_.State()); }
    [[nodiscard]] constexpr TPolicyLifecycleSnapshot Snapshot() const noexcept { return snapshot_; }

private:
    TPolicyLifecycleSnapshot snapshot_{};
};


} // namespace assembler::ecosystem_governance::policy_type_system
