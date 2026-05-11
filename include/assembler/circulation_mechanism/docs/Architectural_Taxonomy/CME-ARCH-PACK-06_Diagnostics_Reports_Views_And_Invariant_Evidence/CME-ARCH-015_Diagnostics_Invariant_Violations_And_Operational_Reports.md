# CME-ARCH-015 — Diagnostics Invariant Violations And Operational Reports

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-015-DOC-001 | Document Title | Diagnostics Invariant Violations And Operational Reports |
| CME-ARCH-015-DOC-002 | Package | CME-ARCH-PACK-06 |
| CME-ARCH-015-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-015-DOC-004 | Scope Level | Diagnostics, invariant violations, operational events, diagnostic reporting |
| CME-ARCH-015-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-015-DOC-006 | Implementation Direction | C++17, header-only-first, diagnostic-visible, report-driven |
| CME-ARCH-015-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-014 |
| CME-ARCH-015-DOC-008 | Related Models | Views, reports, state machines, reference validity, safe points, dispatch boundary |
| CME-ARCH-015-DOC-009 | Primary Rule | Invariant violations and operational anomalies must be diagnostic-visible without exposing mutable internals |
| CME-ARCH-015-DOC-010 | Excluded | Logging framework implementation, persistence, telemetry exporter, bridge recovery, receiver retry |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the diagnostics model for the Circulation Mechanism Engine.

It answers:

```text
How does the engine classify and report invariant violations, profile failures,
reference faults, state mismatches, safe-point violations, eviction events, and
boundary assumption failures?
```

### 2.2 Core Thesis

```text
Diagnostics describe abnormal or important operational conditions.
Diagnostics do not become hidden control flow.
```

### 2.3 Diagnostic Role

Diagnostics support:

1. development correctness,
2. smoke tests,
3. compliance checks,
4. production readiness,
5. invariant enforcement,
6. boundary protection,
7. failure triage,
8. observability.

---

## 3. Diagnostic Categories

| Category | Meaning |
|---|---|
| `invariant_violation` | An engine rule was broken |
| `state_mismatch` | State did not match expected transition/access |
| `reference_fault` | Reference invalid, stale, or directionally wrong |
| `safe_point_violation` | Sensitive operation attempted outside safe point |
| `profile_failure` | Configured profile guarantee was broken |
| `boundary_assumption_failure` | External/boundary expectation failed |
| `eviction_event` | Eviction selected/applied/rejected |
| `operational_report` | Significant non-error event |
| `diagnostic_only` | Observation for tests/trace only |

---

## 4. Core Diagnostic Inventory

## 4.1 Invariant Violation

| Diagnostic | Meaning |
|---|---|
| `TInvariantViolationReport` | Generic invariant violation |
| `TBundleInvariantReport` | Bundle/capacity/topology invariant broken |
| `TContainerRegistryInvariantReport` | Registry invariant broken |
| `TContainerStateMismatchReport` | Container state mismatch |
| `TSlotStateMismatchReport` | Slot state mismatch |
| `TRoundInvariantReport` | Round invariant broken |
| `TWaitingListInvariantReport` | Waiting-list invariant broken |
| `TDispatcherInvariantReport` | Dispatcher invariant broken |

## 4.2 Reference Diagnostics

| Diagnostic | Meaning |
|---|---|
| `TReferenceSupplyInterruptionReport` | Continuous next-ref supply failed |
| `TStaleReferenceReport` | Stale reference use detected |
| `TReferenceDirectionMismatchReport` | Ingress/dispatch ref misuse |
| `TReferenceGenerationMismatchReport` | Old registry/profile generation |
| `TReferenceInvalidationReport` | Ref invalidated |
| `TReferenceCandidateRejectionReport` | Candidate rejected during precalc |

## 4.3 Safe Point Diagnostics

| Diagnostic | Meaning |
|---|---|
| `TSafePointViolationReport` | Operation attempted outside safe point |
| `TResetSafePointReport` | Reset safe point readiness |
| `TScalingSafePointReport` | Scaling safe point readiness |
| `TReferenceInvalidationSafePointReport` | Ref invalidation readiness |
| `TRegistryRebuildSafePointReport` | Registry rebuild readiness |

## 4.4 Eviction Diagnostics

| Diagnostic | Meaning |
|---|---|
| `TEvictionSelectionReport` | Candidate selected |
| `TEvictionAppliedReport` | Eviction applied |
| `TEvictionRejectedReport` | Eviction rejected |
| `TContainerTimeRangeViolationReport` | Time range invalid |
| `TEvictionWithoutSafePointReport` | Unsafe eviction attempt |

