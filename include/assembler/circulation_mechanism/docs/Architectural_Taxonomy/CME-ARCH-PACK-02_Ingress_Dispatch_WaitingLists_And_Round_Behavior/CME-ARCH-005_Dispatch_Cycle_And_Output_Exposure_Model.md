# CME-ARCH-005 — Dispatch Cycle And Output Exposure Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-005-DOC-001 | Document Title | Dispatch Cycle And Output Exposure Model |
| CME-ARCH-005-DOC-002 | Package | CME-ARCH-PACK-02 |
| CME-ARCH-005-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-005-DOC-004 | Scope Level | Dispatch cycle, passive exposure, bridge-facing access, output boundary |
| CME-ARCH-005-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-005-DOC-006 | Implementation Direction | C++17, header-only-first, profile-driven, single-dispatcher pre-bridge profile |
| CME-ARCH-005-DOC-007 | Depends On | CME-ARCH-000, CME-ARCH-001, CME-ARCH-002, CME-ARCH-003, CME-ARCH-004 |
| CME-ARCH-005-DOC-008 | Related Models | `TDispatchWaitingList`, `RoundManager`, `ReferencePrecalculator`, `TDispatchAccessRef`, `Dispatcher`, `BridgeFacingPluginAdapter` |
| CME-ARCH-005-DOC-009 | Primary Rule | Dispatcher exposes dispatch-ready material through precomputed dispatch references; bridge-side semantics decide copy/move/pull |
| CME-ARCH-005-DOC-010 | Excluded | Bridge protocol execution, final receiver lifecycle, persistence, query, replay, downstream acknowledgement |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the dispatch-side movement cycle of the Circulation Mechanism Engine.

It answers:

```text
How does material leave the pre-bridge circulation engine through a dispatch-facing
exposure model without turning the engine into the bridge, a message broker,
or a final delivery executor?
```

### 2.2 Core Thesis

```text
Dispatcher exposes.
Bridge-facing side consumes.
The engine does not own the final transfer semantics after exposure.
```

### 2.3 Payload Direction

```text
engine → outside
```

The envelope payload moves from circulation-owned residency toward the bridge-facing output boundary.

---

## 3. Scope

### 3.1 In Scope

1. Dispatch-side payload direction.
2. Dispatcher as output exposure authority.
3. Passive exposure default.
4. Optional push dispatch profile as a later profile.
5. Bridge-facing adapter as consumer.
6. `TDispatchAccessRef`.
7. `TDispatchWaitingList`.
8. Dispatching container exposure.
9. Dispatch reports/views.
10. Copy/move semantics boundary.

### 3.2 Out of Scope

1. Bridge orchestration.
2. Bridge session/protocol/channel management.
3. Final receiver behavior.
4. Database/persistence.
5. Thin C ABI passage.
6. Add-on execution.
7. Receiver acknowledgement.
8. Read-side failed-dispatch lifecycle.

---

## 4. Dispatch Boundary Participants

### 4.1 Internal Participant: Dispatcher

| Field | Value |
|---|---|
| Name | `Dispatcher` |
| Role | Final pre-bridge circulation-side output exposure actor |
| Consumes | `TDispatchAccessRef` |
| Provides | passive exposure view / dispatch report |
| Does Not Own | bridge protocol, final receiver, copy/move decision, downstream lifecycle |

### 4.2 Boundary Participant: Bridge-Facing Adapter

| Field | Value |
|---|---|
| Name | `BridgeFacingPluginAdapter` / output binding adapter |
| Role | Consumer of dispatch exposure |
| Consumes | dispatch ref / dispatching container exposure |
| Owns | bridge-side pull/copy/move semantics |
| Does Not Grant | circulation ownership of bridge or receiver |

### 4.3 Output Boundary Rule

```text
Dispatch exposure is a boundary event, not downstream delivery completion.
```

---

## 5. Dispatch Cycle Overview

### 5.1 Precondition Chain

