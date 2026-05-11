# CME-CAPDELIV-DEP-000 — Dependency-First Delivery Cluster Method

## 1. Purpose

This document defines the dependency-first cluster method for capability delivery.

Instead of delivering by component number, the plan groups the 21 parent components into dependency-first clusters.

## 2. Principle

```text
Dependency first.
Then what depends on it.
```

## 3. Cluster Logic

The cluster sequence is:

```text
CME-CL-00 Vocabulary / Identity Foundations
→ CME-CL-01 Observation / Evidence Foundations
→ CME-CL-02 Capacity / Safety Foundations
→ CME-CL-03 Residency Structures
→ CME-CL-04 Runtime Coordination
→ CME-CL-05 Reference And Movement Execution
→ CME-CL-06 Lifecycle, Eviction, And Boundary Contracts
→ CME-CL-07 Post-Bridge / Read-Side Circulation Profile
```

## 4. Why This Matters

A component like `Dispatcher` cannot be delivered production-functionally before:

```text
IDs
State
Views/Reports
ReferencePrecalculator
Slot/Container
Boundary contracts
```

Similarly, `ReadSide_Circulation_Profile` depends on the output boundary, release/recycle, diagnostics, capacity, and bridge/addon contracts.

## 5. Outputs

```text
CME-CAPDELIV-DEP-001_Component_Dependency_Cluster_Map.csv
CME-CAPDELIV-DEP-002_Topological_Component_Order.csv
CME-CAPDELIV-DEP-003_Cluster_Delivery_Roadmap.csv
CME-CAPDELIV-DEP-004_Component_Cluster_Membership.csv
CME-CAPDELIV-DEP-005_Cluster_Dependency_Edges.csv
```
