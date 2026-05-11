# CME-W03 — Capacity Profiles And Container Shape

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W03` |
| Wave Name | Capacity Profiles And Container Shape |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Establish capacity and uniform container shape descriptors before real containers, registry storage, or scaling behavior |

## 2. What This Wave Implements

```text
capacity/
  TCapacityProfileId
  TCapacityGenerationId
  TCapacityProfileStatus
  TCapacityProfileKind
  TScalingDirectionKind
  TCapacityIssueKind
  TUniformContainerCapacityProfile
  TIngressCapacityProfile
  TDispatchCapacityProfile
  TCirculationCapacityProfile
  TExtremeDefaultProfile
  THorizontalScalingProfile
  TVerticalScalingProfile
  TCapacityProfileReport
  TUniformCapacityInvariantReport
```

## 3. What This Wave Does Not Implement

```text
container storage
container registry
actual horizontal scaling
actual vertical scaling
safe-point execution
eviction execution
reference supply
ingress placement
dispatch exposure
bridge drain handling
read-side backpressure
```

## 4. Architectural Rules Preserved

1. Capacity is profile-defined, not hot-path discovered.
2. Uniform container capacity is a family-level invariant.
3. Horizontal scaling changes container count.
4. Vertical scaling changes family-wide slots-per-container.
5. Extreme default is a profile descriptor, not unbounded memory.
6. This wave does not introduce broker/backpressure behavior.
