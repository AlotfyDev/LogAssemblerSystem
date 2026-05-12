
# GL-SCHEMA-001 — Markdown Entry Schema

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-SCHEMA-001-DOC-001 | Document Title | GL-SCHEMA-001_Markdown_Entry_Schema.md |
| GL-SCHEMA-001-DOC-002 | Formal Version | Formal Draft V1 |
| GL-SCHEMA-001-DOC-003 | Project | Assembler System |
| GL-SCHEMA-001-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-SCHEMA-001-DOC-005 | Document Type | Schema / Representation Definition Pack |
| GL-SCHEMA-001-DOC-006 | Language | English |
| GL-SCHEMA-001-DOC-007 | Status | Formal Draft V1 |
| GL-SCHEMA-001-DOC-008 | Depends On | GL-CONT-000 through GL-CONT-010, Unified Glossary Content Consolidation Pack, GL-CONS-002, GL-CONS-003 |
| GL-SCHEMA-001-DOC-009 | Scope | Markdown entry structure, required sections, optional sections, field order, table grammar, source trace block, anti-collapse block, validation-readiness rules |
| GL-SCHEMA-001-DOC-010 | Excluded From This Pack | CSV schema, JSON schema, JSON Schema draft syntax, population of all term entries, final glossary text generation, database schema |
| GL-SCHEMA-001-DOC-011 | Enables | GL-SCHEMA-002_CSV_Schema_Definitions.md, GL-SCHEMA-003_JSON_Schema_Definitions.md, GL-SCHEMA-004_Representation_Mapping.md, future Glossary.md assembly |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical Markdown entry schema for glossary terms in the Assembler System.

It answers the question:

```text
How must each canonical glossary term be written in Markdown so that it remains
human-readable, source-traceable, anti-collapse-safe, and later derivable into
CSV, JSON, validation matrices, and database rows?
````

This pack does not populate the final glossary.

It defines the Markdown structure that future glossary entries must follow.

### 2.2 Why Markdown Schema Comes Before CSV and JSON

Markdown is the human-governed canonical authoring representation.

CSV and JSON are downstream machine-readable representations.

Therefore, the sequence is:

```text
Canonical meaning
→ Markdown entry schema
→ CSV schema
→ JSON schema
→ representation mapping
→ population
→ validation
```

Markdown must preserve semantic richness before the content is normalized into tabular or object-based structures.

### 2.3 Schema Role

The Markdown entry schema serves five roles:

|              Record ID | Role                         | Description                                                       |
| ---------------------: | ---------------------------- | ----------------------------------------------------------------- |
| GL-SCHEMA-001-ROLE-001 | Human Authoring Schema       | Defines how maintainers write canonical glossary entries          |
| GL-SCHEMA-001-ROLE-002 | Semantic Preservation Schema | Preserves definition, role, boundaries, and anti-collapse meaning |
| GL-SCHEMA-001-ROLE-003 | Traceability Schema          | Requires source trace and evidence status where available         |
| GL-SCHEMA-001-ROLE-004 | Representation Source        | Provides the source structure for CSV and JSON derivation         |
| GL-SCHEMA-001-ROLE-005 | Validation Preparation       | Makes future coverage and consistency checks possible             |

---

## 3. Markdown Schema Principles

### 3.1 Meaning-First Principle

```text id="gl-schema-001-meaning-first"
Markdown glossary entries must preserve meaning before representation.
```

A Markdown entry must be understandable as documentation before it is transformed into CSV rows or JSON objects.

### 3.2 Stable Field Order Principle

```text id="gl-schema-001-field-order"
All canonical entries should use the same major section order unless a term type
explicitly allows a reduced entry profile.
```

Stable field order enables:

1. review consistency,
2. parser readiness,
3. source trace extraction,
4. future CSV mapping,
5. future JSON mapping.

### 3.3 Anti-Collapse Inclusion Principle

```text id="gl-schema-001-anti-collapse"
Every canonical_full term and every high-risk canonical_partial term must include
a Must Not Be Confused With section.
```

This continues the anti-collapse requirement already established across the content packs.

### 3.4 Source Trace Inclusion Principle

```text id="gl-schema-001-source-trace"
Every canonical glossary entry should include Source Trace.
If the source is incomplete, the entry must explicitly mark its evidence status.
```

### 3.5 No Hidden Implementation Principle

```text id="gl-schema-001-no-hidden-implementation"
A Markdown glossary entry must not silently define final implementation classes,
packages, functions, database tables, or runtime algorithms.
```

Implementation direction may be documented as future derivation, but not as final code structure.

---

## 4. Entry Profiles

Not every term requires the same amount of detail.

This schema defines five entry profiles.

|              Record ID | Entry Profile           | Applies To                | Required Detail Level                                 |
| ---------------------: | ----------------------- | ------------------------- | ----------------------------------------------------- |
| GL-SCHEMA-001-PROF-001 | Full Canonical Entry    | `canonical_full` terms    | Complete schema                                       |
| GL-SCHEMA-001-PROF-002 | Partial Canonical Entry | `canonical_partial` terms | Core schema plus known constraints                    |
| GL-SCHEMA-001-PROF-003 | Seed Entry              | `seed` terms              | Minimal identity plus source/evidence status          |
| GL-SCHEMA-001-PROF-004 | Alias Entry             | `alias` terms             | Alias mapping plus canonical target                   |
| GL-SCHEMA-001-PROF-005 | Future Derivation Entry | `future_derivation` terms | Meaning, derivation gate, non-prematurity constraints |

---

## 5. Full Canonical Markdown Entry Schema

### 5.1 Required Section Order

A `canonical_full` term entry must use the following section order.

```text id="gl-schema-001-full-entry-order"
### <TERM_ID> — <Canonical Term>

