# ASCC-COMP-W01 — Bridge Carriers Runtime Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W01-CARRIER-RUNTIME-001` |
| Document Title | Bridge Carriers Runtime Analysis |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/bridge_carriers/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first with possible minimal `.cpp` orchestration at Pipeline Composer level |
| Status | Corrected formal analysis record |
| Companion Matrix | `ASCC-COMP-W01_Bridge_Carriers_Runtime_Matrix.csv` |

---

## 2. Purpose

This document corrects the previous interpretation of `bridge_carriers/`.

The corrected rule is:

```text
A carrier value is not carrier flow runtime.

A helper method on a carrier is not enough to classify it as operational runtime.

Carrier runtime exists only when the system can:
    validate carrier use,
    bind carrier to protocol requirements,
    bind carrier to participant roles,
    bind carrier to obligation surfaces,
    record produced/consumed/observed events,
    report carrier-flow evidence,
    and block readiness when required carriers are missing or invalid.
```

---

## 3. Corrected Core Finding

`bridge_carriers/` currently contains typed bridge-visible carrier contracts.

Examples:

```text
TCorrelationToken
TPlacementRequest
TPlacementHandle
TAdmissionResult
TReadinessView
TLoadSignal
TNextDestinationRequest
TCarrierView
```

These are not useless and not merely documentation. They are typed contracts used by protocols, participants, bindings, adapters, ports, readiness, diagnostics, and future invocation paths.

However, they are not sufficient carrier runtime.

The missing production layer is:

```text
carrier runtime above carrier contracts
```

---

## 4. Current Carrier Contracts

The current carrier contracts provide:

```text
opaque correlation
placement request data
opaque placement handle
admission outcome value
participant/port/adapter readiness view
load signal value
next destination request value
carrier diagnostic view
```

They deliberately do not own:

```text
payload storage
carrier routing
protocol requirement satisfaction
adapter or port invocation
CME slot/container/round internals
endpoint-private state
Pipeline Composer topology
```

---

## 5. Required Carrier Runtime

The carrier runtime layer must provide:

```text
TCarrierValidationEngine
TCarrierRequirementSatisfactionEngine
TCarrierFlowRuntime
TCarrierFlowLedger
TCarrierFlowRecord
TCarrierFlowReport
TCarrierProtocolBindingMap
TCarrierObligationResolver
```

This layer does not replace the existing carrier structs.

It operationalizes them.

---

## 6. Relationship To Protocol Requirements

`TProtocolCarrierRequirement` declares what carriers are required, by whom, and in which direction.

The carrier runtime must answer:

```text
Was the required carrier produced?
Was it produced by the expected participant role?
Was it consumed by the expected participant role?
Was the direction correct?
Was the carrier kind correct?
Was the carrier valid for this protocol stage?
```

---

## 7. Relationship To Bindings And Obligations

Bindings map participants and obligation surfaces.

The carrier runtime must link:

```text
TCarrierProtocolBindingMap
    -> TBindingParticipantRoleMap
    -> TBindingObligationSurfaceMap
    -> TCarrierObligationResolver
```

This creates the pre-invocation operational map without executing endpoints.

---

## 8. Relationship To Facade Layer

Facade layer must expose carrier runtime evidence, not raw mutable flow state.

Required facade entities:

```text
TAsccCarrierCatalogView
TAsccCarrierReadinessView
TCarrierFacadeEvidenceAdapter
```

The Pipeline Composer consumes these facade outputs only.

---

## 9. Header-Only And Minimal CPP Clarification

The project is header-only-first, but not `.cpp`-forbidden.

Core carrier contracts, runtime types, policies, and reports may be header-only.

A minimal `.cpp` in Pipeline Composer or smoke/runtime composition is acceptable and may orchestrate configured component instances.

The issue is not `.hpp` versus `.cpp`.

The issue is whether a real carrier runtime exists.

---

## 10. Closure Statement

`bridge_carriers/` should be classified as:

```text
bridge-visible carrier contracts currently
+ missing carrier runtime layer
+ required facade-safe carrier evidence layer
```

The production direction is to add carrier runtime above the existing carrier contracts.
