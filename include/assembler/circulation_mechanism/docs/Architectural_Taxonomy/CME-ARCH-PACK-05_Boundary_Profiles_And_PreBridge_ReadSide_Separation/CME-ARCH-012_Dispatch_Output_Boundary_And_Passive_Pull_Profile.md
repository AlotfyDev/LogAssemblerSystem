# CME-ARCH-012 — Dispatch Output Boundary And Passive Pull Profile

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-012-DOC-001 | Document Title | Dispatch Output Boundary And Passive Pull Profile |
| CME-ARCH-012-DOC-002 | Package | CME-ARCH-PACK-05 |
| CME-ARCH-012-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-012-DOC-004 | Scope Level | Dispatch boundary, output exposure, passive pull, optional push |
| CME-ARCH-012-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-012-DOC-006 | Implementation Direction | C++17, header-only-first, profile-driven, boundary-safe |
| CME-ARCH-012-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-011 |
| CME-ARCH-012-DOC-008 | Related Models | `Dispatcher`, `TDispatchAccessRef`, `TDispatchExposureState`, `TDispatchExposureView`, `BridgeFacingPluginAdapter` |
| CME-ARCH-012-DOC-009 | Primary Rule | Dispatch output is exposure, not final delivery |
| CME-ARCH-012-DOC-010 | Excluded | Bridge protocol execution, read-side retry, receiver acknowledgement, persistence, query, final delivery |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the output boundary of the pre-bridge Circulation Mechanism Engine.

It answers:

```text
How does the Dispatcher expose dispatch-ready payload material to the bridge-facing side
without becoming a bridge, receiver, persistence layer, or message broker?
```

### 2.2 Core Thesis

```text
Dispatcher exposes.
Bridge consumes.
Receiver-side lifecycle starts beyond the pre-bridge CME boundary.
```

### 2.3 Boundary Position

The dispatch output boundary is the last circulation-owned boundary in the pre-bridge profile.

```text
CME residency
→ dispatch readiness
→ reference-precalculated dispatch access
→ Dispatcher output exposure
→ bridge-facing consumption
```

Everything after bridge-facing consumption is outside this document.

---

## 3. Scope

### 3.1 In Scope

1. Dispatcher role at output boundary.
2. Passive pull as default dispatch profile.
3. Optional push as a profile.
4. Bridge-facing adapter relation.
5. Output exposure.
6. Boundary reports.
7. Copy/move non-ownership.
8. Dispatch access reference consumption.
9. Dispatch exposure state.
10. Output boundary invariants.

### 3.2 Out of Scope

1. Bridge protocol.
2. Bridge sessions.
3. Bridge routing.
4. Receiver-side queue/circulation.
5. Receiver acknowledgement.
6. Add-on delivery.
7. Database persistence.
8. Telemetry export.
9. Retry loop.
10. Query lifecycle.

---

## 4. Dispatcher Definition At Boundary

### 4.1 Definition

`Dispatcher` is the final pre-bridge circulation actor that consumes `TDispatchAccessRef` and exposes dispatch-ready material through a boundary-safe projection.

### 4.2 Dispatch Output Responsibility

The dispatcher owns:

1. consuming dispatch references,
2. validating dispatch exposure preconditions,
3. creating passive exposure views,
4. emitting dispatch boundary reports,
5. moving exposure state forward,
6. participating in release/recycle transitions.

### 4.3 Dispatcher Non-Responsibilities

The dispatcher does not own:

1. bridge protocol,
2. bridge session,
3. receiver lifecycle,
4. copy/move semantics after exposure,
5. persistence,
6. final delivery,
7. replay,
8. downstream mutation,
9. read-side retry.

---

## 5. Passive Pull Profile

### 5.1 Profile Name

```text
TPassivePullDispatchProfile
```

### 5.2 Definition

Passive pull means the dispatcher exposes dispatch-ready material and waits for a bridge-facing side to consume or observe the exposure.

### 5.3 Passive Pull Flow

```text
ReferencePrecalculator prepares TDispatchAccessRef.
Dispatcher consumes TDispatchAccessRef.
Dispatcher creates TDispatchExposureView.
Bridge-facing adapter pulls or observes.
Dispatcher transitions exposure state according to release policy.
```

