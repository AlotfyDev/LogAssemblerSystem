# CME-ARCH-009 — State Model And Transition Ownership

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-009-DOC-001 | Document Title | State Model And Transition Ownership |
| CME-ARCH-009-DOC-002 | Package | CME-ARCH-PACK-04 |
| CME-ARCH-009-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-009-DOC-004 | Scope Level | State taxonomy, state ownership, transition authority, local state machines |
| CME-ARCH-009-DOC-005 | Status | Architecture Specification Draft |
| CME-ARCH-009-DOC-006 | Implementation Direction | C++17, header-only-first, state-rich, transition-guarded |
| CME-ARCH-009-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-008 |
| CME-ARCH-009-DOC-008 | Related Models | Slot, Container, Round, Moderator, BundleAgent, ReferencePrecalculator, Dispatcher |
| CME-ARCH-009-DOC-009 | Primary Rule | State belongs to the narrowest owner whose behavior is constrained by that state |
| CME-ARCH-009-DOC-010 | Excluded | Global lifecycle state, bridge lifecycle, receiver lifecycle, downstream persistence state |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the state model of the Circulation Mechanism Engine.

It answers:

```text
Which engine aspects have state, who owns each state, who may transition it,
and how do local state machines prevent manual or random intervention?
```

### 2.2 Core Thesis

```text
State is not a cosmetic status field.
State is a behavioral constraint that controls what may happen next.
```

### 2.3 State-Rich Engine Principle

The engine is intentionally state-rich because its correctness depends on mechanical transitions across:

1. slots,
2. containers,
3. rounds,
4. moderators,
5. bundle/topology agents,
6. reference supply,
7. dispatch exposure.

---

## 3. State Taxonomy

## 3.1 State Families

| State Family | Owner | Scope |
|---|---|---|
| `TSlotState` | `TSlot` / slot access policy | local placement/access |
| `TContainerState` | `TContainer` / Moderator for transitions | container-level cycle eligibility |
| `TRoundState` | `RoundManager` / `TRound` | round lifecycle and membership |
| `TModeratorState` | `SlotsContainerModerator` | per-container moderation |
| `TBundleAgentState` | `SlotsContainerBundleAgent` | topology/scaling/profile state |
| `TReferenceSupplyState` | `ReferencePrecalculator` | reference supply lifecycle |
| `TDispatchExposureState` | `Dispatcher` | output exposure lifecycle |

### 3.2 State Non-Collapse Rule

```text
TSlotState ≠ TContainerState ≠ TRoundState.
```

Container state may observe slot states, but it is not mechanically identical to their aggregate.

---

## 4. `TSlotState`

### 4.1 Definition

`TSlotState` is the local state of a placement/access position inside a `TContainer`.

### 4.2 Candidate States

```text
empty
reserved_for_ingress
occupied
sealed
dispatch_ready
dispatch_exposed
released
recyclable
faulted
```

### 4.3 State Meanings

| State | Meaning |
|---|---|
| `empty` | Slot has no resident envelope |
| `reserved_for_ingress` | Slot is reserved for an incoming ingress access reference |
| `occupied` | Envelope is resident |
| `sealed` | Slot is no longer accepting modifications for current payload |
| `dispatch_ready` | Slot can be referenced for dispatch |
| `dispatch_exposed` | Slot material is exposed through dispatch boundary |
| `released` | Slot no longer holds active residency |
| `recyclable` | Slot can be returned to empty/reset path |
| `faulted` | Slot invariant broken |

### 4.4 Transition Authority

| Transition | Authority |
|---|---|
| `empty → reserved_for_ingress` | ReferencePrecalculator / ingress access policy |
| `reserved_for_ingress → occupied` | Ingress |
| `occupied → sealed` | Container/round policy |
| `sealed → dispatch_ready` | Container/dispatch readiness policy |
| `dispatch_ready → dispatch_exposed` | Dispatcher |
| `dispatch_exposed → released` | Dispatcher/release policy |
| `released → recyclable` | Container reset/recycle policy |
| `recyclable → empty` | Moderator/container reset |

### 4.5 Slot State Invariants

