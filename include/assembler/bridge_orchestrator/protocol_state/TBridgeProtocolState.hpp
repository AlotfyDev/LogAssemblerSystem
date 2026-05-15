#pragma once

/**
 * @file TBridgeProtocolState.hpp
 * @brief Mutable operational protocol lifecycle state.
 *
 * IMPORTANT:
 *
 * This entity is NOT a passive descriptor.
 *
 * It acts as:
 *
 *     mutable lifecycle state nucleus
 *
 * for the protocol_state subsystem.
 *
 * Responsibilities:
 *
 * - runtime lifecycle ownership
 * - current stage ownership
 * - transition continuity
 * - mutation coordination substrate
 * - readiness-oriented lifecycle visibility
 *
 * IMPORTANT:
 *
 * This entity intentionally DOES NOT:
 *
 * - enforce transition legality
 * - perform invariant validation
 * - aggregate readiness
 * - produce diagnostics evidence
 *
 * Those responsibilities belong to dedicated runtime layers.
 */

#include "TBridgeStage.hpp"
#include "TBridgeTransition.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Mutable protocol lifecycle runtime state.
 */
class TBridgeProtocolState
{
public:

    /**
     * @brief Constructs protocol state at Created stage.
     */
    constexpr TBridgeProtocolState() noexcept = default;

    /**
     * @brief Returns current lifecycle stage.
     */
    [[nodiscard]] constexpr TBridgeStage
    current_stage() const noexcept
    {
        return current_stage_;
    }

    /**
     * @brief Returns previous lifecycle stage.
     */
    [[nodiscard]] constexpr TBridgeStage
    previous_stage() const noexcept
    {
        return previous_stage_;
    }

    /**
     * @brief Returns lifecycle transition generation.
     */
    [[nodiscard]] constexpr std::uint64_t
    generation() const noexcept
    {
        return generation_;
    }

    /**
     * @brief Returns true if runtime entered terminal lifecycle.
     */
    [[nodiscard]] constexpr bool
    is_terminal() const noexcept
    {
        return is_terminal_stage(current_stage_);
    }

    /**
     * @brief Returns true if runtime currently active.
     */
    [[nodiscard]] constexpr bool
    is_active() const noexcept
    {
        return is_active_stage(current_stage_);
    }

    /**
     * @brief Returns true if runtime may continue progression.
     */
    [[nodiscard]] constexpr bool
    can_progress() const noexcept
    {
        return can_progress_forward(current_stage_);
    }

    /**
     * @brief Applies lifecycle mutation.
     *
     * IMPORTANT:
     *
     * This method assumes transition legality
     * was validated externally.
     */
    constexpr void
    apply_transition(
        const TBridgeTransition& transition) noexcept
    {
        previous_stage_ = current_stage_;
        current_stage_ = transition.to;

        ++generation_;
    }

private:

    TBridgeStage current_stage_ =
        TBridgeStage::Created;

    TBridgeStage previous_stage_ =
        TBridgeStage::Unknown;

    std::uint64_t generation_ = 0;
};

} // namespace assembler::bridge_orchestrator::protocol_state
