# CME-IMPL-002 — First Waves Header Skeleton Plan

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-IMPL-002-DOC-001 | Document Title | First Waves Header Skeleton Plan |
| CME-IMPL-002-DOC-002 | Package | CME-IMPL-PLAN-00 |
| CME-IMPL-002-DOC-003 | Scope Level | First wave header skeletons, foundational types, compile-only implementation posture |
| CME-IMPL-002-DOC-004 | Status | Implementation Planning Draft |
| CME-IMPL-002-DOC-005 | Primary Rule | The first waves create semantic skeletons, not full algorithms |

---

## 2. Purpose

This document gives a more focused skeleton plan for the first four implementation waves.

The first implementation phase should produce:

```text
small headers
strong names
no heavy behavior
compile-only tests
anti-collapse tests
```

---

## 3. CME-W01 — Foundational Identity And State Types

### 3.1 Goal

Create stable atoms that later components depend on.

### 3.2 Candidate Folders

```text
include/assembler/circulation_mechanism/ids/
include/assembler/circulation_mechanism/state/
include/assembler/circulation_mechanism/diagnostics/
```

### 3.3 Candidate Headers

```text
ids/TContainerId.hpp
ids/TContainerRegistryIndex.hpp
ids/TSlotIndex.hpp
ids/TRoundId.hpp
ids/TReferenceId.hpp
ids/TBoundaryId.hpp

state/TSlotState.hpp
state/TContainerState.hpp
state/TRoundState.hpp
state/TModeratorState.hpp
state/TBundleAgentState.hpp
state/TReferenceValidityState.hpp
state/TReferenceSupplyState.hpp
state/TSafePointState.hpp
state/TDispatchExposureState.hpp

diagnostics/TDiagnosticSeverity.hpp
diagnostics/TDiagnosticCategory.hpp
```

### 3.4 Allowed Content

1. `enum class`.
2. lightweight id structs.
3. constexpr invalid/default values if safe.
4. no container storage.
5. no algorithms.

### 3.5 Smoke Test

```text
cme_w01_foundational_types_smoke_test.cpp
```

---

## 4. CME-W02 — Views Reports And Diagnostics Primitives

### 4.1 Goal

Create base evidence/read-only surfaces.

### 4.2 Candidate Folders

```text
views/
reports/
diagnostics/
```

### 4.3 Candidate Headers

```text
views/TViewScope.hpp
views/TViewStability.hpp
reports/TReportId.hpp
reports/TReportStatus.hpp
reports/TOperationalReport.hpp
diagnostics/TDiagnosticIssue.hpp
diagnostics/TInvariantViolationReport.hpp
```

### 4.4 Allowed Content

1. base report carriers,
2. base view categories,
3. no component-specific mutation,
4. no central collector yet.

---

## 5. CME-W03 — Capacity Profiles And Container Shape

### 5.1 Goal

Represent capacity before containers.

### 5.2 Candidate Headers

```text
capacity/TCirculationCapacityProfile.hpp
capacity/TUniformContainerCapacityProfile.hpp
capacity/TExtremeDefaultProfile.hpp
capacity/TIngressCapacityProfile.hpp
capacity/TDispatchCapacityProfile.hpp
capacity/TCapacityProfileReport.hpp
```

### 5.3 Allowed Content

1. profile descriptors,
2. simple validation helpers if constexpr/static,
3. no dynamic scaling algorithm.

---

## 6. CME-W04 — Slot And Container Skeleton

### 6.1 Goal

Create `TSlot` and `TContainer` skeletons after states and capacity exist.

### 6.2 Candidate Headers

```text
slot/TSlot.hpp
slot/TSlotView.hpp
slot/TSlotOccupancyView.hpp
container/TContainer.hpp
container/TContainerView.hpp
container/TContainerStateView.hpp
container/TContainerTimeRange.hpp
```

### 6.3 Allowed Content

1. storage shape placeholders,
2. state fields,
3. accessors/views,
4. no registry yet,
5. no full placement algorithm.

---

## 7. First-Wave Anti-Collapse Checks

```text
Container is not broker.
Slot is not envelope.
View is not mutable handle.
Report is not downstream proof.
State is not cosmetic status.
```

---

## 8. Summary

W01–W04 establish the atoms and structures from which the rest of the engine can be safely built.
