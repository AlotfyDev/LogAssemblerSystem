# CME-ARCH-002 — Container Family, Registry, And Uniform Capacity Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-002-DOC-001 | Document Title | Container Family, Registry, And Uniform Capacity Model |
| CME-ARCH-002-DOC-002 | File Name | `CME-ARCH-002_Container_Family_Registry_And_Uniform_Capacity_Model.md` |
| CME-ARCH-002-DOC-003 | Architecture Pack | `CME-ARCH-PACK-01` |
| CME-ARCH-002-DOC-004 | Domain | `circulation_mechanism` |
| CME-ARCH-002-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-002-DOC-006 | Primary Scope | Container family creation, registry indexing, identity, references, uniform capacity, scaling, default empty container, move semantics |
| CME-ARCH-002-DOC-007 | Depends On | `CME-ARCH-000`, `CME-ARCH-001` |
| CME-ARCH-002-DOC-008 | Enables | Slot residency model, waiting-list model, reference precalculation, release/recycle, eviction |
| CME-ARCH-002-DOC-009 | Primary Rule | All active containers are registry-owned, index-addressable, and uniform in capacity/layout under the active profile |
| CME-ARCH-002-DOC-010 | Non-Purpose | Final data structure choice, allocator implementation, lock-free storage, bridge/read-side storage |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines how the Circulation Mechanism Engine owns and accesses its container family.

It answers:

```text
How are circulation containers created, indexed, stored, scaled, reset, and
kept structurally compatible so the engine can sustain precomputed access,
move-oriented circulation, and continuous movement without exposing container
internals to Log-Level API or bridge-side consumers?
```

### 2.2 Core Thesis

```text
All active containers live inside TContainerRegistry.

Waiting lists carry registry indices.

ReferencePrecalculator consumes registry indices and container/slot state to
prepare access references.

External consumers do not locate containers or slots.
```

---

## 3. Container Family Model

### 3.1 Definition

A container family is the active set of `TContainer` instances governed by one active capacity/layout profile.

### 3.2 Family Ownership

| Owner | Owns |
|---|---|
| `SlotsContainerBundleAgent` | family creation, scaling, active capacity profile, default empty container profile |
| `TContainerRegistry` | indexed storage of all active containers |
| `SlotsContainerModerator` | per-container readiness/reset |
| `RoundManager` | eligibility admission into waiting lists |
| `ReferencePrecalculator` | access reference calculation from registry-backed candidates |

### 3.3 Family Invariants

```text
All containers in the active family have the same capacity.
All containers in the active family have compatible slot layout.
A vertical capacity change is a family-level profile change.
A horizontal scaling operation changes container count, not slot semantics.
A container outside the registry is not an active circulation container.
```

---

## 4. TContainerRegistry Model

### 4.1 Definition

`TContainerRegistry` is the engine-owned indexed storage and lookup structure for all active `TContainer` instances.

### 4.2 Required Capabilities

| ID | Capability |
|---:|---|
| CME-ARCH-002-REG-CAP-001 | Store active containers |
| CME-ARCH-002-REG-CAP-002 | Provide stable registry indices under the active profile |
| CME-ARCH-002-REG-CAP-003 | Resolve an index to an approved internal container access path |
| CME-ARCH-002-REG-CAP-004 | Expose read-only registry views |
| CME-ARCH-002-REG-CAP-005 | Support safe-point-gated rebuild or profile switch |
| CME-ARCH-002-REG-CAP-006 | Produce invariant reports |

### 4.3 Registry Non-Capabilities

```text
The registry does not decide eligibility.
The registry does not calculate access references.
The registry does not own waiting-list order.
The registry does not own dispatch exposure.
The registry is not a downstream registry.
```

### 4.4 Registry State

| State | Meaning |
|---|---|
| `empty` | Registry has no active containers |
| `initialized` | Containers have been created but not yet active |
| `active` | Registry is serving active cycles |
| `resizing_pending` | A profile/count change is planned |
| `locked_for_profile_switch` | Registry mutations are restricted until safe point |
| `invariant_violation` | Registry consistency failed |

---

## 5. Container Identity And Locator Model

### 5.1 TContainerId

`TContainerId` is the logical identity of a container.

It answers:

```text
Which container is this?
```

### 5.2 TContainerRegistryIndex

`TContainerRegistryIndex` is the physical/indexed locator of a container inside `TContainerRegistry`.

It answers:

```text
Where is this container inside the active registry?
```

### 5.3 TContainerRef Optionality

`TContainerRef` is optional at this stage.

It may later become:

1. a resolved safe handle around registry + index,
2. a read-only view carrier,
3. a capability-limited handle,
4. an implementation-only convenience,
5. unnecessary if `TContainerRegistryIndex` is sufficient.

### 5.4 Separation Rules

```text
TContainerId ≠ TContainerRegistryIndex.
TContainerRegistryIndex ≠ TIngressAccessRef.
TContainerRegistryIndex ≠ TDispatchAccessRef.
TContainerRef, if introduced, must not expose private container internals.
```

---

## 6. Uniform Capacity Model

### 6.1 Definition

Uniform capacity means all active containers have equal slot capacity and compatible layout.

### 6.2 Purpose

Uniform capacity supports:

1. move-semantics-oriented circulation,
2. predictable reference calculation,
3. simple profile-driven scaling,
4. deterministic registry indexing,
5. simplified reset from default empty container,
6. reduced hot-path compatibility checks.

### 6.3 Capacity Profile

```text
TUniformContainerCapacityProfile
    slot_count
    slot_layout_kind
    payload_envelope_shape
    optional alignment policy
    optional reservation policy
```

### 6.4 Capacity Invariants

