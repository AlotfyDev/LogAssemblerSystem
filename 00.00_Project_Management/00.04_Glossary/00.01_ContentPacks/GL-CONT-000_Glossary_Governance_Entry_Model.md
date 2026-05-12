# GL-CONT-000 — Glossary Governance & Entry Model Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-000-DOC-001 | Pack Name | GL-CONT-000 — Glossary Governance & Entry Model Pack |
| GL-CONT-000-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-000-DOC-003 | Project | Assembler System |
| GL-CONT-000-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-000-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-000-DOC-006 | Language | English |
| GL-CONT-000-DOC-007 | Scope | Governance rules, term entry model, classification model, anti-collapse model, traceability model, maturity model |
| GL-CONT-000-DOC-008 | Excluded From This Pack | Full term inventory, CSV population, JSON population, JSON schema finalization, glossary consolidation |
| GL-CONT-000-DOC-009 | Depends On | README.md, ProjectOverview.md, VisionAndScope.md, SYSTEM_GOALS.md, Canonical Kernel, ID Grammar and Join-Key rules |
| GL-CONT-000-DOC-010 | Enables | GL-CONT-001 through GL-CONT-010, later schema packs, later population packs, later validation packs |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the governance model for the Assembler System Glossary.

The glossary is not a convenience dictionary.

The glossary is a controlled vocabulary, anti-collapse reference, and system-element inventory that preserves the canonical meaning of Assembler System terms before those terms are used in roadmap planning, semantic domain derivation, package derivation, C++ abstraction design, processing-unit derivation, CSV representation, JSON representation, or validation reports.

### 2.2 Core Function

The glossary must perform three connected functions:

| Record ID | Function | Description |
|---:|---|---|
| GL-CONT-000-FUNC-001 | Controlled Vocabulary | Define the canonical term and its intended meaning |
| GL-CONT-000-FUNC-002 | Anti-Collapse Glossary | State what the term must not be confused with |
| GL-CONT-000-FUNC-003 | System Element Inventory | Preserve all named system elements, including low-detail seed elements |
| GL-CONT-000-FUNC-004 | Derivation Support | Prepare future semantic domains, packages, C++ abstractions, and processing units |
| GL-CONT-000-FUNC-005 | Representation Readiness | Prepare later CSV and JSON representation without forcing early population |
| GL-CONT-000-FUNC-006 | Review and Validation Support | Allow future coverage audits, anti-collapse checks, alias audits, and source trace checks |

### 2.3 Non-Purpose

This pack does not populate the full glossary.

It does not produce the final `Glossary.md`.

It does not fill CSV files.

It does not fill JSON files.

It does not finalize JSON schemas.

It does not decide final implementation packages.

It defines the rules that all later glossary content packs must obey.

---

## 3. Glossary Governance Principle

### 3.1 Primary Principle

The Assembler System Glossary must be governed by the following principle:

