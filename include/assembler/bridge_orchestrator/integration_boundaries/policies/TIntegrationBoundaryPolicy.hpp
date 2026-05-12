#pragma once

#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"

/**
 * @file TIntegrationBoundaryPolicy.hpp
 * @brief Reusable abstract policy checks for integration boundary ports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - small helper policy for request, descriptor, direction, and capability
 *   checks;
 * - no endpoint validation internals;
 * - no concrete boundary admission algorithm.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - readiness classification for boundary requests;
 * - supports ordered handoff checks;
 * - outbound/inbound direction helpers.
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
    struct TIntegrationBoundaryPolicy final
    {
        [[nodiscard]] static constexpr TReadinessView request_readiness(
            const TBoundaryHandoffRequest& request) noexcept
        {
            if (!request.correlation.is_valid())
            {
                return TReadinessView::not_ready(
                    "boundary_handoff_request_correlation_invalid",
                    request.correlation);
            }

            if (!request.target.is_valid())
            {
                return TReadinessView::not_ready(
                    "boundary_handoff_target_invalid",
                    request.correlation);
            }

            if (!request.target.has(TIntegrationBoundaryCapability::accepts_handoff))
            {
                return TReadinessView::not_ready(
                    "boundary_does_not_accept_handoff",
                    request.correlation);
            }

            if (request.material_kind.empty())
            {
                return TReadinessView::not_ready(
                    "boundary_handoff_material_kind_empty",
                    request.correlation);
            }

            if (request.requires_ordered_handoff
                && !request.target.has(TIntegrationBoundaryCapability::supports_ordering))
            {
                return TReadinessView::deferred(
                    "boundary_ordering_not_supported",
                    request.correlation);
            }

            return TReadinessView::ready(request.correlation, request.material_size_hint);
        }

        [[nodiscard]] static constexpr bool supports_outbound_handoff(
            const TIntegrationBoundaryDescriptor& descriptor) noexcept
        {
            return descriptor.is_valid()
                && can_emit_across_boundary(descriptor.direction)
                && descriptor.has(TIntegrationBoundaryCapability::accepts_handoff);
        }

        [[nodiscard]] static constexpr bool supports_inbound_handoff(
            const TIntegrationBoundaryDescriptor& descriptor) noexcept
        {
            return descriptor.is_valid()
                && can_receive_across_boundary(descriptor.direction)
                && descriptor.has(TIntegrationBoundaryCapability::accepts_handoff);
        }
    };
}
