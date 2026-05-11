# CME-ARCH-006 — Round Manager And Waiting List Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-006-DOC-001 | Document Title | Round Manager And Waiting List Model |
| CME-ARCH-006-DOC-002 | Package | CME-ARCH-PACK-02 |
| CME-ARCH-006-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-006-DOC-004 | Scope Level | Round management, waiting-list ordering, container eligibility, round closure |
| CME-ARCH-006-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-006-DOC-006 | Implementation Direction | C++17, header-only-first, state-driven, profile-specialized |
| CME-ARCH-006-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-005 |
| CME-ARCH-006-DOC-008 | Related Models | `RoundManager`, `TRoundState`, `TIngressWaitingList`, `TDispatchWaitingList`, `TContainerState`, `TContainerRegistryIndex` |
| CME-ARCH-006-DOC-009 | Primary Rule | RoundManager registers eligible container indices into the proper waiting list based on state/readiness |
| CME-ARCH-006-DOC-010 | Excluded | Slot reference calculation, container creation, container reset, bridge handoff, final delivery |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines how the `RoundManager` coordinates round membership and waiting-list registration for the two circulation cycles.

It answers:

```text
How does a container become a candidate for ingress or dispatch movement,
and how is that candidacy recorded without storing payloads or leaking runtime internals?
```

### 2.2 Core Thesis

```text
RoundManager owns round membership action.
Waiting lists own ordered candidate indices.
ReferencePrecalculator owns reference calculation.
```

### 2.3 Central Separation

| Concern | Owner |
|---|---|
| container readiness exposure | Moderator / TContainer state |
| round eligibility decision | RoundManager |
| candidate ordering | WaitingList |
| access reference calculation | ReferencePrecalculator |
| access execution | Ingress / Dispatcher |

---

## 3. Scope

### 3.1 In Scope

1. Round identity.
2. Round lifecycle state.
3. Ingress vs dispatch rounds.
4. Waiting-list registration.
5. FIFO ordering.
6. Time-range-aware dispatch ordering.
7. Container eligibility.
8. Round closure and rebuild.
9. Waiting-list invariants.
10. Round reports/views.

### 3.2 Out of Scope

1. Slot access reference calculation.
2. Container topology creation.
3. Container reset.
4. Envelope parsing.
5. Bridge handoff.
6. Receiver delivery.
7. Persistence.
8. Multi-producer arbitration.

---

## 4. Round Kinds

### 4.1 Ingress Round

| Field | Value |
|---|---|
| Direction | outside → engine |
| Waiting List | `TIngressWaitingList` |
| Candidate | ingress-ready container index |
| Output | ordered indices for ingress reference calculation |
| Terminal Result | containers receive payloads into slots |

### 4.2 Dispatch Round

| Field | Value |
|---|---|
| Direction | engine → outside |
| Waiting List | `TDispatchWaitingList` |
| Candidate | dispatch-ready container index |
| Output | ordered indices for dispatch reference calculation |
| Terminal Result | containers/slots exposed to output boundary |

---

## 5. RoundManager Responsibilities

### 5.1 Positive Responsibilities

1. Own round context.
2. Own round state.
3. Evaluate container eligibility by round kind.
4. Add eligible container indices to proper waiting list.
5. Prevent registration into closed rounds.
6. Preserve separation between ingress and dispatch waiting lists.
7. Emit round admission/progression/closure reports.
8. Coordinate round-level safe points.

### 5.2 Non-Responsibilities

1. Does not create containers.
2. Does not reset containers.
3. Does not calculate slot access references.
4. Does not consume access references.
5. Does not place envelopes.
6. Does not expose dispatch.
7. Does not execute bridge handoff.
8. Does not interpret envelope content.

---

## 6. Round State Model

### 6.1 Candidate States

```text
idle
collecting_candidates
open
locked
draining
closing
closed
completed
aborted
invariant_violation
```

### 6.2 State Meaning

| State | Meaning |
|---|---|
| `idle` | No active round |
| `collecting_candidates` | Manager is evaluating containers |
| `open` | Registration allowed |
| `locked` | Membership fixed |
| `draining` | Waiting list is being consumed by ReferencePrecalculator |
| `closing` | Round is no longer accepting candidates |
| `closed` | Round cannot accept candidates |
| `completed` | Round processing complete |
| `aborted` | Round stopped due to invariant/fault |
| `invariant_violation` | Illegal state transition or membership condition |

