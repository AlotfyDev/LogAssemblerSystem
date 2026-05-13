# ASCC-COMP-W10 — Policy Relationship As Composition Capability

## 1. Purpose

This document records a key architectural decision about the relationship between:

```text
ASCC / Bridge Orchestrator / Communication Context
```

and:

```text
Policy Object / Policy System / Pipeline Composer
```

The decision is:

```text
Policy belongs primarily to the composition layer.
ASCC must not treat Policy Object assignment as a direct internal ownership concern.
ASCC must instead expose capabilities, profiles, readiness evidence, and safe-point surfaces that allow the composition layer to realize policy decisions through configuration and admission.
```

---

## 2. Core Thesis

```text
Policy is composition authority.
ASCC is a composable operational component.
ASCC does not own policy semantics directly.
ASCC exposes the capabilities needed for policies to be realized by the Pipeline Composer.
```

This means that ASCC should not receive a Policy Object as if it were an internal subsystem controller.

Instead, ASCC should expose:

```text
capability declarations
configuration knobs
binding/profile surfaces
readiness views
safe-point flags
operational entry surfaces
evidence reports
```

The Pipeline Composer, or a composition-level policy assigner, decides how a policy is applied to ASCC as one component inside a larger data-trading pipeline.

---

## 3. Ownership Split

| Concern | Owner |
|---|---|
| Policy semantics | Policy System / Composition Layer |
| Pipeline-level policy decision | Pipeline Composer |
| Component selection | Pipeline Composer |
| Component configuration profile selection | Pipeline Composer |
| ASCC capability declaration | ASCC |
| ASCC readiness evidence | ASCC |
| ASCC safe-point availability | ASCC |
| ASCC local operational behavior | ASCC |
| Direct policy semantics execution | Not ASCC Core |

---

## 4. What ASCC Must Provide

ASCC must provide enough component-level capability information so that the composition layer can decide whether a policy can be realized.

Required ASCC surfaces include:

```text
TAsccBridgeReadinessView
TBridgeCoreReadinessPolicy
TBindingCompositionMetadata
TProtocolRequirementSet
TParticipantCapabilitySet
TBridgeEndpointInvocationProfile
TBridgeStaticProfile
TBridgeStatusTransitionMatrix
TBridgeExecutionReport
```

These are not policy objects.

They are component capabilities and evidence surfaces used by policy-aware composition.

---

## 5. What ASCC Must Not Do

ASCC must not:

```text
own governance policy semantics
construct global Policy Objects
decide pipeline-wide policy assignment
replace Pipeline Composer as policy authority
mutate itself from a policy object without composition-level admission
host policy as a direct internal subsystem unless explicitly wrapped as a composition-facing host surface
```

A future ASCC policy host, if needed, must be interpreted as:

```text
component-owned safe assignment/configuration port
```

not as:

```text
ASCC owning policy governance
```

---

## 6. Correct Policy Flow

The correct policy flow is:

```text
Policy System defines policy semantics
    -> Pipeline Composer interprets policy for pipeline composition
    -> Pipeline Composer selects component profiles/capabilities
    -> ASCC exposes capability/readiness/safe-point evidence
    -> Composition-level assignment selects ASCC configuration/profile
    -> ASCC runs according to the admitted configuration/profile
    -> ASCC reports evidence back to composition layer
```

Incorrect flow:

```text
Policy Object directly mutates ASCC internals
```

Incorrect flow:

```text
ASCC reads global policy semantics and decides pipeline policy itself
```

---

## 7. Relation To Policy Object Host Model

If the Policy Object Host model is used with ASCC, it must be applied carefully.

The ASCC-facing host must represent:

```text
an assignment/configuration/safe-point surface for the ASCC component
```

not:

```text
policy governance ownership inside ASCC
```

Therefore, ASCC may later expose something like:

```text
TAsccPolicyCapabilityDeclaration
TAsccPolicyConfigAdmission
TAsccPolicySafePointView
TAsccPolicyAssignmentReadinessReport
```

But these must be composition-facing surfaces, not direct policy-semantic execution engines.

---

## 8. Capability Realization Pattern

Policy realization should happen through capability exposure.

Example:

```text
Policy wants bounded bridge execution.
ASCC exposes TBridgeStepBudget, TBridgeRunMode, and readiness evidence.
Pipeline Composer selects bounded_model_run profile.
ASCC executes only that admitted profile.
```

Example:

```text
Policy wants no endpoint invocation.
ASCC exposes TBridgeEndpointInvocationProfile.
Pipeline Composer selects model_only profile.
ASCC runs model-only and reports evidence.
```

Example:

```text
Policy wants diagnostic trace capture.
ASCC exposes trace capability and diagnostic readiness.
Pipeline Composer selects trace-enabled profile.
ASCC emits TBridgeCoreTrace / TBridgeExecutionReport evidence.
```

---

## 9. Matrix Implication

Any ASCC operational matrix should distinguish:

```text
Existing descriptive/model entities
Proposed operational entities
Composition-facing capability surfaces
Policy-realizable configuration/profile surfaces
```

A missing policy-related component should be described as:

```text
missing component capability required for composition-level policy realization
```

not as:

```text
missing direct Policy Object integration inside ASCC
```

---

## 10. Consequence For Future Waves

Future ASCC waves should prefer names such as:

```text
TAsccComponentCapabilityView
TAsccPolicyRealizationCapability
TAsccPolicyAdmissibleProfile
TAsccCompositionPolicyReadinessView
TAsccPolicySafePointEvidence
```

and avoid names that imply ASCC owns governance semantics directly, such as:

```text
TAsccPolicyExecutor
TAsccPolicySemanticEngine
TAsccGlobalPolicyRegistry
```

unless a later architecture decision explicitly changes ownership.

---

## 11. Closure Statement

ASCC should be policy-aware only through component capabilities, readiness evidence, safe points, and configuration/profile admission.

Policy belongs to the composition layer.

ASCC supplies the capability to realize the desired policy; it does not directly own policy semantics.
