# CME-ARCH-PACK-02 — Ingress, Dispatch, Waiting Lists, And Round Behavior

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-02` |
| Package Name | Ingress, Dispatch, Waiting Lists, And Round Behavior |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | Cycle behavior, payload direction, waiting-list participation, round management, ingress placement, dispatch exposure |
| Implementation Direction | C++17, header-only-first, static/profile-driven, single-producer/single-dispatcher pre-bridge profile |

## 2. Package Purpose

This package specifies the two primary movement cycles inside the Circulation Mechanism Engine:

```text
Ingress / Container-Providing Cycle:
    payload envelope moves from outside the engine into a slot inside a TContainer.

Dispatch / Output Exposure Cycle:
    payload envelope moves from inside the engine toward the bridge-facing output boundary.
```

The package also specifies how `RoundManager`, `TIngressWaitingList`, and `TDispatchWaitingList` coordinate container eligibility and movement without turning the engine into a message broker, bridge runtime, or final delivery owner.

## 3. Documents

```text
CME-ARCH-004_Ingress_Cycle_And_Container_Providing_Model.md
CME-ARCH-005_Dispatch_Cycle_And_Output_Exposure_Model.md
CME-ARCH-006_Round_Manager_And_Waiting_List_Model.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-004_ingress_sequence.mmd
diagrams/CME-ARCH-005_dispatch_sequence.mmd
diagrams/CME-ARCH-006_round_waiting_list_stateflow.mmd
diagrams/CME-ARCH-006_fifo_time_range_ordering.mmd
```

## 5. Package-Level Rules

### 5.1 Payload Direction Rule

```text
Ingress moves payload into the engine.
Dispatch moves payload out of the engine.
```

### 5.2 Waiting List Rule

```text
Waiting lists order eligible container registry indices.
They do not store envelopes, containers, or bridge delivery material.
```

### 5.3 Round Manager Rule

```text
RoundManager admits qualified containers into the proper waiting list based on state/readiness.
It does not calculate slot references, create containers, reset containers, or execute bridge handoff.
```

### 5.4 Boundary Rule

```text
The pre-bridge circulation engine ends at output exposure.
Bridge-side copy/move/pull semantics remain outside this package.
```
