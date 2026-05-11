# CME-W08 — Reference Handles And Validity Model

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W08` |
| Wave Name | Reference Handles And Validity Model |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce ingress/dispatch/slot/round/next reference artifacts, validity policy surface, and stale diagnostics |

## 2. What This Wave Implements

```text
reference_precalculator/handles/
  TAccessRefId
  TAccessRefDirection
  TAccessRefKind
  TAccessRefScope
  TSlotAccessRef
  TIngressAccessRef
  TDispatchAccessRef
  TRoundScopedRef
  TNextRefToken

reference_precalculator/validity/
  TReferenceValidityDecisionKind
  TReferenceValidityPolicy
  TStaleReferenceReport
  TReferenceInvalidationReport
  TReferenceDirectionMismatchReport
```

## 3. What This Wave Does Not Implement

```text
ReferencePrecalculator algorithm
container/slot locating
ingress placement
dispatch exposure
bridge protocol
copy/move semantics
registry rebuild
safe-point execution
```

## 4. Architectural Rules Preserved

1. Reference is not raw pointer.
2. Reference validity is scope-bound.
3. Ingress refs are not dispatch refs.
4. Dispatch refs are not ingress refs.
5. Stale reference usage is diagnostic-visible.
6. References do not own bridge/read-side lifecycle.
