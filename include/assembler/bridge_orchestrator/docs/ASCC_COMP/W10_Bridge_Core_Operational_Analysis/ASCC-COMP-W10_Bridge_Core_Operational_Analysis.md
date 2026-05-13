# ASCC-COMP-W10 — Bridge Core Operational Analysis

## 1. Document Control

| Field | Value |
|---|---|
| Document ID | `ASCC-COMP-W10-BC-OPS-001` |
| Document Title | Bridge Core Operational Analysis |
| Repository Root | `include/assembler/bridge_orchestrator/` |
| Analysed Subdirectory | `include/assembler/bridge_orchestrator/bridge_core/` |
| Internal Namespace | `assembler::communication_context` |
| Language / Implementation Direction | C++17, header-only-first |
| Status | Formal domain analysis record |
| Companion Matrix | `ASCC-COMP-W10_Bridge_Core_Operational_Matrix.csv` |

---

## 2. Purpose

This document records the formal operational analysis for the Bridge Core root subdirectory:

```text
include/assembler/bridge_orchestrator/bridge_core/
```

The analysis exists to prevent a recurring classification mistake:

```text
Header-only file does not imply descriptor-only file.
```

In this codebase, operational model logic may live entirely inside `.hpp` files because the project follows a C++17 header-only-first implementation style.

Therefore, this document classifies each Bridge Core header by actual operational behavior, not by file extension.

---

## 3. Scope

### 3.1 In Scope

This document covers:

1. the operational role of `bridge_core/`,
2. the distinction between Bridge Core model execution and concrete endpoint invocation/composition,
3. the operational classification of Bridge Core headers,
4. current model execution flow,
5. operational gaps,
6. recommended missing components or future waves.

### 3.2 Out of Scope

This document does not implement or design:

1. concrete adapter invocation path,
2. concrete port invocation path,
3. endpoint invocation/composition component,
4. scheduler/thread/async execution policy,
5. Log Level API internals,
6. Circulation Mechanism Engine internals,
7. read-side receiver lifecycle,
8. persistence or telemetry exporters.

Important clarification:

```text
Out of scope does not mean this logic must live outside headers.
In a header-only system, concrete endpoint invocation could also be implemented
as headers/templates/traits.

The current finding is only that this concrete invocation path is not present
inside bridge_core/ today.
```

---

## 4. Core Finding

`bridge_core/` is not a descriptor-only directory.

It contains a real header-only Bridge Core model runtime centered on:

```text
bridge_core/TBridge.hpp
```

The current Bridge Core owns:

```text
model-step orchestration
bounded model execution
bridge status transition
bridge result mapping
declaration preflight checks
read-only evidence production
step reports
frames / views / snapshots / traces
```

The current Bridge Core does not currently contain:

```text
concrete adapter invocation path
concrete port invocation path
binding-to-endpoint invocation composition
payload movement inside CME
LogAPI content preparation
read-side dispatch retry
scheduler / worker pool / async policy
IO / persistence / telemetry
```

The precise architectural statement is:

```text
Bridge Core currently owns header-only Bridge Core model execution.
Bridge Core does not currently contain the header-level concrete endpoint
invocation/composition path that would connect model steps to concrete
adapter/port calls.
```

This is not a distinction between `.hpp` and `.cpp`.

It is a distinction between:

```text
A) model-step advancement already implemented in headers
B) endpoint adapter/port invocation path not yet represented as headers/types
```

---

## 5. Classification Vocabulary

| Classification | Meaning |
|---|---|
| `RUNTIME_OPERATIONAL_MODEL` | Header contains actual model execution or state transition logic |
| `MODEL_LOGIC_EXECUTION_GUARD` | Header enforces execution guard rules such as budget consumption |
| `GUARD_LOGIC` | Header validates declarations/preconditions and returns issues/results |
| `RESULT_LOGIC` | Header provides result factories and operational outcome classification |
| `STATE_TAXONOMY_WITH_HELPERS` | Header defines state vocabulary plus helper functions |
| `READ_ONLY_PROJECTION` | Header exposes safe current-state projection |
| `READ_ONLY_FRAME_LOGIC` | Header exposes current frame evidence and validity helpers |
| `REPORT_LOGIC` | Header records before/after/action evidence |
| `TRACE_EVIDENCE` | Header records trace evidence without telemetry backend |
| `DIAGNOSTIC_VALUE_WITH_FACTORIES` | Header models issues and diagnostic severity without backend ownership |
| `CONFIG_CONTRACT_WITH_FACTORIES` | Header defines execution configuration values and static factory presets |
| `SURFACE_AGGREGATOR` | Header aggregates public surface includes |
| `VALUE_CONTRACT` | Header provides identity/error/value primitives |
| `FORWARDER_ALIAS` | Header forwards to canonical implementation path |
| `DEFERRED_TRAIT_SURFACE` | Header is intentionally deferred pending runtime/contract decision |

