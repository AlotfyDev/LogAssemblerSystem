# ASCC-COMP-W09 — Protocol Model Operational Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W09-PROTO-OPS-001` |
| Document Title | Protocol Model Operational Analysis |
| Repository Root | `include/assembler/bridge_orchestrator/` |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/protocols/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first |
| Status | Formal domain analysis record |
| Companion Matrix | `ASCC-COMP-W09_Protocol_Operational_Matrix.csv` |

---

## 2. Purpose

This document records the operational analysis for the ASCC protocol model layer:

```text
include/assembler/bridge_orchestrator/protocols/
```

The goal is to distinguish between:

```text
protocol model runtime
protocol plan / step descriptors consumed by runtime
protocol requirements and readiness descriptors
protocol evidence surfaces
missing step-to-obligation / step-to-invocation binding entities
```

The analysis follows the same method used for `bridge_core/`: header-only files are classified by actual behavior, not by extension.

---

## 3. Core Finding

`protocols/` is not descriptor-only.

It contains a real header-only protocol model runtime centered on:

```text
protocols/common/TBridgeProtocol.hpp
```

`TBridgeProtocol` owns protocol-level state advancement over an open session and a declared protocol plan.

It activates the protocol, consumes the current step, applies a protocol-state transition, updates protocol/session status, and produces protocol result/evidence.

---

## 4. Current Protocol Runtime Boundary

The current protocol layer owns:

```text
protocol identity
protocol kind
protocol plan
current step index
protocol status
protocol result
session-bound protocol state advancement
protocol view/frame/trace/result evidence
```

The current protocol layer does not contain:

```text
adapter invocation
port invocation
carrier movement
endpoint callback/closure
binding-to-call execution
scheduler / async / worker ownership
LogAPI internals
CME internals
receiver lifecycle
```

The precise statement is:

```text
Protocols currently own header-only protocol model execution.
Protocols do not currently contain the header-level step-to-obligation or
step-to-endpoint invocation binding that maps protocol steps to concrete
adapter/port calls.
```

---

## 5. Protocols And Bridge Core Relationship

`bridge_core/TBridge.hpp` delegates its central model advancement to:

```text
TBridgeProtocol<PlanCapacity>::advance_model_step()
```

Therefore:

```text
TBridge
    = bridge-level orchestrator and bounded run owner

TBridgeProtocol
    = protocol-level state machine runner
```

`TBridge` does not replace `TBridgeProtocol`.

`TBridgeProtocol` does not replace `TBridge`.

---

## 6. Main Entity Categories

| Category | Entities | Operational Meaning |
|---|---|---|
| Protocol model runtime | `TBridgeProtocol` | Activates and advances protocol state over a session |
| Protocol plan descriptors with bounded logic | `TBridgeProtocolPlan` | Holds ordered steps, validates continuity, supplies default plans |
| Protocol step descriptors | `TBridgeProtocolStep` | Declares stage-to-stage step consumed by runtime |
| Protocol status/result/view/frame/trace | `TBridgeProtocolStatus`, `TBridgeProtocolResult`, `TBridgeProtocolView`, `TBridgeProtocolFrame`, `TBridgeProtocolTrace` | Evidence and state vocabulary |
| Protocol requirements | `TProtocolRequirementSet`, `TProtocolCarrierRequirement`, `TProtocolParticipantRequirement`, `TProtocolBindingRequirement` | Managerial/readiness inputs |
| Protocol requirement evidence | `TProtocolRequirementMatchResult`, `TProtocolRequirementReport` | Readiness/matching reports |
| Missing binding layer | Proposed step binding/invocation entities | Maps protocol step to requirements, obligations, adapter/port calls, and evidence |

---

## 7. Operational Flow

Current protocol model flow:

```text
TBridgeProtocol::declare()
    -> validates protocol id, open session, valid plan, and first step alignment
    -> protocol status becomes ready or rejected
    -> TBridgeProtocol::advance_model_step()
    -> activates if ready
    -> reads current TBridgeProtocolStep
    -> checks session.protocol_state.current_stage == step.from
    -> applies TBridgeTransition(step.from, step.to, step.step_name)
    -> increments current_step_index
    -> completes / fails / remains active
    -> produces TBridgeProtocolResult
```

This is real operational model logic.

It is not merely descriptive.

---

## 8. Requirement Layer Role

`protocols/requirements/` declares what a protocol requires from participants, carriers, and bindings.

Examples include:

```text
content_provider produces placement_request
receiver_provider consumes placement_request
receiver_provider produces placement_handle
content_provider consumes placement_handle
envelope_placement requires bridge_mediated one_to_one binding with session/bridge/protocol
```

This requirement layer does not execute protocol steps.

It is a managerial/readiness input for ASCC admission and Pipeline Composer compatibility checks.

---

## 9. Missing Operational Binding Layer

The main production gap is not the absence of protocol runtime.

The main production gap is the absence of a layer that binds:

```text
TBridgeProtocolStep
    + TProtocolRequirementSet
    + TBindingCompositionMetadata
    + TParticipantCapabilitySet
    + TPluginAdapter / TPort contracts
```

to:

```text
an executable or invocable protocol-step obligation.
```

Candidate entities:

```text
TProtocolStepRequirementBinding
TProtocolStepObligationBinding
TProtocolStepInvocationDescriptor
TProtocolStepExecutionPolicy
TProtocolStepEvidenceRequirement
TProtocolPlanReadinessReport
```

These are not replacements for `TBridgeProtocolStep`.

They are binding entities between the existing descriptive/model layer and any future operational invocation layer.

---

## 10. Facade Layer Impact

After adding:

```text
facade_layer/
```

`protocols/` should not be exposed directly to Pipeline Composer as raw internals.

Instead:

```text
Administrative facade
    exposes supported protocol catalogs and protocol profiles.

Managerial facade
    evaluates protocol readiness and requirement matching.

Consuming facade
    consumes admitted protocol operation through bridge/protocol operation entry points.
```

Candidate facade-facing protocol entities:

```text
TAsccProtocolCatalogView
TAsccSupportedProtocolSet
TAsccProtocolProfileCatalog
TAsccProtocolAdmissionPolicy
TAsccProtocolReadinessView
TAsccProtocolRequirementFacadeAdapter
```

---

## 11. Anti-Collapse Rules

### 11.1 Protocol Model Must Not Become Bridge Core

The protocol model advances protocol/session state.

Bridge Core owns bridge-level orchestration and step budget.

### 11.2 Protocol Requirement Catalog Must Not Execute

Requirement entities declare participant/carrier/binding requirements.

They must not invoke endpoints or move carriers.

### 11.3 Protocol Step Must Not Become Endpoint Callback

`TBridgeProtocolStep` declares stage-to-stage movement.

If invocation is needed, it must be represented by a separate step binding or invocation descriptor.

### 11.4 Facade Must Control External Exposure

Pipeline Composer should consume protocol capabilities through facade surfaces, not raw protocol internals.

---

## 12. Closure Statement

`protocols/` is officially classified as:

```text
Header-only protocol model runtime + protocol requirement/readiness layer.
```

It is not merely descriptive.

The missing production layer is:

```text
header-level protocol step binding to obligations, requirements, and optional
adapter/port invocation machinery.
```
