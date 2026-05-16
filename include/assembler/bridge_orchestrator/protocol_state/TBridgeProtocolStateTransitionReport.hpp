#pragma once

/**
 * @file TBridgeProtocolStateTransitionReport.hpp
 * @brief Immutable diagnostic record of a lifecycle transition event.
 *
 * Responsibilities:
 *
 * - Capture pre/post state context
 * - Record transition intent
 * - Store admission verdict
 * - Classify causality (Reason Kind)
 * - Provide audit trail entry
 *
 * Architectural Role:
 *
 *     Evidence atom for diagnostics and replay analysis.
 */

#include "TBridgeStage.hpp"
#include "TBridgeTransition.hpp"
#include "TBridgeTransitionReasonKind.hpp"

#include <cstdint>

namespace assembler::bridge_orchestrator::protocol_state
{

/**
 * @brief Comprehensive report of a single transition attempt.
 */
struct TProtocolStateTransitionReport
{
    /** The attempted transition definition. */
    TBridgeTransition attempt {};

    /** Actual state BEFORE the attempt. */
    TBridgeStage state_before = TBridgeStage::Unknown;

    /** Actual state AFTER the attempt (same as before if rejected). */
    TBridgeStage state_after = TBridgeStage::Unknown;

    /** Result of the admission engine evaluation. */
    bool admitted = false;

    /** Classified reason for the outcome. */
    TTransitionReasonKind reason_kind = TTransitionReasonKind::Unspecified;

    /** Runtime generation counter at the time of event. */
    std::uint64_t generation = 0;

    /**
     * @brief Returns true if transition was successfully applied.
     */
    [[nodiscard]] constexpr bool
    was_successful() const noexcept
    {
        return admitted && (state_before != state_after);
    }

    /**
     * @brief Returns true if failure was due to safety violation.
     */
    [[nodiscard]] constexpr bool
    is_safety_critical() const noexcept
    {
        return is_safety_violation(reason_kind);
    }
};

} // namespace assembler::bridge_orchestrator::protocol_state
