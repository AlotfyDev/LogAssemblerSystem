#pragma once

#include <cstddef>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/protocol_state/snapshots/TBridgeProtocolSnapshot.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/status/TBridgeProtocolStatus.hpp"
#include "assembler/communication_context/protocols/steps/TBridgeProtocolStep.hpp"
#include "assembler/communication_context/sessions/views/TSessionView.hpp"

/**
 * @file TBridgeProtocolFrame.hpp
 * @brief Read-only current bridge protocol frame.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - compact current-frame projection for a protocol value;
 * - future diagnostic and trace record input for bridge setup, session
 *   inspection, and protocol reports;
 * - no endpoint internals or execution handle exposure.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - protocol id, kind, status, session view, protocol snapshot, current
 *   step, step index, total steps, and correlation;
 * - validity and completion helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - mutable protocol execution context or callback frame.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Protocol Model headers may depend on W01 carriers/results/errors,
 * W02 protocol-state foundations, W06 binding model through sessions, W07
 * compatibility through sessions, and W08 session model. They must not include
 * endpoint-domain headers such as log_level_api, write_side, read_side,
 * persistence implementations, telemetry SDKs, or thin C ABI implementation
 * internals.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolFrame final
    {
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeProtocolKind kind{TBridgeProtocolKind::unknown};
        TBridgeProtocolStatus status{TBridgeProtocolStatus::unknown};
        TSessionView session{};
        TBridgeProtocolSnapshot protocol_snapshot{};
        TBridgeProtocolStep current_step{};
        std::size_t step_index{0u};
        std::size_t step_count{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol_id.is_valid()
                && kind != TBridgeProtocolKind::unknown
                && status != TBridgeProtocolStatus::unknown
                && session.is_valid()
                && protocol_snapshot.is_valid()
                && step_count > 0u;
        }

        [[nodiscard]] constexpr bool has_current_step() const noexcept
        {
            return current_step.is_valid()
                && step_index < step_count;
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_protocol_status(status)
                || protocol_snapshot.is_terminal();
        }
    };
}
