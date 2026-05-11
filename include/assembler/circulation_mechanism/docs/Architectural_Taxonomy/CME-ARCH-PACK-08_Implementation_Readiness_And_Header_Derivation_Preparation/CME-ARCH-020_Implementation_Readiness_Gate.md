# CME-ARCH-020 — Implementation Readiness Gate

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-020-DOC-001 | Document Title | Implementation Readiness Gate |
| CME-ARCH-020-DOC-002 | Package | CME-ARCH-PACK-08 |
| CME-ARCH-020-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-020-DOC-004 | Scope Level | Readiness gates, coverage checklist, deferred decisions, test derivation, diagram completion |
| CME-ARCH-020-DOC-005 | Status | Implementation Readiness Gate Draft |
| CME-ARCH-020-DOC-006 | Implementation Direction | C++17, header-only-first, static/profile-driven |
| CME-ARCH-020-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-019 |
| CME-ARCH-020-DOC-008 | Primary Rule | Implementation may begin only after architecture coverage and deferred decisions are classified |
| CME-ARCH-020-DOC-009 | Excluded | Actual C++ implementation, final include graph, final test code |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the readiness gate for moving from circulation architecture documents to implementation wave planning.

It answers:

```text
What must be true before we start deriving C++ headers and implementation waves
for the Circulation Mechanism Engine?
```

### 2.2 Core Thesis

```text
Readiness is not implementation.
Readiness is permission to plan implementation waves.
```

---

## 3. Readiness Gate Overview

### 3.1 Gate Status Values

| Status | Meaning |
|---|---|
| `ready` | May enter implementation planning |
| `ready_with_notes` | May proceed with known cautions |
| `needs_modeling` | Must model further |
| `deferred` | Intentionally out of current wave |
| `blocked` | Cannot proceed |

### 3.2 Gate Families

1. identity and boundary,
2. component ownership,
3. state and transition ownership,
4. reference validity,
5. safe points,
6. release/recycle,
7. boundary profiles,
8. diagnostics/views/reports,
9. capacity/eviction,
10. header candidate derivation,
11. test derivation,
12. deferred decisions.

---

## 4. Coverage Checklist

## 4.1 Identity And Boundary

| Gate | Status | Evidence |
|---|---|---|
| Engine identity defined | ready | CME-ARCH-000 |
| Pre-bridge write-side profile defined | ready | CME-ARCH-000 / 013 |
| Read-side separation defined | ready_with_notes | CME-ARCH-013 |
| Log API boundary defined | ready | CME-ARCH-004 / prior LOGAPI binding |
| Bridge boundary defined | ready_with_notes | CME-ARCH-005 / 012 |

## 4.2 Component Ownership

| Component | Status |
|---|---|
| BundleAgent | ready |
| Moderator | ready |
| TContainerRegistry | ready |
| TContainer | ready |
| TSlot | ready |
| WaitingLists | ready |
| RoundManager | ready |
| ReferencePrecalculator | ready |
| Ingress | ready |
| Dispatcher | ready |
| BoundaryBindings | ready_with_notes |

## 4.3 State Ownership

| State | Status |
|---|---|
| TSlotState | ready |
| TContainerState | ready |
| TRoundState | ready |
| TModeratorState | ready |
| TBundleAgentState | ready |
| TReferenceSupplyState | ready |
| TDispatchExposureState | ready |

## 4.4 References

| Gate | Status |
|---|---|
| TIngressAccessRef defined | ready |
| TDispatchAccessRef defined | ready |
| TSlotAccessRef defined | ready_with_notes |
| TRoundScopedRef defined | ready |
| TNextRefToken defined | needs_modeling |
| Stale ref diagnostics defined | ready |
| Reference invalidation rules defined | ready |

## 4.5 Safe Points

| Gate | Status |
|---|---|
| Safe point sources defined | ready |
| Safe point states defined | ready |
| Reset safe point defined | ready |
| Vertical scaling safe point defined | ready |
| Eviction safe point defined | ready |
| Registry rebuild safe point defined | ready |
| Safe point implementation location | deferred |

## 4.6 Release / Recycle

| Gate | Status |
|---|---|
| Slot release defined | ready |
| Container release defined | ready |
| Reference release defined | ready |
| Exposure release defined | ready_with_notes |
| Container recycle defined | ready |
| Default empty reentry defined | ready |

## 4.7 Boundary Profiles

| Gate | Status |
|---|---|
| Passive pull default defined | ready |
| Optional push profile defined | ready_with_notes |
| Bridge drain assumption defined | ready_with_notes |
| Copy/move outside CME defined | ready |
| Failed-dispatch mostly read-side | ready_with_notes |

## 4.8 Diagnostics / Views / Reports

| Gate | Status |
|---|---|
| View inventory defined | ready |
| Report inventory defined | ready |
| Diagnostic categories defined | ready |
| Invariant violation matrix defined | ready |
| Central diagnostics root | deferred |
| Report storage strategy | deferred |

