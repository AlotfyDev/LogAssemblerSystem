# CME-ARCH-014 — Views Reports And Read Only Projection Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-014-DOC-001 | Document Title | Views Reports And Read Only Projection Model |
| CME-ARCH-014-DOC-002 | Package | CME-ARCH-PACK-06 |
| CME-ARCH-014-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-014-DOC-004 | Scope Level | Views, reports, read-only projection, report evidence, anti-leakage |
| CME-ARCH-014-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-014-DOC-006 | Implementation Direction | C++17, header-only-first, read-only projections, report carriers |
| CME-ARCH-014-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-013 |
| CME-ARCH-014-DOC-008 | Related Models | State model, safe point model, reference validity, dispatch boundary, waiting lists, registry |
| CME-ARCH-014-DOC-009 | Primary Rule | Views expose safe read-only current state; reports preserve evidence of actions and diagnostics |
| CME-ARCH-014-DOC-010 | Excluded | mutable internal exposure, bridge delivery proof, receiver acknowledgement, persistence proof |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the view and report model for the Circulation Mechanism Engine.

It answers:

```text
How can the engine be observed, tested, diagnosed, and traced without leaking
mutable internals or confusing evidence reports with downstream success?
```

### 2.2 Core Thesis

```text
View = safe read-only current-state projection.
Report = action / transition / diagnostic evidence.
```

### 2.3 Architectural Role

Views and reports are not optional documentation conveniences. They are core architectural surfaces that allow:

1. diagnostics,
2. tests,
3. traceability,
4. invariant validation,
5. safe cross-component observation,
6. boundary reporting,
7. implementation-readiness derivation.

---

## 3. View Definition

### 3.1 Definition

A View is a read-only projection of current component state, readiness, membership, topology, reference supply, exposure, or boundary condition.

### 3.2 View Properties

| Property | Meaning |
|---|---|
| Read-only | Does not allow mutation |
| Scope-bound | Belongs to the component that owns the viewed meaning |
| Anti-leakage | Does not expose private mutable internals |
| Stable enough | Snapshot or live-view semantics must be declared |
| Consumer-safe | May be consumed by approved components/tests/diagnostics |
| Meaning-preserving | Does not reinterpret state outside owner context |

### 3.3 View Non-Meaning

A View is not:

1. a mutable handle,
2. a state owner,
3. a transition executor,
4. a registry mutation surface,
5. a bridge protocol object,
6. final delivery proof,
7. a replacement for report evidence.

---

## 4. Report Definition

### 4.1 Definition

A Report is an evidence artifact emitted after an action, transition, diagnostic check, invariant validation, boundary exposure, or profile event.

### 4.2 Report Properties

| Property | Meaning |
|---|---|
| Evidence | Records what happened or was detected |
| Immutable | Should be treated as immutable after emission |
| Scope-bound | Does not prove events outside its scope |
| Traceable | Connects component, state, action, issue, and time/sequence where applicable |
| Diagnostic-ready | Can support diagnostics and compliance-like checks |
| Non-executing | Does not perform action |

### 4.3 Report Non-Meaning

A Report is not:

1. downstream success proof,
2. bridge protocol completion,
3. receiver acknowledgement,
4. persistence proof,
5. mutation authority,
6. retry instruction by default.

---

## 5. View vs Report

| Dimension | View | Report |
|---|---|---|
| Time | current / snapshot | event / transition evidence |
| Mutability | read-only | immutable evidence |
| Purpose | observe current condition | record what happened |
| Consumer | diagnostics, tests, other components | diagnostics, trace, audits, tests |
| Scope | current owner state | event scope |
| Example | `TContainerStateView` | `TContainerStateTransitionReport` |

---

## 6. View Inventory

## 6.1 Bundle / Capacity Views

| View | Owner | Purpose |
|---|---|---|
| `TBundleTopologyView` | BundleAgent | Shows active container family topology |
| `TUniformCapacityProfileView` | BundleAgent | Shows active uniform capacity profile |
| `TContainerFamilyView` | BundleAgent | Shows container family identity and profile |
| `TBundleAgentStateView` | BundleAgent | Shows scaling/profile state |

## 6.2 Registry Views

| View | Owner | Purpose |
|---|---|---|
| `TContainerRegistryView` | TContainerRegistry | Shows registry-level index/container status |
| `TContainerRegistryCapacityView` | TContainerRegistry | Shows registry capacity profile |
| `TContainerRegistrySlotLayoutView` | TContainerRegistry | Shows uniform layout view |
| `TContainerRegistryGenerationView` | TContainerRegistry | Shows registry generation/version if modeled |

## 6.3 Container Views

| View | Owner | Purpose |
|---|---|---|
| `TContainerView` | TContainer | Read-only projection of container identity/state |
| `TContainerStateView` | TContainer / Moderator | Container operational state |
| `TContainerSlotLayoutView` | TContainer | Slot layout/capacity |
| `TContainerTimeRangeView` | TContainer | Time range metadata |
| `TContainerDispatchReadinessView` | TContainer | Dispatch eligibility/readiness |
| `TContainerSafePointView` | TContainer / Moderator | Reset/profile safe-point readiness |

