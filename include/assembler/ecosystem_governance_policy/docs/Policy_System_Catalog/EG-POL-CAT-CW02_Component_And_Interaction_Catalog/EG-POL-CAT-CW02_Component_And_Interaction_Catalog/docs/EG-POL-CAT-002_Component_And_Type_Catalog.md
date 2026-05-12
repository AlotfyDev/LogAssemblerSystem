# EG-POL-CAT-002 — Component And Type Catalog

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| EG-POL-CAT-002-DOC-001 | Document Title | Component And Type Catalog |
| EG-POL-CAT-002-DOC-002 | File Name | `EG-POL-CAT-002_Component_And_Type_Catalog.md` |
| EG-POL-CAT-002-DOC-003 | Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| EG-POL-CAT-002-DOC-004 | Catalog Wave | `EG-POL-CAT-CW02_Component_And_Interaction_Catalog` |
| EG-POL-CAT-002-DOC-005 | Scope | EG-POL policy system only; `EG-POL-W01` through `EG-POL-W34` |
| EG-POL-CAT-002-DOC-006 | Status | Catalog Draft V1 |
| EG-POL-CAT-002-DOC-007 | Depends On | `EG-POL-CAT-000`, `EG-POL-CAT-001`, `EG-POL-W01`–`EG-POL-W34`, `EG-POL-ARCH-001`–`EG-POL-ARCH-008` |
| EG-POL-CAT-002-DOC-008 | Companion Diagram | `diagrams/EG-POL-CAT-002_component_type_map.mmd` |

---

## 2. Purpose

This document catalogs the **components and type groups** delivered in the EG-POL policy system waves.

It answers:

```text
What major policy-system components exist, where do they live, what do they own,
what do they explicitly not own, what waves delivered them, and what maturity
classification should readers assign to each part?
```

This is a **catalog**, not an implementation source of truth. It summarizes the architecture and delivery status so that the policy subsystem can be navigated without reopening every wave package.

---

## 3. Catalog Boundary

### 3.1 In Scope

This document catalogs:

```text
EG-POL-W01 → EG-POL-W34
Policy object foundation
Assignment and registry basics
Phase A architecture completion outputs
Phase B implementation foundation
Phase C runtime-readiness carriers
Phase D realization runtime skeletons
Phase E ecosystem target descriptors
Phase F production hardening boundaries and gates
```

### 3.2 Out of Scope

This document does **not** define:

```text
new C++ behavior
runtime execution
target invocation
target mutation
storage engine
service locator
policy registry implementation details beyond catalog references
communication-context mechanics
material-circulation mechanics
add-on runtime behavior
```

### 3.3 Core Non-Collapse Rules

```text
Catalog entry ≠ implementation type
Catalog entry ≠ registry entry
Catalog entry ≠ runtime handle
Catalog entry ≠ authority grant
Catalog entry ≠ execution permission
```

---

## 4. Maturity Vocabulary

| Maturity | Meaning |
|---|---|
| `primitive` | Low-level identity/status/result/reference types. |
| `foundation` | Foundational structure with bounded semantics, not runtime behavior. |
| `descriptor` | Describes something that may exist or be compatible; does not execute it. |
| `relation` | Represents a governed relation such as assignment or compatibility. |
| `boundary` | Defines an edge between the policy system and another concern without implementing the other concern. |
| `skeleton` | Structural placeholder for future runtime orchestration without production execution. |
| `gate` | Validation/readiness decision surface. |
| `catalog` | Navigational summary over delivered artifacts. |

---

## 5. Component Catalog Summary

