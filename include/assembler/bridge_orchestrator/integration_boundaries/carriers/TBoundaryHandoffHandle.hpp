#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/kinds/TIntegrationBoundaryKind.hpp"

/**
 * @file TBoundaryHandoffHandle.hpp
 * @brief Opaque handle for accepted abstract boundary handoff.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - opaque handle returned by abstract boundary ports after accepting a
 *   handoff request;
 * - no endpoint resource ownership;
 * - boundary kind, value, family, and correlation.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - value-only handle;
 * - validity helper;
 * - invalid and make factories;
 * - equality helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete persistence, telemetry, ABI, read-side, or external receiver
 *   integration;
 * - endpoint-domain internals;
 * - adapter/port call wiring for concrete endpoints;
 * - storage, database, file IO, network IO, telemetry export, or logging sinks;
 * - runtime scheduling, service location, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - bridge execution replacement;
 * - ownership over downstream lifecycle or endpoint resources.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W13 may depend on W01-W12 public Communication Context surfaces.
 * It must remain future-facing and abstract. Concrete implementations belong
 * to later dedicated binding waves.
 */

namespace assembler::communication_context
{
    struct TBoundaryHandoffHandle final
    {
        std::uint64_t value{0u};
        TIntegrationBoundaryKind boundary_kind{TIntegrationBoundaryKind::unknown};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view handle_family{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u
                && boundary_kind != TIntegrationBoundaryKind::unknown
                && correlation.is_valid();
        }

        [[nodiscard]] static constexpr TBoundaryHandoffHandle invalid() noexcept
        {
            return TBoundaryHandoffHandle{};
        }

        [[nodiscard]] static constexpr TBoundaryHandoffHandle make(
            std::uint64_t opaque_value,
            TIntegrationBoundaryKind kind,
            TCorrelationToken token,
            std::string_view family = {}) noexcept
        {
            return TBoundaryHandoffHandle{
                opaque_value,
                kind,
                token,
                family
            };
        }

        [[nodiscard]] friend constexpr bool operator==(
            const TBoundaryHandoffHandle& lhs,
            const TBoundaryHandoffHandle& rhs) noexcept
        {
            return lhs.value == rhs.value
                && lhs.boundary_kind == rhs.boundary_kind
                && lhs.correlation == rhs.correlation;
        }

        [[nodiscard]] friend constexpr bool operator!=(
            const TBoundaryHandoffHandle& lhs,
            const TBoundaryHandoffHandle& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
