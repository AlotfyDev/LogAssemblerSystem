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

#include <string>

#include "TLogApiDiagnosticRecord.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticRecordView final {
    std::string id{};
    std::string code{};
    std::string component{};
    std::string message{};
    bool blocking{false};

    [[nodiscard]] static TLogApiDiagnosticRecordView From(const TLogApiDiagnosticRecord& record) {
        TLogApiDiagnosticRecordView view{};
        view.id = record.id.ToString();
        view.code = record.code.value;
        view.component = record.source.component;
        view.message = record.message;
        view.blocking = record.blocking;
        return view;
    }
};

} // namespace assembler::log_level_api::diagnostics