```text
1. A slot cannot be written unless empty or reserved_for_ingress.
2. A slot cannot be dispatched unless sealed or dispatch_ready.
3. A slot cannot be reset while an active reference targets it.
4. Slot state does not own envelope lifecycle after dispatch exposure.
5. Slot state is local to the owning container.
```

---

## 5. `TContainerState`

### 5.1 Definition

`TContainerState` is the operational and cycle-participation state of a complete `TContainer`.

### 5.2 Candidate States

```text
default_empty
ingress_ready
ingress_round_member
receiving
filled_or_closed
dispatch_candidate
dispatch_round_member
dispatch_exposed
dispatch_completed
reset_pending
under_moderation
inactive
evicted
faulted
```

### 5.3 State Meanings

| State | Meaning |
|---|---|
| `default_empty` | Container matches default empty profile |
| `ingress_ready` | Container can enter ingress/container-providing cycle |
| `ingress_round_member` | Container belongs to an ingress round |
| `receiving` | Container is currently receiving envelopes |
| `filled_or_closed` | Container no longer accepts ingress for current cycle |
| `dispatch_candidate` | Container may enter dispatch waiting list |
| `dispatch_round_member` | Container belongs to dispatch round |
| `dispatch_exposed` | Container material exposed to output boundary |
| `dispatch_completed` | Dispatch exposure lifecycle complete for current cycle |
| `reset_pending` | Container awaits reset |
| `under_moderation` | Moderator is applying reset/reinitialization |
| `inactive` | Not active in current bundle |
| `evicted` | Selected/removed by eviction policy |
| `faulted` | Container invariant broken |

### 5.4 Transition Authority

| Transition | Authority |
|---|---|
| `default_empty → ingress_ready` | Moderator |
| `ingress_ready → ingress_round_member` | RoundManager |
| `ingress_round_member → receiving` | Ingress / round policy |
| `receiving → filled_or_closed` | Container policy |
| `filled_or_closed → dispatch_candidate` | Container/round readiness policy |
| `dispatch_candidate → dispatch_round_member` | RoundManager |
| `dispatch_round_member → dispatch_exposed` | Dispatcher |
| `dispatch_exposed → dispatch_completed` | Dispatcher/release policy |
| `dispatch_completed → reset_pending` | Release/recycle model |
| `reset_pending → under_moderation` | Moderator |
| `under_moderation → default_empty` | Moderator |
| `any eligible → evicted` | Eviction policy at safe point |

### 5.5 Container State Invariants

```text
1. Container state is not derived mechanically from slot states.
2. Container cannot enter ingress and dispatch rounds simultaneously.
3. Container reset requires safe point.
4. Container vertical scaling requires safe point.
5. Container eviction requires safe point.
6. Container state governs waiting-list eligibility.
7. Container state does not imply bridge success.
```

---

## 6. `TRoundState`

### 6.1 Definition

`TRoundState` governs the lifecycle of a movement round.

### 6.2 Candidate States

```text
idle
collecting_candidates
open
locked
draining
closing
closed
completed
aborted
invariant_violation
```

### 6.3 State Meanings

| State | Meaning |
|---|---|
| `idle` | No active round |
| `collecting_candidates` | Candidates being evaluated |
| `open` | Candidate registration allowed |
| `locked` | Membership fixed |
| `draining` | Waiting list consumed by ReferencePrecalculator |
| `closing` | Closure in progress |
| `closed` | No more candidates accepted |
| `completed` | Round completed |
| `aborted` | Round stopped due to fault |
| `invariant_violation` | Illegal transition/membership |

### 6.4 Transition Authority

RoundManager owns round transitions.

### 6.5 Round State Invariants

```text
1. No candidate may enter a closed round.
2. A locked round cannot change membership unless policy explicitly allows.
3. Round completion may create safe points.
4. Round state does not reset containers by itself.
5. Round state does not execute dispatch exposure.
```

---

## 7. `TModeratorState`

### 7.1 Definition

`TModeratorState` is the state of a per-container moderator.

### 7.2 Candidate States

```text
idle
observing
preparing
resetting
ready_exposed
safe_point_confirmed
moderation_blocked
invariant_violation
```

### 7.3 Transition Authority

The moderator owns its local state. It may require safe-point evidence from container/round/reference models.

### 7.4 Invariants