| Field | Value |
|---|---|
| Term ID | ... |
| Canonical Term | ... |
| Family | ... |
| Category | ... |
| Ownership Scope | ... |
| Entry Maturity | ... |
| Evidence Status | ... |

#### Definition

...

#### Architectural Role

...

#### Must Not Be Confused With

...

#### Valid Usage

...

#### Invalid Usage

...

#### Related Terms

...

#### Source Trace

...
```

### 5.2 Required Fields Table

|               Record ID | Field           | Required | Description                               |
| ----------------------: | --------------- | -------- | ----------------------------------------- |
| GL-SCHEMA-001-FIELD-001 | Term ID         | Yes      | Stable canonical glossary term identifier |
| GL-SCHEMA-001-FIELD-002 | Canonical Term  | Yes      | Human-readable canonical term             |
| GL-SCHEMA-001-FIELD-003 | Family          | Yes      | One or more family codes                  |
| GL-SCHEMA-001-FIELD-004 | Category        | Yes      | One or more architectural categories      |
| GL-SCHEMA-001-FIELD-005 | Ownership Scope | Yes      | Ownership or authority scope              |
| GL-SCHEMA-001-FIELD-006 | Entry Maturity  | Yes      | Maturity status                           |
| GL-SCHEMA-001-FIELD-007 | Evidence Status | Yes      | Evidence classification                   |

### 5.3 Required Narrative Sections

|             Record ID | Section                   | Required               | Purpose                                              |
| --------------------: | ------------------------- | ---------------------- | ---------------------------------------------------- |
| GL-SCHEMA-001-SEC-001 | Definition                | Yes                    | Defines the term’s canonical meaning                 |
| GL-SCHEMA-001-SEC-002 | Architectural Role        | Yes                    | Explains the term’s role inside the Assembler System |
| GL-SCHEMA-001-SEC-003 | Must Not Be Confused With | Yes for canonical_full | Lists anti-collapse protections                      |
| GL-SCHEMA-001-SEC-004 | Valid Usage               | Yes                    | Shows correct use in documentation                   |
| GL-SCHEMA-001-SEC-005 | Invalid Usage             | Yes                    | Shows prohibited or misleading use                   |
| GL-SCHEMA-001-SEC-006 | Related Terms             | Yes                    | Links the term to adjacent vocabulary                |
| GL-SCHEMA-001-SEC-007 | Source Trace              | Yes                    | Preserves source authority and evidence basis        |

---

## 6. Partial Canonical Entry Schema

### 6.1 Purpose

A `canonical_partial` entry is used when the term is accepted as canonical but not yet fully detailed.

Partial entries prevent loss of important terms while avoiding false precision.

### 6.2 Required Structure

```text id="gl-schema-001-partial-entry"
### <TERM_ID> — <Canonical Term>

| Field | Value |
|---|---|
| Term ID | ... |
| Canonical Term | ... |
| Family | ... |
| Category | ... |
| Ownership Scope | ... |
| Entry Maturity | canonical_partial |
| Evidence Status | ... |