## 4.9 Capacity / Eviction

| Gate | Status |
|---|---|
| Capacity profile defined | ready |
| Uniform capacity defined | ready |
| Horizontal scaling defined | ready |
| Vertical scaling defined | ready |
| Extreme default profile defined | ready |
| Time range model defined | ready |
| Eviction policies defined | ready_with_notes |
| Eviction default policy | deferred |

---

## 5. Unresolved Decisions

### 5.1 Critical Before First Implementation Wave

1. Are refs generation-bound in the first wave?
2. Is `TNextRefToken` a real type or a documentation-level rhythm?
3. Are safe points centralized or component-local?
4. Do reports live locally or under diagnostics root?
5. Is `TContainerRef` needed in addition to registry index?

### 5.2 Can Be Deferred

1. Push dispatch profile.
2. Read-side failed-dispatch list.
3. Read-side retry profile.
4. Central diagnostics collector.
5. Policy assignment integration.
6. Persistence / audit export.

---

## 6. Deferred Read-Side Profile

### 6.1 Deferred Items

```text
TFailedDispatchWaitingList
TReceiverRetryList
TDelayedReleaseList
TReceiverBackpressureProfile
TReceiverAcknowledgementProfile
```

### 6.2 Rule

These should not block pre-bridge CME implementation unless bridge/read-side contract requires them.

---

## 7. Deferred Policy Assignment

Policy assignment remains deferred for CME core implementation.

However, future policy integration may affect:

1. capacity profiles,
2. eviction profiles,
3. dispatch exposure profile,
4. round policy,
5. safe point policy,
6. diagnostics severity policy.

Policy integration must follow the policy object host and target capability model later.

---

## 8. Test Derivation

### 8.1 First-Wave Tests

Recommended first implementation tests:

```text
container_registry_index_test
uniform_capacity_test
slot_state_machine_test
container_state_machine_test
waiting_list_no_payload_test
round_closed_registration_test
reference_validity_test
ingress_requires_ref_test
dispatcher_passive_pull_test
safe_point_required_operations_test
```

### 8.2 Negative Tests

```text
waiting_list_stores_envelope_negative_test
dispatch_ref_used_for_ingress_negative_test
reset_outside_safe_point_negative_test
eviction_with_active_ref_negative_test
bridge_mutable_internal_exposure_negative_test
```

### 8.3 Test Rule

Tests must verify architectural boundaries, not only compile success.

---

## 9. Diagram Completion

### 9.1 Completed Diagram Families

1. context and holistic map,
2. taxonomy tree,
3. container registry indexing,
4. ingress sequence,
5. dispatch sequence,
6. round/waiting list stateflow,
7. reference precalculation,
8. reference validity,
9. state machines,
10. safe points,
11. release/recycle,
12. passive/push dispatch,
13. capacity/eviction.

### 9.2 Still Useful Later

1. class diagrams,
2. package diagrams,
3. candidate header dependency diagrams,
4. test coverage matrix diagrams,
5. read-side profile diagrams.

---

## 10. Implementation Wave Recommendation

### 10.1 Wave 01 — Foundational Types

```text
TContainerRegistryIndex
TContainerId
TSlotIndex
TSlotState
TContainerState
TRoundState
```

### 10.2 Wave 02 — Container / Registry Skeleton

```text
TSlot
TContainer
TContainerRegistry
views/reports minimal
```

### 10.3 Wave 03 — Bundle / Moderator

```text
BundleAgent
Moderator
default empty profile
uniform capacity profile
```

### 10.4 Wave 04 — Waiting Lists / RoundManager

```text
TIngressWaitingList
TDispatchWaitingList
RoundManager
```

### 10.5 Wave 05 — Reference Precalculator

```text
TIngressAccessRef
TDispatchAccessRef
ReferencePrecalculator
validity reports
```

### 10.6 Wave 06 — Ingress / Dispatcher / Boundary

```text
Ingress
Dispatcher
passive pull exposure
boundary reports
```

### 10.7 Wave 07 — Diagnostics / Capacity / Eviction

```text
diagnostics
capacity profiles
eviction policies
production readiness checks
```

---

## 11. Readiness Verdict

| Area | Verdict |
|---|---|
| Architecture identity | ready |
| Core component taxonomy | ready |
| Movement cycles | ready |
| Reference model | ready |
| State/safe-point/recycle | ready |
| Boundary separation | ready_with_notes |
| Diagnostics/views/reports | ready |
| Capacity/eviction | ready_with_notes |
| Header derivation | ready_for_candidate_inventory |
| Implementation | not started |

## 12. Final Gate Statement

```text
CME architecture is ready for candidate header inventory derivation.

It is not yet an instruction to implement all candidates.

Implementation must begin with foundational types and compile-only skeletons,
then progress through state, registry, container, waiting-list, reference,
ingress, dispatcher, diagnostics, and profile waves.
```
