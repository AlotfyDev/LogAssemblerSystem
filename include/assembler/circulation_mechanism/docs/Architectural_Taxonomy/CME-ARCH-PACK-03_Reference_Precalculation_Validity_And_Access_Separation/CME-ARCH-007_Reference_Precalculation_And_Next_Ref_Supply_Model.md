# CME-ARCH-007 — Reference Precalculation And Next Ref Supply Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-007-DOC-001 | Document Title | Reference Precalculation And Next Ref Supply Model |
| CME-ARCH-007-DOC-002 | Package | CME-ARCH-PACK-03 |
| CME-ARCH-007-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-007-DOC-004 | Scope Level | Reference calculation, next-ref supply, candidate resolution, access preparation |
| CME-ARCH-007-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-007-DOC-006 | Implementation Direction | C++17, header-only-first, profile-driven, hot-path locating avoided |
| CME-ARCH-007-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-006 |
| CME-ARCH-007-DOC-008 | Related Models | `TContainerRegistry`, `TContainerRegistryIndex`, `TIngressWaitingList`, `TDispatchWaitingList`, `RoundManager`, `TIngressAccessRef`, `TDispatchAccessRef` |
| CME-ARCH-007-DOC-009 | Primary Rule | ReferencePrecalculator separates locating/reference calculation from slot/data access |
| CME-ARCH-007-DOC-010 | Excluded | Log API internals, bridge protocol, envelope content interpretation, copy/move decision, final receiver lifecycle |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the reference-precalculation model inside the Circulation Mechanism Engine.

It answers:

```text
How does the engine continuously provide ready access references to ingress-side
and dispatch-side consumers without requiring those consumers to locate containers
or slots at access time?
```

### 2.2 Core Thesis

```text
Locating is a preparation concern.
Accessing is an execution concern.
```

The `ReferencePrecalculator` computes and supplies access references from registered container candidates, registry indices, container state, slot state, waiting-list ordering, and round context.

The consumers of these references only consume `next`.

### 2.3 Architectural Role

The `ReferencePrecalculator` is the mechanism that makes the following possible:

```text
producer-facing side:
    give me next ingress placement ref

dispatch-facing side:
    give me next dispatch access/exposure ref
```

Neither consumer needs to know:

1. container count,
2. current container,
3. slot index,
4. remaining capacity,
5. waiting-list ordering,
6. registry access path,
7. round membership mechanics.

---

## 3. Scope

### 3.1 In Scope

1. ReferencePrecalculator responsibility.
2. Inputs from waiting lists.
3. Inputs from container registry.
4. Inputs from container state.
5. Inputs from slot state.
6. Inputs from round context.
7. Ingress reference preparation.
8. Dispatch reference preparation.
9. Next-ref supply.
10. Reference supply state.
11. Reference supply reports.
12. Invariants and diagnostics.

### 3.2 Out of Scope

1. Consumer-side access execution.
2. Envelope assembly.
3. Payload parsing.
4. Bridge protocol.
5. Copy/move semantics after dispatch exposure.
6. Final receiver behavior.
7. Persistent storage.
8. Multi-producer scheduling.
9. Message broker semantics.

---

## 4. ReferencePrecalculator Definition

### 4.1 Definition

`ReferencePrecalculator` is the circulation-owned actor responsible for continuously preparing ingress-side and dispatch-side access references from:

1. `TContainerRegistryIndex`,
2. `TContainerRegistry`,
3. `TContainerState`,
4. `TSlotState`,
5. slot layout,
6. waiting-list ordering,
7. round context,
8. reference validity policy,
9. access direction profile.

### 4.2 Category

| Field | Value |
|---|---|
| Category | Actor / Reference Calculation Coordinator |
| Ownership | `circulation_mechanism` |
| Execution Position | Between waiting lists and access executors |
| Primary Output | `TIngressAccessRef`, `TDispatchAccessRef`, optional `TSlotAccessRef` |
| Default Behavior | Continuous next-ref supply |

### 4.3 Positive Responsibilities

1. Consume ordered candidate indices from waiting lists.
2. Resolve container candidates through the registry.
3. Inspect container state and slot state through approved views.
4. Select or prepare valid access references.
5. Maintain a ready supply of next ingress references.
6. Maintain a ready supply of next dispatch references.
7. Invalidate references when scope changes.
8. Emit reference-precalculation reports.
9. Emit supply interruption diagnostics.
10. Preserve direction-specific reference separation.

### 4.4 Non-Responsibilities

The `ReferencePrecalculator` does not:

1. produce envelopes,
2. parse envelopes,
3. inspect envelope semantic content,
4. place envelopes into slots,
5. expose envelopes to bridge,
6. own copy/move semantics,
7. execute bridge protocol,
8. create containers,
9. reset containers,
10. decide final receiver delivery.

---

## 5. Inputs

### 5.1 Input Matrix