#### Working Definition

...

#### Known Architectural Role

...

#### Known Constraints

...

#### Open Clarifications

...

#### Related Terms

...

#### Source Trace

...
```

### 6.3 Partial Entry Rules

|              Record ID | Rule                            | Description                                                        |
| ---------------------: | ------------------------------- | ------------------------------------------------------------------ |
| GL-SCHEMA-001-PART-001 | Must not imply completeness     | Partial entries must not read as final definitions                 |
| GL-SCHEMA-001-PART-002 | Must preserve known constraints | Known anti-collapse or authority constraints must be stated        |
| GL-SCHEMA-001-PART-003 | Must list open clarifications   | Missing details must be visible                                    |
| GL-SCHEMA-001-PART-004 | Must carry evidence status      | Evidence weakness must be explicit                                 |
| GL-SCHEMA-001-PART-005 | May later become full           | A partial entry may be promoted to canonical_full after validation |

---

## 7. Seed Entry Schema

### 7.1 Purpose

A `seed` entry is used for a referenced system element that must not be discarded even though its current details are limited.

### 7.2 Required Structure

```text id="gl-schema-001-seed-entry"
### <TERM_ID> — <Canonical Term>

| Field | Value |
|---|---|
| Term ID | ... |
| Canonical Term | ... |
| Family | ... |
| Category | ... |
| Ownership Scope | unknown / governed / pending |
| Entry Maturity | seed |
| Evidence Status | needs_validation |

#### Seed Description

...

#### Why Preserved

...

#### Known Source

...

#### Required Clarification

...
```

### 7.3 Seed Entry Rules

|              Record ID | Rule                         | Description                                                        |
| ---------------------: | ---------------------------- | ------------------------------------------------------------------ |
| GL-SCHEMA-001-SEED-001 | Preserve referenced elements | Referenced terms must not be lost only because they are incomplete |
| GL-SCHEMA-001-SEED-002 | Do not overdefine            | Seed entries must not invent full semantics                        |
| GL-SCHEMA-001-SEED-003 | Require clarification        | Seed entries must identify what needs validation                   |
| GL-SCHEMA-001-SEED-004 | Must include known source    | Even weak source evidence must be recorded                         |
| GL-SCHEMA-001-SEED-005 | May be deprecated            | A seed may be removed or merged after formal validation            |

---

## 8. Alias Entry Schema

### 8.1 Purpose

An `alias` entry is used when a legacy, shorthand, or alternate name maps to a canonical term.

Alias entries prevent hidden semantic forks.

### 8.2 Required Structure

```text id="gl-schema-001-alias-entry"
### <TERM_ID> — <Alias Term>

| Field | Value |
|---|---|
| Term ID | ... |
| Alias Term | ... |
| Canonical Target Term ID | ... |
| Canonical Target Term | ... |
| Family | ALIAS / ... |
| Category | alias |
| Entry Maturity | alias |
| Evidence Status | legacy_alias |

#### Alias Meaning

...

#### Canonical Mapping

...

#### Valid Usage

...

#### Invalid Usage

...

#### Source Trace

...
```

### 8.3 Alias Rules

|               Record ID | Rule                                 | Description                                                  |
| ----------------------: | ------------------------------------ | ------------------------------------------------------------ |
| GL-SCHEMA-001-ALIAS-001 | Alias must point to canonical target | Alias entries cannot stand as independent canonical meanings |
| GL-SCHEMA-001-ALIAS-002 | Alias must not create fork           | Alias wording must not introduce a second concept            |
| GL-SCHEMA-001-ALIAS-003 | Alias usage should be constrained    | Formal docs should prefer the canonical term                 |
| GL-SCHEMA-001-ALIAS-004 | Legacy source must be recorded       | Alias origin must be traceable where possible                |

---

## 9. Future Derivation Entry Schema

### 9.1 Purpose

A `future_derivation` entry is used for implementation-facing or schema-facing concepts that are valid only as later derivation targets.

Examples include:

1. Semantic Domain,
2. Package Candidate,
3. Processing Unit Candidate,
4. Abstract C++ Layer,
5. Filesystem Representation,
6. Compliance Matrix.

### 9.2 Required Structure

```text id="gl-schema-001-future-entry"
### <TERM_ID> — <Canonical Term>

