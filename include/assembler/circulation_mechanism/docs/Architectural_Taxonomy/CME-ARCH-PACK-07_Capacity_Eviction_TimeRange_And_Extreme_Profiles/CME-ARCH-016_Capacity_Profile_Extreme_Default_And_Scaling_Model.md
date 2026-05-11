# CME-ARCH-016 — Capacity Profile Extreme Default And Scaling Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-016-DOC-001 | Document Title | Capacity Profile Extreme Default And Scaling Model |
| CME-ARCH-016-DOC-002 | Package | CME-ARCH-PACK-07 |
| CME-ARCH-016-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-016-DOC-004 | Scope Level | Capacity profile, horizontal/vertical scaling, uniform capacity, default extreme provisioning |
| CME-ARCH-016-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-016-DOC-006 | Implementation Direction | C++17, header-only-first, profile-driven capacity, safe-point guarded scaling |
| CME-ARCH-016-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-015 |
| CME-ARCH-016-DOC-008 | Related Models | BundleAgent, TContainerRegistry, TContainer, TSlot, WaitingLists, ReferencePrecalculator, SafePoint |
| CME-ARCH-016-DOC-009 | Primary Rule | Capacity is configured and profiled before hot-path circulation; it is not discovered by consumers |
| CME-ARCH-016-DOC-010 | Excluded | Message broker backpressure, receiver delay, bridge retry, dynamic unbounded queueing |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the capacity and scaling model for the pre-bridge Circulation Mechanism Engine.

It answers:

```text
How does the engine guarantee continuous circulation under a single-producer,
single-dispatcher pre-bridge profile without converting capacity pressure into
message-broker backpressure behavior?
```

### 2.2 Core Thesis

```text
Capacity is a configured architectural envelope.
It is not a surprise detected by the hot path.
```

### 2.3 Architectural Role

The capacity model exists to ensure:

1. intake is pre-sized,
2. dispatch is pre-sized,
3. all active containers are layout-compatible,
4. move semantics are safe by construction,
5. scaling happens only through declared profiles and safe points,
6. consumers continue using `next` without learning topology.

---

## 3. Capacity Model Overview

### 3.1 Core Capacity Concepts

| Concept | Meaning |
|---|---|
| `TCirculationCapacityProfile` | Overall capacity envelope for engine instance |
| `TUniformContainerCapacityProfile` | Shared capacity/slot layout for all active containers |
| `THorizontalScalingProfile` | Number of active containers |
| `TVerticalScalingProfile` | Slots per container / uniform capacity dimension |
| `TExtremeDefaultProfile` | Default profile that adopts worst-case/extreme expected capacity |
| `TIngressCapacityProfile` | Intake-side capacity |
| `TDispatchCapacityProfile` | Dispatch-side capacity |
| `TWaitingListCapacityProfile` | Waiting-list capacity for each cycle |
| `TReferenceSupplyCapacityProfile` | Number of refs prepared ahead |

### 3.2 Capacity Ownership

| Capacity Concern | Owner |
|---|---|
| Overall capacity profile | Engine configuration / BundleAgent |
| Uniform container capacity | BundleAgent |
| Container count | BundleAgent |
| Concrete container registry storage | TContainerRegistry |
| Slot count/layout | TContainer / BundleAgent profile |
| Waiting-list capacity | WaitingList profile |
| Reference supply depth | ReferencePrecalculator profile |
| Dispatch exposure capacity | Dispatcher/output profile |

---

## 4. `TCirculationCapacityProfile`

### 4.1 Definition

`TCirculationCapacityProfile` is the governing capacity envelope for one pre-bridge circulation engine instance.

### 4.2 Fields

Candidate fields:

```text
profile_id
engine_instance_id
max_intake_units_per_cycle
max_dispatch_units_per_cycle
container_count
slots_per_container
ingress_waiting_list_capacity
dispatch_waiting_list_capacity
reference_supply_depth
default_extreme_mode
eviction_policy_profile
safe_point_scaling_policy
bridge_drain_assumption_profile
```

### 4.3 Responsibilities

