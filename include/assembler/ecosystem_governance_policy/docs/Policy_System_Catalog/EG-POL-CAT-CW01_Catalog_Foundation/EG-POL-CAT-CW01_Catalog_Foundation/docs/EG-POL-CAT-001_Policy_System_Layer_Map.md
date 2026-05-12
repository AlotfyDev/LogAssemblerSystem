# EG-POL-CAT-001 — Policy System Layer Map

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| EG-POL-CAT-001-DOC-001 | Document Title | Policy System Layer Map |
| EG-POL-CAT-001-DOC-002 | File Name | `EG-POL-CAT-001_Policy_System_Layer_Map.md` |
| EG-POL-CAT-001-DOC-003 | Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| EG-POL-CAT-001-DOC-004 | Catalog Wave | `EG-POL-CAT-CW01_Catalog_Foundation` |
| EG-POL-CAT-001-DOC-005 | Domain | `ecosystem_governance` |
| EG-POL-CAT-001-DOC-006 | Subsystem Scope | Policy System only |
| EG-POL-CAT-001-DOC-007 | Covered Span | `EG-POL-W01` through `EG-POL-W34` |
| EG-POL-CAT-001-DOC-008 | Status | Catalog Layer Map Draft |
| EG-POL-CAT-001-DOC-009 | Related Diagram | `diagrams/EG-POL-CAT-001_layer_map.mmd` |
| EG-POL-CAT-001-DOC-010 | Depends On | `EG-POL-CAT-000_Catalog_Roadmap_And_Doctrine.md` |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the layer map for the completed EG-POL Policy System.

It answers the question:

```text
How should the Policy System be viewed as a stack of architectural and
implementation layers from primitive policy identity through production
readiness gates?
```

The map is meant for navigation, onboarding, review, and later gap analysis.

---

## 3. Layer Summary

The completed Policy System is organized into eight major layers:

```text
1. Policy Object Foundation
2. Assignment And Registry Basics
3. Architecture Completion
4. Implementation Foundation Completion
5. Policy Runtime Readiness
6. Policy Realization Runtime Skeleton
7. Ecosystem Integration
8. Production Hardening
```

These layers correspond to the delivery history of the subsystem.

---

## 4. Layer 1 — Policy Object Foundation

### 4.1 Scope

```text
EG-POL-W01 → EG-POL-W09
```

### 4.2 Role

This layer defines what a policy object is.

It includes:

1. primitive identity,
2. clauses,
3. safe point and replacement,
4. lifecycle,
5. observation and audit,
6. realization binding and target kind descriptors,
7. policy graph structure,
8. traversal foundation types,
9. `TPolicy` aggregate and views.

### 4.3 Layer Boundary

This layer does not own:

```text
assignment runtime
policy registry runtime
realizer execution
target invocation
persistence
production deployment
```

### 4.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W01 | `EG-POL-W01_Primitive_Policy_Identity` | identity, family id, version, scope, source, provenance, status/result basics |
| W02 | `EG-POL-W02_Policy_Clauses` | clause ids, kinds, roles, status, sets, views |
| W03 | `EG-POL-W03_Safe_Point_And_Replacement` | safe points, replacement boundaries, eligibility, rules, plans |
| W04 | `EG-POL-W04_Policy_Lifecycle` | lifecycle states, activation/suspension/retirement markers, snapshots |
| W05 | `EG-POL-W05_Policy_Observation_And_Audit` | observation ids/kinds, evidence, trace, audit trail |
| W06 | `EG-POL-W06_Realization_Binding_And_Target_Kind` | realization binding descriptor layer and target kind descriptor |
| W07 | `EG-POL-W07_Policy_Graph_Structure` | structural graph, nodes, edges, invariants, views |
| W08 | `EG-POL-W08_Traversal_Foundation_Types` | traversal vocabulary only |
| W09 | `EG-POL-W09_TPolicy_Aggregate_And_View` | semantic governing aggregate |

---

## 5. Layer 2 — Assignment And Registry Basics

### 5.1 Scope

```text
EG-POL-W10 → EG-POL-W11
```

### 5.2 Role

This layer introduces the first external relations around policy objects:

