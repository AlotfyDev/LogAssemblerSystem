# CME-ARCH-000 — Holistic Foundation And System View

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-000-DOC-001 | Document Title | Holistic Foundation And System View |
| CME-ARCH-000-DOC-002 | File Name | `CME-ARCH-000_Holistic_Foundation_And_System_View.md` |
| CME-ARCH-000-DOC-003 | Architecture Pack | `CME-ARCH-PACK-00_Foundation_And_Holistic_View` |
| CME-ARCH-000-DOC-004 | Domain | `circulation_mechanism` |
| CME-ARCH-000-DOC-005 | Parent System | Log-Level Assembler System |
| CME-ARCH-000-DOC-006 | Formal Version | Architecture Draft V1 |
| CME-ARCH-000-DOC-007 | Language | English with preserved domain vocabulary |
| CME-ARCH-000-DOC-008 | Scope Level | Holistic architecture foundation, boundary model, component taxonomy, two-cycle model, high-value cross-cutting models |
| CME-ARCH-000-DOC-009 | Implementation Direction | C++17, header-only-first where appropriate, templates, traits, static polymorphism, CRTP-compatible abstraction layers |
| CME-ARCH-000-DOC-010 | Status | Pre-Implementation Architecture Specification |
| CME-ARCH-000-DOC-011 | Primary Rule | The Circulation Mechanism Engine is a pre-bridge, write-side, envelope-aware but payload-content-blind circulation engine |
| CME-ARCH-000-DOC-012 | Excluded From This Document | Final C++ headers, final class names, final runtime algorithms, final bridge protocol, final read-side receiver behavior, final add-on implementation |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document establishes the holistic architecture view of the **Circulation Mechanism Engine**.

It answers:

```text
What is the Circulation Mechanism Engine, where does it sit between the
Log-Level API and the bridge/read-side boundary, what does it own, what does it
not own, which actors and data structures form its core, and which cross-cutting
models must govern all later component-level specifications?
```

### 2.2 Document Role

| Record ID | Role | Description |
|---:|---|---|
| CME-ARCH-000-ROLE-001 | Engine Identity Anchor | Defines the engine as a pre-bridge circulation mechanism, not a broker or bridge |
| CME-ARCH-000-ROLE-002 | Boundary Anchor | Fixes what enters from Log-Level API and what leaves toward bridge/read-side |
| CME-ARCH-000-ROLE-003 | Taxonomy Anchor | Establishes actor, registry, data-structure, state, reference, view, report, and profile families |
| CME-ARCH-000-ROLE-004 | Two-Cycle Anchor | Establishes ingress and dispatch cycles as directionally distinct uses of the same circulation family |
| CME-ARCH-000-ROLE-005 | Implementation Readiness Input | Prepares detailed architecture packs and later header derivation |

### 2.3 Non-Purpose

This document does not:

1. define final header names,
2. define final C++ template parameters,
3. define concrete memory storage implementation,
4. define bridge protocol,
5. define read-side receiver lifecycle,
6. define final add-on adapter behavior,
7. define production diagnostics engine,
8. implement any runtime algorithm.

---

## 3. Engine Identity

### 3.1 Canonical Engine Name

```text
Circulation Mechanism Engine
```

### 3.2 Current Root Domain Name

```text
circulation_mechanism/
```

### 3.3 Legacy Vocabulary Mapping

Earlier documents may use:

```text
write_side
queue
queue container
queue bundle
single queue moderator
writing / feeding round
dispatching / delivery round
```

The current interpretation is:

| Legacy Term | Current Reading |
|---|---|
| `write_side` | pre-bridge write-side circulation profile |
| `queue` | container, not broker |
| `queue container` | `TContainer` candidate |
| `queue bundle` | `TContainerBundle` candidate |
| `queue bundle agent` | `SlotsContainerBundleAgent` |
| `single queue moderator` | `SlotsContainerModerator` |
| `writing / feeding round` | ingress / container-providing round |
| `dispatching / delivery round` | dispatching round before bridge boundary |

