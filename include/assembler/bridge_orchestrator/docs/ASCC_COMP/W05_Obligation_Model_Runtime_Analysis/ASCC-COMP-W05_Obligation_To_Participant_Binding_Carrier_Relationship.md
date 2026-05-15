# ASCC-COMP-W05 — Obligation To Participant, Binding, Carrier, And Protocol Relationship

## 1. Obligation To Participant

A participant can only participate operationally when its role and capabilities are bound to a concrete obligation surface.

```text
TParticipant
TParticipantCapabilitySet
TParticipantObligationSurfaceBinding
    -> obligation runtime context
```

## 2. Obligation To Binding

Binding maps the plugin-adapter side and the port side.

```text
TBindingObligationSurfaceMap
TObligationSurfacePair
    -> TObligationSurfaceReadinessEvaluator
```

## 3. Obligation To Carrier

Obligations produce and consume carriers:

```text
adapter.prepare_placement_request -> TPlacementRequest
port.admit                         -> TAdmissionResult
port.placement_handle              -> TPlacementHandle
adapter.emit_load_signal           -> TLoadSignal
```

Carrier events must be recorded through carrier-flow runtime.

## 4. Obligation To Protocol

Protocol steps and requirements determine which obligations may be invoked and when.

```text
TBridgeProtocolStep
TProtocolCarrierRequirement
TProtocolParticipantRequirement
TProtocolBindingRequirement
    -> TObligationInvocationPolicy
    -> TObligationInvocationSequencer
```

## 5. Obligation To Facade

Facade consumes reports and readiness views:

```text
TObligationInvocationReport
TObligationRuntimeView
TObligationReport
    -> TObligationFacadeEvidenceAdapter
    -> TAsccObligationReadinessView
```

Pipeline Composer must not call port/plugin internals directly.
