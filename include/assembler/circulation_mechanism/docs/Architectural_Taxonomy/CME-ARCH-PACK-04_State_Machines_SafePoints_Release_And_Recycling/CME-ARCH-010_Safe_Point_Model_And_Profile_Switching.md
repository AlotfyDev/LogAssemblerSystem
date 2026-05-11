# CME-ARCH-010 — Safe Point Model And Profile Switching

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-010-DOC-001 | Document Title | Safe Point Model And Profile Switching |
| CME-ARCH-010-DOC-002 | Package | CME-ARCH-PACK-04 |
| CME-ARCH-010-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-010-DOC-004 | Scope Level | Safe-point sources, safe-point states, profile switching, reset/scaling/eviction safety |
| CME-ARCH-010-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-010-DOC-006 | Implementation Direction | C++17, header-only-first, guarded transitions, profile-driven safe points |
| CME-ARCH-010-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-009 |
| CME-ARCH-010-DOC-008 | Related Models | `TContainerState`, `TSlotState`, `TRoundState`, `TReferenceSupplyState`, `TBundleAgentState`, `TModeratorState` |
| CME-ARCH-010-DOC-009 | Primary Rule | Reset, eviction, vertical scaling, registry rebuild, and reference invalidation require safe points |
| CME-ARCH-010-DOC-010 | Excluded | Global scheduler pause, OS thread coordination, bridge safe point, receiver acknowledgement lifecycle |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the safe-point model for the Circulation Mechanism Engine.

It answers:

```text
When is it safe to perform sensitive operations such as reset, vertical scaling,
profile switching, registry rebuild, eviction, or reference invalidation?
```

### 2.2 Core Thesis

```text
A safe point is a locally owned transition condition.
It is not a global stop-the-world event unless a profile explicitly declares it.
```

### 2.3 Why Safe Points Matter

Safe points prevent:

1. stale reference usage,
2. resetting active containers,
3. changing layout under active refs,
4. evicting exposed containers,
5. rebuilding registry while indices are in use,
6. violating uniform capacity.

---

## 3. Safe Point Definition

### 3.1 Definition

A safe point is a state or condition under which a sensitive transition may occur without breaking engine invariants.

### 3.2 Safe Point Ownership

Safe points are owned by the component whose state enables the operation.

Examples:

| Safe Point | Owner |
|---|---|
| slot recyclable | Slot |
| container reset-ready | Container/Moderator |
| round closed | RoundManager |
| references invalidated | ReferencePrecalculator |
| dispatch exposure closed | Dispatcher |
| profile-switch-ready | BundleAgent |
| registry rebuild safe | Registry + BundleAgent |

---

## 4. Safe Point Sources

| Source | Safe Point Examples |
|---|---|
| `TSlotState` | released, recyclable, empty |
| `TContainerState` | dispatch_completed, reset_pending, default_empty |
| `TRoundState` | closed, completed |
| `TModeratorState` | safe_point_confirmed |
| `TBundleAgentState` | profile_switch_ready |
| `TReferenceSupplyState` | invalidating_refs complete |
| `TDispatchExposureState` | bridge_consumed, exposure closed |

---

## 5. Safe Point State Model

### 5.1 Candidate States

```text
unavailable
pending
available
claimed
consumed
expired
violated
```

### 5.2 State Meaning

| State | Meaning |
|---|---|
| `unavailable` | Operation cannot safely occur |
| `pending` | Preconditions are being prepared |
| `available` | Operation may be performed |
| `claimed` | Operation has reserved the safe point |
| `consumed` | Safe point was used |
| `expired` | Safe point is no longer valid |
| `violated` | Operation attempted outside safe point |

### 5.3 Transition Sketch

```text
unavailable → pending → available → claimed → consumed
available → expired
pending → unavailable
any → violated
```

---

## 6. Safe-Point Required Operations

## 6.1 Container Reset

Requires:

1. container not in active ingress round,
2. container not in active dispatch round,
3. no active refs to its slots,
4. dispatch exposure closed,
5. container state reset_pending or dispatch_completed,
6. moderator ready to apply default empty profile.

## 6.2 Vertical Scaling

Requires:

1. bundle-level safe point,
2. all affected containers out of active rounds,
3. no active refs bound to old layout,
4. registry profile switch ready,
5. uniform capacity target profile prepared,
6. waiting lists rebuildable.

## 6.3 Uniform Capacity Profile Switch

Requires:

1. no active use of old capacity assumptions,
2. default empty container for new profile prepared,
3. registry rebuild or update safe,
4. reference invalidation complete,
5. round cycle boundary reached.

## 6.4 Registry Rebuild

Requires:

1. waiting lists locked/cleared,
2. refs invalidated or consumed,
3. round closed/completed,
4. no consumer holds registry-index-bound active ref,
5. bundle topology update authorized.

## 6.5 Eviction

Requires:

1. selected container is not active in ingress,
2. selected container is not active in dispatch exposure,
3. refs invalidated or consumed,
4. round state permits removal,
5. eviction policy selected candidate,
6. report emitted.