## 4.5 Boundary Diagnostics

| Diagnostic | Meaning |
|---|---|
| `TBridgeDrainAssumptionReport` | Drain state observation |
| `TBoundaryAssumptionBrokenReport` | Bridge drain assumption broken |
| `TDispatchBoundaryReport` | Output boundary event |
| `TOutputBoundaryBindingMismatchReport` | Adapter/profile mismatch |
| `TMutableInternalExposureViolationReport` | Boundary attempted mutable internal access |
| `TCopyMoveOwnershipViolationReport` | CME attempted to own bridge transfer semantics |

---

## 5. Major Diagnostics Required By Current Model

## 5.1 `InvariantViolationReport`

### 5.1.1 Purpose

Reports a violation of a declared CME invariant.

### 5.1.2 Typical Sources

1. registry,
2. container,
3. slot,
4. waiting list,
5. round manager,
6. reference precalculator,
7. dispatcher,
8. safe-point policy.

### 5.1.3 Required Fields

```text
component_id
invariant_id
expected_condition
observed_condition
affected_state
severity
recovery_hint
```

## 5.2 `ReferenceSupplyInterrupted`

### 5.2.1 Purpose

Reports failure to maintain ready next-ref supply under a profile that expects continuous supply.

### 5.2.2 Meaning

This is not a normal consumer-facing error. It indicates:

1. capacity profile failure,
2. waiting-list shortage,
3. registry inconsistency,
4. reference invalidation storm,
5. broken round/slot/container state assumptions.

### 5.2.3 Required Fields

```text
reference_kind
direction
waiting_list_state
round_state
profile_id
supply_depth_expected
supply_depth_observed
```

## 5.3 `ContainerStateMismatch`

### 5.3.1 Purpose

Reports that a container state is incompatible with an attempted action.

### 5.3.2 Examples

1. container in dispatch list but not dispatch-ready,
2. container in ingress list but under moderation,
3. container reset attempted while in active round,
4. container evicted but referenced by waiting list.

## 5.4 `RoundStateViolation`

### 5.4.1 Purpose

Reports an illegal round action or transition.

### 5.4.2 Examples

1. candidate registered after round closed,
2. waiting list drained before round locked,
3. round completed while refs still active,
4. duplicate membership not allowed.

## 5.5 `SafePointViolation`

### 5.5.1 Purpose

Reports an operation attempted without a required safe point.

### 5.5.2 Examples

1. reset outside safe point,
2. vertical scaling outside safe point,
3. eviction outside safe point,
4. registry rebuild outside safe point,
5. reference invalidation performed incorrectly.

## 5.6 `EvictionReport`

### 5.6.1 Purpose

Reports eviction selection or application.

### 5.6.2 Subtypes

```text
selection
applied
rejected
unsafe_attempt
time_range_invalid
```

## 5.7 `BridgeDrainAssumptionBroken`

### 5.7.1 Purpose

Reports that the bridge-facing side did not drain output exposure as expected by the pre-bridge profile.

### 5.7.2 Meaning

This does not automatically create pre-bridge retry ownership.  
The condition is normally delegated to read-side or bridge/read-side profile modeling.

---

## 6. Diagnostic Event Flow

### 6.1 Detection

A diagnostic event may be detected by:

1. component state guard,
2. transition guard,
3. reference validity policy,
4. waiting-list membership check,
5. round state check,
6. safe-point evaluator,
7. boundary profile evaluator,
8. eviction policy.

### 6.2 Classification

The detector classifies the event into a diagnostic category.

### 6.3 Report Creation

The component emits a report with:

1. owner,
2. component id,
3. state,
4. expected condition,
5. observed condition,
6. severity,
7. suggested owner of next action.

### 6.4 Consumption

Reports may be consumed by:

1. diagnostics surface,
2. tests,
3. production readiness checks,
4. future monitoring/export boundary,
5. local component owner.

### 6.5 Non-Consumption

Reports are not automatically:

1. retries,
2. bridge actions,
3. receiver actions,
4. persistence writes,
5. policy executions.

---

## 7. Severity Model

| Severity | Meaning |
|---|---|
| `trace` | informational trace |
| `info` | normal operational event |
| `warning` | possible issue but engine may continue |
| `error` | local component invariant broken |
| `critical` | engine-wide profile/invariant threatened |
| `fatal` | engine cannot preserve correctness under current profile |

