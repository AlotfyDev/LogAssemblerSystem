#pragma once

/**
 * @file TBridgeStage.hpp
 * @brief Canonical lifecycle stage semantics for the protocol_state subsystem.
 *
 * This file defines the foundational lifecycle vocabulary consumed by:
 *
 * - transition admission
 * - protocol runtime
 * - invariant enforcement
 * - readiness aggregation
 * - diagnostics normalization
 *
 * Architectural Role:
 *
 * TBridgeStage is NOT a passive enum collection.
 *
 * It acts as:
 *
 *     constexpr operational semantic substrate
 *
 * for the entire protocol_state subsystem.
 *
 * Design Goals:
 *
 * - constexpr-first
 * - allocation-free
 * - semantically centralized
 * - dependency-light
 * - facade-safe
 * - operationally stable
 */

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Canonical lifecycle stages for bridge protocol execution.
 */
enum class TBridgeStage : std::uint8_t
{
    Unknown = 0,

    Created,
    Initialized,
    Admitted,
    Bound,

    Active,
    Suspended,

    Completed,
    Failed,
    Cancelled,
    Terminated
};

/**
 * @brief Returns true if the stage is terminal.
 */
[[nodiscard]] constexpr bool
is_terminal_stage(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Completed:
        case TBridgeStage::Failed:
        case TBridgeStage::Cancelled:
        case TBridgeStage::Terminated:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the stage represents failure semantics.
 */
[[nodiscard]] constexpr bool
is_failure_stage(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Failed:
        case TBridgeStage::Cancelled:
        case TBridgeStage::Terminated:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the stage is operationally active.
 */
[[nodiscard]] constexpr bool
is_active_stage(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Active:
        case TBridgeStage::Suspended:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the stage occurs before activation.
 */
[[nodiscard]] constexpr bool
is_pre_activation_stage(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Created:
        case TBridgeStage::Initialized:
        case TBridgeStage::Admitted:
        case TBridgeStage::Bound:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the stage is runtime-stable.
 *
 * Runtime-stable stages are:
 *
 * - active runtime stages
 * - terminal lifecycle stages
 */
[[nodiscard]] constexpr bool
is_runtime_stable_stage(const TBridgeStage stage) noexcept
{
    return is_active_stage(stage)
        || is_terminal_stage(stage);
}

/**
 * @brief Returns true if the stage allows forward progression.
 */
[[nodiscard]] constexpr bool
can_progress_forward(const TBridgeStage stage) noexcept
{
    return !is_terminal_stage(stage);
}

/**
 * @brief Returns true if the stage permits suspension semantics.
 */
[[nodiscard]] constexpr bool
supports_suspension(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Active:
            return true;

        default:
            return false;
    }
}

/**
 * @brief Returns true if the stage permits recovery semantics.
 */
[[nodiscard]] constexpr bool
supports_recovery(const TBridgeStage stage) noexcept
{
    switch (stage)
    {
        case TBridgeStage::Suspended:
        case TBridgeStage::Failed:
            return true;

        default:
            return false;
    }
}

} // namespace assembler::bridge_orchestrator::protocol_state
