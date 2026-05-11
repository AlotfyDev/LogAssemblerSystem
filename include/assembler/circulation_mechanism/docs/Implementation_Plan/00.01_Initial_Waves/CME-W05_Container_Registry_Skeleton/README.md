# CME-W05 — Container Registry Skeleton

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W05` |
| Wave Name | Container Registry Skeleton |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first |
| Status | Implementation Skeleton |
| Purpose | Introduce fixed-capacity indexed storage skeleton for TContainer-like values, plus registry views and invariant reports |

## 2. What This Wave Implements

```text
container_registry/
  TContainerRegistry
  TContainerRegistryState
  TContainerStorageKind
  TContainerRegistryView
  TContainerRegistryCapacityView
  TContainerRegistryGenerationView
  TContainerRegistryInvariantReport
  TRegistryProfileSwitchReport
```

## 3. What This Wave Does Not Implement

```text
dynamic scaling
registry rebuild algorithm
waiting lists
reference calculation
container creation semantics
bundle topology authority
ingress placement
dispatch exposure
bridge bindings
```

## 4. Architectural Rules Preserved

1. Registry owns indexed container storage skeleton.
2. Registry index is 1-based and checked before access.
3. Waiting lists will later carry registry indices, not containers.
4. Registry view is read-only.
5. Registry does not calculate refs.
6. Registry does not decide round eligibility.
