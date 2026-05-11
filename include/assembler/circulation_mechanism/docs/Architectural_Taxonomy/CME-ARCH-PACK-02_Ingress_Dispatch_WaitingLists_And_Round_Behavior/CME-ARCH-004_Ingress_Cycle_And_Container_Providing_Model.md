# CME-ARCH-004 — Ingress Cycle And Container Providing Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-004-DOC-001 | Document Title | Ingress Cycle And Container Providing Model |
| CME-ARCH-004-DOC-002 | Package | CME-ARCH-PACK-02 |
| CME-ARCH-004-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-004-DOC-004 | Scope Level | Ingress cycle, container-providing cycle, producer-facing access, placement behavior |
| CME-ARCH-004-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-004-DOC-006 | Implementation Direction | C++17, header-only-first, static/profile-driven, single-producer pre-bridge profile |
| CME-ARCH-004-DOC-007 | Depends On | CME-ARCH-000, CME-ARCH-001, CME-ARCH-002, CME-ARCH-003 |
| CME-ARCH-004-DOC-008 | Related Models | `TIngressWaitingList`, `RoundManager`, `ReferencePrecalculator`, `TIngressAccessRef`, `TContainerRegistry`, `TContainer`, `TSlot` |
| CME-ARCH-004-DOC-009 | Primary Rule | Ingress consumes a precomputed ingress access reference and moves an envelope payload from outside the engine into a slot |
| CME-ARCH-004-DOC-010 | Excluded | Log API parsing, envelope assembly, bridge orchestration, read-side receiver behavior, final delivery |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the ingress-side movement cycle of the Circulation Mechanism Engine.

It answers:

```text
How does a prepared envelope from the Log-Level API enter the circulation engine
without exposing container topology, slot location, or container capacity concerns
to the producer-facing side?
```

### 2.2 Core Thesis

```text
Ingress is not locating.
Ingress is access execution through an already prepared reference.
```

The `ReferencePrecalculator` owns locating and reference calculation.  
`Ingress` consumes a valid `TIngressAccessRef` and performs the placement/access operation.

### 2.3 Payload Direction

```text
outside → engine
```

The payload envelope enters the circulation-owned residency model.

---

## 3. Scope

### 3.1 In Scope

1. Producer-side envelope handoff.
2. Log API plugin adapter relation.
3. Ingress-facing access references.
4. Container-providing participation.
5. Ingress waiting-list consumption.
6. Single-producer assumption.
7. Envelope placement into slot.
8. Ingress state transitions.
9. Ingress reports and views.
10. Ingress invariants.

### 3.2 Out of Scope

1. Raw payload parsing.
2. Log-Level API schema, parser, metadata, timestamp, validator, or assembler internals.
3. Bridge orchestration.
4. Dispatch-side exposure.
5. Final receiver behavior.
6. Read-side failed dispatch.
7. Copy/move semantics after output boundary.

---

## 4. Ingress Boundary Participants

### 4.1 Producer-Side Participant

| Field | Value |
|---|---|
| Name | `EnvelopeAssemblerPluginAdapter` / `LogApiEnvelopeProviderPluginAdapter` |
| Role | Producer-facing plugin adapter representing the Log-Level API |
| Provides | Prepared envelope payload |
| Does Not Know | container id, registry index, slot index, container capacity, remaining slots, waiting list ordering |
| Consumes | `TIngressAccessRef` or a boundary-safe placement token |

### 4.2 Circulation-Side Participant

| Field | Value |
|---|---|
| Name | `Ingress` / `EnvelopePlacementPort` |
| Role | Circulation-side placement/access executor |
| Provides | Controlled access into a preselected slot |
| Does Not Own | envelope assembly, schema, parsing, metadata, timestamp stabilization |
| Consumes | prepared envelope + precomputed ingress access reference |

### 4.3 Boundary Contract

```text
Log-Level API provides an envelope.
Circulation provides a valid placement/access reference.
Ingress consumes both and performs placement.
```