1. policy assignment basics,
2. registry basics.

### 5.3 Layer Boundary

Assignment is not execution.

Registry is not storage engine.

### 5.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W10 | `EG-POL-W10_Policy_Assignment_Basics` | non-executing relation between policy and target descriptor |
| W11 | `EG-POL-W11_Policy_Registry_Basics` | bounded catalog-facing registry layer |

---

## 6. Layer 3 — Architecture Completion

### 6.1 Scope

```text
EG-POL-ARCH-001 → EG-POL-ARCH-008
```

### 6.2 Role

This layer completed the architectural doctrine before Phase B implementation.

It defined:

1. policy family taxonomy and scope,
2. target kind and capability model,
3. family compatibility matrix,
4. assignment lifecycle and conflict model,
5. authority and governance roles,
6. source, publication, and registry versioning,
7. realization contracts and runtime readiness,
8. compliance and validation matrix.

### 6.3 Layer Boundary

This layer is architecture documentation only.

It does not deliver C++ headers.

### 6.4 Architecture Documents

| Document | Subject |
|---|---|
| `EG-POL-ARCH-001` | Policy family taxonomy and scope |
| `EG-POL-ARCH-002` | Target kind and capability model |
| `EG-POL-ARCH-003` | Policy family compatibility matrix |
| `EG-POL-ARCH-004` | Assignment lifecycle and conflict model |
| `EG-POL-ARCH-005` | Policy authority and governance roles |
| `EG-POL-ARCH-006` | Policy source publication and registry versioning |
| `EG-POL-ARCH-007` | Realization contracts and runtime readiness |
| `EG-POL-ARCH-008` | Compliance and validation matrix |

---

## 7. Layer 4 — Implementation Foundation Completion

### 7.1 Scope

```text
EG-POL-W12 → EG-POL-W17
```

### 7.2 Role

This layer implemented the descriptor foundations planned by Phase A.

It includes:

1. family and scope profiles,
2. target capability contracts,
3. family-target compatibility matrix,
4. assignment lifecycle and conflict descriptors,
5. source and publication descriptors,
6. registry versioning and publication view.

### 7.3 Layer Boundary

This layer still does not activate assignments or execute policies.

### 7.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W12 | `EG-POL-W12_Policy_Family_And_Scope` | family profile and scope compatibility foundation |
| W13 | `EG-POL-W13_Target_Capability_Contracts` | target capabilities, descriptors, sets, compatibility report |
| W14 | `EG-POL-W14_Family_Target_Compatibility_Matrix` | family-target rules, evaluator, matrix, report |
| W15 | `EG-POL-W15_Assignment_Lifecycle_And_Conflict` | assignment lifecycle state, conflict, resolution view |
| W16 | `EG-POL-W16_Policy_Source_And_Publication` | source descriptor, publication state/record, version lineage |
| W17 | `EG-POL-W17_Registry_Versioning_And_Publication_View` | registry version index, snapshots, versioned lookup |

---

## 8. Layer 5 — Policy Runtime Readiness

### 8.1 Scope

```text
EG-POL-W18 → EG-POL-W20
```

### 8.2 Role

This layer prepares runtime-facing governance without executing runtime behavior.

It includes:

1. realization contract foundation,
2. runtime readiness model,
3. policy runtime plan.

### 8.3 Layer Boundary

Runtime readiness is not runtime execution.

Runtime plan is not execution plan in the concrete target sense.

### 8.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W18 | `EG-POL-W18_Realization_Contract_Foundation` | contract/context/precondition/failure/trace/request |
| W19 | `EG-POL-W19_Runtime_Readiness_Model` | readiness state/gate/issue/admission/report/evaluator |
| W20 | `EG-POL-W20_Policy_Runtime_Plan` | plan id/status/issue/step/plan/view |

---

## 9. Layer 6 — Policy Realization Runtime Skeleton

### 9.1 Scope

```text
EG-POL-W21 → EG-POL-W24
```

### 9.2 Role

This layer introduces realizer-facing skeletons.

It includes:

1. realizer interface and result model,
2. realization session,
3. realization execution plan,
4. realization engine skeleton.

### 9.3 Layer Boundary

