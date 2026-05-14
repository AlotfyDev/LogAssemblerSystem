# ASCC-COMP-W06 — Binding Model Operational Analysis

## Purpose
This document records the operational analysis for:

```text
include/assembler/bridge_orchestrator/bindings/
```

`bindings/` is the ASCC composition and compatibility hinge between participants, obligations, sessions, protocols, bridge core, facade layer, and the higher Pipeline Composer.

## Core Finding
`bindings/` is not endpoint runtime execution, but it is not passive documentation. It contains and requires entities that make binding declarations operationally useful for readiness, admission, session opening, protocol compatibility, and future invocation description.

## Owned Responsibilities
```text
binding identity and view
binding composition metadata
binding-to-protocol requirement matching
binding-to-session opening profile
participant-role mapping
obligation-surface mapping
facade-safe binding evidence
```

## Non-Responsibilities
```text
endpoint invocation execution
bridge run loop
protocol stepping
session lifecycle mutation
Pipeline Composer topology ownership
policy governance semantics
```

## Required Entities
```text
TBindingCompositionMatcher
TBindingCompositionReadinessReport
TBindingParticipantRoleMap
TBindingObligationSurfaceMap
TConcreteBindingInvocationDescriptor
TBindingSessionOpenProfile
TAsccBindingProfileCatalogView
TAsccBindingReadinessView
TAsccBindingAdmissionPolicy
TAsccBindingEvidenceAdapter
```

## Closure
`bindings/` is classified as a header-only binding composition, compatibility, and readiness foundation. The production direction is to add matcher/readiness/facade entities without collapsing binding into endpoint invocation.
