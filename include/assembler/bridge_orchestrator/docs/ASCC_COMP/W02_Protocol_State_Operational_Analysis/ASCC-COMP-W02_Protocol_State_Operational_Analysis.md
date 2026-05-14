# ASCC-COMP-W02 — Protocol State Operational Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W02-PSTATE-OPS-001` |
| Document Title | Protocol State Operational Analysis |
| Repository Root | `include/assembler/bridge_orchestrator/` |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/protocol_state/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first |
| Status | Formal domain analysis record |
| Companion Matrix | `ASCC-COMP-W02_Protocol_State_Operational_Matrix.csv` |

---

## 2. Purpose

This document records the operational analysis for the ASCC protocol-state foundation layer:

```text
include/assembler/bridge_orchestrator/protocol_state/
```

The analysis follows the established ASCC pattern:

```text
1. classify existing entities as operational or descriptive;
2. link operational entities to related descriptive/model entities;
3. identify missing operational/support entities;
4. describe facade impact;
5. preserve anti-collapse rules.
```

---

## 3. Core Finding

`protocol_state/` is not just enum vocabulary.

It contains a real mutable protocol-state lifecycle value centered on:

```text
protocol_state/lifecycle/TBridgeProtocolState.hpp
```

`TBridgeProtocolState` applies transitions, updates current/previous stages, maps terminal stages to terminal state, completes bridge results, exposes error/terminal checks, and produces snapshots.

Therefore it is a header-only operational state primitive.

---

## 4. Current Protocol-State Boundary

The current protocol-state layer owns:

```text
canonical bridge-visible stages
canonical terminal states
transition records
mutable bridge-visible protocol state
snapshot projection
result/error terminal completion mapping
```

The current protocol-state layer does not own:

```text
bridge orchestration
protocol plan sequencing
protocol runtime loop
session admission
binding compatibility
adapter/port invocation
endpoint lifecycle
Pipeline Composer admission
facade exposure policy
scheduler/thread/async behavior
persistence/telemetry export
```

The precise statement is:

```text
protocol_state/ owns the bridge-visible lifecycle state primitives used by
sessions and protocols. It does not own bridge/protocol orchestration.
```

---

## 5. Main Entity Categories

| Category | Entities | Operational Meaning |
|---|---|---|
| Mutable state runtime | `TBridgeProtocolState` | Applies transitions, completes results, produces snapshots |
| Stage taxonomy | `TBridgeStage` | Canonical bridge-visible stage vocabulary consumed by plans and transitions |
| Transition descriptor | `TBridgeTransition` | Declares a movement from one stage to another, consumed by state runtime |
| Snapshot evidence | `TBridgeProtocolSnapshot` | Read-only evidence projection of protocol state |
| Terminal-state taxonomy | `TBridgeTerminalState` | Canonical terminal outcome vocabulary independent from downstream completion |
| Missing policy/evidence layer | proposed transition matrix/report/facade adapters | Defines legal transitions, transition evidence, and facade exposure |

---

## 6. Operational Flow

Current protocol-state flow:

```text
TBridgeProtocolState::start(correlation)
    -> initializes idle state with no terminal state

TBridgeTransition::make(from, to, reason)
    -> creates a transition descriptor

TBridgeProtocolState::apply_transition(transition)
    -> rejects if terminal or invalid transition
    -> sets previous_stage
    -> sets current_stage
    -> maps terminal stages to terminal state

TBridgeProtocolState::complete(final_result)
    -> stores final bridge result
    -> maps success/rejected/deferred/fail to terminal stage/state

TBridgeProtocolState::snapshot(family)
    -> creates read-only state evidence
```

This flow is operational because it mutates protocol state.

It is not an endpoint runtime and not a bridge/protocol runner by itself.

---

## 7. Relationship To Sessions

`sessions/` uses protocol state as bridge-visible lifecycle metadata.

Key relationship:

```text
TSession::open(...)
    -> TBridgeProtocolState::start(...)
    -> apply_transition(idle -> session_opening)
```

`TSession::complete()` and `TSession::reject()` call `protocol_state.complete(...)`.

Therefore:

```text
TSession
    owns session lifecycle decisions;
TBridgeProtocolState
    owns bridge-visible protocol-state mutation.
```

---

## 8. Relationship To Protocols

`protocols/` consumes protocol-state primitives to advance a declared protocol plan.

Key relationship:

```text
TBridgeProtocol::advance_model_step()
    -> reads current TBridgeProtocolStep
    -> compares step.from with session.protocol_state.current_stage
    -> applies TBridgeTransition(step.from, step.to, step.step_name)
```

Therefore:

```text
TBridgeProtocol
    owns plan/step progression;
TBridgeProtocolState
    owns current/previous stage mutation and terminal state mapping.
```

---

## 9. Relationship To Bridge Core

Bridge Core does not directly own protocol state internals.

Bridge Core delegates protocol advancement through `TBridgeProtocol`, which itself mutates session-owned `TBridgeProtocolState`.

Relationship:

```text
TBridge
    -> TBridgeProtocol
        -> TSession
            -> TBridgeProtocolState
```

---

## 10. Relationship To Facade Layer

After adding `facade_layer/`, raw protocol-state internals should not be the public Pipeline Composer boundary.

Facade should expose protocol-state evidence through controlled surfaces:

```text
TAsccSessionReadinessView
TAsccProtocolReadinessView
TAsccConsumingResult
future TAsccProtocolStateEvidenceView
```

The facade may use protocol-state evidence to explain readiness and operation outcomes, but it must not expose mutable state directly.

---

## 11. Missing Production Entities

Current protocol-state logic is operational, but lacks several production-support entities:

```text
TBridgeStageTransitionMatrix
TBridgeProtocolStateTransitionReport
TBridgeProtocolStateEvidenceAdapter
TBridgeProtocolStateReadinessView
TBridgeProtocolStateInvariantReport
TBridgeProtocolStateFacadeProjection
```

These do not replace `TBridgeProtocolState`.

They formalize legality, evidence, diagnostics, and facade exposure.

---

## 12. Anti-Collapse Rules

### 12.1 Protocol State Must Not Become Protocol Runtime

Protocol state mutates stage and terminal data.

Protocol runtime owns plan/step sequencing.

### 12.2 Protocol State Must Not Become Session

Session owns session lifecycle and binding compatibility context.

Protocol state owns stage movement inside that lifecycle.

### 12.3 Protocol State Must Not Become Bridge Core

Bridge Core owns bridge-level orchestration and budget.

Protocol state owns only bridge-visible stage state.

### 12.4 Protocol State Must Not Become Endpoint State

Protocol state is communication-context state, not endpoint-private lifecycle or transport state.

### 12.5 Facade Must Not Leak Mutable Protocol State

Facade may expose snapshots, reports, and readiness evidence, not mutable state handles.

---

## 13. Closure Statement

`protocol_state/` is officially classified as:

```text
Header-only bridge-visible protocol-state runtime primitive + state vocabulary/evidence layer.
```

It is not merely descriptive.

The missing production layer is:

```text
formal transition policy, transition evidence, invariant diagnostics, and
facade-safe protocol-state projections.
```
