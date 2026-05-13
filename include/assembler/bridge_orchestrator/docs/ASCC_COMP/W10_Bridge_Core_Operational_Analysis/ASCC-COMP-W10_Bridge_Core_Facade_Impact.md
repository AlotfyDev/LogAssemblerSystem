# ASCC-COMP-W10 — Bridge Core Facade Impact

## 1. Purpose

This document records the impact of introducing:

```text
include/assembler/bridge_orchestrator/facade_layer/
```

on the previously analysed root subdirectory:

```text
include/assembler/bridge_orchestrator/bridge_core/
```

The key conclusion is:

```text
bridge_core/ remains the internal Bridge Core model-runtime implementation layer.
facade_layer/ becomes the component-facing boundary that exposes selected bridge_core capabilities to Pipeline Composer and participants.
```

---

## 2. Core Impact

Before facade introduction, `bridge_core/` could be read as the public operational surface.

After facade introduction, the architectural split is:

```text
facade_layer/
    = component-facing administrative / managerial / consuming boundary

bridge_core/
    = internal Bridge Core model-runtime and evidence implementation
```

This means `bridge_core/` should not be consumed directly by Pipeline Composer as the final public component interface.

Instead, `facade_layer/` wraps, selects, admits, and exposes Bridge Core behavior through controlled surfaces.

---

## 3. Effect On Bridge Core Entities

## 3.1 TBridge

`TBridge` remains the core model runtime object.

It should be used behind:

```text
TAsccConsumingFacade
TAsccConsumingOperationView
TAsccConsumingResult
```

Impact:

```text
TBridge is no longer the final consuming surface.
TBridge is the implementation object used by consuming facade or future executor.
```

---

## 3.2 TBridgeConfig / TBridgeRunMode / TBridgeStepBudget

These remain configuration and execution-control primitives.

They should be exposed through:

```text
TAsccAdministrativeFacade
TAsccComponentProfileId
TAsccComponentDescriptor
TAsccManagerialFacade
TAsccComponentAdmission
```

Impact:

```text
Bridge configuration is no longer simply local bridge setup.
It becomes part of ASCC component profile selection and managerial admission.
```

---

## 3.3 TBridgeCorePolicy

`TBridgeCorePolicy` remains a bridge declaration preflight guard.

It should be wrapped by a facade-level managerial/readiness policy:

```text
TAsccManagerialFacade
TAsccManagerialReadinessView
TAsccComponentAdmission
```

Impact:

```text
TBridgeCorePolicy is not the whole component readiness gate.
It is one internal readiness input.
```

---

## 3.4 Views / Frames / Snapshots / Reports / Traces

These remain Bridge Core evidence entities.

They should be surfaced through consuming and managerial facade outputs.

Impact:

```text
Bridge Core evidence must become facade-consumable evidence.
```

Examples:

```text
TBridgeCoreView
TBridgeCoreFrame
TBridgeCoreStepReport
TBridgeCoreSnapshot
TBridgeCoreTrace
TBridgeCoreIssue
```

should feed:

```text
TAsccManagerialReadinessView
TAsccConsumingOperationView
TAsccConsumingResult
future TAsccFacadeOperationReport
```

---

## 4. Classification Change

The introduction of facade layer changes how Bridge Core files are classified externally.

| Bridge Core Role | Before Facade | After Facade |
|---|---|---|
| `TBridge` | direct operational core | internal model runtime behind consuming facade |
| `TBridgeConfig` | bridge configuration | component profile/admission input |
| `TBridgeCorePolicy` | bridge declaration preflight | managerial readiness input |
| `TBridgeCoreView` | direct read-only view | evidence projected through facade |
| `TBridgeCoreStepReport` | bridge step report | consuming/evidence report input |
| `TBridgeStatus` | bridge lifecycle state | internal state vocabulary exposed only through controlled views |
| `TBridgeId` | bridge instance identity | subordinate identity under ASCC component identity |

---

## 5. New Architectural Rule

```text
Pipeline Composer must interact with ASCC through facade_layer/.
Pipeline Composer must not depend directly on bridge_core/ internals.
```

The only acceptable direct exposure of Bridge Core types is through facade-controlled views, results, profiles, or reports.

---

## 6. Required Follow-up Entities

Facade introduction creates new bridge_core-related obligations:

```text
TAsccBridgeCoreProfileBinding
TAsccBridgeCoreAdmissionPolicy
TAsccBridgeCoreConsumingBinding
TAsccBridgeCoreEvidenceAdapter
TAsccBridgeCoreOperationAdapter
```

These entities are not replacements for Bridge Core.

They are adapter/binding surfaces between:

```text
facade_layer/  <->  bridge_core/
```

---

## 7. Closure Statement

`bridge_core/` remains operational and valuable.

But after facade introduction, it is no longer the public component boundary.

The production-ready shape becomes:

```text
Pipeline Composer
    -> facade_layer/
        -> bridge_core/
```

not:

```text
Pipeline Composer
    -> bridge_core/ internals
```