```text
No active container may have a different slot count.
No active container may have incompatible slot layout.
No vertical scaling may mutate one container only.
No default empty container may mismatch the active capacity profile.
```

---

## 7. Horizontal Scaling Model

### 7.1 Definition

Horizontal scaling changes the number of active containers.

### 7.2 Owner

`SlotsContainerBundleAgent`.

### 7.3 Operations

| Operation | Meaning |
|---|---|
| `add_container` | Adds a new container matching active profile |
| `remove_container` | Removes a container at safe point |
| `activate_container` | Makes a prepared container active |
| `deactivate_container` | Removes a container from active cycles |
| `rebuild_bundle` | Reconstructs active set at safe point |

### 7.4 Safe-Point Requirements

A container may be removed only when:

```text
not in ingress round
not in dispatch round
not exposed
no active access refs
not required by current capacity guarantee
```

---

## 8. Vertical Scaling Model

### 8.1 Definition

Vertical scaling changes the uniform slot capacity/layout profile for the active family.

### 8.2 Owner

`SlotsContainerBundleAgent`.

### 8.3 Rules

```text
Vertical scaling is family-wide.
Vertical scaling requires safe point.
Vertical scaling invalidates or rebuilds references.
Vertical scaling requires default empty container profile update.
Vertical scaling must not mutate active refs or active slots.
```

### 8.4 Safe-Point Sources

```text
TContainerState
TRoundState
TReferenceSupplyState
TDispatchExposureState
TModeratorState
```

---

## 9. Default Empty Container Model

### 9.1 Definition

`TDefaultEmptyContainer` is the canonical empty container profile or prototype matching the active uniform capacity/layout profile.

### 9.2 Owner

`SlotsContainerBundleAgent`.

### 9.3 Applied By

`SlotsContainerModerator`.

### 9.4 Role

It provides the reset/reinitialization source between:

```text
dispatch completion
→ reset pending
→ under moderation
→ default empty
→ ingress ready
```

### 9.5 Invariants

```text
The default empty container must match active capacity.
The default empty container must clear all slot occupancy.
The default empty container does not itself execute reset.
Reset is performed by Moderator.
```

---

## 10. Move Semantics By Construction

### 10.1 Thesis

Uniform container shape makes move-oriented circulation the default safe transfer model.

### 10.2 Why It Works

```text
same slot count
same slot layout
same payload envelope shape
same container profile
same reset profile
```

### 10.3 What It Does Not Mean

```text
It does not define bridge-side copy/move semantics.
It does not move payload directly to final receiver.
It does not guarantee downstream persistence.
It does not make the envelope an actor.
```

---

## 11. Registry And Waiting Lists

### 11.1 Principle

Waiting lists carry indices, not containers and not payloads.

```text
TIngressWaitingList:
    ordered TContainerRegistryIndex values for ingress cycle

TDispatchWaitingList:
    ordered TContainerRegistryIndex values for dispatch cycle
```

### 11.2 Benefits

1. memory locality,
2. smaller waiting-list entries,
3. lower copy overhead,
4. stable internal locators,
5. clean separation between eligibility and access.

---

## 12. Registry And ReferencePrecalculator

### 12.1 Relationship

```text
WaitingList
    gives registry index

TContainerRegistry
    resolves container data/state

ReferencePrecalculator
    calculates slot access refs

Ingress / Dispatcher
    consume prepared refs
```

### 12.2 Invariant

```text
Consumers do not locate.
Consumers do not scan.
Consumers do not count remaining slots.
Consumers ask for next.
```

---

## 13. Registry Views And Reports

### 13.1 Views

```text
TContainerRegistryView
TContainerRegistryCapacityView
TContainerRegistryIndexView
TContainerFamilyView
TUniformCapacityProfileView
```

### 13.2 Reports

```text
TContainerRegistryInitializationReport
TContainerRegistryInvariantReport
TRegistryProfileSwitchReport
TRegistryRebuildReport
TRegistryIndexInvalidationReport
```

---

## 14. Diagnostics

| Diagnostic | Meaning |
|---|---|
| `InvalidContainerIndex` | index cannot be resolved |
| `ContainerMissingAtIndex` | registry slot is empty/unexpected |
| `RegistryCapacityMismatch` | container capacity differs from profile |
| `RegistryLayoutMismatch` | container layout differs |
| `UnsafeRegistryResize` | attempted resize outside safe point |
| `DanglingWaitingListIndex` | waiting list index no longer valid |
| `ReferencePreparedForInvalidIndex` | precalculator used invalid index |

---

## 15. Implementation Notes

### 15.1 Static-First Direction

The registry should be derivable as a bounded static-profile structure where possible.

Potential future forms:

```text
fixed array
static vector
ring-like bounded storage
profile-sized storage block
```

### 15.2 Runtime Mutability

Runtime mutability should remain profile-gated and safe-point-gated.

### 15.3 Header Derivation Implication

Candidate future files may include:

```text
TContainerRegistry.hpp
TContainerRegistryIndex.hpp
TContainerId.hpp
TContainerRef.hpp
TUniformContainerCapacityProfile.hpp
TDefaultEmptyContainer.hpp
TContainerFamilyView.hpp
```

---

## 16. Deferred Decisions

| ID | Decision |
|---:|---|
| CME-ARCH-002-DEF-001 | Exact registry storage structure |
| CME-ARCH-002-DEF-002 | Whether `TContainerRef` is materialized |
| CME-ARCH-002-DEF-003 | Whether `TContainerId` is required beyond index |
| CME-ARCH-002-DEF-004 | Exact profile switch mechanics |
| CME-ARCH-002-DEF-005 | Exact allocator/storage ownership form |
