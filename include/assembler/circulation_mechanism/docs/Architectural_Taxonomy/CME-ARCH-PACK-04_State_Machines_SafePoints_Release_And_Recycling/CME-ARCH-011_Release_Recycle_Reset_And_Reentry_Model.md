# CME-ARCH-011 — Release Recycle Reset And Reentry Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-011-DOC-001 | Document Title | Release Recycle Reset And Reentry Model |
| CME-ARCH-011-DOC-002 | Package | CME-ARCH-PACK-04 |
| CME-ARCH-011-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-011-DOC-004 | Scope Level | Release, recycle, reset, reentry, default empty container, dispatch completion |
| CME-ARCH-011-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-011-DOC-006 | Implementation Direction | C++17, header-only-first, state-driven recycling |
| CME-ARCH-011-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-010 |
| CME-ARCH-011-DOC-008 | Related Models | Slot state, container state, dispatch exposure, safe points, moderator reset, default empty container |
| CME-ARCH-011-DOC-009 | Primary Rule | Release/recycle/reset/reentry are state transitions, not informal cleanup |
| CME-ARCH-011-DOC-010 | Excluded | Bridge success proof, receiver acknowledgement, downstream persistence, read-side retry lifecycle |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines how slots and containers become reusable after dispatch-side exposure.

It answers:

```text
How does the engine transition from occupied/exposed payload residency back to
a default empty container ready for ingress without manual intervention?
```

### 2.2 Core Thesis

```text
Recycle is not deletion.
Recycle is controlled reentry into the ingress-ready circulation path.
```

---

## 3. Release Levels

| Level | Meaning |
|---|---|
| Slot release | Slot no longer hosts active envelope residency |
| Container release | Container completed its dispatch-side cycle |
| Reference release | Ref consumed, expired, or invalidated |
| Exposure release | Dispatch exposure closed |
| Round release | Round membership closed/completed |
| Registry release | Index safe for reuse/reentry |

---

## 4. Slot Release Model

### 4.1 Candidate Flow

```text
dispatch_exposed
→ released
→ recyclable
→ empty
```

### 4.2 Release Trigger Candidates

1. dispatch exposure consumed,
2. dispatch exposure closed,
3. dispatch round completed,
4. container reset safe point,
5. eviction safe point.

### 4.3 Slot Release Non-Meaning

Slot release does not prove:

1. bridge delivered payload,
2. receiver accepted payload,
3. downstream persisted payload,
4. payload lifecycle completed globally.

---

## 5. Container Release Model

### 5.1 Candidate Flow

```text
dispatch_exposed
→ dispatch_completed
→ reset_pending
→ under_moderation
→ default_empty
→ ingress_ready
```

### 5.2 Release Trigger Candidates

1. dispatch exposure lifecycle complete,
2. dispatch round completed,
3. dispatch refs consumed/invalidated,
4. safe point available,
5. moderator claims reset.

### 5.3 Container Release Non-Meaning

Container release does not mean:

1. final receiver completed processing,
2. bridge protocol succeeded beyond exposure observation,
3. read-side accepted material,
4. persistence occurred.

---

## 6. Reference Release Model

### 6.1 Candidate Flow

```text
issued
→ consumed
```

or:

```text
issued
→ expired
```

or:

```text
issued
→ invalidated
```

### 6.2 Release Relationship

A container cannot be reset while active references still target it unless a policy explicitly invalidates them and emits diagnostic evidence.

### 6.3 Ref Release Non-Meaning

Ref release does not mean payload release.  
It only means access permission is no longer active.

---

## 7. Exposure Release Model

### 7.1 Candidate Flow

```text
passive_exposed
→ bridge_consumed
→ release_pending
→ dispatch_completed
```

or under profile:

```text
passive_exposed
→ exposure_expired
→ release_pending
```

### 7.2 Passive Pull Consideration

Under passive pull, the bridge-facing side may consume/pull through the output boundary.  
The pre-bridge engine may observe that, but does not own what happens after bridge consumption.

### 7.3 Exposure Release Non-Meaning

Exposure release does not prove final delivery.  
It is only the closure of the pre-bridge exposure lifecycle.

---

## 8. Round Release Model

### 8.1 Ingress Round Release

An ingress round releases when:

1. candidate registration is closed,
2. waiting list drained,
3. refs prepared/issued,
4. placements executed or invalidated,
5. round completed or aborted.

### 8.2 Dispatch Round Release

A dispatch round releases when:

1. candidate registration closed,
2. waiting list drained,
3. dispatch refs prepared/issued,
4. exposures executed or invalidated,
5. round completed or aborted.

### 8.3 Round Release Effects

1. waiting lists may rebuild,
2. refs may invalidate,
3. containers may move to next state,
4. safe points may become available.

---

## 9. Container Recycle Model

### 9.1 Definition

Container recycle is the process that moves a dispatch-completed container back toward `default_empty` and `ingress_ready`.

### 9.2 Owner Chain

