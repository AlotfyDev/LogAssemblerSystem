#pragma once

#include <cstdint>

/**
 * @file TDiagnosticId.hpp
 * @brief Opaque diagnostic identifier primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - lightweight diagnostic identifier for records, reports, and future
 *   diagnostic indexes;
 * - no global allocation or registry ownership;
 * - stable invalid/from_value helpers.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - integer-backed opaque ID;
 * - validity helper;
 * - equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - telemetry exporters;
 * - logging framework integration;
 * - persistence, database, file IO, or network IO;
 * - runtime scheduling, service locator, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - ownership or mutation of diagnosed objects;
 * - replacement of Bridge, Protocol, Session, Binding, Channel, Registry, or
 *   concrete binding semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W12 may depend on W01-W11 public Communication Context surfaces.
 * It must remain optional and diagnostic-only. It must not be required by W14
 * concrete bindings or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    struct TDiagnosticId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TDiagnosticId invalid() noexcept
        {
            return TDiagnosticId{0u};
        }

        [[nodiscard]] static constexpr TDiagnosticId from_value(
            std::uint64_t diagnostic_value) noexcept
        {
            return TDiagnosticId{diagnostic_value};
        }

        [[nodiscard]] friend constexpr bool operator==(
            TDiagnosticId lhs,
            TDiagnosticId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            TDiagnosticId lhs,
            TDiagnosticId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
