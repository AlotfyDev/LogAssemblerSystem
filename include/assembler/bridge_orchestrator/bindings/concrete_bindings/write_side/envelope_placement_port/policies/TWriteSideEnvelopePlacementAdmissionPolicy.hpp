#pragma once

#include "assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/config/TWriteSideEnvelopePlacementPortConfig.hpp"

/**
 * @file TWriteSideEnvelopePlacementAdmissionPolicy.hpp
 * @brief Admission policy for the Write Side envelope placement port.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - endpoint-neutral admission checks for bridge-visible placement requests;
 * - distinction between request compatibility and true write-side slot
 *   allocation;
 * - future extension point for backpressure and target-selection policy.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - config validity check;
 * - payload-kind and destination-family checks;
 * - capacity readiness projection;
 * - no slot/container/round internals.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Write Side slot/container/round implementation;
 * - Slots Container Moderator implementation;
 * - Slots Containers Bundle Agent implementation;
 * - Reference Precalculator implementation;
 * - Dispatcher, registry, persistence, database, telemetry, scheduler, thread, or ABI behavior;
 * - Log Level API envelope assembly or content validation;
 * - direct payload memory movement or endpoint object ownership.
 * - concrete Write Side allocation algorithm.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideEnvelopePlacementAdmissionPolicy final
    {
        [[nodiscard]] static constexpr bool payload_kind_is_supported(
            const TPlacementRequest& request,
            const TWriteSideEnvelopePlacementPortConfig& config) noexcept
        {
            return request.payload_kind == config.accepted_payload_kind;
        }

        [[nodiscard]] static constexpr bool destination_is_supported(
            const TPlacementRequest& request,
            const TWriteSideEnvelopePlacementPortConfig& config) noexcept
        {
            return request.requested_destination_family.empty()
                || request.requested_destination_family == config.accepted_destination_family;
        }

        [[nodiscard]] static constexpr bool request_is_admissible(
            const TPlacementRequest& request,
            const TWriteSideEnvelopePlacementPortConfig& config) noexcept
        {
            return config.is_valid()
                && request.is_valid()
                && payload_kind_is_supported(request, config)
                && destination_is_supported(request, config);
        }

        [[nodiscard]] static constexpr std::uint64_t readiness_capacity_hint(
            const TWriteSideEnvelopePlacementPortConfig& config) noexcept
        {
            return config.is_valid() ? config.capacity_hint : 0u;
        }
    };
}