---

## 5. Ingress Cycle Overview

### 5.1 Precondition Chain

```text
BundleAgent creates uniform containers.
TContainerRegistry owns indexed containers.
Moderator exposes container state/readiness.
RoundManager admits ingress-eligible container indices into TIngressWaitingList.
ReferencePrecalculator consumes waiting-list indices and prepares TIngressAccessRef.
Ingress consumes the next ingress ref and places the envelope.
```

### 5.2 Cycle Sequence

| Step | Actor / Structure | Action |
|---:|---|---|
| 1 | `SlotsContainerBundleAgent` | Ensures container family and capacity profile exist |
| 2 | `SlotsContainerModerator` | Confirms container readiness |
| 3 | `RoundManager` | Adds eligible container index to `TIngressWaitingList` |
| 4 | `TIngressWaitingList` | Orders eligible container indices |
| 5 | `ReferencePrecalculator` | Prepares next ingress access references |
| 6 | `EnvelopeAssemblerPluginAdapter` | Presents prepared envelope |
| 7 | `Ingress` | Consumes `TIngressAccessRef` |
| 8 | `TSlot` | Receives envelope residency |
| 9 | `TContainer` | Updates container-level state/readiness as required |
| 10 | Reports | Emit placement and state-transition evidence |

---

## 6. `TIngressAccessRef`

### 6.1 Definition

`TIngressAccessRef` is a direction-specific access reference that allows ingress to place a prepared envelope into a specific slot selected by the engine.

### 6.2 Owned By

```text
ReferencePrecalculator owns calculation.
Ingress owns use.
```

### 6.3 Must Not Be Used For

1. Dispatch.
2. Bridge exposure.
3. Direct container scanning.
4. Slot discovery.
5. Producer-side storage.
6. Long-lived external handle.

### 6.4 Validity Requirements

| Requirement | Meaning |
|---|---|
| Valid registry index | Container still exists in registry |
| Valid container state | Container remains ingress-ready or receiving |
| Valid slot state | Slot is empty/reserved-for-ingress |
| Valid round scope | Ingress round context still allows placement |
| Valid safe-point context | No reset/profile switch invalidated the ref |

---

## 7. Ingress State Model

### 7.1 Candidate States

```text
ready
awaiting_ref
placing
placed
blocked_by_invariant
closed
```

### 7.2 State Meaning

| State | Meaning |
|---|---|
| `ready` | Ingress surface is available |
| `awaiting_ref` | Envelope may exist but no valid ref has been issued yet |
| `placing` | Ingress is consuming a valid ref |
| `placed` | Envelope was placed into slot |
| `blocked_by_invariant` | Placement was blocked by broken state/ref invariant |
| `closed` | Ingress cycle or surface is closed |

### 7.3 Transition Rules

```text
ready → awaiting_ref
awaiting_ref → placing
placing → placed
placing → blocked_by_invariant
placed → ready
ready → closed
```

### 7.4 Transition Authority

Ingress owns its local access state.  
Slot/container state transitions remain owned by the slot/container transition model.

---

## 8. Slot Placement Semantics

### 8.1 Placement Meaning

Placement means:

```text
A prepared envelope payload becomes resident in a selected slot.
```

### 8.2 Placement Does Not Mean

1. Envelope lifecycle ownership by slot.
2. Dispatch readiness.
3. Bridge exposure.
4. Receiver delivery.
5. Downstream acceptance.

### 8.3 Occupancy Relation

```text
Envelope
    occupies:
        Slot
            inside:
                TContainer
```

The slot records occupancy/residency. It does not become the envelope actor.

---

## 9. Single Producer Assumption

### 9.1 Rule

```text
The pre-bridge circulation profile assumes one producer-facing ingress stream.
```

### 9.2 Meaning

Single producer means the pre-bridge engine does not model:

1. producer arbitration,
2. multi-producer contention,
3. producer fairness,
4. producer group scheduling,
5. message-broker admission.

### 9.3 Scaling

