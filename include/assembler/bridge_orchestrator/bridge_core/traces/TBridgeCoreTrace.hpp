#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/protocols/traces/TBridgeProtocolTrace.hpp"

/**
 * @file TBridgeCoreTrace.hpp
 * @brief Bridge Core trace record.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - lightweight trace record for bridge-level model advancement;
 * - future source for diagnostics, validation artifacts, bridge reports, and
 *   model audits;
 * - trace metadata without persistence or telemetry backend ownership.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - bridge id, bridge status, protocol trace, correlation, and note;
 * - validity helper and factory.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - persistent trace sink, telemetry export, or log backend.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBridgeCoreTrace final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeStatus status{TBridgeStatus::unknown};
        TBridgeProtocolTrace protocol_trace{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return bridge_id.is_valid()
                && status != TBridgeStatus::unknown
                && protocol_trace.is_valid()
                && correlation.is_valid();
        }

        [[nodiscard]] static constexpr TBridgeCoreTrace make(
            TBridgeId id,
            TBridgeStatus bridge_status,
            TBridgeProtocolTrace trace,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = {}) noexcept
        {
            return TBridgeCoreTrace{
                id,
                bridge_status,
                trace,
                token,
                text
            };
        }
    };
}
