# CME-W12 — Safe Point And Release/Recycle Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W12` |
| Wave Name | Safe Point And Release/Recycle Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce safe-point carriers, reset/recycle/reentry surfaces, release views and reports |

## 2. What This Wave Implements

```text
safe_points/
  TSafePointId
  TSafePointKind
  TSafePointView
  TSafePointPolicy
  TSafePointViolationReport

release_recycle/
  TReleaseRecycleId
  TReleaseKind
  TRecycleState

release_recycle/views/
  TReleaseRecycleView
  TReentryEligibilityView

release_recycle/reports/
  TReleaseRecycleReportId
  TRecycleReport
  TResetAppliedReport
  TExposureReleaseReport

release_recycle/policies/
  TRecyclePolicy
```

## 3. What This Wave Does Not Implement

```text
actual reset algorithm
actual recycle algorithm
reference invalidation execution
container mutation
registry rebuild
eviction execution
bridge acknowledgement
read-side retry
```

## 4. Architectural Rules Preserved

1. Reset/recycle requires a safe point.
2. Safe point view is read-only.
3. Safe point violation report is evidence, not recovery.
4. Release does not prove receiver delivery.
5. Reentry eligibility does not add container to waiting list.
6. Reset report does not execute reset.
