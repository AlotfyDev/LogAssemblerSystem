# LOGAPI-CAT-008 — Gap Matrix And Logical Extensions

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| LOGAPI-CAT-008-DOC-001 | Document Title | Gap Matrix And Logical Extensions |
| LOGAPI-CAT-008-DOC-002 | File Name | `LOGAPI-CAT-008_Gap_Matrix_And_Logical_Extensions.md` |
| LOGAPI-CAT-008-DOC-003 | Documentation Pack | LOGAPI-CAT — Log Level API Domain Catalog |
| LOGAPI-CAT-008-DOC-004 | Domain | `log_level_api` |
| LOGAPI-CAT-008-DOC-005 | Scope Level | Gap matrix, deferred decisions, logical extensions, priority roadmap |
| LOGAPI-CAT-008-DOC-006 | Status | Gap Matrix Draft |
| LOGAPI-CAT-008-DOC-007 | Related Implementation Waves | `LOGAPI-W01` through `LOGAPI-W34` |
| LOGAPI-CAT-008-DOC-008 | Boundary Rule | Gaps and extensions are limited to Log Level API. Circulation internals, bridge runtime, receiver semantics, and policy runtime are out of scope |
| LOGAPI-CAT-008-DOC-009 | Diagram Index | `LOGAPI-CAT-008_gap_priority_matrix.mmd`, `LOGAPI-CAT-008_extension_roadmap.mmd` |

---

## 2. Purpose

This document identifies:

```text
what is complete,
what is only contract/smoke-ready,
what is deferred,
what remains a gap,
and which logical extensions are valid inside the Log Level API boundary.
```

It does not propose Circulation implementation work.

It does not propose Bridge Orchestrator implementation work.

It does not restart the Policy Assignment layer unless a true governable target behavior appears.

---

## 3. Completion Snapshot

The current Log Level API domain has completed these major capability areas:

```text
configuration spine
content profile/schema paths
validator contract/result carrier
metadata struct/values/profile/default packs
timestamp stabilizer/config/calibration/optional policy-sensitive descriptors
content-only API facade
envelope carrier/final shape/readiness exposure
assembler families
communication binding/handoff contract
default JSON schemas and parsers
default C-style struct schemas and parsers
MT5 schemas and single-structure parsers
MT5 container/batch parsing
public API surface
diagnostics
test compliance
production readiness gate
```

This is a strong **contract-ready and smoke-ready** Log Level API domain.

However, full production-runtime readiness still has several practical gaps.

---

## 4. Gap Severity Model

| Priority | Meaning |
|---:|---|
| P0 | Blocks production runtime use of Log Level API |
| P1 | Important for stable production integration but not blocking for isolated smoke/contract readiness |
| P2 | Useful hardening or developer-experience extension |
| P3 | Optional future enhancement |

---

## 5. Current Gap Matrix

