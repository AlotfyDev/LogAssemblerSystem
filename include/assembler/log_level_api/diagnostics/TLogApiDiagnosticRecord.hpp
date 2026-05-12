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

#include "TLogApiDiagnosticCategory.hpp"
#include "TLogApiDiagnosticCode.hpp"
#include "TLogApiDiagnosticId.hpp"
#include "TLogApiDiagnosticSeverity.hpp"
#include "TLogApiDiagnosticSourceRef.hpp"
#include "TLogApiFailureBoundaryKind.hpp"
#include "TLogApiFailureKind.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticRecord final {
    TLogApiDiagnosticId id{};
    TLogApiDiagnosticSeverity severity{TLogApiDiagnosticSeverity::Unknown};
    TLogApiDiagnosticCategory category{TLogApiDiagnosticCategory::Unknown};
    TLogApiFailureKind failure_kind{TLogApiFailureKind::Unknown};
    TLogApiFailureBoundaryKind boundary{TLogApiFailureBoundaryKind::Unknown};
    TLogApiDiagnosticCode code{};
    TLogApiDiagnosticSourceRef source{};
    std::string message{};
    bool blocking{false};

    [[nodiscard]] bool IsPresent() const noexcept {
        return id.IsValid()
            && severity != TLogApiDiagnosticSeverity::Unknown
            && category != TLogApiDiagnosticCategory::Unknown
            && failure_kind != TLogApiFailureKind::Unknown
            && boundary != TLogApiFailureBoundaryKind::Unknown
            && code.IsPresent()
            && source.IsPresent()
            && !message.empty();
    }
};

} // namespace assembler::log_level_api::diagnostics
