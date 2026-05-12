#pragma once

#include <string_view>

/**
 * @file TIntegrationBoundaryKind.hpp
 * @brief Future-facing integration boundary kind taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - stable taxonomy for abstract boundary families;
 * - explicit future-facing categories for persistence, telemetry, thin C ABI,
 *   read-side, in-process receiver, registry delivery, and external receiver
 *   boundaries;
 * - helper functions for safe classification.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - enum class `TIntegrationBoundaryKind`;
 * - future-facing helper;
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
    enum class TIntegrationBoundaryKind
    {
        unknown,
        registry_delivery,
        persistence,
        telemetry,
        thin_c_abi,
        read_side,
        in_process_receiver,
        external_receiver,
        diagnostic,
        custom
    };

    [[nodiscard]] constexpr bool is_future_facing_boundary_kind(
        TIntegrationBoundaryKind kind) noexcept
    {
        return kind == TIntegrationBoundaryKind::persistence
            || kind == TIntegrationBoundaryKind::telemetry
            || kind == TIntegrationBoundaryKind::thin_c_abi
            || kind == TIntegrationBoundaryKind::read_side
            || kind == TIntegrationBoundaryKind::in_process_receiver
            || kind == TIntegrationBoundaryKind::external_receiver
            || kind == TIntegrationBoundaryKind::diagnostic
            || kind == TIntegrationBoundaryKind::custom;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TIntegrationBoundaryKind kind) noexcept
    {
        switch (kind)
        {
            case TIntegrationBoundaryKind::unknown: return "unknown";
            case TIntegrationBoundaryKind::registry_delivery: return "registry_delivery";
            case TIntegrationBoundaryKind::persistence: return "persistence";
            case TIntegrationBoundaryKind::telemetry: return "telemetry";
            case TIntegrationBoundaryKind::thin_c_abi: return "thin_c_abi";
            case TIntegrationBoundaryKind::read_side: return "read_side";
            case TIntegrationBoundaryKind::in_process_receiver: return "in_process_receiver";
            case TIntegrationBoundaryKind::external_receiver: return "external_receiver";
            case TIntegrationBoundaryKind::diagnostic: return "diagnostic";
            case TIntegrationBoundaryKind::custom: return "custom";
        }

        return "unknown";
    }
}
