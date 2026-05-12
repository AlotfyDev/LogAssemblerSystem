#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
#include "assembler/communication_context/diagnostics/categories/TDiagnosticCategory.hpp"
#include "assembler/communication_context/diagnostics/ids/TDiagnosticId.hpp"
#include "assembler/communication_context/diagnostics/severity/TDiagnosticSeverity.hpp"

/**
 * @file TDiagnosticView.hpp
 * @brief Compact read-only diagnostic projection.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the optional diagnostics layer for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - read-only diagnostic projection for reports and future presentation
 *   layers;
 * - no diagnostic storage or mutation authority;
 * - stable display-safe fields only.
 *
 * @section ascc_current_wave Current W12 Implementation Scope
 * This W12 version intentionally implements only lightweight, header-only,
 * endpoint-neutral diagnostic values, reports, collectors, and builders over
 * already-existing W01-W11 public surfaces.
 *
 * - diagnostic id, category, severity, code, subject, and correlation;
 * - validity and failure helpers;
 * - projection from record.
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
    struct TDiagnosticView final
    {
        TDiagnosticId diagnostic_id{TDiagnosticId::invalid()};
        TDiagnosticCategory category{TDiagnosticCategory::unknown};
        TDiagnosticSeverity severity{TDiagnosticSeverity::none};
        std::string_view code{};
        std::string_view subject{};
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

        [[nodiscard]] static constexpr TDiagnosticView invalid() noexcept
        {
            return TDiagnosticView{};
        }

        [[nodiscard]] static constexpr TDiagnosticView from_record(
            const TDiagnosticRecord& record) noexcept
        {
            if (!record.is_valid())
            {
                return invalid();
            }

            return TDiagnosticView{
                record.diagnostic_id,
                record.category,
                record.severity,
                record.code,
                record.subject,
                record.correlation
            };
        }
    };
}