| Step | Owner |
|---|---|
| dispatch exposure completion | Dispatcher |
| release readiness | Container/release policy |
| reset claim | Moderator |
| default empty profile source | BundleAgent |
| concrete reset application | Moderator |
| reentry eligibility | Container state + RoundManager |

### 9.3 Recycle Preconditions

```text
dispatch exposure closed
dispatch refs consumed/invalidated
round completed
container reset safe point available
default empty profile matches active capacity/layout profile
```

### 9.4 Recycle Result

```text
slot states = empty
container state = default_empty
time range cleared
refs invalidated
container eligible for ingress_ready transition
```

---

## 10. Moderator Reset

### 10.1 Role

Moderator applies the default empty container profile to a concrete container.

### 10.2 Reset Inputs

1. container registry index,
2. container state view,
3. safe-point evidence,
4. default empty container profile,
5. active capacity profile.

### 10.3 Reset Outputs

1. reset report,
2. container state transition,
3. slot state reset,
4. time range clear,
5. readiness view.

### 10.4 Reset Invariants

```text
1. Moderator executes reset.
2. BundleAgent supplies default empty profile.
3. Reset requires safe point.
4. Reset returns container to uniform active profile.
5. Reset must invalidate or consume old refs.
```

---

## 11. Default Empty Container Reentry

### 11.1 Definition

Reentry is the movement of a reset container back into ingress eligibility.

### 11.2 Reentry Flow

```text
under_moderation
→ default_empty
→ ingress_ready
→ ingress waiting-list candidate
```

### 11.3 Reentry Ownership

| Concern | Owner |
|---|---|
| default_empty state | Moderator/container |
| ingress_ready transition | Moderator/container policy |
| waiting-list admission | RoundManager |
| ref preparation | ReferencePrecalculator |

### 11.4 Reentry Non-Meaning

Reentry does not guarantee immediate use.  
It only makes the container eligible to join a future ingress round.

---

## 12. Eviction Relationship

### 12.1 Eviction as Release Path

Eviction may force a container out of normal recycle path, but only at safe point.

### 12.2 Eviction Preconditions

1. container not active in ingress,
2. container not active in dispatch exposure,
3. refs consumed/invalidated,
4. round not using it,
5. time range / policy selected it.

### 12.3 Eviction Result

1. container moves to `evicted`,
2. registry entry may be freed/replaced,
3. report emitted,
4. waiting lists rebuilt.

---

## 13. Invariants

```text
1. Release/recycle/reset are state transitions.
2. Slot release does not equal container release.
3. Container release does not equal bridge/final receiver success.
4. Reset requires safe point.
5. Recycle returns the container to default empty profile.
6. Reentry requires RoundManager admission.
7. No active references may survive reset unless policy explicitly invalidates them.
8. Eviction requires safe point and report.
```

---

## 14. Views

| View | Purpose |
|---|---|
| `TSlotReleaseView` | Slot release readiness |
| `TContainerReleaseView` | Container release readiness |
| `TReferenceReleaseView` | Ref consumption/invalidation |
| `TExposureReleaseView` | Dispatch exposure closure |
| `TRecycleView` | Container recycle status |
| `TReentryEligibilityView` | Ingress reentry readiness |

---

## 15. Reports

| Report | Trigger |
|---|---|
| `TSlotReleaseReport` | Slot released |
| `TContainerReleaseReport` | Container released |
| `TReferenceReleaseReport` | Ref consumed/invalidated |
| `TExposureReleaseReport` | Dispatch exposure closed |
| `TContainerRecycleReport` | Container recycled |
| `TResetAppliedReport` | Moderator reset applied |
| `TReentryEligibilityReport` | Container eligible for ingress reentry |
| `TEvictionAppliedReport` | Eviction path applied |

---

## 16. Failure / Diagnostics

| Condition | Meaning |
|---|---|
| `ResetBeforeRelease` | reset attempted before release conditions |
| `RecycleWithActiveRefs` | recycle attempted with active refs |
| `ReentryWithoutDefaultEmpty` | container not default empty |
| `ExposureNotClosed` | dispatch exposure still active |
| `RoundNotCompleted` | round state blocks release |
| `DefaultProfileMismatch` | reset profile mismatch |
| `EvictionWithoutSafePoint` | eviction violation |

---

## 17. Implementation Derivation Notes

### 17.1 Candidate Headers

```text
release_recycle/
    TSlotReleaseState.hpp
    TContainerReleaseState.hpp
    TRecyclePolicy.hpp
    TRecycleReport.hpp
    TReentryEligibilityView.hpp

slots_container_moderator/
    TContainerResetPlan.hpp
    TContainerResetReport.hpp
```

### 17.2 Deferred Decisions

1. Whether release/recycle lives as shared semantic root or local component policies.
2. Whether dispatch exposure release waits for bridge observation in the pre-bridge profile.
3. Whether container recycle is synchronous inside same cycle or queued for next moderator pass.
4. Whether eviction reuses recycle mechanisms or separate path.

---

## 18. Summary

Release closes active use.  
Recycle prepares reuse.  
Reset applies the default empty container profile.  
Reentry makes the container eligible for ingress again.  
All of this is state-driven and safe-point-guarded.
