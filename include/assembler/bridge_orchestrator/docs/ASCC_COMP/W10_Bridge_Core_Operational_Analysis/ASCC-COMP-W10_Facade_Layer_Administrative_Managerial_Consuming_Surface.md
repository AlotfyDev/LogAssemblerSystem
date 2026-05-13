# ASCC-COMP-W10 — Facade Layer: Administrative, Managerial, And Consuming Surfaces

## 1. Purpose

This document records a domain-wide obligation for the Bridge Orchestrator / Communication Context domain:

```text
Every major Log Assembler System domain must expose a facade layer.

For ASCC / Communication Context, that facade layer must distinguish:
    1. Administrative Surface
    2. Managerial Surface
    3. Consuming Surface
```

The facade layer is necessary because ASCC is not merely an internal folder tree. It is expected to become a composable operational component admitted into a higher-level Pipeline Composer.

Therefore, the component must present clear public-facing surfaces for configuration, management/readiness, and consumption by participants.

---

## 2. Core Thesis

```text
ASCC internal model
    != ASCC external facade

ASCC must hide internal structure behind explicit facade surfaces.
```

The facade must allow the Pipeline Composer and participants to interact with ASCC without depending on ASCC internals.

---

## 3. Three Surface Categories

## 3.1 Administrative Surface

Administrative surface concerns setup-time and governance-time definitions.

It answers:

```text
What is this ASCC component?
What profiles does it support?
What capabilities can be declared?
What protocols and bindings can be registered or selected?
What configuration families exist?
What versioned public surface is exposed?
```

Administrative responsibilities include:

```text
component identity declaration
component version declaration
available bridge profiles
available binding profiles
available protocol requirement sets
capability catalog exposure
static/default configuration profile exposure
policy-realizable capability declarations
public include surface declaration
```

Administrative surface must not execute bridge steps.

Candidate components:

```text
TAsccAdministrativeFacade
TAsccComponentDescriptor
TAsccComponentVersion
TAsccComponentCapabilityCatalog
TAsccProtocolCatalogView
TAsccBindingProfileCatalogView
TAsccDefaultProfileCatalog
TAsccPolicyRealizationCapabilityCatalog
```

---

## 3.2 Managerial Surface

Managerial surface concerns preparation, admission, readiness, profile selection, and lifecycle control.

It answers:

```text
Can this ASCC instance be admitted into a pipeline?
Is this configuration valid?
Are participant capabilities satisfied?
Are protocol requirements satisfied?
Is binding composition valid?
Is the component ready, blocked, degraded, or deferred?
Can the component transition to run-ready state?
```

Managerial responsibilities include:

```text
configuration validation
profile selection
participant capability matching
binding compatibility checks
protocol requirement checks
readiness evaluation
safe-point/readiness evidence
bridge declaration admission
diagnostic setup
component lifecycle preparation
```

Managerial surface may prepare ASCC for operation but should not be confused with participant consumption.

Candidate components:

```text
TAsccManagerialFacade
TAsccComponentAdmission
TAsccComponentReadinessGate
TBridgeCoreReadinessPolicy
TAsccBridgeReadinessView
TAsccCompositionReadinessReport
TAsccProfileSelectionResult
TAsccManagerialIssue
```

---

## 3.3 Consuming Surface

Consuming surface concerns how participants or the Pipeline Composer use ASCC after administrative setup and managerial readiness.

It answers:

```text
How does a participant consume ASCC capability?
How does a bridge model step run?
How does a participant request/observe placement, handoff, or protocol behavior?
What operation entry point is safe to call?
What evidence is returned after operation?
```

Consuming responsibilities include:

```text
bridge model operation entry
optional endpoint invocation entry if ASCC owns it
participant-facing protocol use
binding-facing operation path
result/report return
safe read-only observation
failure/rejection reporting
```

Candidate components:

```text
TAsccConsumingFacade
TBridge
TBridgeStepExecutor
TBridgeEndpointInvocation
TBridgeExecutionReport
TBridgeCoreStepReport
TBridgeCoreRunReport
TAsccParticipantOperationView
TAsccConsumingResult
```

---

## 4. ASCC Facade And Pipeline Composer

From the Pipeline Composer perspective:

```text
Administrative facade
    supplies component definition and supported profiles.

Managerial facade
    evaluates whether the configured ASCC component is ready for pipeline admission.

Consuming facade
    exposes the operational entry surface used after admission.
```

The Pipeline Composer must not inspect ASCC internals directly.

---

## 5. ASCC Facade And Policy

Policy belongs primarily to the composition layer.

Therefore, ASCC policy-related obligations appear through facade capabilities:

```text
Administrative:
    declare policy-realizable capabilities

Managerial:
    admit or reject policy-derived configuration/profile selection

Consuming:
    run only the profile/configuration already admitted by managerial surface
```

ASCC must not directly own policy semantics.

---

## 6. ASCC Facade And Current Bridge Core

Current `bridge_core/` already provides several internal building blocks:

```text
TBridge
TBridgeConfig
TBridgeStepBudget
TBridgeCorePolicy
TBridgeCoreView
TBridgeCoreFrame
TBridgeCoreStepReport
TBridgeCoreIssue
TBridgeCoreResult
```

But these are not yet organized as a public facade layer.

Facade gap:

```text
The domain has internal operational/model/evidence primitives,
but no explicit Administrative / Managerial / Consuming facade split.
```

---

## 7. Required ASCC Facade Obligations

ASCC must eventually provide:

```text
TAsccAdministrativeFacade
TAsccManagerialFacade
TAsccConsumingFacade
```

or equivalent surfaces that preserve the same semantic split.

It must also provide facade-level views and reports:

```text
TAsccAdministrativeView
TAsccManagerialReadinessView
TAsccConsumingOperationView
TAsccFacadeReadinessReport
TAsccFacadeIssue
```

---

## 8. Anti-Collapse Rules

### 8.1 Administrative Must Not Execute

Administrative surface may declare supported protocols, profiles, capabilities, and defaults.

It must not run bridge steps.

### 8.2 Managerial Must Not Become Participant Consumption

Managerial surface may validate readiness and admission.

It must not become the runtime participant-facing operation path.

### 8.3 Consuming Must Not Reconfigure Administrative Decisions

Consuming surface may run or observe admitted operation.

It must not modify global catalogs, profiles, or policy-derived configuration.

### 8.4 Facade Must Not Leak Internals

Participants and Pipeline Composer should not need direct access to internal registries, protocol state internals, binding internals, or private bridge state.

---

## 9. Consequence For Gap Matrices

Future ASCC operational matrices must classify each missing item by facade obligation:

```text
AdministrativeFacadeGap
ManagerialFacadeGap
ConsumingFacadeGap
CrossFacadeGap
```

Every proposed operational entity should state:

```text
which facade consumes it
which existing descriptive/model entities it wraps
which higher-level Pipeline Composer question it answers
```

---

## 10. Closure Statement

ASCC must be delivered as a composable component with explicit facade surfaces.

The correct external shape is:

```text
ASCC Administrative Surface
    + ASCC Managerial Surface
    + ASCC Consuming Surface
```

This facade layer is now a formal obligation of the Bridge Orchestrator / Communication Context domain.