The layer is still not a production executor.

No target invocation or mutation is owned here.

### 9.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W21 | `EG-POL-W21_PolicyRealizer_Interface_And_Result_Model` | realizer id/status/capability/issue/result/view/interface |
| W22 | `EG-POL-W22_PolicyRealizationSession` | session lifecycle around request/contract/readiness/plan/realizer |
| W23 | `EG-POL-W23_PolicyRealizationExecutionPlan` | pre-execution guards/issues/steps/reports/plans |
| W24 | `EG-POL-W24_PolicyRealizationEngine_Skeleton` | non-executing engine skeleton |

---

## 10. Layer 7 — Ecosystem Integration

### 10.1 Scope

```text
EG-POL-W25 → EG-POL-W29
```

### 10.2 Role

This layer maps the policy system onto ecosystem target surfaces.

It includes:

1. LogLevelApi targets,
2. MaterialCirculation targets,
3. CommunicationContext policy surfaces,
4. Addon policy targets,
5. system-wide integration skeleton.

### 10.3 Layer Boundary

Integration descriptors do not execute domain behavior.

### 10.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W25 | `EG-POL-W25_LogLevelApi_Policy_Targets` | log-level API target descriptors and target sets |
| W26 | `EG-POL-W26_MaterialCirculation_Policy_Targets` | material circulation target descriptors and target sets |
| W27 | `EG-POL-W27_CommunicationContext_Policy_Surface` | communication context policy surface descriptors |
| W28 | `EG-POL-W28_Addon_Policy_Targets` | add-on target descriptors and target sets |
| W29 | `EG-POL-W29_System_Wide_Policy_Integration_Skeleton` | system-wide integration id set, plan, report, target set |

---

## 11. Layer 8 — Production Hardening

### 11.1 Scope

```text
EG-POL-W30 → EG-POL-W34
```

### 11.2 Role

This layer prepares production-hardening boundaries and gates.

It includes:

1. persistence boundary,
2. audit export boundary,
3. runtime failure and recovery,
4. test and compliance suite,
5. production readiness gate.

### 11.3 Layer Boundary

Production hardening descriptors do not deploy, persist, export, run CI, or mutate runtime targets.

### 11.4 Delivered Waves

| Wave | Package | Layer Role |
|---|---|---|
| W30 | `EG-POL-W30_Policy_Persistence_Boundary` | persistence admission, medium kind, record/snapshot refs, boundary report |
| W31 | `EG-POL-W31_Policy_Audit_Export_Boundary` | audit export admission, medium kind, record/snapshot refs, boundary report |
| W32 | `EG-POL-W32_Policy_Runtime_Failure_And_Recovery` | runtime failure kinds/severity/records/recovery/quarantine boundary |
| W33 | `EG-POL-W33_Policy_Test_And_Compliance_Suite` | compliance dimensions, assertions, test cases, suite reports |
| W34 | `EG-POL-W34_Production_Readiness_Gate` | production readiness gate, criteria, evidence, report, severity |

---

## 12. Cross-Layer Dependency Direction

The intended direction is:

```text
Policy Object Foundation
→ Assignment / Registry Basics
→ Architecture Completion
→ Implementation Foundation Completion
→ Runtime Readiness
→ Realization Runtime Skeleton
→ Ecosystem Integration
→ Production Hardening
```

Reverse dependencies should be treated as design smell unless explicitly bounded as a view/report/reference.

---

## 13. Key Non-Collapse Rules By Layer

| Layer | Must Not Collapse Into |
|---|---|
| Policy Object Foundation | executor, target owner |
| Assignment / Registry Basics | runtime activation, storage engine |
| Architecture Completion | implementation source of truth |
| Implementation Foundation | runtime execution |
| Runtime Readiness | runtime execution |
| Realization Runtime Skeleton | production executor |
| Ecosystem Integration | domain runtime behavior |
| Production Hardening | deployment, persistence engine, logging backend |

---

## 14. Catalog Continuation

The next catalog document should be:

```text
EG-POL-CAT-002_Component_And_Type_Catalog.md
```

That document will enumerate all primary types and components by ownership, wave, responsibility, dependencies, and maturity.
