# ASCC-COMP-W12 — Diagnostics Runtime Analysis

## 1. Purpose

This package corrects and extends the architectural interpretation of:

```text
include/assembler/bridge_orchestrator/diagnostics/
```

The current diagnostics layer already contains useful local mechanics:

```text
TDiagnosticRecord
TDiagnosticReport
TDiagnosticCollector
TDiagnosticSnapshot
TDiagnosticView
TDiagnosticPolicy
TBridgeDiagnosticBuilder
TRegistryDiagnosticBuilder
```

These are not merely descriptors. They can build, append, filter, snapshot, and summarize bounded diagnostic records.

However, the current implementation is still not a full ASCC diagnostic runtime subsystem.

## 2. Correct Classification

```text
diagnostics/
    existing = optional bounded diagnostic values/reports/collector/builders
    missing = component-level diagnostic runtime/source routing/readiness/export facade
```

## 3. Required Runtime Layer

The runtime layer above the current collector must include:

```text
TDiagnosticRuntimeContext
TDiagnosticRuntime
TDiagnosticSourceKind
TDiagnosticSourceRegistry
TDiagnosticRoutingPolicy
TDiagnosticRuntimeReport
TDiagnosticReadinessView
TDiagnosticBuilderRegistry
TDiagnosticComponentReportAssembler
TDiagnosticExportBoundary
TDiagnosticExportReport
```

## 4. Required Facade Layer

The facade layer must expose diagnostic capability/readiness without leaking collector internals:

```text
TAsccDiagnosticCatalogView
TAsccDiagnosticReadinessView
TAsccDiagnosticAdmissionPolicy
TDiagnosticFacadeEvidenceAdapter
```

## 5. Runtime Rule

```text
A bounded collector is not the full diagnostic runtime.

A production diagnostic runtime must:
    know which sources are enabled,
    route records through policy,
    own collector lifecycle,
    produce runtime readiness,
    assemble component-level reports,
    and expose export boundary contracts without implementing IO.
```

## 6. Closure

Diagnostics is an optional ASCC subsystem, but if enabled for production it must be represented as a component-level runtime with facade-safe evidence.
