# CME-IMPL-003 — Test And Compliance Derivation Plan

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-IMPL-003-DOC-001 | Document Title | Test And Compliance Derivation Plan |
| CME-IMPL-003-DOC-002 | Package | CME-IMPL-PLAN-00 |
| CME-IMPL-003-DOC-003 | Scope Level | Test derivation, negative tests, compile smoke tests, architecture compliance checks |
| CME-IMPL-003-DOC-004 | Status | Implementation Planning Draft |
| CME-IMPL-003-DOC-005 | Primary Rule | Every implementation wave must include a smoke test and at least one architecture-preserving check where meaningful |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the test and compliance strategy for CME implementation waves.

It answers:

```text
How do we protect the architecture during implementation so that headers do not
collapse component boundaries or silently invent runtime ownership?
```

---

## 3. Test Families

## 3.1 Compile Smoke Tests

Purpose:

```text
Verify candidate headers compile under C++17.
```

Naming:

```text
cme_wXX_<wave_name>_smoke_test.cpp
```

## 3.2 Contract Preservation Tests

Purpose:

```text
Verify public surfaces preserve architecture meaning.
```

Examples:

```text
container_is_not_broker_test
waiting_list_no_envelope_storage_test
dispatcher_no_bridge_ownership_test
```

## 3.3 Negative Anti-Collapse Tests

Purpose:

```text
Ensure forbidden usage fails to compile or is clearly rejected.
```

Examples:

```text
dispatch_ref_used_as_ingress_ref_negative_test
mutable_container_in_bridge_boundary_negative_test
reset_outside_safe_point_negative_test
```

## 3.4 State Transition Tests

Purpose:

```text
Verify state transitions and invalid transitions.
```

Examples:

```text
slot_state_machine_test
container_state_machine_test
round_closed_registration_negative_test
```

## 3.5 View / Report Tests

Purpose:

```text
Verify views are read-only and reports are evidence-only.
```

Examples:

```text
view_no_mutation_test
report_non_authority_test
```

---

## 4. Compliance Assertions

## 4.1 Identity Assertions

1. Container is not broker.
2. Dispatcher is not bridge.
3. Waiting list is not envelope store.
4. Reference is not raw pointer.
5. Report is not downstream proof.
6. View is not mutable handle.

## 4.2 Boundary Assertions

1. Log API does not see container internals.
2. Bridge does not mutate container internals.
3. Read-side retry is not pre-bridge default.
4. Copy/move semantics are outside CME.

## 4.3 State Assertions

1. Slot state differs from container state.
2. Container state differs from round state.
3. Reset requires safe point.
4. Profile switch invalidates old refs.
5. Eviction requires safe point.

## 4.4 Reference Assertions

1. Ingress refs cannot be dispatch refs.
2. Dispatch refs cannot be ingress refs.
3. Consumed refs cannot be reused.
4. Stale refs are diagnostic-visible.

---

## 5. Test Matrix

| Wave | Smoke Test | Negative / Compliance Test |
|---:|---|---|
| W01 | foundational types compile | state enum categories distinct |
| W02 | views/reports compile | view no mutation |
| W03 | capacity profiles compile | uniform capacity invariant |
| W04 | slot/container compile | container state not slot state |
| W05 | registry compile | invalid index rejected |
| W06 | bundle/moderator compile | reset requires safe point |
| W07 | waiting/round compile | waiting list no envelope storage |
| W08 | refs compile | direction mismatch rejected |
| W09 | precalculator compile | no payload inspection |
| W10 | ingress compile | ingress requires ref |
| W11 | dispatcher compile | dispatcher no bridge ownership |
| W12 | safe/recycle compile | reset outside safe point rejected |
| W13 | eviction compile | eviction with active refs rejected |
| W14 | bindings compile | mutable internals not exposed |
| W15 | integrated compile | anti-collapse suite |

---

## 6. Readiness For First Implementation Wave

### 6.1 Must Exist Before W01

1. approved wave plan,
2. initial folder skeleton,
3. C++17 compile command,
4. test naming pattern,
5. decision on file naming convention,
6. decision on namespace baseline.

### 6.2 Must Not Be Required Before W01

1. final algorithms,
2. bridge integration,
3. read-side retry,
4. policy assignment,
5. central diagnostics collector.

---

## 7. Summary

Tests must protect the architecture, not merely compile code.

The first implementation phase should produce small, strongly named, boundary-safe headers with compile-only and anti-collapse tests.
