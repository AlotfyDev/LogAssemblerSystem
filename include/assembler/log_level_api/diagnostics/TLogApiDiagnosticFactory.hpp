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
#include "TLogApiFailureClassifier.hpp"

namespace assembler::log_level_api::diagnostics {

class TLogApiDiagnosticFactory final {
public:
    [[nodiscard]] static TLogApiDiagnosticRecord Make(
        std::uint64_t id,
        TLogApiDiagnosticSeverity severity,
        TLogApiFailureKind failure_kind,
        const char* component,
        const char* code,
        const char* message,
        bool blocking
    ) {
        const auto classification = TLogApiFailureClassifier::Classify(failure_kind);

        TLogApiDiagnosticRecord record{};
        record.id = TLogApiDiagnosticId{id};
        record.severity = severity;
        record.category = classification.category;
        record.failure_kind = failure_kind;
        record.boundary = classification.boundary;
        record.code.value = code;
        record.source.component = component;
        record.source.wave = "LOGAPI-W28";
        record.source.local_ref = code;
        record.message = message;
        record.blocking = blocking;
        return record;
    }
};

} // namespace assembler::log_level_api::diagnostics
