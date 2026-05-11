# CME-ARCH-003 — Slot, Container State, And Residency Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-003-DOC-001 | Document Title | Slot, Container State, And Residency Model |
| CME-ARCH-003-DOC-002 | File Name | `CME-ARCH-003_Slot_Container_State_And_Residency_Model.md` |
| CME-ARCH-003-DOC-003 | Architecture Pack | `CME-ARCH-PACK-01` |
| CME-ARCH-003-DOC-004 | Domain | `circulation_mechanism` |
| CME-ARCH-003-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-003-DOC-006 | Primary Scope | `TContainer`, `TSlot`, container state, slot state, residency, occupancy, reset, time range, eviction metadata |
| CME-ARCH-003-DOC-007 | Depends On | `CME-ARCH-001`, `CME-ARCH-002` |
| CME-ARCH-003-DOC-008 | Enables | State machines, release/recycle, reference validity, dispatch ordering, eviction |
| CME-ARCH-003-DOC-009 | Primary Rule | Container state and slot state are separate state models with different authority and consequences |
| CME-ARCH-003-DOC-010 | Non-Purpose | Final class design, final memory layout, final payload envelope structure, bridge copy/move contract |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the residency model for envelope payloads inside the Circulation Mechanism Engine.

It answers:

```text
What is TContainer?
What is TSlot?
How does envelope residency occur?
How are container state and slot state different?
What is slot occupancy?
How is reset handled?
How does container time range support dispatch ordering and eviction?
```

### 2.2 Core Thesis

```text
TContainer is the circulation-owned residency structure.

TSlot is the bounded placement/access structure inside TContainer.

TContainerState governs cycle eligibility.

TSlotState governs local access/occupancy.

Occupancy is a placement relation, not envelope lifecycle ownership.
```

---

## 3. TContainer Model

### 3.1 Definition

`TContainer` is the circulation-owned data-structure container that hosts a uniform layout of slots and participates as a whole in the engine’s ingress, dispatch, reset, waiting-list, and round-management cycles.

### 3.2 Category

```text
data_structure_container
runtime_residency_structure
cycle_participant
state_bearing_structure
```

### 3.3 Responsibilities

| ID | Responsibility |
|---:|---|
| CME-ARCH-003-CONT-RESP-001 | Owns a fixed/uniform slot layout |
| CME-ARCH-003-CONT-RESP-002 | Owns container-level state |
| CME-ARCH-003-CONT-RESP-003 | Hosts payload envelopes inside slots |
| CME-ARCH-003-CONT-RESP-004 | Participates in ingress rounds |
| CME-ARCH-003-CONT-RESP-005 | Participates in dispatch rounds |
| CME-ARCH-003-CONT-RESP-006 | Carries optional time-range metadata |
| CME-ARCH-003-CONT-RESP-007 | Becomes reset/recycle candidate after dispatch completion |

### 3.4 Non-Responsibilities

```text
TContainer is not a message broker.
TContainer is not a bridge.
TContainer is not a final receiver.
TContainer does not parse payload.
TContainer does not assemble envelopes.
TContainer does not perform final dispatch.
TContainer does not own downstream lifecycle.
```

---

## 4. TContainer Identity

### 4.1 Identity Components

```text
TContainerId
TContainerRegistryIndex
optional TContainerRef
```

### 4.2 Identity Rules

```text
TContainerId is logical.
TContainerRegistryIndex is registry-local locator.
TContainerRef is optional and must not expose internals.
```

---

## 5. TContainerState Model

### 5.1 Candidate States

| State | Meaning |
|---|---|
| `default_empty` | Clean reset state matching the active default empty profile |
| `ingress_ready` | Ready to be considered for ingress/container-providing |
| `ingress_round_member` | Registered in an ingress round |
| `receiving` | Accepting envelope placement |
| `filled_or_closed` | No longer accepting ingress for this cycle |
| `dispatch_candidate` | Eligible to be considered for dispatch |
| `dispatch_round_member` | Registered in dispatch round |
| `dispatch_exposed` | Being exposed through dispatcher/output boundary |
| `dispatch_completed` | Dispatch exposure cycle completed internally |
| `reset_pending` | Ready for reset/recycle |
| `under_moderation` | Moderator is applying reset/readiness transition |
| `inactive` | Not part of active circulation |
| `evicted` | Removed by eviction policy |

