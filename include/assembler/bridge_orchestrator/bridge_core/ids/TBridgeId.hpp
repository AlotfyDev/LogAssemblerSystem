#pragma once

#include <cstdint>

/**
 * @file TBridgeId.hpp
 * @brief Opaque bridge identity primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable opaque bridge identifier usable by Bridge Core values, views,
 *   snapshots, future registries, and diagnostics;
 * - invalid/from_value construction and equality semantics;
 * - no global allocation or registry ownership.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - lightweight integer-backed identity;
 * - constexpr invalid/from_value helpers;
 * - equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - bridge registry allocation or global uniqueness enforcement.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBridgeId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TBridgeId invalid() noexcept
        {
            return TBridgeId{0u};
        }

        [[nodiscard]] static constexpr TBridgeId from_value(
            std::uint64_t id_value) noexcept
        {
            return TBridgeId{id_value};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TBridgeId lhs,
            TBridgeId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TBridgeId lhs,
            TBridgeId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
