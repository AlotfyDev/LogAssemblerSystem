#pragma once

#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/obligations/TPluginAdapterObligationProfile.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/config/TLogLevelAPIEnvelopePluginAdapterConfig.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapterViewBuilder.hpp
 * @brief Bridge-visible view builder for the Log Level API envelope plugin adapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - safe construction of W05 `TPluginAdapterView` for the concrete adapter;
 * - stable participant identity projection for compatibility checks and
 *   bindings;
 * - no exposure of Log Level API internals.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - participant construction helper;
 * - plugin-adapter view construction helper;
 * - default placement-content-provider obligation profile.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Log Level API facade implementation;
 * - Envelope Assembler internals;
 * - content validation internals;
 * - metadata injection or timestamp stabilization internals;
 * - Write Side placement port implementation;
 * - Write Side slot/container/round internals;
 * - bridge orchestration beyond W10 model stepping;
 * - registry, database, persistence, telemetry, scheduler, thread, or ABI behavior;
 * - dynamic plugin loading or runtime dependency injection.
 * - adapter registry or endpoint object ownership.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14A concrete adapter headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPluginAdapter` obligations, and W10 aggregate bridge
 * surfaces for smoke-test compatibility. They must not include concrete
 * `assembler/log_level_api/...` or `assembler/write_side/...` endpoint-domain
 * internals until those domains are separately realized and explicitly bridged.
 */

namespace assembler::communication_context
{
    struct TLogLevelAPIEnvelopePluginAdapterViewBuilder final
    {
        [[nodiscard]] static constexpr TParticipant participant(
            const TLogLevelAPIEnvelopePluginAdapterConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipant::make(
                config.participant_id,
                TParticipantRole::content_provider,
                config.participant_domain,
                config.participant_family,
                config.display_name,
                token);
        }

        [[nodiscard]] static constexpr TPluginAdapterView view(
            const TLogLevelAPIEnvelopePluginAdapterConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPluginAdapterView::make(
                config.adapter_id,
                TParticipantView::from_participant(participant(config, token)),
                TPluginAdapterObligationProfile::placement_content_provider(),
                config.display_name,
                token);
        }
    };
}