### 5.4 Why Passive Pull Is Default

Passive pull is default because it:

1. preserves CME boundary,
2. avoids bridge protocol ownership,
3. avoids receiver lifecycle ownership,
4. supports single-dispatcher pre-bridge profile,
5. keeps copy/move decision outside CME,
6. prevents CME from becoming a message broker.

### 5.5 Passive Pull Non-Meaning

Passive pull does not mean:

1. bridge has accepted payload,
2. receiver has received payload,
3. persistence occurred,
4. dispatch succeeded end-to-end,
5. final lifecycle ownership transferred to CME.

---

## 6. Optional Push Profile

### 6.1 Profile Name

```text
TPushDispatchProfile
```

### 6.2 Definition

Push dispatch means the dispatcher actively initiates a boundary-facing send action through an approved output adapter.

### 6.3 Optionality Rule

```text
Push is optional.
Push is profile-bound.
Push is not the default identity of CME dispatch.
```

### 6.4 Push Preconditions

A push profile may be valid only if:

1. the output adapter is explicitly bound,
2. the push action remains inside an approved boundary surface,
3. the engine does not own bridge protocol beyond the adapter contract,
4. failure is reported as boundary failure, not downstream lifecycle failure,
5. release/recycle remains state-driven.

### 6.5 Push Non-Meaning

Push dispatch does not mean:

1. CME owns bridge scheduler,
2. CME owns receiver lifecycle,
3. CME owns retry,
4. CME owns persistence,
5. CME can bypass Dispatcher finality,
6. CME becomes a message broker.

---

## 7. Hybrid / Notification Profiles

### 7.1 Hybrid Dispatch Profile

A hybrid profile may combine passive exposure with a notification.

```text
Dispatcher exposes.
Dispatcher notifies.
Bridge still pulls/consumes under its own contract.
```

### 7.2 Notification-Only Profile

A notification-only profile may signal readiness without pushing payload.

### 7.3 Valid Use

These profiles may be useful when bridge integration needs a readiness signal but payload transfer remains bridge-owned.

---

## 8. Bridge-Facing Adapter

### 8.1 Definition

The bridge-facing adapter is the boundary-side consumer of dispatch exposure.

### 8.2 Role

It may:

1. consume a dispatch exposure view,
2. pull through a dispatch access reference,
3. copy or move payload under bridge-side contract,
4. report observation back if profile requires.

### 8.3 Non-Ownership Transfer

The presence of a bridge-facing adapter does not mean:

1. CME owns bridge,
2. bridge owns CME internals,
3. bridge can inspect private container state,
4. final receiver semantics leak into CME.

### 8.4 Allowed Inputs From CME

1. `TDispatchExposureView`,
2. `TDispatchBoundaryReport`,
3. boundary-safe dispatch ref or token if profile allows,
4. read-only payload exposure surface.

### 8.5 Forbidden Inputs

1. raw `TContainer` mutable object,
2. raw `TSlot` mutable object,
3. private slot state,
4. private container state,
5. registry internals,
6. waiting-list internals.

---

## 9. Output Exposure

### 9.1 Definition

Output exposure is the act of making dispatch-ready material available across the dispatch boundary.

### 9.2 Exposure May Include

1. dispatch exposure view,
2. boundary-safe material reference,
3. envelope access projection,
4. dispatch report,
5. time-range metadata if configured.

### 9.3 Exposure Must Not Include

1. mutable container internals,
2. mutable slot internals,
3. registry mutation access,
4. round state mutation access,
5. bridge session ownership.

### 9.4 Exposure Is Not

1. delivery confirmation,
2. persistence proof,
3. final receiver acceptance,
4. bridge protocol completion,
5. downstream record creation.

---

## 10. Copy/Move Semantics Boundary

### 10.1 Rule

```text
Copy/move semantics after dispatch exposure are owned by the bridge-side contract.
```

### 10.2 CME Responsibility

CME ensures:

1. payload is dispatch-ready,
2. ref/exposure is valid,
3. boundary exposure is created,
4. report is emitted,
5. state is updated.

### 10.3 Bridge Responsibility

Bridge determines:

1. copy,
2. move,
3. borrow-like consumption,
4. transfer timing,
5. protocol/session binding,
6. receiver-side placement.

