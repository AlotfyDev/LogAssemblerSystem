# EG-POL-CAT-004 — Policy System Gap Matrix

## 1. Document Control

| Field | Value |
|---|---|
| Document Title | Policy System Gap Matrix |
| File Name | `EG-POL-CAT-004_Gap_Matrix.md` |
| Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| Catalog Wave | EG-POL-CAT-CW03_Gaps_And_Addons |
| Scope | EG-POL policy subsystem only, covering W01–W34 and ARCH-001–ARCH-008 |
| Status | Catalog Draft V1 |
| Primary Purpose | Identify what has been covered, what remains missing, risk if ignored, and candidate future waves |

---

## 2. Purpose

This document captures the remaining gaps in the policy subsystem after the completion of:

```text
EG-POL-W01 → EG-POL-W34
EG-POL-ARCH-001 → EG-POL-ARCH-008
EG-POL-CAT-CW01 → EG-POL-CAT-CW02
```

The goal is not to reopen completed work. The goal is to classify the remaining gaps so future waves can be planned without collapsing boundaries.

This matrix is catalog-level. It is not a runtime validator, not a backlog manager, not a CI system, and not a replacement for architecture documents or implementation waves.

---

## 3. Gap Classification Model

| Classification | Meaning |
|---|---|
| `type_gap` | Missing type-level representation or semantic carrier |
| `contract_gap` | Missing contract between layers or domains |
| `runtime_gap` | Missing runtime mechanism, deliberately deferred so far |
| `governance_gap` | Missing authority, publication, compliance, or process model implementation |
| `integration_gap` | Missing ecosystem binding between policy subsystem and other subsystem surfaces |
| `addon_gap` | Missing optional extension point implementation |
| `operation_gap` | Missing production operation support, persistence, export, recovery, or hardening |

---

## 4. System-Level Gap Matrix

