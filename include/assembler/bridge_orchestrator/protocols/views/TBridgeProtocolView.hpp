#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/status/TBridgeProtocolStatus.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"

/**
 * @file TBridgeProtocolView.hpp
 * @brief Read-only bridge protocol projection.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - compact read-only projection for protocol identity, kind, status,
 *   session id, current step index, and display name;
 * - future registry, diagnostics, bridge planning, and reporting surface;
 * - no mutable protocol state or endpoint handles.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - protocol id, kind, session id, status, current step, total steps, and
 *   name;
 * - validity, terminal, and active helpers.
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
 * - mutable protocol execution context or endpoint state.
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
    struct TBridgeProtocolView final
    {
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeProtocolKind kind{TBridgeProtocolKind::unknown};
        TSessionId session_id{TSessionId::invalid()};
        TBridgeProtocolStatus status{TBridgeProtocolStatus::unknown};
        std::size_t step_index{0u};
        std::size_t step_count{0u};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol_id.is_valid()
                && kind != TBridgeProtocolKind::unknown
                && session_id.is_valid()
                && status != TBridgeProtocolStatus::unknown
                && step_count > 0u;
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_protocol_status(status);
        }

        [[nodiscard]] constexpr bool is_active() const noexcept
        {
            return status == TBridgeProtocolStatus::active;
        }

        [[nodiscard]] static constexpr TBridgeProtocolView invalid() noexcept
        {
            return TBridgeProtocolView{};
        }
    };
}
