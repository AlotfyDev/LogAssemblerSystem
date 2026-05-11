# CME-ARCH-017 — Eviction By Container Time Range Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-017-DOC-001 | Document Title | Eviction By Container Time Range Model |
| CME-ARCH-017-DOC-002 | Package | CME-ARCH-PACK-07 |
| CME-ARCH-017-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-017-DOC-004 | Scope Level | Eviction, container time range, eviction candidate selection, safe-point guarded removal |
| CME-ARCH-017-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-017-DOC-006 | Implementation Direction | C++17, header-only-first, policy-driven, safe-point guarded |
| CME-ARCH-017-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-016 |
| CME-ARCH-017-DOC-008 | Related Models | `TContainerTimeRange`, `TDispatchWaitingList`, `TContainerState`, `TReferenceValidity`, `SafePoint`, `ReadSideProfile` |
| CME-ARCH-017-DOC-009 | Primary Rule | Eviction is safe-point guarded and may use container time range as ordering metadata |
| CME-ARCH-017-DOC-010 | Excluded | receiver retry, persistence deletion, bridge failure recovery, downstream lifecycle eviction |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines eviction behavior for the pre-bridge Circulation Mechanism Engine.

It answers:

```text
If the engine reaches a configured boundary, how can it select an eviction candidate
without turning into a backpressure broker or receiver-side retry mechanism?
```

### 2.2 Core Thesis

```text
Eviction is an exceptional, policy-governed, safe-point-guarded container transition.
It is not ordinary message-broker backpressure.
```

### 2.3 Architectural Role

Eviction exists to:

1. protect finite capacity boundaries,
2. provide deterministic candidate selection,
3. preserve time-ordering where configured,
4. prevent unsafe mutation of active containers,
5. emit diagnostic evidence.

---

## 3. `TContainerTimeRange`

### 3.1 Definition

`TContainerTimeRange` is metadata describing the timestamp range covered by the payload envelopes resident in a container.

### 3.2 Candidate Fields

```text
first_timestamp
last_timestamp
timestamp_basis
completeness_status
source_count
sealed_at_sequence
```

### 3.3 Purpose

The time range supports:

1. dispatch ordering,
2. eviction candidate selection,
3. diagnostics,
4. temporal coverage reports,
5. traceability of container residency.

### 3.4 Non-Meaning

Time range does not mean:

1. circulation interprets business timestamp semantics,
2. timestamp stabilization belongs to CME,
3. downstream query semantics belong to CME,
4. eviction proves payload is unimportant,
5. container time range replaces envelope timestamp.

---

## 4. Time Range Lifecycle

### 4.1 Initial State

When a container is `default_empty`, its time range is empty/cleared.

### 4.2 Update During Ingress

As envelopes are placed:

1. first timestamp may initialize range,
2. later timestamps update last/coverage,
3. invalid or absent timestamp may set completeness status,
4. update remains metadata-only.

### 4.3 Sealing

When container becomes `filled_or_closed`, the time range may be sealed for dispatch ordering.

### 4.4 Clearing

During reset/recycle, time range is cleared.

---

## 5. `TEvictionCandidate`

### 5.1 Definition

`TEvictionCandidate` is a diagnostic/decision carrier identifying a container selected or considered for eviction.

### 5.2 Candidate Fields

```text
candidate_id
container_registry_index
container_id
container_state
time_range
eviction_reason
eligibility_state
safe_point_status
selected_by_policy
```

### 5.3 Non-Meaning

An eviction candidate is not:

1. already evicted,
2. unsafe to keep,
3. receiver failure,
4. persistence deletion,
5. bridge failure proof.

---

## 6. Eviction Policies

## 6.1 `OldestTimeRangeEviction`

### 6.1.1 Definition

Select the eligible container with the oldest time range.

### 6.1.2 Use

Useful when dispatch ordering or bounded memory requires removing older material first.

### 6.1.3 Requirements

1. time range exists,
2. time range comparable,
3. container safe to evict,
4. refs consumed/invalidated,
5. round not using container.

## 6.2 `FifoContainerEviction`

### 6.2.1 Definition

Select the oldest registered container by FIFO order.

### 6.2.2 Use

Useful when time range is unavailable or disabled.

## 6.3 `NoEvictionPreBridgeProfile`

### 6.3.1 Definition

Eviction disabled for normal pre-bridge operation.

### 6.3.2 Use

Preferred when pre-sized extreme profile should avoid eviction altogether.

### 6.3.3 Diagnostic

If capacity is exceeded under this profile:

```text
ExtremeProfileInsufficient
```

## 6.4 `DelegateToReadSideProfile`

### 6.4.1 Definition

Capacity/receiver delay concern is delegated beyond the bridge.

### 6.4.2 Use

When delayed receiver consumption is better modeled in read-side circulation.

## 6.5 `EmergencyEvictionProfile`

### 6.5.1 Definition

Eviction allowed only under severe invariant/protection condition.

### 6.5.2 Use

Production-hardening or emergency mode, not default.

---

## 7. Eviction Preconditions

Eviction may occur only if all required conditions hold:

