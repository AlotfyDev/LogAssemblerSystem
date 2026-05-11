# CME-ARCH-019 — Header Derivation Candidate Map

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-ARCH-019-DOC-001 | Document Title | Header Derivation Candidate Map |
| CME-ARCH-019-DOC-002 | Package | CME-ARCH-PACK-08 |
| CME-ARCH-019-DOC-003 | Domain | `circulation_mechanism` |
| CME-ARCH-019-DOC-004 | Scope Level | Candidate header map, folder-to-file derivation, implementation preparation |
| CME-ARCH-019-DOC-005 | Status | Candidate Header Map Draft |
| CME-ARCH-019-DOC-006 | Implementation Direction | C++17, header-only-first, architecture-owned header derivation |
| CME-ARCH-019-DOC-007 | Depends On | CME-ARCH-000 through CME-ARCH-018 |
| CME-ARCH-019-DOC-008 | Primary Rule | Headers derive from folder/component ownership; headers do not reshape architecture |
| CME-ARCH-019-DOC-009 | Excluded | Final class definitions, final function signatures, final include graph, CMake targets |

---

## 2. Purpose

### 2.1 Purpose Statement

This document proposes candidate header families for the Circulation Mechanism Engine.

It answers:

```text
Given the accepted architecture and component ownership model, which header
families are plausible candidates for later implementation waves?
```

### 2.2 Non-Freeze Rule

```text
A candidate header is not a final file.
A candidate header does not freeze a final C++ type.
```

### 2.3 Derivation Chain

```text
architecture ownership
→ component spec
→ local subfolder role
→ candidate header
→ later C++ declaration
```

The reverse direction is forbidden.

---

## 3. Root Candidate Shape

Proposed root:

```text
include/assembler/circulation_mechanism/
```

Candidate internal roots:

```text
bundle_agent/
moderator/
container_registry/
container/
slot/
waiting_list/
round_manager/
reference_precalculator/
ingress/
dispatcher/
communication_bindings/
capacity/
eviction/
diagnostics/
profiles/
safe_points/
release_recycle/
tests/
docs/
```

These are candidate roots, not final frozen folders.

---

## 4. Bundle Agent Candidate Headers

```text
bundle_agent/
  TSlotsContainerBundleAgent.hpp
  TSlotsContainerBundleAgentConfig.hpp
  TBundleAgentState.hpp
  TBundleTopologyView.hpp
  TContainerFamilyView.hpp
  TBundleScalingReport.hpp
  TDefaultEmptyContainerProfileReport.hpp
```

## 5. Moderator Candidate Headers

```text
moderator/
  TSlotsContainerModerator.hpp
  TModeratorId.hpp
  TModeratorState.hpp
  TModeratorReadinessView.hpp
  TModeratedContainerView.hpp
  TContainerResetPlan.hpp
  TContainerResetReport.hpp
  TSafePointConfirmationReport.hpp
```

## 6. Container Registry Candidate Headers

```text
container_registry/
  TContainerRegistry.hpp
  TContainerRegistryId.hpp
  TContainerRegistryIndex.hpp
  TContainerRegistryState.hpp
  TContainerRegistryView.hpp
  TContainerRegistryCapacityView.hpp
  TContainerRegistryGenerationView.hpp
  TContainerRegistryInvariantReport.hpp
  TRegistryProfileSwitchReport.hpp
```

## 7. Container Candidate Headers

```text
container/
  TContainer.hpp
  TContainerId.hpp
  TContainerRef.hpp
  TContainerState.hpp
  TContainerView.hpp
  TContainerStateView.hpp
  TContainerSlotLayoutView.hpp
  TContainerTimeRange.hpp
  TContainerTimeRangeView.hpp
  TContainerStateTransitionReport.hpp
  TContainerResetReport.hpp
  TContainerReleaseReport.hpp
  TContainerRecycleReport.hpp
```

## 8. Slot Candidate Headers

```text
slot/
  TSlot.hpp
  TSlotIndex.hpp
  TSlotState.hpp
  TSlotView.hpp
  TSlotStateView.hpp
  TSlotOccupancyView.hpp
  TSlotAccessView.hpp
  TSlotTransitionReport.hpp
  TSlotOccupancyReport.hpp
  TSlotReleaseReport.hpp
```

## 9. Waiting List Candidate Headers

```text
waiting_list/
  TWaitingListState.hpp
  TWaitingListEntry.hpp
  TIngressWaitingList.hpp
  TIngressWaitingListView.hpp
  TIngressWaitingListRegistrationReport.hpp
  TDispatchWaitingList.hpp
  TDispatchWaitingListView.hpp
  TDispatchOrderingView.hpp
  TDispatchEvictionCandidateView.hpp
  TDispatchWaitingListRegistrationReport.hpp
```

## 10. Round Manager Candidate Headers

```text
round_manager/
  TRoundManager.hpp
  TRoundId.hpp
  TRoundState.hpp
  TRoundView.hpp
  TRoundStateView.hpp
  TRoundMembershipView.hpp
  TRoundEligibilityView.hpp
  TRoundAdmissionReport.hpp
  TRoundClosureReport.hpp
```

## 11. Reference Precalculator Candidate Headers