| Gap ID | Area | Current State | Gap | Priority | Recommended Extension |
|---|---|---|---|---:|---|
| LOGAPI-GAP-001 | Public API orchestration | W27 defines public API surface and opaque skeleton | Public API does not yet orchestrate full path from JSON/C-struct/MT5 input to parser + metadata + timestamp + envelope + handoff | P0 | `LOGAPI-EXT_Public_Api_Full_Flow_Orchestrator` |
| LOGAPI-GAP-002 | Specialized parser execution from Public API | Parsers exist W14–W18 and container parsers W32–W34 | Public API skeleton only executes OpaqueNoParse directly | P0 | Bind public call variants to dedicated parser entrypoints |
| LOGAPI-GAP-003 | Envelope assembler final-shape alignment | W08 assembler families and W23 final envelope exist | W08 outputs W07 envelope, not W23 final envelope shape | P0 | Add final envelope assembler bridge or update assembler output target |
| LOGAPI-GAP-004 | Batch-to-envelope materialization | W31 defines batch strategies; W32–W34 parse containers | No implementation maps parsed batches into `BatchAsSingleEnvelope` or `ElementAsEnvelopeStream` | P1 | `LOGAPI-EXT_Batch_Envelope_Materialization` |
| LOGAPI-GAP-005 | JSON parser robustness | W14 has minimal default field extractor | Not a production JSON parser; handles simple known fields only | P1 | Replace/internalize production JSON parser strategy while preserving dedicated parser types |
| LOGAPI-GAP-006 | C-style binary parsing depth | W15 reads integer/default fields for default primitive layout | Float/char buffer/presence-flag semantics are deferred | P1 | Complete primitive binary read helpers and presence model |
| LOGAPI-GAP-007 | MT5 direct runtime binding | W16–W18 use C++ input views mirroring MT5 structures | No direct MQL5 runtime/memory binding or generated interop code | P1 | MT5 adapter/binding layer outside core schema/parser descriptors |
| LOGAPI-GAP-008 | MT5 binary ABI layout | MT5 schemas describe fields, not binary ABI layout | No explicit binary layout for MT5 structures | P1 | Add optional MT5 binary layout descriptors if raw binary input is required |
| LOGAPI-GAP-009 | External schema/parser registration | Core supports parser binding conceptually | No dedicated admin port for imported schema + custom parser registration | P1 | `LOGAPI-EXT_External_Schema_And_Parser_Registration_Port` |
| LOGAPI-GAP-010 | Concrete constraint validators | Validator contract exists; validators deferred | No optional constraint validators for parsed views | P2 | Add optional constraint validators only when needed |
| LOGAPI-GAP-011 | Validation action model | Validation result slot exists | No model for action based on validation result | P2 | Future user/policy action model, not validator responsibility |
| LOGAPI-GAP-012 | Metadata persistence | Metadata profile registry exists in-memory | No persistent metadata profile store | P2 | Metadata config persistence boundary |
| LOGAPI-GAP-013 | Timestamp clock acquisition | W21 models clock sources/samples | No actual OS/system clock adapter | P1 | Clock adapter layer with injected sample provider |
| LOGAPI-GAP-014 | Calendar conversion | Timestamp config has calendar kinds | No calendar conversion implementation | P2 | Optional calendar conversion add-on |
| LOGAPI-GAP-015 | Diagnostics mapping | W28 defines failure taxonomy | Not all W01–W34 issue codes are mapped to W28 failure kinds | P1 | Diagnostic mapping catalog |
| LOGAPI-GAP-016 | Test compliance execution | W29 defines compliance descriptors | No external test runner/CI integration | P2 | CI/test runner adapter outside catalog |
| LOGAPI-GAP-017 | Production readiness evidence automation | W30 uses evidence labels | Evidence is manually represented, not generated from manifests | P2 | Manifest-driven readiness evidence generator |
| LOGAPI-GAP-018 | Memory/lifetime model | Many refs are non-owning views | No production lifetime/ownership doctrine for payload refs and parsed refs | P0 | `LOGAPI-EXT_Content_Ref_Lifetime_And_Ownership_Model` |
| LOGAPI-GAP-019 | Performance benchmark suite | No benchmark layer | Hot-path claims are not benchmarked | P1 | Parser/envelope/handoff benchmark suite |
| LOGAPI-GAP-020 | Threading / concurrency model | Mostly value types/smoke skeletons | No production concurrency rules for public API calls, metadata updates, timestamp samples | P2 | Concurrency and update visibility doctrine |
| LOGAPI-GAP-021 | Policy assignment layer | Intentionally deferred | No functional object currently requires policy-governed replacement | Deferred | Revisit only when governable runtime behavior appears |
| LOGAPI-GAP-022 | Circulation real admission | W25/W26 are contract/smoke only | No real circulation implementation | Out of scope | Belongs to Circulation domain |
| LOGAPI-GAP-023 | Bridge orchestration | LogAPI handoff surface exists | No bridge session/protocol work here | Out of scope | Belongs to ASCC/Bridge domain |
| LOGAPI-GAP-024 | External receivers | Not represented | No database/telemetry/external receiver adapters | Out of scope | Belongs to add-ons/external receiver domains |

---

## 6. Priority Roadmap

## 6.1 P0 — Production Runtime Blockers

These should be addressed before declaring Log Level API production-runtime-ready.

```text
LOGAPI-GAP-001 Public API full orchestration
LOGAPI-GAP-002 Specialized parser execution from Public API
LOGAPI-GAP-003 Envelope assembler final-shape alignment
LOGAPI-GAP-018 Content reference lifetime and ownership model
```

Recommended work:

```text
LOGAPI-EXT-W01_Public_Api_Full_Flow_Orchestrator
LOGAPI-EXT-W02_Final_Envelope_Assembler_Bridge
LOGAPI-EXT-W03_Content_Ref_Lifetime_And_Ownership_Model
```

## 6.2 P1 — Production Integration Stabilizers

```text
LOGAPI-GAP-004 Batch-to-envelope materialization
LOGAPI-GAP-005 JSON parser robustness
LOGAPI-GAP-006 C-style binary parsing depth
LOGAPI-GAP-007 MT5 direct runtime binding
LOGAPI-GAP-008 MT5 binary ABI layout
LOGAPI-GAP-009 External schema/parser registration
LOGAPI-GAP-013 Timestamp clock acquisition
LOGAPI-GAP-015 Diagnostics mapping
LOGAPI-GAP-019 Performance benchmark suite
```

## 6.3 P2 — Hardening / Developer Experience

```text
LOGAPI-GAP-010 Optional constraint validators
LOGAPI-GAP-011 Validation action model
LOGAPI-GAP-012 Metadata persistence
LOGAPI-GAP-014 Calendar conversion
LOGAPI-GAP-016 Test runner/CI integration
LOGAPI-GAP-017 Readiness evidence generator
LOGAPI-GAP-020 Concurrency/update visibility doctrine
```

