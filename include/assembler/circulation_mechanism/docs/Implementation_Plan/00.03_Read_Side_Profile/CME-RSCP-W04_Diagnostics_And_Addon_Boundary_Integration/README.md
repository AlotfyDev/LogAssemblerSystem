# CME-RSCP-W04 — Diagnostics And Addon Boundary Integration

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-RSCP-W04` |
| Component | `ReadSide_Circulation_Profile` |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish read-side diagnostic records, addon boundary descriptors, views, and integration reports |

## 2. What This Wave Implements

```text
diagnostics/
  TReadSideDiagnosticId
  TReadSideDiagnosticKind
  TReadSideDiagnosticSeverity
  TReadSideDiagnosticRecord

addon_boundary/
  TAddonBoundaryId
  TAddonBoundaryKind
  TAddonBoundaryStatus
  TAddonBoundaryDescriptor

views/
  TReadSideDiagnosticView
  TAddonBoundaryView

reports/
  TReadSideIntegrationReportId
  TReadSideIntegrationIssueKind
  TReadSideIntegrationReport
```

## 3. What This Wave Does Not Implement

```text
addon runtime behavior
database persistence
telemetry export
file sink behavior
diagnostic sink execution
bridge runtime
receiver implementation
failed-dispatch recovery
```

## 4. Architectural Rules Preserved

1. Diagnostics describe conditions; they do not execute recovery.
2. Addon boundary descriptor is not addon implementation.
3. Integration report is evidence, not runtime invocation.
4. Persistence/telemetry/file sinks remain external/addon concerns.
5. Read-side profile remains separate from pre-bridge profile.
