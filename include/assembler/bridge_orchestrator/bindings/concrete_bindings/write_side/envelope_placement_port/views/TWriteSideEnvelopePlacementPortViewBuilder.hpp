#pragma once

#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/views/TParticipantView.hpp"
#include "assembler/communication_context/obligations/ports/obligations/TPortObligationProfile.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/write_side/envelope_placement_port/config/TWriteSideEnvelopePlacementPortConfig.hpp"

/**
 * @file TWriteSideEnvelopePlacementPortViewBuilder.hpp
 * @brief Bridge-visible view builder for the Write Side envelope placement port.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - safe construction of W05 `TPortView` for the concrete placement host;
 * - stable participant identity projection for compatibility checks and
 *   bindings;
 * - no exposure of Write Side internals.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - participant construction helper;
 * - port view construction helper;
 * - default placement-host obligation profile.
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
 * - endpoint registry or write-side object ownership.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideEnvelopePlacementPortViewBuilder final
    {
        [[nodiscard]] static constexpr TParticipant participant(
            const TWriteSideEnvelopePlacementPortConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipant::make(
                config.participant_id,
                TParticipantRole::host_provider,
                config.participant_domain,
                config.participant_family,
                config.display_name,
                token);
        }

        [[nodiscard]] static constexpr TPortView view(
            const TWriteSideEnvelopePlacementPortConfig& config,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TPortView::make(
                config.port_id,
                TParticipantView::from_participant(participant(config, token)),
                TPortObligationProfile::placement_host("write_side_envelope_placement_host"),
                config.display_name,
                token);
        }
    };
}
