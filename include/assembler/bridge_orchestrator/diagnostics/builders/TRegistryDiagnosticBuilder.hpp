#pragma once

#include "assembler/communication_context/registries/optional_registries/snapshots/TRegistrySnapshot.hpp"
#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"

/**
 * @file TRegistryDiagnosticBuilder.hpp
 * @brief Diagnostic builders for optional registry snapshots.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - endpoint-neutral builders that translate optional registry snapshots
 *   into diagnostic records;
 * - no mutation of registries;
 * - no registry-backed service locator behavior.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - diagnostic record from `TRegistrySnapshot`;
 * - invalid/full/rejected-count classification.
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
    struct TRegistryDiagnosticBuilder final
    {
        [[nodiscard]] static constexpr TDiagnosticRecord from_snapshot(
            TDiagnosticId id,
            const TRegistrySnapshot& snapshot,
            std::string_view subject = "registry_snapshot") noexcept
        {
            if (!snapshot.is_valid())
            {
                return TDiagnosticRecord::error(
                    id,
                    TDiagnosticCategory::registry,
                    "registry.snapshot.invalid",
                    subject,
                    "registry snapshot is invalid",
                    snapshot.correlation);
            }

            if (snapshot.rejected_insertions > 0u)
            {
                return TDiagnosticRecord::warning(
                    id,
                    TDiagnosticCategory::registry,
                    "registry.snapshot.rejected_insertions",
                    subject,
                    snapshot.registry_name,
                    snapshot.correlation);
            }

            if (snapshot.full())
            {
                return TDiagnosticRecord::warning(
                    id,
                    TDiagnosticCategory::registry,
                    "registry.snapshot.full",
                    subject,
                    snapshot.registry_name,
                    snapshot.correlation);
            }

            if (snapshot.empty())
            {
                return TDiagnosticRecord::info(
                    id,
                    TDiagnosticCategory::registry,
                    "registry.snapshot.empty",
                    subject,
                    snapshot.registry_name,
                    snapshot.correlation);
            }

            return TDiagnosticRecord::info(
                id,
                TDiagnosticCategory::registry,
                "registry.snapshot.valid",
                subject,
                snapshot.registry_name,
                snapshot.correlation);
        }
    };
}
