#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"

/**
 * @file TBridgeCorePolicy.hpp
 * @brief Bridge Core declaration policy and preflight checks.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - bridge-level policy checks over protocol readiness, config validity,
 *   terminal consistency, and budget constraints;
 * - future extension point for bridge setup validation and registry admission;
 * - policy checks without endpoint calls or orchestration side effects.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - config/protocol preflight helper;
 * - issue return value for invalid declarations.
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
 * - runtime policy registry or endpoint-governance enforcement.
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
    struct TBridgeCorePolicy final
    {
        template <std::size_t PlanCapacity>
        [[nodiscard]] static constexpr TBridgeCoreIssue check_declaration(
            TBridgeId bridge_id,
            const TBridgeConfig& config,
            const TBridgeProtocol<PlanCapacity>& protocol,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            if (!bridge_id.is_valid())
            {
                return TBridgeCoreIssue::fatal(
                    TBridgeStatus::rejected,
                    "bridge.id.invalid",
                    "bridge id is invalid",
                    token);
            }

            if (!config.is_valid())
            {
                return TBridgeCoreIssue::fatal(
                    TBridgeStatus::rejected,
                    "bridge.config.invalid",
                    "bridge config is invalid",
                    token);
            }

            if (!protocol.is_valid())
            {
                return TBridgeCoreIssue::fatal(
                    TBridgeStatus::rejected,
                    "bridge.protocol.invalid",
                    "bridge protocol is invalid",
                    token);
            }

            if (config.require_ready_protocol && !protocol.is_ready())
            {
                return TBridgeCoreIssue::block(
                    TBridgeStatus::rejected,
                    "bridge.protocol.not_ready",
                    "bridge requires a ready protocol",
                    token);
            }

            if (config.budget.exhausted())
            {
                return TBridgeCoreIssue::block(
                    TBridgeStatus::exhausted,
                    "bridge.budget.exhausted",
                    "bridge step budget is exhausted",
                    token);
            }

            return TBridgeCoreIssue::none();
        }
    };
}
