# CME-IMPL-001 — Wave Sequencing And Dependency Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-IMPL-001-DOC-001 | Document Title | Wave Sequencing And Dependency Model |
| CME-IMPL-001-DOC-002 | Package | CME-IMPL-PLAN-00 |
| CME-IMPL-001-DOC-003 | Scope Level | Wave dependencies, wave gates, wave contents, wave exclusions |
| CME-IMPL-001-DOC-004 | Status | Implementation Planning Draft |
| CME-IMPL-001-DOC-005 | Primary Rule | No wave may introduce a dependency on a later wave |

---

## 2. Wave Model

Each wave must define:

1. wave id,
2. wave name,
3. dependencies,
4. candidate headers,
5. compile smoke test,
6. negative or boundary test if applicable,
7. excluded behavior,
8. readiness exit criteria.

---

## 3. Wave Details

## 3.1 CME-W01 — Foundational Identity And State Types

### 3.1.1 Purpose

Create foundational IDs, indices, state enums/descriptors, and issue/severity atoms.

### 3.1.2 Dependencies

Architecture only.

### 3.1.3 Candidate Headers

```text
ids/TContainerId.hpp
ids/TSlotIndex.hpp
ids/TRoundId.hpp
ids/TContainerRegistryIndex.hpp
state/TSlotState.hpp
state/TContainerState.hpp
state/TRoundState.hpp
state/TReferenceValidityState.hpp
state/TSafePointState.hpp
state/TDispatchExposureState.hpp
diagnostics/TDiagnosticSeverity.hpp
diagnostics/TDiagnosticCategory.hpp
```

### 3.1.4 Tests

```text
cme_w01_foundational_types_smoke_test.cpp
```

### 3.1.5 Exclusions

No container implementation.  
No registry.  
No reference calculation.

---

## 3.2 CME-W02 — Views Reports And Diagnostics Primitives

### 3.2.1 Purpose

Introduce base report/view primitives so later components can expose state safely.

### 3.2.2 Dependencies

CME-W01.

### 3.2.3 Candidate Headers

```text
views/TViewVisibility.hpp
reports/TReportId.hpp
reports/TReportStatus.hpp
diagnostics/TDiagnosticIssue.hpp
diagnostics/TInvariantViolationReport.hpp
reports/TOperationalReport.hpp
```

### 3.2.4 Tests

```text
cme_w02_views_reports_smoke_test.cpp
cme_w02_report_non_mutation_negative_test.cpp
```

### 3.2.5 Exclusions

No component-specific reports yet except base forms.

---

## 3.3 CME-W03 — Capacity Profiles And Container Shape

### 3.3.1 Purpose

Represent capacity and container uniformity before actual containers.

### 3.3.2 Dependencies

CME-W01, CME-W02.

### 3.3.3 Candidate Headers

```text
capacity/TCirculationCapacityProfile.hpp
capacity/TUniformContainerCapacityProfile.hpp
capacity/TExtremeDefaultProfile.hpp
capacity/TIngressCapacityProfile.hpp
capacity/TDispatchCapacityProfile.hpp
capacity/TCapacityProfileReport.hpp
```

### 3.3.4 Tests

```text
cme_w03_capacity_profile_smoke_test.cpp
cme_w03_uniform_capacity_invariant_test.cpp
```

### 3.3.5 Exclusions

No scaling execution.

---

## 3.4 CME-W04 — Slot And Container Skeleton

### 3.4.1 Purpose

Introduce `TSlot`, `TContainer`, occupancy, and time range skeletons.

### 3.4.2 Dependencies

CME-W01, CME-W02, CME-W03.

### 3.4.3 Candidate Headers

```text
slot/TSlot.hpp
slot/TSlotView.hpp
slot/TSlotOccupancyView.hpp
slot/TSlotTransitionReport.hpp
container/TContainer.hpp
container/TContainerView.hpp
container/TContainerStateView.hpp
container/TContainerTimeRange.hpp
container/TContainerTimeRangeView.hpp
```

### 3.4.4 Tests

```text
cme_w04_slot_container_smoke_test.cpp
cme_w04_container_state_not_slot_state_test.cpp
```

### 3.4.5 Exclusions

No registry storage.  
No placement algorithm.  
No dispatch exposure.

---

## 3.5 CME-W05 — Container Registry Skeleton

### 3.5.1 Purpose

Introduce indexed ownership of containers.

