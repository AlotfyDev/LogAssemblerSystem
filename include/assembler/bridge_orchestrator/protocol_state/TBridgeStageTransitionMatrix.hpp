#pragma once

/**
 * @file TBridgeStageTransitionMatrix.hpp
 * @brief Canonical lifecycle transition admissibility substrate.
 *
 * IMPORTANT:
 *
 * This file is NOT merely a constexpr lookup table.
 *
 * It acts as:
 *
 *     canonical transition legality authority
 *
 * for the entire protocol_state subsystem.
 *
 * Consumed by:
 *
 * - transition admission runtime
 * - invariant enforcement
 * - protocol runtime
 * - readiness aggregation
 * - diagnostics normalization
 *
 * Design Goals:
 *
 * - constexpr-first
 * - allocation-free
 * - deterministic
 * - semantically centralized
 * - runtime-safe
 */

#include "TBridgeTransition.hpp"

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Returns true if the transition is semantically legal.
 *
 * IMPORTANT:
 *
 * This validates:
 *
 * - lifecycle progression legality
 * - suspension legality
 * - recovery legality
 * - terminal semantics
 *
 * This function does NOT validate:
 *
 * - runtime invariants
 * - orchestration ownership
 * - external obligations
 * - readiness state
 *
 * Those belong to later runtime layers.
 */
[[nodiscard]] constexpr bool
is_transition_legal(
    const TBridgeTransition& transition) noexcept
{
    switch (transition.from)
    {
        case TBridgeStage::Created:
        {
            return transition.to
                == TBridgeStage::Initialized;
        }

        case TBridgeStage::Initialized:
        {
            return transition.to
                    == TBridgeStage::Admitted
                || transition.to
                    == TBridgeStage::Cancelled;
        }

        case TBridgeStage::Admitted:
        {
            return transition.to
                    == TBridgeStage::Bound
                || transition.to
                    == TBridgeStage::Cancelled;
        }

        case TBridgeStage::Bound:
        {
            return transition.to
                    == TBridgeStage::Active
                || transition.to
                    == TBridgeStage::Failed;
        }

        case TBridgeStage::Active:
        {
            return transition.to
                    == TBridgeStage::Suspended
                || transition.to
                    == TBridgeStage::Completed
                || transition.to
                    == TBridgeStage::Failed
                || transition.to
                    == TBridgeStage::Cancelled;
        }

        case TBridgeStage::Suspended:
        {
            return transition.to
                    == TBridgeStage::Active
                || transition.to
                    == TBridgeStage::Cancelled
                || transition.to
                    == TBridgeStage::Failed;
        }

        case TBridgeStage::Completed:
        case TBridgeStage::Failed:
        case TBridgeStage::Cancelled:
        case TBridgeStage::Terminated:
        {
            return false;
        }

        default:
            return false;
    }
}

/**
 * @brief Returns true if the transition preserves active execution continuity.
 */
[[nodiscard]] constexpr bool
preserves_runtime_continuity(
    const TBridgeTransition& transition) noexcept
{
    return is_active_stage(transition.from)
        && is_active_stage(transition.to);
}

/**
 * @brief Returns true if the transition enters a terminal state.
 */
[[nodiscard]] constexpr bool
enters_terminal_state(
    const TBridgeTransition& transition) noexcept
{
    return is_terminal_stage(transition.to);
}

/**
 * @brief Returns true if the transition exits a stable runtime state.
 */
[[nodiscard]] constexpr bool
exits_runtime_stability(
    const TBridgeTransition& transition) noexcept
{
    return is_runtime_stable_stage(transition.from)
        && !is_runtime_stable_stage(transition.to);
}

/**
 * @brief Returns true if the transition represents semantic recovery.
 */
[[nodiscard]] constexpr bool
is_semantic_recovery_transition(
    const TBridgeTransition& transition) noexcept
{
    return transition.from
            == TBridgeStage::Suspended
        && transition.to
            == TBridgeStage::Active;
}

} // namespace assembler::bridge_orchestrator::protocol_state
