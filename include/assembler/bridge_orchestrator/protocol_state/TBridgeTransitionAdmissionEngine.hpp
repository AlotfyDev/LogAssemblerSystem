#pragma once

/**
 * @file TBridgeTransitionAdmissionEngine.hpp
 * @brief Runtime transition admissibility enforcement layer.
 *
 * IMPORTANT:
 *
 * This is the FIRST true runtime enforcement layer
 * inside the protocol_state subsystem.
 *
 * Responsibilities:
 *
 * - runtime transition admissibility
 * - semantic transition enforcement
 * - rejection normalization
 * - legality evidence generation
 * - runtime-safe lifecycle mutation gating
 *
 * This engine intentionally separates:
 *
 *     transition semantics
 *
 * from:
 *
 *     mutable runtime orchestration
 *
 * Consumed later by:
 *
 * - protocol state runtime
 * - invariant runtime
 * - readiness aggregation
 * - diagnostics runtime
 */

#include "TBridgeStageTransitionMatrix.hpp"

#include <string_view>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Runtime admission result classification.
 */
enum class TTransitionAdmissionResult
{
    Admitted,
    Rejected
};

/**
 * @brief Canonical rejection reasons.
 */
enum class TTransitionRejectionReason
{
    None,

    IllegalTransition,
    TerminalStateViolation,
    InvalidRecoverySemantics,
    RuntimeContinuityViolation,
    Unknown
};

/**
 * @brief Runtime transition admission report.
 *
 * Lightweight runtime evidence object.
 */
struct TTransitionAdmissionReport
{
    TTransitionAdmissionResult result =
        TTransitionAdmissionResult::Rejected;

    TTransitionRejectionReason rejection_reason =
        TTransitionRejectionReason::Unknown;

    bool preserves_continuity = false;
    bool enters_terminal_state = false;

    [[nodiscard]] constexpr bool
    admitted() const noexcept
    {
        return result
            == TTransitionAdmissionResult::Admitted;
    }
};

/**
 * @brief Runtime transition admissibility engine.
 */
class TBridgeTransitionAdmissionEngine
{
public:

    /**
     * @brief Evaluates runtime transition admissibility.
     */
    [[nodiscard]] constexpr TTransitionAdmissionReport
    evaluate(
        const TBridgeTransition& transition) const noexcept
    {
        TTransitionAdmissionReport report {};

        if (!is_transition_legal(transition))
        {
            report.result =
                TTransitionAdmissionResult::Rejected;

            report.rejection_reason =
                TTransitionRejectionReason::IllegalTransition;

            return report;
        }

        if (is_terminal_stage(transition.from))
        {
            report.result =
                TTransitionAdmissionResult::Rejected;

            report.rejection_reason =
                TTransitionRejectionReason::TerminalStateViolation;

            return report;
        }

        if (transition.is_recovery_transition()
            && !is_semantic_recovery_transition(transition))
        {
            report.result =
                TTransitionAdmissionResult::Rejected;

            report.rejection_reason =
                TTransitionRejectionReason::
                    InvalidRecoverySemantics;

            return report;
        }

        report.result =
            TTransitionAdmissionResult::Admitted;

        report.rejection_reason =
            TTransitionRejectionReason::None;

        report.preserves_continuity =
            preserves_runtime_continuity(transition);

        report.enters_terminal_state =
            enters_terminal_state(transition);

        return report;
    }

    /**
     * @brief Returns true if the transition is admissible.
     */
    [[nodiscard]] constexpr bool
    admits(
        const TBridgeTransition& transition) const noexcept
    {
        return evaluate(transition).admitted();
    }
};

/**
 * @brief Converts rejection reasons into stable textual semantics.
 *
 * IMPORTANT:
 *
 * This intentionally returns constexpr-safe static strings.
 *
 * No allocation is performed.
 */
[[nodiscard]] constexpr std::string_view
to_string(
    const TTransitionRejectionReason reason) noexcept
{
    switch (reason)
    {
        case TTransitionRejectionReason::None:
            return "none";

        case TTransitionRejectionReason::IllegalTransition:
            return "illegal_transition";

        case TTransitionRejectionReason::TerminalStateViolation:
            return "terminal_state_violation";

        case TTransitionRejectionReason::InvalidRecoverySemantics:
            return "invalid_recovery_semantics";

        case TTransitionRejectionReason::RuntimeContinuityViolation:
            return "runtime_continuity_violation";

        default:
            return "unknown";
    }
}

} // namespace assembler::bridge_orchestrator::protocol_state
