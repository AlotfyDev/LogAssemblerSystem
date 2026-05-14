# ASCC-COMP-W06 — Binding To Session And Protocol Relationship

## Binding To Session
```text
TBinding
  -> TCompatibilityEvaluator / TCompatibilityView
  -> TSessionOpenRequest
  -> TSession::open()
```

## Binding To Protocol
```text
TProtocolBindingRequirement
  -> TBindingCompositionMatcher
  -> TBindingCompositionReadinessReport
  -> TProtocolRequirementReport
  -> TAsccProtocolReadinessView
```

## Binding To Bridge Core
Bridge Core should receive ready protocol/session context. It must not inspect raw binding internals.

## Binding To Facade
```text
Pipeline Composer
  -> TAsccBindingProfileCatalogView
  -> TAsccBindingAdmissionPolicy
  -> TAsccBindingReadinessView
  -> TAsccManagerialReadinessView
```

## Binding To Invocation
Binding may describe callable paths through `TBindingObligationSurfaceMap` and `TConcreteBindingInvocationDescriptor`. Actual endpoint invocation belongs to an explicit future invocation layer.
