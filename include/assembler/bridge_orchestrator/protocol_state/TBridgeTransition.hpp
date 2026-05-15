#pragma once

/**
 * @file TBridgeTransition.hpp
 * @brief Canonical lifecycle transition semantics for protocol_state.
 *
 * This entity defines the semantic mutation contract between lifecycle stages.
 *
 * TBridgeTransition is intentionally lightweight and constexpr-oriented,
 * but semantically operational.
 *
 * It acts as:
 *
 *     lifecycle mutation semantic substrate
 *
 * consumed later by:
 *
 * - transition admission runtime
 * - invariant enforcement
 * - diagnostics runtime
 * - readiness aggregation
 * - protocol state runtime
 */

#include "TBridgeStage.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Semantic classification of lifecycle transitions.
 */
enum class TBridgeTransitionKind : std::uint8_t
{
    Unknown = 0,

    Activation,
    Suspension,
    Recovery,

    Completion,
    Failure,
    Cancellation,

    Internal
};

/**
 * @brief Canonical lifecycle mutation descriptor.
 */
struct TBridgeTransition
{
    TBridgeStage from = TBridgeStage::Unknown;
    TBridgeStage to = TBridgeStage::Unknown;

    TBridgeTransitionKind kind =
        TBridgeTransitionKind::Unknown;

    /**
     * @brief Returns true if the transition targets a terminal stage.
     */
    [[nodiscard]] constexpr bool
    is_terminal_transition() const noexcept
    {
        return is_terminal_stage(to);
    }

    /**
     * @brief Returns true if the transition represents failure semantics.
     */
    [[nodiscard]] constexpr bool
    is_failure_transition() const noexcept
    {
        return kind == TBridgeTransitionKind::Failure
            || kind == TBridgeTransitionKind::Cancellation;
    }

    /**
     * @brief Returns true if the transition activates runtime execution.
     */
    [[nodiscard]] constexpr bool
    is_activation_transition() const noexcept
    {
        return kind == TBridgeTransitionKind::Activation;
    }

    /**
     * @brief Returns true if the transition represents runtime suspension.
     */
    [[nodiscard]] constexpr bool
    is_suspension_transition() const noexcept
    {
        return kind == TBridgeTransitionKind::Suspension;
    }

    /**
     * @brief Returns true if the transition represents runtime recovery.
     */
    [[nodiscard]] constexpr bool
    is_recovery_transition() const noexcept
    {
        return kind == TBridgeTransitionKind::Recovery;
    }

    /**
     * @brief Returns true if the transition preserves active execution semantics.
     */
    [[nodiscard]] constexpr bool
    preserves_runtime_activity() const noexcept
    {
        return is_active_stage(from)
            && is_active_stage(to);
    }
};

/**
 * @brief Returns true if the transition changes lifecycle phase.
 */
[[nodiscard]] constexpr bool
is_cross_phase_transition(const TBridgeTransition& transition) noexcept
{
    return transition.from != transition.to;
}

/**
 * @brief Returns true if the transition is terminally destructive.
 */
[[nodiscard]] constexpr bool
is_destructive_transition(const TBridgeTransition& transition) noexcept
{
    return transition.is_failure_transition()
        || transition.is_terminal_transition();
}

} // namespace assembler::bridge_orchestrator::protocol_state
