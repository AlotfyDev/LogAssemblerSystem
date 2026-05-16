#pragma once

/**
 * @file TBridgeProtocolStateRuntimeReadinessView.hpp
 * @brief Operational readiness projection for protocol runtime.
 *
 * IMPORTANT:
 *
 * This is the READINESS AUTHORITY.
 *
 * It does NOT store state.
 * It DOES compute readiness based on current runtime snapshot.
 *
 * Responsibilities:
 *
 * - evaluate lifecycle progression capability
 * - check for terminal blockage
 * - verify invariant integrity status
 * - synthesize aggregated readiness report
 *
 * Architectural Role:
 *
 *     readiness aggregation facade for runtime consumers
 */

#include "TBridgeProtocolState.hpp"
#include "TBridgeProtocolStateReadinessReport.hpp"
#include "TBridgeStateInvariantEngine.hpp"

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Runtime readiness evaluation engine.
 */
class TBridgeProtocolStateRuntimeReadinessView
{
public:

    /**
     * @brief Evaluates readiness based on current protocol state.
     *
     * Logic Flow:
     * 1. Check if state is initialized (not Unknown/Created invalidly)
     * 2. Check if state is Terminal (blocked)
     * 3. Run invariant checks (integrity)
     * 4. If all pass -> Ready
     */
    [[nodiscard]] static constexpr TBridgeProtocolStateReadinessReport
    evaluate(const TBridgeProtocolState& state) noexcept
    {
        const auto current_stage = state.current_stage();

        // Check 1: Initialization Status
        if (current_stage == TBridgeStage::Unknown)
        {
            return TBridgeProtocolStateReadinessReport::make_not_initialized();
        }

        // Check 2: Terminal State Blockage
        if (is_terminal_stage(current_stage))
        {
            return TBridgeProtocolStateReadinessReport::make_terminal_blocked(current_stage);
        }

        // Check 3: Invariant Integrity
        // We run a quick integrity check on the current state
        const auto inv_report = TBridgeStateInvariantEngine::validate_state_integrity(state);
        
        if (inv_report.has_violation())
        {
            return TBridgeProtocolStateReadinessReport::make_invariant_violation(
                current_stage, inv_report);
        }

        // All checks passed
        return TBridgeProtocolStateReadinessReport::make_ready(current_stage);
    }

    /**
     * @brief Quick boolean check for readiness (optimized path).
     */
    [[nodiscard]] static constexpr bool
    is_ready(const TBridgeProtocolState& state) noexcept
    {
        return evaluate(state).is_ready();
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state