| Layer | Wave(s) | Primary Folder | Maturity | Summary |
|---|---:|---|---|---|
| Primitive Policy Identity | W01 | `policy_type_system/identity/` | primitive | Policy identity, family identity, version, scope, source, provenance, status, issue, and result carriers. |
| Policy Clauses | W02 | `policy_type_system/clauses/` | foundation | Clause ids, kinds, roles, statuses, clause object, set, and view. |
| Safe Point And Replacement | W03 | `policy_type_system/replacement/` | foundation | Safe points, boundaries, eligibility, rules, plan, and replacement view. |
| Policy Lifecycle | W04 | `policy_type_system/lifecycle/` | foundation | Lifecycle, activation, suspension, retirement, markers, transitions, snapshots, views. |
| Observation And Audit | W05 | `policy_type_system/observation/` | foundation | Observation ids/kinds, evidence refs, trace refs, audit markers, records, trails, views. |
| Realization Binding And Target Kind | W06 | `policy_type_system/realization_binding/` | descriptor | Describes target kind and realization expectations without executing. |
| Policy Graph Structure | W07 | `policy_type_system/policy_graph/` | foundation | Structural policy graph, nodes, edges, invariants, and views. |
| Traversal Foundation Types | W08 | `policy_type_system/traversal_foundation/` | foundation | Sequence channels, readiness, cursor, relations, transitions, entry/exit surfaces. |
| TPolicy Aggregate And View | W09 | `policy_type_system/policy_core/` | foundation | Semantic governing aggregate and views/snapshots/build/validation carriers. |
| Assignment Basics | W10 | `policy_type_system/assignment/` | relation | Non-executing policy-to-target relation basics. |
| Policy Registry Basics | W11 | `policy_registry/` | catalog/foundation | Bounded in-memory/catalog-facing registry layer, not storage or service locator. |
| Policy Family And Scope | W12 | `policy_type_system/family/` | descriptor | Family kinds, scope paths, scope compatibility, family profile and view. |
| Target Capability Contracts | W13 | `policy_type_system/target_capability/` | descriptor | Target capability ids/kinds/descriptors/sets and compatibility report. |
| Family Target Compatibility Matrix | W14 | `policy_type_system/compatibility_matrix/` | relation/gate | Family-target compatibility rules, report, evaluator, matrix, and issues. |
| Assignment Lifecycle And Conflict | W15 | `policy_type_system/assignment_lifecycle/` | descriptor/relation | Assignment lifecycle states, transitions, conflicts, resolution, view. |
| Policy Source And Publication | W16 | `policy_type_system/source_publication/` | descriptor | Source descriptor, publication state, publication record, version lineage, view. |
| Registry Versioning And Publication View | W17 | `policy_registry/versioning/` | descriptor/catalog | Registry version index, publication snapshot, versioned lookup, publication view. |
| Realization Contract Foundation | W18 | `policy_type_system/realization_contract/` | descriptor | Contract ids/kinds, context ids, preconditions, failures, traces, contracts, contexts, requests. |
| Runtime Readiness Model | W19 | `policy_type_system/runtime_readiness/` | gate | Runtime readiness state, gate, issue, admission, report, evaluator. |
| Policy Runtime Plan | W20 | `policy_type_system/runtime_plan/` | descriptor/pre-execution | Runtime plan id/status/issues/steps/plan/view. |
| PolicyRealizer Interface And Result | W21 | `policy_type_system/policy_realizer/` | skeleton/interface | Realizer id/status/capability/issue/result/view/interface. |
| PolicyRealizationSession | W22 | `policy_type_system/realization_session/` | skeleton/session | Realization session id/state/issues/open request/result/view/session. |
| PolicyRealizationExecutionPlan | W23 | `policy_type_system/realization_execution_plan/` | descriptor/pre-execution | Execution plan id/status/guard/issues/steps/report/view/plan. |
| PolicyRealizationEngine Skeleton | W24 | `policy_type_system/realization_engine/` | skeleton | Engine id/status/config/issues/result/view/engine. |
| LogLevelApi Policy Targets | W25 | `policy_type_system/ecosystem_targets/log_level_api/` | descriptor | Log-level API policy target kinds, descriptors, capability profile, rules, registry view, integration report. |
| MaterialCirculation Policy Targets | W26 | `policy_type_system/ecosystem_targets/material_circulation/` | descriptor | Material circulation policy target kinds and integration descriptors. |
| CommunicationContext Policy Surface | W27 | `policy_type_system/ecosystem_targets/communication_context/` | descriptor | Communication-context policy surfaces and capability profiles. |
| Addon Policy Targets | W28 | `policy_type_system/ecosystem_targets/addons/` | descriptor | Add-on policy target descriptors and integration rule sets. |
| System-Wide Policy Integration Skeleton | W29 | `policy_type_system/ecosystem_targets/system_wide/` | skeleton/catalog | System-wide target set and integration plan/report skeleton. |
| Policy Persistence Boundary | W30 | `policy_persistence/` | boundary | Persistence admission, boundary descriptor, record refs, snapshot refs, medium kind, report. |
| Policy Audit Export Boundary | W31 | `policy_audit_export/` | boundary | Audit export admission, boundary descriptor, record refs, snapshot refs, medium kind, report. |
| Policy Runtime Failure And Recovery | W32 | `policy_runtime_failure/` | boundary/gate | Failure kind/severity/record, recovery action/plan/report, quarantine, boundary. |
| Policy Test And Compliance Suite | W33 | `policy_test_compliance/` | gate/catalog | Compliance assertions, dimensions, outcomes, severities, test cases, negative catalog, suite report. |
| Production Readiness Gate | W34 | `policy_production_readiness/` | gate | Production readiness criteria, evidence refs, issues, severity, report, gate and view. |