| Field | Value |
|---|---|
| Term ID | ... |
| Canonical Term | ... |
| Family | DER / ... |
| Category | future_derivation |
| Ownership Scope | future / governed |
| Entry Maturity | canonical_full / canonical_partial |
| Evidence Status | derived / user_decision / needs_validation |

#### Definition

...

#### Future Derivation Role

...

#### Derivation Preconditions

...

#### Must Not Be Confused With

...

#### Invalid Premature Use

...

#### Related Terms

...

#### Source Trace

...
```

### 9.3 Future Derivation Rules

|             Record ID | Rule                                  | Description                                                                              |
| --------------------: | ------------------------------------- | ---------------------------------------------------------------------------------------- |
| GL-SCHEMA-001-FUT-001 | Must declare derivation preconditions | Future artifacts must state what must exist first                                        |
| GL-SCHEMA-001-FUT-002 | Must prevent premature implementation | Future terms must not become classes/packages directly                                   |
| GL-SCHEMA-001-FUT-003 | Must trace to architecture            | Future terms must trace to contracts, responsibilities, obligations, or derivation rules |
| GL-SCHEMA-001-FUT-004 | Must preserve authority exclusions    | Future implementation must not absorb excluded downstream authority                      |

---

## 10. Controlled Field Values

### 10.1 Entry Maturity Values

| Value               | Meaning                                                                 |
| ------------------- | ----------------------------------------------------------------------- |
| `canonical_full`    | Fully accepted canonical entry with complete definition and constraints |
| `canonical_partial` | Accepted term with incomplete detail                                    |
| `seed`              | Preserved referenced term requiring validation                          |
| `alias`             | Non-canonical wording mapped to canonical target                        |
| `future_derivation` | Future implementation/schema/validation derivation term                 |

### 10.2 Evidence Status Values

| Value                     | Meaning                                             |
| ------------------------- | --------------------------------------------------- |
| `direct`                  | Term appears directly in source                     |
| `derived`                 | Term is derived from source meaning                 |
| `user_decision`           | Term or rule is based on explicit user decision     |
| `legacy_alias`            | Term is a legacy or alternate name                  |
| `inferred`                | Term is inferred and needs review                   |
| `needs_validation`        | Term is retained pending validation                 |
| `consolidation_authority` | Term stabilized by consolidation pack               |
| `validation_authority`    | Term stabilized by validation or anti-collapse rule |

### 10.3 Ownership Scope Values

| Value                        | Meaning                                       |
| ---------------------------- | --------------------------------------------- |
| `assembler_owned`            | Owned by the Assembler System                 |
| `assembler_owned / governed` | Owned but constrained by governance rules     |
| `external`                   | External to Assembler ownership               |
| `downstream / not_owned`     | Downstream and explicitly not assembler-owned |
| `governed`                   | Governed by glossary or architectural rule    |
| `future`                     | Future derivation area                        |
| `not_owned`                  | Explicitly excluded from ownership            |
| `pending`                    | Requires clarification                        |

### 10.4 Family Codes

| Code    | Meaning                          |
| ------- | -------------------------------- |
| `SYS`   | System Identity                  |
| `DOC`   | Documentation / Phase            |
| `BND`   | Boundary                         |
| `EXT`   | External Context                 |
| `ENT`   | Internal Entity                  |
| `OBJ`   | Governed Object                  |
| `RUN`   | Runtime                          |
| `CON`   | Contract                         |
| `POL`   | Policy / Metadata / Governance   |
| `TRC`   | Traceability                     |
| `CPP`   | C++ Direction                    |
| `EXC`   | Exclusion / Authority Closure    |
| `ALIAS` | Alias                            |
| `DER`   | Future Derivation                |
| `GUARD` | Anti-Collapse / Governance Guard |
| `DOM`   | Semantic Domain                  |

---

## 11. Source Trace Block Schema

### 11.1 Source Trace Markdown Table

Each source trace block should use the following table when possible.

```markdown id="gl-schema-001-source-trace-template"
#### Source Trace

