#pragma once

/**
 * @file TBridgeProtocolStateInvariantReport.hpp
 * @brief Diagnostic report for protocol lifecycle invariant violations.
 *
 * IMPORTANT:
 *
 * This entity represents the "forensic evidence" of a lifecycle integrity failure.
 *
 * It is NOT an error log.
 * It IS a structured invariant violation record.
 *
 * Responsibilities:
 *
 * - capture invariant kind
 * - capture violated state snapshot
 * - capture severity level
 * - provide diagnostic context
 *
 * Architectural Role:
 *
 *     diagnostics-grade evidence carrier
 */

#include "TBridgeStage.hpp"
#include "TBridgeTransition.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Classification of invariant violation kinds.
 */
enum class TInvariantViolationKind : std::uint8_t
{
    None = 0,

    /// Lifecycle regression detected (e.g., generation decreased)
    GenerationRegression = 1,

    /// Transition attempted from a terminal state
    TerminalStateMutation = 2,

    /// Invalid stage classification detected in state
    InvalidStageClassification = 3,

    /// Continuity break detected (previous != expected)
    ContinuityBreak = 4,

    /// Internal logic inconsistency (should never happen)
    InternalInconsistency = 5
};

/**
 * @brief Severity level of the invariant violation.
 */
enum class TInvariantSeverity : std::uint8_t
{
    Low = 0,      /// Anomaly detected but system might recover
    Critical = 1, /// Integrity compromised, immediate halt required
    Fatal = 2     /// State corruption confirmed, undefined behavior risk
};

/**
 * @brief Structured report for invariant violations.
 */
struct TBridgeProtocolStateInvariantReport
{
    /**
     * @brief Default constructor (No violation).
     */
    constexpr TBridgeProtocolStateInvariantReport() noexcept = default;

    /**
     * @brief Returns true if a violation was detected.
     */
    [[nodiscard]] constexpr bool
    has_violation() const noexcept
    {
        return kind_ != TInvariantViolationKind::None;
    }

    /**
     * @brief Returns the specific kind of violation.
     */
    [[nodiscard]] constexpr TInvariantViolationKind
    kind() const noexcept
    {
        return kind_;
    }

    /**
     * @brief Returns the severity level.
     */
    [[nodiscard]] constexpr TInvariantSeverity
    severity() const noexcept
    {
        return severity_;
    }

    /**
     * @brief Returns the stage where violation occurred.
     */
    [[nodiscard]] constexpr TBridgeStage
    observed_stage() const noexcept
    {
        return observed_stage_;
    }

    /**
     * @brief Returns the generation counter at violation time.
     */
    [[nodiscard]] constexpr std::uint64_t
    observed_generation() const noexcept
    {
        return observed_generation_;
    }

    // Factory methods for creating specific violation reports
    static constexpr TBridgeProtocolStateInvariantReport
    make_generation_regression(
        TBridgeStage stage,
        std::uint64_t generation) noexcept
    {
        TBridgeProtocolStateInvariantReport report {};
        report.kind_ = TInvariantViolationKind::GenerationRegression;
        report.severity_ = TInvariantSeverity::Critical;
        report.observed_stage_ = stage;
        report.observed_generation_ = generation;
        return report;
    }

    static constexpr TBridgeProtocolStateInvariantReport
    make_terminal_mutation(
        TBridgeStage stage) noexcept
    {
        TBridgeProtocolStateInvariantReport report {};
        report.kind_ = TInvariantViolationKind::TerminalStateMutation;
        report.severity_ = TInvariantSeverity::Fatal;
        report.observed_stage_ = stage;
        report.observed_generation_ = 0;
        return report;
    }

    static constexpr TBridgeProtocolStateInvariantReport
    make_continuity_break(
        TBridgeStage stage,
        std::uint64_t generation) noexcept
    {
        TBridgeProtocolStateInvariantReport report {};
        report.kind_ = TInvariantViolationKind::ContinuityBreak;
        report.severity_ = TInvariantSeverity::Critical;
        report.observed_stage_ = stage;
        report.observed_generation_ = generation;
        return report;
    }

private:
    TInvariantViolationKind kind_ = TInvariantViolationKind::None;
    TInvariantSeverity severity_ = TInvariantSeverity::Low;
    TBridgeStage observed_stage_ = TBridgeStage::Unknown;
    std::uint64_t observed_generation_ = 0;
};

} // namespace assembler::bridge_orchestrator::protocol_state
