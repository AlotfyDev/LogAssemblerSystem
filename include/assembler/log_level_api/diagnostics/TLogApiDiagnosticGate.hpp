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

#include "TLogApiDiagnosticReport.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticGate final {
    [[nodiscard]] static bool AllowsProgress(const TLogApiDiagnosticReport& report) noexcept {
        return !report.HasBlockingDiagnostic();
    }
};

} // namespace assembler::log_level_api::diagnostics
