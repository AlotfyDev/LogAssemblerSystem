#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/bridge_core/frames/TBridgeCoreFrame.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/protocols/views/TBridgeProtocolView.hpp"

/**
 * @file TBridgeCoreSnapshot.hpp
 * @brief Immutable Bridge Core diagnostic snapshot.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - immutable diagnostic snapshot for bridge identity, status, config,
 *   protocol view, current frame, last issue, correlation, and display name;
 * - future bridge between registries, reports, state inspection, and validation
 *   tooling;
 * - no endpoint internals or mutable lifecycle ownership.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - value object with validity, terminal, and issue helpers;
 * - safe bridge-level projection.
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
 * - persistence snapshot or telemetry export payload.
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
    struct TBridgeCoreSnapshot final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeStatus status{TBridgeStatus::unknown};
        TBridgeConfig config{};
        TBridgeProtocolView protocol{};
        TBridgeCoreFrame frame{};
        TBridgeCoreIssue last_issue{TBridgeCoreIssue::none()};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view display_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return bridge_id.is_valid()
                && status != TBridgeStatus::unknown
                && config.is_valid()
                && protocol.is_valid();
        }

        [[nodiscard]] constexpr bool is_terminal() const noexcept
        {
            return is_terminal_bridge_status(status);
        }

        [[nodiscard]] constexpr bool has_issue() const noexcept
        {
            return last_issue.is_present();
        }
    };
}
