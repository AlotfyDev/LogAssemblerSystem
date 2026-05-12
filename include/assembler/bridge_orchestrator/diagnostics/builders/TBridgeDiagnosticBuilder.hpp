#pragma once

#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/snapshots/TBridgeCoreSnapshot.hpp"
#include "assembler/communication_context/bridge_core/traces/TBridgeCoreTrace.hpp"
#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"

/**
 * @file TBridgeDiagnosticBuilder.hpp
 * @brief Diagnostic builders for Bridge Core values.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - endpoint-neutral builders that translate bridge result/snapshot/trace
 *   state into diagnostic records;
 * - no mutation of bridge objects;
 * - no bridge stepping or endpoint invocation.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - diagnostic record from `TBridgeCoreResult`;
 * - diagnostic record from `TBridgeCoreSnapshot`;
 * - diagnostic record from `TBridgeCoreTrace`.
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
    struct TBridgeDiagnosticBuilder final
    {
        [[nodiscard]] static constexpr TDiagnosticRecord from_result(
            TDiagnosticId id,
            const TBridgeCoreResult& result,
            std::string_view subject = "bridge_core_result") noexcept
        {
            if (result.completed())
            {
                return TDiagnosticRecord::info(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.completed",
                    subject,
                    result.note,
                    result.bridge_result.correlation);
            }

            if (result.exhausted())
            {
                return TDiagnosticRecord::warning(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.exhausted",
                    subject,
                    result.note,
                    result.bridge_result.correlation);
            }

            if (result.rejected())
            {
                return TDiagnosticRecord::error(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.rejected",
                    subject,
                    result.note,
                    result.bridge_result.correlation);
            }

            if (result.failed())
            {
                return TDiagnosticRecord::critical(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.failed",
                    subject,
                    result.note,
                    result.bridge_result.correlation);
            }

            if (result.succeeded())
            {
                return TDiagnosticRecord::info(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.succeeded",
                    subject,
                    result.note,
                    result.bridge_result.correlation);
            }

            return TDiagnosticRecord::warning(
                id,
                TDiagnosticCategory::bridge_core,
                "bridge.indeterminate",
                subject,
                result.note,
                result.bridge_result.correlation);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord from_snapshot(
            TDiagnosticId id,
            const TBridgeCoreSnapshot& snapshot,
            std::string_view subject = "bridge_core_snapshot") noexcept
        {
            if (!snapshot.is_valid())
            {
                return TDiagnosticRecord::error(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.snapshot.invalid",
                    subject,
                    "bridge snapshot is invalid",
                    snapshot.correlation);
            }

            if (snapshot.has_issue())
            {
                return TDiagnosticRecord::warning(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.snapshot.has_issue",
                    subject,
                    snapshot.last_issue.message,
                    snapshot.correlation);
            }

            if (snapshot.is_terminal())
            {
                return TDiagnosticRecord::info(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.snapshot.terminal",
                    subject,
                    snapshot.display_name,
                    snapshot.correlation);
            }

            return TDiagnosticRecord::info(
                id,
                TDiagnosticCategory::bridge_core,
                "bridge.snapshot.valid",
                subject,
                snapshot.display_name,
                snapshot.correlation);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord from_trace(
            TDiagnosticId id,
            const TBridgeCoreTrace& trace,
            std::string_view subject = "bridge_core_trace") noexcept
        {
            if (!trace.is_valid())
            {
                return TDiagnosticRecord::warning(
                    id,
                    TDiagnosticCategory::bridge_core,
                    "bridge.trace.invalid",
                    subject,
                    "bridge trace is invalid",
                    trace.correlation);
            }

            return TDiagnosticRecord::info(
                id,
                TDiagnosticCategory::bridge_core,
                "bridge.trace.valid",
                subject,
                trace.note,
                trace.correlation);
        }
    };
}
