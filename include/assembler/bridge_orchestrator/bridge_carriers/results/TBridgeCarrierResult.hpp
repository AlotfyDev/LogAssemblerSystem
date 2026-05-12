#pragma once

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/errors/TBridgeCarrierError.hpp"

/**
 * @file TBridgeCarrierResult.hpp
 * @brief Carrier-level result primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical carrier validation/operation result;
 * - correlation-aware carrier result value;
 * - bridge-visible result independent from protocol orchestration result.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - carrier result status enum;
 * - carrier error integration;
 * - success/failure helper constructors.
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
    enum class TBridgeCarrierResultStatus
    {
        success,
        rejected,
        deferred,
        failed
    };

    struct TBridgeCarrierResult final
    {
        TBridgeCarrierResultStatus status;
        TBridgeCarrierError error;
        TCorrelationToken correlation;

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return status == TBridgeCarrierResultStatus::success && !error.has_error();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TBridgeCarrierResultStatus::rejected;
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TBridgeCarrierResultStatus::deferred;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TBridgeCarrierResultStatus::failed || error.has_error();
        }

        [[nodiscard]] static constexpr TBridgeCarrierResult success(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCarrierResult{TBridgeCarrierResultStatus::success, TBridgeCarrierError::none(), token};
        }

        [[nodiscard]] static constexpr TBridgeCarrierResult reject(
            TBridgeCarrierError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCarrierResult{TBridgeCarrierResultStatus::rejected, reason, token};
        }

        [[nodiscard]] static constexpr TBridgeCarrierResult fail(
            TBridgeCarrierError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBridgeCarrierResult{TBridgeCarrierResultStatus::failed, reason, token};
        }
    };
}