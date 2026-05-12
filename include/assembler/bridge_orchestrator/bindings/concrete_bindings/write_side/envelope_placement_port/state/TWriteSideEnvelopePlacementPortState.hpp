#pragma once

#include <cstdint>

#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp"

/**
 * @file TWriteSideEnvelopePlacementPortState.hpp
 * @brief Local bridge-visible state for the Write Side envelope placement port.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Write Side envelope
 * placement host-port binding surface when ASCC matures. The final version
 * should preserve:
 *
 * - minimal host-port state required for concrete binding tests;
 * - last produced placement handle, admission counters, and signal tracking;
 * - future extension point for diagnostics without exposing endpoint runtime
 *   structures.
 *
 * @section ascc_current_wave Current W14B Implementation Scope
 * This W14B version implements the host-side concrete placement port surface
 * only. It adapts bridge-visible placement carriers into a Write Side-facing
 * boundary contract while remaining compatible with W01-W10 Communication
 * Context foundations and W14A Log Level API envelope PluginAdapter.
 *
 * - admission count;
 * - next opaque handle value;
 * - last placement handle;
 * - last load signal;
 * - state mutation helpers.
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
 * - actual slot occupancy state or durable write-side lifecycle state.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14B concrete port headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPort` obligations, and W14A only for integration smoke
 * tests. They must not include concrete `assembler/write_side/...` endpoint
 * internals or concrete `assembler/log_level_api/...` endpoint internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideEnvelopePlacementPortState final
    {
        std::uint64_t next_handle_value{0u};
        std::uint64_t admission_count{0u};
        std::uint64_t completed_load_count{0u};
        TPlacementHandle last_handle{TPlacementHandle::invalid()};
        TLoadSignal last_signal{};

        [[nodiscard]] constexpr bool has_last_handle() const noexcept
        {
            return last_handle.is_valid();
        }

        [[nodiscard]] constexpr bool has_completed_load() const noexcept
        {
            return last_signal.completed();
        }

        constexpr void reset(std::uint64_t seed = 0u) noexcept
        {
            next_handle_value = seed;
            admission_count = 0u;
            completed_load_count = 0u;
            last_handle = TPlacementHandle::invalid();
            last_signal = TLoadSignal{};
        }

        [[nodiscard]] constexpr std::uint64_t allocate_handle_value() noexcept
        {
            if (next_handle_value == 0u)
            {
                return 0u;
            }

            const auto value = next_handle_value;
            ++next_handle_value;
            return value;
        }

        constexpr void record_admission() noexcept
        {
            ++admission_count;
        }

        constexpr void record_handle(TPlacementHandle handle) noexcept
        {
            last_handle = handle;
        }

        constexpr void record_signal(TLoadSignal signal) noexcept
        {
            last_signal = signal;
            if (signal.completed())
            {
                ++completed_load_count;
            }
        }
    };
}
