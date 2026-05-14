# ASCC-COMP-W09 — Protocol To Bridge Core Relationship

## 1. Purpose

This document explains the relationship between:

```text
include/assembler/bridge_orchestrator/protocols/
```

and:

```text
include/assembler/bridge_orchestrator/bridge_core/
```

The purpose is to prevent collapsing the protocol model into the bridge core, or treating the bridge core as if it owns protocol internals.

---

## 2. Core Relationship

```text
TBridge
    owns bridge-level orchestration.

TBridgeProtocol
    owns protocol-level state advancement.
```

The link is:

```text
TBridge::step_model_once()
    -> TBridgeProtocol<PlanCapacity>::advance_model_step()
```

---

## 3. Bridge Core Responsibilities

Bridge Core owns:

```text
bridge identity
bridge configuration
bridge run mode
step budget
bridge status
bridge result mapping
bridge-level issue handling
bridge frame/view/snapshot/report/trace evidence
bounded bridge model run
```

Bridge Core must not own:

```text
protocol plan construction internals
protocol step transition internals
participant/carrier/binding requirement cataloging
step-to-requirement binding
endpoint invocation from protocol steps unless explicitly introduced as a separate bridge/protocol invocation boundary
```

---

## 4. Protocol Model Responsibilities

Protocol model owns:

```text
protocol identity
protocol kind
protocol plan
current step index
protocol status
protocol result
session-bound protocol state advancement
protocol view/frame/trace evidence
protocol requirement catalogs
protocol requirement reports
```

Protocol model must not own:

```text
bridge-level budget
bridge-level run loop
bridge-level result policy
Pipeline Composer admission
facade exposure policy
endpoint invocation unless represented through explicit step binding/invocation descriptors
```

---

## 5. Model Execution Flow

```text
TBridge::declare()
    -> validates bridge id/config/protocol readiness
    -> produces bridge ready/rejected state

TBridge::step_model_once()
    -> validates bridge status and budget
    -> consumes one bridge step budget
    -> delegates to TBridgeProtocol::advance_model_step()

TBridgeProtocol::advance_model_step()
    -> activates protocol if ready
    -> reads current protocol step
    -> validates session stage alignment
    -> applies TBridgeTransition
    -> updates protocol/session state
    -> returns protocol result

TBridge
    -> maps protocol result to bridge core result/status
    -> records bridge issue/report/evidence
```

---

## 6. Evidence Flow

Protocol evidence:

```text
TBridgeProtocolView
TBridgeProtocolFrame
TBridgeProtocolTrace
TBridgeProtocolResult
TProtocolRequirementReport
```

feeds Bridge Core evidence:

```text
TBridgeCoreFrame
TBridgeCoreTrace
TBridgeCoreStepReport
TBridgeCoreResult
TBridgeCoreSnapshot
```

Bridge Core evidence then feeds facade evidence:

```text
TAsccManagerialReadinessView
TAsccConsumingOperationView
TAsccConsumingResult
future TAsccFacadeOperationReport
```

---

## 7. Requirement Flow

Protocol requirements:

```text
TProtocolRequirementSet
TProtocolParticipantRequirement
TProtocolCarrierRequirement
TProtocolBindingRequirement
TProtocolRequirementMatchResult
TProtocolRequirementReport
```

should feed managerial facade readiness before a protocol is admitted into an ASCC component profile.

They should not be consumed directly by `TBridge::step_model_once()`.

The bridge should receive an already-declared and ready `TBridgeProtocol`.

---

## 8. Missing Middle Layer

The missing middle layer between protocol descriptors and concrete operation is:

```text
TProtocolStepRequirementBinding
TProtocolStepObligationBinding
TProtocolStepInvocationDescriptor
TProtocolStepExecutionPolicy
```

These would connect:

```text
TBridgeProtocolStep
    -> protocol requirement entries
    -> participant capabilities
    -> binding metadata
    -> adapter/port obligation surfaces
```

without overloading `TBridgeProtocolStep` or `TBridge`.

---

## 9. Facade Impact

After the introduction of:

```text
facade_layer/
```

neither `bridge_core/` nor `protocols/` should be the direct public boundary for Pipeline Composer.

The production relationship is:

```text
Pipeline Composer
    -> facade_layer/
        -> bridge_core/
            -> protocols/
                -> protocol_state/
```

This preserves:

```text
component-facing facade
bridge-level orchestration
protocol-level state advancement
protocol-state primitives
```

as separate responsibilities.

---

## 10. Closure Statement

The protocol model is a real operational model runtime.

The bridge core is a real operational bridge model runtime.

They are connected but not interchangeable.

The next production step is not to merge them, but to add the missing binding/admission surfaces that make their relationship composable through the ASCC facade.
