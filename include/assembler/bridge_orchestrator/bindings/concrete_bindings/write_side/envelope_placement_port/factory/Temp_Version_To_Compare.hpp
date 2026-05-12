#pragma once

#include "assembler/communication_context/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPort.hpp"

/**
 * @file TWriteSideEnvelopePlacementPortFactory.hpp
 * @brief Factory helpers for Write Side envelope placement port construction.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - stable construction helpers for the W14B concrete host-side port;
 * - future extension point for construction from real Write Side placement
 *   infrastructure descriptors;
 * - no endpoint factory, DI container, or runtime resource ownership.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - creation from default config;
 * - creation from config and target descriptor;
 * - no dynamic allocation.
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
 * - Write Side object factory or runtime plugin loader.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideEnvelopePlacementPortFactory final
    {
        [[nodiscard]] static constexpr TWriteSideEnvelopePlacementPort make_default() noexcept
        {
            return TWriteSideEnvelopePlacementPort{};
        }

        [[nodiscard]] static constexpr TWriteSideEnvelopePlacementPort from_config(
            TWriteSideEnvelopePlacementPortConfig config,
            TWriteSidePlacementTargetDescriptor target =
                TWriteSidePlacementTargetDescriptor::defaults()) noexcept
        {
            return TWriteSideEnvelopePlacementPort(config, target);
        }
    };
}