---

## 6. Operational Flow

The current model flow is:

```text
TBridge::declare()
    -> TBridgeCorePolicy::check_declaration()
    -> bridge status becomes ready or rejected/failed/exhausted
    -> TBridge::step_model_once()
    -> TBridgeStepBudget::consume_one()
    -> TBridgeProtocol<PlanCapacity>::advance_model_step()
    -> TBridgeCoreResult is produced
    -> frame / view / snapshot / trace / report evidence is available
```

This flow is operational because it mutates bridge model state and consumes bounded steps.

It is not merely descriptive.

The missing layer is not a non-header runtime. The missing layer is a header-level invocation/composition path such as:

```text
TBridgeStepExecutor
TBridgeEndpointInvocation
TBridgeAdapterPortCall
TBridgeConcreteInvocationPolicy
```

Such a layer would be responsible for connecting a bridge/protocol step to concrete adapter/port calls while preserving ASCC boundaries.

---

## 7. File-Level Summary

| File | Operational Judgment |
|---|---|
| `bridge_core/TBridge.hpp` | Core operational model orchestrator |
| `bridge_core/budget/TBridgeStepBudget.hpp` | Execution guard logic; consumes bounded model steps |
| `bridge_core/policies/TBridgeCorePolicy.hpp` | Declaration preflight guard logic |
| `bridge_core/results/TBridgeCoreResult.hpp` | Operational outcome/result logic |
| `bridge_core/status/TBridgeStatus.hpp` | State taxonomy with terminal/runnable helpers |
| `bridge_core/config/TBridgeConfig.hpp` | Model execution configuration contract |
| `bridge_core/views/TBridgeCoreView.hpp` | Safe read-only projection |
| `bridge_core/frames/TBridgeCoreFrame.hpp` | Read-only current model frame |
| `bridge_core/reports/TBridgeCoreStepReport.hpp` | Single-step evidence report |
| `bridge_core/issues/TBridgeCoreIssue.hpp` | Diagnostic issue value and factories |
| `bridge_core/TBridgeCore.hpp` | Aggregate surface, not direct logic |
| `bridge_core/orchestration/TBridge.hpp` | Closed forwarder alias |
| `bridge_core/traits/TBridgeTraits.hpp` | Deferred trait/runtime contract decision |

The detailed row-by-row operational matrix is maintained in:

```text
ASCC-COMP-W10_Bridge_Core_Operational_Matrix.csv
```

---

## 8. Operational Gaps

### 8.1 Concrete Endpoint Invocation Path Gap

Current state:

```text
TBridge advances the bridge/protocol model.
TBridge does not call concrete adapters or ports.
```

Gap:

```text
No header-level concrete endpoint invocation/composition path exists in Bridge Core.
```

This gap does not imply that an implementation must be placed in a `.cpp` file or external runtime.

In this project, the missing component would likely also be header-only and static/profile-driven.

Recommended action:

```text
Add an explicit bridge endpoint invocation boundary only if ASCC is confirmed to own
concrete adapter/port step execution.
```

Candidate component:

```text
TBridgeStepExecutor
TBridgeEndpointInvocation
TBridgeAdapterPortInvocationPolicy
TBridgeExecutionReport
```

Priority: `High`, but only after ASCC ownership is confirmed.

---

### 8.2 Binding / Protocol / Readiness Preflight Gap

Current state:

```text
TBridgeCorePolicy::check_declaration() validates bridge id, config, protocol validity, protocol readiness, and budget.
```

Gap:

```text
It does not yet aggregate W03 participant capabilities, W04 binding composition metadata, or W05 protocol requirements.
```

Recommended action:

