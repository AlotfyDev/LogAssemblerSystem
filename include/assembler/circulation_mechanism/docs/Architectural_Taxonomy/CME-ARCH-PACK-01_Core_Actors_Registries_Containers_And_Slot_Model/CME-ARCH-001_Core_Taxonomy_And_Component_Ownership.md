# CME-ARCH-001 — Core Taxonomy And Component Ownership

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-001-DOC-001 | Document Title | Core Taxonomy And Component Ownership |
| CME-ARCH-001-DOC-002 | File Name | `CME-ARCH-001_Core_Taxonomy_And_Component_Ownership.md` |
| CME-ARCH-001-DOC-003 | Architecture Pack | `CME-ARCH-PACK-01` |
| CME-ARCH-001-DOC-004 | Domain | `circulation_mechanism` |
| CME-ARCH-001-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-001-DOC-006 | Primary Scope | Core actors, registries, containers, slots, waiting lists, round manager, reference precalculator, ingress, dispatcher |
| CME-ARCH-001-DOC-007 | Implementation Direction | C++17, header-only-first, static-first, template/profile-driven |
| CME-ARCH-001-DOC-008 | Depends On | `CME-ARCH-000_Holistic_Foundation_And_System_View.md` |
| CME-ARCH-001-DOC-009 | Enables | Component specs, state specs, reference model, header candidate map |
| CME-ARCH-001-DOC-010 | Primary Rule | Every core element must declare ownership, non-ownership, state, dependencies, views, reports, safe points, and configuration profiles before implementation |
| CME-ARCH-001-DOC-011 | Non-Purpose | Final C++ classes, final headers, final algorithms, bridge runtime, read-side receiver behavior |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the core architectural taxonomy of the Circulation Mechanism Engine.

It answers:

```text
Which core actors, registries, data-structure containers, access structures,
waiting lists, round coordinators, reference calculators, boundary actors,
views, reports, states, and profiles exist in the engine, and what does each
one own or explicitly not own?
```

### 2.2 Why This Document Exists

The engine has multiple moving parts. Without a formal taxonomy, several invalid collapses become likely:

1. treating `TContainer` as a message broker,
2. treating `TSlot` as the envelope lifecycle owner,
3. treating `WaitingList` as an envelope queue,
4. treating `RoundManager` as `Dispatcher`,
5. treating `ReferencePrecalculator` as the accessor,
6. treating `Dispatcher` as bridge or final receiver,
7. treating reports as proof of downstream delivery,
8. treating views as mutable access.

This document prevents those collapses.

### 2.3 Core Distinction

```text
Actor = responsibility-carrying coordinator.
Registry = indexed ownership/access backbone.
Data structure = residency or placement structure.
State = behavioral consequence model.
Reference = scoped access artifact.
View = read-only projection.
Report = action/transition/diagnostic evidence.
Profile = configuration-time behavior constraint.
```

---

## 3. Core Taxonomy Overview

### 3.1 Core Actors

| Taxonomy ID | Actor | Primary Role |
|---:|---|---|
| CME-ACT-001 | `SlotsContainerBundleAgent` | Creates and manages the family/topology/capacity of `TContainer` instances |
| CME-ACT-002 | `SlotsContainerModerator` | Moderates one concrete `TContainer`, exposes readiness, and applies reset/reinitialization |
| CME-ACT-003 | `RoundManager` | Evaluates container readiness and registers eligible container indices into cycle waiting lists |
| CME-ACT-004 | `ReferencePrecalculator` | Computes access references ahead of access from registry indices, container state, slot state, and round context |
| CME-ACT-005 | `Ingress` | Consumes ingress access refs to move envelope payloads into the engine |
| CME-ACT-006 | `Dispatcher` | Consumes dispatch access refs to expose envelope payloads out of the engine toward the bridge-facing side |

### 3.2 Registries And Locators

| Taxonomy ID | Element | Primary Role |
|---:|---|---|
| CME-REG-001 | `TContainerRegistry` | Stores all active `TContainer` instances in an indexed registry |
| CME-REF-002 | `TContainerRegistryIndex` | Lightweight locator used in waiting lists and reference precalculation |
| CME-REF-001 | `TContainerId` | Logical identity for a container |
| CME-REF-003 | `TContainerRef` | Optional resolved reference/view abstraction around registry index and registry access |