### 5.2 Container State Authority

| Transition Area | Authority |
|---|---|
| default empty → ingress ready | Moderator |
| ingress ready → ingress round member | RoundManager |
| receiving → filled/closed | Ingress / Container policy |
| dispatch candidate → dispatch round member | RoundManager |
| dispatch round member → dispatch exposed | Dispatcher |
| dispatch completed → reset pending | Dispatcher / Round closure |
| reset pending → default empty | Moderator |
| active → evicted | Eviction policy + safe point |

### 5.3 Container State Invariants

```text
Container state is not mechanically derived from slot state.
Container state may consider slot states but includes cycle/round/readiness facts.
Container state determines waiting-list eligibility.
Container state determines safe-point eligibility.
Container state determines whether references may be prepared.
```

---

## 6. TSlot Model

### 6.1 Definition

`TSlot` is a bounded placement/access structure inside a `TContainer`.

It is the local residency position for one payload envelope unit.

### 6.2 Category

```text
placement_structure
access_structure
state_bearing_cell
residency_position
```

### 6.3 Responsibilities

```text
Provides bounded placement position.
Tracks slot-level state.
Represents occupancy relation.
Supports ingress access.
Supports dispatch access.
Participates in release/recycle via state transitions.
```

### 6.4 Non-Responsibilities

```text
TSlot is not the envelope.
TSlot does not own the envelope lifecycle.
TSlot does not decide container eligibility.
TSlot does not dispatch itself.
TSlot does not know final receiver.
TSlot does not parse payload.
```

---

## 7. TSlot Identity

### 7.1 Identity Components

```text
TSlotIndex
TContainerRegistryIndex + TSlotIndex
TSlotAccessRef
```

### 7.2 Identity Rules

```text
TSlotIndex is local to a container.
TSlotAccessRef is scoped and validity-bound.
External consumers do not manually compute slot index.
```

---

## 8. TSlotState Model

### 8.1 Candidate States

| State | Meaning |
|---|---|
| `empty` | Slot contains no active envelope |
| `reserved_for_ingress` | Slot reserved by prepared ingress ref |
| `occupied` | Envelope payload is placed |
| `sealed` | Slot is no longer accepting writes |
| `dispatch_ready` | Slot may be exposed for dispatch |
| `dispatch_exposed` | Slot is under dispatch exposure |
| `released` | Payload residency has ended internally |
| `recyclable` | Slot may be reset to empty |
| `faulted` | Slot state invariant failed |

### 8.2 Slot Transition Authority

| Transition Area | Authority |
|---|---|
| empty → reserved | ReferencePrecalculator / Ingress reservation policy |
| reserved → occupied | Ingress |
| occupied → sealed | Container/round policy |
| sealed → dispatch_ready | Dispatch eligibility policy |
| dispatch_ready → dispatch_exposed | Dispatcher |
| dispatch_exposed → released | Dispatch exposure completion |
| released → recyclable → empty | Reset/recycle policy |

### 8.3 Slot State Invariants

```text
Slot belongs to exactly one container.
Slot access requires a valid access reference.
Slot state is not a substitute for container state.
Slot occupancy is placement relation.
Slot release does not imply downstream delivery.
```

---

## 9. Occupancy Relation

### 9.1 Definition

Occupancy is the relation:

```text
PayloadEnvelope
    occupies:
        TSlot
            inside:
                TContainer
                    indexed by:
                        TContainerRegistryIndex
```

### 9.2 Occupancy Is Not Ownership

Occupancy does not mean:

1. the slot owns the semantic lifecycle of the envelope,
2. the container owns downstream record lifecycle,
3. the envelope has been dispatched,
4. the bridge has consumed it,
5. the final receiver has accepted it.

### 9.3 Occupancy Evidence

Possible future artifacts:

```text
TSlotOccupancyView
TSlotOccupancyReport
TSlotOccupancyTransition
```

---

## 10. Residency Model

### 10.1 Residency Definition

Residency is the engine-local condition that a payload envelope is placed inside a slot of a container and is governed by slot/container state until it is exposed and released.

### 10.2 Residency Phases

```text
admitted
placed
sealed
dispatch_ready
exposed
released
recycled
```

### 10.3 Residency Non-Meaning

Residency is not:

```text
downstream persistence
bridge acceptance
final receiver ownership
query availability
message broker durability
```

---

## 11. Container Time Range