## 6.4 Slot Views

| View | Owner | Purpose |
|---|---|---|
| `TSlotView` | TSlot | Slot projection |
| `TSlotStateView` | TSlot | Slot lifecycle state |
| `TSlotOccupancyView` | TSlot | Envelope occupancy relation |
| `TSlotAccessView` | TSlot / access policy | Access readiness |
| `TSlotReleaseView` | TSlot | Release/recycle readiness |

## 6.5 Waiting List Views

| View | Owner | Purpose |
|---|---|---|
| `TIngressWaitingListView` | TIngressWaitingList | Ordered ingress candidate indices |
| `TIngressEligibilityView` | Ingress waiting list / RoundManager | Ingress eligibility projection |
| `TDispatchWaitingListView` | TDispatchWaitingList | Ordered dispatch candidate indices |
| `TDispatchOrderingView` | TDispatchWaitingList | FIFO/time-range ordering |
| `TDispatchEvictionCandidateView` | TDispatchWaitingList | Eviction candidates |

## 6.6 Round Views

| View | Owner | Purpose |
|---|---|---|
| `TRoundView` | RoundManager | Round state and kind |
| `TRoundStateView` | RoundManager | Round lifecycle state |
| `TRoundMembershipView` | RoundManager | Round members |
| `TRoundEligibilityView` | RoundManager | Candidate eligibility |
| `TRoundSafePointView` | RoundManager | Round closure/completion safe-point |

## 6.7 Reference Views

| View | Owner | Purpose |
|---|---|---|
| `TReferenceSupplyView` | ReferencePrecalculator | Overall reference supply |
| `TIngressReferenceSupplyView` | ReferencePrecalculator | Ingress ref supply |
| `TDispatchReferenceSupplyView` | ReferencePrecalculator | Dispatch ref supply |
| `TReferenceValidityView` | Reference validity policy | Validity state |
| `TReferenceScopeView` | Reference validity policy | Scope dimensions |
| `TReferenceInvalidationView` | ReferencePrecalculator | Pending invalidations |
| `TReferenceGenerationView` | Reference validity policy | Registry/profile generation binding |

## 6.8 Ingress Views

| View | Owner | Purpose |
|---|---|---|
| `TIngressView` | Ingress | Ingress actor state |
| `TIngressAdmissionView` | Ingress / boundary | Admission readiness |
| `TIngressPlacementView` | Ingress | Current/last placement projection |
| `TIngressReferenceConsumptionView` | Ingress | Ref consumption status |

## 6.9 Dispatch / Boundary Views

| View | Owner | Purpose |
|---|---|---|
| `TDispatchExposureView` | Dispatcher | Current output exposure |
| `TDispatchReadyView` | Dispatcher | Dispatch readiness |
| `TDispatcherView` | Dispatcher | Dispatcher state |
| `TDispatchBoundaryView` | Dispatcher / binding | Output boundary state |
| `TBridgeDrainAssumptionView` | Dispatch boundary profile | Drain assumption state |
| `TBoundaryDelegationView` | Boundary profile | Which side owns delay/retry |
| `TPreBridgeProfileView` | Profile | Pre-bridge configuration |
| `TReadSideProfileView` | Profile | Read-side profile needs |

---

## 7. Report Inventory

## 7.1 Bundle / Capacity Reports

| Report | Trigger |
|---|---|
| `TBundleScalingReport` | Horizontal/vertical scaling event |
| `TDefaultEmptyContainerProfileReport` | Default empty profile created/changed |
| `TCapacityProfileSwitchReport` | Capacity profile switch |
| `TBundleInvariantReport` | Bundle-level invariant violation |
| `TProfileSwitchReadinessReport` | Safe profile switch readiness |
| `TProfileSwitchAppliedReport` | Profile switch applied |

## 7.2 Registry Reports

| Report | Trigger |
|---|---|
| `TContainerRegistryInitializationReport` | Registry initialized |
| `TContainerRegistryInvariantReport` | Registry invariant check |
| `TRegistryProfileSwitchReport` | Registry profile/generation switch |
| `TRegistryIndexInvalidationReport` | Registry index invalidated |
| `TDanglingWaitingListIndexReport` | Waiting list references stale index |

## 7.3 Container Reports

| Report | Trigger |
|---|---|
| `TContainerStateTransitionReport` | Container state changed |
| `TContainerResetReport` | Moderator reset applied |
| `TContainerReleaseReport` | Container released |
| `TContainerRecycleReport` | Container recycled |
| `TContainerEvictionReport` | Container evicted |
| `TContainerTimeRangeReport` | Time range updated |

## 7.4 Slot Reports

| Report | Trigger |
|---|---|
| `TSlotTransitionReport` | Slot state changed |
| `TSlotOccupancyReport` | Occupancy relation created/changed |
| `TSlotReleaseReport` | Slot released |
| `TSlotAccessViolationReport` | Invalid access attempt |
| `TSlotStateMismatchReport` | Slot state mismatch detected |

