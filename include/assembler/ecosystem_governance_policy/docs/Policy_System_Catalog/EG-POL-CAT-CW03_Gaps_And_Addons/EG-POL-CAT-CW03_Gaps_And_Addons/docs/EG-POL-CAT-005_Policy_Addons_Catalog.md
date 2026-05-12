# EG-POL-CAT-005 — Policy Add-ons Catalog

## 1. Document Control

| Field | Value |
|---|---|
| Document Title | Policy Add-ons Catalog |
| File Name | `EG-POL-CAT-005_Policy_Addons_Catalog.md` |
| Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| Catalog Wave | EG-POL-CAT-CW03_Gaps_And_Addons |
| Scope | Optional add-ons for the EG-POL policy subsystem only |
| Status | Catalog Draft V1 |
| Primary Purpose | Identify policy subsystem extension points, allowed ownership, forbidden ownership, required contracts, and future implementation candidates |

---

## 2. Purpose

This document catalogs possible add-ons for the policy subsystem after the completion of the current EG-POL waves.

An add-on is an optional extension module that plugs into a defined boundary or descriptor surface without redefining the core policy subsystem.

This document does not implement add-ons. It defines what kinds of add-ons may exist and what constraints apply.

---

## 3. Add-on Classification

| Add-on Family | Purpose |
|---|---|
| Policy Source Add-ons | Bring policy definitions from external or generated sources |
| Policy Persistence Add-ons | Persist policy objects, registry views, snapshots, or reports |
| Policy Audit Export Add-ons | Export observation/audit data to approved external forms |
| Policy Compliance Add-ons | Run policy compliance checks outside the core type system |
| Policy Realization Add-ons | Provide concrete domain-specific realizers after readiness gates |
| Policy Visualization Add-ons | Export graphs, matrices, readiness reports, or catalog diagrams |
| Policy Diagnostics Add-ons | Correlate policy issues with system diagnostics |
| Policy Tooling Add-ons | Provide developer tooling, report generation, or static analysis |

---

## 4. Policy Source Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| YAML Policy Source Adapter | `source_publication` | YAML parsing into source descriptors | Policy semantics, assignment, realization | source descriptor, publication precheck, provenance | Medium |
| JSON Policy Source Adapter | `source_publication` | JSON parsing into source descriptors | Policy validation authority | source descriptor, schema version, provenance | Medium |
| C++ Constexpr Policy Source Adapter | `source_publication` | Compile-time source declarations | Runtime mutation | policy identity, source descriptor | Low |
| Generated Policy Source Adapter | `source_publication` | Generated source metadata | Governance approval | provenance, generator id, source trust | Medium |
| Migration Source Adapter | `source_publication` | Legacy config import | Silent publication | migration provenance, compatibility report | High |

---

## 5. Policy Persistence Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| File Snapshot Persistence Adapter | `policy_persistence` | Writing policy snapshots to files | Policy registry authority | persistence boundary, snapshot ref, admission report | Medium |
| Append-only Journal Adapter | `policy_persistence` | Append-only policy event records | Recovery execution | record ref, snapshot ref, failure report | Medium |
| SQLite Policy Catalog Adapter | `policy_persistence` | Local embedded DB persistence | Runtime service locator | persistence boundary, registry view export | High |
| Embedded KV Policy Adapter | `policy_persistence` | Key-value policy records | Target discovery | record ref, lookup key mapping | High |
| In-memory Snapshot Export Adapter | `policy_persistence` | Memory-local export view | Durable persistence claim | snapshot ref, export boundary | Low |

---

## 6. Policy Audit Export Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| JSON Audit Exporter | `policy_audit_export` | Structured JSON audit export | Audit truth source | audit export boundary, record ref | Medium |
| File Audit Exporter | `policy_audit_export` | File-based audit records | Persistence engine | export boundary, medium kind | Medium |
| Console Debug Audit Exporter | `policy_audit_export` | Debug output | Production audit compliance | export admission, severity mapping | Low |
| OpenTelemetry Audit Exporter | `policy_audit_export` | OTEL event/span export | Policy observation ownership | audit export boundary, trace ref | High |
| Compliance Report Exporter | `policy_test_compliance` | Exporting compliance reports | Compliance evaluation itself | suite report, export boundary | Medium |

---

## 7. Policy Compliance Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| Static Compliance Runner | `policy_test_compliance` | Offline compliance checks | Runtime enforcement | compliance suite, assertions | Medium |
| CI Compliance Runner | `policy_test_compliance` | CI execution of compliance tests | Policy source authority | suite report, outcome mapping | Medium |
| Negative Test Catalog Runner | `policy_test_compliance` | Anti-collapse test catalog execution | Production deployment | negative catalog, severity mapping | Medium |
| Readiness Report Validator | `runtime_readiness` | Validating readiness reports | Readiness authority | readiness report, compliance dimension | Medium |
| Production Gate Preflight Tool | `policy_production_readiness` | Preflight gate checks | Deployment | readiness gate, evidence refs | High |

