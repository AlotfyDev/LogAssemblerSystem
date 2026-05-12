# EG-POL-CAT-003 — Policy System Interaction Catalog

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| EG-POL-CAT-003-DOC-001 | Document Title | Policy System Interaction Catalog |
| EG-POL-CAT-003-DOC-002 | File Name | `EG-POL-CAT-003_Policy_System_Interaction_Catalog.md` |
| EG-POL-CAT-003-DOC-003 | Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| EG-POL-CAT-003-DOC-004 | Catalog Wave | `EG-POL-CAT-CW02_Component_And_Interaction_Catalog` |
| EG-POL-CAT-003-DOC-005 | Scope | Interactions among EG-POL policy system layers only |
| EG-POL-CAT-003-DOC-006 | Status | Catalog Draft V1 |
| EG-POL-CAT-003-DOC-007 | Depends On | `EG-POL-CAT-001`, `EG-POL-CAT-002`, `EG-POL-W01`–`EG-POL-W34` |
| EG-POL-CAT-003-DOC-008 | Companion Diagram | `diagrams/EG-POL-CAT-003_interaction_map.mmd` |

---

## 2. Purpose

This document catalogs the primary **interactions** inside the EG-POL policy system.

It answers:

```text
How do the policy system layers relate to one another, what information flows
between them, what gates are required, and what collapses are forbidden?
```

This document catalogs relations; it does not implement the relations.

---

## 3. Interaction Vocabulary

| Interaction Kind | Meaning |
|---|---|
| `contains` | One aggregate structurally carries another concept. |
| `describes` | One descriptor describes a target, capability, contract, or boundary. |
| `requires` | A later stage needs evidence from an earlier stage. |
| `gates` | A stage can allow/block progression. |
| `indexes` | A catalog or registry view references a policy artifact. |
| `plans` | A stage builds a non-executing plan. |
| `observes` | A stage records evidence/trace/audit references. |
| `reports` | A stage emits status, issue, or readiness output. |

---

## 4. Core Interaction Chain

The central policy-system progression is:

```text
Policy Object Foundation
→ Family / Target Capability / Compatibility
→ Assignment Lifecycle
→ Source / Publication / Registry Versioning
→ Realization Contract
→ Runtime Readiness
→ Runtime Plan
→ Realizer Interface
→ Realization Session
→ Execution Plan
→ Engine Skeleton
→ Failure / Recovery Boundaries
→ Compliance Suite
→ Production Readiness Gate
```

This chain is intentionally **not** an execution pipeline.

It is a governed progression from structure to readiness and production hardening.

---

## 5. Primary Interactions

### 5.1 Policy Object Foundation → `TPolicy`

| Field | Value |
|---|---|
| Source | W01–W08 foundations |
| Target | W09 `TPolicy` aggregate |
| Interaction Kind | `contains` |
| Data Passed | identity, clauses, replacement, lifecycle, observation, realization binding, graph/traversal foundations |
| Boundary Rule | `TPolicy` remains semantic governing aggregate. |
| Forbidden Collapse | `TPolicy` must not become executor, registry, assignment, target owner, or runtime orchestrator. |

---

### 5.2 `TPolicy` → Assignment Basics

| Field | Value |
|---|---|
| Source | W09 `TPolicy` / `TPolicyView` |
| Target | W10 assignment relation |
| Interaction Kind | `requires` / `relates` |
| Data Passed | policy reference, target reference, assignment status/result |
| Boundary Rule | Assignment relates policy to external target context. |
| Forbidden Collapse | Assignment must not execute or own target. |

---

### 5.3 Assignment Basics → Policy Registry Basics

| Field | Value |
|---|---|
| Source | W10 assignment relation |
| Target | W11 policy registry basics |
| Interaction Kind | `indexes` |
| Data Passed | policy identity, lookup key, registry entry descriptor, registry view/snapshot |
| Boundary Rule | Registry catalogs policy artifacts and lookup views. |
| Forbidden Collapse | Registry must not become service locator, DI container, persistence engine, or target locator. |

---

### 5.4 Family And Scope → Target Capability Contracts