### 3.3 Data Structures

| Taxonomy ID | Element | Primary Role |
|---:|---|---|
| CME-DS-001 | `TContainer` | Uniform-capacity data-structure container that owns a slot layout |
| CME-DS-002 | `TSlot` | Bounded placement/access structure inside a `TContainer` |
| CME-DS-003 | `TContainerBundle` | Grouping/topology of active containers |
| CME-DS-004 | `TDefaultEmptyContainer` | Canonical empty container profile used for reset/reinitialization |
| CME-DS-005 | `TIngressWaitingList` | FIFO eligibility list of container indices for ingress/container-providing cycles |
| CME-DS-006 | `TDispatchWaitingList` | FIFO/time-range-aware eligibility list of container indices for dispatch cycles |
| CME-DS-007 | `TRound` | Round context, membership, and lifecycle |
| CME-DS-010 | `TContainerTimeRange` | Container-level time-range metadata used for dispatch ordering and eviction |
| CME-DS-012 | `TPayloadEnvelope` | Opaque envelope payload unit from the engine perspective |

### 3.4 State Models

| Taxonomy ID | State | Primary Role |
|---:|---|---|
| CME-ST-001 | `TSlotState` | Slot-local access/occupancy state |
| CME-ST-002 | `TContainerState` | Container-level operational/cycle eligibility state |
| CME-ST-003 | `TRoundState` | Round lifecycle and membership state |
| CME-ST-004 | `TModeratorState` | Moderator-local reset/readiness state |
| CME-ST-005 | `TBundleAgentState` | Topology/scaling/profile-switch state |
| CME-ST-006 | `TReferenceSupplyState` | Prepared reference supply state |
| CME-ST-007 | `TDispatchExposureState` | Dispatch/output exposure state |
| CME-ST-008 | `TAccessReferenceValidity` | Prepared access reference validity state |

---

## 4. Component Specification Template

Each core element follows this template:

```text
1. Definition
2. Category
3. Ownership Scope
4. Responsibilities
5. Non-Responsibilities
6. Identity
7. State
8. Inputs
9. Outputs
10. Dependencies
11. Views
12. Reports
13. Safe Points
14. Configuration Profiles
15. Invariants
16. Failure / Diagnostics
17. Implementation Notes
18. Deferred Decisions
```

---

## 5. CME-ACT-001 — SlotsContainerBundleAgent

### 5.1 Definition

`SlotsContainerBundleAgent` is the runtime coordination actor responsible for creating and governing the family of `TContainer` instances used by the Circulation Mechanism Engine.

### 5.2 Category

```text
actor
runtime_coordinator
topology_authority
capacity_profile_owner
```

### 5.3 Responsibilities

| ID | Responsibility |
|---:|---|
| CME-ACT-001-RESP-001 | Creates or declares the active `TContainer` family |
| CME-ACT-001-RESP-002 | Owns horizontal scaling: number of containers |
| CME-ACT-001-RESP-003 | Owns vertical scaling: uniform slot capacity per container |
| CME-ACT-001-RESP-004 | Provides the active `TDefaultEmptyContainer` profile |
| CME-ACT-001-RESP-005 | Maintains the invariant that all active containers share uniform capacity/layout |
| CME-ACT-001-RESP-006 | Produces scaling and capacity reports |
| CME-ACT-001-RESP-007 | Participates in safe-point-gated capacity/profile switching |

### 5.4 Non-Responsibilities

| ID | Non-Responsibility |
|---:|---|
| CME-ACT-001-NON-001 | Does not moderate a concrete container instance |
| CME-ACT-001-NON-002 | Does not apply reset to a container |
| CME-ACT-001-NON-003 | Does not decide round membership |
| CME-ACT-001-NON-004 | Does not calculate slot access references |
| CME-ACT-001-NON-005 | Does not inspect envelope payload content |
| CME-ACT-001-NON-006 | Does not own bridge or receiver behavior |

### 5.5 Identity

| Field | Value |
|---|---|
| Identity Required | Yes |
| Candidate Identity | `TBundleAgentId` or engine-profile-bound identity |
| Visibility | Internal and diagnostics |
| Stability | Stable for one engine instance |

