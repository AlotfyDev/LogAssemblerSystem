#pragma once

#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffHandle.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"

/**
 * @file TWriteSideRegistryDeliveryPluginAdapterState.hpp
 * @brief Local state for the Write Side registry delivery PluginAdapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - accepted placement handle for W05 PluginAdapter flow;
 * - emitted-load-signal flag;
 * - accepted boundary handoff handle for W13-compatible handoff flow;
 * - no ownership over Write Side slots or downstream registry lifecycle.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - small value state;
 * - reset, handle-acceptance, and boundary-handoff helpers;
 * - no dynamic allocation or endpoint state.
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
    struct TWriteSideRegistryDeliveryPluginAdapterState final
    {
        TPlacementHandle accepted_placement_handle{TPlacementHandle::invalid()};
        bool load_signal_emitted{false};
        TBoundaryHandoffHandle accepted_boundary_handle{TBoundaryHandoffHandle::invalid()};
        bool boundary_handoff_completed{false};

        [[nodiscard]] constexpr bool has_accepted_placement_handle() const noexcept
        {
            return accepted_placement_handle.is_valid();
        }

        [[nodiscard]] constexpr bool has_accepted_boundary_handle() const noexcept
        {
            return accepted_boundary_handle.is_valid();
        }

        constexpr void accept_placement_handle(TPlacementHandle handle) noexcept
        {
            accepted_placement_handle = handle;
            load_signal_emitted = false;
        }

        constexpr void mark_load_signal_emitted() noexcept
        {
            load_signal_emitted = true;
        }

        constexpr void accept_boundary_handoff(TBoundaryHandoffResult result) noexcept
        {
            if (result.accepted())
            {
                accepted_boundary_handle = result.handle;
                boundary_handoff_completed = false;
            }
        }

        constexpr void complete_boundary_handoff(TBoundaryHandoffResult result) noexcept
        {
            if (result.completed())
            {
                accepted_boundary_handle = result.handle;
                boundary_handoff_completed = true;
            }
        }

        constexpr void reset() noexcept
        {
            accepted_placement_handle = TPlacementHandle::invalid();
            load_signal_emitted = false;
            accepted_boundary_handle = TBoundaryHandoffHandle::invalid();
            boundary_handoff_completed = false;
        }
    };
}