| Field | Value |
|---|---|
| Source | W12 family/scope profile |
| Target | W13 target capability contracts |
| Interaction Kind | `requires` |
| Data Passed | family kind, scope path, target capability descriptor/set |
| Boundary Rule | Family language and target capability language remain descriptive. |
| Forbidden Collapse | Capability descriptor must not become C++ method call or target invocation. |

---

### 5.5 Family / Capability → Compatibility Matrix

| Field | Value |
|---|---|
| Source | W12 family profile, W13 target capability set |
| Target | W14 compatibility matrix |
| Interaction Kind | `gates` |
| Data Passed | compatibility rule, issue, report, evaluator, matrix |
| Boundary Rule | Compatibility can allow/block relation, not activate it. |
| Forbidden Collapse | Compatibility must not become assignment lifecycle or runtime readiness. |

---

### 5.6 Compatibility Matrix → Assignment Lifecycle

| Field | Value |
|---|---|
| Source | W14 compatibility report/rule/evaluator |
| Target | W15 assignment lifecycle/conflict |
| Interaction Kind | `requires` / `gates` |
| Data Passed | compatibility outcome, issues, conflicts, resolution candidates |
| Boundary Rule | Assignment lifecycle consumes compatibility results. |
| Forbidden Collapse | Assignment lifecycle must not invent compatibility semantics or execute policy. |

---

### 5.7 Source / Publication → Registry Versioning

| Field | Value |
|---|---|
| Source | W16 source/publication descriptors |
| Target | W17 registry versioning/publication view |
| Interaction Kind | `indexes` / `describes` |
| Data Passed | source descriptor, publication state, publication record, version lineage, snapshot, versioned lookup |
| Boundary Rule | Publication and registry versioning provide eligibility context. |
| Forbidden Collapse | Publication must not imply assignment; registry versioning must not persist or execute. |

---

### 5.8 Assignment / Registry / Compatibility → Realization Contract

| Field | Value |
|---|---|
| Source | W14–W17 evidence |
| Target | W18 realization contract foundation |
| Interaction Kind | `requires` |
| Data Passed | compatibility result, assignment state, publication state, context id, preconditions, trace, request |
| Boundary Rule | Realization contract describes conditions for possible realization. |
| Forbidden Collapse | Realization contract must not become realizer or executor. |

---

### 5.9 Realization Contract → Runtime Readiness

| Field | Value |
|---|---|
| Source | W18 contract/context/request/preconditions |
| Target | W19 runtime readiness model |
| Interaction Kind | `gates` |
| Data Passed | readiness gates, issues, admission, report, state |
| Boundary Rule | Readiness determines whether future realization may be considered. |
| Forbidden Collapse | Runtime readiness must not execute, mutate, or invoke target. |

---

### 5.10 Runtime Readiness → Runtime Plan

| Field | Value |
|---|---|
| Source | W19 readiness report/admission |
| Target | W20 runtime plan |
| Interaction Kind | `plans` |
| Data Passed | readiness state, plan status, plan step, issue, plan view |
| Boundary Rule | Plan is still pre-execution. |
| Forbidden Collapse | Runtime plan must not become execution engine. |

---

### 5.11 Runtime Plan → PolicyRealizer Interface

| Field | Value |
|---|---|
| Source | W20 runtime plan |
| Target | W21 realizer interface/result model |
| Interaction Kind | `requires` / `reports` |
| Data Passed | plan ref, realizer id/status/capability/issue/result/view |
| Boundary Rule | Realizer interface defines runtime-facing contract. |
| Forbidden Collapse | Realizer interface must not directly mutate targets without future target-specific execution contracts. |

---

### 5.12 Realizer Interface → Realization Session

| Field | Value |
|---|---|
| Source | W21 realizer identity/result/capability |
| Target | W22 realization session |
| Interaction Kind | `contains` / `observes` |
| Data Passed | session id, state, issue, open request, result, view |
| Boundary Rule | Session scopes a realization attempt. |
| Forbidden Collapse | Session must not become target invocation or engine runtime. |

---

### 5.13 Realization Session → Execution Plan

| Field | Value |
|---|---|
| Source | W22 session context |
| Target | W23 execution plan |
| Interaction Kind | `plans` |
| Data Passed | plan id, status, guard, issue, step, report, view |
| Boundary Rule | Execution plan is pre-execution description. |
| Forbidden Collapse | Execution plan must not execute. |