### 5.6 State

| State | Meaning |
|---|---|
| `stable` | Current container family profile is active |
| `horizontal_scaling_pending` | A container-count change is planned |
| `vertical_scaling_pending` | A uniform capacity change is planned |
| `waiting_for_safe_point` | Scaling/profile change is waiting for safe point |
| `profile_switch_ready` | Safe point is available and profile switch can proceed |
| `profile_switch_applied` | New profile was applied |
| `invariant_violation` | Capacity/topology invariant is broken |

### 5.7 Inputs

| Input | Source |
|---|---|
| `TCirculationCapacityProfile` | engine configuration |
| `TUniformContainerCapacityProfile` | engine configuration |
| `THorizontalScalingProfile` | engine configuration |
| `TVerticalScalingProfile` | engine configuration |
| safe-point reports | Moderator / RoundManager / ReferencePrecalculator |

### 5.8 Outputs

| Output | Consumer |
|---|---|
| `TContainerBundle` | `TContainerRegistry` |
| `TDefaultEmptyContainer` | `SlotsContainerModerator` |
| `TBundleTopologyView` | diagnostics and planning |
| `TBundleScalingReport` | diagnostics |
| `TCapacityProfileSwitchReport` | diagnostics / implementation readiness |

### 5.9 Dependencies

| Depends On | Dependency Type |
|---|---|
| capacity profiles | configuration-time |
| safe-point reports | runtime-light |
| active registry state | view/report only |

### 5.10 Views

```text
TBundleTopologyView
TUniformCapacityProfileView
TContainerFamilyView
TBundleAgentView
```

### 5.11 Reports

```text
TBundleScalingReport
TDefaultEmptyContainerProfileReport
TCapacityProfileSwitchReport
TBundleInvariantReport
```

### 5.12 Safe Points

Scaling and profile changes require:

```text
all_containers_out_of_active_rounds
refs_invalidated_or_consumed
container_reset_safe
profile_switch_safe
```

### 5.13 Configuration Profiles

```text
TCirculationCapacityProfile
TUniformContainerCapacityProfile
THorizontalScalingProfile
TVerticalScalingProfile
TExtremeDefaultProfile
```

### 5.14 Invariants

```text
All active containers share uniform capacity.
All active containers share compatible slot layout.
Default empty container matches the active family profile.
Move semantics remain structurally safe because container shapes are identical.
Vertical scaling applies to the family, never to one container instance.
```

---

## 6. CME-ACT-002 — SlotsContainerModerator

### 6.1 Definition

`SlotsContainerModerator` is the per-container runtime actor responsible for moderating one concrete `TContainer`, exposing its readiness/state view, and applying reset/reinitialization using the active `TDefaultEmptyContainer`.

### 6.2 Category

```text
actor
per_container_coordinator
readiness_authority
reset_executor
```

### 6.3 Responsibilities

| ID | Responsibility |
|---:|---|
| CME-ACT-002-RESP-001 | Maintains or exposes the operational reference/view for its container |
| CME-ACT-002-RESP-002 | Exposes container state and readiness |
| CME-ACT-002-RESP-003 | Applies reset from `TDefaultEmptyContainer` |
| CME-ACT-002-RESP-004 | Confirms safe points for reset/reinitialization |
| CME-ACT-002-RESP-005 | Produces moderation, readiness, and reset reports |

### 6.4 Non-Responsibilities

| ID | Non-Responsibility |
|---:|---|
| CME-ACT-002-NON-001 | Does not create the container family |
| CME-ACT-002-NON-002 | Does not choose uniform capacity |
| CME-ACT-002-NON-003 | Does not register containers into waiting lists |
| CME-ACT-002-NON-004 | Does not calculate access references |
| CME-ACT-002-NON-005 | Does not own payload semantics |
| CME-ACT-002-NON-006 | Does not own bridge behavior |

### 6.5 Identity

| Field | Value |
|---|---|
| Identity Required | Yes |
| Candidate Identity | `TModeratorId`, `TContainerRegistryIndex` association |
| Visibility | Internal / diagnostic reports |
| Stability | Stable while assigned to a container |

### 6.6 State

