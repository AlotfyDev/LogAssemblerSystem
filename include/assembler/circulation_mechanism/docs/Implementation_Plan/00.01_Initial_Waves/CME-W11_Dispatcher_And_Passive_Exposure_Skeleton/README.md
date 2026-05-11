# CME-W11 — Dispatcher And Passive Exposure Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W11` |
| Wave Name | Dispatcher And Passive Exposure Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce Dispatcher skeleton, passive pull dispatch profile, optional push profile descriptor, dispatch exposure views, and boundary reports |

## 2. What This Wave Implements

```text
dispatcher/
  TDispatcher
  TDispatcherId
  TDispatcherStatus
  TDispatchExposureStatus

dispatcher/profiles/
  TDispatchProfileKind
  TPassivePullDispatchProfile
  TPushDispatchProfile

dispatcher/boundary/
  TDispatchBoundaryId
  TDispatchBoundaryStatus
  TDispatchBoundaryDescriptor

dispatcher/views/
  TDispatchExposureView
  TDispatchReadyView
  TDispatcherView
  TDispatchBoundaryView

dispatcher/reports/
  TDispatchReportId
  TDispatchExposureReport
  TPassiveExposureReport
  TBoundaryAssumptionBrokenReport
  TPushDispatchAttemptReport
```

## 3. What This Wave Does Not Implement

```text
bridge protocol
receiver lifecycle
actual payload copy/move
push dispatch execution
reference calculation
container scan
dispatch release/recycle
persistence
read-side retry
```

## 4. Architectural Rules Preserved

1. Dispatcher exposes; bridge consumes.
2. Passive pull is the default profile.
3. Push is optional and disabled unless profile enables it.
4. Copy/move semantics are outside CME.
5. Dispatch exposure report is not final delivery proof.
6. Boundary assumption broken report is diagnostic, not retry behavior.
