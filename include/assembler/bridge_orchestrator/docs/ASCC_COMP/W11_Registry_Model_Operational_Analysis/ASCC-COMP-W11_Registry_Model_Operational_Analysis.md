# ASCC-COMP-W11 — Registry Model Operational Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W11-REG-OPS-001` |
| Document Title | Registry Model Operational Analysis |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/registries/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first |
| Status | Formal domain analysis record |
| Companion Matrix | `ASCC-COMP-W11_Registry_Operational_Matrix.csv` |

---

## 2. Purpose

This document records the operational analysis for the ASCC registry model layer:

```text
include/assembler/bridge_orchestrator/registries/
```

The goal is to classify registry entities by actual behavior and identify the support entities needed to expose registries safely through `facade_layer/`.

---

## 3. Core Finding

`registries/` is not descriptor-only.

It contains header-only bounded registry logic centered on:

```text
TBoundedRegistry
TRegistryEntry
typed registries
TCommunicationContextRegistrySet
```

These entities register values, reject invalid insertions, perform lookup, expose snapshots, and maintain status evidence.

They are operational catalog/evidence containers, but they must not become service locators, dependency injection containers, endpoint invokers, brokers, schedulers, persistence engines, or pipeline composers.

---

## 4. Current Registry Boundary

The registry layer owns:

```text
bounded catalog storage
entry wrapping and status
lookup results
registry snapshots
typed registries for channels/bindings/sessions/protocols/bridges
grouped registry set
```

The registry layer does not own:

```text
runtime endpoint resolution
adapter/port invocation
pipeline composition
global singleton ownership
dynamic service location
scheduler/worker ownership
persistence/telemetry export
policy governance semantics
```

---

## 5. Relationship To Other ASCC Domains

```text
bindings/     -> TBindingRegistry
sessions/     -> TSessionRegistry
protocols/    -> TBridgeProtocolRegistry
bridge_core/  -> TBridgeRegistry
channels/     -> TChannelRegistry
facade_layer/ -> registry catalog/readiness/evidence adapters
```

A registry should provide evidence that a model entity exists and is usable. It should not execute that entity.

---

## 6. Facade Layer Impact

After adding `facade_layer/`, registry internals should not be consumed directly by Pipeline Composer.

Needed facade surfaces:

```text
TAsccRegistryCatalogView
TAsccRegistryReadinessView
TAsccRegistryEvidenceAdapter
TAsccRegistryAdmissionPolicy
```

These expose catalog/readiness/evidence without leaking mutable registry entries or turning registries into service locators.

---

## 7. Missing Production Entities

The following entities are needed:

```text
TRegistryAdmissionPolicy
TRegistryReadinessReport
TRegistrySetReadinessReport
TRegistryFacadeProjection
TAsccRegistryCatalogView
TAsccRegistryReadinessView
TAsccRegistryEvidenceAdapter
TAsccRegistryAdmissionPolicy
```

---

## 8. Anti-Collapse Rules

1. Registry must not become service locator.
2. Registry must not become Pipeline Composer.
3. Registry must not invoke endpoints.
4. Registry must not own persistence/telemetry.
5. Registry must expose snapshots/reports through facade-safe adapters.
6. Registry entry status is catalog status, not endpoint lifecycle status.

---

## 9. Closure Statement

`registries/` is officially classified as:

```text
Header-only bounded registry runtime/evidence layer.
```

It is not merely descriptive, and it is not an execution scheduler or endpoint service locator.

The missing production layer is:

```text
registry admission/readiness/evidence surfaces and facade-safe catalog projections.
```