### 3.5.2 Dependencies

CME-W01 through CME-W04.

### 3.5.3 Candidate Headers

```text
container_registry/TContainerRegistry.hpp
container_registry/TContainerRegistryView.hpp
container_registry/TContainerRegistryCapacityView.hpp
container_registry/TContainerRegistryInvariantReport.hpp
```

### 3.5.4 Tests

```text
cme_w05_container_registry_smoke_test.cpp
cme_w05_registry_index_validity_test.cpp
```

### 3.5.5 Exclusions

No dynamic scaling algorithm.

---

## 3.6 CME-W06 — Bundle Agent And Moderator Skeleton

### 3.6.1 Purpose

Introduce topology/capacity owner and per-container reset/readiness actor skeletons.

### 3.6.2 Dependencies

CME-W01 through CME-W05.

### 3.6.3 Candidate Headers

```text
bundle_agent/TSlotsContainerBundleAgent.hpp
bundle_agent/TBundleTopologyView.hpp
bundle_agent/TBundleScalingReport.hpp
moderator/TSlotsContainerModerator.hpp
moderator/TModeratorReadinessView.hpp
moderator/TContainerResetReport.hpp
```

### 3.6.4 Tests

```text
cme_w06_bundle_moderator_smoke_test.cpp
cme_w06_moderator_reset_requires_safe_point_test.cpp
```

### 3.6.5 Exclusions

No real scaling execution beyond skeleton/profile checks.

---

## 3.7 CME-W07 — Waiting Lists And Round Manager Skeleton

### 3.7.1 Purpose

Introduce round and waiting-list candidate ordering.

### 3.7.2 Dependencies

CME-W01 through CME-W06.

### 3.7.3 Candidate Headers

```text
waiting_list/TIngressWaitingList.hpp
waiting_list/TDispatchWaitingList.hpp
waiting_list/TWaitingListEntry.hpp
round_manager/TRoundManager.hpp
round_manager/TRoundView.hpp
round_manager/TRoundAdmissionReport.hpp
```

### 3.7.4 Tests

```text
cme_w07_waiting_list_round_smoke_test.cpp
cme_w07_waiting_list_no_envelope_storage_test.cpp
cme_w07_round_closed_registration_negative_test.cpp
```

### 3.7.5 Exclusions

No access refs yet.

---

## 3.8 CME-W08 — Reference Handles And Validity Model

### 3.8.1 Purpose

Introduce reference kinds and validity states.

### 3.8.2 Dependencies

CME-W01 through CME-W07.

### 3.8.3 Candidate Headers

```text
reference_precalculator/handles/TIngressAccessRef.hpp
reference_precalculator/handles/TDispatchAccessRef.hpp
reference_precalculator/handles/TSlotAccessRef.hpp
reference_precalculator/handles/TRoundScopedRef.hpp
reference_precalculator/handles/TNextRefToken.hpp
reference_precalculator/validity/TReferenceValidityPolicy.hpp
reference_precalculator/validity/TStaleReferenceReport.hpp
```

### 3.8.4 Tests

```text
cme_w08_reference_handle_smoke_test.cpp
cme_w08_direction_mismatch_negative_test.cpp
```

### 3.8.5 Exclusions

No full precalculation algorithm.

---

## 3.9 CME-W09 — ReferencePrecalculator Skeleton

### 3.9.1 Purpose

Introduce the actor skeleton and reports for next-ref supply.

### 3.9.2 Dependencies

CME-W01 through CME-W08.

### 3.9.3 Candidate Headers

```text
reference_precalculator/TReferencePrecalculator.hpp
reference_precalculator/TReferenceSupplyView.hpp
reference_precalculator/TReferencePrecalculationReport.hpp
reference_precalculator/TReferenceSupplyInterruptionReport.hpp
```

### 3.9.4 Tests

```text
cme_w09_reference_precalculator_smoke_test.cpp
cme_w09_no_payload_inspection_test.cpp
```

### 3.9.5 Exclusions

No optimized selection algorithm.

---

## 3.10 CME-W10 — Ingress Placement Skeleton

### 3.10.1 Purpose

Introduce ingress actor and placement reports.

### 3.10.2 Dependencies

CME-W01 through CME-W09.

### 3.10.3 Candidate Headers

```text
ingress/TIngress.hpp
ingress/TIngressView.hpp
ingress/TIngressPlacementReport.hpp
ingress/TIngressAccessPolicy.hpp
```

