#pragma once

#include <cstdint>

/**
 * @file TBridgeProtocolId.hpp
 * @brief Opaque bridge protocol identity primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable opaque protocol identifier usable by protocol values, views,
 *   traces, future registries, and bridge diagnostics;
 * - invalid/from_value construction and equality semantics;
 * - no global allocation or registry ownership.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - lightweight integer-backed identity;
 * - constexpr invalid/from_value helpers;
 * - equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - protocol registry allocation or global uniqueness enforcement.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Protocol Model headers may depend on W01 carriers/results/errors,
 * W02 protocol-state foundations, W06 binding model through sessions, W07
 * compatibility through sessions, and W08 session model. They must not include
 * endpoint-domain headers such as log_level_api, write_side, read_side,
 * persistence implementations, telemetry SDKs, or thin C ABI implementation
 * internals.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TBridgeProtocolId invalid() noexcept
        {
            return TBridgeProtocolId{0u};
        }

        [[nodiscard]] static constexpr TBridgeProtocolId from_value(
            std::uint64_t id_value) noexcept
        {
            return TBridgeProtocolId{id_value};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TBridgeProtocolId lhs,
            TBridgeProtocolId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TBridgeProtocolId lhs,
            TBridgeProtocolId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
