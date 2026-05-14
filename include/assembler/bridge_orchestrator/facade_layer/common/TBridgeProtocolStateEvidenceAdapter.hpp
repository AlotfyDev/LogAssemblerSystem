#pragma once

#include <string_view>

#include "assembler/communication_context/facade_layer/common/TBridgeProtocolStateFacadeProjection.hpp"
#include "assembler/communication_context/protocol_state/lifecycle/TBridgeProtocolState.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"

/**
 * @file TBridgeProtocolStateEvidenceAdapter.hpp
 * @brief Common facade adapter for projecting protocol-state evidence.
 *
 * @section ascc_facade_purpose Purpose
 * `TBridgeProtocolStateEvidenceAdapter` is a common ASCC Facade Layer adapter
 * that converts protocol-state runtime evidence into facade-safe projections.
 *
 * The adapter protects the ASCC boundary by ensuring external component-facing
 * surfaces receive read-only evidence derived from `TBridgeProtocolSnapshot`,
 * not mutable `TBridgeProtocolState` references.
 *
 * @section facade_position Facade Layer Position
 * This header belongs to:
 *
 * ```text
 * facade_layer/common/
 * ```
 *
 * It is common because session readiness, protocol readiness, consuming
 * operation reports, diagnostics, and future policy/composition audit surfaces
 * may all need normalized protocol-state evidence.
 *
 * @section relationship_to_protocol_state Relationship To Protocol State
 * The adapter accepts either:
 *
 * ```text
 * TBridgeProtocolState
 * TBridgeProtocolSnapshot
 * ```
 *
 * and emits:
 *
 * ```text
 * TBridgeProtocolStateFacadeProjection
 * ```
 *
 * Canonical mature relationship:
 *
 * ```text
 * TBridgeProtocolState
 *     -> TBridgeProtocolSnapshot
 *     -> TBridgeProtocolStateEvidenceAdapter
 *     -> TBridgeProtocolStateFacadeProjection
 * ```
 *
 * @section relationship_to_sessions_protocols_bridge Relationship To Sessions, Protocols, And Bridge Core
 * `TSession`, `TBridgeProtocol`, and `TBridge` produce or carry protocol-state
 * evidence at different levels. This adapter gives all of them a common facade
 * projection shape without collapsing their responsibilities.
 *
 * @section policy_relationship Policy Relationship
 * Composition-level policy may ask whether ASCC reached a certain stage,
 * terminal state, or error condition. This adapter supplies evidence for that
 * decision, but it does not interpret policy semantics.
 *
 * @section non_responsibilities Non-Responsibilities
 * This header must not implement or expose:
 *
 * - protocol-state mutation;
 * - transition application;
 * - transition legality decisions;
 * - session opening;
 * - protocol stepping;
 * - bridge execution;
 * - adapter/port invocation;
 * - persistence/export backend;
 * - telemetry, IO, threading, async, or scheduler behavior.
 *
 * @section current_shape Current Shape
 * The current adapter is intentionally stateless and constexpr-friendly.
 * Later versions may add evidence ids, provenance refs, and diagnostic report
 * integration without changing the responsibility boundary.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStateEvidenceAdapter final
    {
        [[nodiscard]] static constexpr TBridgeProtocolStateFacadeProjection from_snapshot(
            TBridgeProtocolSnapshot snapshot) noexcept
        {
            return TBridgeProtocolStateFacadeProjection::from_snapshot(snapshot);
        }

        [[nodiscard]] static constexpr TBridgeProtocolStateFacadeProjection from_state(
            const TBridgeProtocolState& state,
            std::string_view protocol_family = {}) noexcept
        {
            return from_snapshot(state.snapshot(protocol_family));
        }
    };
}
