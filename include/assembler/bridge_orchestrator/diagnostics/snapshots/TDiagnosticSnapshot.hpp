#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/diagnostics/reports/TDiagnosticReport.hpp"

/**
 * @file TDiagnosticSnapshot.hpp
 * @brief Summary snapshot for bounded diagnostic reports.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - compact summary of a diagnostic report;
 * - count, failure count, highest severity, and rejected-record visibility;
 * - no record storage or export behavior.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - summary value type;
 * - validity helper;
 * - factory from diagnostic report.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - telemetry exporters;
 * - logging framework integration;
 * - persistence, database, file IO, or network IO;
 * - runtime scheduling, service locator, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - endpoint-domain internals;
 * - concrete adapter/port invocation;
 * - ownership or mutation of diagnosed objects;
 * - replacement of Bridge, Protocol, Session, Binding, Channel, Registry, or
 *   concrete binding semantics.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W12 may depend on W01-W11 public Communication Context surfaces.
 * It must remain optional and diagnostic-only. It must not be required by W14
 * concrete bindings or W15 first integration skeleton.
 */

namespace assembler::communication_context
{
    struct TDiagnosticSnapshot final
    {
        std::string_view report_name{};
        std::size_t count{0u};
        std::uint64_t rejected_records{0u};
        std::size_t failure_count{0u};
        TDiagnosticSeverity highest_severity{TDiagnosticSeverity::none};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !report_name.empty();
        }

        [[nodiscard]] constexpr bool has_failures() const noexcept
        {
            return failure_count > 0u;
        }

        template <std::size_t Capacity>
        [[nodiscard]] static constexpr TDiagnosticSnapshot from_report(
            const TDiagnosticReport<Capacity>& report) noexcept
        {
            return TDiagnosticSnapshot{
                report.report_name,
                report.count,
                report.rejected_records,
                report.failure_count(),
                report.highest_severity(),
                report.correlation
            };
        }
    };
}
