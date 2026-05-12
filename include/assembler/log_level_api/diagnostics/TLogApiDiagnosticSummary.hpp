#pragma once

/*
    LOGAPI-W28 — Diagnostics And Failure Model

    Responsibility:
        Define Log Level API diagnostics, failure classification, diagnostic
        records, diagnostic reports, and boundary-local failure ownership across
        configuration, content, parser, metadata, timestamp, envelope, handoff,
        and public API surfaces.

    Boundary:
        This wave does not implement a logging backend, telemetry exporter,
        persistence, recovery engine, policy assignment, circulation engine,
        bridge orchestration, or final receiver behavior.

    Doctrine:
        Diagnostics explain Log Level API-owned states and failures.
        Diagnostics must not become telemetry, database audit, receiver retry,
        or policy governance.
*/

#include <cstddef>

#include "TLogApiDiagnosticSeverity.hpp"
#include "TLogApiDiagnosticReport.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticSummary final {
    std::size_t trace_count{0};
    std::size_t info_count{0};
    std::size_t warning_count{0};
    std::size_t error_count{0};
    std::size_t fatal_count{0};
    std::size_t blocking_count{0};

    [[nodiscard]] static TLogApiDiagnosticSummary From(const TLogApiDiagnosticReport& report) noexcept {
        TLogApiDiagnosticSummary summary{};

        for (const auto& record : report.records) {
            if (record.blocking) ++summary.blocking_count;

            switch (record.severity) {
                case TLogApiDiagnosticSeverity::Trace: ++summary.trace_count; break;
                case TLogApiDiagnosticSeverity::Info: ++summary.info_count; break;
                case TLogApiDiagnosticSeverity::Warning: ++summary.warning_count; break;
                case TLogApiDiagnosticSeverity::Error: ++summary.error_count; break;
                case TLogApiDiagnosticSeverity::Fatal: ++summary.fatal_count; break;
                default: break;
            }
        }

        return summary;
    }
};

} // namespace assembler::log_level_api::diagnostics
