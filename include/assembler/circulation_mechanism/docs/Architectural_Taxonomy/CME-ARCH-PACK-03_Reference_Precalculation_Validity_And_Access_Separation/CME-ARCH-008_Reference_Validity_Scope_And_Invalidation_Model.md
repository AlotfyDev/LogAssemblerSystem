# CME-ARCH-008 — Reference Validity Scope And Invalidation Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-008-DOC-001 | Document Title | Reference Validity Scope And Invalidation Model |
| CME-ARCH-008-DOC-002 | Package | CME-ARCH-PACK-03 |
| CME-ARCH-008-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-008-DOC-004 | Scope Level | Reference validity, reference scope, invalidation, stale diagnostics |
| CME-ARCH-008-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-008-DOC-006 | Implementation Direction | C++17, header-only-first, scoped reference discipline |
| CME-ARCH-008-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-007 |
| CME-ARCH-008-DOC-008 | Related Models | `TIngressAccessRef`, `TDispatchAccessRef`, `TSlotAccessRef`, `TRoundScopedRef`, `TNextRefToken`, `TReferenceValidityPolicy` |
| CME-ARCH-008-DOC-009 | Primary Rule | Every access reference is valid only within its declared scope and must be invalidated on incompatible state/profile/round transitions |
| CME-ARCH-008-DOC-010 | Excluded | General pointer safety implementation, memory allocator design, bridge acknowledgement lifecycle, external reference ownership |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the reference validity model for the Circulation Mechanism Engine.

It answers:

```text
When is a precomputed access reference valid, when does it expire or become
invalid, and how does the engine detect or report stale reference use?
```

### 2.2 Core Thesis

```text
A reference is not valid because it exists.
A reference is valid only because its scope remains true.
```

### 2.3 Validity Scope

A reference may be scoped by:

1. round,
2. container state,
3. slot state,
4. registry index,
5. direction,
6. safe point,
7. exposure lifecycle,
8. profile version.

---

## 3. Reference Type Inventory

## 3.1 `TIngressAccessRef`

| Field | Value |
|---|---|
| Direction | outside → engine |
| Consumer | Ingress / producer-facing placement path |
| Access | write/place envelope into slot |
| Scope | ingress round + container state + slot state |
| Invalidated By | reset, round close, slot state change, profile switch, eviction |

## 3.2 `TDispatchAccessRef`

| Field | Value |
|---|---|
| Direction | engine → outside |
| Consumer | Dispatcher / bridge-facing output path |
| Access | read/expose dispatch-ready material |
| Scope | dispatch round + exposure lifecycle + container/slot state |
| Invalidated By | dispatch round close, exposure closure, reset, eviction, profile switch |

## 3.3 `TSlotAccessRef`

| Field | Value |
|---|---|
| Direction | abstract / internal |
| Consumer | internal specialization |
| Access | slot-local access basis |
| Scope | slot state + container state |
| Invalidated By | slot transition, container reset, profile switch |

## 3.4 `TRoundScopedRef`

| Field | Value |
|---|---|
| Direction | any |
| Consumer | internal validity wrapper |
| Access | reference validity bound to round |
| Scope | round id/state |
| Invalidated By | round close, round abort, round rebuild |

## 3.5 `TNextRefToken`

| Field | Value |
|---|---|
| Direction | consumer-facing rhythm |
| Consumer | approved external-facing consumer |
| Access | obtains/represents next prepared ref |
| Scope | supply policy + consumer profile |
| Invalidated By | supply interruption, boundary mismatch, profile switch |

---

## 4. Reference Validity State Model

### 4.1 Candidate States

```text
prepared
issued
consumed
expired
invalidated
stale_detected
blocked_by_state
```

### 4.2 State Meaning

| State | Meaning |
|---|---|
| `prepared` | Ref has been calculated but not issued |
| `issued` | Ref is available to consumer |
| `consumed` | Ref was used successfully |
| `expired` | Ref outlived its scope |
| `invalidated` | Ref explicitly cancelled by transition |
| `stale_detected` | Ref was used after becoming invalid |
| `blocked_by_state` | Ref cannot be used because state changed |

### 4.3 Transition Sketch

```text
prepared → issued
issued → consumed
issued → expired
issued → invalidated
expired → stale_detected
invalidated → stale_detected
issued → blocked_by_state
blocked_by_state → invalidated
```

---

## 5. Scope Dimensions

### 5.1 Registry Scope

A reference tied to a container must include or imply a valid registry index.

Invalidation triggers:

1. registry rebuild,
2. index invalidation,
3. container removal,
4. topology profile switch,
5. container eviction.

### 5.2 Container Scope

A reference is valid only if the target container state remains compatible.

Ingress-compatible states may include:

```text
default_empty
ingress_ready
receiving
```

Dispatch-compatible states may include:

```text
dispatch_candidate
dispatch_ready
dispatch_exposed
```

### 5.3 Slot Scope

A reference is valid only if slot state matches the access.

Ingress slot states:

```text
empty
reserved_for_ingress
```

Dispatch slot states:

```text
sealed
dispatch_ready
dispatch_exposed
```

### 5.4 Round Scope

A reference may be bound to:

1. ingress round,
2. dispatch round,
3. round membership snapshot,
4. round closure boundary.

### 5.5 Direction Scope

```text
ingress ref ≠ dispatch ref
dispatch ref ≠ ingress ref
```

Direction mismatch is always an error.

### 5.6 Safe-Point Scope

A safe-point operation may invalidate references before reset/scaling/eviction.

### 5.7 Profile Scope

A reference prepared under one capacity/layout profile must not survive a profile switch unless explicitly transformed.

---

## 6. Invalidation Triggers