Throughput is handled by:

1. pre-sized capacity,
2. horizontal scaling of containers,
3. vertical scaling of uniform container capacity,
4. continuous reference supply,
5. stable single-producer access rhythm.

---

## 10. Ingress Waiting List Participation

### 10.1 Waiting List Role

`TIngressWaitingList` orders container registry indices that are eligible to receive envelopes.

### 10.2 Entry Conditions

A container index may enter the ingress waiting list only if:

```text
container exists
container state permits ingress
container is not locked for reset or profile switch
round state accepts candidates
registry index is valid
```

### 10.3 Output to ReferencePrecalculator

The list provides ordered container indices.  
It does not provide slots.  
Slot selection remains reference-precalculation work.

---

## 11. Invariants

### 11.1 Core Invariants

```text
1. Ingress never performs locating.
2. Ingress never scans containers.
3. Ingress never chooses a slot.
4. Ingress never interprets payload content.
5. Ingress only consumes valid ingress references.
6. Ingress direction is outside → engine.
7. The producer-side adapter must not know container topology.
8. Slot occupancy is not envelope lifecycle ownership.
```

### 11.2 Boundary Invariants

```text
1. Log-Level API is producer, not circulation owner.
2. Circulation owns placement, not envelope assembly.
3. The ingress access reference is the only approved placement path.
4. Raw payloads do not enter circulation directly.
```

---

## 12. Views

| View | Purpose |
|---|---|
| `TIngressView` | Read-only ingress status |
| `TIngressAdmissionView` | Admission surface readiness |
| `TIngressPlacementView` | Last/active placement projection |
| `TIngressReferenceConsumptionView` | Ref consumption status |
| `TIngressWaitingListView` | Ordered eligible container indices |

---

## 13. Reports

| Report | Trigger |
|---|---|
| `TIngressPlacementReport` | Envelope placed |
| `TIngressAccessReport` | Ref consumed |
| `TIngressInvariantReport` | Ingress invariant violation |
| `TIngressBoundaryReport` | Producer/boundary mismatch |
| `TIngressWaitingListDrainReport` | List drained for reference preparation |

---

## 14. Failure / Diagnostic Conditions

| Condition | Classification |
|---|---|
| `InvalidIngressRef` | invariant violation |
| `EnvelopeNotReady` | boundary contract violation |
| `SlotNotWritable` | slot-state mismatch |
| `ContainerNoLongerIngressReady` | container-state mismatch |
| `RoundClosedForIngress` | round-state mismatch |
| `IngressReferenceExpired` | reference validity violation |

Most of these are not normal producer-facing hot-path errors. Under the configured profile, they are diagnostics for broken invariants or misconfiguration.

---

## 15. Configuration Profiles

| Profile | Purpose |
|---|---|
| `TIngressCycleProfile` | Defines single-producer ingress behavior |
| `TIngressAccessPolicy` | Defines how access refs are consumed |
| `TIngressAdmissionPolicy` | Defines admission constraints |
| `TIngressBoundaryProfile` | Defines plugin/port compatibility |
| `TIngressListCapacityProfile` | Defines number of ingress candidates |

---

## 16. Implementation Derivation Notes

### 16.1 Candidate Headers

```text
ingress/
    TIngress.hpp
    TIngressState.hpp
    TIngressView.hpp
    TIngressPlacementReport.hpp
    TIngressAccessPolicy.hpp
```

### 16.2 Deferred Decisions

1. Whether `Ingress` is a concrete actor type or a policy-bound template surface.
2. Whether `TIngressAccessRef` lives under `reference_precalculator/` or `ingress/handles/`.
3. Whether producer-facing boundary calls `Ingress` directly or through `communication_bindings/envelope_placement_port`.

---

## 17. Summary

Ingress is the access executor for the intake direction.  
It consumes prepared references; it does not calculate them.  
It places envelopes into slots; it does not assemble or interpret envelopes.  
It moves payload into the engine; it does not dispatch outward.