### 3.4 Engine Definition

```text
The Circulation Mechanism Engine is a pre-bridge write-side engine responsible
for admitting prepared payload envelopes into circulation-owned containers,
maintaining container/slot residency, organizing container participation in
ingress and dispatch cycles, precomputing access references, and exposing
dispatch-ready material toward the bridge boundary without interpreting payload
content, owning bridge protocols, or owning final receiver lifecycle.
```

### 3.5 Short Definition

```text
The engine circulates prepared envelopes through containerized residency and
reference-driven access before bridge handoff.
```

### 3.6 Essential Identity Constraints

| Record ID | Constraint | Meaning |
|---:|---|---|
| CME-ARCH-000-ID-001 | Envelope-aware | The engine knows the circulation unit is an envelope/payload envelope |
| CME-ARCH-000-ID-002 | Payload-content-blind | The engine does not parse, validate, or interpret envelope content |
| CME-ARCH-000-ID-003 | Pre-bridge | It ends before bridge runtime and receiver lifecycle |
| CME-ARCH-000-ID-004 | Single producer / single dispatcher | The pre-bridge profile assumes one producer-facing intake and one dispatcher |
| CME-ARCH-000-ID-005 | State-rich | Slot, container, round, reference, and exposure states govern transitions |
| CME-ARCH-000-ID-006 | Reference-driven | Consumers access through prepared refs, not through locating logic |
| CME-ARCH-000-ID-007 | Container-registry-backed | Active containers are indexed through a registry |
| CME-ARCH-000-ID-008 | Non-broker | The engine is not a message broker, pub/sub system, or durable queue |

---

## 4. Boundary Position

### 4.1 Upstream Boundary: Log-Level API

The upstream domain is:

```text
log_level_api/
```

The Log-Level API prepares and produces the envelope.

It owns:

1. content intake,
2. schema/profile resolution,
3. parser binding,
4. optional validation,
5. metadata preparation,
6. timestamp stabilization,
7. envelope construction,
8. envelope provider plugin adapter.

The Circulation Mechanism Engine does **not** own those concerns.

### 4.2 Log-Level API Role Toward Circulation

```text
Log-Level API side = Content / Envelope Provider Plugin Adapter
```

The Log-Level API provides an already prepared envelope. The Circulation Engine does not receive raw payloads for parsing.

### 4.3 Circulation Role Toward Log-Level API

```text
Circulation side = Container / Admission / Placement Port Adapter
```

The Circulation Engine provides placement/admission capacity through the intake boundary and internally provides ready access references.

### 4.4 Downstream Boundary: Bridge / Read-Side Direction

The Circulation Engine exposes dispatch-ready material.

It does **not** own:

1. bridge session,
2. bridge protocol,
3. communication channel execution,
4. final receiver semantics,
5. read-side delay/retry behavior,
6. add-on storage or telemetry behavior.

### 4.5 Boundary Flow

```text
Log-Level API
    produces prepared envelope
        ↓
Circulation Mechanism Engine
    admits, stores, circulates, exposes
        ↓
Bridge-facing boundary
    consumes exposure / dispatch refs
        ↓
Read-side circulation or receiver/add-on side
    absorbs, delays, retries, stores, exports, or otherwise handles receiver semantics
```

### 4.6 Boundary Anti-Collapse Rules

| Record ID | Protected Distinction | Must Not Collapse Into |
|---:|---|---|
| CME-ARCH-000-BND-001 | Log-Level API | Circulation internals |
| CME-ARCH-000-BND-002 | Circulation Engine | Log-Level API parser/assembler |
| CME-ARCH-000-BND-003 | Dispatcher | Bridge protocol runtime |
| CME-ARCH-000-BND-004 | Dispatch exposure | Final receiver acceptance |
| CME-ARCH-000-BND-005 | Container registry | Downstream registry |
| CME-ARCH-000-BND-006 | Waiting list | Message queue or envelope store |
| CME-ARCH-000-BND-007 | Envelope | Actor or dispatcher |
| CME-ARCH-000-BND-008 | Output boundary | Final destination lifecycle |