## 6.4 Deferred

```text
LOGAPI-GAP-021 Policy assignment layer
```

The policy assignment layer remains deferred until a concrete Log Level API functional object requires policy-governed runtime replacement at a declared safe point.

---

## 7. Logical Extension Roadmap

## 7.1 Extension Track A — Public API Orchestration

Purpose:

```text
Turn the existing content-only public API surface into a complete production execution path.
```

Candidate waves:

```text
LOGAPI-EXT-W01_Public_Api_Full_Flow_Orchestrator
LOGAPI-EXT-W02_Public_Api_Specialized_Parser_Routing_By_Profile
LOGAPI-EXT-W03_Public_Api_Result_Error_Taxonomy
```

Boundary:

```text
No per-call config.
No parser discovery in hot path.
Routing is via resolved profile, not runtime inspection.
```

## 7.2 Extension Track B — Final Envelope Assembly Alignment

Purpose:

```text
Bridge W08 assembler families to W23 final envelope shape.
```

Candidate waves:

```text
LOGAPI-EXT-W04_Final_Envelope_Assembler_Bridge
LOGAPI-EXT-W05_Validation_Result_Slot_Assembly_Model
```

Boundary:

```text
Validation result remains evidence.
Payload action remains user/policy concern.
```

## 7.3 Extension Track C — Batch Envelope Materialization

Purpose:

```text
Make W31 batch strategies actionable.
```

Candidate waves:

```text
LOGAPI-EXT-W06_Batch_As_Single_Envelope_Materializer
LOGAPI-EXT-W07_Element_As_Envelope_Stream_Skeleton
```

Boundary:

```text
No circulation stream execution.
No receiver lifecycle.
```

## 7.4 Extension Track D — External Schema / Parser Registration

Purpose:

```text
Support user-defined content schemas and dedicated parsers.
```

Candidate waves:

```text
LOGAPI-EXT-W08_External_Content_Schema_Registration_Port
LOGAPI-EXT-W09_External_Content_Parser_Registration_Port
LOGAPI-EXT-W10_External_Profile_Binding_Registry
```

Boundary:

```text
Admin/configuration surface only.
No hot-path discovery.
No security/threat model in this layer.
```

## 7.5 Extension Track E — Parser Production Hardening

Purpose:

```text
Strengthen concrete parsers while preserving dedicated parser types.
```

Candidate waves:

```text
LOGAPI-EXT-W11_JSON_Parser_Production_Backend
LOGAPI-EXT-W12_CStruct_Primitive_Binary_Read_Completion
LOGAPI-EXT-W13_MT5_Runtime_Binding_Adapter
LOGAPI-EXT-W14_MT5_Binary_Layout_Descriptors
```

Boundary:

```text
No generic parser dispatch.
No MT5 trade execution.
No Circulation internals.
```

## 7.6 Extension Track F — Observability / Benchmarking

Purpose:

```text
Make hot-path claims measurable and failure reporting consistent.
```

Candidate waves:

```text
LOGAPI-EXT-W15_Diagnostic_Code_Mapping_Catalog
LOGAPI-EXT-W16_Hot_Path_Benchmark_Suite
LOGAPI-EXT-W17_Readiness_Evidence_Generator
```

Boundary:

```text
No telemetry backend yet.
No production monitoring runtime.
```

---

## 8. Non-Scope Matrix

These are not Log Level API extensions:

| Item | Reason |
|---|---|
| Circulation placement implementation | belongs to Circulation domain |
| Circulation queues / slots / waiting lists | belongs to Circulation domain |
| Bridge sessions/protocols | belongs to ASCC / Bridge domain |
| Database writer | belongs to add-ons / external receiver domain |
| Telemetry exporter | belongs to add-ons / observability domain |
| Policy object lifecycle implementation | belongs to Policy System |
| TPolicyObjectHost / PolicyAssigner integration | deferred until a real governable target appears |

---

## 9. Recommended Next Step

The most valuable next work inside Log Level API is:

```text
LOGAPI-EXT-W01_Public_Api_Full_Flow_Orchestrator
```

because it closes the biggest practical gap:

```text
The pieces exist,
but the public API does not yet orchestrate the full production flow.
```

Second priority:

```text
LOGAPI-EXT-W02_Final_Envelope_Assembler_Bridge
```

because W08 and W23 currently represent different envelope generations.

---

## 10. Acceptance Criteria

This gap matrix is accepted if it:

1. separates real gaps from out-of-scope items,
2. does not move Circulation work into Log Level API,
3. does not prematurely start policy assignment,
4. identifies P0 blockers,
5. gives logical extension tracks,
6. preserves hot-path and configuration-first rules.
