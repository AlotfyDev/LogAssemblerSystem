# CME-W09 — ReferencePrecalculator Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W09` |
| Wave Name | ReferencePrecalculator Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce ReferencePrecalculator identity, next-ref supply policy, supply views, and reference preparation/interruption/candidate-rejection reports |

## 2. What This Wave Implements

```text
reference_precalculator/
  TReferencePrecalculatorId
  TReferencePrecalculationStatus
  TReferencePrecalculator

reference_precalculator/policies/
  TReferenceSupplyPolicy

reference_precalculator/views/
  TReferenceSupplyView
  TIngressReferenceSupplyView
  TDispatchReferenceSupplyView

reference_precalculator/reports/
  TReferenceReportId
  TReferenceCandidateRejectionKind
  TReferencePrecalculationReport
  TReferenceSupplyInterruptionReport
  TReferenceCandidateRejectionReport
```

## 3. What This Wave Does Not Implement

```text
actual locating algorithm
actual reference pool
waiting-list consumption
container registry resolution
slot selection
TIngressAccessRef production
TDispatchAccessRef production
ingress placement
dispatch exposure
bridge protocol
copy/move semantics
```

## 4. Architectural Rules Preserved

1. ReferencePrecalculator owns locating/reference calculation surface.
2. Ingress/Dispatcher own access execution, not this wave.
3. Supply view is read-only.
4. Supply interruption is diagnostic-visible.
5. Candidate rejection does not mutate waiting lists or containers.
6. No envelope content inspection is introduced.