| Source Type | Source | Trace Relation | Evidence Status | Source Summary |
|---|---|---|---|---|
| ... | ... | ... | ... | ... |
```

### 11.2 Source Trace Fields

|             Record ID | Field           | Required | Description                                                  |
| --------------------: | --------------- | -------- | ------------------------------------------------------------ |
| GL-SCHEMA-001-SRC-001 | Source Type     | Yes      | Type of source authority                                     |
| GL-SCHEMA-001-SRC-002 | Source          | Yes      | Source document, pack, goal, rule, or decision               |
| GL-SCHEMA-001-SRC-003 | Trace Relation  | Yes      | direct / derived / supports / constrains / aliases / enables |
| GL-SCHEMA-001-SRC-004 | Evidence Status | Yes      | Evidence classification                                      |
| GL-SCHEMA-001-SRC-005 | Source Summary  | Yes      | Short explanation of source contribution                     |

### 11.3 Source Trace Rules

|                  Record ID | Rule                                           | Description                                                                               |
| -------------------------: | ---------------------------------------------- | ----------------------------------------------------------------------------------------- |
| GL-SCHEMA-001-SRC-RULE-001 | No empty source trace                          | Canonical entries must not omit source trace                                              |
| GL-SCHEMA-001-SRC-RULE-002 | Weak evidence must be visible                  | Inferred or pending evidence must be declared                                             |
| GL-SCHEMA-001-SRC-RULE-003 | Consolidation is not enough for critical terms | Critical terms should trace back to foundational or content packs, not only consolidation |
| GL-SCHEMA-001-SRC-RULE-004 | Alias must trace origin                        | Alias entries must preserve legacy source basis                                           |
| GL-SCHEMA-001-SRC-RULE-005 | Future derivation must trace preconditions     | Future terms must trace back to contract/responsibility/derivation chain sources          |

---

## 12. Anti-Collapse Block Schema

### 12.1 Standard Anti-Collapse Section

```markdown id="gl-schema-001-anti-collapse-template"
#### Must Not Be Confused With

1. ...
2. ...
3. ...
```

### 12.2 Anti-Collapse Rules

|            Record ID | Rule                         | Description                                                              |
| -------------------: | ---------------------------- | ------------------------------------------------------------------------ |
| GL-SCHEMA-001-AC-001 | Use explicit list            | Anti-collapse targets must be visible as list items                      |
| GL-SCHEMA-001-AC-002 | Include adjacent concepts    | Terms close in the runtime path must be listed if confusion is likely    |
| GL-SCHEMA-001-AC-003 | Include ownership risks      | Downstream ownership confusion must be listed for boundary/handoff terms |
| GL-SCHEMA-001-AC-004 | Include implementation risks | Future derivation terms must prevent class/package/function collapse     |
| GL-SCHEMA-001-AC-005 | Map later to validation      | Each item may later become anti-collapse validation row                  |

---

## 13. Usage Block Schema

### 13.1 Valid Usage

```markdown id="gl-schema-001-valid-usage-template"
#### Valid Usage

- “...”
- “...”
```

### 13.2 Invalid Usage

```markdown id="gl-schema-001-invalid-usage-template"
#### Invalid Usage

- “...”
- “...”
```

### 13.3 Usage Rules

|               Record ID | Rule                                        | Description                                                           |
| ----------------------: | ------------------------------------------- | --------------------------------------------------------------------- |
| GL-SCHEMA-001-USAGE-001 | Usage examples must be sentence-like        | Examples should show realistic documentation use                      |
| GL-SCHEMA-001-USAGE-002 | Invalid usage must expose common errors     | Invalid examples should reflect likely category or ownership collapse |
| GL-SCHEMA-001-USAGE-003 | Usage must not introduce new meaning        | Examples clarify; they do not define extra semantics                  |
| GL-SCHEMA-001-USAGE-004 | Invalid usage must align with anti-collapse | Invalid examples should correspond to stated anti-collapse risks      |

---

## 14. Related Terms Block Schema

### 14.1 Standard Related Terms Section

```markdown id="gl-schema-001-related-terms-template"
#### Related Terms

- GL-XXX-000 — Term Name
- GL-YYY-000 — Term Name
```

### 14.2 Related Terms Rules

|                 Record ID | Rule                                 | Description                                                                  |
| ------------------------: | ------------------------------------ | ---------------------------------------------------------------------------- |
| GL-SCHEMA-001-RELTERM-001 | Use Term ID where available          | Related terms should include IDs                                             |
| GL-SCHEMA-001-RELTERM-002 | Do not use vague links               | Related terms must be meaningful semantic neighbors                          |
| GL-SCHEMA-001-RELTERM-003 | Include producer/carrier relations   | Actor/object pairs should cross-reference each other                         |
| GL-SCHEMA-001-RELTERM-004 | Include boundary/authority relations | Boundary and handoff terms should cross-reference exclusions                 |
| GL-SCHEMA-001-RELTERM-005 | Avoid excessive relation lists       | Related terms should support understanding, not duplicate the whole glossary |

---

## 15. Markdown Parsing Readiness

### 15.1 Heading Grammar

| Heading Level | Meaning               |
| ------------: | --------------------- |
|           `#` | Pack title            |
|          `##` | Pack section          |
|         `###` | Term entry            |
|        `####` | Term entry subsection |

