# ASCC-COMP-W13 — Integration Boundary Runtime Analysis

## 1. Purpose

This package corrects and extends the architectural interpretation of:

```text
include/assembler/bridge_orchestrator/integration_boundaries/
```

The current layer already contains future-facing boundary contracts and CRTP boundary call-through surfaces:

```text
TIntegrationBoundaryAbstractPorts
TIntegrationBoundaryPort
TBoundaryHandoffRequest
TBoundaryHandoffResult
TBoundaryHandoffHandle
TIntegrationBoundaryDescriptor
TIntegrationBoundaryPolicy
TIntegrationBoundaryReport
```

These are not useless descriptors. They define the abstract boundary contract for future integration with persistence, telemetry, ABI, read-side, or external receiver-facing surfaces.

However, they are not the full integration boundary runtime.

## 2. Correct Classification

```text
integration_boundaries/
    existing = abstract boundary contracts + CRTP boundary call-through + handoff carriers
    missing = integration boundary runtime + handoff lifecycle + evidence + facade projection
```

## 3. Required Runtime Layer

The runtime layer above current contracts must include:

```text
TIntegrationBoundaryRuntimeContext
TIntegrationBoundaryAdmissionPolicy
TBoundaryHandoffRuntime
TBoundaryHandoffLifecycleController
TBoundaryHandoffRuntimeReport
TBoundaryHandoffLedger
TIntegrationBoundaryRetryPolicy
TIntegrationBoundaryMaterialClassifier
TIntegrationBoundaryRuntimeView
TIntegrationBoundaryExportContract
```

## 4. Required Facade Layer

The facade layer must expose integration boundary support without leaking boundary internals:

```text
TAsccIntegrationBoundaryCatalogView
TAsccIntegrationBoundaryReadinessView
TAsccIntegrationBoundaryAdmissionPolicy
TIntegrationBoundaryFacadeEvidenceAdapter
```

## 5. Runtime Rule

```text
CRTP boundary call-through is not full boundary runtime.

A production boundary runtime must:
    evaluate admission,
    check boundary readiness,
    accept handoff,
    complete/reject/defer handoff,
    record handoff lifecycle,
    produce runtime reports,
    and expose facade-safe evidence.
```

## 6. Closure

`integration_boundaries/` should evolve from future-facing abstract contracts into:

```text
abstract boundary contracts
+ boundary handoff runtime
+ handoff lifecycle/evidence
+ optional export contract
+ facade-safe catalog/readiness/admission/evidence
```