| State | Meaning |
|---|---|
| `idle` | No active moderation action |
| `observing` | Reading container state/readiness |
| `preparing` | Preparing container for a cycle |
| `resetting` | Applying default empty container |
| `ready_exposed` | Container readiness has been exposed |
| `safe_point_confirmed` | Safe point confirmed |
| `moderation_blocked` | Guard prevented moderation |
| `invariant_violation` | Detected invalid state/profile combination |

### 6.7 Inputs

| Input | Source |
|---|---|
| `TContainerRegistryIndex` | Registry / assignment |
| `TContainerState` | Container |
| `TDefaultEmptyContainer` | BundleAgent |
| safe-point flag | Container/Round/Reference state |
| active capacity profile | BundleAgent view |

### 6.8 Outputs

```text
TModeratorReadinessView
TContainerStateView
TContainerResetReport
TModerationReport
TSafePointConfirmationReport
```

### 6.9 Invariants

```text
Moderator applies reset only at a safe point.
Moderator does not alter the uniform capacity profile.
Moderator does not register containers into waiting lists.
Moderator exposes readiness; RoundManager consumes that readiness.
```

---

## 7. CME-REG-001 — TContainerRegistry

### 7.1 Definition

`TContainerRegistry` is the engine-owned indexed storage and locator backbone for all active `TContainer` instances.

### 7.2 Category

```text
registry
indexed_storage_owner
container_locator_backbone
```

### 7.3 Responsibilities

| ID | Responsibility |
|---:|---|
| CME-REG-001-RESP-001 | Stores active `TContainer` instances |
| CME-REG-001-RESP-002 | Provides stable `TContainerRegistryIndex` values under an active profile |
| CME-REG-001-RESP-003 | Enables memory-local indexed access |
| CME-REG-001-RESP-004 | Supports registry views for diagnostics |
| CME-REG-001-RESP-005 | Supports profile switch and registry rebuild at safe points |

### 7.4 Non-Responsibilities

```text
Does not decide container eligibility.
Does not compute slot access references.
Does not own round membership.
Does not inspect envelopes.
Does not act as downstream registry.
```

### 7.5 Identity

| Field | Value |
|---|---|
| Identity Required | Optional registry id; required index type |
| Main Locator | `TContainerRegistryIndex` |
| Logical Identity | `TContainerId` |
| Optional Reference | `TContainerRef` |

### 7.6 State

```text
empty
initialized
active
resizing_pending
locked_for_profile_switch
invariant_violation
```

### 7.7 Inputs / Outputs

| Direction | Values |
|---|---|
| Inputs | container family from BundleAgent, reset updates from Moderator |
| Outputs | registry indices, registry view, container access view, invariant reports |

### 7.8 Invariants

```text
No active container exists outside the registry.
Every waiting-list index must resolve to a valid registry entry.
Every active container matches the active uniform capacity profile.
Registry rebuild requires safe point.
Registry index is not a public external reference.
```

---

## 8. CME-DS-001 — TContainer

### 8.1 Definition

`TContainer` is the circulation-owned data-structure container that provides a uniform slot layout for envelope residency and participates as a whole in ingress, dispatch, reset, waiting-list, and round-management cycles.

### 8.2 Category

```text
data_structure_container
runtime_residency_structure
cycle_participant
```

### 8.3 Responsibilities

```text
Owns slot layout.
Owns container-level state.
Hosts slots.
Carries time-range metadata where configured.
Participates in ingress and dispatch rounds.
Becomes reset/recycle candidate after dispatch cycle completion.
```

### 8.4 Non-Responsibilities

```text
Does not assemble envelopes.
Does not parse payload.
Does not own bridge.
Does not own final receiver lifecycle.
Does not act as message broker.
Does not own envelope lifecycle after dispatch exposure.
```

### 8.5 Identity

```text
TContainerId
TContainerRegistryIndex
optional TContainerRef
```

### 8.6 State

```text
default_empty
ingress_ready
ingress_round_member
receiving
filled_or_closed
dispatch_candidate
dispatch_round_member
dispatch_exposed
dispatch_completed
reset_pending
under_moderation
inactive
evicted
```

### 8.7 Invariants