| Input | Source | Purpose |
|---|---|---|
| `TContainerRegistryIndex` | Waiting lists | Identify container candidate |
| `TContainerRegistryView` | Registry | Resolve index safely |
| `TContainerStateView` | Container / Moderator | Determine cycle eligibility |
| `TSlotStateView` | Slot / Container | Determine access readiness |
| `TIngressWaitingListView` | Ingress waiting list | Ordered ingress candidates |
| `TDispatchWaitingListView` | Dispatch waiting list | Ordered dispatch candidates |
| `TRoundView` | RoundManager | Round state/scope |
| `TRoundMembershipView` | RoundManager | Membership context |
| `TReferenceValidityPolicy` | Configuration/profile | Validity rules |
| `TReferenceSupplyPolicy` | Configuration/profile | Supply depth and refill strategy |

### 5.2 Input Guard Rules

A reference must not be prepared unless:

```text
1. registry index is valid,
2. container exists,
3. container state matches requested direction,
4. slot layout is compatible,
5. slot state allows access,
6. round state is open/valid for reference preparation,
7. no safe-point invalidation is pending,
8. direction profile matches requested ref type.
```

---

## 6. Outputs

### 6.1 Output Types

| Output | Direction | Consumer |
|---|---|---|
| `TIngressAccessRef` | outside → engine | Ingress / Log API plugin adapter |
| `TDispatchAccessRef` | engine → outside | Dispatcher / bridge-facing side |
| `TSlotAccessRef` | abstract/internal | internal specialization |
| `TRoundScopedRef` | scoped | any direction-specific ref |
| `TNextRefToken` | consumer-facing rhythm | approved consumers |
| `TReferencePrecalculationReport` | diagnostics | observability/tests |
| `TReferenceSupplyView` | read-only | diagnostics/monitoring |

### 6.2 Output Stability

| Output | Stability |
|---|---|
| `TIngressAccessRef` | valid until consumed, expired, invalidated, or round closes |
| `TDispatchAccessRef` | valid until consumed, expired, invalidated, or exposure changes |
| `TSlotAccessRef` | internal validity determined by specialization |
| `TNextRefToken` | token-level validity only; not a container locator |
| Report | immutable event evidence |
| View | read-only projection, snapshot or live-view depending profile |

---

## 7. Continuous Next-Ref Supply

### 7.1 Meaning

Continuous next-ref supply means that, under the configured capacity and profile assumptions, approved consumers experience the reference supply as:

```text
next
next
next
...
```

without participating in locating.

### 7.2 Internal Mechanics

The continuous supply is maintained by:

1. waiting-list candidate ordering,
2. registry-index resolution,
3. container-state checks,
4. slot-state checks,
5. round context checks,
6. precomputed reference queue/pool,
7. invalidation/replenishment policy.

### 7.3 Not a Guarantee of Infinite Capacity

Continuous supply is not unbounded magic. It depends on:

1. `TCirculationCapacityProfile`,
2. uniform container capacity,
3. waiting-list availability,
4. configured extreme default provisioning,
5. safe-point timing,
6. bridge drain assumption for dispatch side.

### 7.4 Supply Interruption

If next-ref supply is interrupted under a profile that declares it should be continuous, the interruption is an invariant diagnostic, not a normal consumer-facing outcome.

---

## 8. Ingress Reference Preparation

### 8.1 Ingress Candidate Source

`TIngressWaitingList` provides container registry indices for containers eligible to receive envelopes.

### 8.2 Ingress Calculation

The precalculator:

1. obtains next ingress candidate index,
2. resolves container view,
3. checks container ingress state,
4. identifies writable/reserved slot,
5. creates `TIngressAccessRef`,
6. publishes it to ingress-side supply.

### 8.3 Ingress Reference Consumer

Ingress-side consumers include:

1. `Ingress`,
2. `EnvelopePlacementPort`,
3. Log API plugin adapter through the approved boundary.

### 8.4 Ingress Ref Non-Meaning

An ingress ref does not mean:

1. envelope is already placed,
2. dispatch is possible,
3. bridge may access the slot,
4. producer owns the slot,
5. container topology is exposed.

---

## 9. Dispatch Reference Preparation

### 9.1 Dispatch Candidate Source

`TDispatchWaitingList` provides container registry indices for containers eligible for output exposure.

### 9.2 Dispatch Calculation

The precalculator:

1. obtains next dispatch candidate index,
2. resolves container view,
3. checks container dispatch state,
4. identifies dispatch-ready slot/material,
5. creates `TDispatchAccessRef`,
6. publishes it to dispatch-side supply.

### 9.3 Dispatch Reference Consumer

Dispatch-side consumers include:

1. `Dispatcher`,
2. bridge-facing adapter,
3. passive exposure boundary.

### 9.4 Dispatch Ref Non-Meaning

A dispatch ref does not mean:

1. bridge has copied or moved the envelope,
2. final receiver received the envelope,
3. downstream persistence exists,
4. slot can be reset immediately,
5. bridge protocol has executed.

