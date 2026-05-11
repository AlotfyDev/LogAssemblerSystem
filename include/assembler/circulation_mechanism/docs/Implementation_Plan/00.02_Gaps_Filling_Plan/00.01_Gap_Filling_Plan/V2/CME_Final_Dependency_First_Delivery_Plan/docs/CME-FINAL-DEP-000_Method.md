# CME-FINAL-DEP-000 — Final Dependency-First Delivery Method

## 1. Purpose

This package updates the prior 21-component capability delivery plan so that delivery follows dependency-first topological ordering rather than original component numbering.

## 2. Source Inputs

```text
CME-CAPDELIV-DEP-00_Dependency_First_Delivery_Clusters
CME_Capability_Delivery_Plan_21_Phases
```

## 3. Method

```text
1. Use cluster order as the primary dependency-first layer.
2. Use topological component order inside clusters.
3. Preserve each component's vertical wave plan.
4. Renumber phases and waves into final delivery order.
5. Track old component-number order vs new dependency-first order.
```

## 4. Counts

```text
final phases: 21
final waves: 80
clusters: 8
```

## 5. Delivery Rule

```text
A cluster should not start before its dependency clusters pass their acceptance gates,
unless a wave is explicitly marked safe-to-overlap.
```