```text
Container becomes dispatch-ready.
RoundManager admits dispatch-eligible container index into TDispatchWaitingList.
ReferencePrecalculator consumes the waiting list and prepares TDispatchAccessRef.
Dispatcher consumes dispatch ref and exposes material to bridge-facing side.
Bridge-facing side pulls/copies/moves under its own contract.
```

### 5.2 Cycle Sequence

| Step | Actor / Structure | Action |
|---:|---|---|
| 1 | `TContainer` | Becomes dispatch candidate |
| 2 | `RoundManager` | Registers container index in dispatch waiting list |
| 3 | `TDispatchWaitingList` | Orders dispatch candidates |
| 4 | `ReferencePrecalculator` | Prepares dispatch access refs |
| 5 | `Dispatcher` | Consumes `TDispatchAccessRef` |
| 6 | `Dispatcher` | Exposes payload/container/slot view to output boundary |
| 7 | `BridgeFacingPluginAdapter` | Pulls or consumes exposure |
| 8 | State Model | Marks exposure consumed/released as appropriate |
| 9 | Moderator | Later resets/recycles the container at safe point |

---

## 6. Passive Exposure Default

### 6.1 Rule

```text
Passive Pull is the default dispatch profile.
```

### 6.2 Meaning

The dispatcher does not push payload by default.  
It exposes a dispatching container / dispatch access reference / output view, then the bridge-facing side pulls.

### 6.3 Why Passive Pull Is Default

1. It prevents the circulation engine from becoming bridge runtime.
2. It lets bridge-side contract own copy/move semantics.
3. It preserves final receiver non-ownership.
4. It keeps the engine continuously moving under its pre-bridge profile.
5. It allows optional push later without making push the core model.

### 6.4 Optional Push Profile

Push may later be modeled as:

```text
TPushDispatchProfile
THybridDispatchProfile
TDispatchNotificationProfile
```

But these are optional profiles, not the core dispatch identity.

---

## 7. `TDispatchAccessRef`

### 7.1 Definition

`TDispatchAccessRef` is a direction-specific access reference that allows the dispatcher or bridge-facing side to access dispatch-ready material selected by the engine.

### 7.2 Owned By

```text
ReferencePrecalculator owns calculation.
Dispatcher owns exposure.
Bridge-facing adapter owns post-exposure transfer semantics.
```

### 7.3 Must Not Be Used For

1. Ingress.
2. Producer-side placement.
3. Long-lived downstream handle.
4. Persistence proof.
5. Receiver acknowledgement.
6. Direct bridge protocol ownership.

### 7.4 Validity Requirements

| Requirement | Meaning |
|---|---|
| Valid registry index | Container still exists |
| Valid container state | Container remains dispatch-ready/exposed |
| Valid slot state | Slot contains dispatch-ready envelope |
| Valid round scope | Dispatch round still allows exposure |
| Valid boundary profile | Output binding is compatible |

---

## 8. Dispatch Waiting List Role

### 8.1 Definition

`TDispatchWaitingList` orders container registry indices that are eligible for dispatch.

### 8.2 Ordering

Default:

```text
FIFO
```

Optional enhancement:

```text
FIFO + container time range ordering
```

### 8.3 Does Not Mean

1. Bridge has accepted payload.
2. Receiver has received payload.
3. Container can be reset immediately.
4. Downstream delivery is complete.

---

## 9. Dispatcher State Model

### 9.1 Candidate States

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

### 9.2 State Meaning

| State | Meaning |
|---|---|
| `ready` | Dispatcher can consume refs |
| `awaiting_dispatch_ref` | No current dispatch ref |
| `exposing` | Dispatcher is preparing output exposure |
| `passive_exposed` | Exposure available to bridge-facing side |
| `bridge_consumed` | Bridge-side consumer observed/pulled exposure if modeled |
| `release_pending` | Awaiting release/recycle safe transition |
| `closed` | Dispatch surface closed |
| `boundary_assumption_broken` | Bridge drain assumption failed or timed out |

---

## 10. Copy / Move Semantics Boundary

