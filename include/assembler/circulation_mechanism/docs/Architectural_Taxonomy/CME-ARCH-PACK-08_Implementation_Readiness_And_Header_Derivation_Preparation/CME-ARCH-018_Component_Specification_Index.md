# CME-ARCH-018 — Component Specification Index

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-018-DOC-001 | Document Title | Component Specification Index |
| CME-ARCH-018-DOC-002 | Package | CME-ARCH-PACK-08 |
| CME-ARCH-018-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-018-DOC-004 | Scope Level | Component specification inventory, public surfaces, local state, views, reports, handles, policies, tests |
| CME-ARCH-018-DOC-005 | Status | Architecture-to-Implementation Readiness Draft |
| CME-ARCH-018-DOC-006 | Implementation Direction | C++17, header-only-first, static/profile-driven |
| CME-ARCH-018-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-017 |
| CME-ARCH-018-DOC-008 | Primary Rule | Each component must have a declared specification boundary before headers are derived |
| CME-ARCH-018-DOC-009 | Excluded | Final header implementation, final class bodies, final function signatures, final include graph |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the component specification index for the Circulation Mechanism Engine.

It answers:

```text
For each core component, what public surface, state model, views, reports,
handles, policies, tests, and non-ownership boundaries must be specified before
implementation starts?
```

### 2.2 Core Thesis

```text
Component specifications are the bridge between architecture and headers.
They are not code.
```

### 2.3 Spec Grain

Each component specification must capture:

1. identity,
2. role,
3. responsibilities,
4. non-responsibilities,
5. public surface,
6. state files,
7. views,
8. reports,
9. handles / refs,
10. policies / profiles,
11. tests,
12. diagnostics,
13. safe points,
14. dependencies,
15. deferred implementation decisions.

---

## 3. Global Component Inventory

| ID | Component | Category | Readiness |
|---:|---|---|---|
| CME-SPEC-001 | `SlotsContainerBundleAgent` | Actor / topology authority | ready for spec |
| CME-SPEC-002 | `SlotsContainerModerator` | Actor / per-container coordinator | ready for spec |
| CME-SPEC-003 | `TContainerRegistry` | Registry / indexed storage owner | ready for spec |
| CME-SPEC-004 | `TContainer` | Data-structure container | ready for spec |
| CME-SPEC-005 | `TSlot` | Placement/access structure | ready for spec |
| CME-SPEC-006 | `TIngressWaitingList` | Active eligibility list | ready for spec |
| CME-SPEC-007 | `TDispatchWaitingList` | Active eligibility list | ready for spec |
| CME-SPEC-008 | `RoundManager` | Actor / round coordinator | ready for spec |
| CME-SPEC-009 | `ReferencePrecalculator` | Actor / reference calculation coordinator | ready for spec |
| CME-SPEC-010 | `Ingress` | Actor / intake access executor | ready for spec |
| CME-SPEC-011 | `Dispatcher` | Actor / output exposure authority | ready for spec |
| CME-SPEC-012 | `BoundaryBindings` | Boundary / communication adapters | ready for spec |
| CME-SPEC-013 | `CapacityProfiles` | Profiles / configuration | ready for spec |
| CME-SPEC-014 | `EvictionModel` | Policy / diagnostic model | ready for spec |
| CME-SPEC-015 | `DiagnosticsReportsViews` | Observability model | ready for spec |

---

## 4. `SlotsContainerBundleAgent` Specification Index

### 4.1 Public Surface

Candidate public surface:

```text
TSlotsContainerBundleAgent
TSlotsContainerBundleAgentConfig
TSlotsContainerBundleAgentView
```

### 4.2 State Files

```text
TBundleAgentState
```

### 4.3 Views

```text
TBundleTopologyView
TUniformCapacityProfileView
TContainerFamilyView
TBundleAgentStateView
```

### 4.4 Reports

```text
TBundleScalingReport
TDefaultEmptyContainerProfileReport
TCapacityProfileSwitchReport
TBundleInvariantReport
```

### 4.5 Handles

Usually none directly exposed. Bundle profile ids may exist.

```text
TBundleAgentId
TContainerFamilyId
```

### 4.6 Policies / Profiles

