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

/*
    Minimal in-memory collector.

    This is not a logging backend and not telemetry.
*/
class TLogApiDiagnosticCollector final {
public:
    void Add(const TLogApiDiagnosticRecord& record) {
        if (record.IsPresent()) {
            report_.records.push_back(record);
        }
    }

    [[nodiscard]] const TLogApiDiagnosticReport& Report() const noexcept {
        return report_;
    }

private:
    TLogApiDiagnosticReport report_{};
};

} // namespace assembler::log_level_api::diagnostics
