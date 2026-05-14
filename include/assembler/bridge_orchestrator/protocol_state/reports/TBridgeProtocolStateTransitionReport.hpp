#pragma once

#include "assembler/communication_context/protocol_state/reasons/TBridgeTransitionReasonKind.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"

/**
 * @file TBridgeProtocolStateTransitionReport.hpp
 * @brief Evidence report for a protocol-state transition attempt.
 *
 * @section ascc_purpose Purpose
 * `TBridgeProtocolStateTransitionReport` records the before/after evidence of
 * a protocol-state transition attempt, including whether it was accepted and a
 * normalized transition reason kind.
 *
 * The report converts mutable protocol-state movement into safe evidence that
 * can be used by diagnostics, tests, facade readiness, consuming operation
 * reports, and future compliance gates.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not apply transitions, execute protocols, open sessions,
 * run bridges, invoke endpoints, or own persistence/telemetry/export behavior.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStateTransitionReport final
    {
        TBridgeProtocolSnapshot before{};
        TBridgeProtocolSnapshot after{};
        TBridgeTransition transition{};
        TBridgeTransitionReasonKind reason_kind{TBridgeTransitionReasonKind::unknown};
        bool accepted{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return before.is_valid()
                && after.is_valid()
                && transition.is_valid();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return is_valid() && !accepted;
        }

        [[nodiscard]] static constexpr TBridgeProtocolStateTransitionReport make(
            TBridgeProtocolSnapshot before_snapshot,
            TBridgeProtocolSnapshot after_snapshot,
            TBridgeTransition attempted_transition,
            bool was_accepted,
            TBridgeTransitionReasonKind reason = TBridgeTransitionReasonKind::unknown) noexcept
        {
            return TBridgeProtocolStateTransitionReport{
                before_snapshot,
                after_snapshot,
                attempted_transition,
                reason,
                was_accepted
            };
        }
    };
}
