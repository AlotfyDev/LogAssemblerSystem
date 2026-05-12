#pragma once

#include <string_view>

/**
 * @file TDiagnosticSeverity.hpp
 * @brief Diagnostic severity taxonomy for optional ASCC diagnostics.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - small stable severity vocabulary;
 * - ordering helpers for bounded report aggregation;
 * - string conversion for local diagnostic reports.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - enum class `TDiagnosticSeverity`;
 * - severity comparison helpers;
 * - textual conversion.
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
    enum class TDiagnosticSeverity
    {
        none,
        trace,
        info,
        warning,
        error,
        critical
    };

    [[nodiscard]] constexpr bool is_failure_diagnostic_severity(
        TDiagnosticSeverity severity) noexcept
    {
        return severity == TDiagnosticSeverity::error
            || severity == TDiagnosticSeverity::critical;
    }

    [[nodiscard]] constexpr bool is_actionable_diagnostic_severity(
        TDiagnosticSeverity severity) noexcept
    {
        return severity == TDiagnosticSeverity::warning
            || severity == TDiagnosticSeverity::error
            || severity == TDiagnosticSeverity::critical;
    }

    [[nodiscard]] constexpr int severity_rank(TDiagnosticSeverity severity) noexcept
    {
        switch (severity)
        {
            case TDiagnosticSeverity::none: return 0;
            case TDiagnosticSeverity::trace: return 1;
            case TDiagnosticSeverity::info: return 2;
            case TDiagnosticSeverity::warning: return 3;
            case TDiagnosticSeverity::error: return 4;
            case TDiagnosticSeverity::critical: return 5;
        }

        return 0;
    }

    [[nodiscard]] constexpr bool severity_at_least(
        TDiagnosticSeverity actual,
        TDiagnosticSeverity threshold) noexcept
    {
        return severity_rank(actual) >= severity_rank(threshold);
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TDiagnosticSeverity severity) noexcept
    {
        switch (severity)
        {
            case TDiagnosticSeverity::none: return "none";
            case TDiagnosticSeverity::trace: return "trace";
            case TDiagnosticSeverity::info: return "info";
            case TDiagnosticSeverity::warning: return "warning";
            case TDiagnosticSeverity::error: return "error";
            case TDiagnosticSeverity::critical: return "critical";
        }

        return "none";
    }
}