---

## 5. Pre-Bridge Write-Side Profile

### 5.1 Profile Definition

The pre-bridge write-side profile is the primary profile of this engine.

It assumes:

1. one producer-facing intake,
2. one dispatcher-facing output path,
3. preconfigured capacity,
4. extreme/default provisioning,
5. horizontal scaling through more containers,
6. vertical scaling through uniform capacity profile changes,
7. passive output exposure by default,
8. no receiver-side retry/failure lifecycle inside this engine.

### 5.2 Why This Profile Exists

The engine is placed before the bridge. Therefore, it must keep movement continuous and deterministic without absorbing downstream uncertainty.

### 5.3 Profile Invariants

```text
1. No hot-path parser or content inspection exists inside the engine.
2. No multi-producer arbitration exists inside the pre-bridge engine.
3. No multi-consumer dispatch arbitration exists inside the pre-bridge engine.
4. No receiver backpressure model is owned by this profile.
5. No final receiver acknowledgement is required for core circulation movement.
6. Dispatch exposure is not downstream completion.
```

### 5.4 Single-Writer Relation

The profile is compatible with a single-writer baseline: correctness is established for one mutation authority per pipeline/engine instance before optional parallelism is introduced.

---

## 6. Payload Direction Thesis

### 6.1 Core Thesis

The two main circulation cycles differ primarily by payload direction.

| Cycle | Direction | Consumer | Meaning |
|---|---|---|---|
| Ingress / Intake / Container-Providing Cycle | outside → engine | Log-Level API / envelope provider side | Place prepared envelope into a slot |
| Dispatch Cycle | engine → outside | Dispatcher / bridge-facing side | Expose or hand off access to ready envelope |

### 6.2 Shared Mechanical Pattern

Both cycles use:

1. container registry,
2. container state,
3. waiting list,
4. round manager,
5. reference precalculation,
6. prepared access reference,
7. controlled access,
8. state transition,
9. report/view evidence.

### 6.3 Direction-Specific Ref Types

| Ref | Cycle | Direction |
|---|---|---|
| `TIngressAccessRef` | ingress | outside → engine |
| `TDispatchAccessRef` | dispatch | engine → outside |

### 6.4 Direction Anti-Collapse

```text
An ingress reference must not be consumed as a dispatch reference.
A dispatch reference must not be consumed as an ingress reference.
```

---

## 7. Core Taxonomy

### 7.1 Taxonomy Families

The engine contains nine architecture families:

1. actors,
2. registries,
3. data-structure containers,
4. states,
5. references / handles,
6. boundaries,
7. policies / profiles,
8. diagnostics,
9. reports / views.

### 7.2 Actor Family

| ID | Actor | Core Role |
|---|---|---|
| CME-ACT-001 | `SlotsContainerBundleAgent` | Creates/manages container family, scaling, and default empty profile |
| CME-ACT-002 | `SlotsContainerModerator` | Moderates one container instance, exposes state/ref, applies reset |
| CME-ACT-003 | `RoundManager` | Registers eligible container indices into waiting lists |
| CME-ACT-004 | `ReferencePrecalculator` | Precomputes access references from registry/list/state/round context |
| CME-ACT-005 | `Ingress` | Consumes ingress refs and places envelopes into slots |
| CME-ACT-006 | `Dispatcher` | Consumes dispatch refs and exposes material toward bridge boundary |

### 7.3 Registry Family

| ID | Registry / Locator | Core Role |
|---|---|---|
| CME-REG-001 | `TContainerRegistry` | Stores all active containers in indexed storage |
| CME-REG-002 | `TContainerRegistryIndex` | Lightweight locator for container position |
| CME-REG-003 | `TContainerIdRegistry` | Optional identity-to-index mapping |
| CME-REG-004 | `TAccessReferenceCache` | Optional ready reference store |

### 7.4 Data-Structure Container Family

