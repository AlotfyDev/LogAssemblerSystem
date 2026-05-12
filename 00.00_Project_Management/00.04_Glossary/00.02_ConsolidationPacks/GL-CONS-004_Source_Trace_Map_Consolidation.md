
# GL-CONS-003 — Source Trace Index Consolidation

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONS-003-DOC-001 | Document Title | GL-CONS-003_SourceTrace_Index_Consolidation.md |
| GL-CONS-003-DOC-002 | Formal Version | Formal Draft V1 |
| GL-CONS-003-DOC-003 | Project | Assembler System |
| GL-CONS-003-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-CONS-003-DOC-005 | Document Type | Consolidated Index / Source Trace Control Pack |
| GL-CONS-003-DOC-006 | Language | English |
| GL-CONS-003-DOC-007 | Status | Formal Draft V1 |
| GL-CONS-003-DOC-008 | Consolidates | Source trace rules and source dependencies from GL-CONT-000 through GL-CONT-010 |
| GL-CONS-003-DOC-009 | Scope | Source classes, trace levels, source-to-pack mapping, source-to-term mapping readiness, evidence status rules, future database trace readiness |
| GL-CONS-003-DOC-010 | Excluded From This Pack | Full glossary entry population, full source quotation extraction, final JSON schema, final database schema, final PostgreSQL derivation |
| GL-CONS-003-DOC-011 | Enables | Source trace matrix, glossary QA, coverage validation, source-backed JSON/CSV population, future DB-backed traceability |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack consolidates the source trace model for the Assembler System glossary workstream.

It answers the question:

