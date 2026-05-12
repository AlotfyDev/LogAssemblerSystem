# EG-POL-CAT-006 — Wave Index And Delivery Map

## 1. Document Control

| Field | Value |
|---|---|
| Document Title | Wave Index And Delivery Map |
| File Name | `EG-POL-CAT-006_Wave_Index_And_Delivery_Map.md` |
| Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| Scope | EG-POL implementation and architecture delivery waves |
| Covered Range | `EG-POL-W01` through `EG-POL-W34`, plus `EG-POL-ARCH-001` through `EG-POL-ARCH-008` |
| Status | Catalog Draft V1 |

## 2. Purpose

This document indexes the policy system waves delivered so far and places each wave in its architectural phase, responsibility band, maturity level, and dependency position.

The goal is not to repeat every header file or every implementation detail. The goal is to provide a stable navigation and delivery map for the policy subsystem.

## 3. Catalog Boundary

This catalog does not replace:

- implementation waves,
- architecture documents,
- policy registry,
- persistence store,
- test runner,
- CI pipeline,
- runtime executor.

It is a navigational and architectural index.

## 4. Phase-Level Delivery Map

| Phase | Wave Range | Main Delivery Theme | Maturity |
|---|---:|---|---|
| Foundation | W01–W09 | Policy object constitution and aggregate | foundation |
| Foundation extension | W10–W11 | Assignment relation and registry basics | foundation / catalog-facing |
| Phase A | ARCH-001–ARCH-008 | Architecture completion before runtime | architecture doctrine |
| Phase B | W12–W17 | Family/scope, target capabilities, compatibility, lifecycle, publication, registry versioning | descriptor / governance foundation |
| Phase C | W18–W20 | Realization contract, runtime readiness, runtime plan | pre-execution |
| Phase D | W21–W24 | Realizer/session/execution-plan/engine skeleton | interface / skeleton |
| Phase E | W25–W29 | Ecosystem target descriptors and system-wide integration skeleton | integration descriptor |
| Phase F | W30–W34 | Persistence boundary, audit export boundary, runtime failure/recovery, compliance suite, production readiness gate | hardening boundary / gate |

## 5. Detailed Wave Index

