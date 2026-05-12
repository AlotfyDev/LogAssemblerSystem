#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/terminal_states/TBridgeTerminalState.hpp"

/**
 * @file TBridgeProtocolSnapshot.hpp
 * @brief Read-only bridge-visible protocol-state snapshot.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative protocol-state definition
 * for its Communication Context concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - safe diagnostic and state-inspection projection for a bridge protocol
 *   execution;
 * - future support for session diagnostics, protocol trace views, transition
 *   audit, and controlled test assertions;
 * - snapshot semantics that expose communication state without exposing
 *   endpoint-private runtime state.
 *
 * @section ascc_current_wave Current W02 Implementation Scope
 * This W02 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable bridge-visible protocol
 * state categories, transition records, snapshots, and lifecycle values.
 *
 * - correlation token;
 * - current and previous stage;
 * - terminal state;
 * - bridge result and bridge error;
 * - protocol-family label;
 * - read-only terminal and validity helpers.
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
 * - mutable endpoint-domain state snapshots.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This protocol-state foundation header may depend on W01 primitive carriers
 * and bridge result/error foundations. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolSnapshot final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TBridgeStage current_stage{TBridgeStage::idle};
        TBridgeStage previous_stage{TBridgeStage::idle};
        TBridgeTerminalState terminal_state{TBridgeTerminalState::none};
        TBridgeResult result{TBridgeResult::success()};
        TBridgeError error{TBridgeError::none()};
        std::string_view protocol_family{};

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_state(terminal_state) || is_terminal_bridge_stage(current_stage);
        }

        [[nodiscard]] constexpr bool has_error() const noexcept
        {
            return error.has_error() || result.failed();
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid();
        }

        [[nodiscard]] static constexpr TBridgeProtocolSnapshot make(
            TCorrelationToken token,
            TBridgeStage current,
            TBridgeStage previous,
            TBridgeTerminalState terminal = TBridgeTerminalState::none,
            TBridgeResult bridge_result = TBridgeResult::success(),
            TBridgeError bridge_error = TBridgeError::none(),
            std::string_view family = {}) noexcept
        {
            return TBridgeProtocolSnapshot{
                token,
                current,
                previous,
                terminal,
                bridge_result,
                bridge_error,
                family
            };
        }
    };
}