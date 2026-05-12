# EG-POL-CAT-007 — Readiness And Maturity Catalog

## 1. Document Control

| Field | Value |
|---|---|
| Document Title | Readiness And Maturity Catalog |
| File Name | `EG-POL-CAT-007_Readiness_And_Maturity_Catalog.md` |
| Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| Scope | Readiness and maturity classification for EG-POL W01–W34 |
| Status | Catalog Draft V1 |

## 2. Purpose

This document classifies the maturity of the policy subsystem layers delivered so far.

It prevents a common architectural mistake: confusing foundation, descriptor, boundary, skeleton, or gate artifacts with production runtime behavior.

## 3. Maturity Vocabulary

| Maturity | Meaning | Runtime Meaning |
|---|---|---|
| primitive | atomic identity/status/kind/result vocabulary | not runtime |
| foundation | structural or semantic building block | not runtime |
| descriptor | describes a relation, target, capability, or condition | not runtime |
| evaluator descriptor | can model evaluation/reporting but does not enforce runtime mutation | pre-runtime only |
| boundary | defines where integration may happen | not implementation of the boundary mechanism |
| skeleton | shapes an engine/session/plan without production execution | not production runtime |
| gate | decides readiness/admission in a descriptive form | does not deploy or execute |
| runtime-ready | eligible for runtime planning once all real checks exist | not necessarily executed |
| production-ready | eligible for production use after implementation, tests, evidence, and operations | not implied by current catalog |

## 4. Current Readiness Classification

| Layer | Waves | Current Maturity | Reason |
|---|---:|---|---|
| Policy object constitution | W01–W09 | foundation / aggregate | Defines what a policy is; does not execute it |
| Assignment and registry basics | W10–W11 | relation / catalog-facing foundation | Assignment and registry are modeled, not live-governance engines |
| Family and scope | W12 | descriptor | Describes family/scope taxonomy |
| Target capabilities | W13 | descriptor | Describes target capability contracts, not target methods |
| Compatibility matrix | W14 | evaluator descriptor | Provides matrix and evaluator shape; no runtime assignment |
| Assignment lifecycle/conflict | W15 | lifecycle descriptor | Defines lifecycle/conflict carriers; no activation engine |
| Source/publication | W16 | publication descriptor | No parser or publication workflow engine |
| Registry versioning/publication view | W17 | registry descriptor | No persistent registry |
| Realization contract | W18 | contract foundation | No realization execution |
| Runtime readiness | W19 | pre-execution gate/evaluator | No runtime mutation |
| Runtime plan | W20 | pre-execution plan | No executor |
| Realizer interface | W21 | interface | No concrete realizer implementation |
| Realization session | W22 | session skeleton | No live session engine |
| Execution plan | W23 | pre-execution plan | No executor |
| Realization engine | W24 | skeleton | No production execution engine |
| LogLevelApi targets | W25 | integration descriptor | No log-level runtime behavior |
| MaterialCirculation targets | W26 | integration descriptor | No slot/round/dispatcher mutation |
| CommunicationContext surface | W27 | integration descriptor | No bridge/session/protocol execution |
| Addon targets | W28 | integration descriptor | No add-on runtime behavior |
| System-wide integration | W29 | integration skeleton | No runtime integration execution |
| Persistence boundary | W30 | boundary | No storage engine |
| Audit export boundary | W31 | boundary | No exporter |
| Runtime failure/recovery | W32 | failure/recovery descriptor | No automatic recovery |
| Test/compliance suite | W33 | test/compliance descriptor | No test runner |
| Production readiness gate | W34 | gate | No deployment or production execution |

## 5. Readiness Ladder

The current subsystem has reached:

```text
Semantic completeness for policy governance vocabulary
+ descriptor completeness for target compatibility and readiness
+ skeleton completeness for realization orchestration
+ boundary/gate completeness for production hardening
```

It has not reached:

```text
runtime enforcement
runtime target invocation
automatic recovery
persistent storage
actual audit export
production deployment
```

## 6. What Production-Ready Would Require Later

A future production-ready policy subsystem would require at least:

1. concrete authority model implementation,
2. concrete source adapter implementation,
3. persistent registry or policy store adapter,
4. assignment activation engine,
5. real compatibility evaluator implementation wired to target descriptors,
6. runtime readiness evaluator with real environment evidence,
7. concrete realizer implementations per target family,
8. controlled executor or invocation surface,
9. audit export implementation,
10. compliance runner and CI integration,
11. operational playbooks and failure drills.

## 7. Anti-Collapse Summary

```text
foundation ≠ runtime
boundary ≠ adapter
descriptor ≠ implementation
skeleton ≠ engine
readiness gate ≠ execution
compliance report ≠ remediation
production readiness gate ≠ deployment
```