```text
One canonical term should express one canonical meaning inside one declared architectural context.
````

### 3.2 Governance Requirements

|           Record ID | Requirement                                  | Explanation                                                                                                                         |
| ------------------: | -------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-000-GOV-001 | Canonical meaning must be explicit           | A term must not depend on reader intuition                                                                                          |
| GL-CONT-000-GOV-002 | Architectural category must be explicit      | A term must declare whether it is an entity, port, carrier, object, doctrine, runtime state, contract, or future derivation concept |
| GL-CONT-000-GOV-003 | Anti-collapse risk must be explicit          | Important terms must declare what they must not be confused with                                                                    |
| GL-CONT-000-GOV-004 | Source trace should be preserved             | Where possible, a term must identify its source group, source file, record ID, or prior document basis                              |
| GL-CONT-000-GOV-005 | Low-detail elements must not be discarded    | A sparse term is still recorded as a seed if it appears in the system references                                                    |
| GL-CONT-000-GOV-006 | Representation must not precede meaning      | CSV/JSON representation follows content governance, not the reverse                                                                 |
| GL-CONT-000-GOV-007 | Implementation must not redefine terminology | Code, package names, and build layout must follow canonical terms, not invent parallel meanings                                     |
| GL-CONT-000-GOV-008 | Aliases must point to canonical terms        | Legacy or shorthand terms must not create hidden semantic forks                                                                     |

---

## 4. Glossary Scope

### 4.1 In Scope

The glossary must include every term that participates in the Assembler System semantic model, even if the current evidence is partial.

|             Record ID | Scope Class             | Included Examples                                                        |
| --------------------: | ----------------------- | ------------------------------------------------------------------------ |
| GL-CONT-000-SCOPE-001 | System Identity Terms   | Assembler System, Assembler Subsystem, C++ Write-Side Preparation Kernel |
| GL-CONT-000-SCOPE-002 | Boundary Terms          | Assembler Boundary, Authority Boundary, Registry / Delivery Port         |
| GL-CONT-000-SCOPE-003 | External Context Terms  | Level API, Policy Registry / Policy Source, Reading / Querying Subsystem |
| GL-CONT-000-SCOPE-004 | Internal Entity Terms   | Envelope Assembler, Dispatcher, Validator                                |
| GL-CONT-000-SCOPE-005 | Delegated Entity Terms  | Queue Bundle Agent, Single Queue Moderator, Round Managers               |
| GL-CONT-000-SCOPE-006 | Governed Object Terms   | Log Level Envelope, Delivery-Cycle Flag Set, Dispatcher Feedback Report  |
| GL-CONT-000-SCOPE-007 | Runtime State Terms     | Queue Container, Slot, Envelope Slot Occupancy                           |
| GL-CONT-000-SCOPE-008 | Contract Terms          | Contract Family, Ingress Contract Family, Runtime State Contract Family  |
| GL-CONT-000-SCOPE-009 | Responsibility Terms    | Responsibility, Obligation, Delegation, Enablement                       |
| GL-CONT-000-SCOPE-010 | Anti-Collapse Terms     | Guard rules preventing invalid conceptual merges                         |
| GL-CONT-000-SCOPE-011 | C++ Direction Terms     | C++17, Header-Only First, CRTP, Template Abstraction Layer               |
| GL-CONT-000-SCOPE-012 | Future Derivation Terms | Semantic Domain, DDD Package Structure, Processing Unit                  |
| GL-CONT-000-SCOPE-013 | Alias Terms             | Log Envelope, RoadMap.md, Registry Port                                  |
| GL-CONT-000-SCOPE-014 | Seed Terms              | Any referenced system element with limited current information           |

### 4.2 Out of Scope

|           Record ID | Out-of-Scope Area           | Reason                                            |
| ------------------: | --------------------------- | ------------------------------------------------- |
| GL-CONT-000-OOS-001 | Final C++ class definitions | Belongs to later implementation derivation        |
| GL-CONT-000-OOS-002 | Final package layout        | Belongs to semantic domain and package derivation |
| GL-CONT-000-OOS-003 | Final runtime algorithms    | Belongs to runtime implementation design          |
| GL-CONT-000-OOS-004 | CSV population              | Belongs to later population packs                 |
| GL-CONT-000-OOS-005 | JSON population             | Belongs to later population packs                 |
| GL-CONT-000-OOS-006 | Final JSON schema freezing  | Belongs to schema definition packs                |
| GL-CONT-000-OOS-007 | Downstream registry schema  | Outside assembler-core ownership                  |
| GL-CONT-000-OOS-008 | PostgreSQL derivation       | Future downstream branch, not glossary governance |
| GL-CONT-000-OOS-009 | Thin C API / FFI design     | Future integration branch                         |

---

## 5. Foundational Source Rules

### 5.1 Source Dependency Rule

All glossary entries should be traceable to one or more of the following source classes:

|           Record ID | Source Class                   | Description                                                                |
| ------------------: | ------------------------------ | -------------------------------------------------------------------------- |
| GL-CONT-000-SRC-001 | Prior Foundational Documents   | README, ProjectOverview, VisionAndScope, SYSTEM_GOALS                      |
| GL-CONT-000-SRC-002 | Architectural Taxonomy         | External/internal/runtime/object/contract/doctrine taxonomy                |
| GL-CONT-000-SRC-003 | Canonical Responsibilities     | Responsibility, obligation, and responsibility-obligation records          |
| GL-CONT-000-SRC-004 | Delegation / Enablement Matrix | Delegated entities, governed objects, enablement families, surfaces, ports |
| GL-CONT-000-SRC-005 | Anti-Collapse Rules            | Guard rules preventing invalid conceptual merges                           |
| GL-CONT-000-SRC-006 | ID Grammar and Join-Key Rules  | Namespaces, join keys, row grain, source trace, validation rules           |
| GL-CONT-000-SRC-007 | User Decisions                 | Explicit project decisions made during documentation construction          |
| GL-CONT-000-SRC-008 | Future Formal Proposals        | Draft terms pending validation and registration                            |

### 5.2 Vendored Source Rule

When a glossary entry cites source material, the source should resolve through vendored source data or approved aliases.

This follows the source-data and ID grammar principle that source references should resolve through the source-data root or approved aliases, not through unstable runtime paths. 

### 5.3 Evidence Status Rule

Each glossary entry should declare an evidence status where possible.

|            Record ID | Evidence Status          | Meaning                                                                |
| -------------------: | ------------------------ | ---------------------------------------------------------------------- |
| GL-CONT-000-EVID-001 | `direct`                 | The term appears directly in a source or prior formal document         |
| GL-CONT-000-EVID-002 | `derived`                | The term is derived from a canonical chain or relation                 |
| GL-CONT-000-EVID-003 | `user_decision`          | The term is established by explicit project decision                   |
| GL-CONT-000-EVID-004 | `seed_low_detail`        | The term appears but lacks full detail                                 |
| GL-CONT-000-EVID-005 | `needs_validation`       | The term is plausible but requires later source confirmation           |
| GL-CONT-000-EVID-006 | `legacy_alias`           | The term is a legacy or source-data variant mapped to a canonical term |
| GL-CONT-000-EVID-007 | `rejected_or_deprecated` | The term is retained only to prevent invalid use                       |

---

## 6. Term Family Model

### 6.1 Purpose

Term families group glossary entries by semantic role.

They are not implementation packages.

They are not filesystem folders.

They are controlled vocabulary classes used to organize the glossary.

### 6.2 Term Families

|           Record ID | Family Code | Family Name                        | Description                                                                              |
| ------------------: | ----------- | ---------------------------------- | ---------------------------------------------------------------------------------------- |
| GL-CONT-000-FAM-001 | `SYS`       | System Identity Terms              | Terms defining what the Assembler System is                                              |
| GL-CONT-000-FAM-002 | `BND`       | Boundary Terms                     | Terms defining boundaries, surfaces, authority limits, and ports                         |
| GL-CONT-000-FAM-003 | `EXT`       | External Context Terms             | External actors, upstream sources, downstream destinations, and non-owned systems        |
| GL-CONT-000-FAM-004 | `ENT`       | Internal Entity and Actor Terms    | Internal delegated entities, actors, moderators, managers, and assembler-side components |
| GL-CONT-000-FAM-005 | `OBJ`       | Governed Object and Carrier Terms  | Carrier objects, governed objects, reports, state artifacts, and records                 |
| GL-CONT-000-FAM-006 | `RUN`       | Runtime and Queue Terms            | Queue, slot, occupancy, waiting list, round, and runtime coordination terms              |
| GL-CONT-000-FAM-007 | `CON`       | Contract and Type Terms            | Contract, typed contract, template contract, contract family, and type-safety terms      |
| GL-CONT-000-FAM-008 | `POL`       | Policy and Governance Terms        | Policy objects, policy assignment, policy hosts, and governance terms                    |
| GL-CONT-000-FAM-009 | `TRC`       | Traceability Terms                 | Responsibility, obligation, delegation, enablement, source trace, ID namespace           |
| GL-CONT-000-FAM-010 | `EXC`       | Authority and Exclusion Terms      | Post-handoff exclusion, downstream non-ownership, registry/query exclusion               |
| GL-CONT-000-FAM-011 | `CPP`       | C++ Implementation Direction Terms | C++17, header-only first, templates, CRTP, static polymorphism                           |
| GL-CONT-000-FAM-012 | `DER`       | Future Derivation Terms            | Semantic domain, package derivation, processing unit, roadmap derivative concepts        |
| GL-CONT-000-FAM-013 | `ALIAS`     | Alias and Legacy Terms             | Legacy/source variants mapped to canonical terms                                         |
| GL-CONT-000-FAM-014 | `DOC`       | Documentation and Governance Terms | Terms used for documentation control, record IDs, schema readiness                       |
| GL-CONT-000-FAM-015 | `GUARD`     | Anti-Collapse Guard Terms          | Guard rules and invalid collapse identifiers                                             |

---

## 7. Architectural Category Model

### 7.1 Purpose

A term family describes a grouping.

A category describes the architectural nature of the term.

For example, `Registry / Delivery Port` may belong to the `BND` family and have the category `port` or `contract_surface`.

### 7.2 Categories

|           Record ID | Category                   | Definition                                                                              |
| ------------------: | -------------------------- | --------------------------------------------------------------------------------------- |
| GL-CONT-000-CAT-001 | `system_identity`          | A term describing the system’s identity or architectural role                           |
| GL-CONT-000-CAT-002 | `external_context`         | A term describing an external actor, source, destination, or non-owned subsystem        |
| GL-CONT-000-CAT-003 | `internal_entity`          | A term describing an internal assembler-side entity                                     |
| GL-CONT-000-CAT-004 | `delegated_entity`         | An entity carrying delegated responsibility                                             |
| GL-CONT-000-CAT-005 | `supporting_entity`        | A component supporting a responsibility without being the primary responsibility owner  |
| GL-CONT-000-CAT-006 | `actor`                    | A responsibility-carrying internal actor                                                |
| GL-CONT-000-CAT-007 | `boundary_surface`         | A governance boundary or visible interaction surface                                    |
| GL-CONT-000-CAT-008 | `port`                     | A bounded delivery, registry, or contract-facing surface                                |
| GL-CONT-000-CAT-009 | `contract_surface`         | A surface governed by a contract                                                        |
| GL-CONT-000-CAT-010 | `carrier_object`           | A carrier for prepared content or governed state                                        |
| GL-CONT-000-CAT-011 | `governed_object`          | An object controlled, validated, emitted, stored, resolved, or interpreted by an entity |
| GL-CONT-000-CAT-012 | `runtime_state`            | A runtime state or state-bearing structure                                              |
| GL-CONT-000-CAT-013 | `contract_family`          | A family of related contracts                                                           |
| GL-CONT-000-CAT-014 | `enablement_family`        | A capability family enabling responsibility execution                                   |
| GL-CONT-000-CAT-015 | `responsibility`           | A canonical duty or ownership requirement                                               |
| GL-CONT-000-CAT-016 | `obligation`               | A preservation, enforcement, guarantee, or prevention requirement                       |
| GL-CONT-000-CAT-017 | `doctrine`                 | A governing architectural rule                                                          |
| GL-CONT-000-CAT-018 | `anti_collapse_guard`      | A rule preventing invalid conceptual merging                                            |
| GL-CONT-000-CAT-019 | `implementation_direction` | A term guiding future implementation but not itself code                                |
| GL-CONT-000-CAT-020 | `future_derivation`        | A term reserved for later derivation                                                    |
| GL-CONT-000-CAT-021 | `alias`                    | A non-canonical or legacy name mapped to a canonical term                               |

### 7.3 Category Integrity Rule

A term must not silently change category.

For example:

|                Record ID | Invalid Category Drift                            | Correct Treatment                      |
| -----------------------: | ------------------------------------------------- | -------------------------------------- |
| GL-CONT-000-CAT-RULE-001 | Treating `Log Level Envelope` as an actor         | It is a carrier object                 |
| GL-CONT-000-CAT-RULE-002 | Treating `Registry / Delivery Port` as Dispatcher | It is a port or contract surface       |
| GL-CONT-000-CAT-RULE-003 | Treating `Queue Container` as message broker      | It is runtime/container structure      |
| GL-CONT-000-CAT-RULE-004 | Treating `Enablement` as code                     | It is a capability/governance family   |
| GL-CONT-000-CAT-RULE-005 | Treating `Semantic Domain` as folder category     | It is a semantic architecture boundary |

The Canonical Kernel explicitly distinguishes responsibilities, obligations, delegated entities, governed objects, enablement, surfaces, ports, contract families, and gaps; this is the basis for category integrity in the glossary. 

---

## 8. Entry Maturity Model

### 8.1 Purpose

The glossary must include even incomplete system elements.

To avoid pretending that all entries have the same maturity, each entry must carry an entry maturity value.

### 8.2 Maturity Values

|           Record ID | Maturity Value           | Meaning                                                                                           |
| ------------------: | ------------------------ | ------------------------------------------------------------------------------------------------- |
| GL-CONT-000-MAT-001 | `canonical_full`         | Fully canonical term with clear definition, category, role, anti-collapse rules, and source trace |
| GL-CONT-000-MAT-002 | `canonical_partial`      | Canonical term with enough evidence to use, but not enough detail for final derivation            |
| GL-CONT-000-MAT-003 | `seed`                   | Named system element preserved for later expansion                                                |
| GL-CONT-000-MAT-004 | `alias`                  | Legacy, shorthand, or source-data variant mapped to a canonical term                              |
| GL-CONT-000-MAT-005 | `future_derivation`      | Term reserved for later roadmap, domain, package, or implementation derivation                    |
| GL-CONT-000-MAT-006 | `deprecated_or_rejected` | Term retained only to prevent incorrect usage                                                     |
| GL-CONT-000-MAT-007 | `needs_review`           | Term requires review before use in formal derivation                                              |

### 8.3 Seed Entry Rule

A seed entry is valid when:

1. the term appears in a source, prior document, or explicit user decision,
2. the term has plausible system relevance,
3. the term’s category can be tentatively assigned,
4. the term is marked as incomplete,
5. the term is not used to derive implementation packages until upgraded.

### 8.4 Seed Entry Warning

```text
A seed entry preserves visibility.
It does not grant implementation authority.
```

---

## 9. Term Entry Schema for Markdown

### 9.1 Purpose

This schema defines how entries should appear in the human-readable glossary content packs.

It is not yet the CSV schema.

It is not yet the JSON schema.

It is the Markdown content entry shape from which later representations can be derived.

### 9.2 Full Entry Schema

Each major glossary term should use the following schema.

|             Record ID | Field                     |    Required | Description                                                                               |
| --------------------: | ------------------------- | ----------: | ----------------------------------------------------------------------------------------- |
| GL-CONT-000-ENTRY-001 | Term ID                   |         Yes | Stable glossary identifier                                                                |
| GL-CONT-000-ENTRY-002 | Canonical Term            |         Yes | Official controlled vocabulary term                                                       |
| GL-CONT-000-ENTRY-003 | Family                    |         Yes | SYS, BND, EXT, ENT, OBJ, RUN, CON, POL, TRC, EXC, CPP, DER, ALIAS, DOC, GUARD             |
| GL-CONT-000-ENTRY-004 | Category                  |         Yes | Architectural category                                                                    |
| GL-CONT-000-ENTRY-005 | Definition                |         Yes | Clear definition                                                                          |
| GL-CONT-000-ENTRY-006 | Architectural Role        |         Yes | Role inside Assembler System                                                              |
| GL-CONT-000-ENTRY-007 | Ownership Scope           |         Yes | assembler-owned, external, downstream, governed, future, not-owned                        |
| GL-CONT-000-ENTRY-008 | Must Not Be Confused With | Conditional | Required for important or high-risk terms                                                 |
| GL-CONT-000-ENTRY-009 | Related Terms             | Recommended | Related canonical terms                                                                   |
| GL-CONT-000-ENTRY-010 | Valid Usage               | Recommended | Correct usage examples                                                                    |
| GL-CONT-000-ENTRY-011 | Invalid Usage             | Recommended | Incorrect usage examples                                                                  |
| GL-CONT-000-ENTRY-012 | Source Trace              | Recommended | Source group, source file, source record, prior document, or user decision                |
| GL-CONT-000-ENTRY-013 | Evidence Status           | Recommended | direct, derived, user_decision, seed_low_detail, needs_validation                         |
| GL-CONT-000-ENTRY-014 | Entry Maturity            |         Yes | canonical_full, canonical_partial, seed, alias, future_derivation, deprecated_or_rejected |
| GL-CONT-000-ENTRY-015 | Future Derivation Notes   | Conditional | Notes for future domain/package/C++ derivation                                            |
| GL-CONT-000-ENTRY-016 | Representation Notes      |    Optional | Notes for later CSV/JSON mapping                                                          |

### 9.3 Compact Entry Schema

Secondary or low-detail seed terms may use a compact schema.

|              Record ID | Field              |    Required | Description                             |
| ---------------------: | ------------------ | ----------: | --------------------------------------- |
| GL-CONT-000-CENTRY-001 | Term ID            |         Yes | Stable glossary identifier              |
| GL-CONT-000-CENTRY-002 | Canonical Term     |         Yes | Official or proposed term               |
| GL-CONT-000-CENTRY-003 | Family             |         Yes | Term family                             |
| GL-CONT-000-CENTRY-004 | Category           |         Yes | Architectural category                  |
| GL-CONT-000-CENTRY-005 | Short Definition   |         Yes | One- or two-line definition             |
| GL-CONT-000-CENTRY-006 | Anti-Collapse Note | Conditional | Required if the term is easy to confuse |
| GL-CONT-000-CENTRY-007 | Entry Maturity     |         Yes | Usually seed or canonical_partial       |
| GL-CONT-000-CENTRY-008 | Source Trace       | Recommended | Evidence basis where known              |

### 9.4 Markdown Entry Template

```markdown
### <TERM-ID> — <Canonical Term>