```text
TContainerState is not mechanically derived from TSlotState.
Uniform capacity is required.
Slot layout compatibility is required.
Reset returns the container to default_empty profile.
Time-range metadata is ordering data, not timestamp semantic interpretation.
```

---

## 9. CME-DS-002 — TSlot

### 9.1 Definition

`TSlot` is a bounded placement/access structure inside `TContainer`, into which a prepared envelope payload may be admitted and from which it may later be exposed for dispatch.

### 9.2 Category

```text
placement_structure
access_structure
state_bearing_residency_cell
```

### 9.3 Responsibilities

```text
Provides local placement.
Tracks slot-level access/occupancy state.
Participates in ingress and dispatch access.
Supports occupancy views and transition reports.
```

### 9.4 Non-Responsibilities

```text
Does not own the envelope lifecycle.
Does not decide container eligibility.
Does not dispatch itself.
Does not know bridge.
Does not parse or inspect envelope payload.
```

### 9.5 Identity

```text
TSlotIndex
TContainerRegistryIndex + TSlotIndex
TSlotAccessRef
```

### 9.6 State

```text
empty
reserved_for_ingress
occupied
sealed
dispatch_ready
dispatch_exposed
released
recyclable
faulted
```

### 9.7 Invariants

```text
Slot belongs to exactly one container.
Slot access requires a valid access reference.
Slot state and container state are distinct.
Occupancy is placement relation, not envelope lifecycle ownership.
```

---

## 10. CME-DS-005 — TIngressWaitingList

### 10.1 Definition

`TIngressWaitingList` is an active ordered eligibility list of `TContainerRegistryIndex` values for containers that may participate in ingress/container-providing rounds.

### 10.2 Responsibilities

```text
Stores eligible container indices.
Preserves FIFO ingress ordering by default.
Provides candidate stream to ReferencePrecalculator.
Supports registration and invariant reports.
```

### 10.3 Non-Responsibilities

```text
Does not store envelopes.
Does not store container objects.
Does not select slots.
Does not calculate access references.
```

### 10.4 State

```text
empty
accepting_candidates
ready_for_round
locked_by_round
draining_to_precalculator
cleared
invariant_violation
```

### 10.5 Invariants

```text
Only ingress-eligible container indices may enter the list.
The list is round-scoped.
The list is not an envelope store.
```

---

## 11. CME-DS-006 — TDispatchWaitingList

### 11.1 Definition

`TDispatchWaitingList` is an active ordered eligibility list of `TContainerRegistryIndex` values for containers that may participate in dispatch rounds.

### 11.2 Responsibilities

```text
Stores dispatch-eligible container indices.
Preserves FIFO ordering by default.
May use container time range for ordering/eviction.
Provides candidate stream to ReferencePrecalculator.
```

### 11.3 Non-Responsibilities

```text
Does not perform dispatch.
Does not own bridge.
Does not own copy/move semantics.
Does not prove downstream delivery.
```

### 11.4 State

```text
empty
accepting_dispatch_candidates
ready_for_dispatch_round
locked_by_round
draining_to_precalculator
eviction_candidate_selection
cleared
invariant_violation
```

### 11.5 Invariants

```text
Only dispatch-eligible container indices may enter.
Time range ordering is metadata-based, not timestamp semantic interpretation.
Presence in list does not mean bridge has consumed.
```

---

## 12. CME-ACT-003 — RoundManager

### 12.1 Definition

`RoundManager` is the runtime coordination actor responsible for opening, managing, locking, closing, and completing ingress and dispatch rounds, and for registering eligible container indices into the appropriate waiting list.

### 12.2 Responsibilities

```text
Evaluates container readiness.
Controls round membership.
Adds eligible indices to ingress or dispatch waiting lists.
Maintains round state.
Produces round admission and closure reports.
```

### 12.3 Non-Responsibilities

```text
Does not create containers.
Does not reset containers.
Does not calculate access refs.
Does not perform final dispatch.
```

### 12.4 State

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

### 12.5 Invariants

```text
No registration into closed round.
No ineligible container enters a round.
Round state is independent from container state.
Ingress round and dispatch round are distinct profiles.
```

---

## 13. CME-ACT-004 — ReferencePrecalculator

### 13.1 Definition