### 11.1 Definition

`TContainerTimeRange` is optional container-level metadata describing the range of envelope timestamps contained in the container.

### 11.2 Purpose

It supports:

1. dispatch ordering,
2. oldest-container eviction,
3. diagnostics,
4. report readability,
5. bounded timeline reasoning.

### 11.3 Non-Purpose

It does not interpret timestamp semantics.

The Log-Level API stabilizes timestamps before envelope production.

The circulation engine only consumes time range as ordering metadata when configured.

### 11.4 Candidate Fields

```text
first_timestamp
last_timestamp
timestamp_basis
coverage_status
source_count
```

### 11.5 Invariants

```text
first_timestamp <= last_timestamp when complete.
time range may be incomplete while container is receiving.
time range must be sealed before dispatch-order use.
time range is not proof of downstream ordering.
```

---

## 12. Reset And Default Empty State

### 12.1 Reset Definition

Reset is the moderation action that returns a container to the active `TDefaultEmptyContainer` profile.

### 12.2 Reset Owner

`SlotsContainerModerator`.

### 12.3 Reset Source

`TDefaultEmptyContainer`, supplied by `SlotsContainerBundleAgent`.

### 12.4 Reset Preconditions

```text
container is not in active ingress round
container is not in active dispatch round
no active access refs
dispatch exposure is closed or consumed
safe point available
default empty profile matches active container profile
```

### 12.5 Reset Result

```text
all slots empty
container state default_empty
time range cleared
references invalidated
waiting-list membership cleared
```

---

## 13. Eviction Metadata

### 13.1 Purpose

Eviction metadata supports selection of a container to evict when configured limits require it.

### 13.2 Candidate Inputs

```text
TContainerRegistryIndex
TContainerTimeRange
TContainerState
TRoundState
TDispatchExposureState
TReferenceValidity
```

### 13.3 Eviction Eligibility

A container may be an eviction candidate only if:

```text
not active in ingress
not active in dispatch
not exposed
refs are consumed or invalidated
safe point available
```

### 13.4 Eviction Non-Meaning

Eviction does not mean:

```text
downstream failure
semantic timestamp interpretation
message-drop semantics by default
receiver rejection
```

---

## 14. Views

```text
TContainerView
TContainerStateView
TContainerSlotLayoutView
TContainerTimeRangeView
TContainerDispatchReadinessView
TSlotView
TSlotStateView
TSlotOccupancyView
TSlotAccessView
```

---

## 15. Reports

```text
TContainerStateTransitionReport
TContainerResetReport
TContainerEvictionReport
TContainerDispatchExposureReport
TSlotTransitionReport
TSlotOccupancyReport
TSlotReleaseReport
TSlotAccessViolationReport
```

---

## 16. Diagnostics

| Diagnostic | Meaning |
|---|---|
| `ContainerStateMismatch` | container state does not match round/waiting-list/ref context |
| `SlotLayoutMismatch` | container layout differs from family profile |
| `UnsafeContainerReset` | reset attempted outside safe point |
| `ContainerTimeRangeInvalid` | time range metadata inconsistent |
| `SlotAccessRefExpired` | access attempted after ref expiration |
| `SlotOccupiedOnIngress` | write attempted to occupied slot |
| `SlotNotDispatchReady` | dispatch attempted before readiness |
| `SlotStateMismatch` | slot state conflicts with requested access |

---

## 17. Implementation Notes

### 17.1 Header Derivation Candidate Areas

```text
container/
slot/
container_state/
slot_state/
occupancy/
container_time_range/
reset/
eviction_metadata/
views/
reports/
```

### 17.2 Static-First Direction

`TContainer` and `TSlot` should be derivable from capacity/profile types, not runtime-discovered shapes.

### 17.3 Boundary Protection

No external participant should receive mutable access to container or slot internals.

---

## 18. Deferred Decisions

| ID | Decision |
|---:|---|
| CME-ARCH-003-DEF-001 | Whether slot reservation is explicit or implicit inside ingress ref |
| CME-ARCH-003-DEF-002 | Exact slot state enum names |
| CME-ARCH-003-DEF-003 | Whether time range is mandatory for all containers |
| CME-ARCH-003-DEF-004 | Whether eviction is compiled out in pre-bridge profile |
| CME-ARCH-003-DEF-005 | Whether occupancy is a distinct type or state view |
