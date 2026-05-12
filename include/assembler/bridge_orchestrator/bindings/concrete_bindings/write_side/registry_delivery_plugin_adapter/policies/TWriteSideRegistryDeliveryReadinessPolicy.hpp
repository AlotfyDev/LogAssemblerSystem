#pragma once

#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/carriers/TWriteSideRegistryDeliveryMaterialDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/config/TWriteSideRegistryDeliveryPluginAdapterConfig.hpp"
#include "assembler/communication_context/integration_boundaries/policies/TIntegrationBoundaryPolicy.hpp"

/**
 * @file TWriteSideRegistryDeliveryReadinessPolicy.hpp
 * @brief Readiness policy for Write Side registry delivery material.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - descriptor/config validation helpers;
 * - boundary-handoff readiness check using W13 policy;
 * - no registry acceptance or storage policy.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - static readiness helper;
 * - material descriptor validation;
 * - ordered-delivery compatibility check.
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
    struct TWriteSideRegistryDeliveryReadinessPolicy final
    {
        [[nodiscard]] static constexpr bool descriptor_is_ready(
            const TWriteSideRegistryDeliveryMaterialDescriptor& descriptor) noexcept
        {
            return descriptor.is_valid();
        }

        [[nodiscard]] static constexpr TReadinessView readiness(
            const TWriteSideRegistryDeliveryMaterialDescriptor& descriptor,
            const TWriteSideRegistryDeliveryPluginAdapterConfig& config) noexcept
        {
            if (!config.is_valid())
            {
                return TReadinessView::not_ready(
                    "write_side_registry_delivery_plugin_adapter_config_invalid",
                    descriptor.correlation);
            }

            if (!descriptor.is_valid())
            {
                return TReadinessView::not_ready(
                    "write_side_registry_delivery_material_descriptor_invalid",
                    descriptor.correlation);
            }

            if (descriptor.requires_ordered_delivery && !config.allow_ordered_delivery)
            {
                return TReadinessView::deferred(
                    "write_side_registry_delivery_ordered_delivery_disabled",
                    descriptor.correlation);
            }

            if (!TIntegrationBoundaryPolicy::supports_outbound_handoff(descriptor.registry_boundary))
            {
                return TReadinessView::not_ready(
                    "registry_delivery_boundary_does_not_support_outbound_handoff",
                    descriptor.correlation);
            }

            return TReadinessView::ready(
                descriptor.correlation,
                descriptor.material_size_hint);
        }
    };
}
