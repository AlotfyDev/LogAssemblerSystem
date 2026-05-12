#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TPlacementRequest.hpp
 * @brief Bridge-visible placement request carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - content-side request carrier prepared by a plugin adapter for host-side
 *   admission;
 * - future support for payload description, placement requirements, ordering,
 *   capacity hints, and protocol-specific request metadata;
 * - no ownership of the payload or endpoint-private content model.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - correlation-aware placement request value;
 * - payload-kind and size hints;
 * - ordering and destination-family hints;
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
 * - direct payload storage or content validation.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TPlacementRequest final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view payload_kind{};
        std::uint64_t payload_size_hint{0};
        bool requires_ordered_placement{false};
        std::string_view requested_destination_family{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid() && !payload_kind.empty();
        }

        [[nodiscard]] static constexpr TPlacementRequest make(
            TCorrelationToken token,
            std::string_view kind,
            std::uint64_t size_hint = 0u,
            bool ordered = false,
            std::string_view destination_family = {}) noexcept
        {
            return TPlacementRequest{token, kind, size_hint, ordered, destination_family};
        }
    };
}