# CME-RSCP-W02 — Failed Dispatch And Retry Profile

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-RSCP-W02` |
| Component | `ReadSide_Circulation_Profile` |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish failed-dispatch, retry-profile, retry-attempt, and receiver-acknowledgement skeletons for post-bridge/read-side circulation |

## 2. What This Wave Implements

```text
failed_dispatch/
  TFailedDispatchId
  TFailedDispatchKind
  TFailedDispatchState
  TFailedDispatchRecord

retry/
  TRetryProfileId
  TRetryPolicyKind
  TRetryAttemptId
  TRetryAttemptState
  TReadSideRetryProfile
  TRetryAttempt

receiver_acknowledgement/
  TReceiverAcknowledgementId
  TReceiverAcknowledgementState
  TReceiverAcknowledgementRecord

views/
  TFailedDispatchView
  TRetryProfileView

reports/
  TReadSideRetryReportId
  TReadSideRetryIssueKind
  TReadSideRetryReport
```

## 3. What This Wave Does Not Implement

```text
retry algorithm
failed-dispatch waiting list
receiver acknowledgement execution
bridge recovery
persistence adapter
backpressure algorithm
delayed release algorithm
```

## 4. Architectural Rules Preserved

1. Failed-dispatch is read-side/post-bridge, not pre-bridge dispatcher behavior.
2. Retry profile is a descriptor, not a retry engine.
3. Receiver acknowledgement record is not receiver implementation.
4. Retry reports are evidence, not runtime action.
