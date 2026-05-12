#pragma once

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/sessions/status/TSessionStatus.hpp"

/**
 * @file TSessionResult.hpp
 * @brief Session operation result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - bridge-visible result for session opening, closing, rejection, and
 *   failure operations;
 * - stable mapping to bridge-level results without endpoint internals;
 * - future use in session registry, bridge setup, and protocol bootstrap
 *   gates.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - session id, resulting status, and bridge result;
 * - success/reject/fail/defer helpers;
 * - derived status helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - exception transport or endpoint result interpretation.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TSessionResult final
    {
        TSessionId session_id{TSessionId::invalid()};
        TSessionStatus status{TSessionStatus::unknown};
        TBridgeResult bridge_result{TBridgeResult::success()};

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return bridge_result.succeeded()
                && status != TSessionStatus::unknown
                && !is_terminal_failure();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TSessionStatus::rejected || bridge_result.rejected();
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TSessionStatus::deferred || bridge_result.deferred();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TSessionStatus::failed || bridge_result.failed();
        }

        [[nodiscard]] constexpr bool is_terminal_failure() const noexcept
        {
            return rejected() || deferred() || failed();
        }

        [[nodiscard]] static constexpr TSessionResult opened(
            TSessionId id,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionResult{
                id,
                TSessionStatus::open,
                TBridgeResult::success(token)
            };
        }

        [[nodiscard]] static constexpr TSessionResult completed(
            TSessionId id,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionResult{
                id,
                TSessionStatus::completed,
                TBridgeResult::success(token)
            };
        }

        [[nodiscard]] static constexpr TSessionResult reject(
            TSessionId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionResult{
                id,
                TSessionStatus::rejected,
                TBridgeResult::reject(reason, token)
            };
        }

        [[nodiscard]] static constexpr TSessionResult fail(
            TSessionId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionResult{
                id,
                TSessionStatus::failed,
                TBridgeResult::fail(reason, token)
            };
        }

        [[nodiscard]] static constexpr TSessionResult defer(
            TSessionId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TSessionResult{
                id,
                TSessionStatus::deferred,
                TBridgeResult::defer(reason, token)
            };
        }
    };
}
