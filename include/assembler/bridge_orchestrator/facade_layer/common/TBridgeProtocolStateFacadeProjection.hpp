#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocol_state/terminal_states/TBridgeTerminalState.hpp"

/**
 * @file TBridgeProtocolStateFacadeProjection.hpp
 * @brief Facade-safe read-only projection of bridge-visible protocol state.
 *
 * @section ascc_facade_purpose Purpose
 * `TBridgeProtocolStateFacadeProjection` is a common ASCC Facade Layer value
 * that exposes a safe immutable subset of protocol-state evidence to the
 * Pipeline Composer, Managerial Facade, Consuming Facade, diagnostics, and
 * future reports.
 *
 * It exists because `TBridgeProtocolState` is a mutable runtime primitive. The
 * facade must not leak mutable protocol-state handles outside the ASCC internal
 * model. External component-facing surfaces should consume snapshots,
 * projections, and reports.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/common/
 * ```
 *
 * It is common because protocol-state evidence may be used by:
 *
 * ```text
 * TAsccSessionReadinessView
 * TAsccProtocolReadinessView
 * TAsccConsumingResult
 * future TAsccFacadeOperationReport
 * future diagnostic export adapters
 * ```
 *
 * @section relationship_to_protocol_state Relationship To Protocol State
 * This projection is derived from `TBridgeProtocolSnapshot`, not directly from
 * mutable `TBridgeProtocolState`.
 *
 * Canonical relationship:
 *
 * ```text
 * TBridgeProtocolState
 *     -> TBridgeProtocolSnapshot
 *     -> TBridgeProtocolStateFacadeProjection
 * ```
 *
 * The projection preserves current stage, previous stage, terminal state,
 * correlation, protocol family label, and derived terminal/error flags.
 *
 * @section relationship_to_sessions_protocols_bridge Relationship To Sessions, Protocols, And Bridge Core
 * Session, protocol, and bridge layers all depend on protocol state evidence:
 *
 * ```text
 * TSessionSnapshot       -> protocol state snapshot
 * TBridgeProtocolFrame   -> session/protocol state evidence
 * TBridgeCoreFrame       -> protocol frame evidence
 * ```
 *
 * This facade projection provides a single safe shape for exposing that
 * evidence outside internal runtime objects.
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may require evidence that a protocol state is
 * terminal, non-terminal, failed, rejected, deferred, or at a specific
 * bridge-visible stage. This projection supplies that evidence without giving
 * policy or Pipeline Composer direct mutation access to ASCC internals.
 *
 * ASCC does not own governance policy semantics. It exposes policy-realizable
 * state evidence through this projection.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol-state mutation;
 * - transition application;
 * - protocol runtime stepping;
 * - bridge orchestration;
 * - session opening;
 * - adapter/port invocation;
 * - endpoint lifecycle;
 * - persistence/export backend;
 * - telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current version is intentionally compact and header-only. Later versions
 * may add projection ids, evidence refs, invariant classifications, and stable
 * export-schema metadata.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStateFacadeProjection final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TBridgeStage current_stage{TBridgeStage::idle};
        TBridgeStage previous_stage{TBridgeStage::idle};
        TBridgeTerminalState terminal_state{TBridgeTerminalState::none};
        bool terminal{false};
        bool has_error{false};
        std::string_view protocol_family{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return terminal;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return terminal_state == TBridgeTerminalState::failed || has_error;
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return terminal_state == TBridgeTerminalState::rejected;
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return terminal_state == TBridgeTerminalState::deferred;
        }

        [[nodiscard]] static constexpr TBridgeProtocolStateFacadeProjection from_snapshot(
            TBridgeProtocolSnapshot snapshot) noexcept
        {
            return TBridgeProtocolStateFacadeProjection{
                snapshot.correlation,
                snapshot.current_stage,
                snapshot.previous_stage,
                snapshot.terminal_state,
                snapshot.is_terminal(),
                snapshot.has_error(),
                snapshot.protocol_family
            };
        }
    };
}
