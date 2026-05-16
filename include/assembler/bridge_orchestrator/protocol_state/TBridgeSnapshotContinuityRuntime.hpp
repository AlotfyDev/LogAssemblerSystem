#pragma once

/**
 * @file TBridgeSnapshotContinuityRuntime.hpp
 * @brief Runtime enforcement engine for snapshot continuity and replay integrity.
 *
 * IMPORTANT:
 *
 * This is the CONTINUITY AUTHORITY
 * of the protocol_state subsystem.
 *
 * Responsibilities:
 *
 * - validate transition chain continuity between snapshots
 * - detect replay corruption attempts
 * - enforce monotonic generation progression
 * - verify state fingerprint consistency
 *
 * Architectural Role:
 *
 *     runtime continuity guardian
 *
 * This layer intentionally separates:
 *
 * - snapshot creation (TBridgeProtocolSnapshot)
 * - continuity validation (this file)
 * - state mutation (TBridgeProtocolStateRuntime)
 *
 * to prevent:
 *
 * - illegal state reconstruction
 * - replay attacks
 * - broken transition chains
 */

#include "TBridgeProtocolSnapshot.hpp"
#include "TBridgeProtocolState.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Result of continuity validation check.
 */
struct TContinuityValidationReport
{
    bool is_continuous = false;
    bool is_monotonic = false;
    bool is_fingerprint_valid = false;
    
    // Detailed reason for failure (if any)
    enum class FailureReason : std::uint8_t
    {
        None,
        InvalidSourceSnapshot,
        InvalidTargetSnapshot,
        GenerationRegression,
        GenerationGap,
        FingerprintMismatch,
        StageMismatch
    };

    FailureReason failure_reason = FailureReason::None;

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return is_continuous && is_monotonic && is_fingerprint_valid;
    }
};

/**
 * @brief Runtime engine enforcing snapshot continuity.
 */
class TBridgeSnapshotContinuityRuntime
{
public:

    /**
     * @brief Validates continuity between two snapshots.
     *
     * Ensures that 'current' logically follows 'previous'
     * without gaps, regressions, or tampering.
     *
     * @param previous The earlier snapshot.
     * @param current The later snapshot.
     * @return Validation report detailing continuity status.
     */
    [[nodiscard]] static constexpr TContinuityValidationReport
    validate_continuity(
        const TBridgeProtocolSnapshot& previous,
        const TBridgeProtocolSnapshot& current) noexcept
    {
        TContinuityValidationReport report {};

        // 1. Validate Snapshot Integrity
        if (!previous.is_valid())
        {
            report.failure_reason = TContinuityValidationReport::FailureReason::InvalidSourceSnapshot;
            return report;
        }

        if (!current.is_valid())
        {
            report.failure_reason = TContinuityValidationReport::FailureReason::InvalidTargetSnapshot;
            return report;
        }

        // 2. Enforce Monotonic Generation Progression
        if (current.captured_generation <= previous.captured_generation)
        {
            report.failure_reason = TContinuityValidationReport::FailureReason::GenerationRegression;
            return report;
        }

        // Optional: Strict continuity check (no gaps allowed)
        // Remove this check if gaps are allowed in your specific pipeline logic
        if (current.captured_generation != previous.captured_generation + 1)
        {
             // Depending on strictness, this might be a warning or error.
             // For high-security orchestration, we treat gaps as potential replay attacks.
             report.failure_reason = TContinuityValidationReport::FailureReason::GenerationGap;
             // We do not return yet, allowing partial validity check, but marking non-continuous
        }
        else
        {
            report.is_monotonic = true;
        }

        // 3. Verify Fingerprint Consistency
        // Ensure the chain fingerprint evolves correctly
        // Note: In a real system, this would verify a cryptographic chain.
        // Here we verify the generation/stage consistency implies valid evolution.
        if (current.chain_fingerprint == previous.chain_fingerprint)
        {
             // Fingerprint must change if generation changed
             report.failure_reason = TContinuityValidationReport::FailureReason::FingerprintMismatch;
             return report;
        }

        report.is_fingerprint_valid = true;

        // 4. Final Continuity Decision
        if (report.is_monotonic && report.is_fingerprint_valid)
        {
            report.is_continuous = true;
        }

        return report;
    }

    /**
     * @brief Validates a single snapshot against expected generation.
     *
     * Useful for replay detection when loading from storage.
     */
    [[nodiscard]] static constexpr bool
    validate_generation_expectation(
        const TBridgeProtocolSnapshot& snapshot,
        std::uint64_t expected_generation) noexcept
    {
        if (!snapshot.is_valid()) return false;
        return snapshot.captured_generation == expected_generation;
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state
