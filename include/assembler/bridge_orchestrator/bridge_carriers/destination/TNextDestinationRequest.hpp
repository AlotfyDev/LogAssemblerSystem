#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"

/**
 * @file TNextDestinationRequest.hpp
 * @brief Bridge-visible next-destination request carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - request carrier used when a content-side adapter or bridge protocol needs
 *   a future destination after current placement/load progress;
 * - future support for continuous workflow, pre-calculated placement, and
 *   bridge-visible destination negotiation;
 * - no access to host-side round manager, slot, or container internals.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - current opaque handle;
 * - correlation token;
 * - destination reason;
 * - validity helper.
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
 * - reference pre-calculation algorithms or write-side round decisions.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TNextDestinationReason
    {
        unknown,
        current_destination_completed,
        current_destination_rejected,
        current_destination_saturated,
        continuous_flow_requested,
        retry_requested
    };

    struct TNextDestinationRequest final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TPlacementHandle current_handle{TPlacementHandle::invalid()};
        TNextDestinationReason reason{TNextDestinationReason::unknown};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid();
        }

        [[nodiscard]] static constexpr TNextDestinationRequest make(
            TCorrelationToken token,
            TPlacementHandle handle,
            TNextDestinationReason why,
            std::string_view text = {}) noexcept
        {
            return TNextDestinationRequest{token, handle, why, text};
        }
    };
}