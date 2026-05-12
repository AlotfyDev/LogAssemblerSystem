#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"

/**
 * @file TBridgeProtocolTrace.hpp
 * @brief Single bridge protocol trace record.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - lightweight trace record for protocol-state progression;
 * - future source for diagnostics, validation artifacts, bridge reports, and
 *   protocol audits;
 * - trace metadata without persistence or telemetry backend ownership.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - protocol id, session id, from/to stages, step name, correlation, and
 *   note;
 * - validity helper;
 * - factory from step-like stage data.
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
 * - persistent trace sink, telemetry export, or log backend.
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
    struct TBridgeProtocolTrace final
    {
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TSessionId session_id{TSessionId::invalid()};
        TBridgeStage from{TBridgeStage::idle};
        TBridgeStage to{TBridgeStage::idle};
        std::string_view step_name{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return protocol_id.is_valid()
                && session_id.is_valid()
                && from != to
                && correlation.is_valid();
        }

        [[nodiscard]] static constexpr TBridgeProtocolTrace make(
            TBridgeProtocolId id,
            TSessionId session,
            TBridgeStage from_stage,
            TBridgeStage to_stage,
            std::string_view name = {},
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = {}) noexcept
        {
            return TBridgeProtocolTrace{
                id,
                session,
                from_stage,
                to_stage,
                name,
                token,
                text
            };
        }
    };
}
