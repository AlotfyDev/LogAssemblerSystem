#pragma once

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/terminal_states/TBridgeTerminalState.hpp"
#include "assembler/communication_context/protocol_state/transitions/TBridgeTransition.hpp"

/**
 * @file TBridgeProtocolState.hpp
 * @brief Mutable bridge-visible protocol lifecycle value.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative protocol-state definition
 * for its Communication Context concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - central protocol-state value used by sessions, protocols, diagnostics,
 *   and later bridge orchestration;
 * - controlled bridge-visible lifecycle mutation through transitions;
 * - future support for transition policy, compatibility checks, staged result
 *   consolidation, and protocol-family specialization without endpoint
 *   leakage.
 *
 * @section ascc_current_wave Current W02 Implementation Scope
 * This W02 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable bridge-visible protocol
 * state categories, transition records, snapshots, and lifecycle values.
 *
 * - current and previous bridge stage;
 * - terminal state;
 * - bridge result and error;
 * - transition application;
 * - snapshot generation.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - endpoint lifecycle state;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - endpoint lifecycle ownership or host-side state mutation.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This protocol-state foundation header may depend on W01 primitive carriers
 * and bridge result/error foundations. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolState final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TBridgeStage current_stage{TBridgeStage::idle};
        TBridgeStage previous_stage{TBridgeStage::idle};
        TBridgeTerminalState terminal_state{TBridgeTerminalState::none};
        TBridgeResult result{TBridgeResult::success()};
        TBridgeError error{TBridgeError::none()};

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_state(terminal_state) || is_terminal_bridge_stage(current_stage);
        }

        [[nodiscard]] constexpr bool has_error() const noexcept
        {
            return error.has_error() || result.failed();
        }

        [[nodiscard]] constexpr bool can_transition() const noexcept
        {
            return !is_terminal();
        }

        [[nodiscard]] constexpr TBridgeProtocolSnapshot snapshot(
            std::string_view protocol_family = {}) const noexcept
        {
            return TBridgeProtocolSnapshot::make(
                correlation,
                current_stage,
                previous_stage,
                terminal_state,
                result,
                error,
                protocol_family);
        }

        constexpr bool apply_transition(TBridgeTransition transition) noexcept
        {
            if (!can_transition() || !transition.is_valid())
            {
                return false;
            }

            previous_stage = transition.from;
            current_stage = transition.to;

            if (current_stage == TBridgeStage::terminal_success)
            {
                terminal_state = TBridgeTerminalState::success;
            }
            else if (current_stage == TBridgeStage::terminal_rejected)
            {
                terminal_state = TBridgeTerminalState::rejected;
            }
            else if (current_stage == TBridgeStage::terminal_failed)
            {
                terminal_state = TBridgeTerminalState::failed;
            }
            else if (current_stage == TBridgeStage::terminal_deferred)
            {
                terminal_state = TBridgeTerminalState::deferred;
            }

            return true;
        }

        constexpr void complete(TBridgeResult final_result) noexcept
        {
            result = final_result;

            if (final_result.succeeded())
            {
                current_stage = TBridgeStage::terminal_success;
                terminal_state = TBridgeTerminalState::success;
            }
            else if (final_result.rejected())
            {
                current_stage = TBridgeStage::terminal_rejected;
                terminal_state = TBridgeTerminalState::rejected;
            }
            else if (final_result.deferred())
            {
                current_stage = TBridgeStage::terminal_deferred;
                terminal_state = TBridgeTerminalState::deferred;
            }
            else
            {
                current_stage = TBridgeStage::terminal_failed;
                terminal_state = TBridgeTerminalState::failed;
            }
        }

        [[nodiscard]] static constexpr TBridgeProtocolState start(
            TCorrelationToken token) noexcept
        {
            return TBridgeProtocolState{
                token,
                TBridgeStage::idle,
                TBridgeStage::idle,
                TBridgeTerminalState::none,
                TBridgeResult::success(token),
                TBridgeError::none()
            };
        }
    };
}