```text
Extend readiness/preflight through ASCC-COMP-W06/W07 rather than overloading TBridgeCorePolicy prematurely.
```

Candidate components:

```text
TAsccBridgeReadinessView
TBridgeCoreReadinessPolicy
TAsccCompositionReadinessReport
```

Priority: `High`.

---

### 8.3 Run-Mode Compatibility Gap

Current state:

```text
TBridgeConfig defines run modes and factories.
```

Gap:

```text
No formal compatibility matrix maps run modes to allowed operations and evidence requirements.
```

Recommended action:

```text
Add run-mode compatibility only when bounded run, diagnostic dry run, or endpoint invocation modes require formal gating.
```

Candidate component:

```text
TBridgeRunModeCompatibilityMatrix
```

Priority: `Medium`.

---

### 8.4 Status Transition Matrix Gap

Current state:

```text
TBridgeStatus defines lifecycle vocabulary and helpers.
TBridge performs status mutation internally.
```

Gap:

```text
No standalone transition matrix or transition ownership report exists.
```

Recommended action:

```text
Add status transition matrix if status mutation expands beyond TBridge.
```

Candidate component:

```text
TBridgeStatusTransitionMatrix
TBridgeStatusTransitionReport
```

Priority: `Medium`.

---

### 8.5 Diagnostic Collection Gap

Current state:

```text
Issues, frames, reports, snapshots, and traces exist as value/evidence records.
```

Gap:

```text
No collector, export boundary, issue catalog, or durable diagnostic sink exists.
```

Recommended action:

```text
Keep evidence values in Bridge Core; add collectors/exporters in diagnostics or production hardening layer.
```

Candidate components:

```text
TBridgeFrameCollector
TBridgeTraceCollector
TBridgeCoreIssueCatalog
TBridgeDiagnosticExportBoundary
```

Priority: `Medium`.

---

### 8.6 Traits / Static Profile Gap

Current state:

```text
TBridgeTraits.hpp is deferred by W01 as a bridge runtime/contract decision.
```

Gap:

```text
No static customization trait contract exists for protocol capacity, diagnostics profile, endpoint invocation profile, or evidence policy.
```

Recommended action:

```text
Do not invent traits yet. Define traits only after protocols, bindings, and execution ownership are finalized.
```

Candidate component:

```text
TBridgeTraits
TBridgeStaticProfile
```

Priority: `Medium`.

---

## 9. Anti-Collapse Rules

### 9.1 Bridge Core Must Not Become CME

Bridge Core must not absorb:

```text
slots
containers
rounds
waiting lists
reference precalculation
dispatch exposure ownership
```

These belong to the Circulation Mechanism Engine.

### 9.2 Bridge Core Must Not Become LogAPI

Bridge Core must not absorb:

```text
content parsing
schema handling
metadata injection
timestamp stabilization
envelope assembly
```

These belong to the Log Level API domain.

### 9.3 Bridge Core Must Not Become Read-Side Runtime

Bridge Core must not absorb:

```text
receiver retry
delayed receiver lifecycle
read-side backpressure
final consumer acknowledgement
```

These belong to read-side circulation or receiver-side profiles.

### 9.4 Bridge Core Must Not Become Scheduler By Accident

Bridge Core model execution is bounded by step budget.

If scheduling, threading, or async policy is required later, it must be represented explicitly as a profile/contract, not smuggled into `TBridge`.

```text
thread owner
async loop
worker pool
runtime scheduler
broker
```

---

## 10. Recommended Next Domain Step

The next operational analysis should cover:

```text
include/assembler/bridge_orchestrator/protocols/
```

Reason:

```text
TBridge::step_model_once() delegates its central advancement to
TBridgeProtocol<PlanCapacity>::advance_model_step().
```

Therefore, the next analytical question is:

```text
How much operational logic is inside the protocol model, and what protocol invocation/composition gaps remain?
```

---

## 11. Closure Statement

`bridge_core/` is officially classified as:

```text
Header-only Bridge Core model runtime.
```

It is not merely descriptive.

The missing production layer is not “runtime outside headers”.

The missing production layer is:

```text
header-level concrete endpoint invocation/composition machinery,
if ASCC is supposed to own that machinery.
```

The correct production path is to preserve the current model execution while adding missing readiness, diagnostics, and optional endpoint invocation boundaries only through explicit later waves.
