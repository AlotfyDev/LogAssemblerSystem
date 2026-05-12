#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"

/**
 * @file TBridgeCoreView.hpp
 * @brief Read-only Bridge Core projection.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - compact bridge view for registries, diagnostics, reports, and future
 *   orchestration dashboards;
 * - stable projection of bridge id, protocol id, status, consumed/max steps,
 *   correlation, and name;
 * - no mutable protocol, session, or endpoint state.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - bridge id, protocol id, status, counters, correlation, and display name;
 * - validity and terminal helpers.
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
 * - endpoint execution handles or registry ownership.
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
    struct TBridgeCoreView final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeStatus status{TBridgeStatus::unknown};
        std::uint32_t consumed_steps{0u};
        std::uint32_t max_steps{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return bridge_id.is_valid()
                && protocol_id.is_valid()
                && status != TBridgeStatus::unknown
                && max_steps > 0u;
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_status(status);
        }

        [[nodiscard]] static constexpr TBridgeCoreView invalid() noexcept
        {
            return TBridgeCoreView{};
        }
    };
}
