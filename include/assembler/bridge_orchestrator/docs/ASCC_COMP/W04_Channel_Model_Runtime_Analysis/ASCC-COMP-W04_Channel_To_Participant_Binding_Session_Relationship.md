# ASCC-COMP-W04 — Channel To Participant, Binding, And Session Relationship

## 1. Channel To Participant

A channel connects two participants:

```text
source participant
target participant
```

A channel is not ready merely because the descriptors are valid. It needs participant readiness:

```text
TAsccParticipantReadinessView
TParticipantRuntimeContext
```

## 2. Channel To Binding

The channel profile and binding policy constrain the binding shape.

```text
TChannelProfile
TChannelBindingPolicy
    -> TChannelBindingReadinessBridge
    -> TAsccBindingReadinessView
```

## 3. Channel To Session

Session opening should occur only after channel admission and binding readiness:

```text
TChannelRuntimeContext
TChannelSessionPreparationPolicy
TSessionOpenRequest
```

## 4. Channel To Protocol

Protocol model contains a `channel_resolution` stage. That stage should consume channel readiness evidence, not raw channel internals.

## 5. Channel To Facade

Facade exposes:

```text
TAsccChannelCatalogView
TAsccChannelReadinessView
TAsccChannelAdmissionPolicy
TChannelFacadeEvidenceAdapter
```

Pipeline Composer should not inspect or mutate channel internals directly.