| ID | Data Structure | Core Role |
|---|---|---|
| CME-DS-001 | `TContainer` | Uniform-capacity slot container and cycle participant |
| CME-DS-002 | `TSlot` | Bounded placement/access position |
| CME-DS-003 | `TContainerBundle` | Grouping of containers under BundleAgent |
| CME-DS-004 | `TDefaultEmptyContainer` | Reset/reinitialization source profile |
| CME-DS-005 | `TIngressWaitingList` | FIFO list of ingress-eligible container indices |
| CME-DS-006 | `TDispatchWaitingList` | FIFO/time-range-aware dispatch-eligible container indices |
| CME-DS-007 | `TRound` | Runtime round structure |
| CME-DS-008 | `TIngressRound` | Directional ingress round |
| CME-DS-009 | `TDispatchRound` | Directional dispatch round |
| CME-DS-010 | `TContainerTimeRange` | Time-range metadata for dispatch ordering/eviction |
| CME-DS-011 | `TEvictionCandidate` | Candidate selected under eviction policy |
| CME-DS-012 | `TPayloadEnvelope` | Opaque envelope payload unit from engine perspective |

### 7.5 State Family

| State | Scope |
|---|---|
| `TSlotState` | slot-local placement/access state |
| `TContainerState` | container-level cycle eligibility and readiness |
| `TRoundState` | round lifecycle |
| `TModeratorState` | per-container moderation state |
| `TBundleAgentState` | topology/scaling state |
| `TReferenceSupplyState` | reference supply lifecycle |
| `TDispatchExposureState` | output exposure lifecycle |
| `TAccessReferenceValidity` | reference validity |

### 7.6 Reference Family

| Reference | Purpose |
|---|---|
| `TContainerId` | logical container identity |
| `TContainerRegistryIndex` | indexed locator |
| `TContainerRef` | optional resolved safe reference |
| `TSlotAccessRef` | generic slot access reference |
| `TIngressAccessRef` | ingress-specific access reference |
| `TDispatchAccessRef` | dispatch-specific access reference |
| `TRoundScopedRef` | round-scoped validity wrapper |
| `TNextRefToken` | consumer-facing next-ref rhythm |

### 7.7 Boundary Family

| Boundary | Purpose |
|---|---|
| `EnvelopePlacementPort` | Intake boundary for prepared envelope |
| `EnvelopeAssemblerPluginAdapter` | Log-Level API provider-side adapter |
| `DispatchOutputExposureBoundary` | Output exposure boundary |
| `BridgeFacingPluginAdapter` | Bridge-facing consumer of dispatch exposure |
| `PullDispatchProfile` | Passive pull default |
| `PushDispatchProfile` | Optional push profile |

### 7.8 Profiles / Policies Family

| Profile | Purpose |
|---|---|
| `TCirculationCapacityProfile` | Total planned capacity |
| `TUniformContainerCapacityProfile` | Uniform container capacity invariant |
| `THorizontalScalingProfile` | container count |
| `TVerticalScalingProfile` | slots per container |
| `TExtremeDefaultProfile` | default extreme provisioning |
| `TIngressCycleProfile` | ingress direction and assumptions |
| `TDispatchCycleProfile` | dispatch direction and assumptions |
| `TEvictionPolicyProfile` | eviction behavior |
| `TReferenceSupplyPolicy` | next-ref guarantee |
| `TDispatchExposurePolicy` | passive/push dispatch behavior |

### 7.9 Diagnostics Family

| Diagnostic | Meaning |
|---|---|
| `ContainerRegistryInvariantViolation` | registry index/storage inconsistency |
| `ContainerStateMismatch` | waiting list or round membership contradicts container state |
| `SlotStateMismatch` | access ref contradicts slot state |
| `ReferenceSupplyInterrupted` | next-ref supply guarantee interrupted |
| `RoundStateViolation` | invalid round transition/action |
| `SafePointViolation` | unsafe operation attempted outside safe point |
| `EvictionTriggered` | eviction selected/applied |
| `BridgeDrainAssumptionBroken` | bridge-side drain did not follow pre-bridge assumption |

