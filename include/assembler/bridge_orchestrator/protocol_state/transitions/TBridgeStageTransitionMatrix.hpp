#pragma once

#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"

/**
 * @file TBridgeStageTransitionMatrix.hpp
 * @brief Declarative legality matrix for bridge-visible protocol stage transitions.
 *
 * @section ascc_purpose Purpose
 * `TBridgeStageTransitionMatrix` defines which bridge-visible protocol-stage
 * movements are legal before a transition is applied to `TBridgeProtocolState`.
 *
 * `TBridgeProtocolState::apply_transition()` currently accepts any non-self
 * valid transition while the state is not terminal. This matrix provides the
 * stricter production-oriented policy layer needed by diagnostics, readiness
 * checks, tests, and future transition reports.
 *
 * @section relationship_to_protocol_state Relationship To Protocol State
 * This matrix does not mutate state. It should be consulted by future guarded
 * transition paths, reports, and validation tools before a transition is
 * applied by `TBridgeProtocolState`.
 *
 * @section relationship_to_protocols Relationship To Protocols
 * `TBridgeProtocolPlan` and `TBridgeProtocolStep` define expected ordered
 * movement. This matrix defines broad legal stage adjacency.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not mutate protocol state, execute a protocol step, open a
 * session, run a bridge loop, invoke endpoints, move carriers, or own
 * persistence/telemetry.
 */

namespace assembler::communication_context
{
    struct TBridgeStageTransitionMatrix final
    {
        [[nodiscard]] static constexpr bool can_transition(
            TBridgeStage from,
            TBridgeStage to) noexcept
        {
            if (from == to || is_terminal_bridge_stage(from))
            {
                return false;
            }

            if (is_terminal_bridge_stage(to))
            {
                return true;
            }

            switch (from)
            {
                case TBridgeStage::idle:
                    return to == TBridgeStage::session_opening;
                case TBridgeStage::session_opening:
                    return to == TBridgeStage::channel_resolution;
                case TBridgeStage::channel_resolution:
                    return to == TBridgeStage::binding_resolution;
                case TBridgeStage::binding_resolution:
                    return to == TBridgeStage::compatibility_check;
                case TBridgeStage::compatibility_check:
                    return to == TBridgeStage::adapter_readiness;
                case TBridgeStage::adapter_readiness:
                    return to == TBridgeStage::request_preparation;
                case TBridgeStage::request_preparation:
                    return to == TBridgeStage::port_readiness;
                case TBridgeStage::port_readiness:
                    return to == TBridgeStage::admission_request;
                case TBridgeStage::admission_request:
                    return to == TBridgeStage::admission_result;
                case TBridgeStage::admission_result:
                    return to == TBridgeStage::handle_exchange;
                case TBridgeStage::handle_exchange:
                    return to == TBridgeStage::adapter_handle_acceptance;
                case TBridgeStage::adapter_handle_acceptance:
                    return to == TBridgeStage::load_or_delivery_signal;
                case TBridgeStage::load_or_delivery_signal:
                    return to == TBridgeStage::next_destination
                        || to == TBridgeStage::result_consolidation;
                case TBridgeStage::next_destination:
                    return to == TBridgeStage::result_consolidation;
                case TBridgeStage::result_consolidation:
                    return to == TBridgeStage::session_closure
                        || to == TBridgeStage::terminal_success;
                case TBridgeStage::session_closure:
                    return to == TBridgeStage::terminal_success;
                case TBridgeStage::terminal_success:
                case TBridgeStage::terminal_rejected:
                case TBridgeStage::terminal_failed:
                case TBridgeStage::terminal_deferred:
                    return false;
            }

            return false;
        }

        [[nodiscard]] static constexpr bool can_transition(
            TBridgeTransition transition) noexcept
        {
            return transition.is_valid()
                && can_transition(transition.from, transition.to);
        }
    };
}
