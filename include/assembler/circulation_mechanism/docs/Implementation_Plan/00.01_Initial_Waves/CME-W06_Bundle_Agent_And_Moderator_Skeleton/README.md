# CME-W06 — Bundle Agent And Moderator Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W06` |
| Wave Name | Bundle Agent And Moderator Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce topology owner and per-container reset/readiness surfaces after capacity, container, and registry skeletons |

## 2. What This Wave Implements

```text
bundle_agent/
  TBundleAgentId
  TContainerFamilyId
  TSlotsContainerBundleAgentConfig
  TSlotsContainerBundleAgent
  TBundleTopologyView
  TBundleScalingReport
  TDefaultEmptyContainerProfileReport

moderator/
  TModeratorId
  TSlotsContainerModeratorConfig
  TSlotsContainerModerator
  TModeratorReadinessView
  TModeratedContainerView
  TContainerResetReport
```

## 3. What This Wave Does Not Implement

```text
actual horizontal scaling
actual vertical scaling
registry rebuild
container reset algorithm
waiting-list admission
round management
reference calculation
ingress placement
dispatch exposure
bridge bindings
```

## 4. Architectural Rules Preserved

1. BundleAgent owns topology/capacity profile surface.
2. BundleAgent supplies default empty profile evidence.
3. Moderator owns per-container readiness/reset surface.
4. Moderator does not own bundle topology.
5. Moderator does not add containers to waiting lists.
6. Neither component calculates access references.
