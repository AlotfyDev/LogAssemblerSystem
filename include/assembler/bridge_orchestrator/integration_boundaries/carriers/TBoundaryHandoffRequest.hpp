#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"

/**
 * @file TBoundaryHandoffRequest.hpp
 * @brief Abstract request to hand material across an integration boundary.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - endpoint-neutral handoff request for future boundary ports;
 * - correlation, target descriptor, material kind, size hint, and ordering
 *   intent;
 * - no payload ownership or serialization format.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - value-only request carrier;
 * - validity helper;
 * - factory helper.
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
    struct TBoundaryHandoffRequest final
    {
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        TIntegrationBoundaryDescriptor target{};
        std::string_view material_kind{};
        std::uint64_t material_size_hint{0u};
        bool requires_ordered_handoff{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return correlation.is_valid()
                && target.is_valid()
                && target.has(TIntegrationBoundaryCapability::accepts_handoff)
                && !material_kind.empty();
        }

        [[nodiscard]] static constexpr TBoundaryHandoffRequest make(
            TCorrelationToken token,
            TIntegrationBoundaryDescriptor boundary,
            std::string_view kind,
            std::uint64_t size_hint = 0u,
            bool ordered = false) noexcept
        {
            return TBoundaryHandoffRequest{
                token,
                boundary,
                kind,
                size_hint,
                ordered
            };
        }
    };
}
