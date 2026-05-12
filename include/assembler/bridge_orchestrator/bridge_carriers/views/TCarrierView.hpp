#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TCarrierView.hpp
 * @brief Minimal bridge-visible carrier diagnostic view.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - safe read-only projection of a bridge carrier;
 * - future support for diagnostics, validation reports, trace displays, and
 *   test assertions without exposing endpoint-private structures;
 * - common carrier classification vocabulary.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - carrier-kind enum;
 * - correlation token;
 * - validity flag;
 * - optional label.
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
    enum class TCarrierKind
    {
        unknown,
        correlation_token,
        placement_request,
        placement_handle,
        admission_result,
        readiness_view,
        load_signal,
        next_destination_request,
        bridge_result,
        bridge_error,
        carrier_result,
        carrier_error
    };

    struct TCarrierView final
    {
        TCarrierKind kind{TCarrierKind::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        bool valid{false};
        std::string_view label{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return valid;
        }

        [[nodiscard]] static constexpr TCarrierView make(
            TCarrierKind carrier_kind,
            TCorrelationToken token,
            bool is_valid_carrier,
            std::string_view display_label = {}) noexcept
        {
            return TCarrierView{carrier_kind, token, is_valid_carrier, display_label};
        }
    };
}