### 7.10 Reports / Views Family

| Kind | Meaning |
|---|---|
| View | read-only current-state projection |
| Report | action, transition, or diagnostic evidence |

---

## 8. Two-Cycle Model

### 8.1 Cycle 1 — Ingress / Container Providing

The ingress cycle prepares containers for receiving payload envelopes.

Core sequence:

```text
BundleAgent
→ Registry
→ Moderator
→ RoundManager
→ TIngressWaitingList
→ ReferencePrecalculator
→ Ingress
→ TSlot occupancy
```

### 8.2 Cycle 2 — Dispatch / Output Exposure

The dispatch cycle prepares containers or slots for outward exposure.

Core sequence:

```text
Moderator / Container State
→ RoundManager
→ TDispatchWaitingList
→ ReferencePrecalculator
→ Dispatcher
→ DispatchOutputExposureBoundary
→ Bridge-facing adapter
```

### 8.3 Cycle Symmetry

Both cycles use the same family of mechanics but opposite payload direction.

### 8.4 Cycle Asymmetry

| Aspect | Ingress | Dispatch |
|---|---|---|
| Payload movement | into engine | out of engine |
| Consumer-facing side | Log-Level API plugin adapter | Bridge-facing adapter |
| Ref type | `TIngressAccessRef` | `TDispatchAccessRef` |
| Waiting list | `TIngressWaitingList` | `TDispatchWaitingList` |
| Final engine actor | `Ingress` | `Dispatcher` |

---

## 9. Container Registry Foundation

### 9.1 Registry Rule

```text
All active containers are stored in a container registry.
```

### 9.2 Registry Purpose

The registry provides:

1. memory locality,
2. stable indexed access,
3. lightweight waiting-list entries,
4. separation between identity and access,
5. failure/invariant diagnostics,
6. profile-switch safety.

### 9.3 Registry Index Role

The waiting lists carry indices, not containers.

```text
TIngressWaitingList → TContainerRegistryIndex[]
TDispatchWaitingList → TContainerRegistryIndex[]
```

### 9.4 Registry Anti-Collapse Rules

```text
TContainerRegistry is not a downstream registry.
TContainerRegistry is not a policy registry.
TContainerRegistry is not a message broker.
TContainerRegistry is not a bridge registry.
```

---

## 10. Reference Precalculation Principle

### 10.1 Core Principle

```text
Do not locate while accessing.
```

### 10.2 ReferencePrecalculator Responsibility

The `ReferencePrecalculator` consumes:

1. container registry indices,
2. container state,
3. slot state,
4. slot layout,
5. waiting-list ordering,
6. round context,
7. capacity/profile context.

It produces:

1. ingress access references,
2. dispatch access references,
3. round-scoped refs,
4. ready next-ref supply.

### 10.3 What Consumers See

Consumers see:

```text
next
```

They do not see:

1. container index scan,
2. slot selection,
3. capacity lookup,
4. waiting-list mechanics,
5. round membership mechanics.

### 10.4 Reference Invariants

```text
1. Every access operation must consume a valid reference.
2. Refs are scoped.
3. Refs can expire.
4. Refs can be invalidated.
5. Refs must not cross direction.
6. Refs are not ownership transfer by themselves.
```

---

## 11. State-Rich Circulation Principle

### 11.1 State Is Structural

State is not a decorative status field.

State determines:

1. eligibility,
2. access,
3. transition legality,
4. waiting-list membership,
5. reference validity,
6. release/recycle readiness,
7. safe-point availability,
8. diagnostic interpretation.

### 11.2 State Layers

```text
SlotState
ContainerState
RoundState
ReferenceValidity
DispatchExposureState
ModeratorState
BundleAgentState
```

### 11.3 State Separation Rule

```text
ContainerState is independent from SlotState.
RoundState is independent from ContainerState.
ReferenceValidity is independent from consumer intention.
```

### 11.4 Transition Authority

