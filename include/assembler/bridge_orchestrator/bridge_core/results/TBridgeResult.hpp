#pragma once

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TBridgeResult.hpp
 * @brief Bridge-level result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical bridge execution outcome categories;
 * - correlation-aware bridge result value;
 * - common result object usable by protocols, sessions, diagnostics, and bridge
 *   orchestration without exposing endpoint internals.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - bridge result status enum;
 * - lightweight status/error/correlation value object;
 * - success, rejection, deferral, and failure helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBridgeResultStatus
    {
        success,
        rejected,
        deferred,
        failed
    };

    struct TBridgeResult final
    {
        TBridgeResultStatus status{TBridgeResultStatus::success};
        TBridgeError error{TBridgeError::none()};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return status == TBridgeResultStatus::success && !error.has_error();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TBridgeResultStatus::rejected;
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TBridgeResultStatus::deferred;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TBridgeResultStatus::failed || error.has_error();
        }

        [[nodiscard]] static constexpr TBridgeResult success(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeResult{TBridgeResultStatus::success, TBridgeError::none(), token};
        }

        [[nodiscard]] static constexpr TBridgeResult reject(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeResult{TBridgeResultStatus::rejected, reason, token};
        }

        [[nodiscard]] static constexpr TBridgeResult defer(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeResult{TBridgeResultStatus::deferred, reason, token};
        }

        [[nodiscard]] static constexpr TBridgeResult fail(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeResult{TBridgeResultStatus::failed, reason, token};
        }
    };
}