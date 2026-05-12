#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/protocols/status/TBridgeProtocolStatus.hpp"

/**
 * @file TBridgeProtocolResult.hpp
 * @brief Bridge protocol operation result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - protocol-level result value for declaration, readiness, advancement,
 *   completion, rejection, deferral, and failure;
 * - stable mapping to bridge-level result without endpoint result systems;
 * - future bridge to orchestration planning and diagnostics.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - protocol id, status, bridge result, and note;
 * - success/reject/fail/defer helpers;
 * - result classification helpers.
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
 * - endpoint result interpretation or exception transport.
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
    struct TBridgeProtocolResult final
    {
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeProtocolStatus status{TBridgeProtocolStatus::unknown};
        TBridgeResult bridge_result{TBridgeResult::success()};
        std::string_view note{};

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return bridge_result.succeeded()
                && (status == TBridgeProtocolStatus::ready
                    || status == TBridgeProtocolStatus::active
                    || status == TBridgeProtocolStatus::completed);
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TBridgeProtocolStatus::rejected
                || bridge_result.rejected();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TBridgeProtocolStatus::failed
                || bridge_result.failed();
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TBridgeProtocolStatus::deferred
                || bridge_result.deferred();
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult ready(
            TBridgeProtocolId id,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "protocol ready") noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::ready,
                TBridgeResult::success(token),
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult active(
            TBridgeProtocolId id,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "protocol active") noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::active,
                TBridgeResult::success(token),
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult completed(
            TBridgeProtocolId id,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "protocol completed") noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::completed,
                TBridgeResult::success(token),
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult reject(
            TBridgeProtocolId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::rejected,
                TBridgeResult::reject(reason, token),
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult fail(
            TBridgeProtocolId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::failed,
                TBridgeResult::fail(reason, token),
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBridgeProtocolResult defer(
            TBridgeProtocolId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeProtocolResult{
                id,
                TBridgeProtocolStatus::deferred,
                TBridgeResult::defer(reason, token),
                reason.message
            };
        }
    };
}