## 7.5 Waiting List Reports

| Report | Trigger |
|---|---|
| `TIngressWaitingListRegistrationReport` | Candidate added |
| `TIngressWaitingListDrainReport` | List consumed |
| `TIngressWaitingListInvariantReport` | List invariant broken |
| `TDispatchWaitingListRegistrationReport` | Dispatch candidate added |
| `TDispatchWaitingListDrainReport` | List consumed |
| `TDispatchEvictionSelectionReport` | Eviction candidate selected |
| `TDispatchWaitingListInvariantReport` | List invariant broken |

## 7.6 Round Reports

| Report | Trigger |
|---|---|
| `TRoundAdmissionReport` | Container admitted |
| `TRoundProgressionReport` | Round transitioned |
| `TRoundClosureReport` | Round closed |
| `TRoundInvariantReport` | Round invariant violation |
| `TRoundMembershipReport` | Round membership frozen/emitted |

## 7.7 Reference Reports

| Report | Trigger |
|---|---|
| `TReferencePrecalculationReport` | References prepared |
| `TReferenceSupplyInterruptionReport` | Expected supply interrupted |
| `TReferenceInvalidationReport` | References invalidated |
| `TStaleReferenceReport` | Stale ref detected |
| `TReferenceCandidateRejectionReport` | Candidate rejected |
| `TReferenceDirectionMismatchReport` | Wrong ref direction |
| `TReferenceGenerationMismatchReport` | Old registry/profile generation |

## 7.8 Ingress Reports

| Report | Trigger |
|---|---|
| `TIngressPlacementReport` | Envelope placed |
| `TIngressAccessReport` | Ingress ref consumed |
| `TIngressInvariantReport` | Ingress invariant broken |
| `TIngressBoundaryReport` | Producer/boundary mismatch |

## 7.9 Dispatch / Boundary Reports

| Report | Trigger |
|---|---|
| `TDispatchExposureReport` | Exposure created |
| `TPassiveExposureReport` | Passive exposure made available |
| `TBridgePullObservationReport` | Bridge pull observed |
| `TPushDispatchAttemptReport` | Push attempted |
| `TDispatchBoundaryReport` | Boundary event |
| `TBoundaryAssumptionBrokenReport` | Drain assumption violated |
| `TDispatchExposureReleaseReport` | Exposure released |

## 7.10 Release / Recycle Reports

| Report | Trigger |
|---|---|
| `TReferenceReleaseReport` | Ref consumed/invalidated |
| `TExposureReleaseReport` | Exposure closed |
| `TReentryEligibilityReport` | Container can reenter ingress |
| `TResetAppliedReport` | Reset applied |
| `TEvictionAppliedReport` | Eviction applied |

---

## 8. View Exposure Rules

### 8.1 Allowed View Consumers

Views may be consumed by:

1. local component owner,
2. dependent actor through approved public surface,
3. diagnostics layer,
4. tests,
5. report generation logic,
6. boundary adapter where explicitly allowed.

### 8.2 Forbidden View Consumers

Views must not expose internal mutability to:

1. Log API internals,
2. bridge protocol internals,
3. final receiver,
4. add-on internals,
5. generic external consumers,
6. unapproved cross-domain code.

### 8.3 View Stability Types

```text
snapshot
live_readonly
round_scoped
profile_scoped
diagnostic_only
boundary_safe
```

---

## 9. Report Authority Rules

### 9.1 Report Scope Rule

A report proves only what it reports.

Examples:

```text
TDispatchExposureReport proves exposure was created.
It does not prove bridge delivery.

TContainerResetReport proves reset was applied.
It does not prove future ingress use.

TReferenceConsumedReport proves ref consumption.
It does not prove payload lifecycle completion.
```

### 9.2 Report Non-Expansion Rule

Reports must not expand engine authority.

### 9.3 Report Immutability Rule

A report should be immutable after emission.

### 9.4 Report Trace Fields

Recommended report fields:

```text
report_id
component_id
event_kind
state_before
state_after
affected_container_index
affected_slot_index
round_id
reference_id
profile_generation
issue_kind
severity
timestamp_or_sequence
notes
```

---

## 10. Implementation Derivation Notes

### 10.1 Candidate View Folders

```text
*/views/
```

Views should generally live under the component that owns the viewed meaning.

### 10.2 Candidate Report Folders

Possible options:

```text
*/reports/
*/carriers/
diagnostics/reports/
```

Final placement deferred to file inventory derivation.

### 10.3 Deferred Decisions

1. Whether reports are local carriers or diagnostics root artifacts.
2. Whether views carry generation tokens.
3. Whether views are snapshots or live references in first implementation.
4. Whether all reports require stable report IDs from day one.

---

## 11. Summary

Views keep observation safe.  
Reports preserve evidence.  
Neither grants mutation authority.  
Neither proves downstream success unless a later boundary contract explicitly says so.
