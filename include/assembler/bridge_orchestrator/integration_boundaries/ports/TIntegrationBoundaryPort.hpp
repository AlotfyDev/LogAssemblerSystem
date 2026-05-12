#pragma once

#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffHandle.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffRequest.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"
#include "assembler/communication_context/integration_boundaries/traits/TIntegrationBoundaryPortTraits.hpp"
#include "assembler/communication_context/integration_boundaries/views/TIntegrationBoundaryPortView.hpp"

/**
 * @file TIntegrationBoundaryPort.hpp
 * @brief CRTP abstract surface for future-facing integration boundary ports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - endpoint-neutral CRTP base for future boundary ports;
 * - required obligations: boundary view, descriptor, readiness, accept,
 *   complete, and reject handoff;
 * - no concrete endpoint transport or lifecycle behavior.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - CRTP forwarding methods;
 * - compile-time static_assert obligation checks;
 * - protected constructor and derived accessors.
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
    template<typename Derived>
    class TIntegrationBoundaryPort
    {
    public:
        using derived_type = Derived;

        [[nodiscard]] constexpr TIntegrationBoundaryPortView boundary_view() const noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_view,
                "Derived integration boundary port must implement boundary_view() const -> TIntegrationBoundaryPortView");

            return derived().boundary_view();
        }

        [[nodiscard]] constexpr TIntegrationBoundaryDescriptor boundary_descriptor() const noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_descriptor,
                "Derived integration boundary port must implement boundary_descriptor() const -> TIntegrationBoundaryDescriptor");

            return derived().boundary_descriptor();
        }

        [[nodiscard]] TReadinessView boundary_readiness(
            const TBoundaryHandoffRequest& request) noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_readiness,
                "Derived integration boundary port must implement boundary_readiness(const TBoundaryHandoffRequest&) -> TReadinessView");

            return derived().boundary_readiness(request);
        }

        [[nodiscard]] TBoundaryHandoffResult accept_boundary_handoff(
            const TBoundaryHandoffRequest& request) noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_accept_handoff,
                "Derived integration boundary port must implement accept_boundary_handoff(const TBoundaryHandoffRequest&) -> TBoundaryHandoffResult");

            return derived().accept_boundary_handoff(request);
        }

        [[nodiscard]] TBoundaryHandoffResult complete_boundary_handoff(
            const TBoundaryHandoffHandle& handle) noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_complete_handoff,
                "Derived integration boundary port must implement complete_boundary_handoff(const TBoundaryHandoffHandle&) -> TBoundaryHandoffResult");

            return derived().complete_boundary_handoff(handle);
        }

        [[nodiscard]] TBoundaryHandoffResult reject_boundary_handoff(
            const TBoundaryHandoffRequest& request) noexcept
        {
            static_assert(
                TIntegrationBoundaryPortTraits<Derived>::has_reject_handoff,
                "Derived integration boundary port must implement reject_boundary_handoff(const TBoundaryHandoffRequest&) -> TBoundaryHandoffResult");

            return derived().reject_boundary_handoff(request);
        }

    protected:
        constexpr TIntegrationBoundaryPort() noexcept = default;

        [[nodiscard]] constexpr Derived& derived() noexcept
        {
            return static_cast<Derived&>(*this);
        }

        [[nodiscard]] constexpr const Derived& derived() const noexcept
        {
            return static_cast<const Derived&>(*this);
        }
    };
}
