#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"

/**
 * @file TLoadSignal.hpp
 * @brief Bridge-visible content-load signal carrier.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative primitive definition for
 * its Communication Context carrier concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - bridge-visible signal emitted when a content-side adapter reports load
 *   progress or completion against an opaque placement handle;
 * - future extension point for staged load, delivery, and failure signals;
 * - no exposure of payload internals or host-internal placement structures.
 *
 * @section ascc_current_wave Current W01 Implementation Scope
 * This W01 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable value categories,
 * lightweight value types, opaque identifiers, and bridge-visible fields.
 *
 * - load signal kind enum;
 * - correlation-aware signal object;
 * - optional byte-count and note fields;
 * - helpers for started/completed/failed signals.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This primitive foundation header must not include endpoint-domain headers
 * such as log_level_api, write_side, read_side, persistence implementations,
 * telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TLoadSignalKind
    {
        unknown,
        load_started,
        load_completed,
        load_failed
    };

    struct TLoadSignal final
    {
        TLoadSignalKind kind{TLoadSignalKind::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TPlacementHandle placement{TPlacementHandle::invalid()};
        std::uint64_t bytes_loaded{0};
        std::string_view note{};

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return kind == TLoadSignalKind::load_completed;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return kind == TLoadSignalKind::load_failed;
        }

        [[nodiscard]] static constexpr TLoadSignal started(
            TCorrelationToken token,
            TPlacementHandle handle) noexcept
        {
            return TLoadSignal{TLoadSignalKind::load_started, token, handle, 0u, {}};
        }

        [[nodiscard]] static constexpr TLoadSignal completed(
            TCorrelationToken token,
            TPlacementHandle handle,
            std::uint64_t bytes = 0u) noexcept
        {
            return TLoadSignal{TLoadSignalKind::load_completed, token, handle, bytes, {}};
        }

        [[nodiscard]] static constexpr TLoadSignal failed(
            TCorrelationToken token,
            TPlacementHandle handle,
            std::string_view why = {}) noexcept
        {
            return TLoadSignal{TLoadSignalKind::load_failed, token, handle, 0u, why};
        }
    };
}