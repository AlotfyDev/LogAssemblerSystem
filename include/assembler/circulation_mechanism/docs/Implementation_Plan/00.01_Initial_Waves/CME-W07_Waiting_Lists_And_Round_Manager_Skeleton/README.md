# CME-W07 — Waiting Lists And Round Manager Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W07` |
| Wave Name | Waiting Lists And Round Manager Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce ingress/dispatch waiting-list skeletons and RoundManager admission-decision surface |

## 2. What This Wave Implements

```text
waiting_list/
  TWaitingListState
  TWaitingListEntry
  TIngressWaitingList
  TDispatchWaitingList
  TIngressWaitingListView
  TDispatchWaitingListView
  TIngressWaitingListRegistrationReport
  TDispatchWaitingListRegistrationReport

round_manager/
  TRoundKind
  TRoundAdmissionDecisionKind
  TRoundView
  TRoundAdmissionReport
  TRoundClosureReport
  TRoundManager
```

## 3. What This Wave Does Not Implement

```text
reference calculation
ingress placement
dispatch exposure
container reset
registry rebuild
bridge handoff
envelope storage in waiting lists
dynamic scheduling
```

## 4. Architectural Rules Preserved

1. Waiting lists store `TContainerRegistryIndex` through `TWaitingListEntry`.
2. Waiting lists do not store envelopes.
3. RoundManager owns admission decision classification.
4. RoundManager does not compute access references.
5. RoundManager does not execute ingress or dispatch.
6. Dispatch waiting list is not a bridge or receiver queue.
