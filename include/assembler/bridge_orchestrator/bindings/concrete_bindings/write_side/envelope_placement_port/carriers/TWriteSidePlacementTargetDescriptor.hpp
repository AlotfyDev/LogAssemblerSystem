#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TWriteSidePlacementTargetDescriptor.hpp
 * @brief Bridge-visible descriptor for the Write Side placement target.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - endpoint-neutral projection of a Write Side placement host;
 * - destination family, handle family, capacity hint, and ordered-placement
 *   capability without exposing slots, containers, moderators, or rounds;
 * - future extension point for placement-class, backpressure, and target
 *   readiness metadata.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - lightweight target descriptor fields;
 * - validity helper;
 * - default Write Side envelope placement target factory.
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
 * - direct slot/container identifiers or round-manager references.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSidePlacementTargetDescriptor final
    {
        std::string_view destination_family{"write_side"};
        std::string_view handle_family{"write_side_envelope_slot"};
        std::uint64_t capacity_hint{1u};
        bool supports_ordered_placement{true};
        bool accepts_log_level_envelope{true};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !destination_family.empty()
                && !handle_family.empty()
                && capacity_hint > 0u;
        }

        [[nodiscard]] static constexpr TWriteSidePlacementTargetDescriptor defaults() noexcept
        {
            return TWriteSidePlacementTargetDescriptor{};
        }
    };
}