```text
reference_precalculator/
  TReferencePrecalculator.hpp
  TReferencePrecalculatorId.hpp
  TReferenceSupplyState.hpp
  TReferenceSupplyView.hpp
  TReferencePrecalculationReport.hpp
  TReferenceSupplyInterruptionReport.hpp

reference_precalculator/handles/
  TIngressAccessRef.hpp
  TDispatchAccessRef.hpp
  TSlotAccessRef.hpp
  TRoundScopedRef.hpp
  TNextRefToken.hpp

reference_precalculator/validity/
  TReferenceValidityState.hpp
  TReferenceValidityPolicy.hpp
  TReferenceInvalidationReport.hpp
  TStaleReferenceReport.hpp
```

## 12. Ingress Candidate Headers

```text
ingress/
  TIngress.hpp
  TIngressId.hpp
  TIngressState.hpp
  TIngressView.hpp
  TIngressAdmissionView.hpp
  TIngressPlacementView.hpp
  TIngressPlacementReport.hpp
  TIngressAccessReport.hpp
  TIngressAccessPolicy.hpp
```

## 13. Dispatcher Candidate Headers

```text
dispatcher/
  TDispatcher.hpp
  TDispatcherId.hpp
  TDispatchExposureState.hpp
  TDispatcherView.hpp
  TDispatchExposureView.hpp
  TDispatchReadyView.hpp
  TDispatchExposureReport.hpp
  TPassiveExposureReport.hpp
  TBoundaryAssumptionBrokenReport.hpp
  TDispatchExposurePolicy.hpp
  TPassivePullDispatchProfile.hpp
  TPushDispatchProfile.hpp
```

## 14. Communication Binding Candidate Headers

```text
communication_bindings/
  TEnvelopePlacementPort.hpp
  TIngressBindingView.hpp
  TBoundaryBindingReport.hpp

communication_bindings/circulation_output_plugin_adapter/
  TBridgeFacingDispatchAdapterDescriptor.hpp
  TDispatchOutputBindingView.hpp
  TDispatchOutputBindingMismatchReport.hpp
```

## 15. Capacity Candidate Headers

```text
capacity/
  TCirculationCapacityProfile.hpp
  TUniformContainerCapacityProfile.hpp
  TExtremeDefaultProfile.hpp
  TIngressCapacityProfile.hpp
  TDispatchCapacityProfile.hpp
  TCapacityProfileReport.hpp
  TCapacityDiagnosticReport.hpp
```

## 16. Eviction Candidate Headers

```text
eviction/
  TEvictionCandidate.hpp
  TEvictionPolicyProfile.hpp
  TOldestTimeRangeEviction.hpp
  TFifoContainerEviction.hpp
  TNoEvictionPreBridgeProfile.hpp
  TDelegateToReadSideProfile.hpp
  TEmergencyEvictionProfile.hpp
  TEvictionSelectionReport.hpp
  TEvictionAppliedReport.hpp
```

## 17. Safe Points Candidate Headers

```text
safe_points/
  TSafePointState.hpp
  TSafePointView.hpp
  TSafePointPolicy.hpp
  TSafePointViolationReport.hpp
  TScalingSafePointReport.hpp
  TResetSafePointReport.hpp
```

## 18. Release / Recycle Candidate Headers

```text
release_recycle/
  TSlotReleaseState.hpp
  TContainerReleaseState.hpp
  TRecyclePolicy.hpp
  TRecycleReport.hpp
  TReentryEligibilityView.hpp
  TReferenceReleaseReport.hpp
  TExposureReleaseReport.hpp
```

## 19. Diagnostics Candidate Headers

```text
diagnostics/
  TDiagnosticSeverity.hpp
  TDiagnosticCategory.hpp
  TInvariantViolationReport.hpp
  TOperationalReport.hpp
  TDiagnosticIssue.hpp
  TDiagnosticCollector.hpp
```

## 20. Profiles Candidate Headers

```text
profiles/
  TPreBridgeWriteSideProfile.hpp
  TReadSideCirculationProfile.hpp
  TBridgeDrainAssumptionProfile.hpp
  TProfileBoundaryReport.hpp
```

## 21. Tests Candidate Map

```text
tests/
  bundle_agent_smoke_test.cpp
  moderator_reset_test.cpp
  container_registry_index_test.cpp
  container_state_test.cpp
  slot_occupancy_test.cpp
  waiting_list_fifo_test.cpp
  round_manager_membership_test.cpp
  reference_precalculator_ref_validity_test.cpp
  ingress_access_test.cpp
  dispatcher_passive_pull_test.cpp
  safe_point_violation_test.cpp
  eviction_time_range_test.cpp
```

## 22. Public vs Local vs Private Guidance

### 22.1 Public Surface Candidates

```text
views
reports
handles
ports
profiles
public component surfaces
```

### 22.2 Local Surface Candidates

```text
state
transition helpers
local policies
local detail
```

### 22.3 Private Detail Candidates

```text
detail/
  internal algorithms
  storage helpers
  local calculations
```

## 23. State File Exposure Rule

```text
State files are local by default.
Cross-component state observation must go through views/reports.
```

## 24. Header Derivation Invariants

```text
1. A header must have a declared owner.
2. A header must have a role.
3. A header must not invent a new component.
4. A header must not expose private state cross-boundary.
5. A header must not collapse bridge/read-side concerns into CME.
6. A header must map to a documented responsibility.
```

## 25. Deferred Decisions

1. Final folder names.
2. Whether shared roots such as `safe_points/` and `capacity/` remain top-level.
3. Whether reports live locally or under diagnostics.
4. Whether refs live under `reference_precalculator/handles/` or component-local handles.
5. Whether policies/profiles are centralized or local.

---

## 26. Summary

This map proposes candidate header families.  
It is not code.  
It is not a final inventory.  
It is the bridge from architecture specs to implementation wave planning.
