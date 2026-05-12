#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/diagnostics/categories/TDiagnosticCategory.hpp"
#include "assembler/communication_context/diagnostics/ids/TDiagnosticId.hpp"
#include "assembler/communication_context/diagnostics/severity/TDiagnosticSeverity.hpp"

/**
 * @file TDiagnosticRecord.hpp
 * @brief Atomic endpoint-neutral diagnostic record.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - single diagnostic observation with stable ID, category, severity,
 *   code, subject, message, and correlation token;
 * - no ownership over the diagnosed object;
 * - future suitability for reports, validation matrices, or telemetry export
 *   adapters without implementing those adapters here.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - value-only diagnostic record;
 * - validity, failure, and actionable helpers;
 * - factory helpers for info/warning/error/critical records.
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
    struct TDiagnosticRecord final
    {
        TDiagnosticId diagnostic_id{TDiagnosticId::invalid()};
        TDiagnosticCategory category{TDiagnosticCategory::unknown};
        TDiagnosticSeverity severity{TDiagnosticSeverity::none};
        std::string_view code{};
        std::string_view subject{};
        std::string_view message{};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return diagnostic_id.is_valid()
                && category != TDiagnosticCategory::unknown
                && severity != TDiagnosticSeverity::none
                && !code.empty();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_failure_diagnostic_severity(severity);
        }

        [[nodiscard]] constexpr bool actionable() const noexcept
        {
            return is_actionable_diagnostic_severity(severity);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord make(
            TDiagnosticId id,
            TDiagnosticCategory diagnostic_category,
            TDiagnosticSeverity diagnostic_severity,
            std::string_view diagnostic_code,
            std::string_view diagnostic_subject = {},
            std::string_view diagnostic_message = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TDiagnosticRecord{
                id,
                diagnostic_category,
                diagnostic_severity,
                diagnostic_code,
                diagnostic_subject,
                diagnostic_message,
                token
            };
        }

        [[nodiscard]] static constexpr TDiagnosticRecord info(
            TDiagnosticId id,
            TDiagnosticCategory diagnostic_category,
            std::string_view diagnostic_code,
            std::string_view diagnostic_subject = {},
            std::string_view diagnostic_message = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                id,
                diagnostic_category,
                TDiagnosticSeverity::info,
                diagnostic_code,
                diagnostic_subject,
                diagnostic_message,
                token);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord warning(
            TDiagnosticId id,
            TDiagnosticCategory diagnostic_category,
            std::string_view diagnostic_code,
            std::string_view diagnostic_subject = {},
            std::string_view diagnostic_message = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                id,
                diagnostic_category,
                TDiagnosticSeverity::warning,
                diagnostic_code,
                diagnostic_subject,
                diagnostic_message,
                token);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord error(
            TDiagnosticId id,
            TDiagnosticCategory diagnostic_category,
            std::string_view diagnostic_code,
            std::string_view diagnostic_subject = {},
            std::string_view diagnostic_message = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                id,
                diagnostic_category,
                TDiagnosticSeverity::error,
                diagnostic_code,
                diagnostic_subject,
                diagnostic_message,
                token);
        }

        [[nodiscard]] static constexpr TDiagnosticRecord critical(
            TDiagnosticId id,
            TDiagnosticCategory diagnostic_category,
            std::string_view diagnostic_code,
            std::string_view diagnostic_subject = {},
            std::string_view diagnostic_message = {},
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return make(
                id,
                diagnostic_category,
                TDiagnosticSeverity::critical,
                diagnostic_code,
                diagnostic_subject,
                diagnostic_message,
                token);
        }
    };
}
