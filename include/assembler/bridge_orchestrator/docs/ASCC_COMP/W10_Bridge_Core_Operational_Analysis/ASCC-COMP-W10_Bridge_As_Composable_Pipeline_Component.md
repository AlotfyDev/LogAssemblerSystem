# ASCC-COMP-W10 — Bridge / Communication Context As A Composable Pipeline Component

## 1. Purpose

This document records an architectural clarification:

```text
Bridge Orchestrator / Communication Context is internally a system,
but externally it must be deliverable as one composable operational component
inside a higher-level Pipeline Composer layer.
```

The higher layer is expected to compose data-trading pipelines between a writer side and a receiver side.

The Bridge Orchestrator must therefore be prepared not merely as an internal subsystem, but as a configurable, readiness-reporting, operational unit that can be admitted into a pipeline composition.

---

## 2. Core Thesis

```text
ASCC / Communication Context
    = internally structured bridge orchestration system
    = externally composable operational component
```

It should be supplied upward as:

```text
configured component
+ declared capabilities
+ binding requirements
+ protocol requirements
+ readiness evidence
+ diagnostics evidence
+ execution/operation entry surface
```

The Pipeline Composer layer decides:

```text
which components participate
how writer-side and receiver-side components are connected
whether ASCC is used in a given pipeline profile
which ASCC profile/configuration is selected
how readiness gates are evaluated
```

---

## 3. Relationship To Current Domains

The same rule applies to all current major domains:

```text
Log Level API
Circulation Mechanism Engine
Communication Context / Bridge Orchestrator
Read-side / Receiver-side components
Policy System
Add-on packs
```

Each domain may be internally complex.

But at the Pipeline Composer layer, each domain must expose a composable component contract.

---

## 4. ASCC External Delivery Shape

ASCC should eventually be delivered to the Pipeline Composer as a component with the following surface categories.

| Surface | Meaning |
|---|---|
| Identity Surface | ASCC component identity, version, profile id |
| Configuration Surface | Bridge config, run mode, budget, invocation profile if enabled |
| Capability Surface | What ASCC can mediate, observe, diagnose, and require |
| Binding Surface | Supported handoff styles and ownership boundaries |
| Protocol Surface | Supported protocol kinds and requirement sets |
| Readiness Surface | Whether ASCC is ready to be included in a pipeline |
| Operational Entry Surface | Header-level entry points for model execution and optional invocation execution |
| Evidence Surface | Views, reports, traces, snapshots, diagnostics |
| Failure Surface | Rejection, failure, exhaustion, incompatibility, deferred readiness |

---

## 5. Pipeline Composer Ownership

The Pipeline Composer owns pipeline-level decisions:

```text
pipeline topology
writer-side to receiver-side path
component selection
component ordering
cross-component compatibility
pipeline profile
component admission
pipeline readiness gate
pipeline-level lifecycle
```

ASCC must not own these pipeline-level decisions.

ASCC only declares and executes its own component behavior once configured and admitted.

---

## 6. ASCC Ownership Inside Its Component Boundary

ASCC may own:

```text
bridge identity
bridge configuration
bridge model-step execution
protocol model advancement
session/protocol/bridge evidence
binding/protocol readiness evaluation
participant/capability compatibility evidence
optional endpoint invocation path if explicitly assigned to ASCC
```

ASCC must not own:

```text
LogAPI content parsing
CME slot/container movement
receiver-side retry lifecycle
pipeline-wide scheduling
pipeline-wide backpressure
component selection for the pipeline
policy governance execution
```

---

## 7. Consequence For Bridge Core Analysis

The previous Bridge Core analysis must be read with this external component view.

When the analysis says that `bridge_core/` lacks a concrete endpoint invocation/composition path, the production interpretation is:

```text
ASCC is not yet fully packaged as a ready-to-run composable pipeline component
for scenarios where the Pipeline Composer expects ASCC to perform adapter/port
invocation as part of bridge operation.
```

It does not mean:

```text
runtime must live outside headers
or ASCC cannot contain operational logic
or Bridge Core is merely descriptive
```

Rather, it means:

```text
The existing header-only model execution must be extended with a component-facing
operational entry contract if ASCC is to be admitted by Pipeline Composer as an
operational bridge component.
```

---

## 8. Required Component-Readiness Categories For ASCC

To become a composable pipeline component, ASCC must provide or expose:

### 8.1 Component Identity

Candidate entities:

```text
TAsccComponentId
TAsccComponentVersion
TAsccComponentProfileId
```

### 8.2 Component Configuration

Candidate entities:

```text
TAsccComponentConfig
TBridgeConfig
TBridgeEndpointInvocationProfile
TBridgeStaticProfile
```

### 8.3 Component Capability Declaration

Candidate entities:

```text
TParticipantCapabilitySet
TProtocolCapabilitySet
TBindingCompositionMetadata
TAsccBridgeCapabilityView
```

### 8.4 Component Requirements

Candidate entities:

```text
TProtocolRequirementSet
TProtocolCarrierRequirement
TProtocolBindingRequirement
TBindingCompositionRequirement
```

### 8.5 Component Readiness

Candidate entities:

```text
TAsccBridgeReadinessView
TBridgeCoreReadinessPolicy
TAsccCompositionReadinessReport
TAsccReadinessEvidenceRef
```

### 8.6 Component Operation

Candidate entities:

```text
TBridge
TBridgeStepExecutor
TBridgeEndpointInvocation
TBridgeAdapterPortInvocationPolicy
```

### 8.7 Component Evidence

Candidate entities:

```text
TBridgeCoreView
TBridgeCoreFrame
TBridgeCoreSnapshot
TBridgeCoreStepReport
TBridgeExecutionReport
TBridgeCoreRunReport
TBridgeCoreTrace
TBridgeCoreIssue
```

---

## 9. Pipeline Composer Contract View

From the Pipeline Composer perspective, ASCC should answer these questions:

| Question | Required ASCC Surface |
|---|---|
| What are you? | Component identity/version/profile |
| What can you do? | Capability view |
| What do you require? | Protocol/binding/participant requirements |
| How are you configured? | Component config / bridge config |
| Are you ready? | Readiness view/report |
| How do I run you? | Operational entry surface |
| What happened? | Reports/traces/snapshots/issues |
| Why can you not run? | Readiness issues / gap reports |

---

## 10. Anti-Collapse Rule

The Pipeline Composer must not be collapsed into ASCC.

ASCC must be composable by the Pipeline Composer, not become the composer itself.

```text
ASCC prepares and runs bridge/communication behavior.
Pipeline Composer assembles ASCC with other components into a data-trading pipeline.
```

---

## 11. Production Direction

The practical direction is:

```text
1. Keep current bridge_core model runtime.
2. Continue analysing protocols/ and bindings/.
3. Identify the exact ASCC component contract needed by Pipeline Composer.
4. Add component readiness views and reports.
5. Add endpoint invocation path only if ASCC is confirmed to own it.
6. Expose ASCC as a configured composable component, not as a hidden internal subsystem.
```

---

## 12. Closure Statement

ASCC should be treated as:

```text
A configurable, readiness-reporting, operational communication component
prepared for admission into a higher-level Pipeline Composer.
```

This clarification changes the meaning of operational gaps:

```text
A gap is not merely an internal missing class.
A gap is a missing part of the component contract needed for Pipeline Composer
admission, configuration, operation, or evidence.
```
