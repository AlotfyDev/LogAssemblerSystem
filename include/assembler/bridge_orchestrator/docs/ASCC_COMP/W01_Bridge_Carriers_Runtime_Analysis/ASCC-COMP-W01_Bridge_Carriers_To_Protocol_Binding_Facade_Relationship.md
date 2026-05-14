# ASCC-COMP-W01 — Bridge Carriers To Protocol, Binding, And Facade Relationship

## 1. Purpose

This document explains how carrier contracts become operational through protocol, binding, obligation, and facade relationships.

---

## 2. Carrier To Protocol

Protocol requirements declare carrier expectations:

```text
TProtocolCarrierRequirement
    -> required carrier kind
    -> participant role
    -> participant capability
    -> direction
```

Carrier runtime satisfies those requirements through:

```text
TCarrierRequirementSatisfactionEngine
TCarrierRequirementSatisfactionReport
```

---

## 3. Carrier To Binding

Binding provides participant role and surface mapping:

```text
TBindingParticipantRoleMap
TBindingObligationSurfaceMap
```

Carrier runtime uses:

```text
TCarrierProtocolBindingMap
```

to connect required carriers to protocol steps and binding roles.

---

## 4. Carrier To Obligation

Obligation resolver maps carriers to callable surfaces without invoking them:

```text
placement_request -> adapter.prepare_placement_request / port.admit
placement_handle  -> port.produces_handle / adapter.accepts_handle
load_signal       -> adapter.emit_load_signal / port.receive_load_signal
```

This is described by:

```text
TCarrierObligationResolver
```

Actual invocation remains a future explicit endpoint invocation path.

---

## 5. Carrier To Facade

Facade consumes reports and readiness views:

```text
TCarrierFlowReport
TCarrierValidationReport
TCarrierRequirementSatisfactionReport
    -> TCarrierFacadeEvidenceAdapter
    -> TAsccCarrierReadinessView
```

This prevents the Pipeline Composer from depending on carrier internals.

---

## 6. Closure

Carriers are contracts. Carrier runtime validates, binds, records, and reports carrier movement.
