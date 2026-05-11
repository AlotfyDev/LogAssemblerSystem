# CME-RSCP-W01 — ReadSide Profile Identity And Boundary Contracts

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-RSCP-W01` |
| Component | `ReadSide_Circulation_Profile` |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish read-side profile identity, admission boundary, receiver context, and post-bridge boundary contract descriptors |

## 2. What This Wave Implements

```text
TReadSideProfileId
TReadSideProfileStatus
TReadSideCirculationProfile

admission/
  TReadSideAdmissionBoundaryId
  TReadSideAdmissionMode
  TReadSideAdmissionStatus
  TReadSideAdmissionBoundaryDescriptor

receiver_context/
  TReceiverContextId
  TReceiverContextKind
  TReceiverLifecycleExpectation
  TReceiverContextDescriptor

boundary_contracts/
  TPostBridgeBoundaryContractId
  TPostBridgeTransferSemantic
  TPostBridgeBoundaryContractStatus
  TPostBridgeBoundaryContractDescriptor

views/
  TReadSideProfileView

reports/
  TReadSideProfileReportId
  TReadSideProfileIssueKind
  TReadSideProfileReadinessReport
```

## 3. What This Wave Does Not Implement

```text
failed-dispatch list
retry algorithm
backpressure algorithm
receiver acknowledgement execution
persistence adapter
bridge protocol
addon implementation
post-bridge container registry
```

## 4. Architectural Rules Preserved

1. Read-side profile is inside circulation mechanism family but outside pre-bridge profile.
2. Bridge transfer semantic is described, not executed.
3. Receiver context is described, not implemented.
4. Persistence is boundary-dependent and not owned here.
