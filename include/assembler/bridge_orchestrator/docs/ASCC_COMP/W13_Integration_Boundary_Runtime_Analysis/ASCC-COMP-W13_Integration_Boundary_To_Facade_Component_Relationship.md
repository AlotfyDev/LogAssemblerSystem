# ASCC-COMP-W13 — Integration Boundary To Facade And Component Relationship

## 1. Boundary To ASCC Component

Integration boundaries represent optional component-facing boundaries for moving material out of or into ASCC-facing integration surfaces.

They are not the Pipeline Composer itself.

## 2. Boundary To Handoff Runtime

Current boundary carriers define request/result/handle contracts.

Runtime must sequence:

```text
readiness
accept
complete
reject
defer
fail
```

## 3. Boundary To Diagnostics

Boundary runtime should produce reports that can be converted to diagnostic records.

It should not implement file IO, network IO, database persistence, telemetry export, or logging sinks.

## 4. Boundary To Facade

Pipeline Composer consumes facade surfaces:

```text
TAsccIntegrationBoundaryCatalogView
TAsccIntegrationBoundaryReadinessView
TAsccIntegrationBoundaryAdmissionPolicy
TIntegrationBoundaryFacadeEvidenceAdapter
```

It must not call concrete boundary ports directly.

## 5. Boundary To Export

`TIntegrationBoundaryExportContract` is a contract that allows future export add-ons. It is not an exporter implementation.