### 3.10.4 Tests

```text
cme_w10_ingress_smoke_test.cpp
cme_w10_ingress_requires_valid_ref_negative_test.cpp
```

### 3.10.5 Exclusions

No Log API parsing/assembly.

---

## 3.11 CME-W11 — Dispatcher And Passive Exposure Skeleton

### 3.11.1 Purpose

Introduce dispatcher output exposure with passive pull default.

### 3.11.2 Dependencies

CME-W01 through CME-W10.

### 3.11.3 Candidate Headers

```text
dispatcher/TDispatcher.hpp
dispatcher/TDispatchExposureView.hpp
dispatcher/TDispatchExposureReport.hpp
dispatcher/TPassivePullDispatchProfile.hpp
dispatcher/TPushDispatchProfile.hpp
```

### 3.11.4 Tests

```text
cme_w11_dispatcher_smoke_test.cpp
cme_w11_passive_pull_default_test.cpp
cme_w11_no_bridge_ownership_negative_test.cpp
```

### 3.11.5 Exclusions

No bridge protocol.

---

## 3.12 CME-W12 — Safe Point And Release Recycle Skeleton

### 3.12.1 Purpose

Introduce safe-point and release/recycle carriers.

### 3.12.2 Dependencies

CME-W01 through CME-W11.

### 3.12.3 Candidate Headers

```text
safe_points/TSafePointState.hpp
safe_points/TSafePointView.hpp
safe_points/TSafePointViolationReport.hpp
release_recycle/TRecyclePolicy.hpp
release_recycle/TRecycleReport.hpp
release_recycle/TReentryEligibilityView.hpp
```

### 3.12.4 Tests

```text
cme_w12_safe_point_smoke_test.cpp
cme_w12_reset_outside_safe_point_negative_test.cpp
```

### 3.12.5 Exclusions

No full reset algorithm beyond skeleton.

---

## 3.13 CME-W13 — Eviction And Time Range Skeleton

### 3.13.1 Purpose

Introduce time range and eviction policy skeletons.

### 3.13.2 Dependencies

CME-W01 through CME-W12.

### 3.13.3 Candidate Headers

```text
eviction/TContainerTimeRange.hpp
eviction/TEvictionCandidate.hpp
eviction/TEvictionPolicyProfile.hpp
eviction/TOldestTimeRangeEviction.hpp
eviction/TNoEvictionPreBridgeProfile.hpp
eviction/TEvictionAppliedReport.hpp
```

### 3.13.4 Tests

```text
cme_w13_eviction_smoke_test.cpp
cme_w13_eviction_requires_safe_point_negative_test.cpp
```

### 3.13.5 Exclusions

No read-side retry.

---

## 3.14 CME-W14 — Communication Binding Integration Skeleton

### 3.14.1 Purpose

Introduce ingress/dispatch boundary binding skeletons.

### 3.14.2 Dependencies

CME-W01 through CME-W13.

### 3.14.3 Candidate Headers

```text
communication_bindings/TEnvelopePlacementPort.hpp
communication_bindings/TIngressBindingView.hpp
communication_bindings/TBoundaryBindingReport.hpp
communication_bindings/circulation_output_plugin_adapter/TBridgeFacingDispatchAdapterDescriptor.hpp
communication_bindings/circulation_output_plugin_adapter/TDispatchOutputBindingView.hpp
```

### 3.14.4 Tests

```text
cme_w14_binding_smoke_test.cpp
cme_w14_no_mutable_internal_exposure_negative_test.cpp
```

### 3.14.5 Exclusions

No bridge runtime.

---

## 3.15 CME-W15 — Integrated Smoke And Negative Compliance Suite

### 3.15.1 Purpose

Verify architecture boundaries across the implementation skeleton.

### 3.15.2 Dependencies

All prior waves.

### 3.15.3 Candidate Tests

```text
cme_integration_compile_smoke_test.cpp
cme_anti_broker_negative_test.cpp
cme_no_bridge_ownership_negative_test.cpp
cme_waiting_list_no_envelope_storage_negative_test.cpp
cme_reference_direction_negative_test.cpp
cme_safe_point_negative_test.cpp
```

### 3.15.4 Exclusions

No production hardening.

---

## 4. Summary

Wave sequencing ensures architecture becomes code in dependency order.

The implementation begins with state, identity, views, reports, and profiles, then moves toward behavior-bearing actors.
