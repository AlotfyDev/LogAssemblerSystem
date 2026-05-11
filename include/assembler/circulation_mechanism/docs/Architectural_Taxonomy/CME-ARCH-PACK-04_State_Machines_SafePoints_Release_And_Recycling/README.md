# CME-ARCH-PACK-04 — State Machines, Safe Points, Release, And Recycling

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-04` |
| Package Name | State Machines, Safe Points, Release, And Recycling |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | State ownership, transition authority, safe-point discipline, release/recycle/reset/reentry |
| Implementation Direction | C++17, header-only-first, state-rich, transition-guarded, profile-driven |

## 2. Package Purpose

This package specifies the state-driven mechanics that make the Circulation Mechanism Engine deterministic, mechanically traceable, and safe to convert into C++ later.

The package defines:

```text
TSlotState
TContainerState
TRoundState
TModeratorState
TBundleAgentState
TReferenceSupplyState
TDispatchExposureState
Safe-point sources
Safe-point states
Safe-point required operations
Release/recycle/reset/reentry transitions
```

## 3. Documents

```text
CME-ARCH-009_State_Model_And_Transition_Ownership.md
CME-ARCH-010_Safe_Point_Model_And_Profile_Switching.md
CME-ARCH-011_Release_Recycle_Reset_And_Reentry_Model.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-009_slot_state_machine.mmd
diagrams/CME-ARCH-009_container_state_machine.mmd
diagrams/CME-ARCH-009_round_state_machine.mmd
diagrams/CME-ARCH-010_safe_point_sources.mmd
diagrams/CME-ARCH-011_release_recycle_flow.mmd
```

## 5. Package-Level Rules

### 5.1 State Ownership Rule

```text
Every state belongs to the narrowest component that owns the behavior affected by that state.
```

### 5.2 Transition Authority Rule

```text
A transition may only be executed by the component that owns or is explicitly delegated that transition.
```

### 5.3 Safe-Point Rule

```text
Reset, eviction, vertical scaling, profile switching, registry rebuild, and reference invalidation require safe points.
```

### 5.4 Non-Global Rule

```text
A safe point is not a global stop-the-world event unless a profile explicitly declares it.
```

### 5.5 Release Rule

```text
Release and recycle are state transitions, not informal callbacks or manual cleanup.
```
