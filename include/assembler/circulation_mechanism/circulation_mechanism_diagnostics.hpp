#pragma once

/*
    circulation_mechanism_diagnostics.hpp

    Delivery:
        CME-DIAGNOSTICS-PROD-W01 — Production Issue And Invariant Contract

    Responsibility:
        Aggregate include for production-grade CME Diagnostics contract.
*/

#include "diagnostics/TDiagnosticIssueId.hpp"
#include "diagnostics/TDiagnosticSeverity.hpp"
#include "diagnostics/TDiagnosticCategory.hpp"
#include "diagnostics/TDiagnosticIssueKind.hpp"
#include "diagnostics/TDiagnosticResolutionHint.hpp"
#include "diagnostics/TDiagnosticClassifiers.hpp"
#include "diagnostics/TDiagnosticIssue.hpp"
#include "diagnostics/TDiagnosticValidationResult.hpp"
#include "diagnostics/TInvariantViolationReport.hpp"
#include "diagnostics/TDiagnosticCollector.hpp"
