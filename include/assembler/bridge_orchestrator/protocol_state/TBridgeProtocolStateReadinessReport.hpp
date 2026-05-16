#pragma once

/**
 * @file TBridgeProtocolStateReadinessReport.hpp
 * @brief Aggregated readiness diagnostic report for protocol lifecycle.
 *
 * IMPORTANT:
 *
 * This entity is NOT a simple boolean flag.
 *
 * It IS a structured readiness diagnosis container.
 *
 * Responsibilities:
 *
 * - aggregate readiness status from multiple sources
 * - capture specific readiness blockers
 * - provide actionable diagnostic context
 * - support readiness trend analysis
 *
 * Architectural Role:
 *
 *     readiness aggregation substrate
 */

#include "TBridgeStage.hpp"
#include "TBridgeProtocolStateInvariantReport.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Classification of readiness blockers.
 */
enum class TReadinessBlockerKind : std::uint8_t
{
    None = 0,

    /// Lifecycle not started or in initial transient state
    NotInitialized = 1,

    /// Currently in a terminal state (cannot progress)
    TerminalStateReached = 2,

    /// Previous transition was rejected or failed
    TransitionFailure = 3,

    /// Invariant violation detected (critical integrity loss)
    InvariantViolation = 4,

    /// System in a paused or suspended state (if supported)
    Suspended = 5
};

/**
 * @brief Structured readiness diagnostic report.
 */
struct TBridgeProtocolStateReadinessReport
{
    /**
     * @brief Default constructor (Ready state).
     */
    constexpr TBridgeProtocolStateReadinessReport() noexcept = default;

    /**
     * @brief Returns true if system is fully ready for operations.
     */
    [[nodiscard]] constexpr bool
    is_ready() const noexcept
    {
        return blocker_ == TReadinessBlockerKind::None;
    }

    /**
     * @brief Returns the specific blocker preventing readiness.
     */
    [[nodiscard]] constexpr TReadinessBlockerKind
    blocker_kind() const noexcept
    {
        return blocker_;
    }

    /**
     * @brief Returns current stage context for readiness decision.
     */
    [[nodiscard]] constexpr TBridgeStage
    current_stage() const noexcept
    {
        return current_stage_;
    }

    /**
     * @brief Returns associated invariant violation report if any.
     */
    [[nodiscard]] constexpr const TBridgeProtocolStateInvariantReport&
    invariant_report() const noexcept
    {
        return invariant_report_;
    }

    // -----------------------------------------------------------------
    // Factory Methods for creating specific readiness states
    // -----------------------------------------------------------------

    static constexpr TBridgeProtocolStateReadinessReport
    make_ready(TBridgeStage stage) noexcept
    {
        TBridgeProtocolStateReadinessReport report {};
        report.blocker_ = TReadinessBlockerKind::None;
        report.current_stage_ = stage;
        return report;
    }

    static constexpr TBridgeProtocolStateReadinessReport
    make_not_initialized() noexcept
    {
        TBridgeProtocolStateReadinessReport report {};
        report.blocker_ = TReadinessBlockerKind::NotInitialized;
        report.current_stage_ = TBridgeStage::Created;
        return report;
    }

    static constexpr TBridgeProtocolStateReadinessReport
    make_terminal_blocked(TBridgeStage stage) noexcept
    {
        TBridgeProtocolStateReadinessReport report {};
        report.blocker_ = TReadinessBlockerKind::TerminalStateReached;
        report.current_stage_ = stage;
        return report;
    }

    static constexpr TBridgeProtocolStateReadinessReport
    make_invariant_violation(
        TBridgeStage stage,
        const TBridgeProtocolStateInvariantReport& inv_report) noexcept
    {
        TBridgeProtocolStateReadinessReport report {};
        report.blocker_ = TReadinessBlockerKind::InvariantViolation;
        report.current_stage_ = stage;
        report.invariant_report_ = inv_report;
        return report;
    }

private:
    TReadinessBlockerKind blocker_ = TReadinessBlockerKind::None;
    TBridgeStage current_stage_ = TBridgeStage::Unknown;
    TBridgeProtocolStateInvariantReport invariant_report_ {};
};

} // namespace assembler::bridge_orchestrator::protocol_state