## 6.6 Reference Invalidation

Requires:

1. affected ref scope known,
2. affected registry generation/profile known,
3. consumers prevented from receiving old refs,
4. stale diagnostics enabled,
5. new refs regenerated if needed.

---

## 7. Vertical Scaling Model

### 7.1 Rule

```text
Vertical scaling changes the uniform capacity profile of the container family.
```

It does not resize one container independently.

### 7.2 Owner

`SlotsContainerBundleAgent` owns vertical scaling decision.

### 7.3 Executor

`SlotsContainerModerator` applies reset/reinitialization to concrete containers using the new default empty container profile.

### 7.4 Required Safe Points

1. bundle safe point,
2. container reset safe point,
3. reference invalidation safe point,
4. round closure safe point,
5. registry update safe point.

### 7.5 Invariant

```text
No active container may have a capacity/layout different from the active uniform capacity profile.
```

---

## 8. Container Reset Model

### 8.1 Owner

The reset operation on a concrete container is executed by its moderator.

### 8.2 Source Profile

The reset uses the default empty container profile supplied by BundleAgent.

### 8.3 Reset Preconditions

```text
container state = reset_pending or equivalent
dispatch exposure closed
refs consumed/invalidated
round membership closed
safe point available
```

### 8.4 Reset Result

```text
container state = default_empty
slot states = empty
container time range = cleared
dispatch exposure state = closed/reset
```

---

## 9. Profile Switching

### 9.1 Profile Types

| Profile | Meaning |
|---|---|
| `TUniformContainerCapacityProfile` | slots per container |
| `THorizontalScalingProfile` | container count |
| `TVerticalScalingProfile` | uniform capacity change |
| `TExtremeDefaultProfile` | pre-sized maximum/default extreme profile |
| `TDispatchExposureProfile` | passive/push/hybrid dispatch behavior |
| `TReferenceSupplyPolicy` | next-ref generation rules |

### 9.2 Profile Switch Rule

```text
A profile switch changes future behavior.
It must not retroactively mutate active access or exposed material.
```

### 9.3 Profile Switch Reports

1. `TProfileSwitchRequestReport`,
2. `TProfileSwitchReadinessReport`,
3. `TProfileSwitchAppliedReport`,
4. `TProfileSwitchRejectedReport`.

---

## 10. Safe-Point Invariants

```text
1. No reset outside safe point.
2. No eviction outside safe point.
3. No vertical scaling outside safe point.
4. No registry rebuild outside safe point.
5. No active ref survives incompatible safe-point operation.
6. Safe point ownership is local, not global by default.
7. Safe point evidence must be reportable.
8. Safe point violation is diagnostic-visible.
```

---

## 11. Views

| View | Purpose |
|---|---|
| `TSafePointView` | Generic safe-point projection |
| `TContainerSafePointView` | Container reset/readiness |
| `TRoundSafePointView` | Round closure/completion |
| `TReferenceInvalidationSafePointView` | Ref invalidation readiness |
| `TBundleProfileSwitchSafePointView` | Bundle-level switch readiness |
| `TRegistryRebuildSafePointView` | Registry safe rebuild |

---

## 12. Reports

| Report | Trigger |
|---|---|
| `TSafePointAvailabilityReport` | Safe point becomes available |
| `TSafePointClaimReport` | Operation claims safe point |
| `TSafePointConsumedReport` | Operation uses safe point |
| `TSafePointViolationReport` | Attempt outside safe point |
| `TScalingSafePointReport` | Scaling readiness |
| `TResetSafePointReport` | Container reset readiness |
| `TReferenceInvalidationSafePointReport` | Ref invalidation readiness |

---

## 13. Failure / Diagnostics

| Condition | Classification |
|---|---|
| `ResetOutsideSafePoint` | violation |
| `ScalingOutsideSafePoint` | violation |
| `EvictionOutsideSafePoint` | violation |
| `RegistryRebuildOutsideSafePoint` | violation |
| `ActiveReferenceDuringProfileSwitch` | invariant violation |
| `RoundStillOpenForReset` | round-state mismatch |
| `DispatchExposureStillActive` | exposure-state mismatch |

---

## 14. Implementation Derivation Notes

### 14.1 Candidate Headers

```text
safe_points/
    TSafePointState.hpp
    TSafePointView.hpp
    TSafePointPolicy.hpp
    TSafePointViolation.hpp

slots_container_bundle_agent/
    TProfileSwitchPlan.hpp
    TProfileSwitchReport.hpp

slots_container_moderator/
    TContainerResetSafePoint.hpp
```

### 14.2 Deferred Decisions

1. Whether safe points are a shared semantic root or local component subfolders.
2. Whether safe-point detection is runtime checked in release builds or only diagnostics.
3. Whether profile generation is mandatory.
4. Whether safe-point claims are one-shot tokens.

---

## 15. Summary

Safe points are the protection layer for sensitive transitions.  
They are local and profile-driven.  
They make reset, scaling, registry rebuild, eviction, and invalidation deterministic and auditable.