### 6.3 Transition Sketch

```text
idle
→ collecting_candidates
→ open
→ locked
→ draining
→ closing
→ closed
→ completed
```

Abort path:

```text
open / locked / draining
→ aborted
```

---

## 7. Container Eligibility

### 7.1 Ingress Eligibility

A container is ingress-eligible when:

1. It exists in `TContainerRegistry`.
2. Its registry index is valid.
3. Its state is `default_empty`, `ingress_ready`, or other configured receiving-eligible state.
4. It is not under moderation/reset.
5. It is not locked by another round.
6. It has compatible active capacity/layout profile.
7. Round state allows candidate registration.

### 7.2 Dispatch Eligibility

A container is dispatch-eligible when:

1. It exists in `TContainerRegistry`.
2. Its registry index is valid.
3. Its state is `dispatch_candidate`, `dispatch_ready`, or configured dispatch-eligible state.
4. It has no pending reset.
5. It is not already exposed.
6. It is not evicted.
7. Round state allows candidate registration.
8. Optional time range metadata is usable if profile requires it.

---

## 8. Waiting List Model

### 8.1 Shared Meaning

A waiting list is an ordered set/list of eligible container registry indices.

It does not own:

1. container objects,
2. slot objects,
3. envelopes,
4. bridge references,
5. access refs,
6. receiver lifecycle.

### 8.2 Ingress Waiting List

```text
TIngressWaitingList
    stores indices of containers eligible to receive incoming payload envelopes.
```

### 8.3 Dispatch Waiting List

```text
TDispatchWaitingList
    stores indices of containers eligible for output exposure.
```

---

## 9. FIFO Ordering

### 9.1 Default Rule

```text
FIFO is the default waiting-list ordering policy.
```

### 9.2 Ingress FIFO

Ingress FIFO means containers enter reference calculation in the same order they were registered by the round manager.

### 9.3 Dispatch FIFO

Dispatch FIFO means containers are exposed in the order they become dispatch-eligible, unless a time-range ordering policy overrides or refines it.

### 9.4 FIFO Is Not

1. Message broker fairness.
2. Consumer group scheduling.
3. Multi-producer arbitration.
4. Receiver retry ordering.

---

## 10. Time-Range-Aware Dispatch Ordering

### 10.1 Purpose

For dispatch, a container may carry a `TContainerTimeRange`.

This supports:

1. oldest-container eviction,
2. dispatch ordering,
3. diagnostic reporting,
4. proof of temporal coverage.

### 10.2 Time Range Fields

```text
first_timestamp
last_timestamp
timestamp_basis
completeness_status
```

### 10.3 Ordering Rule

Default:

```text
FIFO
```

Optional:

```text
FIFO primary + oldest time range tie-breaker
```

or:

```text
Oldest time range first
```

depending on dispatch profile.

### 10.4 Non-Meaning

Time range metadata does not make circulation interpret timestamp semantics.  
It is ordering/eviction metadata only.

---

## 11. Waiting List State

### 11.1 Shared Candidate States

```text
empty
accepting_candidates
ready_for_round
locked_by_round
draining_to_precalculator
cleared
invariant_violation
```

### 11.2 Dispatch-Specific Extension

```text
eviction_candidate_selection
```

### 11.3 State Ownership

The waiting list owns its list state.  
RoundManager owns the action that changes list membership during round participation.

---

## 12. Round Closure

### 12.1 Closure Meaning

Round closure means no more candidates may be added.

### 12.2 Effects

1. Waiting list becomes locked or draining.
2. ReferencePrecalculator may consume list entries.
3. New eligibility must wait for a new round.
4. Stale registrations are rejected.
5. Safe point may become available after draining/completion.

### 12.3 Closure Does Not Mean

1. Container reset.
2. Slot release.
3. Bridge acceptance.
4. Payload lifecycle completion.
5. Dispatch finality.

---

## 13. Waiting List Rebuild

### 13.1 Rebuild Triggers

1. Round completed.
2. Registry profile switched.
3. Container evicted.
4. Reference invalidation sweep.
5. Moderator reset applied.
6. Safe-point profile rebuild.

### 13.2 Rebuild Requirements

```text
registry indices must be valid
container states must be re-evaluated
duplicate membership must be prevented
round state must accept new candidates
```

---

## 14. Invariants

### 14.1 RoundManager Invariants

