#pragma once

#include <cstdint>

/**
 * @file TSessionId.hpp
 * @brief Opaque session identity primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable opaque session identifier usable by sessions, views, snapshots,
 *   diagnostics, future registries, and bridge traces;
 * - invalid/from_value construction and equality semantics;
 * - no global allocation or registry ownership.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - lightweight integer-backed identity;
 * - constexpr invalid/from_value helpers;
 * - equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - session registry allocation or global uniqueness enforcement.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TSessionId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TSessionId invalid() noexcept
        {
            return TSessionId{0u};
        }

        [[nodiscard]] static constexpr TSessionId from_value(
            std::uint64_t id_value) noexcept
        {
            return TSessionId{id_value};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TSessionId lhs,
            TSessionId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TSessionId lhs,
            TSessionId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