1. Declare expected capacity.
2. Bind container count and slot capacity.
3. Bind waiting-list capacities.
4. Bind reference supply depth.
5. Provide limits for diagnostics.
6. Declare whether eviction is disabled/delegated/enabled.
7. Declare the pre-bridge drain assumption.

### 4.4 Non-Responsibilities

The capacity profile does not:

1. create containers directly,
2. execute scaling directly,
3. select eviction candidate directly,
4. perform reference calculation,
5. own bridge drain behavior,
6. own read-side receiver delay.

---

## 5. `TUniformContainerCapacityProfile`

### 5.1 Definition

`TUniformContainerCapacityProfile` defines the common slot count, slot layout, and capacity shape shared by every active `TContainer` in the active bundle.

### 5.2 Uniformity Rule

```text
Every active TContainer in the bundle must match the active uniform container capacity profile.
```

### 5.3 Why Uniformity Matters

Uniformity enables:

1. move semantics by construction,
2. predictable reference calculation,
3. safe default empty container reuse,
4. simpler registry indexing,
5. simpler diagnostics,
6. safe horizontal scaling,
7. safe profile switching at declared safe points.

### 5.4 Uniformity Invariants

```text
1. No active container may have a different slot count.
2. No active container may have a different slot layout.
3. Default empty container must match the active uniform profile.
4. Vertical scaling changes the whole family profile.
5. ReferencePrecalculator may assume profile compatibility within active generation.
```

---

## 6. Horizontal Scaling

### 6.1 Definition

Horizontal scaling changes the number of active `TContainer` instances in the registry/bundle.

### 6.2 Owner

`SlotsContainerBundleAgent`

### 6.3 Effects

1. Add containers.
2. Remove inactive containers.
3. Update container registry.
4. Update waiting-list profile if needed.
5. Update capacity reports.
6. Possibly update reference supply strategy.

### 6.4 Safe-Point Requirements

Adding new empty containers may be less restrictive than removing active ones, but all topology-affecting changes must preserve registry and reference validity.

### 6.5 Horizontal Scaling Invariants

```text
1. Added containers must match active uniform capacity profile.
2. Removed containers must not be active in a round.
3. Removed containers must not have active references.
4. Waiting lists must not retain stale indices.
5. Registry view/report must reflect topology change.
```

---

## 7. Vertical Scaling

### 7.1 Definition

Vertical scaling changes the uniform capacity of all active containers.

### 7.2 Owner

`SlotsContainerBundleAgent`

### 7.3 Executor

`SlotsContainerModerator` applies reset/reinitialization for concrete containers at safe points.

### 7.4 Effects

1. New uniform capacity profile.
2. New default empty container profile.
3. Registry/profile generation update.
4. Reference invalidation/rebuild.
5. Waiting-list rebuild.
6. Container reset/reentry.

### 7.5 Safe-Point Requirements

Vertical scaling requires:

```text
all affected containers out of active rounds
no active refs to old layout
dispatch exposures closed
round boundaries reached
registry rebuild/update safe
default empty profile prepared
```

### 7.6 Vertical Scaling Invariants

```text
1. Vertical scaling is family-wide.
2. It must not resize only one active container.
3. It must invalidate old layout-bound refs.
4. It must produce reports.
5. It must not occur while containers are active under old layout.
```

---

## 8. Extreme Default Profile

### 8.1 Definition

`TExtremeDefaultProfile` is a default provisioning profile that sizes the pre-bridge engine to expected upper-bound intake and dispatch needs.

### 8.2 Purpose

The extreme default exists to prevent normal runtime operation from becoming a backpressure negotiation.

### 8.3 Typical Inputs

1. expected max intake per cycle,
2. expected max dispatch per cycle,
3. envelope size class,
4. average/maximum envelope batch behavior if known,
5. bridge drain assumption,
6. container count,
7. slots per container,
8. safety margin.

### 8.4 Extreme Default Non-Meaning

Extreme default does not mean:

1. unbounded memory,
2. no diagnostics,
3. no safe points,
4. no eviction profile,
5. no read-side pressure,
6. no capacity configuration.

