#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/capabilities/TIntegrationBoundaryCapability.hpp"
#include "assembler/communication_context/integration_boundaries/directions/TIntegrationBoundaryDirection.hpp"
#include "assembler/communication_context/integration_boundaries/kinds/TIntegrationBoundaryKind.hpp"

/**
 * @file TIntegrationBoundaryDescriptor.hpp
 * @brief Descriptor for future-facing abstract integration boundaries.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - stable value descriptor for boundary identity, kind, direction,
 *   capability mask, family name, and correlation;
 * - no concrete endpoint handle or resource ownership;
 * - helpers for common future-facing descriptors.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - descriptor value type;
 * - validity and capability helpers;
 * - factory helpers for registry delivery, persistence, telemetry, ABI,
 *   read-side, in-process receiver, and custom boundaries.
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
    struct TIntegrationBoundaryDescriptor final
    {
        TIntegrationBoundaryKind kind{TIntegrationBoundaryKind::unknown};
        TIntegrationBoundaryDirection direction{TIntegrationBoundaryDirection::unknown};
        std::uint32_t capability_mask{0u};
        std::string_view boundary_family{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return kind != TIntegrationBoundaryKind::unknown
                && direction != TIntegrationBoundaryDirection::unknown
                && !boundary_family.empty();
        }

        [[nodiscard]] constexpr bool has(
            TIntegrationBoundaryCapability capability) const noexcept
        {
            return has_capability(capability_mask, capability);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor make(
            TIntegrationBoundaryKind boundary_kind,
            TIntegrationBoundaryDirection boundary_direction,
            std::uint32_t capabilities,
            std::string_view family,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TIntegrationBoundaryDescriptor{
                boundary_kind,
                boundary_direction,
                capabilities,
                family,
                token
            };
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor registry_delivery(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::registry_delivery,
                TIntegrationBoundaryDirection::outbound,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::completes_handoff
                    | TIntegrationBoundaryCapability::exposes_readiness,
                "registry_delivery",
                token);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor persistence(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::persistence,
                TIntegrationBoundaryDirection::outbound,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::completes_handoff
                    | TIntegrationBoundaryCapability::emits_acknowledgement
                    | TIntegrationBoundaryCapability::supports_backpressure,
                "persistence",
                token);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor telemetry(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::telemetry,
                TIntegrationBoundaryDirection::outbound,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::supports_batch
                    | TIntegrationBoundaryCapability::supports_diagnostics,
                "telemetry",
                token);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor thin_c_abi(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::thin_c_abi,
                TIntegrationBoundaryDirection::bidirectional,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::completes_handoff
                    | TIntegrationBoundaryCapability::emits_acknowledgement,
                "thin_c_abi",
                token);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor read_side(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::read_side,
                TIntegrationBoundaryDirection::outbound,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::exposes_readiness,
                "read_side",
                token);
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryDescriptor in_process_receiver(
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                TIntegrationBoundaryKind::in_process_receiver,
                TIntegrationBoundaryDirection::outbound,
                TIntegrationBoundaryCapability::accepts_handoff
                    | TIntegrationBoundaryCapability::emits_acknowledgement
                    | TIntegrationBoundaryCapability::exposes_readiness,
                "in_process_receiver",
                token);
        }
    };
}
