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

#include "TLogApiDiagnosticCategory.hpp"
#include "TLogApiDiagnosticCode.hpp"
#include "TLogApiDiagnosticCollector.hpp"
#include "TLogApiDiagnosticFactory.hpp"
#include "TLogApiDiagnosticGate.hpp"
#include "TLogApiDiagnosticId.hpp"
#include "TLogApiDiagnosticRecord.hpp"
#include "TLogApiDiagnosticRecordView.hpp"
#include "TLogApiDiagnosticReport.hpp"
#include "TLogApiDiagnosticReportView.hpp"
#include "TLogApiDiagnosticSeverity.hpp"
#include "TLogApiDiagnosticSourceRef.hpp"
#include "TLogApiDiagnosticSummary.hpp"
#include "TLogApiFailureBoundaryKind.hpp"
#include "TLogApiFailureClassifier.hpp"
#include "TLogApiFailureKind.hpp"