### 15.2 Term Heading Pattern

```text id="gl-schema-001-heading-pattern"
### <TERM_ID> — <Canonical Term>
```

Example:

```markdown
### GL-OBJ-001 — Log Level Envelope
```

### 15.3 Table Rules

|               Record ID | Rule                             | Description                                           |
| ----------------------: | -------------------------------- | ----------------------------------------------------- |
| GL-SCHEMA-001-TABLE-001 | Use two-column field table       | Term metadata must use `Field / Value` table          |
| GL-SCHEMA-001-TABLE-002 | Use pipe tables only             | Markdown tables should be standard pipe tables        |
| GL-SCHEMA-001-TABLE-003 | Avoid nested tables              | Nested tables reduce parser stability                 |
| GL-SCHEMA-001-TABLE-004 | Preserve exact field names       | Field names must match schema labels                  |
| GL-SCHEMA-001-TABLE-005 | Use slash-separated multi-values | Multiple family/category values may use `/` separator |

---

## 16. Markdown-to-Representation Readiness

### 16.1 CSV Derivation Targets

The following Markdown fields should map cleanly to CSV columns:

| Markdown Field            | CSV Target                                      |
| ------------------------- | ----------------------------------------------- |
| Term ID                   | `term_id`                                       |
| Canonical Term            | `canonical_term`                                |
| Family                    | `family_codes`                                  |
| Category                  | `categories`                                    |
| Ownership Scope           | `ownership_scope`                               |
| Entry Maturity            | `entry_maturity`                                |
| Evidence Status           | `evidence_status`                               |
| Definition                | `definition`                                    |
| Architectural Role        | `architectural_role`                            |
| Must Not Be Confused With | separate anti-collapse table or delimited field |
| Valid Usage               | usage examples table                            |
| Invalid Usage             | usage examples table                            |
| Related Terms             | relation table                                  |
| Source Trace              | source trace table                              |

### 16.2 JSON Derivation Targets

The following Markdown sections should map to JSON objects or arrays:

| Markdown Section          | JSON Target                                  |
| ------------------------- | -------------------------------------------- |
| Field table               | `term.metadata`                              |
| Definition                | `term.definition`                            |
| Architectural Role        | `term.architectural_role`                    |
| Must Not Be Confused With | `term.anti_collapse.must_not_confuse_with[]` |
| Valid Usage               | `term.usage.valid[]`                         |
| Invalid Usage             | `term.usage.invalid[]`                       |
| Related Terms             | `term.related_terms[]`                       |
| Source Trace              | `term.source_traces[]`                       |

---

## 17. Validation Rules

### 17.1 Entry-Level Validation

|               Rule ID | Validation Rule                                               | Severity |
| --------------------: | ------------------------------------------------------------- | -------- |
| GL-SCHEMA-001-VAL-001 | canonical_full entry must include required metadata fields    | Critical |
| GL-SCHEMA-001-VAL-002 | canonical_full entry must include Definition                  | Critical |
| GL-SCHEMA-001-VAL-003 | canonical_full entry must include Architectural Role          | High     |
| GL-SCHEMA-001-VAL-004 | canonical_full entry must include Must Not Be Confused With   | High     |
| GL-SCHEMA-001-VAL-005 | canonical_full entry must include Source Trace                | Critical |
| GL-SCHEMA-001-VAL-006 | alias entry must include canonical target                     | Critical |
| GL-SCHEMA-001-VAL-007 | seed entry must include Required Clarification                | Medium   |
| GL-SCHEMA-001-VAL-008 | future_derivation entry must include Derivation Preconditions | High     |
| GL-SCHEMA-001-VAL-009 | Term heading must match `<TERM_ID> — <Canonical Term>`        | High     |
| GL-SCHEMA-001-VAL-010 | Field names must match schema vocabulary                      | High     |

### 17.2 Cross-Entry Validation

