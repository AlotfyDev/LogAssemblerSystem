#pragma once

#include "assembler/communication_context/diagnostics/records/TDiagnosticRecord.hpp"

/**
 * @file TDiagnosticPolicy.hpp
 * @brief Diagnostic classification and filtering policy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - small diagnostic filtering and classification helpers;
 * - future extension point for local report policies without becoming a
 *   logging framework or telemetry exporter;
 * - no runtime side effects.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - severity threshold;
 * - record inclusion helper;
 * - failure classification helper.
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
    struct TDiagnosticPolicy final
    {
        TDiagnosticSeverity minimum_severity{TDiagnosticSeverity::trace};
        bool include_invalid_records{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return minimum_severity != TDiagnosticSeverity::none;
        }

        [[nodiscard]] constexpr bool includes(
            const TDiagnosticRecord& record) const noexcept
        {
            if (!record.is_valid())
            {
                return include_invalid_records;
            }

            return severity_at_least(record.severity, minimum_severity);
        }

        [[nodiscard]] static constexpr TDiagnosticPolicy all() noexcept
        {
            return TDiagnosticPolicy{TDiagnosticSeverity::trace, false};
        }

        [[nodiscard]] static constexpr TDiagnosticPolicy warnings_and_above() noexcept
        {
            return TDiagnosticPolicy{TDiagnosticSeverity::warning, false};
        }

        [[nodiscard]] static constexpr TDiagnosticPolicy errors_only() noexcept
        {
            return TDiagnosticPolicy{TDiagnosticSeverity::error, false};
        }
    };
}