### 10.1 Rule

```text
Copy/move semantics after dispatch exposure belong to the bridge-side contract,
not the pre-bridge circulation engine.
```

### 10.2 Circulation Responsibility

The engine provides:

1. dispatch-ready reference,
2. output exposure view,
3. dispatch report,
4. state transition evidence.

### 10.3 Bridge Responsibility

The bridge-side participant decides:

1. whether to copy or move,
2. how to bind to receiver side,
3. how to manage bridge protocol/session,
4. what acknowledgement model exists.

### 10.4 Non-Ownership

Dispatch exposure does not mean:

1. bridge success,
2. receiver success,
3. persistence,
4. query readiness,
5. downstream lifecycle transfer proof.

---

## 11. Invariants

### 11.1 Core Invariants

```text
1. Dispatcher consumes dispatch references only.
2. Dispatcher does not calculate references.
3. Dispatcher does not scan containers.
4. Dispatch direction is engine → outside.
5. Passive pull is default.
6. Push is optional profile, not core.
7. Bridge-side transfer semantics are outside CME.
8. Dispatch exposure is not downstream acceptance.
```

### 11.2 Boundary Invariants

```text
1. Dispatcher is final pre-bridge circulation actor.
2. Output boundary is not final receiver.
3. TDispatchWaitingList is not a delivery queue.
4. TDispatchAccessRef is not a downstream handle.
```

---

## 12. Views

| View | Purpose |
|---|---|
| `TDispatchExposureView` | Exposed dispatch material |
| `TDispatchReadyView` | Dispatch readiness projection |
| `TDispatcherView` | Dispatcher state |
| `TDispatchWaitingListView` | Ordered dispatch candidates |
| `TBridgeDrainObservationView` | Optional bridge-side observation |

---

## 13. Reports

| Report | Trigger |
|---|---|
| `TDispatchExposureReport` | Exposure created |
| `TPassiveExposureReport` | Passive exposure published |
| `TBridgePullObservationReport` | Bridge pull observed |
| `TDispatchBoundaryReport` | Output boundary event |
| `TDispatcherInvariantReport` | Dispatcher invariant violation |
| `TPushDispatchAttemptReport` | Optional push attempt |

---

## 14. Failure / Diagnostic Conditions

| Condition | Classification |
|---|---|
| `InvalidDispatchRef` | reference validity violation |
| `SlotNotDispatchReady` | slot-state mismatch |
| `ContainerNotDispatchReady` | container-state mismatch |
| `RoundClosedForDispatch` | round-state mismatch |
| `BridgeDrainAssumptionBroken` | boundary/profile condition |
| `DispatchExposureExpired` | exposure lifecycle condition |
| `PushDispatchFailed` | optional push-profile condition |

---

## 15. Configuration Profiles

| Profile | Purpose |
|---|---|
| `TDispatchCycleProfile` | Direction and single-dispatcher behavior |
| `TDispatchExposurePolicy` | Passive/push/hybrid |
| `TBridgeDrainAssumptionProfile` | Expected bridge drain behavior |
| `TDispatchReleasePolicy` | Release/recycle relationship |
| `TDispatchBoundaryProfile` | Output boundary compatibility |

---

## 16. Implementation Derivation Notes

### 16.1 Candidate Headers

```text
dispatcher/
    TDispatcher.hpp
    TDispatcherState.hpp
    TDispatchExposureView.hpp
    TDispatchExposureReport.hpp
    TDispatchExposurePolicy.hpp
```

### 16.2 Deferred Decisions

1. Whether `BridgePullObservationReport` belongs in dispatcher or communication bindings.
2. Whether push dispatch is implemented in CME or only as external boundary adapter behavior.
3. Whether dispatch release is triggered by bridge observation or round closure in the pre-bridge profile.

---

## 17. Summary

Dispatch moves payload out of the engine.  
Dispatcher exposes; it does not own bridge transfer semantics.  
The default behavior is passive pull.  
Copy/move belongs to bridge-side contract, not the circulation engine.
