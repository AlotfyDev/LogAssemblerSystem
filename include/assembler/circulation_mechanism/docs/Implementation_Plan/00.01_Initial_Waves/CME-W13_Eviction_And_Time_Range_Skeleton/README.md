# CME-W13 — Eviction And Time Range Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W13` |
| Wave Name | Eviction And Time Range Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce container time range metadata, eviction candidate carriers, eviction policy profiles, and eviction/delegation reports |

## 2. What This Wave Implements

```text
eviction/
  TEvictionCandidateId
  TEvictionPolicyKind
  TEvictionCandidateStatus
  TTimeRangeCompletenessStatus
  TContainerTimeRange
  TEvictionCandidate

eviction/views/
  TContainerTimeRangeView
  TEvictionCandidateView

eviction/policies/
  TEvictionPolicyProfileId
  TEvictionPolicyProfile
  TOldestTimeRangeEviction
  TFifoContainerEviction
  TNoEvictionPreBridgeProfile
  TDelegateToReadSideProfile
  TEmergencyEvictionProfile

eviction/reports/
  TEvictionReportId
  TEvictionReportKind
  TEvictionSelectionReport
  TEvictionAppliedReport
  TEvictionRejectedReport
  TCapacityDelegatedToReadSideReport
```

## 3. What This Wave Does Not Implement

```text
actual eviction execution
registry mutation
waiting-list rebuild
reference invalidation execution
read-side retry
bridge recovery
persistence deletion
```

## 4. Architectural Rules Preserved

1. Time range is ordering/diagnostic metadata, not timestamp semantic ownership.
2. Eviction is exceptional and safe-point-gated.
3. NoEvictionPreBridgeProfile is represented as a first-class profile.
4. DelegateToReadSideProfile preserves receiver-delay separation.
5. Candidate/report objects do not perform eviction.