---

## 6. Detailed Component Entries

### 6.1 `policy_type_system/identity` — W01

**Owns:** primitive policy identity carriers.

**Does not own:** policy object behavior, assignment, registry, lifecycle, execution.

**Used by:** almost every later wave.

**Maturity:** `primitive`.

---

### 6.2 `policy_type_system/clauses` — W02

**Owns:** local clause representation and clause collection/view semantics.

**Does not own:** typed expression language, evaluation, runtime validation, policy realization.

**Used by:** `TPolicy`, validation, future expression/evaluator add-ons.

**Maturity:** `foundation`.

---

### 6.3 `policy_type_system/replacement` — W03

**Owns:** safe point and replacement metadata.

**Does not own:** hot-swap algorithm, quiescence protocol, target mutation, rollback execution.

**Used by:** lifecycle, graph, assignment, runtime readiness, failure/recovery.

**Maturity:** `foundation`.

---

### 6.4 `policy_type_system/lifecycle` — W04

**Owns:** policy lifecycle states and transition carriers.

**Does not own:** lifecycle authority, runtime commands, assignment activation.

**Used by:** assignment lifecycle, publication, runtime readiness, production gates.

**Maturity:** `foundation`.

---

### 6.5 `policy_type_system/observation` — W05

**Owns:** evidence, trace, audit marker, observation records, audit trails.

**Does not own:** telemetry exporter, logging framework, database audit sink.

**Used by:** realization traces, audit export boundary, compliance suite.

**Maturity:** `foundation`.

---

### 6.6 `policy_type_system/realization_binding` — W06

**Owns:** descriptive target-kind and realization-binding vocabulary.

**Does not own:** realizer, executor, target invocation, target ownership.

**Used by:** target capability contracts, realization contract foundation, runtime plan.

**Maturity:** `descriptor`.

---

### 6.7 `policy_type_system/policy_graph` — W07

**Owns:** structural graph constitution.

**Does not own:** traversal algorithm, scheduler, runtime orchestration.

**Used by:** `TPolicy`, validation, compliance checks.

**Maturity:** `foundation`.

---

### 6.8 `policy_type_system/traversal_foundation` — W08

**Owns:** traversal vocabulary and sequence-channel foundation.

**Does not own:** traversal engine, path selection, scheduling.

**Used by:** policy analysis, future orchestration tooling, graph views.

**Maturity:** `foundation`.

---

### 6.9 `policy_type_system/policy_core` — W09

**Owns:** `TPolicy` as semantic governing aggregate.

**Does not own:** assignment, registry, realizer, executor, target ownership.

**Used by:** assignment, registry, realization contract, compliance.

**Maturity:** `foundation`.

---

### 6.10 `policy_type_system/assignment` — W10

**Owns:** non-executing assignment relation basics.

**Does not own:** assignment lifecycle, activation, target invocation, compatibility evaluation.

**Used by:** assignment lifecycle, runtime readiness, realization session.

