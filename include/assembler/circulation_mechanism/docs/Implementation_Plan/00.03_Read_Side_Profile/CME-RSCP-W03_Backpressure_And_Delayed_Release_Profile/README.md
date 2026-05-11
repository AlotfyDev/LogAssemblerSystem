# CME-RSCP-W03 — Backpressure And Delayed Release Profile

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-RSCP-W03` |
| Component | `ReadSide_Circulation_Profile` |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish post-bridge capacity, read-side backpressure profile, delayed-release profile, and related views/reports |

## 2. What This Wave Implements

```text
post_bridge_capacity/
  TPostBridgeCapacityProfileId
  TPostBridgeCapacityStatus
  TPostBridgeCapacityProfile

backpressure/
  TReadSideBackpressureProfileId
  TReadSideBackpressureMode
  TReadSideBackpressureState
  TReadSideBackpressureProfile

delayed_release/
  TDelayedReleaseProfileId
  TDelayedReleaseRecordId
  TDelayedReleaseTriggerKind
  TDelayedReleaseState
  TDelayedReleaseProfile
  TDelayedReleaseRecord

views/
  TReadSideBackpressureView
  TDelayedReleaseView
  TPostBridgeCapacityView

reports/
  TReadSideCapacityReportId
  TReadSideCapacityIssueKind
  TReadSideCapacityReport
```

## 3. What This Wave Does Not Implement

```text
backpressure algorithm
delayed release algorithm
receiver acknowledgement execution
retry execution
persistence adapter
bridge protocol
post-bridge container registry
```

## 4. Architectural Rules Preserved

1. Backpressure is read-side/post-bridge, not pre-bridge broker behavior.
2. Delayed release is profile/state evidence, not release execution.
3. Post-bridge capacity is a profile descriptor, not allocation.
4. Persistence completion is a possible trigger, not owned here.