```text
TCirculationCapacityProfile
TUniformContainerCapacityProfile
THorizontalScalingProfile
TVerticalScalingProfile
TExtremeDefaultProfile
```

### 4.7 Tests

```text
bundle_agent_uniform_capacity_test
bundle_agent_default_empty_profile_test
bundle_agent_scaling_safe_point_test
```

### 4.8 Non-Ownership

1. Does not reset concrete containers.
2. Does not compute slot refs.
3. Does not determine round membership.
4. Does not inspect envelope content.

---

## 5. `SlotsContainerModerator` Specification Index

### 5.1 Public Surface

```text
TSlotsContainerModerator
TSlotsContainerModeratorView
TContainerResetSurface
```

### 5.2 State Files

```text
TModeratorState
```

### 5.3 Views

```text
TModeratorReadinessView
TModeratedContainerView
TContainerStateView
TContainerSafePointView
```

### 5.4 Reports

```text
TContainerResetReport
TModerationReport
TContainerReadinessReport
TSafePointConfirmationReport
```

### 5.5 Handles

```text
TModeratorId
TContainerRegistryIndex
```

### 5.6 Policies

```text
TModerationPolicy
TResetPolicy
TSafePointPolicy
```

### 5.7 Tests

```text
moderator_reset_safe_point_test
moderator_default_empty_application_test
moderator_readiness_view_test
```

### 5.8 Non-Ownership

1. Does not own capacity profile.
2. Does not add containers to waiting lists.
3. Does not compute access refs.
4. Does not perform dispatch exposure.

---

## 6. `TContainerRegistry` Specification Index

### 6.1 Public Surface

```text
TContainerRegistry
TContainerRegistryView
```

### 6.2 State Files

```text
TContainerRegistryState
```

### 6.3 Views

```text
TContainerRegistryView
TContainerRegistryCapacityView
TContainerRegistrySlotLayoutView
TContainerRegistryGenerationView
```

### 6.4 Reports

```text
TContainerRegistryInitializationReport
TContainerRegistryInvariantReport
TRegistryProfileSwitchReport
TRegistryIndexInvalidationReport
TDanglingWaitingListIndexReport
```

### 6.5 Handles

```text
TContainerRegistryIndex
TContainerId
TContainerRef  // optional
```

### 6.6 Policies

```text
TContainerRegistryCapacityProfile
TContainerRegistryIndexPolicy
TContainerStoragePolicy
TRegistryResizePolicy
```

### 6.7 Tests

```text
container_registry_index_validity_test
container_registry_uniform_layout_test
container_registry_generation_test
```

### 6.8 Non-Ownership

1. Does not own eligibility decision.
2. Does not calculate refs.
3. Does not interpret envelopes.
4. Does not become downstream registry.

---

## 7. `TContainer` Specification Index

### 7.1 Public Surface

```text
TContainer
TContainerView
```

### 7.2 State Files

```text
TContainerState
```

### 7.3 Views

```text
TContainerView
TContainerStateView
TContainerSlotLayoutView
TContainerTimeRangeView
TContainerDispatchReadinessView
```

### 7.4 Reports

```text
TContainerStateTransitionReport
TContainerResetReport
TContainerReleaseReport
TContainerRecycleReport
TContainerEvictionReport
TContainerTimeRangeReport
```

### 7.5 Handles

```text
TContainerId
TContainerRegistryIndex
TContainerRef  // optional
```

### 7.6 Policies

```text
TContainerCapacityProfile
TContainerLayoutProfile
TContainerStatePolicy
TContainerTimeRangePolicy
TContainerEvictionPolicy
```

### 7.7 Tests

```text
container_state_transition_test
container_uniform_capacity_test
container_time_range_test
container_reset_to_default_empty_test
```

### 7.8 Non-Ownership

1. Does not become a message broker.
2. Does not own downstream lifecycle.
3. Does not expose mutable internals to bridge.
4. Does not interpret envelope content.

---

## 8. `TSlot` Specification Index

### 8.1 Public Surface

```text
TSlot
TSlotView
```

### 8.2 State Files

```text
TSlotState
```

### 8.3 Views

```text
TSlotView
TSlotStateView
TSlotOccupancyView
TSlotAccessView
TSlotReleaseView
```

### 8.4 Reports

