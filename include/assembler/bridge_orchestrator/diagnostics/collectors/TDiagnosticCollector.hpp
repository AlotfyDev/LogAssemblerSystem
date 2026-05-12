#pragma once

#include "assembler/communication_context/diagnostics/reports/TDiagnosticReport.hpp"
#include "assembler/communication_context/diagnostics/snapshots/TDiagnosticSnapshot.hpp"

/**
 * @file TDiagnosticCollector.hpp
 * @brief Bounded in-memory diagnostic collector.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - local bounded collector over `TDiagnosticReport`;
 * - convenience API for adding diagnostics and producing snapshots;
 * - no global singleton, service locator, logger, telemetry exporter, or
 *   persistent sink.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - report wrapper;
 * - append helpers;
 * - snapshot helper;
 * - reset helper.
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
    template <std::size_t Capacity>
    struct TDiagnosticCollector final
    {
        TDiagnosticReport<Capacity> report{
            TDiagnosticReport<Capacity>::make("diagnostic_collector")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return report.is_valid();
        }

        constexpr bool add(TDiagnosticRecord record) noexcept
        {
            return report.append(record);
        }

        constexpr bool add_if_included(
            TDiagnosticRecord record,
            TDiagnosticPolicy policy) noexcept
        {
            return report.append_if_included(record, policy);
        }

        [[nodiscard]] constexpr TDiagnosticSnapshot snapshot() const noexcept
        {
            return TDiagnosticSnapshot::from_report(report);
        }

        constexpr void reset(
            std::string_view name = "diagnostic_collector",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            report = TDiagnosticReport<Capacity>::make(name, token);
        }

        [[nodiscard]] static constexpr TDiagnosticCollector make(
            std::string_view name = "diagnostic_collector",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TDiagnosticCollector{
                TDiagnosticReport<Capacity>::make(name, token)
            };
        }
    };
}
