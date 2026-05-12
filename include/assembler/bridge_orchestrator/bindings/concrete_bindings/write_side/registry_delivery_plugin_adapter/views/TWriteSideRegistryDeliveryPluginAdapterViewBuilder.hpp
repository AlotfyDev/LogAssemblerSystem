#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/config/TWriteSideRegistryDeliveryPluginAdapterConfig.hpp"
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationProfile.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"

/**
 * @file TWriteSideRegistryDeliveryPluginAdapterViewBuilder.hpp
 * @brief View builder for the Write Side registry delivery PluginAdapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - participant and adapter view construction;
 * - content-provider identity for Write Side registry delivery;
 * - no endpoint-private state exposure.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - participant helper;
 * - adapter view helper;
 * - uses W05 delivery-content-provider obligation profile shape.
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
    struct TWriteSideRegistryDeliveryPluginAdapterViewBuilder final
    {
        [[nodiscard]] static constexpr TParticipant participant(
            const TWriteSideRegistryDeliveryPluginAdapterConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipant::make(
                config.participant_id,
                TParticipantRole::content_provider,
                config.participant_domain,
                config.participant_family,
                config.participant_display_name,
                token);
        }

        [[nodiscard]] static constexpr TPluginAdapterObligationProfile delivery_content_provider_profile() noexcept
        {
            return TPluginAdapterObligationProfile{
                TPluginAdapterObligationFamily::delivery_content_provider,
                true,
                true,
                true,
                true,
                true,
                1u,
                "registry_delivery_content_plugin_adapter"
            };
        }

        [[nodiscard]] static constexpr TPluginAdapterView view(
            const TWriteSideRegistryDeliveryPluginAdapterConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            if (!config.is_valid())
            {
                return TPluginAdapterView::invalid();
            }

            return TPluginAdapterView::make(
                config.adapter_id,
                TParticipantView::from_participant(participant(config, token)),
                delivery_content_provider_profile(),
                config.adapter_display_name,
                token);
        }
    };
}
