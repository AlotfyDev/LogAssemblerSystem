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

namespace assembler::log_level_api::diagnostics {

/*
    Source reference for a diagnostic.

    This is descriptive only and does not expose internal object ownership.
*/
struct TLogApiDiagnosticSourceRef final {
    std::string domain{"log_level_api"};
    std::string component{};
    std::string wave{};
    std::string local_ref{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return !domain.empty() && !component.empty();
    }
};

} // namespace assembler::log_level_api::diagnostics