```text
1. container is not under active ingress.
2. container is not under active dispatch exposure.
3. container is not a member of an active round.
4. all references to the container/slots are consumed, expired, or invalidated.
5. container state allows eviction.
6. registry index is valid.
7. safe point is available and claimed.
8. eviction policy selected the candidate.
9. eviction report can be emitted.
```

---

## 8. Eviction Decision Flow

### 8.1 Decision Inputs

1. active capacity profile,
2. dispatch waiting list state,
3. container registry view,
4. container time range views,
5. reference validity views,
6. round state,
7. safe point views,
8. eviction policy profile.

### 8.2 Decision Outcomes

| Outcome | Meaning |
|---|---|
| `no_eviction_required` | Capacity not exceeded |
| `eviction_disabled` | Profile disallows eviction |
| `candidate_selected` | Candidate identified |
| `candidate_rejected` | Candidate failed preconditions |
| `eviction_applied` | Candidate evicted |
| `delegated_to_read_side` | Concern deferred beyond bridge |
| `emergency_eviction_required` | Emergency profile invoked |

---

## 9. Eviction And Waiting Lists

### 9.1 Dispatch Waiting List

Eviction may use `TDispatchWaitingList` ordering and time range metadata.

### 9.2 Ingress Waiting List

Ingress waiting list is generally not used for eviction selection unless a profile explicitly says so.

### 9.3 Waiting List Rebuild

After eviction:

1. waiting list entries referencing evicted index must be removed,
2. stale index diagnostics may be emitted,
3. reference supply must invalidate related refs,
4. registry view must update.

---

## 10. Eviction And References

### 10.1 Reference Rule

```text
No active reference may target a container selected for eviction.
```

### 10.2 Required Actions

Before eviction:

1. detect active refs,
2. consume or invalidate refs,
3. emit invalidation report,
4. prevent new refs for target container,
5. confirm safe point.

### 10.3 Violation

If eviction occurs with active refs:

```text
EvictionWithActiveRefsViolation
```

---

## 11. Eviction And Dispatch Exposure

### 11.1 Rule

```text
A container under active dispatch exposure cannot be evicted.
```

### 11.2 Exposure Closure

Eviction requires:

1. exposure closed,
2. bridge observation completed or expired according to profile,
3. release state reached,
4. safe point available.

---

## 12. Eviction And Read-Side Delegation

### 12.1 Pre-Bridge Default

The pre-bridge profile should generally avoid normal eviction through extreme capacity.

### 12.2 Delegation

If the problem is receiver delay, retry, or failed dispatch, the model should delegate to read-side profile.

### 12.3 Delegation Report

```text
TCapacityDelegatedToReadSideReport
```

### 12.4 Non-Collapse

Delegation does not make read-side part of pre-bridge CME.

---

## 13. Eviction Invariants

```text
1. No eviction without safe point.
2. No eviction while container is active in ingress.
3. No eviction while container is under active dispatch exposure.
4. No eviction while round uses the container.
5. No eviction with active refs.
6. Time range is ordering metadata only.
7. Eviction does not prove final delivery failure.
8. Eviction does not make CME a retry engine.
```

---

## 14. Views

| View | Purpose |
|---|---|
| `TContainerTimeRangeView` | Shows container time range |
| `TEvictionCandidateView` | Shows selected/possible candidate |
| `TEvictionPolicyView` | Shows active eviction profile |
| `TEvictionSafePointView` | Shows eviction safe-point readiness |
| `TCapacityBoundaryView` | Shows capacity boundary condition |
| `TReadSideDelegationView` | Shows delegation decision |

---

## 15. Reports

| Report | Trigger |
|---|---|
| `TEvictionSelectionReport` | Candidate selected |
| `TEvictionAppliedReport` | Eviction applied |
| `TEvictionRejectedReport` | Candidate rejected |
| `TEvictionWithoutSafePointReport` | Unsafe attempt |
| `TEvictionWithActiveRefsReport` | Active refs detected |
| `TContainerTimeRangeViolationReport` | Time range invalid |
| `TCapacityDelegatedToReadSideReport` | Delegated to read-side |
| `TExtremeProfileInsufficientReport` | Extreme profile insufficient |

---

## 16. Implementation Derivation Notes

### 16.1 Candidate Headers

```text
eviction/
    TContainerTimeRange.hpp
    TEvictionCandidate.hpp
    TEvictionPolicyProfile.hpp
    TEvictionSelectionReport.hpp
    TEvictionAppliedReport.hpp

capacity/
    TCapacityBoundaryView.hpp
```

### 16.2 Deferred Decisions

1. Whether eviction lives in `dispatcher/`, `slots_container/`, or a shared `eviction/` root.
2. Whether time range is required for all containers or only dispatch profile.
3. Whether `NoEvictionPreBridgeProfile` is the first implementation default.
4. Whether read-side delegation emits only report or opens a boundary event.
5. Whether eviction removes container or recycles it into default empty profile.

---

## 17. Summary

Eviction is exceptional.  
Time range helps select candidates.  
Safe points protect references and active rounds.  
Read-side delay should remain read-side unless a profile explicitly pulls responsibility into pre-bridge CME.