### 10.4 Invariant

```text
CME must not make implementation assumptions about bridge transfer semantics.
```

---

## 11. Dispatch Exposure State

### 11.1 Candidate States

```text
ready
awaiting_dispatch_ref
exposing
passive_exposed
bridge_observed
bridge_consumed
release_pending
closed
boundary_assumption_broken
```

### 11.2 State Meaning

| State | Meaning |
|---|---|
| `ready` | Dispatcher can expose |
| `awaiting_dispatch_ref` | No dispatch ref available |
| `exposing` | Exposure being created |
| `passive_exposed` | Boundary exposure available |
| `bridge_observed` | Bridge observed exposure, if modeled |
| `bridge_consumed` | Bridge consumed exposure, if modeled |
| `release_pending` | Ready for release/recycle policy |
| `closed` | Exposure lifecycle closed |
| `boundary_assumption_broken` | Expected bridge drain did not occur |

---

## 12. Boundary Reports

### 12.1 Required Reports

| Report | Trigger |
|---|---|
| `TDispatchExposureReport` | Exposure created |
| `TPassiveExposureReport` | Passive exposure made available |
| `TBridgePullObservationReport` | Bridge pull observed |
| `TPushDispatchAttemptReport` | Push profile action attempted |
| `TDispatchBoundaryReport` | Boundary-level state change |
| `TBoundaryAssumptionBrokenReport` | Drain/consumption assumption violated |

### 12.2 Report Non-Meaning

Reports do not prove final delivery unless a later bridge/read-side contract explicitly says so.

---

## 13. Invariants

```text
1. Dispatcher is final pre-bridge circulation actor.
2. Dispatch output is exposure, not final delivery.
3. Passive pull is default.
4. Push is optional and profile-bound.
5. Copy/move semantics belong outside CME.
6. Bridge-facing adapter cannot receive mutable container internals.
7. Output exposure must be view/ref/report based.
8. Dispatch release remains state-driven.
9. Dispatch boundary failure is not receiver lifecycle failure.
```

---

## 14. Diagnostics

| Diagnostic | Meaning |
|---|---|
| `DispatchExposureExpired` | Exposure not consumed within profile expectation |
| `BridgeDrainAssumptionBroken` | Bridge-side did not pull/observe as expected |
| `OutputBoundaryBindingMismatch` | Adapter/profile incompatible |
| `PushDispatchFailed` | Optional push failed |
| `MutableInternalExposureViolation` | Boundary attempted to expose internals |
| `CopyMoveOwnershipViolation` | CME attempted to own bridge transfer semantics |

---

## 15. Configuration Profiles

| Profile | Purpose |
|---|---|
| `TPassivePullDispatchProfile` | Default output behavior |
| `TPushDispatchProfile` | Optional active push behavior |
| `THybridDispatchProfile` | Exposure + notification |
| `TDispatchNotificationProfile` | Signal only |
| `TBridgeDrainAssumptionProfile` | Expected bridge drain behavior |
| `TDispatchBoundaryProfile` | Adapter compatibility |
| `TDispatchReleasePolicy` | Release after exposure |

---

## 16. Implementation Derivation Notes

### 16.1 Candidate Header Families

```text
dispatcher/
    TDispatchExposureProfile.hpp
    TPassivePullDispatchProfile.hpp
    TPushDispatchProfile.hpp
    TDispatchExposureView.hpp
    TDispatchBoundaryReport.hpp
    TBoundaryAssumptionBrokenReport.hpp

communication_bindings/circulation_output_plugin_adapter/
    TBridgeFacingDispatchAdapterDescriptor.hpp
    TDispatchOutputBindingView.hpp
```

### 16.2 Deferred Decisions

1. Whether bridge pull observation is required in pre-bridge profile.
2. Whether push dispatch is implemented inside dispatcher or output adapter only.
3. Whether dispatch refs are exposed directly or wrapped by exposure views.
4. Whether `boundary_assumption_broken` triggers read-side recovery or CME diagnostic only.

---

## 17. Summary

The dispatch output boundary is an exposure boundary.  
Passive pull is the default.  
Optional push is a profile.  
CME does not own bridge protocol, bridge transfer semantics, or receiver lifecycle.
