#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TAdmissionResult.hpp
 * @brief Host-side admission outcome carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - bridge-visible admission outcome returned by a host-side port;
 * - explicit distinction between accepted, rejected, deferred, and failed
 *   admission;
 * - future extension point for admission metadata while preserving handle
 *   opacity and endpoint non-leakage.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - admission status enum;
 * - correlation-aware admission result value;
 * - reason/error helpers;
 * - no host-internal object exposure.
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
    enum class TAdmissionStatus
    {
        accepted,
        rejected,
        deferred,
        failed
    };

    struct TAdmissionResult final
    {
        TAdmissionStatus status{TAdmissionStatus::accepted};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TBridgeError error{TBridgeError::none()};
        std::string_view reason{};

        [[nodiscard]] constexpr bool accepted() const noexcept
        {
            return status == TAdmissionStatus::accepted && !error.has_error();
        }

        [[nodiscard]] constexpr bool rejected() const noexcept
        {
            return status == TAdmissionStatus::rejected;
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TAdmissionStatus::deferred;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return status == TAdmissionStatus::failed || error.has_error();
        }

        [[nodiscard]] static constexpr TAdmissionResult accept(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAdmissionResult{TAdmissionStatus::accepted, token, TBridgeError::none(), {}};
        }

        [[nodiscard]] static constexpr TAdmissionResult reject(
            std::string_view why,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAdmissionResult{
                TAdmissionStatus::rejected,
                token,
                TBridgeError::make(TBridgeErrorCode::admission_rejected, why),
                why
            };
        }

        [[nodiscard]] static constexpr TAdmissionResult defer(
            std::string_view why,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TAdmissionResult{
                TAdmissionStatus::deferred,
                token,
                TBridgeError::make(TBridgeErrorCode::admission_deferred, why),
                why
            };
        }
    };
}