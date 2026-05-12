#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"

/**
 * @file TWriteSideRegistryDeliveryMaterialDescriptor.hpp
 * @brief Descriptor for Write Side material intended for registry delivery.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the concrete Write Side registry
 * delivery PluginAdapter binding for the Communication Context. The final
 * version should preserve:
 *
 * - stable descriptor for material emitted by Write Side toward registry
 *   delivery;
 * - material id, material kind, size hint, ordering requirement, registry
 *   boundary descriptor, and correlation token;
 * - no ownership of actual envelope payload or downstream registry record.
 *
 * @section ascc_current_wave Current W14C Implementation Scope
 * This W14C version intentionally implements only a lightweight, header-only,
 * concrete content-provider PluginAdapter surface for Write Side material that
 * is intended to be handed toward a registry-delivery boundary.
 *
 * - value-only descriptor;
 * - validity helper;
 * - boundary descriptor helper;
 * - factory helpers for default registry delivery material.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - the downstream Log Level Records Registry;
 * - persistence, database, file IO, network IO, telemetry export, or logging
 *   sinks;
 * - Write Side slot, slots container, round manager, dispatcher, or reference
 *   precalculator internals;
 * - registry delivery port implementation;
 * - bridge runtime scheduling or endpoint invocation wiring;
 * - downstream lifecycle ownership after handoff.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14C may depend on W01-W13 public Communication Context surfaces.
 * It must not include concrete `assembler/write_side/...` or downstream
 * registry internals.
 */

namespace assembler::communication_context
{
    struct TWriteSideRegistryDeliveryMaterialDescriptor final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view material_id{};
        std::string_view material_kind{"log_level_envelope"};
        std::uint64_t material_size_hint{0u};
        bool requires_ordered_delivery{false};
        TIntegrationBoundaryDescriptor registry_boundary{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid()
                && !material_id.empty()
                && !material_kind.empty()
                && registry_boundary.is_valid()
                && registry_boundary.kind == TIntegrationBoundaryKind::registry_delivery
                && registry_boundary.has(TIntegrationBoundaryCapability::accepts_handoff);
        }

        [[nodiscard]] constexpr std::string_view destination_family() const noexcept
        {
            return registry_boundary.boundary_family.empty()
                ? "registry_delivery"
                : registry_boundary.boundary_family;
        }

        [[nodiscard]] static constexpr TWriteSideRegistryDeliveryMaterialDescriptor make(
            TCorrelationToken token,
            std::string_view id,
            std::uint64_t size_hint = 0u,
            bool ordered = false,
            std::string_view kind = "log_level_envelope",
            TIntegrationBoundaryDescriptor boundary =
                TIntegrationBoundaryDescriptor::registry_delivery()) noexcept
        {
            const auto resolved_boundary = boundary.is_valid()
                ? boundary
                : TIntegrationBoundaryDescriptor::registry_delivery(token);

            return TWriteSideRegistryDeliveryMaterialDescriptor{
                token,
                id,
                kind,
                size_hint,
                ordered,
                TIntegrationBoundaryDescriptor::make(
                    resolved_boundary.kind,
                    resolved_boundary.direction,
                    resolved_boundary.capability_mask,
                    resolved_boundary.boundary_family.empty()
                        ? "registry_delivery"
                        : resolved_boundary.boundary_family,
                    token)
            };
        }

        [[nodiscard]] static constexpr TWriteSideRegistryDeliveryMaterialDescriptor default_log_level_envelope(
            TCorrelationToken token,
            std::string_view id,
            std::uint64_t size_hint = 0u,
            bool ordered = false) noexcept
        {
            return make(
                token,
                id,
                size_hint,
                ordered,
                "log_level_envelope",
                TIntegrationBoundaryDescriptor::registry_delivery(token));
        }
    };
}
