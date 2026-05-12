#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"

/**
 * @file TBridgeCoreResult.hpp
 * @brief Bridge Core operation result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - bridge-level result value for declaration, step advancement, bounded run,
 *   completion, rejection, failure, and exhaustion;
 * - stable mapping to W01 `TBridgeResult`;
 * - future bridge to orchestration reports and diagnostics.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - bridge id, bridge status, bridge result, executed step count, and note;
 * - success/reject/fail/exhaust helpers;
 * - result classification helpers.
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
 * - endpoint result interpretation or exception transport.
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
    struct TBridgeCoreResult final
    {
        TBridgeId bridge_id{TBridgeId::invalid()};
        TBridgeStatus status{TBridgeStatus::unknown};
        TBridgeResult bridge_result{TBridgeResult::success()};
        std::uint32_t executed_steps{0u};
        std::string_view note{};

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return bridge_result.succeeded()
                && (status == TBridgeStatus::ready
                    || status == TBridgeStatus::running
                    || status == TBridgeStatus::completed);
        }

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return status == TBridgeStatus::completed
                && bridge_result.succeeded();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TBridgeStatus::failed
                || bridge_result.failed();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TBridgeStatus::rejected
                || bridge_result.rejected();
        }

        [[nodiscard]] constexpr bool exhausted() const noexcept
        {
            return status == TBridgeStatus::exhausted;
        }

        [[nodiscard]] static constexpr TBridgeCoreResult ready(
            TBridgeId id,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "bridge ready") noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::ready,
                TBridgeResult::success(token),
                0u,
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreResult running(
            TBridgeId id,
            std::uint32_t steps,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "bridge running") noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::running,
                TBridgeResult::success(token),
                steps,
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreResult completed(
            TBridgeId id,
            std::uint32_t steps,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "bridge completed") noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::completed,
                TBridgeResult::success(token),
                steps,
                text
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreResult rejected(
            TBridgeId id,
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::rejected,
                TBridgeResult::reject(reason, token),
                0u,
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreResult failed(
            TBridgeId id,
            TBridgeError reason,
            std::uint32_t steps,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::failed,
                TBridgeResult::fail(reason, token),
                steps,
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBridgeCoreResult exhausted_budget(
            TBridgeId id,
            std::uint32_t steps,
            TCorrelationToken token = TCorrelationToken::invalid(),
            std::string_view text = "bridge step budget exhausted") noexcept
        {
            return TBridgeCoreResult{
                id,
                TBridgeStatus::exhausted,
                TBridgeResult::defer(
                    TBridgeError::make(TBridgeErrorCode::timeout, text),
                    token),
                steps,
                text
            };
        }
    };
}
