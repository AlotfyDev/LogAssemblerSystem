#pragma once

#include <string_view>

/**
 * @file TIntegrationBoundaryDirection.hpp
 * @brief Direction taxonomy for abstract integration boundaries.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - stable direction vocabulary for outbound, inbound, bidirectional, and
 *   inspection-only boundaries;
 * - no protocol, transport, or endpoint ownership semantics;
 * - helper functions for bridge-oriented classification.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - enum class `TIntegrationBoundaryDirection`;
 * - helper classification;
 * - textual conversion.
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
    enum class TIntegrationBoundaryDirection
    {
        unknown,
        outbound,
        inbound,
        bidirectional,
        inspection_only
    };

    [[nodiscard]] constexpr bool can_emit_across_boundary(
        TIntegrationBoundaryDirection direction) noexcept
    {
        return direction == TIntegrationBoundaryDirection::outbound
            || direction == TIntegrationBoundaryDirection::bidirectional;
    }

    [[nodiscard]] constexpr bool can_receive_across_boundary(
        TIntegrationBoundaryDirection direction) noexcept
    {
        return direction == TIntegrationBoundaryDirection::inbound
            || direction == TIntegrationBoundaryDirection::bidirectional;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TIntegrationBoundaryDirection direction) noexcept
    {
        switch (direction)
        {
            case TIntegrationBoundaryDirection::unknown: return "unknown";
            case TIntegrationBoundaryDirection::outbound: return "outbound";
            case TIntegrationBoundaryDirection::inbound: return "inbound";
            case TIntegrationBoundaryDirection::bidirectional: return "bidirectional";
            case TIntegrationBoundaryDirection::inspection_only: return "inspection_only";
        }

        return "unknown";
    }
}