```text
1. Moderator applies reset; BundleAgent owns default empty profile.
2. Moderator exposes readiness; RoundManager decides list admission.
3. Moderator must not profile-switch without BundleAgent authority.
4. Moderator must not reset active containers.
```

---

## 8. `TBundleAgentState`

### 8.1 Definition

`TBundleAgentState` governs topology/scaling/profile state.

### 8.2 Candidate States

```text
stable
horizontal_scaling_pending
vertical_scaling_pending
waiting_for_safe_point
profile_switch_ready
profile_switch_applied
invariant_violation
```

### 8.3 Invariants

```text
1. BundleAgent owns uniform capacity profile.
2. BundleAgent owns default empty container profile.
3. Vertical scaling must be family-wide.
4. Scaling must not occur outside safe point.
```

---

## 9. `TReferenceSupplyState`

### 9.1 Definition

`TReferenceSupplyState` governs continuous next-ref supply.

### 9.2 Candidate States

```text
ready
replenishing
ingress_refs_ready
dispatch_refs_ready
waiting_for_candidates
invalidating_refs
supply_interrupted
invariant_violation
```

### 9.3 Invariants

```text
1. Reference supply state is not access state.
2. Reference supply interruption under continuous profile is diagnostic-visible.
3. Invalidation must precede reset/profile switch when refs are affected.
```

---

## 10. `TDispatchExposureState`

### 10.1 Definition

`TDispatchExposureState` governs the output exposure lifecycle.

### 10.2 Candidate States

```text
ready
awaiting_dispatch_ref
exposing
passive_exposed
bridge_consumed
release_pending
closed
boundary_assumption_broken
```

### 10.3 Invariants

```text
1. Passive exposure does not prove bridge success.
2. Dispatch exposure does not prove receiver delivery.
3. Release after exposure is profile-defined.
4. Push dispatch is optional profile, not core state assumption.
```

---

## 11. Transition Ownership Matrix

| Transition Area | Authority |
|---|---|
| slot write | Ingress |
| slot dispatch exposure | Dispatcher |
| slot release | Dispatcher/release policy |
| container ingress admission | RoundManager |
| container reset | Moderator |
| container profile switch | BundleAgent + safe point |
| waiting-list admission | RoundManager |
| reference invalidation | ReferencePrecalculator / validity policy |
| round lifecycle | RoundManager |
| dispatch exposure lifecycle | Dispatcher |

---

## 12. State Views

| View | Owner |
|---|---|
| `TSlotStateView` | Slot |
| `TContainerStateView` | Container/Moderator |
| `TRoundStateView` | RoundManager |
| `TModeratorStateView` | Moderator |
| `TBundleAgentStateView` | BundleAgent |
| `TReferenceSupplyStateView` | ReferencePrecalculator |
| `TDispatchExposureStateView` | Dispatcher |

---

## 13. Reports

| Report | Trigger |
|---|---|
| `TSlotTransitionReport` | Slot transition |
| `TContainerStateTransitionReport` | Container transition |
| `TRoundProgressionReport` | Round transition |
| `TModerationReport` | Moderator transition |
| `TBundleScalingReport` | BundleAgent transition |
| `TReferenceSupplyReport` | Reference supply transition |
| `TDispatchExposureReport` | Dispatch exposure transition |

---

## 14. Implementation Derivation Notes

### 14.1 Candidate State Headers

```text
slot/state/TSlotState.hpp
slots_container/state/TContainerState.hpp
round_manager/state/TRoundState.hpp
slots_container_moderator/state/TModeratorState.hpp
slots_container_bundle_agent/state/TBundleAgentState.hpp
reference_precalculator/state/TReferenceSupplyState.hpp
dispatcher/state/TDispatchExposureState.hpp
```

### 14.2 Deferred Decisions

1. Exact enum naming.
2. Whether states are enum class only or richer state descriptors.
3. Whether transition guards are separate headers or policy traits.
4. Whether state reports live under component-local `reports/` or `carriers/`.

---

## 15. Summary

The engine is state-driven.  
Slot, container, round, moderator, bundle agent, reference supply, and dispatch exposure each own distinct state.  
No state family replaces another.  
Transitions must have declared authority.
