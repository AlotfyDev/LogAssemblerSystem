# Protocol State Runtime Dependency Order

---

# Purpose

This document defines the canonical execution/build order for the
`protocol_state/` operational subsystem.

The ordering is dependency-first.

Meaning:

- foundational runtime primitives first
- semantic enforcement second
- evidence/readiness aggregation third
- facade projections last

This ordering prevents:

- circular runtime construction
- facade leakage
- unstable readiness composition
- premature orchestration coupling

---

# Canonical Dependency Order

## Layer 1 — Foundational State Vocabulary

These entities define the bounded descriptive substrate.

They intentionally remain lightweight.

### 1. TBridgeStage

Responsibilities:

- canonical stage vocabulary
- stage normalization
- lifecycle classification

Dependencies:

- none

Dependents:

- entire protocol_state subsystem

---

### 2. TBridgeTransition

Responsibilities:

- transition descriptor
- source/target stage relation
- transition semantic metadata

Dependencies:

- TBridgeStage

Dependents:

- transition admission
- transition evidence
- invariant enforcement

---

### 3. TBridgeTerminalState

Responsibilities:

- terminal taxonomy
- terminal classification semantics

Dependencies:

- TBridgeStage

Dependents:

- invariant enforcement
- readiness semantics
- runtime lifecycle validation

---

# Layer 2 — Transition Semantic Foundation

These entities define runtime transition legality semantics.

### 4. TBridgeStageTransitionMatrix

Responsibilities:

- canonical transition legality map
- bounded stage-transition semantics
- transition admissibility substrate

Dependencies:

- TBridgeStage
- TBridgeTransition

Dependents:

- transition admission runtime
- invariant runtime
- state runtime

---

### 5. TBridgeTransitionAdmissionEngine

Responsibilities:

- runtime transition admissibility
- operational transition enforcement
- transition rejection semantics

Dependencies:

- TBridgeStageTransitionMatrix
- TBridgeTransition

Dependents:

- protocol state runtime
- transition evidence runtime
- readiness aggregation

---

# Layer 3 — Runtime State Core

These entities define mutable operational runtime semantics.

### 6. TBridgeProtocolState

Responsibilities:

- bounded mutable protocol state
- runtime stage ownership
- state mutation orchestration

Dependencies:

- TBridgeStage
- TBridgeTransition
- TBridgeTerminalState

Dependents:

- state runtime
- snapshots
- readiness
- evidence

---

### 7. TBridgeProtocolStateRuntime

Responsibilities:

- operational runtime orchestration
- transition execution lifecycle
- runtime state continuity

Dependencies:

- TBridgeProtocolState
- TBridgeTransitionAdmissionEngine

Dependents:

- readiness aggregation
- evidence runtime
- invariant runtime

---

# Layer 4 — Continuity And Snapshot Runtime

### 8. TBridgeProtocolSnapshot

Responsibilities:

- immutable runtime snapshot
- runtime evidence projection
- continuity checkpoint substrate

Dependencies:

- TBridgeProtocolState

Dependents:

- continuity runtime
- diagnostics
- evidence runtime

---

### 9. TBridgeSnapshotContinuityRuntime

Responsibilities:

- continuity verification
- transition causality validation
- replay continuity semantics

Dependencies:

- TBridgeProtocolSnapshot
- TBridgeTransition

Dependents:

- invariant runtime
- readiness aggregation
- diagnostics

---

# Layer 5 — Runtime Evidence And Diagnostics

### 10. TBridgeTransitionReasonKind

Responsibilities:

- stable diagnostics taxonomy
- transition failure classification
- operational reasoning normalization

Dependencies:

- none

Dependents:

- transition reports
- invariant reports
- diagnostics subsystem

---

### 11. TBridgeTransitionEvidenceRuntime

Responsibilities:

- transition evidence aggregation
- runtime transition causality evidence
- evidence normalization

Dependencies:

