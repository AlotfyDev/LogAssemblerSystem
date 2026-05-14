#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/common/TBridgeProtocolStateFacadeProjection.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"

/**
 * @file TBridgeProtocolStateReadinessView.hpp
 * @brief Managerial facade readiness view over protocol-state evidence.
 *
 * @section ascc_facade_purpose Purpose
 * `TBridgeProtocolStateReadinessView` is part of the ASCC Managerial Facade.
 * It converts facade-safe protocol-state projection data into a readiness
 * judgment that can feed session readiness, protocol readiness, bridge
 * readiness, and component admission decisions.
 *
 * It is not a protocol-state runtime object. It does not mutate stage state.
 * It does not apply transitions. It only reports whether the projected state is
 * acceptable for the selected ASCC managerial context.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/managerial/
 * ```
 *
 * Managerial surface answers:
 *
 * ```text
 * Is this bridge-visible protocol state acceptable for the current admission,
 * bootstrap, or operation-readiness decision?
 * ```
 *
 * @section relationship_to_protocol_state Relationship To Protocol State
 * The view consumes `TBridgeProtocolStateFacadeProjection`, which should be
 * produced from `TBridgeProtocolSnapshot` through
 * `TBridgeProtocolStateEvidenceAdapter`.
 *
 * @section relationship_to_sessions_protocols_bridge Relationship To Sessions, Protocols, And Bridge Core
 * Session admission may need a state at `session_opening`.
 * Protocol declaration may need a non-terminal state aligned with the first
 * protocol step. Bridge operation may reject already-terminal or error states.
 *
 * This readiness view provides a generic managerial projection while leaving
 * exact admission policy to the calling facade policy.
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may require or forbid terminal states, failure
 * states, or specific stage reachability. This view exposes local ASCC state
 * readiness evidence; it does not own global policy semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol-state mutation;
 * - transition application;
 * - protocol plan execution;
 * - session opening;
 * - bridge orchestration;
 * - endpoint invocation;
 * - carrier movement;
 * - persistence, telemetry, IO, threading, async, or scheduler behavior.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStateReadinessView final
    {
        TBridgeProtocolStateFacadeProjection projection{};
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        bool stage_known{false};
        bool terminal_allowed{false};
        bool error_allowed{false};
        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return projection.is_valid()
                && status != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid() && status == TAsccComponentReadinessStatus::ready;
        }

        [[nodiscard]] static constexpr TBridgeProtocolStateReadinessView evaluate(
            TBridgeProtocolStateFacadeProjection state_projection,
            bool allow_terminal = false,
            bool allow_error = false,
            std::string_view note = {}) noexcept
        {
            const bool terminal_ok = allow_terminal || !state_projection.terminal;
            const bool error_ok = allow_error || !state_projection.has_error;
            const bool is_ready = state_projection.is_valid()
                && terminal_ok
                && error_ok;

            return TBridgeProtocolStateReadinessView{
                state_projection,
                is_ready
                    ? TAsccComponentReadinessStatus::ready
                    : TAsccComponentReadinessStatus::blocked,
                state_projection.current_stage != TBridgeStage::idle
                    || !state_projection.protocol_family.empty(),
                allow_terminal,
                allow_error,
                note
            };
        }
    };
}
