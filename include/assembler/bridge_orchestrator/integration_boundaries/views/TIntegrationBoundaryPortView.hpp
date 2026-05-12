#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/integration_boundaries/descriptors/TIntegrationBoundaryDescriptor.hpp"

/**
 * @file TIntegrationBoundaryPortView.hpp
 * @brief Read-only view of an abstract integration boundary port.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - compact public view of a future boundary port;
 * - descriptor, readiness label, and correlation only;
 * - no endpoint private state exposure.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - value-only view;
 * - validity helper;
 * - invalid and make factories.
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
    struct TIntegrationBoundaryPortView final
    {
        TIntegrationBoundaryDescriptor descriptor{};
        std::string_view port_name{};
        std::string_view readiness_label{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return descriptor.is_valid() && !port_name.empty();
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryPortView invalid() noexcept
        {
            return TIntegrationBoundaryPortView{};
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryPortView make(
            TIntegrationBoundaryDescriptor boundary,
            std::string_view name,
            std::string_view readiness = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TIntegrationBoundaryPortView{
                boundary,
                name,
                readiness,
                token
            };
        }
    };
}
