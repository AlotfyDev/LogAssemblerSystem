# CME-W04 — Slot And Container Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W04` |
| Wave Name | Slot And Container Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce foundational `TSlot`, `TContainer`, occupancy, layout views, time range metadata, and transition reports |

## 2. What This Wave Implements

```text
slot/
  TSlot
  TSlotView
  TSlotOccupancyView
  TSlotTransitionReport

container/
  TContainer
  TContainerView
  TContainerStateView
  TContainerSlotLayoutView
  TContainerTimeRange
  TContainerTimeRangeView
  TContainerStateTransitionReport
```

## 3. What This Wave Does Not Implement

```text
container registry
slot storage array
actual envelope payload storage
ingress placement algorithm
dispatch exposure
reference calculation
container reset
safe-point algorithms
eviction execution
bridge bindings
```

## 4. Architectural Rules Preserved

1. Slot is a placement/access structure, not an envelope.
2. Slot occupancy is not envelope lifecycle ownership.
3. Container state is independent from slot state.
4. Container is not a message broker.
5. Time range is ordering/diagnostic metadata, not timestamp semantic ownership.
6. Container skeleton does not expose bridge or read-side semantics.
