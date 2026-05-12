#pragma once

#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/plugin_adapters/views/TPluginAdapterView.hpp"
#include "assembler/communication_context/obligations/ports/views/TPortView.hpp"

/**
 * @file TObligationSurfacePair.hpp
 * @brief Bridge-visible pair of compatible obligation surface views.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative obligation-surface
 * definition for Communication Context participants when the full ASCC
 * implementation matures. The final version should preserve:
 *
 * - minimal pair record for one plugin-adapter view and one port view;
 * - future input to binding models, compatibility checks, sessions, protocols,
 *   and bridge setup;
 * - safe surface pairing that does not execute the binding and does not expose
 *   endpoint internals.
 *
 * @section ascc_current_wave Current W05 Implementation Scope
 * This W05 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It defines bridge-visible host-side port
 * obligations and content-side plugin-adapter obligations without binding
 * execution, session execution, protocol execution, bridge orchestration, or
 * endpoint-domain dependency.
 *
 * - plugin adapter view;
 * - port view;
 * - primary-placement compatibility helper;
 * - simple report helper for pre-binding diagnostics.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - session lifecycle or session execution;
 * - concrete adapter-port binding execution;
 * - channel registry or binding registry ownership;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - concrete binding lifecycle or session creation.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This obligation foundation header may depend on W01 primitive carriers,
 * W02 protocol-state concepts where needed, W03 participant descriptors, and
 * W04 channel topology where needed. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TObligationSurfacePair final
    {
        TPluginAdapterView plugin_adapter{};
        TPortView port{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return plugin_adapter.is_valid() && port.is_valid();
        }

        [[nodiscard]] constexpr bool supports_primary_placement_flow() const noexcept
        {
            return is_valid()
                && plugin_adapter.supports_primary_placement_flow()
                && port.supports_primary_placement_flow();
        }

        [[nodiscard]] constexpr TObligationReport report_primary_placement_support() const noexcept
        {
            if (supports_primary_placement_flow())
            {
                return TObligationReport::satisfied(
                    TObligationSide::binding,
                    "primary_placement_surface_pair");
            }

            return TObligationReport::incomplete(
                TObligationSide::binding,
                "primary_placement_surface_pair",
                "plugin adapter and port views do not both satisfy the primary placement flow");
        }

        [[nodiscard]] static constexpr TObligationSurfacePair make(
            TPluginAdapterView plugin_adapter_view,
            TPortView port_view) noexcept
        {
            return TObligationSurfacePair{plugin_adapter_view, port_view};
        }
    };
}