---

### 5.14 Execution Plan → Realization Engine Skeleton

| Field | Value |
|---|---|
| Source | W23 execution plan/report/guards |
| Target | W24 engine skeleton |
| Interaction Kind | `requires` / `reports` |
| Data Passed | engine config, status, issue, result, view |
| Boundary Rule | Engine remains skeleton. |
| Forbidden Collapse | Engine skeleton must not become production executor. |

---

### 5.15 Policy Targets → System-Wide Integration Skeleton

| Field | Value |
|---|---|
| Source | W25–W28 target descriptors |
| Target | W29 system-wide integration skeleton |
| Interaction Kind | `collects` / `plans` |
| Data Passed | log-level API targets, material circulation targets, communication context surfaces, add-on targets, integration plan/report |
| Boundary Rule | System-wide skeleton summarizes target surfaces. |
| Forbidden Collapse | System-wide skeleton must not execute domain behavior. |

---

### 5.16 Hardening Boundaries → Production Readiness Gate

| Field | Value |
|---|---|
| Source | W30 persistence boundary, W31 audit export boundary, W32 failure/recovery, W33 test/compliance |
| Target | W34 production readiness gate |
| Interaction Kind | `gates` / `reports` |
| Data Passed | persistence refs, audit refs, failure/recovery records, compliance assertions, readiness evidence |
| Boundary Rule | Production readiness gate evaluates hardening posture. |
| Forbidden Collapse | Production gate must not deploy, execute, or mutate targets. |

---

## 6. Ecosystem Target Interactions

### 6.1 Log Level API Policy Targets

| Field | Value |
|---|---|
| Wave | W25 |
| Interaction | EG-POL describes target kinds and capability profiles for log-level API components. |
| Data Passed | target kind, descriptor, capability profile, family target rules, registry view, integration report. |
| Does Not Do | validation mutation, timestamp algorithm, metadata injection, envelope assembly runtime. |

### 6.2 Material Circulation Policy Targets

| Field | Value |
|---|---|
| Wave | W26 |
| Interaction | EG-POL describes policy target surfaces for material-circulation components. |
| Data Passed | target kind, descriptor, capability profile, family target rules, registry view, integration report. |
| Does Not Do | slot mutation, round manager algorithm, dispatcher execution. |

### 6.3 Communication Context Policy Surface

| Field | Value |
|---|---|
| Wave | W27 |
| Interaction | EG-POL describes policy surfaces over communication context. |
| Data Passed | surface kind, descriptor, capability profile, rules, registry view, integration report. |
| Does Not Do | channel mutation, binding execution, session opening, bridge stepping, endpoint invocation. |

### 6.4 Add-on Policy Targets

| Field | Value |
|---|---|
| Wave | W28 |
| Interaction | EG-POL describes optional add-on policy targets. |
| Data Passed | add-on target kind, descriptor, capability profile, family target rule set, registry view, integration report. |
| Does Not Do | database write, telemetry export, file I/O, foreign runtime call, Thin C ABI invocation. |

---

## 7. Interaction Anti-Collapse Matrix

| Interaction | Must Not Collapse Into |
|---|---|
| `Policy → Assignment` | assignment execution |
| `Compatibility → Assignment` | assignment activation |
| `Assignment → Runtime Readiness` | runtime execution |
| `Publication → Registry` | persistence engine |
| `Registry → Runtime Plan` | service locator |
| `Runtime Readiness → Runtime Plan` | target invocation |
| `Runtime Plan → Realizer` | target mutation |
| `Realizer → Session` | production execution engine |
| `Session → Execution Plan` | execution |
| `Execution Plan → Engine` | production runtime |
| `Engine → Failure/Recovery` | automatic remediation |
| `Compliance Suite → Production Gate` | CI/CD runner or deployment |

---

## 8. Interaction Maintenance Notes

1. Add a new interaction when a wave introduces a new dependency path or new integration target.
2. Each interaction must explicitly state what is passed and what is forbidden.
3. Do not create an interaction that implies target invocation unless a future runtime wave explicitly authorizes it.
4. Keep diagrams aligned with this catalog; every major interaction in this file should be visible in `EG-POL-CAT-003_interaction_map.mmd`.