**Maturity:** `relation`.

---

### 6.11 `policy_registry` — W11 and W17

**Owns:** catalog-facing policy registry basics and versioned publication views.

**Does not own:** persistence storage engine, service location, dependency injection, target location.

**Used by:** publication, assignment eligibility, readiness, production gate.

**Maturity:** `catalog/foundation`.

---

### 6.12 `family`, `target_capability`, `compatibility_matrix` — W12–W14

**Owns:** policy-family profiles, target capability contracts, family-target compatibility rules.

**Does not own:** live target checks, target invocation, concrete target behavior.

**Used by:** assignment lifecycle, runtime readiness, policy realization.

**Maturity:** `descriptor/relation/gate`.

---

### 6.13 `assignment_lifecycle` — W15

**Owns:** assignment lifecycle and conflict descriptors.

**Does not own:** runtime activation engine, authority implementation, target mutation.

**Used by:** runtime readiness, realization session, failure/recovery, production gate.

**Maturity:** `descriptor/relation`.

---

### 6.14 `source_publication` and `policy_registry/versioning` — W16–W17

**Owns:** source/publication descriptors and registry versioning views.

**Does not own:** source parser, persistence storage, publication workflow engine.

**Used by:** assignment eligibility, runtime readiness, production readiness.

**Maturity:** `descriptor/catalog`.

---

### 6.15 `realization_contract`, `runtime_readiness`, `runtime_plan` — W18–W20

**Owns:** pre-execution contract, readiness, and runtime plan surfaces.

**Does not own:** realizer invocation, executor, target mutation, runtime engine.

**Used by:** realizer interface, realization sessions, execution plans.

**Maturity:** `descriptor/gate/pre-execution`.

---

### 6.16 `policy_realizer`, `realization_session`, `realization_execution_plan`, `realization_engine` — W21–W24

**Owns:** runtime-facing interfaces and skeletons.

**Does not own:** production execution, target invocation, target mutation, domain behavior.

**Used by:** future concrete realizers, failure/recovery, production gates.

**Maturity:** `skeleton/interface`.

---

### 6.17 `ecosystem_targets/*` — W25–W29

**Owns:** policy-target descriptors for ecosystem integration.

**Does not own:** runtime behavior of those domains.

**Used by:** compatibility, assignment, readiness, realization planning.

**Maturity:** `descriptor/skeleton`.

---

### 6.18 Phase F Boundaries And Gates — W30–W34

**Owns:** persistence boundary, audit export boundary, failure/recovery boundary, compliance suite, production readiness gate.

**Does not own:** storage engine, audit sink, actual recovery automation, CI runner, deployment.

**Used by:** production-hardening planning.

**Maturity:** `boundary/gate`.

---

## 7. Ownership Anti-Collapse Catalog

| Rule | Meaning |
|---|---|
| `TPolicy` must not own targets | Policy is governing aggregate, not target container. |
| Assignment must not execute | Assignment relates policy to target context only. |
| Compatibility must not activate | Compatibility permits or rejects progression. |
| Registry must not locate services | Registry catalogs policy artifacts, not runtime services. |
| Realization contract must not realize | Contract describes preconditions and allowed relation. |
| Runtime readiness must not execute | Readiness gates future realization. |
| Runtime plan must not execute | Plan describes intended steps only. |
| Realizer interface must not mutate directly | Concrete target mutation remains deferred behind future target-specific contracts. |
| Engine skeleton must not become production runtime | It is orchestration skeleton only. |
| Persistence boundary must not store | It defines boundary, not storage. |
| Audit export boundary must not export | It defines export boundary, not exporter. |
| Compliance suite must not become CI runner | It defines test/compliance structures only. |
| Production readiness gate must not deploy | It gates production movement only. |

---

## 8. Catalog Maintenance Notes

1. Add a new component entry whenever a new wave introduces a new folder or stable type group.
2. Do not add one entry per header unless the header is architecturally central.
3. Keep `owns` and `does not own` explicit for every major component group.
4. Update the companion diagram when a new major component group or dependency appears.
5. Do not convert this catalog into source-of-truth implementation logic.
