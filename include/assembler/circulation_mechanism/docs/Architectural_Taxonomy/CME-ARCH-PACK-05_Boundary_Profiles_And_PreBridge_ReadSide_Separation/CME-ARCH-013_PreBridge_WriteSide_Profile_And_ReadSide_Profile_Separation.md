# CME-ARCH-013 — PreBridge WriteSide Profile And ReadSide Profile Separation

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-013-DOC-001 | Document Title | PreBridge WriteSide Profile And ReadSide Profile Separation |
| CME-ARCH-013-DOC-002 | Package | CME-ARCH-PACK-05 |
| CME-ARCH-013-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-013-DOC-004 | Scope Level | Profile separation, pre-bridge write-side profile, read-side circulation profile |
| CME-ARCH-013-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-013-DOC-006 | Implementation Direction | C++17, header-only-first, profile-based family modeling |
| CME-ARCH-013-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-012 |
| CME-ARCH-013-DOC-008 | Related Models | Pre-bridge profile, read-side profile, bridge drain assumption, failed-dispatch list, receiver delay |
| CME-ARCH-013-DOC-009 | Primary Rule | Pre-bridge write-side circulation and read-side circulation are related profiles, not the same responsibility boundary |
| CME-ARCH-013-DOC-010 | Excluded | Final read-side implementation, bridge orchestrator internals, add-on delivery internals |

---

## 2. Purpose

### 2.1 Purpose Statement

This document separates the pre-bridge write-side circulation profile from the read-side circulation profile.

It answers:

```text
Which circulation concerns belong before the bridge, which concerns should move
to read-side circulation, and how do we avoid turning the pre-bridge engine
into a receiver-side delay/retry/backpressure manager?
```

### 2.2 Core Thesis

```text
The same mechanism family may appear on both sides of the bridge.
The profiles are different because their responsibilities are different.
```

### 2.3 Corrected Naming

The historical phrase `write-side` refers here to:

```text
pre-bridge write-side circulation profile
```

It does not mean right-side.

---

## 3. Profile Overview

## 3.1 Pre-Bridge Write-Side Profile

The pre-bridge profile is the current core CME profile.

It is characterized by:

1. single producer,
2. single dispatcher,
3. pre-sized capacity,
4. extreme default provisioning,
5. horizontal/vertical scaling through profiles,
6. reference-precalculated access,
7. passive pull output exposure,
8. no receiver delay ownership,
9. no retry lifecycle,
10. no failed-dispatch backlog by default.

## 3.2 Read-Side Circulation Profile

The read-side profile is a later or downstream profile that may absorb:

1. receiver delay,
2. failed dispatch,
3. retry,
4. delayed release,
5. receiver-side capacity pressure,
6. add-on-specific flow control,
7. persistence/export interactions,
8. multi-consumer patterns if required.

## 3.3 Shared Family

Both profiles may share concepts:

1. containers,
2. slots,
3. registries,
4. waiting lists,
5. rounds,
6. references,
7. safe points,
8. release/recycle,
9. reports/views.

They do not share the same boundary responsibilities.

---

## 4. Pre-Bridge Profile

### 4.1 Producer Model

| Field | Value |
|---|---|
| Producer | Log-Level API / envelope provider plugin adapter |
| Producer Count | Single producer |
| Input | Prepared envelope payload |
| Producer Knowledge | No container/slot internals |
| Entry | Ingress access refs |

### 4.2 Dispatcher Model

| Field | Value |
|---|---|
| Dispatcher Count | Single dispatcher |
| Dispatch Style | Passive pull default |
| Output | Exposure view/ref/report |
| Consumer | Bridge-facing adapter |
| Non-Ownership | bridge protocol, receiver lifecycle, retry, persistence |

### 4.3 Capacity Model

Pre-bridge capacity is assumed to be computed before runtime hot path.

```text
max intake capacity
container count
slots per container
dispatch waiting-list capacity
extreme default profile
```

### 4.4 Backpressure Position

Backpressure is not a normal pre-bridge runtime problem if capacity is properly configured.

If the bridge/read-side cannot drain, the concern should normally be modeled beyond the bridge.

### 4.5 Failure Position

Failures are mostly:

1. invariant violations,
2. profile exhaustion,
3. boundary assumption failures,
4. stale reference use,
5. safe-point violations.

They are not ordinary broker-style consumer errors.

---

## 5. Read-Side Profile

### 5.1 Producer Model

The producer may be:

1. bridge-facing adapter,
2. dispatcher output consumer,
3. add-on feeder,
4. receiver-side admission boundary.

### 5.2 Consumer Model

The consumer may be:

1. final receiver,
2. file sink,
3. database adapter,
4. telemetry adapter,
5. diagnostic sink,
6. in-process receiver.

### 5.3 Additional Concerns

Read-side profile may need:

1. delayed release,
2. receiver acknowledgement,
3. failed dispatch waiting list,
4. retry plan,
5. receiver-side backpressure,
6. receiver-specific capacity profile,
7. persistence-specific boundary,
8. add-on-specific dispatch.

### 5.4 Read-Side Non-Meaning

Read-side profile does not retroactively make pre-bridge CME own:

1. final delivery,
2. receiver acknowledgement,
3. persistence,
4. retry,
5. query readiness.

---

## 6. Failed-Dispatch List

### 6.1 Pre-Bridge Position

A failed-dispatch list is not part of the default pre-bridge profile.

Reason:

```text
pre-bridge engine assumes continuous bridge drain under configured profile
```

### 6.2 Read-Side Position

A failed-dispatch list may be appropriate on the read-side profile because receiver delay and retry are receiver-side concerns.

### 6.3 Possible Read-Side Structure

