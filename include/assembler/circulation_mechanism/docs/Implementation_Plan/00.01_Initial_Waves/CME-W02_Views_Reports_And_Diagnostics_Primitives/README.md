# CME-W02 — Views Reports And Diagnostics Primitives

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W02` |
| Wave Name | Views Reports And Diagnostics Primitives |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce foundational read-only view, report, and diagnostic carriers after W01 identity/state atoms |

## 2. What This Wave Implements

```text
views/
  TViewId
  TViewScope
  TViewStability
  TViewVisibility
  TReadOnlyViewDescriptor

reports/
  TReportId
  TReportKind
  TReportStatus
  TReportDescriptor
  TOperationalReport

diagnostics/
  TDiagnosticIssueId
  TDiagnosticIssueKind
  TDiagnosticIssue
  TInvariantViolationReport
  TDiagnosticCollector
```

## 3. What This Wave Does Not Implement

```text
component-specific views
component-specific reports
diagnostic storage
logging
telemetry export
recovery behavior
container storage
reference calculation
ingress placement
dispatch exposure
```

## 4. Architectural Rules Preserved

1. A view is read-only.
2. A report is evidence, not authority expansion.
3. A diagnostic issue does not execute recovery.
4. Reports do not prove downstream success.
5. The diagnostic collector is only a reserved surface in this wave.
