# CME-W14 — Communication Binding Integration Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W14` |
| Wave Name | Communication Binding Integration Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce ingress/dispatch boundary descriptors, views, reports, and compatibility policy without executing Log API or Bridge runtime |

## 2. What This Wave Implements

```text
communication_bindings/
  TCommunicationBindingId
  TCommunicationBindingStatus
  TCommunicationBindingKind
  TBindingCompatibilityStatus
  TCommunicationBindingCompatibility
  TCirculationCommunicationBindingDescriptor
  TCommunicationBindingCompatibilityPolicy

communication_bindings/ingress/
  TEnvelopePlacementPortId
  TEnvelopePlacementPortDescriptor
  TIngressBindingView

communication_bindings/dispatch_output/
  TDispatchOutputAdapterId
  TBridgeFacingDispatchAdapterDescriptor
  TDispatchOutputBindingView

communication_bindings/views/
  TCirculationCommunicationBindingView

communication_bindings/reports/
  TCommunicationBindingReportId
  TCommunicationBindingIssueKind
  TCommunicationBindingReport
```

## 3. What This Wave Does Not Implement

```text
actual adapter invocation
Log API runtime
Bridge Orchestrator runtime
bridge sessions/protocols
payload movement
ingress placement
dispatch exposure
mutable container exposure
receiver lifecycle
```

## 4. Architectural Rules Preserved

1. Ingress binding describes envelope placement boundary only.
2. Dispatch output binding describes bridge-facing output boundary only.
3. Bindings are not adapters executing behavior.
4. Bridge-facing descriptor must not request mutable CME internals.
5. Binding compatibility is descriptive and non-executing.
6. Reports are evidence, not adapter invocation.