```text
TFailedDispatchWaitingList
TReceiverRetryList
TDelayedReleaseList
TReceiverBackpressureList
```

### 6.4 Pre-Bridge Diagnostic

If pre-bridge dispatch exposure cannot drain, the engine emits:

```text
BridgeDrainAssumptionBroken
```

rather than becoming a retry system.

---

## 7. Receiver Delay

### 7.1 Pre-Bridge Rule

Receiver delay is outside the pre-bridge CME responsibility.

### 7.2 Read-Side Rule

Receiver delay may be modeled as:

1. receiver-side waiting list,
2. delayed release state,
3. retry state,
4. receiver-side capacity pressure,
5. add-on-specific profile.

### 7.3 Boundary Report

The pre-bridge engine may produce:

```text
TBoundaryAssumptionBrokenReport
TBridgeDrainObservationReport
```

but not a receiver delay recovery plan.

---

## 8. Retry

### 8.1 Pre-Bridge Rule

Retry is not a pre-bridge default concern.

### 8.2 Read-Side Rule

Retry belongs to read-side or add-on-specific profile if required.

### 8.3 Retry Non-Collapse

Retry must not collapse into:

1. dispatcher output exposure,
2. bridge core,
3. container registry,
4. reference precalculation,
5. pre-bridge waiting list.

---

## 9. Delayed Release

### 9.1 Pre-Bridge Position

Delayed release is limited and profile-dependent before bridge.

Possible pre-bridge release triggers:

1. dispatch exposure issued,
2. bridge pull observed,
3. dispatch round completed,
4. exposure closed.

### 9.2 Read-Side Position

Read-side may delay release based on:

1. receiver acknowledgement,
2. persistence completion,
3. add-on completion,
4. retry exhaustion,
5. receiver safe point.

### 9.3 Rule

```text
Pre-bridge release must not require final receiver proof unless the profile explicitly defines a bridge/read-side contract.
```

---

## 10. Bridge Drain Assumption

### 10.1 Definition

Bridge drain assumption is the configured expectation that the bridge-facing side will consume output exposure fast enough to keep pre-bridge circulation moving.

### 10.2 Status Values

```text
assumed_continuous
observed_healthy
delayed
broken
delegated_to_read_side
```

### 10.3 Broken Assumption

If broken, pre-bridge may:

1. emit diagnostic,
2. close exposure,
3. select eviction if configured,
4. delegate failure to read-side profile,
5. stop short of becoming retry owner.

### 10.4 Report

```text
TBridgeDrainAssumptionReport
```

---

## 11. Profile Comparison Matrix

| Dimension | Pre-Bridge Write-Side Profile | Read-Side Circulation Profile |
|---|---|---|
| Main direction | Log API → CME → Bridge | Bridge → Receiver/Add-on |
| Producer count | Single | Profile-dependent |
| Dispatcher count | Single | Profile-dependent |
| Backpressure | Avoided by sizing/profile | May be central |
| Failed-dispatch list | Deferred/not default | Likely possible |
| Retry | Out of scope | Possible |
| Receiver delay | Out of scope | In scope |
| Copy/move | Bridge-side contract | Receiver/add-on contract |
| Passive pull | Default | Optional |
| Release | exposure/round/profile-bound | receiver/ack/profile-bound |
| Eviction | time-range/profile diagnostic | receiver-pressure/profile |
| Persistence | out of scope | add-on-specific |
| Diagnostics | invariant/profile/boundary | receiver/add-on/runtime |

---

## 12. Profile Invariants

```text
1. Pre-bridge profile must not own final receiver lifecycle.
2. Read-side profile must not redefine Log API production.
3. Bridge drain failure does not automatically make pre-bridge CME a retry engine.
4. Failed-dispatch list belongs mostly read-side unless explicit pre-bridge profile adds it.
5. Copy/move semantics remain outside CME core.
6. Shared mechanism family does not mean shared boundary responsibility.
```

---

## 13. Views

| View | Profile | Purpose |
|---|---|---|
| `TPreBridgeProfileView` | pre-bridge | Current pre-bridge configuration |
| `TReadSideProfileView` | read-side | Future read-side profile |
| `TBridgeDrainAssumptionView` | boundary | Drain assumption state |
| `TBoundaryDelegationView` | bridge/read-side | Which side owns delay/retry |

---

## 14. Reports

| Report | Trigger |
|---|---|
| `TPreBridgeProfileReport` | profile setup |
| `TReadSideProfileRequirementReport` | read-side concern detected |
| `TBridgeDrainAssumptionReport` | bridge drain observation |
| `TReceiverDelayDelegationReport` | receiver delay delegated |
| `TFailedDispatchDeferredReport` | failed-dispatch list deferred to read-side |
| `TProfileBoundaryViolationReport` | concern assigned to wrong profile |

---

## 15. Implementation Derivation Notes

### 15.1 Candidate Header Families

```text
profiles/
    TPreBridgeWriteSideProfile.hpp
    TReadSideCirculationProfile.hpp
    TBridgeDrainAssumptionProfile.hpp
    TProfileBoundaryReport.hpp
```

### 15.2 Deferred Decisions

1. Whether read-side circulation profile is implemented in same root or separate domain.
2. Whether failed-dispatch list is modeled pre-bridge as optional disabled-by-default profile.
3. Whether bridge drain observation is hard requirement or diagnostic-only.
4. Whether receiver-side retry profiles reuse the same RoundManager/WaitingList templates.

---

## 16. Summary

Pre-bridge circulation is not read-side circulation.  
The same mechanism family may appear on both sides, but responsibilities differ.  
Pre-bridge assumes continuous bridge drain under profile.  
Read-side may own receiver delay, failed dispatch, retry, and delayed release.