```text
Which documents, packs, decisions, rules, and derived consolidation layers
serve as source authorities for glossary terms, anti-collapse rules,
ownership boundaries, contract families, responsibility chains, and future
implementation derivation terms?
````

This pack is not a master glossary.

It is not a source quotation archive.

It is a source trace index.

It defines how source authority should be referenced, classified, preserved, and later represented in validation, JSON, CSV, or database form.

### 2.2 Why This Pack Exists

The glossary workstream already contains multiple layers of content:

1. foundational project documents,
2. glossary governance packs,
3. content definition packs,
4. consolidation packs,
5. anti-collapse indexes,
6. future schema and database derivation candidates.

Without a consolidated source trace index, later artifacts may lose the distinction between:

1. direct source,
2. derived source,
3. user decision,
4. consolidation authority,
5. validation rule,
6. future derivation readiness,
7. implementation-facing interpretation.

This pack prevents source ambiguity.

### 2.3 Core Function

|            Record ID | Function               | Description                                                  |
| -------------------: | ---------------------- | ------------------------------------------------------------ |
| GL-CONS-003-FUNC-001 | Source Authority Index | Identifies authoritative source layers for glossary meaning  |
| GL-CONS-003-FUNC-002 | Trace Classification   | Defines how trace types should be labeled                    |
| GL-CONS-003-FUNC-003 | Pack-to-Source Map     | Connects each GL-CONT pack to its source authority basis     |
| GL-CONS-003-FUNC-004 | Evidence Support       | Preserves evidence status for canonical and derived terms    |
| GL-CONS-003-FUNC-005 | Validation Support     | Enables source-backed review and coverage validation         |
| GL-CONS-003-FUNC-006 | Database Readiness     | Prepares source traces for future relational or JSON storage |

---

## 3. Consolidation Principle

### 3.1 Primary Principle

```text
Every canonical glossary term, anti-collapse rule, contract family,
responsibility-chain element, authority exclusion, and future derivation term
should preserve a visible source trace.
```

### 3.2 Trace Integrity Rule

```text
A source trace is not decorative citation.
It is the evidence path that explains why a term, rule, boundary,
or derivation constraint exists.
```

### 3.3 No-Orphan-Term Rule

```text
No canonical glossary term should remain source-orphaned once the consolidation
and validation phases begin.
```

A term may initially be marked as a low-detail seed.

However, even a seed term should record at least one of:

1. source pack,
2. source document,
3. user decision,
4. derived-from relation,
5. future validation requirement.

---

## 4. Source Trace Record Model

Each source trace record should be interpretable as a future database row.

| Field             | Meaning                                                                                                 |
| ----------------- | ------------------------------------------------------------------------------------------------------- |
| `trace_id`        | Stable identifier for the trace record                                                                  |
| `target_id`       | Term ID, rule ID, pack ID, goal ID, or artifact ID being traced                                         |
| `target_type`     | term / rule / pack / goal / doctrine / relation / derivation_item                                       |
| `source_id`       | Source document, pack, goal, rule, or decision identifier                                               |
| `source_type`     | foundational_document / glossary_pack / consolidation_pack / system_goal / user_decision / derived_rule |
| `trace_relation`  | direct / derived / supports / constrains / aliases / consolidates / enables                             |
| `evidence_status` | direct / derived / user_decision / legacy_alias / inferred / needs_validation                           |
| `source_summary`  | Short description of what the source contributes                                                        |
| `validation_use`  | How this trace should be used in review or future validators                                            |
| `status`          | active / pending / superseded / deprecated                                                              |

---

## 5. Source Type Model

|             Record ID | Source Type              | Meaning                                                                                      |
| --------------------: | ------------------------ | -------------------------------------------------------------------------------------------- |
| GL-CONS-003-STYPE-001 | Foundational Document    | A project-level document defining system identity, scope, goals, or roadmap                  |
| GL-CONS-003-STYPE-002 | Glossary Governance Pack | A pack defining glossary entry rules, source rules, maturity, and anti-collapse requirements |
| GL-CONS-003-STYPE-003 | Glossary Content Pack    | A pack defining canonical terms in a specific semantic area                                  |
| GL-CONS-003-STYPE-004 | Consolidation Pack       | A pack that merges, normalizes, indexes, or governs multiple prior packs                     |
| GL-CONS-003-STYPE-005 | System Goal              | A goal record defining required system behavior or constraint                                |
| GL-CONS-003-STYPE-006 | Anti-Collapse Rule       | A validation-grade distinction that prevents invalid conceptual merging                      |
| GL-CONS-003-STYPE-007 | User Decision            | Explicit project decision made during documentation construction                             |
| GL-CONS-003-STYPE-008 | Derived Rule             | A rule inferred from multiple prior sources                                                  |
| GL-CONS-003-STYPE-009 | Alias Source             | Legacy or alternate term source requiring canonical mapping                                  |
| GL-CONS-003-STYPE-010 | Future Derivation Source | A source that supports later schema, package, C++, test, or database derivation              |

---

## 6. Trace Relation Model

|           Record ID | Trace Relation | Meaning                                                                      |
| ------------------: | -------------- | ---------------------------------------------------------------------------- |
| GL-CONS-003-REL-001 | direct         | The target appears directly in the source                                    |
| GL-CONS-003-REL-002 | derived        | The target is derived from the source meaning                                |
| GL-CONS-003-REL-003 | supports       | The source supports the target but is not the only basis                     |
| GL-CONS-003-REL-004 | constrains     | The source limits what the target may mean                                   |
| GL-CONS-003-REL-005 | consolidates   | The source combines several prior meanings into one normalized form          |
| GL-CONS-003-REL-006 | aliases        | The source contains a legacy or alternate name mapped to a canonical term    |
| GL-CONS-003-REL-007 | enables        | The source prepares a later artifact, validation layer, or derivation branch |
| GL-CONS-003-REL-008 | excludes       | The source defines what the target must not own or become                    |
| GL-CONS-003-REL-009 | validates      | The source is used to validate the target’s correctness                      |
| GL-CONS-003-REL-010 | supersedes     | The source replaces or corrects an earlier interpretation                    |

---

## 7. Evidence Status Model

|            Record ID | Evidence Status         | Meaning                                                          |
| -------------------: | ----------------------- | ---------------------------------------------------------------- |
| GL-CONS-003-EVID-001 | direct                  | The source explicitly states the term, rule, or relation         |
| GL-CONS-003-EVID-002 | derived                 | The term or rule is derived from one or more explicit sources    |
| GL-CONS-003-EVID-003 | user_decision           | The source is an explicit user-approved decision                 |
| GL-CONS-003-EVID-004 | legacy_alias            | The source preserves older wording mapped to a canonical term    |
| GL-CONS-003-EVID-005 | inferred                | The source supports the meaning indirectly and needs review      |
| GL-CONS-003-EVID-006 | needs_validation        | The term or relation is retained but requires later confirmation |
| GL-CONS-003-EVID-007 | consolidation_authority | The meaning is stabilized by a consolidation pack                |
| GL-CONS-003-EVID-008 | validation_authority    | The meaning is stabilized by a validation or anti-collapse rule  |

---

## 8. Foundational Source Index

|        Source ID | Source Name              | Source Type                                | Main Authority                                                                           |
| ---------------: | ------------------------ | ------------------------------------------ | ---------------------------------------------------------------------------------------- |
| GL-SRC-FOUND-001 | README.md                | Foundational Document                      | Public identity, C++17 direction, header-only posture, system non-goals                  |
| GL-SRC-FOUND-002 | ProjectOverview.md       | Foundational Document                      | System position, external/internal context, corrected ingress flow, responsibility chain |
| GL-SRC-FOUND-003 | VisionAndScope.md        | Foundational Document                      | Vision, scope model, permanent exclusions, future derivation scope                       |
| GL-SRC-FOUND-004 | SYSTEM_GOALS.md          | Foundational Document / System Goal Source | Normative goals, verification direction, anti-collapse goals                             |
| GL-SRC-FOUND-005 | LOG_ASSEMBLER_ROADMAP.md | Foundational Document / Roadmap Source     | Architecture-to-implementation ordering, dependency-first sequencing                     |
| GL-SRC-FOUND-006 | Glossary Workstream Plan | Planning Source                            | GL-CONT pack sequencing and glossary program structure                                   |

---

## 9. Glossary Pack Source Index

|       Source ID | Pack ID     | Pack Name                                                                        | Source Authority                                                                       |
| --------------: | ----------- | -------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| GL-SRC-PACK-000 | GL-CONT-000 | Glossary Governance & Entry Model Pack                                           | Entry schema, maturity, source trace requirements, anti-collapse requirement           |
| GL-SRC-PACK-001 | GL-CONT-001 | Core System Identity & Phase Terms Pack                                          | System identity, bounded subsystem identity, pre-implementation phase                  |
| GL-SRC-PACK-002 | GL-CONT-002 | Boundary, Authority, and External Context Terms Pack                             | Boundary surfaces, external context, authority closure, downstream non-ownership       |
| GL-SRC-PACK-003 | GL-CONT-003 | Internal Actors and Delegated Entities Pack                                      | Internal actors, delegated entities, supporting entities, responsibility ownership     |
| GL-SRC-PACK-004 | GL-CONT-004 | Governed Objects, Carriers, and Envelope Terms Pack                              | Log Level Envelope, carrier objects, governed objects, policy objects, evidence        |
| GL-SRC-PACK-005 | GL-CONT-005 | Runtime, Queue, Slot, and Round Terms Pack                                       | Queue-as-container, slot occupancy, waiting lists, runtime rounds                      |
| GL-SRC-PACK-006 | GL-CONT-006 | Contracts, Templates, Type-Safety, and Contract Families Pack                    | Contracts as architectural laws, typed contracts, C++ template direction               |
| GL-SRC-PACK-007 | GL-CONT-007 | Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack    | Responsibility chain, obligations, delegation, enablement, capability candidates       |
| GL-SRC-PACK-008 | GL-CONT-008 | Policy, Metadata, Timestamp, and Governance Terms Pack                           | Policy material, metadata preparation, timestamp stabilization, governance constraints |
| GL-SRC-PACK-009 | GL-CONT-009 | Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack                | Dispatcher finality, handoff, registry-facing delivery, authority closure              |
| GL-SRC-PACK-010 | GL-CONT-010 | C++ Implementation Direction, Semantic Domains, and Future Derivation Terms Pack | C++17 direction, semantic domains, packages, processing units, future derivation       |

---

## 10. Consolidation Source Index

|       Source ID | Consolidation Artifact                          | Source Type                              | Main Authority                                                            |
| --------------: | ----------------------------------------------- | ---------------------------------------- | ------------------------------------------------------------------------- |
| GL-SRC-CONS-001 | Unified Glossary Content Consolidation Pack     | Consolidation Pack                       | Pack map, family model, unified glossary architecture, duplicate handling |
| GL-SRC-CONS-002 | GL-CONS-002_AntiCollapse_Index_Consolidation.md | Consolidation Pack / Anti-Collapse Index | Consolidated anti-collapse rules and validation-grade distinction index   |
| GL-SRC-CONS-003 | GL-CONS-003_SourceTrace_Index_Consolidation.md  | Consolidation Pack / Source Trace Index  | Consolidated source trace model and source authority mapping              |

---

## 11. Source Trace Layer Model

### 11.1 Layer Table

|             Record ID | Trace Layer                | Source Inputs                                                  | Purpose                                                                                 |
| --------------------: | -------------------------- | -------------------------------------------------------------- | --------------------------------------------------------------------------------------- |
| GL-CONS-003-LAYER-001 | Foundational Trace Layer   | README, ProjectOverview, VisionAndScope, SYSTEM_GOALS, Roadmap | Establish system identity, goals, scope, and derivation posture                         |
| GL-CONS-003-LAYER-002 | Governance Trace Layer     | GL-CONT-000                                                    | Establish entry schema, source trace policy, maturity, and anti-collapse rules          |
| GL-CONS-003-LAYER-003 | Content Trace Layer        | GL-CONT-001 through GL-CONT-010                                | Establish canonical term meanings by semantic area                                      |
| GL-CONS-003-LAYER-004 | Consolidation Trace Layer  | UGCC, GL-CONS-002, GL-CONS-003                                 | Normalize cross-pack rules and indexes                                                  |
| GL-CONS-003-LAYER-005 | Representation Trace Layer | Future JSON/CSV schema packs                                   | Preserve source references during data representation                                   |
| GL-CONS-003-LAYER-006 | Validation Trace Layer     | Future validation packs                                        | Check whether terms, rules, and derivations remain source-backed                        |
| GL-CONS-003-LAYER-007 | Implementation Trace Layer | Future C++ and package derivation packs                        | Ensure implementation artifacts trace back to glossary, contracts, and responsibilities |

### 11.2 Layer Rule

```text
Later trace layers must not erase earlier source authority.
A database row, JSON object, package name, class name, or validation test must
preserve the source chain that justified its existence.
```

---

## 12. Pack-to-Source Trace Map

### 12.1 GL-CONT-000 Source Trace

|              Trace ID | Target Pack | Source Basis                                             | Trace Relation | Evidence Status  | Source Summary                                                                          |
| --------------------: | ----------- | -------------------------------------------------------- | -------------- | ---------------- | --------------------------------------------------------------------------------------- |
| GL-TRACE-PACK-000-001 | GL-CONT-000 | README / ProjectOverview / VisionAndScope / SYSTEM_GOALS | supports       | derived          | Establishes need for controlled vocabulary and architecture-first glossary governance   |
| GL-TRACE-PACK-000-002 | GL-CONT-000 | ID Grammar and Join-Key Rules                            | supports       | direct / derived | Establishes ID namespace and join-key discipline                                        |
| GL-TRACE-PACK-000-003 | GL-CONT-000 | Canonical Kernel rules                                   | supports       | derived          | Establishes governance-layer distinction between meaning authority and runtime behavior |

### 12.2 GL-CONT-001 Source Trace

|              Trace ID | Target Pack | Source Basis       | Trace Relation | Evidence Status | Source Summary                                                                    |
| --------------------: | ----------- | ------------------ | -------------- | --------------- | --------------------------------------------------------------------------------- |
| GL-TRACE-PACK-001-001 | GL-CONT-001 | ProjectOverview.md | direct         | direct          | Defines Assembler System as bounded write-side preparation and dispatch subsystem |
| GL-TRACE-PACK-001-002 | GL-CONT-001 | VisionAndScope.md  | supports       | direct          | Defines C++ write-side preparation kernel vision                                  |
| GL-TRACE-PACK-001-003 | GL-CONT-001 | SYSTEM_GOALS.md    | constrains     | direct          | Preserves system identity goals and non-goals                                     |
| GL-TRACE-PACK-001-004 | GL-CONT-001 | GL-CONT-000        | constrains     | derived         | Applies entry schema and anti-collapse rules                                      |

### 12.3 GL-CONT-002 Source Trace

|              Trace ID | Target Pack | Source Basis       | Trace Relation | Evidence Status | Source Summary                                               |
| --------------------: | ----------- | ------------------ | -------------- | --------------- | ------------------------------------------------------------ |
| GL-TRACE-PACK-002-001 | GL-CONT-002 | ProjectOverview.md | direct         | direct          | Defines boundary overview and external architectural context |
| GL-TRACE-PACK-002-002 | GL-CONT-002 | VisionAndScope.md  | supports       | direct          | Defines authority closure and permanent exclusions           |
| GL-TRACE-PACK-002-003 | GL-CONT-002 | SYSTEM_GOALS.md    | constrains     | direct          | Defines boundary goals and authority exclusion goals         |
| GL-TRACE-PACK-002-004 | GL-CONT-002 | GL-CONT-000        | constrains     | derived         | Applies category integrity and source trace model            |

### 12.4 GL-CONT-003 Source Trace

|              Trace ID | Target Pack | Source Basis       | Trace Relation | Evidence Status | Source Summary                                                |
| --------------------: | ----------- | ------------------ | -------------- | --------------- | ------------------------------------------------------------- |
| GL-TRACE-PACK-003-001 | GL-CONT-003 | ProjectOverview.md | direct         | direct          | Defines internal architectural overview and internal entities |
| GL-TRACE-PACK-003-002 | GL-CONT-003 | VisionAndScope.md  | supports       | direct          | Supports corrected ingress and owned architectural concerns   |
| GL-TRACE-PACK-003-003 | GL-CONT-003 | SYSTEM_GOALS.md    | constrains     | direct          | Supports narrow delegation and supporting-entity distinctions |
| GL-TRACE-PACK-003-004 | GL-CONT-003 | GL-CONT-002        | constrains     | derived         | Prevents ports and external context from becoming actors      |

### 12.5 GL-CONT-004 Source Trace

|              Trace ID | Target Pack | Source Basis      | Trace Relation | Evidence Status | Source Summary                                                                |
| --------------------: | ----------- | ----------------- | -------------- | --------------- | ----------------------------------------------------------------------------- |
| GL-TRACE-PACK-004-001 | GL-CONT-004 | VisionAndScope.md | direct         | direct          | Establishes Log Level Envelope centrality                                     |
| GL-TRACE-PACK-004-002 | GL-CONT-004 | SYSTEM_GOALS.md   | constrains     | direct          | Prevents raw content from replacing envelope and envelope from becoming actor |
| GL-TRACE-PACK-004-003 | GL-CONT-004 | GL-CONT-003       | constrains     | derived         | Establishes Envelope Assembler as producer and Log Level Envelope as carrier  |
| GL-TRACE-PACK-004-004 | GL-CONT-004 | GL-CONT-000       | constrains     | derived         | Applies object/category integrity rules                                       |

### 12.6 GL-CONT-005 Source Trace

|              Trace ID | Target Pack | Source Basis      | Trace Relation | Evidence Status | Source Summary                                                  |
| --------------------: | ----------- | ----------------- | -------------- | --------------- | --------------------------------------------------------------- |
| GL-TRACE-PACK-005-001 | GL-CONT-005 | VisionAndScope.md | direct         | direct          | Establishes Queue-as-Container as part of current vision        |
| GL-TRACE-PACK-005-002 | GL-CONT-005 | SYSTEM_GOALS.md   | constrains     | direct          | Defines queue container, waiting list, and slot occupancy goals |
| GL-TRACE-PACK-005-003 | GL-CONT-005 | GL-CONT-003       | constrains     | derived         | Distinguishes runtime actors from runtime containers            |
| GL-TRACE-PACK-005-004 | GL-CONT-005 | GL-CONT-004       | supports       | derived         | Connects runtime placement to Log Level Envelope carrier model  |

### 12.7 GL-CONT-006 Source Trace

|              Trace ID | Target Pack | Source Basis       | Trace Relation | Evidence Status | Source Summary                                                             |
| --------------------: | ----------- | ------------------ | -------------- | --------------- | -------------------------------------------------------------------------- |
| GL-TRACE-PACK-006-001 | GL-CONT-006 | SYSTEM_GOALS.md    | direct         | direct          | Defines contracts as architectural laws before implementation artifacts    |
| GL-TRACE-PACK-006-002 | GL-CONT-006 | ProjectOverview.md | direct         | direct          | Establishes contract families                                              |
| GL-TRACE-PACK-006-003 | GL-CONT-006 | GL-CONT-005        | supports       | derived         | Runtime vocabulary feeds Runtime State Contract Family                     |
| GL-TRACE-PACK-006-004 | GL-CONT-006 | Roadmap Basis      | constrains     | derived         | Places contracts before templates and abstractions before processing units |

### 12.8 GL-CONT-007 Source Trace

|              Trace ID | Target Pack | Source Basis             | Trace Relation | Evidence Status | Source Summary                                                          |
| --------------------: | ----------- | ------------------------ | -------------- | --------------- | ----------------------------------------------------------------------- |
| GL-TRACE-PACK-007-001 | GL-CONT-007 | ProjectOverview.md       | direct         | direct          | Establishes External Relation → Contract → Responsibility chain         |
| GL-TRACE-PACK-007-002 | GL-CONT-007 | SYSTEM_GOALS.md          | constrains     | direct          | Prevents arbitrary responsibility creation and premature implementation |
| GL-TRACE-PACK-007-003 | GL-CONT-007 | Glossary Workstream Plan | supports       | derived         | Identifies GL-CONT-007 as derivation and traceability pack              |
| GL-TRACE-PACK-007-004 | GL-CONT-007 | GL-CONT-006              | constrains     | derived         | Requires contracts before responsibility derivation                     |

### 12.9 GL-CONT-008 Source Trace

|              Trace ID | Target Pack | Source Basis    | Trace Relation | Evidence Status | Source Summary                                                                                         |
| --------------------: | ----------- | --------------- | -------------- | --------------- | ------------------------------------------------------------------------------------------------------ |
| GL-TRACE-PACK-008-001 | GL-CONT-008 | SYSTEM_GOALS.md | direct         | direct          | Defines metadata/timestamp and policy governance goals                                                 |
| GL-TRACE-PACK-008-002 | GL-CONT-008 | GL-CONT-003     | constrains     | derived         | Distinguishes Metadata Injector, Timestamp Stabilizer, PolicyAssigner, and policy-consuming components |
| GL-TRACE-PACK-008-003 | GL-CONT-008 | GL-CONT-004     | constrains     | derived         | Distinguishes Policy Object and Policy Assignment as governed objects                                  |
| GL-TRACE-PACK-008-004 | GL-CONT-008 | GL-CONT-006     | supports       | derived         | Connects policy and metadata terms to contract families                                                |

### 12.10 GL-CONT-009 Source Trace

|              Trace ID | Target Pack | Source Basis    | Trace Relation | Evidence Status | Source Summary                                                              |
| --------------------: | ----------- | --------------- | -------------- | --------------- | --------------------------------------------------------------------------- |
| GL-TRACE-PACK-009-001 | GL-CONT-009 | GL-CONT-002     | constrains     | derived         | Boundary ends at valid dispatcher-mediated handoff                          |
| GL-TRACE-PACK-009-002 | GL-CONT-009 | GL-CONT-003     | direct         | derived         | Defines Dispatcher as final assembler-side outbound actor                   |
| GL-TRACE-PACK-009-003 | GL-CONT-009 | GL-CONT-004     | supports       | derived         | Defines Handoff Evidence and Downstream Registry Record as governed objects |
| GL-TRACE-PACK-009-004 | GL-CONT-009 | SYSTEM_GOALS.md | constrains     | direct          | Establishes Dispatcher finality and authority exclusion goals               |

### 12.11 GL-CONT-010 Source Trace

|              Trace ID | Target Pack | Source Basis                        | Trace Relation | Evidence Status  | Source Summary                                                                 |
| --------------------: | ----------- | ----------------------------------- | -------------- | ---------------- | ------------------------------------------------------------------------------ |
| GL-TRACE-PACK-010-001 | GL-CONT-010 | GL-CONT-006                         | constrains     | derived          | Contracts precede templates, traits, and CRTP                                  |
| GL-TRACE-PACK-010-002 | GL-CONT-010 | GL-CONT-007                         | constrains     | derived          | Future implementation follows responsibility derivation chain                  |
| GL-TRACE-PACK-010-003 | GL-CONT-010 | GL-CONT-009                         | constrains     | derived          | Future implementation must preserve authority closure                          |
| GL-TRACE-PACK-010-004 | GL-CONT-010 | VisionAndScope.md / SYSTEM_GOALS.md | direct         | direct / derived | Supports C++17, header-only-first, templates, CRTP, semantic domain derivation |

---

## 13. Term-Family Source Authority Map

| Family Code | Family Name                    | Primary Source Packs     | Supporting Source Packs                               |
| ----------: | ------------------------------ | ------------------------ | ----------------------------------------------------- |
|         SYS | System Identity                | GL-CONT-001              | README, ProjectOverview, VisionAndScope, SYSTEM_GOALS |
|         DOC | Documentation / Phase          | GL-CONT-001, GL-CONT-000 | Roadmap, Unified Glossary Consolidation               |
|         BND | Boundary                       | GL-CONT-002              | VisionAndScope, SYSTEM_GOALS, GL-CONT-009             |
|         EXT | External Context               | GL-CONT-002              | ProjectOverview, GL-CONT-007                          |
|         ENT | Internal Entity                | GL-CONT-003              | ProjectOverview, SYSTEM_GOALS                         |
|         OBJ | Governed Object                | GL-CONT-004              | VisionAndScope, SYSTEM_GOALS, GL-CONT-003             |
|         RUN | Runtime                        | GL-CONT-005              | VisionAndScope, SYSTEM_GOALS, GL-CONT-003             |
|         CON | Contract                       | GL-CONT-006              | ProjectOverview, SYSTEM_GOALS, Roadmap                |
|         POL | Policy / Metadata / Governance | GL-CONT-008              | SYSTEM_GOALS, GL-CONT-003, GL-CONT-004                |
|         TRC | Traceability                   | GL-CONT-007              | ProjectOverview, SYSTEM_GOALS, GL-CONT-000            |
|         CPP | C++ Direction                  | GL-CONT-006, GL-CONT-010 | README, VisionAndScope, SYSTEM_GOALS                  |
|         EXC | Exclusion / Authority Closure  | GL-CONT-002, GL-CONT-009 | SYSTEM_GOALS, GL-CONS-002                             |
|       ALIAS | Alias                          | GL-CONT-000, GL-CONT-004 | Source documents and legacy naming references         |
|         DER | Future Derivation              | GL-CONT-007, GL-CONT-010 | VisionAndScope, Roadmap, SYSTEM_GOALS                 |

---

## 14. High-Priority Trace Targets

The following targets must always retain source trace.

|     Trace Target ID | Target                         | Required Source Trace                                      |
| ------------------: | ------------------------------ | ---------------------------------------------------------- |
| GL-CONS-003-HPT-001 | Assembler System               | ProjectOverview, VisionAndScope, SYSTEM_GOALS, GL-CONT-001 |
| GL-CONS-003-HPT-002 | Assembler Boundary             | ProjectOverview, VisionAndScope, SYSTEM_GOALS, GL-CONT-002 |
| GL-CONS-003-HPT-003 | Log Level Envelope             | VisionAndScope, SYSTEM_GOALS, GL-CONT-003, GL-CONT-004     |
| GL-CONS-003-HPT-004 | Envelope Assembler             | ProjectOverview, VisionAndScope, SYSTEM_GOALS, GL-CONT-003 |
| GL-CONS-003-HPT-005 | Assembler Ingress Port         | ProjectOverview, SYSTEM_GOALS, GL-CONT-002, GL-CONT-003    |
| GL-CONS-003-HPT-006 | Queue Container                | VisionAndScope, SYSTEM_GOALS, GL-CONT-005                  |
| GL-CONS-003-HPT-007 | Contract                       | SYSTEM_GOALS, ProjectOverview, GL-CONT-006                 |
| GL-CONS-003-HPT-008 | Responsibility Chain           | ProjectOverview, SYSTEM_GOALS, GL-CONT-007                 |
| GL-CONS-003-HPT-009 | Policy Object                  | GL-CONT-004, GL-CONT-008, SYSTEM_GOALS                     |
| GL-CONS-003-HPT-010 | Metadata Injector              | GL-CONT-003, GL-CONT-008, SYSTEM_GOALS                     |
| GL-CONS-003-HPT-011 | Timestamp Stabilizer           | GL-CONT-003, GL-CONT-008, SYSTEM_GOALS                     |
| GL-CONS-003-HPT-012 | Dispatcher                     | GL-CONT-003, GL-CONT-009, SYSTEM_GOALS                     |
| GL-CONS-003-HPT-013 | Dispatcher-Mediated Handoff    | GL-CONT-002, GL-CONT-009, SYSTEM_GOALS                     |
| GL-CONS-003-HPT-014 | Post-Handoff Non-Ownership     | VisionAndScope, SYSTEM_GOALS, GL-CONT-002, GL-CONT-009     |
| GL-CONS-003-HPT-015 | Semantic Domain                | VisionAndScope, SYSTEM_GOALS, GL-CONT-010                  |
| GL-CONS-003-HPT-016 | C++17 Implementation Direction | README, VisionAndScope, SYSTEM_GOALS, GL-CONT-010          |

---

## 15. Source Trace Validation Model

### 15.1 Validation Checks

|           Record ID | Validation Check            | Description                                                                                 |
| ------------------: | --------------------------- | ------------------------------------------------------------------------------------------- |
| GL-CONS-003-VAL-001 | Source Presence Check       | Every canonical term must have at least one source trace                                    |
| GL-CONS-003-VAL-002 | Evidence Status Check       | Every trace must declare evidence status                                                    |
| GL-CONS-003-VAL-003 | Source Type Check           | Every source must have a declared source type                                               |
| GL-CONS-003-VAL-004 | Trace Relation Check        | Every trace must declare how source relates to target                                       |
| GL-CONS-003-VAL-005 | High-Priority Trace Check   | Critical terms must include required foundational and pack-level traces                     |
| GL-CONS-003-VAL-006 | Alias Trace Check           | Alias terms must point to canonical terms and source basis                                  |
| GL-CONS-003-VAL-007 | Anti-Collapse Trace Check   | Anti-collapse rules must trace to the pack or goal that established the distinction         |
| GL-CONS-003-VAL-008 | Authority Trace Check       | Downstream non-ownership claims must trace to boundary and handoff packs                    |
| GL-CONS-003-VAL-009 | Derivation Trace Check      | Future implementation terms must trace to contracts, responsibilities, and derivation rules |
| GL-CONS-003-VAL-010 | No Circular Authority Check | A derived source must not become the only authority for its own basis                       |

### 15.2 Validation Failure Classes

|            Record ID | Failure Class                | Meaning                                                              |
| -------------------: | ---------------------------- | -------------------------------------------------------------------- |
| GL-CONS-003-FAIL-001 | Source Missing               | Target has no source trace                                           |
| GL-CONS-003-FAIL-002 | Source Ambiguous             | Source exists but relation is unclear                                |
| GL-CONS-003-FAIL-003 | Evidence Weak                | Evidence status is inferred or needs validation                      |
| GL-CONS-003-FAIL-004 | Authority Mismatch           | Source does not support the claimed meaning                          |
| GL-CONS-003-FAIL-005 | Derived-Only Critical Term   | Critical term lacks direct or foundational source                    |
| GL-CONS-003-FAIL-006 | Alias Fork Risk              | Alias appears to create a hidden separate canonical term             |
| GL-CONS-003-FAIL-007 | Implementation Prematurity   | Implementation artifact lacks trace to contract/responsibility chain |
| GL-CONS-003-FAIL-008 | Downstream Ownership Leakage | Source trace contradicts authority exclusion                         |
| GL-CONS-003-FAIL-009 | Pack Dependency Gap          | Pack depends on a prior pack but trace is missing                    |
| GL-CONS-003-FAIL-010 | Supersession Conflict        | Older source conflicts with later corrected interpretation           |

---

## 16. Future Database Readiness

### 16.1 Suggested Row Grain

```text
One source trace relation per row.
```

This means that one term may have multiple source trace rows.

Example:

```text
GL-OBJ-001 — Log Level Envelope
  → VisionAndScope.md
  → SYSTEM_GOALS.md
  → GL-CONT-003
  → GL-CONT-004
