# CME-W01 — Foundational Identity And State Types

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W01` |
| Wave Name | Foundational Identity And State Types |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish foundational IDs, indices, states, and diagnostic atoms before any behavior-bearing component |

## 2. What This Wave Implements

```text
ids/
  TContainerId
  TContainerRegistryIndex
  TSlotIndex
  TRoundId
  TReferenceId
  TBoundaryId

state/
  TSlotState
  TContainerState
  TRoundState
  TModeratorState
  TBundleAgentState
  TReferenceValidityState
  TReferenceSupplyState
  TSafePointState
  TDispatchExposureState

diagnostics/
  TDiagnosticSeverity
  TDiagnosticCategory
```

## 3. What This Wave Does Not Implement

```text
container storage
slot storage
registry behavior
waiting lists
round management
reference calculation
ingress placement
dispatch exposure
safe-point algorithms
eviction
bridge bindings
read-side profile
```

## 4. Architectural Rules Preserved

1. State is not behavior.
2. ID is not actor.
3. Registry index is not direct ownership.
4. Slot state, container state, and round state are distinct.
5. Diagnostics are classified but not collected or exported in this wave.
6. No bridge/read-side lifecycle is introduced.