```text
TSlotTransitionReport
TSlotOccupancyReport
TSlotReleaseReport
TSlotAccessViolationReport
TSlotStateMismatchReport
```

### 8.5 Handles

```text
TSlotIndex
TSlotAccessRef
```

### 8.6 Policies

```text
TSlotStatePolicy
TSlotAccessPolicy
TSlotOccupancyPolicy
TSlotResetPolicy
```

### 8.7 Tests

```text
slot_occupancy_test
slot_state_machine_test
slot_access_ref_guard_test
```

### 8.8 Non-Ownership

1. Does not own envelope lifecycle globally.
2. Does not dispatch itself.
3. Does not know bridge.
4. Does not decide round eligibility.

---

## 9. Waiting Lists Specification Index

### 9.1 Public Surfaces

```text
TIngressWaitingList
TDispatchWaitingList
TWaitingListView
```

### 9.2 State Files

```text
TWaitingListState
TIngressWaitingListState
TDispatchWaitingListState
```

### 9.3 Views

```text
TIngressWaitingListView
TIngressEligibilityView
TDispatchWaitingListView
TDispatchOrderingView
TDispatchEvictionCandidateView
```

### 9.4 Reports

```text
TIngressWaitingListRegistrationReport
TIngressWaitingListDrainReport
TIngressWaitingListInvariantReport
TDispatchWaitingListRegistrationReport
TDispatchWaitingListDrainReport
TDispatchEvictionSelectionReport
TDispatchWaitingListInvariantReport
```

### 9.5 Handles

```text
TContainerRegistryIndex
TWaitingListEntry
```

### 9.6 Policies

```text
TIngressWaitingListProfile
TDispatchWaitingListProfile
TIngressOrderingPolicy
TDispatchOrderingPolicy
TDispatchTimeRangeOrderingPolicy
```

### 9.7 Tests

```text
waiting_list_no_envelope_storage_test
waiting_list_fifo_order_test
dispatch_waiting_list_time_range_ordering_test
```

### 9.8 Non-Ownership

1. Does not store envelopes.
2. Does not own containers.
3. Does not choose slots.
4. Does not execute access.

---

## 10. `RoundManager` Specification Index

### 10.1 Public Surface

```text
TRoundManager
TRoundView
```

### 10.2 State Files

```text
TRoundState
```

### 10.3 Views

```text
TRoundView
TRoundStateView
TRoundMembershipView
TRoundEligibilityView
TRoundSafePointView
```

### 10.4 Reports

```text
TRoundAdmissionReport
TRoundProgressionReport
TRoundClosureReport
TRoundInvariantReport
TRoundMembershipReport
```

### 10.5 Handles

```text
TRoundId
TRoundScopedRef
```

### 10.6 Policies

```text
TIngressRoundProfile
TDispatchRoundProfile
TRoundMembershipPolicy
TRoundClosurePolicy
TRoundStatePolicy
```

### 10.7 Tests

```text
round_closed_registration_test
round_membership_test
round_waiting_list_registration_test
```

### 10.8 Non-Ownership

1. Does not create containers.
2. Does not reset containers.
3. Does not calculate refs.
4. Does not execute dispatch exposure.
5. Does not execute bridge handoff.

---

## 11. `ReferencePrecalculator` Specification Index

### 11.1 Public Surface

```text
TReferencePrecalculator
TReferencePrecalculatorView
```

### 11.2 State Files

```text
TReferenceSupplyState
TReferenceValidityState
```

### 11.3 Views

```text
TReferenceSupplyView
TIngressReferenceSupplyView
TDispatchReferenceSupplyView
TReferenceValidityView
TReferenceScopeView
TReferenceInvalidationView
```

### 11.4 Reports

```text
TReferencePrecalculationReport
TReferenceSupplyInterruptionReport
TReferenceInvalidationReport
TStaleReferenceReport
TReferenceDirectionMismatchReport
TReferenceGenerationMismatchReport
```

### 11.5 Handles

```text
TIngressAccessRef
TDispatchAccessRef
TSlotAccessRef
TRoundScopedRef
TNextRefToken
```

### 11.6 Policies

```text
TReferenceSupplyPolicy
TIngressReferencePolicy
TDispatchReferencePolicy
TReferenceValidityPolicy
TReferenceInvalidationPolicy
```