---

## 8. Diagnostic Ownership

| Diagnostic Area | Owner |
|---|---|
| bundle/capacity | BundleAgent |
| container reset/moderation | Moderator |
| registry index/storage | TContainerRegistry |
| container lifecycle | TContainer |
| slot lifecycle | TSlot |
| waiting-list membership | WaitingList |
| round lifecycle | RoundManager |
| reference validity | ReferencePrecalculator / validity policy |
| ingress placement | Ingress |
| dispatch exposure | Dispatcher |
| output boundary | Dispatcher / communication binding |

---

## 9. Recovery Ownership

### 9.1 Local Recovery

Some diagnostics may be locally recoverable:

1. rebuild waiting list,
2. invalidate refs,
3. reject candidate,
4. wait for safe point,
5. emit report and continue.

### 9.2 Profile-Level Recovery

Some diagnostics require profile-level decision:

1. capacity profile exhaustion,
2. bridge drain assumption broken,
3. eviction required,
4. vertical scaling required.

### 9.3 Out-of-Scope Recovery

Some diagnostics belong outside pre-bridge CME:

1. receiver delay,
2. receiver retry,
3. final delivery failure,
4. persistence failure,
5. bridge session failure.

---

## 10. Invariant Violation Matrix

| Invariant | Violation Report | Owner |
|---|---|---|
| uniform container capacity | `TBundleInvariantReport` | BundleAgent |
| valid registry index | `TContainerRegistryInvariantReport` | Registry |
| no envelope in waiting list | `TWaitingListInvariantReport` | WaitingList |
| no candidate in closed round | `TRoundInvariantReport` | RoundManager |
| no access without valid ref | `TReferenceDirectionMismatchReport` / `TStaleReferenceReport` | ReferencePrecalculator |
| no reset outside safe point | `TSafePointViolationReport` | Moderator/SafePoint |
| no mutable internal boundary exposure | `TMutableInternalExposureViolationReport` | Dispatcher/Boundary |
| no final delivery claim | `TDispatchBoundaryReport` / boundary violation | Dispatcher |

---

## 11. Operational Reports

Operational reports are not errors. They record meaningful activity.

Examples:

1. `TIngressPlacementReport`,
2. `TDispatchExposureReport`,
3. `TRoundAdmissionReport`,
4. `TRoundClosureReport`,
5. `TContainerResetReport`,
6. `TReferencePrecalculationReport`,
7. `TBundleScalingReport`,
8. `TCapacityProfileSwitchReport`.

---

## 12. Diagnostic Reports vs Operational Reports

| Dimension | Diagnostic Report | Operational Report |
|---|---|---|
| Purpose | abnormal condition | meaningful normal event |
| Severity | warning/error/critical/fatal | trace/info |
| Effect | may block/alert/escalate | records progress |
| Example | `SafePointViolation` | `ContainerResetReport` |
| Recovery | may require action | often none |

---

## 13. Boundary Diagnostics

### 13.1 Bridge Drain Assumption

If bridge drain assumption breaks:

```text
emit report
do not become retry engine by default
delegate concern to read-side/bridge profile
```

### 13.2 Mutable Internal Exposure

If boundary tries to access private internals:

```text
block exposure
emit violation
preserve boundary
```

### 13.3 Copy/Move Ownership Violation

If CME attempts to own bridge copy/move semantics:

```text
diagnostic violation
profile review required
```

---

## 14. Implementation Derivation Notes

### 14.1 Candidate Diagnostic Headers

```text
diagnostics/
    TDiagnosticSeverity.hpp
    TDiagnosticCategory.hpp
    TInvariantViolationReport.hpp
    TOperationalReport.hpp
    TDiagnosticIssue.hpp
    TDiagnosticCollector.hpp
```

### 14.2 Local Component Reports

Reports may also remain local:

```text
round_manager/reports/
dispatcher/reports/
reference_precalculator/reports/
slots_container/reports/
```

### 14.3 Deferred Decisions

1. Central diagnostics root vs local reports only.
2. Severity enum naming.
3. Whether reports are zero-allocation.
4. Whether diagnostics are compile-time removable.
5. Whether boundary reports are exportable outside process.

---

## 15. Summary

Diagnostics make engine correctness visible.  
Invariant violations are not hidden control flow.  
Operational reports preserve trace.  
Views prevent internal leakage.  
Reports prevent trace loss.
