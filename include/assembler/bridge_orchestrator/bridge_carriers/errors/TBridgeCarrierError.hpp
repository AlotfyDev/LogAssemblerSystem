#pragma once

#include <string_view>

/**
 * @file TBridgeCarrierError.hpp
 * @brief Carrier-level error primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical carrier-level error codes;
 * - distinction between malformed carrier data and bridge orchestration error;
 * - error object suitable for request, handle, readiness, admission, signal,
 *   and destination carrier validation.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - carrier error enum;
 * - lightweight error object;
 * - constexpr none/make helpers.
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
    enum class TBridgeCarrierErrorCode
    {
        none,
        missing_correlation,
        invalid_identifier,
        invalid_request,
        invalid_handle,
        invalid_signal,
        invalid_destination,
        unsupported_payload_kind,
        malformed_view,
        internal_error,
        incompatible_binding
    };

    struct TBridgeCarrierError final
    {
        TBridgeCarrierErrorCode code{TBridgeCarrierErrorCode::none};
        std::string_view message{};

        [[nodiscard]] constexpr bool has_error() const noexcept
        {
            return code != TBridgeCarrierErrorCode::none;
        }

        [[nodiscard]] static constexpr TBridgeCarrierError none() noexcept
        {
            return TBridgeCarrierError{TBridgeCarrierErrorCode::none, {}};
        }

        [[nodiscard]] static constexpr TBridgeCarrierError make(
            TBridgeCarrierErrorCode error_code,
            std::string_view error_message = {}) noexcept
        {
            return TBridgeCarrierError{error_code, error_message};
        }
    };
}