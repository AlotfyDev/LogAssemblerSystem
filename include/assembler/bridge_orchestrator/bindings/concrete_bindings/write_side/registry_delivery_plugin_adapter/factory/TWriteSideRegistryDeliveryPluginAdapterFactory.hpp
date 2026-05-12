#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/TWriteSideRegistryDeliveryPluginAdapter.hpp"

/**
 * @file TWriteSideRegistryDeliveryPluginAdapterFactory.hpp
 * @brief Factory helpers for the Write Side registry delivery PluginAdapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - construction from descriptor;
 * - construction from core material fields;
 * - no service locator or endpoint resource lookup.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - `from_descriptor`;
 * - `from_fields`;
 * - default config usage.
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
    struct TWriteSideRegistryDeliveryPluginAdapterFactory final
    {
        [[nodiscard]] static constexpr TWriteSideRegistryDeliveryPluginAdapter from_descriptor(
            TWriteSideRegistryDeliveryMaterialDescriptor descriptor,
            TWriteSideRegistryDeliveryPluginAdapterConfig config =
                TWriteSideRegistryDeliveryPluginAdapterConfig::defaults()) noexcept
        {
            return TWriteSideRegistryDeliveryPluginAdapter(descriptor, config);
        }

        [[nodiscard]] static constexpr TWriteSideRegistryDeliveryPluginAdapter from_fields(
            TCorrelationToken token,
            std::string_view material_id,
            std::uint64_t material_size_hint = 0u,
            bool ordered = false,
            TWriteSideRegistryDeliveryPluginAdapterConfig config =
                TWriteSideRegistryDeliveryPluginAdapterConfig::defaults()) noexcept
        {
            return TWriteSideRegistryDeliveryPluginAdapter(
                TWriteSideRegistryDeliveryMaterialDescriptor::default_log_level_envelope(
                    token,
                    material_id,
                    material_size_hint,
                    ordered),
                config);
        }
    };
}