| Field | Value |
|---|---|
| Term ID | <TERM-ID> |
| Canonical Term | <Canonical Term> |
| Family | <SYS / BND / EXT / ENT / OBJ / RUN / CON / POL / TRC / EXC / CPP / DER / ALIAS / DOC / GUARD> |
| Category | <architectural category> |
| Ownership Scope | <assembler_owned / external / downstream / governed / future / not_owned> |
| Entry Maturity | <canonical_full / canonical_partial / seed / alias / future_derivation / deprecated_or_rejected> |
| Evidence Status | <direct / derived / user_decision / seed_low_detail / needs_validation> |

#### Definition

<Definition text.>

#### Architectural Role

<Role text.>

#### Must Not Be Confused With

1. <Term or concept>
2. <Term or concept>

#### Valid Usage

- <Valid usage example.>

#### Invalid Usage

- <Invalid usage example.>

#### Related Terms

- <Related term>
- <Related term>

#### Source Trace

| Source Type | Source |
|---|---|
| <source type> | <source reference or decision basis> |

#### Future Derivation Notes

<Notes, if any.>
```

---

## 10. Term ID Model

### 10.1 Purpose

Glossary IDs must allow stable referencing across:

1. Markdown entries,
2. future CSV rows,
3. future JSON records,
4. anti-collapse maps,
5. alias maps,
6. source trace maps,
7. roadmap phases,
8. domain derivation packs,
9. C++ derivation packs.

### 10.2 Term ID Prefixes

|          Record ID | Prefix       | Family                                      |
| -----------------: | ------------ | ------------------------------------------- |
| GL-CONT-000-ID-001 | `GL-SYS-*`   | System identity terms                       |
| GL-CONT-000-ID-002 | `GL-BND-*`   | Boundary and authority terms                |
| GL-CONT-000-ID-003 | `GL-EXT-*`   | External context terms                      |
| GL-CONT-000-ID-004 | `GL-ENT-*`   | Internal entity and actor terms             |
| GL-CONT-000-ID-005 | `GL-OBJ-*`   | Governed object and carrier terms           |
| GL-CONT-000-ID-006 | `GL-RUN-*`   | Runtime and queue terms                     |
| GL-CONT-000-ID-007 | `GL-CON-*`   | Contract and type terms                     |
| GL-CONT-000-ID-008 | `GL-POL-*`   | Policy and governance terms                 |
| GL-CONT-000-ID-009 | `GL-TRC-*`   | Traceability and derivation chain terms     |
| GL-CONT-000-ID-010 | `GL-EXC-*`   | Authority exclusion terms                   |
| GL-CONT-000-ID-011 | `GL-CPP-*`   | C++ implementation direction terms          |
| GL-CONT-000-ID-012 | `GL-DER-*`   | Semantic domain and future derivation terms |
| GL-CONT-000-ID-013 | `GL-ALIAS-*` | Alias and legacy terms                      |
| GL-CONT-000-ID-014 | `GL-DOC-*`   | Documentation governance terms              |
| GL-CONT-000-ID-015 | `GL-GUARD-*` | Anti-collapse guard terms                   |

### 10.3 ID Rule

Glossary term IDs are not replacements for canonical source IDs.

For example:

|             Record ID | Source ID                | Glossary ID              | Relationship                                         |
| --------------------: | ------------------------ | ------------------------ | ---------------------------------------------------- |
| GL-CONT-000-IDMAP-001 | `E-INT-002`              | `GL-ENT-002`             | The glossary entry describes the canonical entity    |
| GL-CONT-000-IDMAP-002 | `BCO-014`                | `GL-OBJ-001`             | The glossary entry describes the governed object     |
| GL-CONT-000-IDMAP-003 | `EN-FAM-004`             | `GL-TRC-*` or `GL-CON-*` | The glossary entry describes the enablement family   |
| GL-CONT-000-IDMAP-004 | `ACG-007` or `GUARD-007` | `GL-GUARD-*`             | The glossary entry describes the anti-collapse guard |

### 10.4 No ID Invention Rule

A glossary entry may propose a `GL-*` term ID for glossary organization.

It must not invent canonical system IDs such as responsibility IDs, entity IDs, governed object IDs, or enablement family IDs.

The ID Grammar source explicitly states that missing IDs must not be invented; missing evidence must be reported or handled through a formal proposal path. 

---

## 11. Anti-Collapse Model

### 11.1 Purpose

Anti-collapse rules prevent the glossary from merging distinct concepts into convenient but false simplifications.

### 11.2 Anti-Collapse Entry Requirement

Every high-risk term must specify:

1. what it is,
2. what it is not,
3. what it must not be confused with,
4. invalid usage examples,
5. related guard IDs where available.

### 11.3 Core Anti-Collapse Classes

|          Record ID | Anti-Collapse Class                         | Example                                                            |
| -----------------: | ------------------------------------------- | ------------------------------------------------------------------ |
| GL-CONT-000-AC-001 | Actor vs Carrier                            | Log Level Envelope is not Envelope Assembler                       |
| GL-CONT-000-AC-002 | Port vs Actor                               | Registry / Delivery Port is not Dispatcher                         |
| GL-CONT-000-AC-003 | Entity vs Governed Object                   | Envelope Slot Occupancy is not lifecycle owner                     |
| GL-CONT-000-AC-004 | Policy Object vs Policy Host                | Policy Object is not PolicyAssigner or executor                    |
| GL-CONT-000-AC-005 | Metadata vs Policy                          | Metadata Injector is schema/directive-governed, not policy-hosted  |
| GL-CONT-000-AC-006 | Queue vs Broker                             | Queue Container is not a message broker                            |
| GL-CONT-000-AC-007 | Queue vs Higher Runtime Container           | Queue equals container; no separate runtime container above it     |
| GL-CONT-000-AC-008 | Contract vs Runtime Interface               | Template contracts are not runtime COM interfaces                  |
| GL-CONT-000-AC-009 | Enablement vs Implementation                | Enablement is not final implementation code                        |
| GL-CONT-000-AC-010 | Capability Candidate vs Class               | Capability candidate is not automatically a class/function/package |
| GL-CONT-000-AC-011 | Semantic Domain vs Technical Folder         | Semantic domain is not `templates/` or `concretes/`                |
| GL-CONT-000-AC-012 | Registry Destination vs Assembler Ownership | Downstream registry does not become assembler-owned                |

### 11.4 Guard Mapping Requirement

Where a source guard exists, glossary entries must reference it.

The source schema identifies core guards such as: Metadata Injector is not a policy host, Queue Runtime Layer is classification-only, Delivery-Cycle Flag Set is not Dispatcher Feedback Report, Queue equals Container, Waiting Lists store Queue Container Identifiers, Envelope Slot Occupancy is not envelope lifecycle ownership, Registry / Delivery Port does not replace Dispatcher, and Template contracts are not runtime COM interfaces. 

---

## 12. Alias and Legacy Term Model

### 12.1 Purpose

Aliases preserve source compatibility without allowing multiple meanings.

A legacy term should not create a second concept if a canonical term already exists.

### 12.2 Alias Entry Requirements

Each alias entry must include:

|                 Record ID | Field          | Description                                                               |
| ------------------------: | -------------- | ------------------------------------------------------------------------- |
| GL-CONT-000-ALIAS-REQ-001 | Alias Term     | The legacy or shorthand term                                              |
| GL-CONT-000-ALIAS-REQ-002 | Canonical Term | The term that should be used in formal documentation                      |
| GL-CONT-000-ALIAS-REQ-003 | Alias Type     | legacy, shorthand, file-name variant, source-data variant, rejected usage |
| GL-CONT-000-ALIAS-REQ-004 | Usage Rule     | How the alias may or may not be used                                      |
| GL-CONT-000-ALIAS-REQ-005 | Risk           | What confusion the alias may cause                                        |
| GL-CONT-000-ALIAS-REQ-006 | Status         | alias, deprecated, rejected, needs_review                                 |

### 12.3 Initial Alias Doctrine

|             Record ID | Alias / Variant   | Canonical Term             | Usage Rule                                                                |
| --------------------: | ----------------- | -------------------------- | ------------------------------------------------------------------------- |
| GL-CONT-000-ALIAS-001 | Log Envelope      | Log Level Envelope         | Legacy/source-data variant unless later distinction is introduced         |
| GL-CONT-000-ALIAS-002 | Registry Port     | Registry / Delivery Port   | Use full canonical term in formal documents                               |
| GL-CONT-000-ALIAS-003 | Queue             | Queue Container            | Use Queue Container when referring to runtime structure                   |
| GL-CONT-000-ALIAS-004 | RoadMap.md        | LOG_ASSEMBLER_ROADMAP.md   | General document name vs specific project roadmap name                    |
| GL-CONT-000-ALIAS-005 | Runtime Container | Queue Container            | Invalid if it implies a container above Queue Container                   |
| GL-CONT-000-ALIAS-006 | Policy Host       | Policy-Consuming Component | Use carefully; do not include Metadata Injector unless explicitly allowed |

---

## 13. Source Trace Model

### 13.1 Purpose

Source trace allows each glossary entry to remain evidence-aware.

The glossary must not become an ungrounded invention layer.

### 13.2 Source Trace Fields

|             Record ID | Field                | Meaning                                                           |
| --------------------: | -------------------- | ----------------------------------------------------------------- |
| GL-CONT-000-TRACE-001 | Source Group         | Broad source category                                             |
| GL-CONT-000-TRACE-002 | Source File          | Specific source document or file                                  |
| GL-CONT-000-TRACE-003 | Source Record ID     | Canonical source ID when available                                |
| GL-CONT-000-TRACE-004 | Prior Document Basis | README, ProjectOverview, VisionAndScope, SYSTEM_GOALS             |
| GL-CONT-000-TRACE-005 | User Decision Basis  | Explicit user-approved decision                                   |
| GL-CONT-000-TRACE-006 | Evidence Status      | direct, derived, user_decision, seed_low_detail, needs_validation |
| GL-CONT-000-TRACE-007 | Trace Notes          | Explanation of evidence strength or limitation                    |

### 13.3 Evidence Sufficiency Rule

A glossary entry is evidence-sufficient when:

1. the term has a clear source or project decision basis,
2. its category is declared,
3. its anti-collapse risks are declared where relevant,
4. its maturity is declared,
5. its use does not depend on unstated assumptions.

The Canonical Kernel states that evidence-backed answers must include source paths or joined canonical IDs, and that joins must use declared canonical keys. 

---

## 14. Relationship Model

### 14.1 Purpose

Terms are not isolated.

The glossary must capture relationships that later help with domain derivation, package derivation, C++ abstraction design, and coverage validation.

### 14.2 Relationship Types

|           Record ID | Relationship Type       | Meaning                                                |
| ------------------: | ----------------------- | ------------------------------------------------------ |
| GL-CONT-000-REL-001 | `related_to`            | General conceptual relation                            |
| GL-CONT-000-REL-002 | `depends_on`            | Term relies on another term’s meaning                  |
| GL-CONT-000-REL-003 | `enables`               | Term enables later concept or derivation               |
| GL-CONT-000-REL-004 | `governed_by`           | Term is governed by doctrine, contract, or source      |
| GL-CONT-000-REL-005 | `carried_by`            | Responsibility/object is carried by an entity          |
| GL-CONT-000-REL-006 | `controls`              | Entity controls or validates an object                 |
| GL-CONT-000-REL-007 | `must_not_confuse_with` | Anti-collapse relation                                 |
| GL-CONT-000-REL-008 | `alias_of`              | Alias maps to canonical term                           |
| GL-CONT-000-REL-009 | `external_to`           | Term belongs outside assembler ownership               |
| GL-CONT-000-REL-010 | `future_derivation_of`  | Term will be derived later from an established concept |

### 14.3 Relationship Integrity Rule

Relationships must not imply ownership unless ownership is explicitly defined.

For example:

|                Record ID | Incorrect Interpretation                                         | Correct Interpretation                                          |
| -----------------------: | ---------------------------------------------------------------- | --------------------------------------------------------------- |
| GL-CONT-000-REL-RULE-001 | Handoff Evidence means assembler owns downstream lifecycle       | Handoff evidence may preserve trace without lifecycle ownership |
| GL-CONT-000-REL-RULE-002 | Queue Slot Occupancy means envelope lifecycle ownership          | Occupancy records slot binding/state only                       |
| GL-CONT-000-REL-RULE-003 | Registry / Delivery Port means registry implementation ownership | It is an outbound contract surface                              |
| GL-CONT-000-REL-RULE-004 | Policy Object means policy executor                              | It is policy material or semantic governor                      |

---

## 15. Usage Rules

### 15.1 General Usage Rules

|          Record ID | Usage Rule                                                                 | Explanation                                                                 |
| -----------------: | -------------------------------------------------------------------------- | --------------------------------------------------------------------------- |
| GL-CONT-000-UR-001 | Use canonical terms in formal documents                                    | Aliases may appear only when explicitly mapped                              |
| GL-CONT-000-UR-002 | Use “boundary” only where governance limit exists                          | Avoid casual boundary language                                              |
| GL-CONT-000-UR-003 | Use “actor” only for responsibility-carrying entities                      | Do not call carriers or state objects actors                                |
| GL-CONT-000-UR-004 | Use “carrier” for objects that carry state/content                         | Do not imply self-executing behavior                                        |
| GL-CONT-000-UR-005 | Use “port” only for contract-facing surfaces                               | Do not promote port into final actor                                        |
| GL-CONT-000-UR-006 | Use “dependency” for architecture; use “include/import” for code mechanics | Prevents architectural relations from collapsing into source-code mechanics |
| GL-CONT-000-UR-007 | Use “semantic domain” for architecture-derived domains                     | Do not derive domains from folder categories                                |
| GL-CONT-000-UR-008 | Use “enablement” for capability family                                     | Do not treat enablement as implementation code                              |
| GL-CONT-000-UR-009 | Use “contract” as architectural law first                                  | Do not reduce contract to interface or template artifact                    |
| GL-CONT-000-UR-010 | Use “downstream” for post-handoff systems                                  | Do not imply assembler ownership after handoff                              |

### 15.2 Dependency Vocabulary Alignment

The glossary should preserve the vocabulary distinction between architectural dependency and code import mechanics. Prior dependency vocabulary guidance states that “dependency” should be used for architectural relation, while “import” should be limited to source-code import mechanics; it also cautions that “boundary” should only be used where a governance limit exists. 

---

## 16. Invalid Usage Model

### 16.1 Purpose

Invalid usage examples are required for high-risk terms because incorrect language can cause incorrect architecture.

### 16.2 Invalid Usage Classes

|          Record ID | Invalid Usage Class                | Example                                                       |
| -----------------: | ---------------------------------- | ------------------------------------------------------------- |
| GL-CONT-000-IU-001 | Actor Promotion                    | “The Log Level Envelope dispatches itself.”                   |
| GL-CONT-000-IU-002 | Port Promotion                     | “Registry / Delivery Port is the final handoff actor.”        |
| GL-CONT-000-IU-003 | Carrier Ownership Expansion        | “Envelope Slot Occupancy owns the envelope lifecycle.”        |
| GL-CONT-000-IU-004 | Boundary Leakage                   | “Assembler owns registry records after handoff.”              |
| GL-CONT-000-IU-005 | Broker Collapse                    | “Queue Container is the message broker.”                      |
| GL-CONT-000-IU-006 | Policy Collapse                    | “Policy Object executes the policy.”                          |
| GL-CONT-000-IU-007 | Metadata/Policy Collapse           | “Metadata Injector is a policy host.”                         |
| GL-CONT-000-IU-008 | Contract/Runtime Collapse          | “Template Contract is a runtime COM interface.”               |
| GL-CONT-000-IU-009 | Domain/Folder Collapse             | “templates/ is a semantic domain.”                            |
| GL-CONT-000-IU-010 | Enablement/Implementation Collapse | “Enablement family is the implementation module.”             |
| GL-CONT-000-IU-011 | Evidence-Free Assertion            | “This term is canonical because it sounds correct.”           |
| GL-CONT-000-IU-012 | Alias Drift                        | “Log Envelope and Log Level Envelope are unrelated concepts.” |

---

## 17. Representation Boundary

### 17.1 Purpose

The glossary must prepare for CSV and JSON representations without letting those representations control the meaning too early.

### 17.2 Content vs Representation

|           Record ID | Layer                   | Meaning                                                                        |
| ------------------: | ----------------------- | ------------------------------------------------------------------------------ |
| GL-CONT-000-REP-001 | Content Layer           | Human-authored definitions, roles, anti-collapse rules, usage rules            |
| GL-CONT-000-REP-002 | Markdown Representation | Primary readable governance document                                           |
| GL-CONT-000-REP-003 | CSV Representation      | Later sortable/queryable tabular export                                        |
| GL-CONT-000-REP-004 | JSON Representation     | Later structured machine-readable record export                                |
| GL-CONT-000-REP-005 | JSON Schema             | Later formal validation schema                                                 |
| GL-CONT-000-REP-006 | Population Pack         | Later act of filling CSV/JSON from stabilized content                          |
| GL-CONT-000-REP-007 | Validation Pack         | Later act of checking coverage, consistency, aliases, trace, and anti-collapse |

### 17.3 Representation Rule

```text
The glossary content defines meaning.
CSV and JSON represent meaning.
Schemas validate representation.
Population fills representation.
Validation checks coverage and consistency.
```

### 17.4 Deferral Rule

This pack does not finalize CSV or JSON schemas.

It only ensures that content entries contain enough structured fields to make later representation possible.

---

## 18. Future Schema Readiness Requirements

### 18.1 Purpose

Even though schemas will be defined later, the content model must be schema-aware.

### 18.2 Required Future Representation Support

|           Record ID | Future Representation Need | Content Field That Enables It                                           |
| ------------------: | -------------------------- | ----------------------------------------------------------------------- |
| GL-CONT-000-FSR-001 | CSV term inventory         | Term ID, Canonical Term, Family, Category, Maturity                     |
| GL-CONT-000-FSR-002 | CSV anti-collapse index    | Must Not Be Confused With, Guard IDs, Invalid Usage                     |
| GL-CONT-000-FSR-003 | CSV alias map              | Alias Term, Canonical Term, Alias Type, Usage Rule                      |
| GL-CONT-000-FSR-004 | CSV source trace map       | Source Group, Source File, Source Record ID, Evidence Status            |
| GL-CONT-000-FSR-005 | JSON term record           | Full entry schema                                                       |
| GL-CONT-000-FSR-006 | JSON relationship graph    | Related Terms, Depends On, Enables, Alias Of                            |
| GL-CONT-000-FSR-007 | Validation report          | Entry Maturity, Evidence Status, Missing Fields, Anti-Collapse Coverage |
| GL-CONT-000-FSR-008 | Domain derivation support  | Category, Ownership Scope, Related Terms, Future Derivation Notes       |
| GL-CONT-000-FSR-009 | C++ derivation support     | Contract relation, Implementation Direction, Future Derivation Notes    |
| GL-CONT-000-FSR-010 | Roadmap dependency support | Depends On, Enables, Source Trace, Maturity                             |

---

## 19. Glossary Pack Dependency Rules

### 19.1 Pack Dependency Principle

Glossary packs must follow dependency order.

Governance comes before content.

Content comes before representation.

Representation schemas come before population.

Population comes before validation reports.

### 19.2 Pack Dependency Table

|           Record ID | Pack        | Depends On                                      | Enables                                 |
| ------------------: | ----------- | ----------------------------------------------- | --------------------------------------- |
| GL-CONT-000-DEP-001 | GL-CONT-000 | Foundational docs, Canonical Kernel, ID grammar | All glossary content packs              |
| GL-CONT-000-DEP-002 | GL-CONT-001 | GL-CONT-000                                     | System identity entries                 |
| GL-CONT-000-DEP-003 | GL-CONT-002 | GL-CONT-000                                     | Boundary and external context entries   |
| GL-CONT-000-DEP-004 | GL-CONT-003 | GL-CONT-000                                     | Internal entity entries                 |
| GL-CONT-000-DEP-005 | GL-CONT-004 | GL-CONT-000                                     | Governed object and carrier entries     |
| GL-CONT-000-DEP-006 | GL-CONT-005 | GL-CONT-000                                     | Runtime and queue entries               |
| GL-CONT-000-DEP-007 | GL-CONT-006 | GL-CONT-000                                     | Contract and type entries               |
| GL-CONT-000-DEP-008 | GL-CONT-007 | GL-CONT-000                                     | Responsibility and traceability entries |
| GL-CONT-000-DEP-009 | GL-CONT-008 | GL-CONT-000                                     | Policy, metadata, timestamp entries     |
| GL-CONT-000-DEP-010 | GL-CONT-009 | GL-CONT-000                                     | Dispatcher, handoff, exclusion entries  |
| GL-CONT-000-DEP-011 | GL-CONT-010 | GL-CONT-000                                     | C++ and future derivation entries       |
| GL-CONT-000-DEP-012 | GL-SCHEMA-* | Content entry model                             | CSV/JSON schema definitions             |
| GL-CONT-000-DEP-013 | GL-POP-*    | Content packs and schemas                       | Populated CSV/JSON records              |
| GL-CONT-000-DEP-014 | GL-VAL-*    | Populated content and source trace              | Coverage and validation reports         |

---

## 20. Validation Expectations for Later Packs

### 20.1 Purpose

This pack establishes what later glossary packs must be checked against.

### 20.2 Validation Rules

|           Record ID | Validation Rule                                                  | Applies To                          |
| ------------------: | ---------------------------------------------------------------- | ----------------------------------- |
| GL-CONT-000-VAL-001 | Every term must have a Term ID                                   | All entries                         |
| GL-CONT-000-VAL-002 | Every term must have a family and category                       | All entries                         |
| GL-CONT-000-VAL-003 | Every major term must include anti-collapse notes                | Major/high-risk entries             |
| GL-CONT-000-VAL-004 | Every alias must map to a canonical term                         | Alias entries                       |
| GL-CONT-000-VAL-005 | Every seed must declare missing detail                           | Seed entries                        |
| GL-CONT-000-VAL-006 | Every future derivation term must avoid premature implementation | Future derivation entries           |
| GL-CONT-000-VAL-007 | Every source-backed claim should cite source trace               | Source-backed entries               |
| GL-CONT-000-VAL-008 | No term may change category silently                             | All entries                         |
| GL-CONT-000-VAL-009 | No entry may invent canonical source IDs                         | All entries                         |
| GL-CONT-000-VAL-010 | No representation schema may override content meaning            | Schema packs                        |
| GL-CONT-000-VAL-011 | No CSV/JSON population may introduce new terms silently          | Population packs                    |
| GL-CONT-000-VAL-012 | Anti-collapse guards must be preserved in exports                | Representation and validation packs |

---

## 21. Glossary Governance Invariants

|           Record ID | Invariant                                  | Meaning                                                               |
| ------------------: | ------------------------------------------ | --------------------------------------------------------------------- |
| GL-CONT-000-INV-001 | The glossary is normative                  | It governs terminology in later documents                             |
| GL-CONT-000-INV-002 | The glossary is not merely descriptive     | It prevents incorrect usage                                           |
| GL-CONT-000-INV-003 | The glossary is anti-collapse aware        | It protects guarded distinctions                                      |
| GL-CONT-000-INV-004 | The glossary is source-trace aware         | It records evidence status where possible                             |
| GL-CONT-000-INV-005 | The glossary is schema-ready               | It is designed for later CSV/JSON representation                      |
| GL-CONT-000-INV-006 | The glossary is not a schema pack          | It does not finalize representation formats yet                       |
| GL-CONT-000-INV-007 | The glossary is not an implementation pack | It does not define final code units                                   |
| GL-CONT-000-INV-008 | The glossary is inventory-oriented         | It includes marginal and low-detail elements as seeds                 |
| GL-CONT-000-INV-009 | The glossary is derivation-enabling        | It supports future domains, packages, templates, and processing units |
| GL-CONT-000-INV-010 | The glossary is roadmap-enabling           | It must be complete enough for roadmap dependency planning            |

---

## 22. Exit Criteria

This pack is complete when the following criteria are satisfied.

|            Record ID | Exit Criterion                                            | Status Target |
| -------------------: | --------------------------------------------------------- | ------------- |
| GL-CONT-000-EXIT-001 | Glossary purpose is defined                               | Required      |
| GL-CONT-000-EXIT-002 | Glossary scope is defined                                 | Required      |
| GL-CONT-000-EXIT-003 | Term families are defined                                 | Required      |
| GL-CONT-000-EXIT-004 | Architectural categories are defined                      | Required      |
| GL-CONT-000-EXIT-005 | Entry maturity model is defined                           | Required      |
| GL-CONT-000-EXIT-006 | Markdown entry schema is defined                          | Required      |
| GL-CONT-000-EXIT-007 | Term ID model is defined                                  | Required      |
| GL-CONT-000-EXIT-008 | Anti-collapse model is defined                            | Required      |
| GL-CONT-000-EXIT-009 | Alias model is defined                                    | Required      |
| GL-CONT-000-EXIT-010 | Source trace model is defined                             | Required      |
| GL-CONT-000-EXIT-011 | Relationship model is defined                             | Required      |
| GL-CONT-000-EXIT-012 | Usage and invalid usage rules are defined                 | Required      |
| GL-CONT-000-EXIT-013 | Content vs representation boundary is defined             | Required      |
| GL-CONT-000-EXIT-014 | Later schema/population/validation boundaries are defined | Required      |
| GL-CONT-000-EXIT-015 | Later content packs can use this governance model         | Required      |

---

## 23. Summary

`GL-CONT-000 — Glossary Governance & Entry Model Pack` establishes the rules for all later glossary work.

It defines the glossary as:

```text
Controlled Vocabulary
+ Anti-Collapse Glossary
+ System Element Inventory
+ Future Derivation Support Layer
```

It ensures that later glossary packs will:

1. include canonical and low-detail terms,
2. classify every term by family and architectural category,
3. distinguish content from representation,
4. preserve anti-collapse rules,
5. record aliases and legacy terms,
6. preserve source trace where possible,
7. avoid inventing canonical IDs,
8. prepare for later CSV and JSON representation,
9. support semantic domain derivation,
10. support C++ abstraction and processing-unit derivation,
11. support roadmap dependency planning.

This pack enables the next content pack:

```text
GL-CONT-001 — Core System Identity & Phase Terms Pack
```

