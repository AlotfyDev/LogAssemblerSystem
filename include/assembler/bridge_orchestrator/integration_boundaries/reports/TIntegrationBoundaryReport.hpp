#pragma once

#include <string_view>

#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"
#include "assembler/communication_context/integration_boundaries/results/TBoundaryHandoffResult.hpp"
#include "assembler/communication_context/integration_boundaries/views/TIntegrationBoundaryPortView.hpp"

/**
 * @file TIntegrationBoundaryReport.hpp
 * @brief Compact report for abstract integration boundary handoff observations.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - boundary view, handoff result, optional diagnostic record, and note;
 * - no report persistence or telemetry export;
 * - future suitability for extension-specific reporting.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - value-only report;
 * - validity and failure helpers;
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
    struct TIntegrationBoundaryReport final
    {
        TIntegrationBoundaryPortView boundary{};
        TBoundaryHandoffResult result{};
        TDiagnosticRecord diagnostic{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return boundary.is_valid()
                && result.status != TBoundaryHandoffStatus::unknown;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return result.failed()
                || (diagnostic.is_valid() && diagnostic.failed());
        }

        [[nodiscard]] static constexpr TIntegrationBoundaryReport make(
            TIntegrationBoundaryPortView view,
            TBoundaryHandoffResult handoff_result,
            TDiagnosticRecord diagnostic_record = {},
            std::string_view text = {}) noexcept
        {
            return TIntegrationBoundaryReport{
                view,
                handoff_result,
                diagnostic_record,
                text
            };
        }
    };
}
