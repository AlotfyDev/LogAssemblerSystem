#pragma once

#include "assembler/communication_context/integration_boundaries/TIntegrationBoundaryAbstractPorts.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/TWriteSideRegistryDeliveryPluginAdapter.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/carriers/TWriteSideRegistryDeliveryMaterialDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/config/TWriteSideRegistryDeliveryPluginAdapterConfig.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/factory/TWriteSideRegistryDeliveryPluginAdapterFactory.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/policies/TWriteSideRegistryDeliveryReadinessPolicy.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/state/TWriteSideRegistryDeliveryPluginAdapterState.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/views/TWriteSideRegistryDeliveryPluginAdapterViewBuilder.hpp"

/**
 * @file TWriteSideRegistryDeliveryPluginAdapterBinding.hpp
 * @brief Aggregate include for W14C Write Side registry delivery PluginAdapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - single aggregate include for the W14C concrete binding;
 * - stable availability marker;
 * - no extra runtime behavior.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - aggregate include only;
 * - availability marker;
 * - no endpoint implementation.
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
    inline constexpr bool ASCC_W14C_WRITE_SIDE_REGISTRY_DELIVERY_PLUGIN_ADAPTER_AVAILABLE = true;
}
