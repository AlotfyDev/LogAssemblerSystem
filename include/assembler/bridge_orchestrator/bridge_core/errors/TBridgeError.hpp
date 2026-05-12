#pragma once

#include <string_view>

/**
 * @file TBridgeError.hpp
 * @brief Bridge-level error category primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical bridge-level error codes;
 * - stable error object usable by bridge results, protocol state, diagnostics,
 *   and later orchestration layers;
 * - bridge-visible failure classification independent from endpoint-private
 *   exception or error systems.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - bridge error enum;
 * - lightweight error object with optional human-readable message;
 * - success/none detection helpers.
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
    enum class TBridgeErrorCode
    {
        none,
        invalid_correlation,
        incompatible_carrier,
        incompatible_binding,
        protocol_violation,
        admission_rejected,
        admission_deferred,
        handle_unavailable,
        endpoint_error,
        timeout,
        internal_error
    };

    struct TBridgeError final
    {
        TBridgeErrorCode code{TBridgeErrorCode::none};
        std::string_view message{};

        [[nodiscard]] constexpr bool has_error() const noexcept
        {
            return code != TBridgeErrorCode::none;
        }

        [[nodiscard]] static constexpr TBridgeError none() noexcept
        {
            return TBridgeError{TBridgeErrorCode::none, {}};
        }

        [[nodiscard]] static constexpr TBridgeError make(
            TBridgeErrorCode error_code,
            std::string_view error_message = {}) noexcept
        {
            return TBridgeError{error_code, error_message};
        }
    };
}