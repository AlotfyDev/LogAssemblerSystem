#pragma once

#include "assembler/communication_context/bindings/TBinding.hpp"
#include "assembler/communication_context/bindings/profiles/TBindingProfile.hpp"
#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/channels/policies/TChannelBindingPolicy.hpp"
#include "assembler/communication_context/channels/profiles/TSingleAdapterSinglePortProfile.hpp"
#include "assembler/communication_context/channels/topology/TChannel.hpp"
#include "assembler/communication_context/obligations/surface_pairs/TObligationSurfacePair.hpp"
#include "assembler/communication_context/protocols/common/TBridgeProtocol.hpp"
#include "assembler/communication_context/protocols/plans/TBridgeProtocolPlan.hpp"
#include "assembler/communication_context/sessions/lifecycle/TSession.hpp"
#include "assembler/communication_context/sessions/policies/TSessionPolicy.hpp"
#include "assembler/communication_context/sessions/requests/TSessionOpenRequest.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapterBinding.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPortBinding.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/config/TFirstIntegrationSkeletonConfig.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/ids/TFirstIntegrationSkeletonIdSet.hpp"

/**
 * @file TFirstIntegrationSkeletonModelPlan.hpp
 * @brief Model-declaration plan for the first ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - dependency-ordered construction of channel, binding, session, protocol,
 *   and bridge model objects;
 * - explicit separation between model declaration and endpoint carrier flow;
 * - future extension point for integration registries without owning them.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - channel declaration helper;
 * - binding declaration helper;
 * - session declaration helper;
 * - protocol and bridge declaration helpers;
 * - no endpoint invocation.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete endpoint-domain internals;
 * - Write Side slot/container/round implementation;
 * - Log Level API envelope assembly, validation, metadata, or timestamp internals;
 * - runtime scheduling, threading, async execution, persistence, telemetry, ABI, or database behavior;
 * - replacing W09 protocol model or W10 bridge model-step orchestration;
 * - hiding bridge-visible failure/report states.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W15 may depend on W01-W10, W14A, and W14B public include surfaces.
 * It must not include concrete endpoint-domain headers such as
 * `assembler/log_level_api/...` or `assembler/write_side/...` internals.
 */

namespace assembler::communication_context
{
    struct TFirstIntegrationSkeletonModelPlan final
    {
        using TEnvelopePlacementProtocolPlan = TBridgeProtocolPlan<12>;
        using TEnvelopePlacementProtocol = TBridgeProtocol<12>;
        using TEnvelopePlacementBridge = TBridge<12>;

        [[nodiscard]] static constexpr TChannel declare_channel(
            const TFirstIntegrationSkeletonConfig& config,
            const TLogLevelAPIEnvelopePluginAdapter& adapter,
            const TWriteSideEnvelopePlacementPort& port,
            TCorrelationToken token) noexcept
        {
            const auto ids = TFirstIntegrationSkeletonIdSet::from_config(config);

            return TChannel::declare(
                ids.channel_id,
                TLogLevelAPIEnvelopePluginAdapterViewBuilder::participant(adapter.config(), token),
                TWriteSideEnvelopePlacementPortViewBuilder::participant(port.config(), token),
                TSingleAdapterSinglePortProfile::make(),
                TChannelBindingPolicy::strict_static_one_to_one(
                    TChannelVisibility::boundary_facing,
                    "w15_boundary_facing_static_one_to_one"),
                config.channel_name,
                token);
        }

        [[nodiscard]] static constexpr TObligationSurfacePair make_surface_pair(
            const TLogLevelAPIEnvelopePluginAdapter& adapter,
            const TWriteSideEnvelopePlacementPort& port) noexcept
        {
            return TObligationSurfacePair::make(adapter.view(), port.view());
        }

        [[nodiscard]] static constexpr TBinding declare_binding(
            const TFirstIntegrationSkeletonConfig& config,
            TChannel channel,
            TObligationSurfacePair surface_pair,
            TCorrelationToken token) noexcept
        {
            const auto ids = TFirstIntegrationSkeletonIdSet::from_config(config);

            return TBinding::propose(
                ids.binding_id,
                channel,
                surface_pair,
                TBindingProfile::strict_static_one_to_one("w15_strict_static_binding_profile"),
                config.binding_name,
                token);
        }

        [[nodiscard]] static constexpr TSession open_session(
            const TFirstIntegrationSkeletonConfig& config,
            TBinding binding,
            TCorrelationToken token) noexcept
        {
            const auto ids = TFirstIntegrationSkeletonIdSet::from_config(config);

            return TSession::open(
                TSessionOpenRequest::make(
                    ids.session_id,
                    binding,
                    TSessionPolicy::strict_declaration_session("w15_strict_declaration_session"),
                    config.session_name,
                    token));
        }

        [[nodiscard]] static constexpr TEnvelopePlacementProtocol declare_protocol(
            const TFirstIntegrationSkeletonConfig& config,
            TSession session,
            TCorrelationToken token) noexcept
        {
            const auto ids = TFirstIntegrationSkeletonIdSet::from_config(config);

            return TEnvelopePlacementProtocol::declare(
                ids.protocol_id,
                session,
                TEnvelopePlacementProtocolPlan::envelope_placement_plan(),
                config.protocol_name,
                token);
        }

        [[nodiscard]] static constexpr TEnvelopePlacementBridge declare_bridge(
            const TFirstIntegrationSkeletonConfig& config,
            TEnvelopePlacementProtocol protocol,
            TCorrelationToken token) noexcept
        {
            const auto ids = TFirstIntegrationSkeletonIdSet::from_config(config);

            return TEnvelopePlacementBridge::declare(
                ids.bridge_id,
                protocol,
                TBridgeConfig::bounded_model_run(
                    config.max_bridge_model_steps,
                    "w15_bounded_model_run"),
                config.bridge_name,
                token);
        }
    };
}
