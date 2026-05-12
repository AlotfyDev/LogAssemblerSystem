#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TWriteSideEnvelopePlacementPortConfig.hpp
 * @brief Configuration for the Write Side envelope placement port.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - stable concrete port identity, participant identity, domain labels, and
 *   target descriptors for bridge-visible setup;
 * - future extension point for endpoint-neutral placement policy;
 * - no runtime dependency injection, write-side object ownership, or
 *   container configuration.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - port id;
 * - participant id and display labels;
 * - accepted payload kind and destination family;
 * - default handle seed;
 * - validity helper and default factory.
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
 * - concrete write-side runtime configuration.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideEnvelopePlacementPortConfig final
    {
        std::uint64_t port_id{1421u};
        std::uint64_t participant_id{14201u};
        std::string_view participant_domain{"write_side"};
        std::string_view participant_family{"envelope_placement_port"};
        std::string_view display_name{"WriteSide Envelope Placement Port"};
        std::string_view accepted_payload_kind{"log_level_envelope"};
        std::string_view accepted_destination_family{"write_side"};
        std::string_view handle_family{"write_side_envelope_slot"};
        std::uint64_t first_handle_value{4200u};
        std::uint64_t capacity_hint{1u};
        std::uint32_t port_version{1u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return port_id != 0u
                && participant_id != 0u
                && !participant_domain.empty()
                && !participant_family.empty()
                && !accepted_payload_kind.empty()
                && !accepted_destination_family.empty()
                && !handle_family.empty()
                && first_handle_value != 0u
                && capacity_hint > 0u
                && port_version > 0u;
        }

        [[nodiscard]] static constexpr TWriteSideEnvelopePlacementPortConfig defaults() noexcept
        {
            return TWriteSideEnvelopePlacementPortConfig{};
        }
    };
}
