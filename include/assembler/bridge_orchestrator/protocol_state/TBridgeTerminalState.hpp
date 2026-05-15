#pragma once

/**
 * @file TBridgeTerminalState.hpp
 * @brief Terminal lifecycle semantic classification utilities.
 *
 * IMPORTANT:
 *
 * This file does NOT duplicate TBridgeStage.
 *
 * Instead, it defines:
 *
 *     terminal semantic meaning
 *
 * independently from lifecycle stage vocabulary.
 *
 * This separation is important for:
 *
 * - diagnostics
 * - readiness semantics
 * - recovery analysis
 * - invariant enforcement
 * - failure normalization
 */

#include "TBridgeStage.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Semantic classification of terminal outcomes.
 */
enum class TBridgeTerminalCategory : std::uint8_t
{
    Unknown = 0,

    Success,
    Failure,
    Cancellation,
    ForcedTermination
};

/**
 * @brief Classifies a terminal lifecycle stage.
 */
[[nodiscard]] constexpr TBridgeTerminalCategory
classify_terminal_stage(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Completed:
            return TBridgeTerminalCategory::Success;

        case TBridgeStage::Failed:
            return TBridgeTerminalCategory::Failure;

        case TBridgeStage::Cancelled:
            return TBridgeTerminalCategory::Cancellation;

        case TBridgeStage::Terminated:
            return TBridgeTerminalCategory::ForcedTermination;

        default:
            return TBridgeTerminalCategory::Unknown;
    }
}

/**
 * @brief Returns true if the terminal category represents successful completion.
 */
[[nodiscard]] constexpr bool
is_success_terminal(
    const TBridgeTerminalCategory category) noexcept
{
    return category == TBridgeTerminalCategory::Success;
}

/**
 * @brief Returns true if the terminal category represents failure semantics.
 */
[[nodiscard]] constexpr bool
is_failure_terminal(
    const TBridgeTerminalCategory category) noexcept
{
    switch (category)
    {
        case TBridgeTerminalCategory::Failure:
        case TBridgeTerminalCategory::Cancellation:
        case TBridgeTerminalCategory::ForcedTermination:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the lifecycle stage is recoverable.
 */
[[nodiscard]] constexpr bool
is_recoverable_terminal_stage(
    const TBridgeStage stage) noexcept
{
    switch (classify_terminal_stage(stage))
    {
        case TBridgeTerminalCategory::Cancellation:
            return true;

        default:
            return false;
    }
}

} // namespace assembler::bridge_orchestrator::protocol_state