| Trigger | Affected References |
|---|---|
| Container reset | refs to that container/slots |
| Vertical scaling | refs bound to old layout/profile |
| Uniform capacity profile switch | all layout-bound refs |
| Registry rebuild | registry-index-bound refs |
| Container eviction | refs to evicted container |
| Round close | round-scoped refs |
| Round abort | all refs for that round |
| Slot state transition | refs to that slot if incompatible |
| Dispatch exposure closure | dispatch refs for exposure |
| Bridge pull observation | may consume or close dispatch ref depending policy |

---

## 7. Stale Reference Diagnostics

### 7.1 Stale Reference Definition

A stale reference is a reference that was once valid but is used after its scope has expired or been invalidated.

### 7.2 Stale Conditions

1. Ref used after round closure.
2. Ref used after container reset.
3. Ref used after profile switch.
4. Ref used after container eviction.
5. Ref used after slot state transition.
6. Ref used by wrong direction consumer.
7. Ref consumed twice.
8. Ref issued under old registry generation.

### 7.3 Diagnostics

| Diagnostic | Meaning |
|---|---|
| `StaleReferenceDetected` | Generic stale use |
| `ReferenceScopeViolation` | Ref used outside declared scope |
| `ReferenceInvalidatedByReset` | Reset invalidated ref |
| `ReferenceInvalidatedByProfileSwitch` | Profile switch invalidated ref |
| `ReferenceConsumedTwice` | One-shot ref reused |
| `ReferenceDirectionMismatch` | Wrong consumer/direction |
| `ReferenceRegistryGenerationMismatch` | Old registry generation |

---

## 8. Reference Validity Invariants

```text
1. A reference must declare or imply direction.
2. A reference must declare or imply scope.
3. A reference must not survive incompatible state transition.
4. A reference must not survive incompatible profile switch.
5. A consumed one-shot ref cannot be reused.
6. A stale ref must be diagnostic-visible.
7. A reference is never a bridge protocol handle.
8. A reference is never a downstream receiver handle.
```

---

## 9. Access Use Rules

### 9.1 Ingress Use

`Ingress` may consume an ingress ref only if:

1. ref state is `issued`,
2. direction is ingress,
3. round scope is valid,
4. container state is compatible,
5. slot state is writable,
6. producer provides prepared envelope.

### 9.2 Dispatch Use

`Dispatcher` may consume a dispatch ref only if:

1. ref state is `issued`,
2. direction is dispatch,
3. round scope is valid,
4. container state is compatible,
5. slot state is dispatch-ready,
6. output exposure profile is active.

### 9.3 Consumer Non-Authority

Consumers do not decide validity by themselves.  
They consume references provided by the engine; validity checks belong to the access/ref policy layer.

---

## 10. Validity Policy

### 10.1 Policy Inputs

1. reference kind,
2. direction,
3. round id/state,
4. registry generation,
5. container id/index/state,
6. slot id/index/state,
7. profile generation,
8. safe-point status,
9. consumption status.

### 10.2 Policy Outputs

1. valid,
2. expired,
3. invalidated,
4. blocked_by_state,
5. stale_detected,
6. direction_mismatch,
7. generation_mismatch.

### 10.3 Policy Non-Meaning

`TReferenceValidityPolicy` is not:

1. a payload validator,
2. bridge validator,
3. final receiver acknowledgement,
4. memory allocator,
5. ownership transfer proof.

---

## 11. Views

| View | Purpose |
|---|---|
| `TReferenceValidityView` | Show current validity |
| `TReferenceScopeView` | Show scope dimensions |
| `TReferenceInvalidationView` | Show pending invalidation |
| `TStaleReferenceDiagnosticView` | Show stale usage |
| `TReferenceGenerationView` | Show registry/profile generation binding |

---

## 12. Reports

| Report | Trigger |
|---|---|
| `TReferenceIssuedReport` | Ref issued |
| `TReferenceConsumedReport` | Ref consumed |
| `TReferenceExpiredReport` | Ref expired |
| `TReferenceInvalidationReport` | Ref invalidated |
| `TStaleReferenceReport` | Stale use detected |
| `TReferenceDirectionMismatchReport` | Wrong direction |
| `TReferenceGenerationMismatchReport` | Old registry/profile generation |

---

## 13. Safe-Point Interaction

### 13.1 Before Safe-Point Operation

Before reset, scaling, profile switch, registry rebuild, or eviction, refs that may target affected structures must be:

```text
consumed
expired
invalidated
or transferred under an explicit allowed policy
```

### 13.2 After Safe-Point Operation

After the operation:

1. old refs must not be usable,
2. new refs must be generated under new state/profile,
3. waiting lists may need rebuild,
4. reference supply may need replenishment,
5. reports must record the transition.

---

## 14. Implementation Derivation Notes

### 14.1 Candidate Headers

```text
reference_precalculator/handles/
    TIngressAccessRef.hpp
    TDispatchAccessRef.hpp
    TSlotAccessRef.hpp
    TRoundScopedRef.hpp
    TNextRefToken.hpp

reference_precalculator/state/
    TReferenceValidityState.hpp
    TReferenceScope.hpp
    TReferenceGeneration.hpp

reference_precalculator/reports/
    TReferenceInvalidationReport.hpp
    TStaleReferenceReport.hpp
```

### 14.2 Deferred Decisions

1. Whether registry/profile generation is mandatory in first implementation.
2. Whether ref consumption is one-shot for both ingress and dispatch.
3. Whether `TNextRefToken` is a separate object or a view over the next prepared ref.
4. Whether stale detection is compile-time guarded, runtime checked, or both.

---

## 15. Summary

Reference validity is scope validity.  
A ref is not valid merely because it exists.  
It is valid only while its registry, container, slot, round, direction, safe-point, and profile constraints remain true.
