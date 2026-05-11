#pragma once

/*
    circulation_mechanism_w02.hpp

    Convenience include for CME-W02 views/reports/diagnostics primitives.
    This header does not create a facade or runtime component.
*/

#include "views/TViewId.hpp"
#include "views/TViewScope.hpp"
#include "views/TViewStability.hpp"
#include "views/TViewVisibility.hpp"
#include "views/TReadOnlyViewDescriptor.hpp"

#include "reports/TReportId.hpp"
#include "reports/TReportKind.hpp"
#include "reports/TReportStatus.hpp"
#include "reports/TReportDescriptor.hpp"
#include "reports/TOperationalReport.hpp"

#include "diagnostics/TDiagnosticIssueId.hpp"
#include "diagnostics/TDiagnosticSeverity.hpp"
#include "diagnostics/TDiagnosticIssueKind.hpp"
#include "diagnostics/TDiagnosticIssue.hpp"
#include "diagnostics/TInvariantViolationReport.hpp"
#include "diagnostics/TDiagnosticCollector.hpp"