| Area | Covered Today | Still Missing | Risk If Ignored | Candidate Future Wave |
|---|---|---|---|---|
| Policy identity | Primitive identity, family id, version, scope, source, provenance | Global naming authority and collision policy across all future subsystems | Duplicate or ambiguous policy families | `EG-POL-W35_Global_Naming_And_Family_Authority` |
| Clause model | Clause id, kind, role, status, clause set, clause view | Typed clause payloads, expression model, clause evaluator, clause normalization | Policies stay descriptive without actionable semantics | `EG-POL-W36_Typed_Clause_Expression_Model` |
| Clause compatibility | Clause grouping exists | Cross-clause compatibility, contradictions, override semantics | Conflicting policy objects may appear structurally valid | `EG-POL-W37_Clause_Compatibility_And_Normalization` |
| Replacement | Safe points, replacement boundaries, eligibility, rules, plans | Runtime quiescence protocol, component-safe replacement handshake | Replacement planning remains descriptive only | `EG-POL-W38_Runtime_Replacement_Protocol` |
| Lifecycle | Lifecycle state and views | Lifecycle command model, lifecycle authority implementation | Lifecycle changes cannot be governed concretely | `EG-POL-W39_Lifecycle_Command_And_Authority_Model` |
| Observation/audit | Observation carriers, evidence refs, trace refs, audit trail | Audit sinks, retention rules, correlation with system diagnostics | Evidence exists as references but is not operationally exported | `EG-POL-W40_Audit_Retention_And_Correlation_Model` |
| Realization binding | Descriptor-level binding and target kind | Concrete target capability surface adapters | Realizer cannot safely act on real component surfaces | `EG-POL-W41_Target_Capability_Surface_Adapters` |
| Policy graph | Structural graph, node/edge/invariant carriers | Graph normalization, graph diff, graph merge, graph validation depth | Large policy objects become hard to review | `EG-POL-W42_Graph_Normalization_And_Diff_Model` |
| Traversal foundation | Traversal vocabulary only | Traversal engine, path selection, branch/merge mechanics | Traversal remains non-executing and analysis-only | Deferred until runtime orchestration is justified |
| TPolicy aggregate | Aggregate, view, snapshot, build request/result, validation report | Rich builder pipeline, canonical validation pipeline | Validity is not consistently enforced at construction time | `EG-POL-W43_Canonical_Policy_Builder_And_Validator` |
| Assignment basics | Assignment relation and target ref | Concrete assignment activation engine | Assignments cannot be activated operationally | `EG-POL-W44_Assignment_Activation_Engine` |
| Assignment lifecycle | Lifecycle states, transitions, conflicts, resolution carriers | Runtime assignment state store, conflict resolver, priority evaluator | Assignment state cannot safely drive runtime readiness | `EG-POL-W45_Assignment_State_And_Conflict_Resolver` |
| Policy registry | In-memory/catalog-facing registry basics | Persistent registry adapter contracts and storage implementations | Registry entries are not durable | `EG-POL-W46_Registry_Persistence_Adapters` |
| Source/publication | Source descriptor, publication state, record, lineage | Source parser adapters, publication workflow engine | Publication remains a descriptor, not workflow | `EG-POL-W47_Source_Adapters_And_Publication_Workflow` |
| Registry versioning | Version index, snapshot, versioned lookup, publication view | Persistent version index, rollback selection logic | Rollback/readiness analysis stays manual | `EG-POL-W48_Version_Index_And_Rollback_Selection` |
| Compatibility matrix | Family-target rules, evaluator foundation, reports | Full rule repository and domain-specific compatibility rule packs | Compatibility may be incomplete across future targets | `EG-POL-W49_Domain_Compatibility_Rule_Packs` |
| Runtime readiness | Readiness states, gates, issues, reports, evaluator | Operational readiness evaluator bound to real sources | Readiness reports stay non-operational | `EG-POL-W50_Operational_Readiness_Evaluator` |
| Runtime plan | Runtime plan id/status/issues/steps/view | Plan compiler from policy + target + readiness | Plans remain manually assembled | `EG-POL-W51_Runtime_Plan_Compiler` |
| Policy realizer | Realizer interface, capabilities, result model | Concrete realizers for subsystem surfaces | Policy cannot apply to real target domains | `EG-POL-W52_Subsystem_Realizer_Packs` |
| Realization session | Session lifecycle around request/contract/readiness/plan/realizer | Session execution coordinator | Realization session cannot drive controlled progression | `EG-POL-W53_Realization_Session_Coordinator` |
| Execution plan | Execution plan and guards | Execution guard evaluator and step runner | Execution planning remains inert | `EG-POL-W54_Execution_Guard_Evaluator` |
| Engine skeleton | Engine skeleton and result/status/config | Production engine implementation | No orchestrated policy realization | Deferred until all guard gates pass |
| Ecosystem target packs | LogLevelApi, MaterialCirculation, CommunicationContext, Addons, system-wide target descriptors | Domain-specific target adapters and capability probes | Integration targets exist but cannot be introspected live | `EG-POL-W55_Domain_Target_Adapter_Probes` |
| Persistence boundary | Persistence boundary descriptors and refs | Concrete persistence medium adapters | No durable policy persistence | `EG-POL-W56_Persistence_Medium_Adapters` |
| Audit export boundary | Audit export boundary descriptors and refs | Audit exporters | Audit export remains declarative | `EG-POL-W57_Audit_Export_Adapters` |
| Failure/recovery | Runtime failure, recovery, quarantine descriptors | Automatic recovery execution and supervised remediation | Failures can be described but not remediated | `EG-POL-W58_Supervised_Recovery_Controller` |
| Compliance suite | Compliance assertions, test cases, suite report | Test runner, CI integration, report persistence | Compliance is not automatically enforced | `EG-POL-W59_Compliance_Runner_And_Report_Export` |
| Production readiness | Readiness gate, criteria, evidence, report | Production gate runner and release signoff workflow | Production status remains manually interpreted | `EG-POL-W60_Production_Gate_Runner` |

---

## 5. Priority Groups

### 5.1 High Priority

```text
Typed clause expression model
Canonical policy builder and validator
Assignment activation engine
Registry persistence adapters
Operational runtime readiness evaluator
Compliance runner
```

These gaps block reliable operational use of the policy subsystem.

### 5.2 Medium Priority

```text
Graph normalization and diff
Version rollback selection
Domain compatibility rule packs
Audit export adapters
Policy target adapter probes
```

These gaps improve governance, maintainability, and integration.

### 5.3 Deferred Until Runtime Justification

```text
Traversal engine
Production realization engine
Automatic recovery execution
Concrete target mutation
Concrete subsystem-specific policy application
```

These remain deliberately deferred because the current subsystem mostly delivers descriptors, boundaries, skeletons, and gates.

---

## 6. Anti-Collapse Gap Rules

The following must remain true while closing gaps:

```text
Clause expression ≠ policy execution
Assignment activation ≠ target invocation
Runtime readiness ≠ runtime execution
Runtime plan ≠ execution
Realizer interface ≠ concrete executor
Persistence boundary ≠ storage engine
Audit export boundary ≠ telemetry exporter
Production readiness gate ≠ deployment
```

---

## 7. Catalog Conclusion

The policy subsystem is architecturally rich and structurally layered, but most completed waves are still intentionally foundational, descriptive, boundary-oriented, or skeleton-oriented. The remaining gap work should proceed from semantic certainty to operational adapters, and only then to concrete realization behavior.