| State | Transition Authority |
|---|---|
| `TSlotState` | Ingress / Dispatcher / Container reset |
| `TContainerState` | Moderator / RoundManager / Dispatcher effects |
| `TRoundState` | RoundManager |
| `TReferenceSupplyState` | ReferencePrecalculator |
| `TDispatchExposureState` | Dispatcher |
| `TBundleAgentState` | BundleAgent |

---

## 12. Reports / Views Principle

### 12.1 Definition

```text
View = safe read-only projection of current state.
Report = result or evidence of an action, transition, or diagnostic event.
```

### 12.2 View Purpose

Views allow safe observation without exposing internals.

### 12.3 Report Purpose

Reports preserve traceability.

### 12.4 Report Non-Meaning

A report does not automatically prove downstream delivery, persistence, or receiver acceptance.

### 12.5 Candidate Views

1. `TBundleTopologyView`
2. `TContainerRegistryView`
3. `TContainerStateView`
4. `TSlotStateView`
5. `TIngressWaitingListView`
6. `TDispatchWaitingListView`
7. `TRoundView`
8. `TReferenceSupplyView`
9. `TDispatchExposureView`
10. `TBoundaryBindingView`

### 12.6 Candidate Reports

1. `TBundleScalingReport`
2. `TContainerResetReport`
3. `TContainerStateTransitionReport`
4. `TSlotTransitionReport`
5. `TWaitingListRegistrationReport`
6. `TRoundAdmissionReport`
7. `TReferencePrecalculationReport`
8. `TDispatchExposureReport`
9. `TEvictionReport`
10. `TInvariantViolationReport`

---

## 13. Passive Pull Dispatch Default

### 13.1 Default Dispatch Profile

```text
Passive pull is the default dispatch behavior.
```

### 13.2 Meaning

The dispatcher exposes dispatch-ready material or refs.

The bridge-facing side pulls or consumes according to its own boundary contract.

### 13.3 Why Passive Pull

Passive pull preserves:

1. bridge ownership of protocol mechanics,
2. separation between circulation and transfer semantics,
3. receiver-side ownership of delay/retry,
4. dispatch finality without downstream ownership.

### 13.4 Optional Push

Push can exist later as profile:

```text
TPushDispatchProfile
```

But it must not redefine the engine as a bridge or delivery executor.

---

## 14. Read-Side Profile Separation

### 14.1 Pre-Bridge Profile

The pre-bridge profile assumes:

1. single producer,
2. single dispatcher,
3. pre-sized capacity,
4. no hot-path backpressure,
5. passive pull default,
6. no receiver retry lifecycle.

### 14.2 Read-Side Profile

A read-side circulation profile may own:

1. delayed receiver release,
2. failed dispatch waiting list,
3. retry,
4. receiver backpressure,
5. receiver acknowledgement,
6. add-on-specific absorption.

### 14.3 Separation Rule

```text
Pre-bridge circulation must not absorb read-side lifecycle concerns.
```

---

## 15. Capacity, Scaling, And Eviction Overview

### 15.1 Capacity Thesis

The pre-bridge engine relies on configured capacity.

### 15.2 Horizontal Scaling

Horizontal scaling increases the number of containers.

Owned by:

```text
SlotsContainerBundleAgent
```

### 15.3 Vertical Scaling

Vertical scaling changes the uniform slots-per-container capacity.

It must occur only at safe points.

### 15.4 Uniform Capacity Rule

```text
All active containers share the same capacity and slot layout.
```

### 15.5 Eviction

Eviction is exceptional and profile-governed.

Default candidate rule:

```text
oldest container by time range
```

### 15.6 Eviction Non-Meaning

Eviction does not imply downstream failure or receiver rejection.

---

## 16. High-Value Cross-Cutting Models

### 16.1 Reference Validity Model

Controls:

1. prepared,
2. issued,
3. consumed,
4. expired,
5. invalidated,
6. stale detected.

### 16.2 Safe-Point Model

Controls:

1. reset,
2. vertical scaling,
3. registry rebuild,
4. ref invalidation,
5. eviction,
6. release/recycle.

