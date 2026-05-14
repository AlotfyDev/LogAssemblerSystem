#pragma once

#include <string_view>

/**
 * @file TBridgeTransitionReasonKind.hpp
 * @brief Normalized reason taxonomy for bridge-visible protocol-state transitions.
 *
 * @section ascc_purpose Purpose
 * `TBridgeTransitionReasonKind` is a descriptive protocol-state helper that
 * provides stable categories for why a transition is attempted or recorded.
 *
 * `TBridgeTransition` currently carries free-form `std::string_view` reason
 * text. That is useful for simple local traces, but production diagnostics,
 * reports, and facade evidence benefit from stable reason categories.
 *
 * @section relationship_to_transition Relationship To TBridgeTransition
 * This type does not replace `TBridgeTransition`. It complements it.
 *
 * @section relationship_to_facade Relationship To Facade Layer
 * Facade reports and readiness views should prefer stable reason kinds when
 * producing diagnostics that might be consumed by Pipeline Composer, tests,
 * compliance gates, or policy-derived composition logic.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not apply transitions, mutate protocol state, decide
 * transition legality, run protocols, execute bridges, call endpoints, or own
 * diagnostics export.
 */

namespace assembler::communication_context
{
    enum class TBridgeTransitionReasonKind
    {
        unknown,
        session_opened,
        session_activated,
        protocol_model_step,
        protocol_transition_accepted,
        protocol_transition_rejected,
        protocol_completed,
        protocol_failed,
        protocol_rejected,
        protocol_deferred,
        bridge_result_consolidated,
        diagnostic_transition,
        manual_transition,
        policy_admitted_transition,
        invalid_transition
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TBridgeTransitionReasonKind kind) noexcept
    {
        switch (kind)
        {
            case TBridgeTransitionReasonKind::unknown: return "unknown";
            case TBridgeTransitionReasonKind::session_opened: return "session_opened";
            case TBridgeTransitionReasonKind::session_activated: return "session_activated";
            case TBridgeTransitionReasonKind::protocol_model_step: return "protocol_model_step";
            case TBridgeTransitionReasonKind::protocol_transition_accepted: return "protocol_transition_accepted";
            case TBridgeTransitionReasonKind::protocol_transition_rejected: return "protocol_transition_rejected";
            case TBridgeTransitionReasonKind::protocol_completed: return "protocol_completed";
            case TBridgeTransitionReasonKind::protocol_failed: return "protocol_failed";
            case TBridgeTransitionReasonKind::protocol_rejected: return "protocol_rejected";
            case TBridgeTransitionReasonKind::protocol_deferred: return "protocol_deferred";
            case TBridgeTransitionReasonKind::bridge_result_consolidated: return "bridge_result_consolidated";
            case TBridgeTransitionReasonKind::diagnostic_transition: return "diagnostic_transition";
            case TBridgeTransitionReasonKind::manual_transition: return "manual_transition";
            case TBridgeTransitionReasonKind::policy_admitted_transition: return "policy_admitted_transition";
            case TBridgeTransitionReasonKind::invalid_transition: return "invalid_transition";
        }

        return "unknown";
    }
}