| Wave | Package | Primary Responsibility | Phase | Maturity | Explicit Non-Ownership |
|---|---|---|---|---|---|
| W01 | Primitive Policy Identity | id/family/version/scope/source/provenance/status/result primitives | Foundation | primitive | no policy aggregate, no registry, no runtime |
| W02 | Policy Clauses | local semantic clause units and sets | Foundation | foundation | no expression evaluator, no runtime behavior |
| W03 | Safe Point And Replacement | safe points, boundaries, eligibility, replacement plans | Foundation | foundation | no hot-swap engine, no synchronization |
| W04 | Policy Lifecycle | lifecycle, activation/suspension/retirement markers and views | Foundation | foundation | no lifecycle authority engine |
| W05 | Policy Observation And Audit | observation, evidence, trace, audit carriers | Foundation | foundation | no exporter, no persistence, no telemetry backend |
| W06 | Realization Binding And Target Kind | realization and target-kind descriptors | Foundation | descriptor | no realizer, no target ownership, no invocation |
| W07 | Policy Graph Structure | structural graph, nodes, edges, invariants | Foundation | structural | no traversal engine |
| W08 | Traversal Foundation Types | sequence channels, transitions, relations, cursor/readiness vocabulary | Foundation | vocabulary | no traversal runtime |
| W09 | TPolicy Aggregate And View | first aggregate over prior policy foundations | Foundation | aggregate | no executor, no target ownership, no orchestrator |
| W10 | Policy Assignment Basics | non-executing policy-to-target relation | Foundation extension | relation | no activation runtime, no target handle |
| W11 | Policy Registry Basics | bounded catalog-facing registry basics | Foundation extension | catalog-facing | no storage engine, no service locator |
| W12 | Policy Family And Scope | family taxonomy, scope path, family profile/view | Phase B | descriptor | no target capability or compatibility evaluator |
| W13 | Target Capability Contracts | target capability id/kind/descriptor/set/report | Phase B | descriptor | no method call surface, no target invocation |
| W14 | Family Target Compatibility Matrix | family-target rule/report/evaluator/matrix | Phase B | evaluator descriptor | no assignment activation |
| W15 | Assignment Lifecycle And Conflict | assignment states, transitions, conflicts, resolutions | Phase B | lifecycle descriptor | no runtime assignment engine |
| W16 | Policy Source And Publication | source descriptor, publication state/record, lineage | Phase B | publication descriptor | no parser, no storage |
| W17 | Registry Versioning And Publication View | version index, snapshots, versioned lookup, publication view | Phase B | registry descriptor | no persistent registry |
| W18 | Realization Contract Foundation | realization contract/context/request/preconditions/failure/trace | Phase C | contract foundation | no realizer execution |
| W19 | Runtime Readiness Model | readiness state/gates/issues/admission/report/evaluator | Phase C | pre-execution evaluator | no target invocation |
| W20 | Policy Runtime Plan | runtime plan id/status/issues/steps/view | Phase C | pre-execution plan | no execution engine |
| W21 | PolicyRealizer Interface And Result Model | realizer id/status/capability/result/view/interface | Phase D | interface | no executor, no target mutation |
| W22 | PolicyRealizationSession | realization session lifecycle around request/contract/plan/realizer | Phase D | session skeleton | no execution |
| W23 | PolicyRealizationExecutionPlan | execution-plan carriers, guards, steps, report | Phase D | pre-execution plan | no executor |
| W24 | PolicyRealizationEngine Skeleton | engine identity/config/status/result/view/skeleton | Phase D | skeleton | no production runtime engine |
| W25 | LogLevelApi Policy Targets | log-level API target descriptors/capability/rules/report | Phase E | integration descriptor | no log-level API behavior |
| W26 | MaterialCirculation Policy Targets | material circulation target descriptors/capability/rules/report | Phase E | integration descriptor | no slots/rounds/dispatcher mutation |
| W27 | CommunicationContext Policy Surface | communication context policy surface descriptors/capability/rules/report | Phase E | integration descriptor | no channel/binding/session/protocol execution |
| W28 | Addon Policy Targets | add-on target descriptors/capability/rules/report | Phase E | integration descriptor | no add-on runtime behavior |
| W29 | System Wide Policy Integration Skeleton | system-wide target set, integration plan/report/skeleton | Phase E | integration skeleton | no runtime integration |
| W30 | Policy Persistence Boundary | persistence boundary ids/media/refs/admission/report | Phase F | boundary | no storage engine, no IO |
| W31 | Policy Audit Export Boundary | audit export boundary ids/media/refs/admission/report | Phase F | boundary | no audit sink/exporter |
| W32 | Policy Runtime Failure And Recovery | failure kinds/severity/records/recovery plan/report/quarantine | Phase F | failure/recovery descriptor | no automatic recovery |
| W33 | Policy Test And Compliance Suite | compliance assertion/test case/catalog/suite/report | Phase F | test/compliance descriptor | no test runner/CI |
| W34 | Production Readiness Gate | production readiness gate, criteria, evidence, report | Phase F | gate | no deployment/runtime execution |

## 6. Architecture Documents Index

| Document | Responsibility |
|---|---|
| ARCH-001 | Policy family taxonomy and scope model |
| ARCH-002 | Target kind and capability model |
| ARCH-003 | Policy family compatibility matrix |
| ARCH-004 | Assignment lifecycle and conflict model |
| ARCH-005 | Policy authority and governance roles |
| ARCH-006 | Source publication and registry versioning |
| ARCH-007 | Realization contracts and runtime readiness |
| ARCH-008 | Compliance and validation matrix |

## 7. Dependency Narrative

The delivery order intentionally moves from semantic constitution to integration and production hardening:

```text
identity / clauses / replacement / lifecycle / observation
→ realization descriptors / graph / traversal vocabulary
→ TPolicy aggregate
→ assignment and registry basics
→ family and target capability descriptors
→ compatibility and assignment lifecycle
→ source/publication and registry versioning
→ realization contract and runtime readiness
→ realizer/session/plan/engine skeleton
→ ecosystem targets
→ hardening boundaries and gates
```

## 8. Update Rule

Every future EG-POL wave must add or update one row in this document and, when needed, update the wave dependency diagram.
