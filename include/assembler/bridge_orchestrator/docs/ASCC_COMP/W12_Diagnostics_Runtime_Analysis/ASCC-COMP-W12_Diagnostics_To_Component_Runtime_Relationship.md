# ASCC-COMP-W12 — Diagnostics To Component Runtime Relationship

## 1. Diagnostics To Bridge Core

`TBridgeDiagnosticBuilder` already converts Bridge Core result/snapshot/trace values into `TDiagnosticRecord`.

A runtime layer must decide when those records are collected, routed, ignored, or exposed.

## 2. Diagnostics To Registries

Registry diagnostics can be built from registry snapshots and reports. The diagnostic runtime should treat registry diagnostics as one source category, not as a service locator.

## 3. Diagnostics To Runtime Subdomains

Runtime packages for participants, carriers, obligations, channels, compatibility, sessions, protocols, and bridge core produce reports and views.

Diagnostics runtime should collect derived diagnostic records without owning those subdomains.

## 4. Diagnostics To Facade

Pipeline Composer consumes diagnostic readiness/evidence through:

```text
TAsccDiagnosticCatalogView
TAsccDiagnosticReadinessView
TAsccDiagnosticAdmissionPolicy
TDiagnosticFacadeEvidenceAdapter
```

not by mutating collectors directly.

## 5. Export Boundary

`TDiagnosticExportBoundary` is a contract boundary, not a file/telemetry implementation.

It allows future export add-ons without turning core diagnostics into IO.
