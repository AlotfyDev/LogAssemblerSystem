#pragma once

/**
 * @file TBridgeProtocolStateRuntime.hpp
 * @brief Operational runtime orchestration layer for protocol lifecycle state.
 *
 * IMPORTANT:
 *
 * This is the TRUE operational nucleus
 * of the protocol_state subsystem.
 *
 * Responsibilities:
 *
 * - transition execution orchestration
 * - runtime admissibility enforcement
 * - lifecycle continuity ownership
 * - mutation coordination
 * - operational transition sequencing
 *
 * Architectural Role:
 *
 *     mutable lifecycle runtime authority
 *
 * This layer intentionally separates:
 *
 * - lifecycle mutation
 * - transition admission
 * - invariant enforcement
 * - evidence aggregation
 * - readiness synthesis
 *
 * to prevent:
 *
 * - semantic leakage
 * - god-object state managers
 * - diagnostics coupling
 * - readiness contamination
 */

#include "TBridgeProtocolState.hpp"
#include "TBridgeTransitionAdmissionEngine.hpp"

#include <optional>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Runtime transition execution result.
 */
struct TProtocolStateRuntimeResult
{
    bool transition_applied = false;

    TTransitionAdmissionReport
        admission_report {};

    std::optional<TBridgeTransition>
        applied_transition;
};

/**
 * @brief Mutable protocol lifecycle runtime authority.
 */
class TBridgeProtocolStateRuntime
{
public:

    /**
     * @brief Returns immutable protocol state view.
     */
    [[nodiscard]] constexpr const TBridgeProtocolState&
    state() const noexcept
    {
        return state_;
    }

    /**
     * @brief Returns current lifecycle stage.
     */
    [[nodiscard]] constexpr TBridgeStage
    current_stage() const noexcept
    {
        return state_.current_stage();
    }

    /**
     * @brief Returns runtime generation.
     */
    [[nodiscard]] constexpr std::uint64_t
    generation() const noexcept
    {
        return state_.generation();
    }

    /**
     * @brief Returns true if runtime reached terminal lifecycle.
     */
    [[nodiscard]] constexpr bool
    is_terminal() const noexcept
    {
        return state_.is_terminal();
    }

    /**
     * @brief Executes runtime lifecycle transition.
     */
    [[nodiscard]] constexpr TProtocolStateRuntimeResult
    execute_transition(
        const TBridgeTransition& transition) noexcept
    {
        TProtocolStateRuntimeResult result {};

        result.admission_report =
            admission_engine_.evaluate(transition);

        if (!result.admission_report.admitted())
        {
            return result;
        }

        state_.apply_transition(transition);

        result.transition_applied = true;
        result.applied_transition = transition;

        return result;
    }

    /**
     * @brief Returns true if runtime admits transition execution.
     */
    [[nodiscard]] constexpr bool
    admits(
        const TBridgeTransition& transition) const noexcept
    {
        return admission_engine_.admits(transition);
    }

private:

    TBridgeProtocolState state_ {};

    TBridgeTransitionAdmissionEngine
        admission_engine_ {};
};

} // namespace assembler::bridge_orchestrator::protocol_state