### 8.5 Extreme Default Invariant

```text
Default pre-bridge operation should not depend on luck or runtime discovery of free slots.
```

---

## 9. Pre-Sized Intake Capacity

### 9.1 Definition

Pre-sized intake capacity is the capacity assigned to receive incoming prepared envelopes without producer-side locating.

### 9.2 Components

1. ingress waiting-list capacity,
2. number of ingress-ready containers,
3. slots per container,
4. reference supply depth,
5. ingress round profile.

### 9.3 Invariant

```text
The Log API plugin adapter must not need to know how many slots remain.
```

It consumes next ingress refs.

---

## 10. Pre-Sized Dispatch Capacity

### 10.1 Definition

Pre-sized dispatch capacity is the capacity assigned to expose outgoing material to the bridge-facing side.

### 10.2 Components

1. dispatch waiting-list capacity,
2. dispatch-ready containers,
3. dispatch refs,
4. passive exposure slots/views,
5. bridge drain assumption profile.

### 10.3 Invariant

```text
The dispatcher/bridge-facing side consumes next dispatch refs or exposure views without scanning containers.
```

---

## 11. Capacity-Related Diagnostics

| Diagnostic | Meaning |
|---|---|
| `CapacityProfileMismatch` | Active component does not match profile |
| `UniformCapacityViolation` | Container has different capacity/layout |
| `ExtremeProfileInsufficient` | Profile not enough for declared assumptions |
| `WaitingListCapacityExceeded` | List capacity exceeded |
| `ReferenceSupplyDepthInsufficient` | Refs not prepared at expected depth |
| `BridgeDrainAssumptionBroken` | Dispatch drain not matching profile |
| `ScalingOutsideSafePoint` | Scaling attempted unsafely |

---

## 12. Views

| View | Purpose |
|---|---|
| `TCirculationCapacityProfileView` | Overall capacity projection |
| `TUniformContainerCapacityProfileView` | Active container capacity |
| `THorizontalScalingView` | Container count/topology |
| `TVerticalScalingView` | Uniform slot capacity |
| `TExtremeDefaultProfileView` | Extreme sizing assumption |
| `TIngressCapacityView` | Intake capacity |
| `TDispatchCapacityView` | Dispatch capacity |
| `TReferenceSupplyCapacityView` | Reference supply depth |

---

## 13. Reports

| Report | Trigger |
|---|---|
| `TCapacityProfileReport` | Profile created/loaded |
| `TExtremeDefaultProfileReport` | Extreme profile selected |
| `THorizontalScalingReport` | Container count changed |
| `TVerticalScalingReport` | Uniform capacity changed |
| `TCapacityProfileSwitchReport` | Profile switched |
| `TUniformCapacityInvariantReport` | Uniformity validated/broken |
| `TCapacityDiagnosticReport` | Capacity diagnostic event |

---

## 14. Implementation Derivation Notes

### 14.1 Candidate Headers

```text
capacity/
    TCirculationCapacityProfile.hpp
    TUniformContainerCapacityProfile.hpp
    TExtremeDefaultProfile.hpp
    TIngressCapacityProfile.hpp
    TDispatchCapacityProfile.hpp
    TCapacityProfileReport.hpp

slots_container_bundle_agent/
    THorizontalScalingProfile.hpp
    TVerticalScalingProfile.hpp
    TBundleScalingReport.hpp
```

### 14.2 Deferred Decisions

1. Exact capacity units.
2. Whether envelope size influences slot profile or only external profile planning.
3. Whether capacity profiles are compile-time constants, configuration-time values, or hybrid.
4. Whether extreme default profile is generated or user-authored.
5. Whether reference supply depth is fixed or adaptive within profile.

---

## 15. Summary

Capacity is designed before the hot path.  
Uniform containers make movement and reference calculation predictable.  
Horizontal scaling changes count.  
Vertical scaling changes family-wide capacity.  
Extreme default avoids ordinary broker-style backpressure inside the pre-bridge engine.