|                Rule ID | Validation Rule                                                           | Severity |
| ---------------------: | ------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-001-XVAL-001 | Related Term IDs must resolve to known terms or seeds                     | High     |
| GL-SCHEMA-001-XVAL-002 | Alias target must resolve to canonical term                               | Critical |
| GL-SCHEMA-001-XVAL-003 | Anti-collapse target should resolve to known term, category, or exclusion | High     |
| GL-SCHEMA-001-XVAL-004 | Source Trace source should resolve to known source index entry            | High     |
| GL-SCHEMA-001-XVAL-005 | Family codes must be known controlled values                              | High     |
| GL-SCHEMA-001-XVAL-006 | Entry maturity must be known controlled value                             | Critical |
| GL-SCHEMA-001-XVAL-007 | Evidence status must be known controlled value                            | Critical |

---

## 18. Example Full Entry

```markdown id="gl-schema-001-example-full-entry"
### GL-OBJ-001 — Log Level Envelope

| Field | Value |
|---|---|
| Term ID | GL-OBJ-001 |
| Canonical Term | Log Level Envelope |
| Family | OBJ |
| Category | carrier_object / governed_object |
| Ownership Scope | assembler_owned / transferable |
| Entry Maturity | canonical_full |
| Evidence Status | direct / user_decision / derived |

#### Definition

The Log Level Envelope is the authoritative assembler-side carrier object produced by the Envelope Assembler after governed content has passed through the required preparation path.

#### Architectural Role

The Log Level Envelope carries assembler-prepared content and associated governance material through assembler-side runtime coordination until it becomes eligible for dispatcher-mediated handoff.

#### Must Not Be Confused With

1. Envelope Assembler.
2. Raw Payload / Raw Content.
3. Assembler Ingress Port.
4. Dispatcher.
5. Queue Container.
6. Downstream Registry Record.

#### Valid Usage

- “Envelope Assembler produces the Log Level Envelope.”
- “Assembler Ingress Port receives Log Level Envelopes, not raw payloads.”

#### Invalid Usage

- “Log Level Envelope assembles itself.”
- “Log Level Envelope is the downstream registry record.”

#### Related Terms

- GL-ENT-001 — Envelope Assembler
- GL-BND-006 — Assembler Ingress Port
- GL-RUN-001 — Queue Container

#### Source Trace

| Source Type | Source | Trace Relation | Evidence Status | Source Summary |
|---|---|---|---|---|
| Glossary Content Pack | GL-CONT-004 | direct | direct | Defines Log Level Envelope as authoritative carrier object |
| Glossary Content Pack | GL-CONT-003 | supports | derived | Defines Envelope Assembler as producer |
| Foundational Document | VisionAndScope.md | supports | direct | Establishes envelope centrality |
```

---

## 19. Exit Criteria

|              Record ID | Exit Criterion                               | Status   |
| ---------------------: | -------------------------------------------- | -------- |
| GL-SCHEMA-001-EXIT-001 | Full canonical entry schema is defined       | Complete |
| GL-SCHEMA-001-EXIT-002 | Partial canonical entry schema is defined    | Complete |
| GL-SCHEMA-001-EXIT-003 | Seed entry schema is defined                 | Complete |
| GL-SCHEMA-001-EXIT-004 | Alias entry schema is defined                | Complete |
| GL-SCHEMA-001-EXIT-005 | Future derivation entry schema is defined    | Complete |
| GL-SCHEMA-001-EXIT-006 | Controlled field values are defined          | Complete |
| GL-SCHEMA-001-EXIT-007 | Source trace block schema is defined         | Complete |
| GL-SCHEMA-001-EXIT-008 | Anti-collapse block schema is defined        | Complete |
| GL-SCHEMA-001-EXIT-009 | Markdown parsing readiness rules are defined | Complete |
| GL-SCHEMA-001-EXIT-010 | CSV/JSON derivation readiness is defined     | Complete |

---

## 20. Summary

`GL-SCHEMA-001_Markdown_Entry_Schema.md` defines the canonical Markdown authoring schema for Assembler System glossary entries.

It preserves the architecture-first glossary model while preparing the content for structured representation.

The governing rule is:

```text id="gl-schema-001-summary-rule"
Markdown is the human-readable canonical authoring form.
CSV and JSON are derived representations.
Validation depends on stable Markdown structure.
```

Next artifact:

```text id="gl-schema-001-next"
GL-SCHEMA-002_CSV_Schema_Definitions.md
```

```
```