```text
1. RoundManager does not add container to waiting list unless state/readiness qualifies.
2. RoundManager does not add to a closed round.
3. RoundManager does not compute refs.
4. RoundManager does not create containers.
5. RoundManager does not execute bridge handoff.
6. RoundManager distinguishes ingress and dispatch rounds.
```

### 14.2 Waiting List Invariants

```text
1. Waiting lists store container registry indices.
2. Waiting lists do not store envelopes.
3. Waiting lists do not own containers.
4. Waiting lists do not choose slots.
5. Waiting lists are round-scoped.
6. Waiting list entries must be valid against registry.
```

### 14.3 Ordering Invariants

```text
1. FIFO is default.
2. Time-range ordering is dispatch-specific unless explicitly generalized.
3. Eviction ordering does not imply payload semantic interpretation.
```

---

## 15. Views

| View | Owner | Purpose |
|---|---|---|
| `TRoundView` | RoundManager | Round state projection |
| `TRoundMembershipView` | RoundManager | Round members |
| `TRoundEligibilityView` | RoundManager | Eligible/blocked candidates |
| `TIngressWaitingListView` | IngressWaitingList | Ordered ingress candidates |
| `TDispatchWaitingListView` | DispatchWaitingList | Ordered dispatch candidates |
| `TDispatchOrderingView` | DispatchWaitingList | FIFO/time-range ordering |
| `TDispatchEvictionCandidateView` | DispatchWaitingList | Eviction candidates |

---

## 16. Reports

| Report | Trigger |
|---|---|
| `TRoundAdmissionReport` | Container admitted to round/list |
| `TRoundProgressionReport` | Round transition |
| `TRoundClosureReport` | Round closed |
| `TIngressWaitingListRegistrationReport` | Ingress candidate registered |
| `TDispatchWaitingListRegistrationReport` | Dispatch candidate registered |
| `TDispatchEvictionSelectionReport` | Eviction candidate selected |
| `TRoundInvariantReport` | Round invariant violation |

---

## 17. Failure / Diagnostics

| Failure | Meaning |
|---|---|
| `RoundClosedRegistration` | Candidate added after closure |
| `ContainerStateNotEligible` | State mismatch |
| `DuplicateRoundMember` | Duplicate membership |
| `WaitingListRejectedCandidate` | List refused index |
| `StaleContainerIndex` | Registry index invalid |
| `UnexpectedEmptyWaitingList` | Profile expected candidates but none available |

---

## 18. Safe Points

| Safe Point | Owner | Meaning |
|---|---|---|
| `round_open` | RoundManager | Candidates accepted |
| `round_locked` | RoundManager | Membership fixed |
| `round_drained` | WaitingList / RefPrecalc | Candidate list consumed |
| `round_closed` | RoundManager | No more candidates |
| `round_completed` | RoundManager | Safe transitions may begin |

---

## 19. Configuration Profiles

| Profile | Purpose |
|---|---|
| `TIngressRoundProfile` | Ingress round behavior |
| `TDispatchRoundProfile` | Dispatch round behavior |
| `TRoundMembershipPolicy` | Membership rules |
| `TRoundClosurePolicy` | Closure rules |
| `TIngressWaitingListProfile` | Ingress list behavior |
| `TDispatchWaitingListProfile` | Dispatch list behavior |
| `TDispatchOrderingPolicy` | FIFO/time-range |
| `TEvictionPolicyProfile` | Eviction selection |

---

## 20. Implementation Derivation Notes

### 20.1 Candidate Headers

```text
round_manager/
    TRoundManager.hpp
    TRoundState.hpp
    TRoundView.hpp
    TRoundAdmissionReport.hpp

waiting_list/
    TIngressWaitingList.hpp
    TDispatchWaitingList.hpp
    TWaitingListState.hpp
    TWaitingListView.hpp
```

### 20.2 Deferred Decisions

1. Whether `RoundManager` is one template specialized by round kind or two separate managers.
2. Whether waiting lists are separate concrete types or `TWaitingList<RoundKind>`.
3. Whether time-range ordering is embedded in dispatch waiting list or delegated to an ordering policy.
4. Whether round IDs are required in first implementation wave.

---

## 21. Summary

RoundManager coordinates eligibility and membership.  
Waiting lists hold ordered container indices.  
ReferencePrecalculator consumes those indices.  
Ingress and Dispatcher consume references.  
No waiting list stores payload.  
No round performs bridge delivery.
