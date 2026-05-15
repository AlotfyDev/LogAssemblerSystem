# ASCC-COMP-W03 — Participant Model Runtime Analysis

## Purpose

This package corrects the participant layer interpretation.

Current `participants/` provides role vocabulary, descriptors, views, capability declarations, carrier-capability declarations, requirement descriptors, and match-result shapes.

The production requirement is a runtime layer above these contracts:

```text
participant admission
capability matching
carrier participation
role-to-binding mapping
participant-to-obligation binding
runtime context
runtime reports
facade-safe evidence
```

## Core Rule

```text
TParticipant is not a runtime context.
TParticipantRole is not operational behavior.
TParticipantCapabilitySet is not a matcher.
TParticipantCapabilityMatchResult is not a matching engine.
TParticipantCarrierCapability is not carrier participation runtime.
```

## Required Additions

```text
participants/runtime/TParticipantAdmissionPolicy.hpp
participants/runtime/TParticipantCapabilityMatcher.hpp
participants/reports/TParticipantCapabilityMatchReport.hpp
participants/runtime/TParticipantCarrierParticipationRuntime.hpp
participants/runtime/TParticipantRoleBindingMap.hpp
participants/runtime/TParticipantObligationSurfaceBinding.hpp
participants/runtime/TParticipantRuntimeContext.hpp
participants/reports/TParticipantRuntimeReport.hpp
participants/runtime/TParticipantRegistryAdmissionPolicy.hpp

facade_layer/administrative/TAsccParticipantCatalogView.hpp
facade_layer/managerial/TAsccParticipantReadinessView.hpp
facade_layer/managerial/TAsccParticipantAdmissionPolicy.hpp
facade_layer/common/TParticipantFacadeEvidenceAdapter.hpp
```

## Closure

`participants/` should evolve from contract layer to participant admission, matching, participation, and facade evidence layer.
