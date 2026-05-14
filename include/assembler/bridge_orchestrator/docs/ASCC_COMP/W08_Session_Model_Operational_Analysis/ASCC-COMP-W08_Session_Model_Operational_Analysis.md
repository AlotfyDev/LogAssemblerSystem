# ASCC-COMP-W08 — Session Model Operational Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W08-SESSION-OPS-001` |
| Document Title | Session Model Operational Analysis |
| Repository Root | `include/assembler/bridge_orchestrator/` |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/sessions/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first |
| Status | Formal domain analysis record |
| Companion Matrix | `ASCC-COMP-W08_Session_Operational_Matrix.csv` |

---

## 2. Purpose

This document records the operational analysis for the ASCC session model layer:

```text
include/assembler/bridge_orchestrator/sessions/
```

The goal is to classify session entities by actual operational behavior and to identify how the session layer connects:

```text
bindings/
compatibility/
protocol_state/
protocols/
bridge_core/
facade_layer/
```

---

## 3. Core Finding

`sessions/` is not descriptor-only.

It contains a real header-only session lifecycle model centered on:

```text
sessions/lifecycle/TSession.hpp
```

`TSession` can open, activate, complete, reject, project views/snapshots, produce results, and mutate bridge-visible protocol state.

However, it does not execute protocol steps, orchestrate bridges, invoke endpoints, allocate endpoint resources, or own endpoint lifecycle.

---

## 4. Session Layer Responsibility

The session layer owns:

```text
session identity
session open request
session policy
binding compatibility snapshot
bridge-visible protocol state at session boundary
session lifecycle status
session view/snapshot/result evidence
session activation/completion/rejection transitions
```

The session layer does not own:

```text
protocol stepping
bridge-level run loop
adapter/port invocation
endpoint resource lifecycle
transport/network session
CME slot/container movement
LogAPI content preparation
read-side receiver lifecycle
scheduler/threading/async runtime
```

---

## 5. Session Relationship To Protocols

`TBridgeProtocol` depends on an already open session.

The relationship is:

```text
TSessionOpenRequest
    -> TSession::open()
    -> TSession with protocol_state at session_opening
    -> TBridgeProtocol::declare(open_session, protocol_plan)
    -> TBridgeProtocol::advance_model_step()
```

Therefore:

```text
TSession
    = lifecycle/context holder for bridge-visible protocol state

TBridgeProtocol
    = protocol-level state machine runner over an open session
```

`TSession` is not the protocol executor.

`TBridgeProtocol` is not the session opener.

---

## 6. Session Relationship To Bridge Core

`TBridge` receives a ready protocol, and that protocol contains an open session.

The relationship is:

```text
TSession
    -> TBridgeProtocol
        -> TBridge
```

Bridge Core should not bypass session validity.

A production-ready ASCC component should expose session readiness through managerial facade before consuming bridge operations.

---

## 7. Session Relationship To Facade Layer

After adding:

```text
facade_layer/
```

`sessions/` should not be exposed directly as the component public boundary.

The expected facade relationship is:

```text
Administrative facade
    declares session policy families and session profile capabilities.

Managerial facade
    validates whether a selected binding can open a session.

Consuming facade
    consumes only operations built on an admitted/open session.
```

Candidate facade-facing session entities:

```text
TAsccSessionPolicyCatalogView
TAsccSessionAdmissionPolicy
TAsccSessionReadinessView
TAsccSessionFacadeAdapter
```

---

## 8. Operational Flow

Current session model flow:

```text
TSessionOpenRequest::make()
    -> evaluates binding compatibility through TCompatibilityEvaluator
    -> captures compatibility view

TSession::open(request)
    -> if request is not openable: creates rejected protocol state and rejected session
    -> if request is openable: starts protocol state and transitions idle -> session_opening
    -> returns open session

TSession::activate()
    -> validates session can activate
    -> accepts session_opening stage or transitions to session_opening
    -> sets status active

TSession::complete()
    -> sets status completed
    -> completes protocol_state with success

TSession::reject(reason)
    -> sets status rejected
    -> completes protocol_state with rejected bridge result
```

This is operational lifecycle logic.

It is not merely descriptive.

---

## 9. Missing Production Bindings

The main missing layer is not session runtime itself.

The missing layer is a component-facing admission/readiness layer that binds session lifecycle to facade and Pipeline Composer decisions.

Candidate entities:

```text
TAsccSessionPolicyCatalogView
TAsccSessionAdmissionPolicy
TAsccSessionReadinessView
TSessionBindingReadinessReport
TSessionProtocolBootstrapPolicy
TSessionLifecycleTransitionMatrix
TSessionFacadeResultAdapter
```

---

## 10. Anti-Collapse Rules

### 10.1 Session Must Not Become Protocol Executor

Session may hold protocol state metadata, but protocol stepping belongs to `TBridgeProtocol`.

### 10.2 Session Must Not Become Bridge Core

Session prepares lifecycle context. Bridge Core owns bridge orchestration and budgeted run behavior.

### 10.3 Session Must Not Become Transport Session

ASCC session is a bridge-visible model session, not a network/web/transport session.

### 10.4 Session Must Not Become Endpoint Resource Owner

Endpoint allocation, adapter invocation, and port resources are outside current session scope.

### 10.5 Facade Must Control External Exposure

Pipeline Composer should consume session readiness through facade surfaces, not raw session internals.

---

## 11. Closure Statement

`sessions/` is officially classified as:

```text
Header-only session lifecycle model runtime + session admission/readiness foundation.
```

It is not merely descriptive.

The missing production layer is:

```text
facade-level session admission/readiness/profile binding that prepares an open
session for protocol declaration and bridge operation within an ASCC component.
```
