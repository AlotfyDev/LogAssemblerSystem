# CME-W10 — Ingress Placement Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W10` |
| Wave Name | Ingress Placement Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce ingress actor skeleton, placement policy surface, ingress boundary shape, placement views, and placement/boundary reports |

## 2. What This Wave Implements

```text
ingress/
  TIngress
  TIngressId
  TIngressState
  TIngressPlacementStatus
  TIngressPayloadEnvelopeRef

ingress/boundary/
  TIngressBoundaryId
  TIngressBoundaryStatus
  TIngressBoundaryDescriptor

ingress/policies/
  TIngressAccessPolicy

ingress/views/
  TIngressView
  TIngressAdmissionView
  TIngressPlacementView

ingress/reports/
  TIngressReportId
  TIngressPlacementReport
  TIngressBoundaryReport
```

## 3. What This Wave Does Not Implement

```text
actual slot mutation
payload storage
Log API envelope assembly
payload parsing
reference calculation
container/slot locating
dispatch behavior
bridge bindings
read-side lifecycle
```

## 4. Architectural Rules Preserved

1. Ingress consumes prepared envelope refs and ingress access refs.
2. Ingress does not locate containers or slots.
3. Ingress does not inspect envelope content.
4. Boundary shape is represented without exposing container internals.
5. Placement report is evidence, not lifecycle ownership.
