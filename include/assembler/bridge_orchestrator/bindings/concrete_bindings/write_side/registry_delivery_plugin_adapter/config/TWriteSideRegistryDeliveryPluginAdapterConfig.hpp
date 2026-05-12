#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TWriteSideRegistryDeliveryPluginAdapterConfig.hpp
 * @brief Configuration for the Write Side registry delivery PluginAdapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - adapter id, participant id, display names, default registry destination
 *   family, and behavior toggles;
 * - no endpoint resource configuration;
 * - no downstream registry connection settings.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - value-only config;
 * - validity helper;
 * - default factory.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - the downstream Log Level Records Registry;
 * - persistence, database, file IO, network IO, telemetry export, or logging
 *   sinks;
 * - Write Side slot, slots container, round manager, dispatcher, or reference
 *   precalculator internals;
 * - registry delivery port implementation;
 * - bridge runtime scheduling or endpoint invocation wiring;
 * - downstream lifecycle ownership after handoff.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14C may depend on W01-W13 public Communication Context surfaces.
 * It must not include concrete `assembler/write_side/...` or downstream
 * registry internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideRegistryDeliveryPluginAdapterConfig final
    {
        std::uint64_t adapter_id{14031u};
        std::uint64_t participant_id{14032u};
        std::string_view participant_domain{"write_side"};
        std::string_view participant_family{"registry_delivery_plugin_adapter"};
        std::string_view participant_display_name{"Write Side Registry Delivery PluginAdapter"};
        std::string_view adapter_display_name{"write_side_registry_delivery_plugin_adapter"};
        std::string_view requested_destination_family{"registry_delivery"};
        bool allow_ordered_delivery{true};
        bool emit_boundary_handoff_requests{true};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return adapter_id != 0u
                && participant_id != 0u
                && !participant_domain.empty()
                && !participant_family.empty()
                && !adapter_display_name.empty()
                && !requested_destination_family.empty();
        }

        [[nodiscard]] static constexpr TWriteSideRegistryDeliveryPluginAdapterConfig defaults() noexcept
        {
            return TWriteSideRegistryDeliveryPluginAdapterConfig{};
        }
    };
}