### 11.7 Tests

```text
reference_direction_mismatch_test
reference_stale_detection_test
reference_supply_continuity_test
```

### 11.8 Non-Ownership

1. Does not access payload.
2. Does not interpret envelope content.
3. Does not execute ingress/dispatch access.
4. Does not own bridge semantics.

---

## 12. `Ingress` Specification Index

### 12.1 Public Surface

```text
TIngress
TIngressView
TIngressAdmissionSurface
```

### 12.2 State Files

```text
TIngressState
```

### 12.3 Views

```text
TIngressView
TIngressAdmissionView
TIngressPlacementView
TIngressReferenceConsumptionView
```

### 12.4 Reports

```text
TIngressPlacementReport
TIngressAccessReport
TIngressInvariantReport
TIngressBoundaryReport
```

### 12.5 Handles

```text
TIngressAccessRef
```

### 12.6 Policies

```text
TIngressCycleProfile
TIngressAccessPolicy
TIngressAdmissionPolicy
TIngressBoundaryProfile
```

### 12.7 Tests

```text
ingress_requires_valid_ref_test
ingress_no_locating_test
ingress_boundary_contract_test
```

### 12.8 Non-Ownership

1. Does not assemble envelope.
2. Does not parse payload.
3. Does not calculate location.
4. Does not dispatch outward.

---

## 13. `Dispatcher` Specification Index

### 13.1 Public Surface

```text
TDispatcher
TDispatcherView
TDispatchExposureSurface
```

### 13.2 State Files

```text
TDispatchExposureState
```

### 13.3 Views

```text
TDispatchExposureView
TDispatchReadyView
TDispatcherView
TDispatchBoundaryView
```

### 13.4 Reports

```text
TDispatchExposureReport
TPassiveExposureReport
TBridgePullObservationReport
TPushDispatchAttemptReport
TDispatchBoundaryReport
TBoundaryAssumptionBrokenReport
```

### 13.5 Handles

```text
TDispatchAccessRef
```

### 13.6 Policies

```text
TDispatchCycleProfile
TDispatchExposurePolicy
TPassivePullDispatchProfile
TPushDispatchProfile
TBridgeDrainAssumptionProfile
TDispatchReleasePolicy
```

### 13.7 Tests

```text
dispatcher_passive_pull_default_test
dispatcher_no_bridge_ownership_test
dispatcher_dispatch_ref_required_test
```

### 13.8 Non-Ownership

1. Does not own bridge protocol.
2. Does not own final receiver.
3. Does not own persistence.
4. Does not decide bridge copy/move semantics.

---

## 14. `BoundaryBindings` Specification Index

### 14.1 Public Surface

```text
TEnvelopePlacementPort
TBridgeFacingDispatchAdapterDescriptor
TDispatchOutputBindingView
TCirculationBindingReport
```

### 14.2 State Files

```text
TBindingState
```

### 14.3 Views

```text
TBoundaryBindingView
TDispatchOutputBindingView
TIngressBindingView
```

### 14.4 Reports

```text
TBoundaryBindingReport
TOutputBoundaryBindingMismatchReport
TMutableInternalExposureViolationReport
```

### 14.5 Policies

```text
TIngressBoundaryProfile
TDispatchBoundaryProfile
TCommunicationBindingCompatibilityPolicy
```

### 14.6 Tests

```text
boundary_no_internal_mutation_exposure_test
binding_compatibility_test
bridge_facing_adapter_no_cme_ownership_test
```

---

## 15. Test Derivation Summary

| Component | Test Focus |
|---|---|
| BundleAgent | capacity uniformity, scaling safe point |
| Moderator | reset, safe point, readiness |
| Registry | index validity, generation, uniform layout |
| Container | state, time range, reset |
| Slot | occupancy, release, state |
| WaitingLists | FIFO, no envelope storage |
| RoundManager | round closure, eligibility |
| ReferencePrecalculator | next-ref supply, stale refs |
| Ingress | valid ref required, no locating |
| Dispatcher | passive pull, no bridge ownership |
| BoundaryBindings | no mutable internals exposed |

---

## 16. Summary

This component specification index is now sufficient to derive a candidate header map.  
It does not implement any file.  
It defines what each component must eventually own.