---

## 10. Reference Supply State

### 10.1 Candidate States

```text
ready
replenishing
ingress_refs_ready
dispatch_refs_ready
waiting_for_candidates
invalidating_refs
supply_interrupted
invariant_violation
```

### 10.2 State Meanings

| State | Meaning |
|---|---|
| `ready` | General reference supply is available |
| `replenishing` | Precalculator is preparing more refs |
| `ingress_refs_ready` | Ingress ref pool/sequence ready |
| `dispatch_refs_ready` | Dispatch ref pool/sequence ready |
| `waiting_for_candidates` | Waiting list did not provide usable candidates |
| `invalidating_refs` | Refs are being invalidated due to transition |
| `supply_interrupted` | Expected next-ref supply broke |
| `invariant_violation` | Internal consistency failed |

---

## 11. Invariants

### 11.1 Calculation Invariants

```text
1. No ref without a valid registry index.
2. No ref without a valid container state.
3. No ref without compatible slot state.
4. No ref across direction boundary.
5. No ref across round scope.
6. No ref across safe-point invalidation.
7. No ref from private container internals exposed to consumer.
```

### 11.2 Ownership Invariants

```text
1. ReferencePrecalculator owns locating.
2. Ingress owns ingress access.
3. Dispatcher owns dispatch exposure.
4. Bridge owns bridge-side transfer semantics.
5. Producer owns envelope production, not slot locating.
```

### 11.3 Hot-Path Invariants

```text
1. No container scan by producer.
2. No slot scan by dispatcher.
3. No payload semantic inspection by ReferencePrecalculator.
4. No bridge protocol assumption in reference calculation.
```

---

## 12. Views

| View | Purpose |
|---|---|
| `TReferenceSupplyView` | Overall supply state |
| `TIngressReferenceSupplyView` | Ingress ref availability |
| `TDispatchReferenceSupplyView` | Dispatch ref availability |
| `TReferenceCandidateView` | Internal candidate projection |
| `TReferenceInvalidationView` | Pending invalidations |
| `TReferencePrecalculatorView` | Actor-level state |

---

## 13. Reports

| Report | Trigger |
|---|---|
| `TReferencePrecalculationReport` | Refs prepared |
| `TReferenceSupplyInterruptionReport` | Expected continuous supply failed |
| `TReferenceInvalidationReport` | Refs invalidated |
| `TStaleReferenceReport` | Stale reference detected |
| `TReferenceCandidateRejectionReport` | Candidate rejected |
| `TReferenceDirectionMismatchReport` | Wrong ref kind/direction detected |

---

## 14. Failure / Diagnostics

| Failure | Meaning |
|---|---|
| `InvalidRegistryIndex` | Waiting list yielded invalid index |
| `ContainerStateMismatch` | Container no longer eligible |
| `SlotStateMismatch` | Slot no longer writable/dispatchable |
| `RoundScopeViolation` | Round context expired/changed |
| `SafePointInvalidation` | Ref invalidated by safe point operation |
| `ReferenceSupplyInterrupted` | Continuous next-ref contract broken |
| `DirectionMismatch` | Ingress/dispatch ref used incorrectly |

---

## 15. Configuration Profiles

| Profile | Purpose |
|---|---|
| `TReferenceSupplyPolicy` | Defines supply behavior/depth |
| `TIngressReferencePolicy` | Ingress ref calculation |
| `TDispatchReferencePolicy` | Dispatch ref calculation |
| `TReferenceValidityPolicy` | Scope and expiration |
| `TReferencePrecalculationBatchPolicy` | Number of refs calculated ahead |
| `TReferenceInvalidationPolicy` | Invalidation rules |

---

## 16. Implementation Derivation Notes

### 16.1 Candidate Header Families

```text
reference_precalculator/
    TReferencePrecalculator.hpp
    TReferenceSupplyState.hpp
    TReferenceSupplyView.hpp
    TReferencePrecalculationReport.hpp
    TReferenceSupplyPolicy.hpp

reference_precalculator/handles/
    TIngressAccessRef.hpp
    TDispatchAccessRef.hpp
    TSlotAccessRef.hpp
    TRoundScopedRef.hpp
    TNextRefToken.hpp
```

### 16.2 Deferred Decisions

1. Whether `TNextRefToken` wraps concrete access refs or only acts as consumer rhythm marker.
2. Whether reference pools are explicit data structures or generated lazily under static policy.
3. Whether `TSlotAccessRef` is public internal or only a base concept for direction-specific refs.
4. Whether the dispatch bridge-facing adapter receives `TDispatchAccessRef` directly or only an exposure view.

---

## 17. Summary

`ReferencePrecalculator` is the engine’s locating/calculation authority.  
It transforms registry indices and state views into direction-specific access references.  
Consumers receive `next` references; they do not locate.  
The model preserves hot-path simplicity and boundary integrity.
