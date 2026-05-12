#pragma once

#include <cstdint>

/**
 * @file TBindingId.hpp
 * @brief Opaque binding identity primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become an authoritative binding-model definition
 * for the Communication Context when the full ASCC implementation matures.
 * The final version should preserve:
 *
 * - stable opaque binding identifier type;
 * - invalid and explicit factory helpers;
 * - equality and validity semantics suitable for registries, diagnostics,
 *   binding views, future sessions, and future bridge snapshots.
 *
 * @section ascc_current_wave Current W06 Implementation Scope
 * This W06 version intentionally implements only the dependency-foundation
 * binding model needed by later phases. It declares binding identity,
 * compatibility, profile, view, and result concepts without session lifecycle,
 * protocol stepping, bridge orchestration, endpoint-domain dependency, or
 * runtime endpoint invocation.
 *
 * - lightweight integer-backed identity;
 * - constexpr invalid/from_value helpers;
 * - no registry ownership and no session allocation.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - session lifecycle or session execution;
 * - protocol execution or bridge orchestration;
 * - endpoint validation internals;
 * - concrete adapter-port invocation;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - binding registry allocation or global uniqueness enforcement.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This binding model header may depend on W01 primitive carriers/results,
 * W02 protocol-state categories where needed, W03 participants, W04 channel
 * topology, and W05 obligation-surface views. It must not include endpoint
 * domain headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBindingId final
    {
        std::uint64_t value{0};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TBindingId invalid() noexcept
        {
            return TBindingId{0u};
        }

        [[nodiscard]] static constexpr TBindingId from_value(
            std::uint64_t id_value) noexcept
        {
            return TBindingId{id_value};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TBindingId lhs,
            TBindingId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TBindingId lhs,
            TBindingId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}