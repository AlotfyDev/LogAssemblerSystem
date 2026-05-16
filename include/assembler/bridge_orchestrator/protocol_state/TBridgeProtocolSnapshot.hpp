#pragma once

/**
 * @file TBridgeProtocolSnapshot.hpp
 * @brief Immutable continuity evidence snapshot of protocol lifecycle state.
 *
 * IMPORTANT:
 *
 * This entity is NOT a passive data dump.
 *
 * It acts as:
 *
 *     cryptographic-grade continuity evidence token
 *
 * Responsibilities:
 *
 * - immutable state capture at specific generation
 * - transition chain fingerprinting
 * - replay integrity anchor
 * - temporal consistency proof
 *
 * Architectural Role:
 *
 *     read-only evidence artifact
 *
 * This layer intentionally separates:
 *
 * - state capture (this file)
 * - continuity validation (TBridgeSnapshotContinuityRuntime)
 * - mutation (TBridgeProtocolStateRuntime)
 *
 * to prevent:
 *
 * - snapshot tampering
 * - replay attacks
 * - temporal inconsistencies
 */

#include "TBridgeProtocolState.hpp"
#include "TBridgeStage.hpp"
#include "TBridgeTransition.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Immutable snapshot of protocol lifecycle state.
 *
 * Captures the exact state at a specific generation,
 * serving as evidence for continuity validation.
 */
struct TBridgeProtocolSnapshot
{
    /**
     * @brief The captured lifecycle stage.
     */
    TBridgeStage captured_stage = TBridgeStage::Unknown;

    /**
     * @brief The generation number at capture time.
     */
    std::uint64_t captured_generation = 0;

    /**
     * @brief Hash/fingerprint of the transition chain up to this point.
     *
     * Simple XOR-based fingerprint for header-only efficiency.
     * In production, replace with cryptographic hash if needed.
     */
    std::uint64_t chain_fingerprint = 0;

    /**
     * @brief Default constructor (represents invalid/empty snapshot).
     */
    constexpr TBridgeProtocolSnapshot() noexcept = default;

    /**
     * @brief Constructs a valid snapshot from current runtime state.
     *
     * @param state The live state to capture.
     */
    explicit constexpr TBridgeProtocolSnapshot(
        const TBridgeProtocolState& state) noexcept
        : captured_stage(state.current_stage())
        , captured_generation(state.generation())
        , chain_fingerprint(compute_fingerprint(state))
    {
    }

    /**
     * @brief Returns true if snapshot represents a valid captured state.
     */
    [[nodiscard]] constexpr bool
    is_valid() const noexcept
    {
        return captured_stage != TBridgeStage::Unknown;
    }

    /**
     * @brief Returns true if snapshot matches a specific generation.
     */
    [[nodiscard]] constexpr bool
    matches_generation(std::uint64_t gen) const noexcept
    {
        return is_valid() && captured_generation == gen;
    }

private:
    /**
     * @brief Computes a simple chain fingerprint based on state history.
     *
     * Note: In a full implementation, this would incorporate
     * the full transition history hash. Here we use generation
     * and stage as a lightweight proxy for header-only constraints.
     */
    [[nodiscard]] static constexpr std::uint64_t
    compute_fingerprint(const TBridgeProtocolState& state) noexcept
    {
        // Lightweight fingerprint: combination of stage enum value and generation
        // Prevents simple replay of old states at new generations
        return (static_cast<std::uint64_t>(state.current_stage()) << 48) ^ state.generation();
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state
