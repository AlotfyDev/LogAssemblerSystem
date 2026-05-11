# CME-IMPL-000 — Implementation Wave Planning Roadmap

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-IMPL-000-DOC-001 | Document Title | Implementation Wave Planning Roadmap |
| CME-IMPL-000-DOC-002 | Package | CME-IMPL-PLAN-00 |
| CME-IMPL-000-DOC-003 | Domain | `circulation_mechanism` |
| CME-IMPL-000-DOC-004 | Scope Level | Implementation wave roadmap, wave intent, dependency order, cutover from architecture to header skeletons |
| CME-IMPL-000-DOC-005 | Status | Implementation Planning Draft |
| CME-IMPL-000-DOC-006 | Implementation Direction | C++17, header-only-first, templates/traits/static polymorphism |
| CME-IMPL-000-DOC-007 | Depends On | CME-ARCH-PACK-00 through CME-ARCH-PACK-08 |
| CME-IMPL-000-DOC-008 | Primary Rule | Implementation waves must derive from architecture ownership and readiness gates |
| CME-IMPL-000-DOC-009 | Excluded | Final implementation algorithms, final include graph, build-system finalization, production runtime |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the implementation wave roadmap for the Circulation Mechanism Engine.

It answers:

```text
Given the completed architecture packs, what implementation waves should be
planned, in what order, with what candidate headers, tests, and architectural
guards?
```

### 2.2 Core Thesis

```text
Implementation must begin with the smallest stable semantic atoms:
ids, indices, states, profiles, views, reports, and handles.
```

Behavior-bearing actors come after their owned data, states, references, and profiles are represented.

### 2.3 Current Readiness Status

The architecture packs are ready for candidate header inventory derivation.

They are not a command to implement all files immediately.

---

## 3. Implementation Principles

## 3.1 Header-Only First

Initial implementation should favor `.hpp` files.

Valid first-wave content:

1. type declarations,
2. enum class candidates,
3. lightweight structs,
4. constexpr/default values where safe,
5. compile-only surfaces,
6. simple view/report carriers,
7. no heavyweight algorithms.

## 3.2 Static-First

The engine should prefer:

1. typed profiles,
2. template parameters,
3. traits,
4. policy types,
5. compile-time default paths,
6. runtime only where configuration/use case requires it.

## 3.3 Behavior Deferral

The following must be delayed until supporting types are stable:

1. full reference calculation algorithm,
2. full container reset algorithm,
3. eviction execution,
4. bridge-facing push behavior,
5. read-side failed-dispatch handling,
6. policy assignment integration.

## 3.4 Anti-Collapse

Implementation must not collapse:

```text
CME into bridge
CME into read-side receiver
waiting list into envelope store
container into broker
dispatcher into bridge protocol
reference into raw pointer
report into downstream proof
state into cosmetic status
```

---

## 4. Proposed Wave Overview

| Wave | Name | Purpose |
|---:|---|---|
| CME-W01 | Foundational Identity And State Types | IDs, indices, states, statuses, issue severities |
| CME-W02 | Views Reports And Diagnostics Primitives | Read-only views, reports, diagnostics base carriers |
| CME-W03 | Capacity Profiles And Container Shape | capacity profiles, uniform profile, default empty descriptor |
| CME-W04 | Slot And Container Skeleton | TSlot, TContainer, occupancy, time range |
| CME-W05 | Container Registry Skeleton | registry index, registry view, storage skeleton |
| CME-W06 | Bundle Agent And Moderator Skeleton | topology owner and reset/moderation surfaces |
| CME-W07 | Waiting Lists And Round Manager Skeleton | ingress/dispatch waiting lists, round state, membership |
| CME-W08 | Reference Handles And Validity Model | ingress/dispatch refs, validity state, stale diagnostics |
| CME-W09 | ReferencePrecalculator Skeleton | next-ref supply surface, input/output reports |
| CME-W10 | Ingress Placement Skeleton | placement actor, ingress reports, boundary shape |
| CME-W11 | Dispatcher And Passive Exposure Skeleton | dispatcher, exposure view, passive pull profile |
| CME-W12 | Safe Point And Release/Recycle Skeleton | safe-point carriers, reset/recycle/reentry surfaces |
| CME-W13 | Eviction And Time Range Skeleton | time range, eviction candidate, policies |
| CME-W14 | Communication Binding Integration Skeleton | ingress/dispatch binding adapters |
| CME-W15 | Integrated Smoke And Negative Compliance Suite | cross-component compile tests and anti-collapse tests |

---

## 5. Wave Dependency Order

```text
W01 foundational atoms
→ W02 observability primitives
→ W03 profiles
→ W04 slot/container
→ W05 registry
→ W06 bundle/moderator
→ W07 waiting lists/rounds
→ W08 reference handles
→ W09 reference precalculator
→ W10 ingress
→ W11 dispatcher
→ W12 safe/recycle
→ W13 eviction/time range
→ W14 bindings
→ W15 compliance/smoke
```

---

## 6. First Implementation Target

The first actual implementation package should be:

```text
CME-W01_Foundational_Identity_And_State_Types
```

It should not include behavior-heavy code.

It should include:

```text
TContainerId
TContainerRegistryIndex
TSlotIndex
TRoundId
TIngressAccessRefId / optional
TDispatchAccessRefId / optional
TSlotState
TContainerState
TRoundState
TReferenceValidityState
TSafePointState
TDispatchExposureState
TDiagnosticSeverity
```

---

## 7. Roadmap Exit Criteria

This planning package is complete when:

1. all waves have stable purpose,
2. each wave has dependencies,
3. each wave has candidate files,
4. each wave has smoke tests,
5. anti-collapse tests are identified,
6. deferred decisions are declared,
7. first implementation wave can be generated without inventing new architecture.

---

## 8. Summary

The implementation plan begins with type stability, not algorithms.

The engine’s correctness relies on state, references, registry indices, profiles, and safe reports before actors perform full behavior.