---

## 8. Policy Realization Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| LogLevelApi Policy Realizer | `policy_realizer` + log-level targets | Applying policies to log-level target surfaces | Log-level API internal ownership | target capability, runtime readiness, contract | High |
| MaterialCirculation Policy Realizer | `policy_realizer` + material circulation targets | Policy application plan for circulation targets | Slot/round runtime mutation without gates | capability profile, readiness, execution guard | High |
| CommunicationContext Policy Realizer | `policy_realizer` + communication surfaces | Applying policy through communication context surface contracts | Bridge execution or endpoint invocation | compatibility, session, readiness, guard | High |
| Addon Boundary Policy Realizer | `policy_realizer` + addon targets | Add-on policy adaptation | Final external receiver semantics | addon target descriptor, audit evidence | High |
| System-Wide Policy Realizer Skeleton | `system_wide` target set | Multi-domain realization plan composition | Direct target mutation | integration skeleton, runtime plan | High |

---

## 9. Policy Visualization Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| Policy Graph Exporter | `policy_graph` | Graph export to Mermaid/Graphviz | Graph semantics | graph view, invariant report | Low |
| Compatibility Matrix Visualizer | `compatibility_matrix` | Matrix visualization | Compatibility evaluation authority | matrix view, report | Low |
| Readiness Ladder Visualizer | `runtime_readiness` | Readiness state diagrams | Gate decisions | readiness report | Low |
| Wave Dependency Graph Exporter | catalog tooling | Dependency diagram generation | Wave definitions | catalog manifest | Low |
| Policy Add-on Map Exporter | catalog tooling | Add-on map diagram | Add-on implementation | add-on catalog | Low |

---

## 10. Policy Diagnostics Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| Policy Issue Aggregator | policy reports | Aggregating issues across reports | Root cause authority | issue records, severity | Medium |
| Policy Trace Correlator | observation/audit | Correlation with trace refs | External telemetry truth | trace refs, audit markers | Medium |
| Runtime Failure Dashboard Adapter | failure/recovery | Present failure/recovery state | Recovery execution | failure record, recovery report | Medium |
| Production Readiness Dashboard Adapter | production readiness | Present readiness status | Deployment approval | readiness gate/report | Medium |

---

## 11. Tooling Add-ons

| Add-on | Extension Point | May Own | Must Not Own | Required Contracts | Risk |
|---|---|---|---|---|---|
| Markdown Report Generator | catalog / reports | Human-readable docs | Source of truth | report views | Low |
| Manifest Linter | manifests | Manifest consistency checks | Runtime validation | manifest schema | Low |
| Header Doctrine Checker | headers | Checking comment header conformance | Code semantics | file header doctrine | Low |
| Wave Pack Verifier | wave packages | Package structure checks | Compile toolchain | manifest, tree, compile check | Medium |

---

## 12. Add-on Boundary Rules

The following rules apply to all policy add-ons:

```text
Add-on ≠ core policy type system
Add-on ≠ policy registry authority
Add-on ≠ assignment activation authority
Add-on ≠ target ownership
Add-on ≠ runtime executor unless explicitly designed as a realizer and gated
Add-on ≠ production deployment authority
```

---

## 13. Suggested Future Add-on Waves

| Candidate Wave | Purpose |
|---|---|
| `EG-POL-ADDON-W01_Source_Adapters` | YAML/JSON/constexpr/generated source adapters |
| `EG-POL-ADDON-W02_Persistence_Adapters` | File, SQLite, journal, KV persistence adapters |
| `EG-POL-ADDON-W03_Audit_Exporters` | JSON/file/console/OTEL audit export adapters |
| `EG-POL-ADDON-W04_Compliance_Runners` | Static/CI/negative-test runners |
| `EG-POL-ADDON-W05_Domain_Realizer_Adapters` | Realizers for log_level_api, material_circulation, communication_context, addons |
| `EG-POL-ADDON-W06_Visualization_Exports` | Graph, matrix, readiness, and catalog diagram exports |

---

## 14. Catalog Conclusion

The policy subsystem is now ready to define optional add-ons, but only where stable boundaries exist. The safest near-term add-ons are visualization, report generation, manifest linting, and static compliance runners. The highest-risk add-ons are concrete realizers, persistence engines, and audit exporters because they may accidentally cross into target invocation, storage authority, or telemetry ownership.