- TBridgeTransitionAdmissionEngine
- TBridgeProtocolStateRuntime
- TBridgeTransitionReasonKind

Dependents:

- readiness aggregation
- diagnostics
- facade evidence projections

---

### 12. TBridgeProtocolStateTransitionReport

Responsibilities:

- transition execution reporting
- operational diagnostics projection

Dependencies:

- TBridgeTransitionEvidenceRuntime

Dependents:

- diagnostics
- readiness reporting
- facade projections

---

# Layer 6 — Runtime Invariant Enforcement

### 13. TBridgeStateInvariantEngine

Responsibilities:

- invariant enforcement
- terminal-state validation
- runtime lifecycle integrity enforcement

Dependencies:

- TBridgeProtocolStateRuntime
- TBridgeSnapshotContinuityRuntime
- TBridgeTerminalState

Dependents:

- readiness aggregation
- diagnostics

---

### 14. TBridgeProtocolStateInvariantReport

Responsibilities:

- invariant diagnostics reporting
- lifecycle integrity evidence projection

Dependencies:

- TBridgeStateInvariantEngine

Dependents:

- diagnostics
- readiness reporting
- facade projections

---

# Layer 7 — Runtime Readiness Aggregation

### 15. TBridgeProtocolStateReadinessReport

Responsibilities:

- readiness aggregation
- runtime readiness evidence normalization
- operational readiness synthesis

Dependencies:

- transition reports
- invariant reports
- continuity runtime

Dependents:

- runtime readiness view
- facade readiness projection

---

### 16. TBridgeProtocolStateRuntimeReadinessView

Responsibilities:

- runtime readiness projection
- bounded readiness semantics
- readiness normalization

Dependencies:

- readiness report

Dependents:

- facade readiness projection
- orchestration readiness evaluation

---

# Layer 8 — Facade And External Projection

### 17. TBridgeProtocolStateEvidenceAdapter

Responsibilities:

- bounded evidence projection
- facade-safe evidence normalization

Dependencies:

- transition evidence runtime
- readiness runtime view

Dependents:

- facade layer
- diagnostics facade projections

---

### 18. TBridgeProtocolStateFacadeProjection

Responsibilities:

- facade-safe runtime projection
- external bounded runtime visibility

Dependencies:

- runtime readiness view
- evidence adapter

Dependents:

- facade layer
- managerial orchestration

---

### 19. TBridgeProtocolStateReadinessView

Responsibilities:

- managerial readiness projection
- facade-consumable readiness semantics

Dependencies:

- runtime readiness view
- facade projection

Dependents:

- sessions/
- protocols/
- diagnostics/
- managerial facade layer

---

# Layer 9 — Stable Composition Boundary

### 20. TBridgeProtocolState.hpp

Responsibilities:

- stable operational composition boundary
- aggregate subsystem export
- dependency normalization
- prevention of topology leakage

Dependencies:

- entire operational subsystem

Dependents:

- protocols/
- sessions/
- bridge_core/
- diagnostics/
- facade layer

---

# Layer 10 — Facade Layer Updates

Final phase.

Facade updates must occur only after runtime readiness semantics stabilize.

Responsibilities:

- consume runtime readiness projections
- consume facade-safe evidence projections
- avoid internal runtime topology leakage

Consumes:

- TBridgeProtocolStateReadinessView
- TBridgeProtocolStateFacadeProjection
- TBridgeProtocolStateEvidenceAdapter

---

# Final Operational Dependency Chain

```text
state vocabulary
    ↓
transition semantics
    ↓
transition admission runtime
    ↓
mutable runtime state
    ↓
runtime orchestration
    ↓
snapshot continuity
    ↓
runtime evidence
    ↓
invariant enforcement
    ↓
readiness aggregation
    ↓
runtime readiness projection
    ↓
facade-safe projection
    ↓
stable composition boundary
    ↓
facade layer integration
```