`ReferencePrecalculator` is the engine-owned coordinator responsible for continuously preparing ingress-side and dispatch-side access references from registry indices, container state/data, slot state/layout, waiting-list ordering, and round context.

### 13.2 Responsibilities

```text
Separates locating from accessing.
Consumes waiting-list candidate indices.
Reads registry-backed container/slot data through approved views/access.
Produces ingress access refs.
Produces dispatch access refs.
Maintains continuous next-ref supply.
```

### 13.3 Non-Responsibilities

```text
Does not access payload itself.
Does not own payload.
Does not decide copy/move.
Does not know bridge protocol.
Does not determine container readiness.
```

### 13.4 State

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

### 13.5 Invariants

```text
No access without valid reference.
Ingress refs are not dispatch refs.
Dispatch refs are not ingress refs.
Every ref is scoped to round/state/safe point.
```

---

## 14. CME-ACT-005 — Ingress

### 14.1 Definition

`Ingress` is the intake-side actor or execution surface that consumes a prepared ingress access reference and places a prepared envelope payload into the engine.

### 14.2 Responsibilities

```text
Consumes TIngressAccessRef.
Admits envelope into the targeted slot.
Produces placement report.
Triggers slot/container state transition through approved access.
```

### 14.3 Non-Responsibilities

```text
Does not create envelope.
Does not parse content.
Does not calculate location.
Does not know container topology.
Does not dispatch.
```

### 14.4 State

```text
ready
awaiting_ref
placing
placed
blocked_by_invariant
closed
```

### 14.5 Invariants

```text
Ingress moves payload outside → engine.
Ingress uses valid ingress refs only.
Ingress does not perform locating.
Single producer-facing profile applies in pre-bridge engine.
```

---

## 15. CME-ACT-006 — Dispatcher

### 15.1 Definition

`Dispatcher` is the final pre-bridge output actor of the circulation engine, responsible for exposing dispatch-ready payload residency through prepared dispatch references or output exposure surfaces.

### 15.2 Responsibilities

```text
Consumes TDispatchAccessRef.
Exposes dispatch-ready payload/container/slot access.
Supports passive pull dispatch by default.
Produces dispatch exposure reports.
Participates in release/recycle state transitions.
```

### 15.3 Non-Responsibilities

```text
Does not own bridge protocol.
Does not own final receiver.
Does not prove downstream delivery.
Does not decide bridge copy/move semantics.
Does not own read-side delay/retry behavior.
```

### 15.4 State

```text
ready
awaiting_dispatch_ref
exposing
passive_exposed
bridge_consumed
release_pending
closed
boundary_assumption_broken
```

### 15.5 Invariants

```text
Dispatcher is the final pre-bridge actor.
Passive pull is default.
Push is optional profile only.
Dispatch exposure is not downstream acceptance.
```

---

## 16. Cross-Component Ownership Matrix

| Element | Owns | Does Not Own |
|---|---|---|
| BundleAgent | topology, capacity profile, default empty profile | per-container reset, refs, payload |
| Moderator | container readiness, reset execution | topology, round membership |
| Registry | container indexed storage | eligibility, refs |
| TContainer | slots, container state, residency | broker behavior, bridge |
| TSlot | placement/access state | envelope lifecycle |
| IngressWaitingList | ingress-eligible indices | envelopes |
| DispatchWaitingList | dispatch-eligible indices | bridge/final delivery |
| RoundManager | round membership/state | refs/dispatch |
| ReferencePrecalculator | locating/ref calculation | access execution |
| Ingress | placement via ref | envelope production |
| Dispatcher | output exposure | bridge/final receiver |

---

## 17. Diagram Reference

```text
diagrams/CME-ARCH-001_taxonomy_tree.mmd
```

---

## 18. Deferred Decisions

| ID | Decision | Reason |
|---:|---|---|
| CME-ARCH-001-DEF-001 | Final C++ type names | Derive after all architecture packs |
| CME-ARCH-001-DEF-002 | Whether `TContainerRef` is materialized | May remain optional if registry index is enough |
| CME-ARCH-001-DEF-003 | Whether waiting list is one template or two concrete types | Needs implementation derivation |
| CME-ARCH-001-DEF-004 | Whether ingress is actor or hosted port surface | Needs boundary model pack |