### 16.3 Release / Recycle Model

Controls:

1. slot release,
2. container release,
3. reference release,
4. exposure release,
5. round release,
6. container recycle.

### 16.4 Reports / Views Model

Controls safe observation and evidence.

### 16.5 Dispatch Profile Model

Controls passive pull vs optional push.

### 16.6 Profile Split Model

Controls pre-bridge vs read-side profile separation.

### 16.7 Eviction Model

Controls time-range-based eviction and safe-point requirements.

---

## 17. Anti-Collapse Rules

| ID | Rule |
|---:|---|
| CME-ARCH-000-AC-001 | The engine is not a message broker |
| CME-ARCH-000-AC-002 | The engine is not the bridge |
| CME-ARCH-000-AC-003 | The engine is not the read-side receiver |
| CME-ARCH-000-AC-004 | The engine does not parse or validate payload content |
| CME-ARCH-000-AC-005 | The engine does not assemble envelopes |
| CME-ARCH-000-AC-006 | The envelope is a payload carrier, not an actor |
| CME-ARCH-000-AC-007 | Slot occupancy is not envelope lifecycle ownership |
| CME-ARCH-000-AC-008 | Waiting lists are not envelope stores |
| CME-ARCH-000-AC-009 | Container registry is not downstream registry |
| CME-ARCH-000-AC-010 | Dispatch exposure is not downstream delivery |
| CME-ARCH-000-AC-011 | Reference calculation is not access execution |
| CME-ARCH-000-AC-012 | Safe point is not an arbitrary callback |
| CME-ARCH-000-AC-013 | Read-side delay/retry is not pre-bridge circulation responsibility |

---

## 18. Architecture Pack Roadmap

### 18.1 Next Pack

```text
CME-ARCH-PACK-01_Core_Actors_Registries_Containers_And_Slot_Model
```

### 18.2 Planned Documents

```text
CME-ARCH-001_Core_Taxonomy_And_Component_Ownership.md
CME-ARCH-002_Container_Family_Registry_And_Uniform_Capacity_Model.md
CME-ARCH-003_Slot_Container_State_And_Residency_Model.md
```

### 18.3 Later Packs

1. ingress/dispatch cycle model,
2. reference validity and precalculation model,
3. state/safe-point/release/recycle model,
4. boundary and profile separation model,
5. diagnostics/views/reports model,
6. capacity/eviction model,
7. implementation-readiness model.

---

## 19. Diagram Index

| Diagram | Purpose |
|---|---|
| `CME-ARCH-000_context_boundary_map.mmd` | Shows boundary between Log-Level API, circulation, bridge, read-side |
| `CME-ARCH-000_holistic_component_map.mmd` | Shows core actors/data structures |
| `CME-ARCH-000_two_cycle_payload_direction.mmd` | Shows ingress vs dispatch direction |
| `CME-ARCH-000_reference_precalculation_pipeline.mmd` | Shows locating/calculation before access |
| `CME-ARCH-000_state_and_safe_point_map.mmd` | Shows state/safe-point sources |
| `CME-ARCH-000_pre_bridge_vs_read_side_profile.mmd` | Shows profile separation |

---

## 20. Deferred Decisions

| ID | Decision | Reason |
|---:|---|---|
| CME-ARCH-000-DD-001 | Final C++ type names | Deferred to implementation derivation |
| CME-ARCH-000-DD-002 | Exact container storage structure | May be array/static vector/ring-like |
| CME-ARCH-000-DD-003 | Whether `TContainerRef` is distinct from registry index | Needs later header modeling |
| CME-ARCH-000-DD-004 | Exact report class inventory | Drafted here, finalized in diagnostics pack |
| CME-ARCH-000-DD-005 | Optional push dispatch | Profile candidate only |
| CME-ARCH-000-DD-006 | Read-side failed-dispatch list | Belongs to read-side profile pack |
| CME-ARCH-000-DD-007 | Eviction default enablement | Likely disabled or exceptional in pre-bridge extreme profile |