```

Each relation should be stored separately.

### 16.2 Suggested Tables

| Table Name                     | Purpose                                                                    |
| ------------------------------ | -------------------------------------------------------------------------- |
| `glossary_sources`             | Stores source documents, packs, goals, rules, and decisions                |
| `glossary_source_traces`       | Stores source-to-target trace relations                                    |
| `glossary_trace_targets`       | Stores terms, rules, packs, goals, and derivation items that require trace |
| `glossary_evidence_statuses`   | Normalizes evidence status values                                          |
| `glossary_trace_relations`     | Normalizes trace relation values                                           |
| `glossary_validation_failures` | Stores validation findings for missing or weak traces                      |
| `glossary_source_aliases`      | Maps legacy source names to canonical source IDs                           |

### 16.3 Suggested Columns for `glossary_source_traces`

| Column            | Meaning                                                           |
| ----------------- | ----------------------------------------------------------------- |
| `trace_id`        | Stable trace row identifier                                       |
| `target_id`       | Term/rule/pack/goal/artifact being traced                         |
| `target_type`     | Type of traced target                                             |
| `source_id`       | Canonical source identifier                                       |
| `source_type`     | Type of source                                                    |
| `trace_relation`  | direct / derived / supports / constrains / consolidates / enables |
| `evidence_status` | direct / derived / user_decision / inferred / needs_validation    |
| `source_summary`  | Short explanation of source contribution                          |
| `validation_use`  | How this trace is used in validation                              |
| `is_required`     | Whether this trace is mandatory for the target                    |
| `status`          | active / pending / superseded / deprecated                        |
| `created_in_pack` | Pack where the trace was introduced                               |
| `notes`           | Optional notes                                                    |

### 16.4 Suggested JSON Shape

```json
{
  "trace_id": "GL-TRACE-TERM-OBJ-001-001",
  "target_id": "GL-OBJ-001",
  "target_type": "term",
  "source_id": "GL-SRC-PACK-004",
  "source_type": "glossary_content_pack",
  "trace_relation": "direct",
  "evidence_status": "direct",
  "source_summary": "GL-CONT-004 defines Log Level Envelope as the authoritative assembler-side carrier object.",
  "validation_use": "Validate that Log Level Envelope remains carrier_object / governed_object and is not treated as actor, raw payload, or downstream registry record.",
  "is_required": true,
  "status": "active"
}
```

---

## 17. Source Trace Application Rules

### 17.1 Master Glossary Rule

```text
Every final master glossary entry must include a Source Trace section or link
to source trace records.
```

### 17.2 JSON/CSV Population Rule

```text
JSON and CSV representations must not flatten source trace into informal prose.
They should preserve source_id, source_type, trace_relation, and evidence_status.
```

### 17.3 Database Rule

```text
Database representation should model source trace as a relation, not as a
single text field embedded inside the term row.
```

### 17.4 Implementation Derivation Rule

```text
No package, class, function, processing unit, or repository layout item should
be considered valid unless its source trace reaches at least one contract,
responsibility, obligation, delegation, enablement, or capability candidate.
```

### 17.5 Authority Exclusion Rule

```text
Any downstream-facing implementation or schema derivation must preserve traces
to Post-Handoff Non-Ownership, Authority Closure, and downstream lifecycle
exclusion sources.
```

---

## 18. Exit Criteria

|            Record ID | Exit Criterion                              | Status   |
| -------------------: | ------------------------------------------- | -------- |
| GL-CONS-003-EXIT-001 | Source type model is defined                | Complete |
| GL-CONS-003-EXIT-002 | Trace relation model is defined             | Complete |
| GL-CONS-003-EXIT-003 | Evidence status model is defined            | Complete |
| GL-CONS-003-EXIT-004 | Foundational source index is defined        | Complete |
| GL-CONS-003-EXIT-005 | Glossary pack source index is defined       | Complete |
| GL-CONS-003-EXIT-006 | Consolidation source index is defined       | Complete |
| GL-CONS-003-EXIT-007 | Pack-to-source trace map is defined         | Complete |
| GL-CONS-003-EXIT-008 | Term-family source authority map is defined | Complete |
| GL-CONS-003-EXIT-009 | High-priority trace targets are identified  | Complete |
| GL-CONS-003-EXIT-010 | Source trace validation model is defined    | Complete |
| GL-CONS-003-EXIT-011 | Future database readiness is defined        | Complete |

---

## 19. Summary

`GL-CONS-003_SourceTrace_Index_Consolidation.md` establishes the source trace authority model for the Assembler System glossary workstream.

It ensures that glossary meaning remains source-backed.

It prepares the project for later validation and database representation without forcing immediate database implementation.

The central doctrine is:

```text
No canonical meaning without source trace.
No source trace without declared relation.
No declared relation without evidence status.
No implementation derivation without trace back to architecture.
```

Recommended next artifact:

```text
GL-CONS-004_TermFamily_Index_Consolidation.md
```

```
```
