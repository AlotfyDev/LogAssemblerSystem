#pragma once

#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapterState.hpp
 * @brief Local bridge-visible state for the Log Level API envelope plugin adapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - minimal content-side adapter state required to remember accepted
 *   placement handle and load-signal progress;
 * - future extension point for retry counters and adapter-local diagnostics;
 * - no ownership of host placement internals or real envelope lifecycle.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - accepted handle flag;
 * - emitted signal flag;
 * - accepted placement handle;
 * - validity and reset helpers.
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
 * - endpoint lifecycle state or durable runtime state.
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
    struct TLogLevelAPIEnvelopePluginAdapterState final
    {
        bool placement_handle_accepted{false};
        bool load_signal_emitted{false};
        TPlacementHandle accepted_handle{TPlacementHandle::invalid()};

        [[nodiscard]] constexpr bool has_accepted_handle() const noexcept
        {
            return placement_handle_accepted && accepted_handle.is_valid();
        }

        [[nodiscard]] constexpr bool can_emit_load_signal() const noexcept
        {
            return has_accepted_handle() && !load_signal_emitted;
        }

        constexpr void accept_handle(TPlacementHandle handle) noexcept
        {
            accepted_handle = handle;
            placement_handle_accepted = handle.is_valid();
            load_signal_emitted = false;
        }

        constexpr void mark_load_signal_emitted() noexcept
        {
            if (has_accepted_handle())
            {
                load_signal_emitted = true;
            }
        }

        constexpr void reset() noexcept
        {
            placement_handle_accepted = false;
            load_signal_emitted = false;
            accepted_handle = TPlacementHandle::invalid();
        }
    };
}
