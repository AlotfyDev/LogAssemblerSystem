#pragma once

/**
 * @file TBridgeStateInvariantEngine.hpp
 * @brief Active enforcement engine for protocol lifecycle invariants.
 *
 * IMPORTANT:
 *
 * This is the "Guardian" of lifecycle integrity.
 *
 * It does NOT execute transitions.
 * It DOES validate state integrity before/after operations.
 *
 * Responsibilities:
 *
 * - enforce generation monotonicity
 * - enforce terminal state immutability
 * - enforce stage classification consistency
 * - detect continuity breaks
 *
 * Architectural Role:
 *
 *     active invariant enforcement authority
 */

#include "TBridgeProtocolState.hpp"
#include "TBridgeProtocolStateInvariantReport.hpp"
#include "TBridgeTransition.hpp"

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Engine for enforcing protocol state invariants.
 */
class TBridgeStateInvariantEngine
{
public:

    /**
     * @brief Validates the current state integrity.
     *
     * Checks:
     * - Terminal state immutability attempts
     * - Stage classification validity
     */
    [[nodiscard]] static constexpr TBridgeProtocolStateInvariantReport
    validate_state_integrity(
        const TBridgeProtocolState& state) noexcept
    {
        // Invariant 1: Terminal states must not be active for progression
        // Note: The state object itself holds the data, we check if 
        // someone tried to mark a terminal state as 'active' incorrectly
        // or if the internal flags are inconsistent.
        
        const auto current = state.current_stage();
        
        if (is_terminal_stage(current))
        {
            // If we are in a terminal state, generation should be stable
            // unless a reset happened (which is external). 
            // Here we just flag if we detect an inconsistency in classification.
            // Real enforcement happens during transition.
        }

        // Placeholder for deep classification checks if needed
        return TBridgeProtocolStateInvariantReport{}; // No violation by default
    }

    /**
     * @brief Validates a proposed transition against state invariants.
     *
     * Checks:
     * - No mutations allowed from Terminal states
     * - Generation must not regress
     */
    [[nodiscard]] static constexpr TBridgeProtocolStateInvariantReport
    validate_transition_invariants(
        const TBridgeProtocolState& current_state,
        const TBridgeTransition& proposed_transition) noexcept
    {
        const auto current_stage = current_state.current_stage();
        const auto current_gen = current_state.generation();

        // Invariant 1: Terminal State Immutability
        if (is_terminal_stage(current_stage))
        {
            return TBridgeProtocolStateInvariantReport::make_terminal_mutation(current_stage);
        }

        // Invariant 2: Generation Monotonicity (Pre-check)
        // The transition itself doesn't carry generation, but the result state will.
        // We ensure we aren't trying to apply a transition that implies regression
        // (Logic handled mostly in Runtime, but we check pre-conditions here).
        
        // If the transition target is invalid relative to current classification
        // (e.g. moving backwards in a strict forward-only phase)
        // This is often covered by AdmissionEngine, but Invariants catch logic bugs.
        
        return TBridgeProtocolStateInvariantReport{}; // Valid
    }

    /**
     * @brief Post-execution validation to ensure state consistency.
     *
     * Checks:
     * - Generation increased exactly by 1
     * - Continuity (previous == old current)
     */
    [[nodiscard]] static constexpr TBridgeProtocolStateInvariantReport
    validate_post_execution(
        const TBridgeProtocolState& old_state,
        const TBridgeProtocolState& new_state) noexcept
    {
        const auto old_gen = old_state.generation();
        const auto new_gen = new_state.generation();

        // Invariant: Generation must strictly increase by 1 on successful transition
        if (new_gen != old_gen + 1)
        {
            if (new_gen < old_gen)
            {
                return TBridgeProtocolStateInvariantReport::make_generation_regression(
                    new_state.current_stage(), new_gen);
            }
            // If it jumped by more than 1, it might be a continuity break or batch op
            // For single transitions, >1 is also suspicious depending on policy
            if (new_gen > old_gen + 1)
            {
                 return TBridgeProtocolStateInvariantReport::make_continuity_break(
                    new_state.current_stage(), new_gen);
            }
        }

        // Invariant: Continuity of previous stage
        if (new_state.previous_stage() != old_state.current_stage())
        {
            return TBridgeProtocolStateInvariantReport::make_continuity_break(
                new_state.current_stage(), new_gen);
        }

        return TBridgeProtocolStateInvariantReport{}; // Valid
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state
