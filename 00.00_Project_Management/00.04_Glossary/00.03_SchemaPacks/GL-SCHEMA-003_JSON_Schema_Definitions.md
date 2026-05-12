
# GL-SCHEMA-003 — JSON Schema Definitions

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-SCHEMA-003-DOC-001 | Document Title | GL-SCHEMA-003_JSON_Schema_Definitions.md |
| GL-SCHEMA-003-DOC-002 | Formal Version | Formal Draft V1 |
| GL-SCHEMA-003-DOC-003 | Project | Assembler System |
| GL-SCHEMA-003-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-SCHEMA-003-DOC-005 | Document Type | Schema / Representation Definition Pack |
| GL-SCHEMA-003-DOC-006 | Language | English |
| GL-SCHEMA-003-DOC-007 | Status | Formal Draft V1 |
| GL-SCHEMA-003-DOC-008 | Depends On | GL-SCHEMA-001_Markdown_Entry_Schema.md, GL-SCHEMA-002_CSV_Schema_Definitions.md, GL-CONT-000 through GL-CONT-010, Unified Glossary Content Consolidation Pack, GL-CONS-002, GL-CONS-003 |
| GL-SCHEMA-003-DOC-009 | Scope | JSON object model, JSON document schema, term object schema, relation object schema, source trace object schema, anti-collapse object schema, validation metadata schema, controlled enum schema |
| GL-SCHEMA-003-DOC-010 | Excluded From This Pack | Actual JSON population, final JSON instance files, PostgreSQL DDL, runtime API contract, final database schema, final implementation package structure |
| GL-SCHEMA-003-DOC-011 | Enables | GL-SCHEMA-004_Representation_Mapping.md, JSON population packs, validation packs, API-readiness analysis, PostgreSQL derivation readiness |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical JSON representation model for the Assembler System glossary.

It answers the question:

```text
How should glossary terms, aliases, families, categories, related-term links,
source traces, anti-collapse rules, usage examples, long-form sections,
controlled values, and validation metadata be represented as structured JSON
without losing the architectural meaning defined in Markdown or the normalized
join discipline defined in CSV?
````

JSON is not the primary meaning authority.

JSON is a structured representation derived from governed Markdown and normalized CSV.

The purpose of JSON is to provide:

1. machine-readable glossary objects,
2. nested term records,
3. validation-ready structured documents,
4. API-friendly glossary payloads,
5. schema-driven consistency checks,
6. export format for tooling,
7. bridge toward database derivation,
8. bridge toward documentation regeneration.

### 2.2 JSON Representation Role

|              Record ID | Role                             | Description                                                                   |
| ---------------------: | -------------------------------- | ----------------------------------------------------------------------------- |
| GL-SCHEMA-003-ROLE-001 | Structured Object Representation | Represents each term as a coherent nested object                              |
| GL-SCHEMA-003-ROLE-002 | Validation Target                | Provides schema-validatable glossary data                                     |
| GL-SCHEMA-003-ROLE-003 | Tooling Payload                  | Supports future glossary tools, reports, search, and coverage checks          |
| GL-SCHEMA-003-ROLE-004 | Mapping Bridge                   | Bridges Markdown richness and CSV normalization                               |
| GL-SCHEMA-003-ROLE-005 | API-Readiness Layer              | Makes glossary content usable by future APIs without defining the API itself  |
| GL-SCHEMA-003-ROLE-006 | Database Derivation Input        | Prepares document structure for later relational or document-store derivation |
| GL-SCHEMA-003-ROLE-007 | Round-Trip Support               | Supports controlled conversion between Markdown, CSV, and JSON                |

### 2.3 JSON Non-Purpose

JSON representation does not define new glossary meaning.

It does not replace Markdown authoring.

It does not replace CSV normalization.

It does not finalize runtime contracts.

It does not define a public API.

It does not define PostgreSQL tables.

It does not determine implementation classes.

It is a representation schema for governed glossary data.

---

## 3. JSON Schema Principles

### 3.1 Meaning Preservation Principle

```text id="gl-schema-003-meaning-preservation"
JSON objects must preserve glossary meaning already defined by content packs
and Markdown entries.
JSON must not invent, compress, or reinterpret canonical meaning.
```

### 3.2 Object Assembly Principle

```text id="gl-schema-003-object-assembly"
A JSON term object assembles normalized glossary records around one canonical
term identifier.
```

The main grouping key is:

```text id="gl-schema-003-term-id-key"
term_id
```

The JSON representation may assemble data from:

1. `glossary_terms.csv`,
2. `glossary_term_families.csv`,
3. `glossary_term_categories.csv`,
4. `glossary_aliases.csv`,
5. `glossary_related_terms.csv`,
6. `glossary_source_traces.csv`,
7. `glossary_anti_collapse_rules.csv`,
8. `glossary_usage_examples.csv`,
9. `glossary_entry_sections.csv`,
10. `glossary_controlled_values.csv`,
11. validation tables where applicable.

### 3.3 Stable Identifier Principle

```text id="gl-schema-003-stable-id"
JSON links must use stable canonical IDs, not display text.
```

A JSON object may include display text for readability, but reference semantics must use IDs.

### 3.4 Nested Meaning Principle

```text id="gl-schema-003-nested-meaning"
JSON may nest semantically dependent records under a term object,
but nesting must not erase the original row grain or join-key semantics.
```

For example, a term object may contain:

1. `families[]`,
2. `categories[]`,
3. `aliases[]`,
4. `related_terms[]`,
5. `source_traces[]`,
6. `anti_collapse_rules[]`,
7. `usage_examples[]`,
8. `sections[]`.

### 3.5 No Hidden Authority Principle

```text id="gl-schema-003-no-hidden-authority"
A JSON object must not imply ownership, authority, or implementation readiness
beyond what the source term explicitly declares.
```

JSON nesting must not imply that the parent term owns every nested relation.

### 3.6 Round-Trip Principle

```text id="gl-schema-003-round-trip"
JSON must support controlled round-trip interpretation across Markdown, CSV,
validation reports, and later database derivation.
```

---

## 4. JSON Artifact Set

### 4.1 Required JSON Artifacts

|              Record ID | JSON Artifact                       | Object Grain                        | Purpose                                       |
| ---------------------: | ----------------------------------- | ----------------------------------- | --------------------------------------------- |
| GL-SCHEMA-003-FILE-001 | `glossary.terms.json`               | One array of assembled term objects | Main structured glossary representation       |
| GL-SCHEMA-003-FILE-002 | `glossary.index.json`               | One glossary metadata/index object  | Pack-level, schema-level, and export metadata |
| GL-SCHEMA-003-FILE-003 | `glossary.controlled-values.json`   | Controlled value sets               | Enumerations and allowed values               |
| GL-SCHEMA-003-FILE-004 | `glossary.validation-rules.json`    | Validation rule objects             | Machine-readable validation rules             |
| GL-SCHEMA-003-FILE-005 | `glossary.validation-findings.json` | Validation finding objects          | Future validation output                      |
| GL-SCHEMA-003-FILE-006 | `glossary.schema.json`              | JSON Schema document                | Formal schema for glossary JSON instances     |

### 4.2 Optional JSON Artifacts

|              Record ID | JSON Artifact                        | Object Grain                 | Purpose                                       |
| ---------------------: | ------------------------------------ | ---------------------------- | --------------------------------------------- |
| GL-SCHEMA-003-FILE-007 | `glossary.packs.json`                | Pack index objects           | Pack map and dependency metadata              |
| GL-SCHEMA-003-FILE-008 | `glossary.relationships.json`        | Relation objects             | Standalone relation graph                     |
| GL-SCHEMA-003-FILE-009 | `glossary.anti-collapse-index.json`  | Anti-collapse rule objects   | Standalone guard index                        |
| GL-SCHEMA-003-FILE-010 | `glossary.source-traces.json`        | Source trace objects         | Standalone source trace index                 |
| GL-SCHEMA-003-FILE-011 | `glossary.derivation-readiness.json` | Derivation readiness objects | Future implementation/database readiness view |

---

## 5. Top-Level JSON Document Model

### 5.1 Main Glossary JSON Shape

The main glossary JSON object must use this logical structure.

```json id="gl-schema-003-main-shape"
{
  "schema_version": "Formal Draft V1",
  "schema_id": "GL-SCHEMA-003",
  "project": "Assembler System",
  "artifact_type": "glossary_terms",
  "generated_from": {
    "markdown_schema": "GL-SCHEMA-001",
    "csv_schema": "GL-SCHEMA-002",
    "content_packs": [
      "GL-CONT-000",
      "GL-CONT-001",
      "GL-CONT-002",
      "GL-CONT-003",
      "GL-CONT-004",
      "GL-CONT-005",
      "GL-CONT-006",
      "GL-CONT-007",
      "GL-CONT-008",
      "GL-CONT-009",
      "GL-CONT-010"
    ]
  },
  "controlled_values_ref": "glossary.controlled-values.json",
  "terms": [],
  "export_metadata": {}
}
```

### 5.2 Top-Level Fields

| Field                   | Required | Type   | Description                            |
| ----------------------- | -------- | ------ | -------------------------------------- |
| `schema_version`        | Yes      | string | Formal schema version                  |
| `schema_id`             | Yes      | string | Schema pack ID                         |
| `project`               | Yes      | string | Project name                           |
| `artifact_type`         | Yes      | enum   | Type of JSON artifact                  |
| `generated_from`        | Yes      | object | Source schema and content-pack basis   |
| `controlled_values_ref` | No       | string | Reference to controlled value artifact |
| `terms`                 | Yes      | array  | Assembled term objects                 |
| `export_metadata`       | Yes      | object | Export/generation metadata             |

### 5.3 Artifact Type Values

| Value                 | Meaning                             |
| --------------------- | ----------------------------------- |
| `glossary_terms`      | Main assembled term file            |
| `glossary_index`      | Top-level glossary index            |
| `controlled_values`   | Controlled value sets               |
| `validation_rules`    | Validation rule definitions         |
| `validation_findings` | Validation results                  |
| `anti_collapse_index` | Standalone anti-collapse rule index |
| `source_trace_index`  | Standalone source trace index       |
| `relationship_index`  | Standalone relation graph           |
| `pack_index`          | Pack metadata and dependency index  |

---

## 6. Term Object Schema

### 6.1 Term Object Shape

Each glossary term should be represented as one assembled JSON object.

```json id="gl-schema-003-term-object-shape"
{
  "term_id": "GL-OBJ-001",
  "canonical_term": "Log Level Envelope",
  "display_term": "Log Level Envelope",
  "entry_profile": "full_canonical",
  "entry_maturity": "canonical_full",
  "status": "active",
  "ownership_scope": "assembler_owned / transferable",
  "evidence_status": "direct / user_decision / derived",
  "primary_family_code": "OBJ",
  "primary_category": "carrier_object",
  "definition_short": "Authoritative assembler-side carrier object produced by Envelope Assembler.",
  "introduced_in_pack_id": "GL-CONT-004",
  "consolidated_by_pack_id": "UGCC",
  "canonical_target_term_id": null,
  "families": [],
  "categories": [],
  "aliases": [],
  "sections": [],
  "related_terms": [],
  "source_traces": [],
  "anti_collapse_rules": [],
  "usage_examples": [],
  "validation_state": {},
  "notes": null
}
```

### 6.2 Required Term Object Fields

| Field                      | Required    | Type        | Description                                |
| -------------------------- | ----------- | ----------- | ------------------------------------------ |
| `term_id`                  | Yes         | string      | Stable canonical glossary term ID          |
| `canonical_term`           | Yes         | string      | Canonical human-readable term              |
| `display_term`             | No          | string/null | Display variant                            |
| `entry_profile`            | Yes         | enum        | Entry profile from controlled values       |
| `entry_maturity`           | Yes         | enum        | Entry maturity from controlled values      |
| `status`                   | Yes         | enum        | active / pending / deprecated / superseded |
| `ownership_scope`          | Yes         | string      | Ownership or authority scope               |
| `evidence_status`          | Yes         | string      | Evidence classification                    |
| `primary_family_code`      | Yes         | string      | Primary family code                        |
| `primary_category`         | Yes         | string      | Primary category                           |
| `definition_short`         | Yes         | string      | Short definition                           |
| `introduced_in_pack_id`    | Yes         | string      | Pack where term was introduced             |
| `consolidated_by_pack_id`  | No          | string/null | Consolidation pack ID                      |
| `canonical_target_term_id` | Conditional | string/null | Required when term is an alias             |
| `families`                 | Yes         | array       | Family membership objects                  |
| `categories`               | Yes         | array       | Category membership objects                |
| `aliases`                  | Yes         | array       | Alias objects where applicable             |
| `sections`                 | Yes         | array       | Long-form section objects                  |
| `related_terms`            | Yes         | array       | Related-term relation objects              |
| `source_traces`            | Yes         | array       | Source trace objects                       |
| `anti_collapse_rules`      | Yes         | array       | Anti-collapse rule objects                 |
| `usage_examples`           | Yes         | array       | Valid/invalid usage examples               |
| `validation_state`         | No          | object      | Validation summary                         |
| `notes`                    | No          | string/null | Notes                                      |

### 6.3 Term Object Constraints

|                    Rule ID | Rule                                                                              |
| -------------------------: | --------------------------------------------------------------------------------- |
| GL-SCHEMA-003-TERM-VAL-001 | `term_id` must be unique within `terms[]`                                         |
| GL-SCHEMA-003-TERM-VAL-002 | `canonical_term` must not be empty                                                |
| GL-SCHEMA-003-TERM-VAL-003 | `entry_profile` must use controlled values                                        |
| GL-SCHEMA-003-TERM-VAL-004 | `entry_maturity` must use controlled values                                       |
| GL-SCHEMA-003-TERM-VAL-005 | `primary_family_code` must appear in `families[]` with `family_role = primary`    |
| GL-SCHEMA-003-TERM-VAL-006 | `primary_category` should appear in `categories[]` with `category_role = primary` |
| GL-SCHEMA-003-TERM-VAL-007 | Alias terms must include `canonical_target_term_id`                               |
| GL-SCHEMA-003-TERM-VAL-008 | Non-alias terms should not include `canonical_target_term_id` except as null      |
| GL-SCHEMA-003-TERM-VAL-009 | `canonical_full` terms must include at least one `definition` section             |
| GL-SCHEMA-003-TERM-VAL-010 | Critical canonical terms must include at least one active source trace            |

---

## 7. Family Membership Object Schema

### 7.1 Object Shape

```json id="gl-schema-003-family-object"
{
  "term_family_id": "GL-TF-000001",
  "family_code": "OBJ",
  "family_role": "primary",
  "source_pack_id": "GL-CONT-004",
  "status": "active"
}
```

### 7.2 Fields

| Field            | Required | Type        | Description                   |
| ---------------- | -------- | ----------- | ----------------------------- |
| `term_family_id` | Yes      | string      | Stable family membership ID   |
| `family_code`    | Yes      | enum/string | Family code                   |
| `family_role`    | Yes      | enum        | primary / secondary           |
| `source_pack_id` | Yes      | string      | Pack establishing membership  |
| `status`         | Yes      | enum        | active / pending / deprecated |

### 7.3 Constraints

|                   Rule ID | Rule                                            |
| ------------------------: | ----------------------------------------------- |
| GL-SCHEMA-003-FAM-VAL-001 | Each term must have exactly one primary family  |
| GL-SCHEMA-003-FAM-VAL-002 | Secondary families are allowed                  |
| GL-SCHEMA-003-FAM-VAL-003 | `family_code` must resolve to controlled values |
| GL-SCHEMA-003-FAM-VAL-004 | `source_pack_id` must not be empty              |

---

## 8. Category Membership Object Schema

### 8.1 Object Shape

```json id="gl-schema-003-category-object"
{
  "term_category_id": "GL-TC-000001",
  "category_code": "carrier_object",
  "category_role": "primary",
  "source_pack_id": "GL-CONT-004",
  "status": "active"
}
```

### 8.2 Fields

| Field              | Required | Type   | Description                    |
| ------------------ | -------- | ------ | ------------------------------ |
| `term_category_id` | Yes      | string | Stable category membership ID  |
| `category_code`    | Yes      | string | Architectural category         |
| `category_role`    | Yes      | enum   | primary / secondary            |
| `source_pack_id`   | Yes      | string | Pack establishing the category |
| `status`           | Yes      | enum   | active / pending / deprecated  |

### 8.3 Constraints

|                   Rule ID | Rule                                                         |
| ------------------------: | ------------------------------------------------------------ |
| GL-SCHEMA-003-CAT-VAL-001 | Each active canonical term must have at least one category   |
| GL-SCHEMA-003-CAT-VAL-002 | Each term should have one primary category                   |
| GL-SCHEMA-003-CAT-VAL-003 | Category labels must preserve architectural meaning          |
| GL-SCHEMA-003-CAT-VAL-004 | Category labels must not be inferred from display text alone |

---

## 9. Alias Object Schema

### 9.1 Object Shape

```json id="gl-schema-003-alias-object"
{
  "alias_id": "GL-ALIAS-MAP-000001",
  "alias_term": "Log Envelope",
  "canonical_target_term_id": "GL-OBJ-001",
  "canonical_target_term": "Log Level Envelope",
  "alias_type": "legacy",
  "evidence_status": "legacy_alias",
  "valid_usage_policy": "source_only",
  "source_pack_id": "GL-CONT-004",
  "status": "active",
  "notes": "Preserved as a source alias; formal documents should prefer Log Level Envelope."
}
```

### 9.2 Fields

| Field                      | Required | Type        | Description                                                       |
| -------------------------- | -------- | ----------- | ----------------------------------------------------------------- |
| `alias_id`                 | Yes      | string      | Stable alias ID                                                   |
| `alias_term`               | Yes      | string      | Alias wording                                                     |
| `canonical_target_term_id` | Yes      | string      | Canonical target ID                                               |
| `canonical_target_term`    | Yes      | string      | Canonical target label                                            |
| `alias_type`               | Yes      | enum        | legacy / shorthand / source_alias / spelling_variant / deprecated |
| `evidence_status`          | Yes      | enum/string | Evidence classification                                           |
| `valid_usage_policy`       | Yes      | enum        | allowed / discouraged / prohibited / source_only                  |
| `source_pack_id`           | Yes      | string      | Pack establishing alias                                           |
| `status`                   | Yes      | enum        | active / deprecated / superseded                                  |
| `notes`                    | No       | string/null | Alias handling notes                                              |

### 9.3 Constraints

|                     Rule ID | Rule                                        |
| --------------------------: | ------------------------------------------- |
| GL-SCHEMA-003-ALIAS-VAL-001 | Alias must point to a canonical target term |
| GL-SCHEMA-003-ALIAS-VAL-002 | Alias should not point to another alias     |
| GL-SCHEMA-003-ALIAS-VAL-003 | Deprecated aliases must include notes       |
| GL-SCHEMA-003-ALIAS-VAL-004 | `valid_usage_policy` must be explicit       |

---

## 10. Entry Section Object Schema

### 10.1 Object Shape

```json id="gl-schema-003-section-object"
{
  "entry_section_id": "GL-SEC-000001",
  "section_type": "definition",
  "section_order": 1,
  "section_title": "Definition",
  "section_text": "The Log Level Envelope is the authoritative assembler-side carrier object produced by the Envelope Assembler after governed content has passed through the required preparation path.",
  "source_pack_id": "GL-CONT-004",
  "status": "active"
}
```

### 10.2 Fields

| Field              | Required | Type    | Description                                                                                                                                                                        |
| ------------------ | -------- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `entry_section_id` | Yes      | string  | Stable section ID                                                                                                                                                                  |
| `section_type`     | Yes      | enum    | definition / architectural_role / working_definition / known_constraints / open_clarifications / future_derivation_role / derivation_preconditions / invalid_premature_use / notes |
| `section_order`    | Yes      | integer | Display order                                                                                                                                                                      |
| `section_title`    | Yes      | string  | Human-readable section title                                                                                                                                                       |
| `section_text`     | Yes      | string  | Markdown-compatible prose                                                                                                                                                          |
| `source_pack_id`   | Yes      | string  | Pack establishing the section                                                                                                                                                      |
| `status`           | Yes      | enum    | active / pending / deprecated                                                                                                                                                      |

### 10.3 Constraints

|                   Rule ID | Rule                                                                  |
| ------------------------: | --------------------------------------------------------------------- |
| GL-SCHEMA-003-SEC-VAL-001 | `section_order` must be positive                                      |
| GL-SCHEMA-003-SEC-VAL-002 | `section_type` must be controlled                                     |
| GL-SCHEMA-003-SEC-VAL-003 | `canonical_full` terms must include a `definition` section            |
| GL-SCHEMA-003-SEC-VAL-004 | `canonical_full` terms should include an `architectural_role` section |
| GL-SCHEMA-003-SEC-VAL-005 | Section text must not silently define final implementation artifacts  |

---

## 11. Related Term Object Schema

### 11.1 Object Shape

```json id="gl-schema-003-related-term-object"
{
  "relationship_id": "GL-REL-000001",
  "source_term_id": "GL-ENT-001",
  "target_term_id": "GL-OBJ-001",
  "target_term": "Log Level Envelope",
  "relationship_type": "produces",
  "directionality": "directed",
  "source_pack_id": "GL-CONT-003",
  "status": "active",
  "notes": "Envelope Assembler produces Log Level Envelope."
}
```

### 11.2 Fields

| Field               | Required | Type        | Description                                                                                          |
| ------------------- | -------- | ----------- | ---------------------------------------------------------------------------------------------------- |
| `relationship_id`   | Yes      | string      | Stable relation ID                                                                                   |
| `source_term_id`    | Yes      | string      | Source term                                                                                          |
| `target_term_id`    | Yes      | string      | Target term                                                                                          |
| `target_term`       | No       | string      | Target display label                                                                                 |
| `relationship_type` | Yes      | enum        | related / produces / receives / governs / excludes / aliases / depends_on / enables / contrasts_with |
| `directionality`    | Yes      | enum        | directed / undirected                                                                                |
| `source_pack_id`    | Yes      | string      | Pack establishing relation                                                                           |
| `status`            | Yes      | enum        | active / pending / deprecated                                                                        |
| `notes`             | No       | string/null | Optional relation explanation                                                                        |

### 11.3 Constraints

|                   Rule ID | Rule                                                                             |
| ------------------------: | -------------------------------------------------------------------------------- |
| GL-SCHEMA-003-REL-VAL-001 | `source_term_id` must match the parent term when nested under a term object      |
| GL-SCHEMA-003-REL-VAL-002 | `target_term_id` must resolve to a known term or permitted seed                  |
| GL-SCHEMA-003-REL-VAL-003 | `relationship_type` must be controlled                                           |
| GL-SCHEMA-003-REL-VAL-004 | Directed relationships must preserve source-target meaning                       |
| GL-SCHEMA-003-REL-VAL-005 | `produces` must not invert actor/object direction without explicit justification |

---

## 12. Source Trace Object Schema

### 12.1 Object Shape

```json id="gl-schema-003-source-trace-object"
{
  "source_trace_id": "GL-SRC-000001",
  "target_id": "GL-OBJ-001",
  "target_type": "term",
  "source_id": "GL-CONT-004",
  "source_type": "glossary_pack",
  "trace_relation": "direct",
  "evidence_status": "direct",
  "source_summary": "Defines Log Level Envelope as authoritative carrier object.",
  "validation_use": "Validate envelope carrier semantics.",
  "status": "active"
}
```

### 12.2 Fields

| Field             | Required | Type        | Description                                                                                                                  |
| ----------------- | -------- | ----------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `source_trace_id` | Yes      | string      | Stable trace ID                                                                                                              |
| `target_id`       | Yes      | string      | Term, rule, relation, pack, or validation item being traced                                                                  |
| `target_type`     | Yes      | enum        | term / rule / pack / relation / goal / doctrine / derivation_item / validation_rule                                          |
| `source_id`       | Yes      | string      | Source document, pack, goal, rule, or decision ID                                                                            |
| `source_type`     | Yes      | enum        | foundational_document / glossary_pack / consolidation_pack / system_goal / user_decision / anti_collapse_rule / derived_rule |
| `trace_relation`  | Yes      | enum        | direct / derived / supports / constrains / consolidates / aliases / enables / excludes / validates / supersedes              |
| `evidence_status` | Yes      | enum/string | Evidence classification                                                                                                      |
| `source_summary`  | Yes      | string      | Source contribution summary                                                                                                  |
| `validation_use`  | No       | string/null | How validators should use the trace                                                                                          |
| `status`          | Yes      | enum        | active / pending / superseded / deprecated                                                                                   |

### 12.3 Constraints

|                   Rule ID | Rule                                                                  |
| ------------------------: | --------------------------------------------------------------------- |
| GL-SCHEMA-003-SRC-VAL-001 | Every source trace must include `target_id`                           |
| GL-SCHEMA-003-SRC-VAL-002 | Nested source traces under a term should use that term as `target_id` |
| GL-SCHEMA-003-SRC-VAL-003 | `source_type` must be controlled                                      |
| GL-SCHEMA-003-SRC-VAL-004 | `trace_relation` must be controlled                                   |
| GL-SCHEMA-003-SRC-VAL-005 | Critical canonical terms must have at least one active source trace   |
| GL-SCHEMA-003-SRC-VAL-006 | `needs_validation` traces must remain visible in validation output    |

---

## 13. Anti-Collapse Rule Object Schema

### 13.1 Object Shape

```json id="gl-schema-003-anti-collapse-object"
{
  "anti_collapse_rule_id": "GL-AC-000001",
  "protected_term_id": "GL-ENT-001",
  "protected_term": "Envelope Assembler",
  "must_not_collapse_into_id": "GL-OBJ-001",
  "must_not_collapse_into_label": "Log Level Envelope",
  "collapse_type": "actor_object",
  "protected_distinction": "Producer must not collapse into produced carrier.",
  "severity": "high",
  "source_pack_id": "GL-CONT-003",
  "validation_use": "Check actor/object separation.",
  "derivation_impact": "Would corrupt envelope lifecycle and responsibility ownership.",
  "status": "active"
}
```

### 13.2 Fields

| Field                          | Required | Type        | Description                                                                                                              |
| ------------------------------ | -------- | ----------- | ------------------------------------------------------------------------------------------------------------------------ |
| `anti_collapse_rule_id`        | Yes      | string      | Stable anti-collapse rule ID                                                                                             |
| `protected_term_id`            | Yes      | string      | Protected term ID                                                                                                        |
| `protected_term`               | Yes      | string      | Protected term display label                                                                                             |
| `must_not_collapse_into_id`    | No       | string/null | Target term ID if known                                                                                                  |
| `must_not_collapse_into_label` | Yes      | string      | Target term/category/system/artifact label                                                                               |
| `collapse_type`                | Yes      | enum        | identity / boundary / authority / actor_object / runtime / contract / responsibility / policy / handoff / implementation |
| `protected_distinction`        | Yes      | string      | Architectural distinction preserved                                                                                      |
| `severity`                     | Yes      | enum        | critical / high / medium / low                                                                                           |
| `source_pack_id`               | Yes      | string      | Main pack establishing the rule                                                                                          |
| `validation_use`               | Yes      | string      | Validation use                                                                                                           |
| `derivation_impact`            | No       | string/null | What breaks if violated                                                                                                  |
| `status`                       | Yes      | enum        | active / pending / deprecated                                                                                            |

### 13.3 Constraints

|                  Rule ID | Rule                                                                                           |
| -----------------------: | ---------------------------------------------------------------------------------------------- |
| GL-SCHEMA-003-AC-VAL-001 | Every anti-collapse rule must have a protected term                                            |
| GL-SCHEMA-003-AC-VAL-002 | Every anti-collapse rule must have a collapse target label                                     |
| GL-SCHEMA-003-AC-VAL-003 | Critical rules must include `validation_use`                                                   |
| GL-SCHEMA-003-AC-VAL-004 | `collapse_type` must be controlled                                                             |
| GL-SCHEMA-003-AC-VAL-005 | Nested anti-collapse rules must protect the parent term unless explicitly marked as cross-term |

---

## 14. Usage Example Object Schema

### 14.1 Object Shape

```json id="gl-schema-003-usage-object"
{
  "usage_example_id": "GL-USE-000001",
  "usage_type": "valid",
  "usage_text": "Envelope Assembler produces the Log Level Envelope.",
  "reason": "Correct producer/carrier distinction.",
  "linked_anti_collapse_rule_id": "GL-AC-000001",
  "source_pack_id": "GL-CONT-004",
  "status": "active"
}
```

### 14.2 Fields

| Field                          | Required | Type        | Description                   |
| ------------------------------ | -------- | ----------- | ----------------------------- |
| `usage_example_id`             | Yes      | string      | Stable usage example ID       |
| `usage_type`                   | Yes      | enum        | valid / invalid               |
| `usage_text`                   | Yes      | string      | Sentence-like usage example   |
| `reason`                       | No       | string/null | Explanation                   |
| `linked_anti_collapse_rule_id` | No       | string/null | Related anti-collapse rule    |
| `source_pack_id`               | Yes      | string      | Pack establishing the usage   |
| `status`                       | Yes      | enum        | active / pending / deprecated |

### 14.3 Constraints

|                   Rule ID | Rule                                                                |
| ------------------------: | ------------------------------------------------------------------- |
| GL-SCHEMA-003-USE-VAL-001 | `usage_type` must be valid or invalid                               |
| GL-SCHEMA-003-USE-VAL-002 | Invalid usage should link to an anti-collapse rule where applicable |
| GL-SCHEMA-003-USE-VAL-003 | Usage examples must not introduce new canonical meaning             |
| GL-SCHEMA-003-USE-VAL-004 | Usage text should be human-readable and sentence-like               |

---

## 15. Validation State Object Schema

### 15.1 Object Shape

```json id="gl-schema-003-validation-state-object"
{
  "validation_status": "not_run",
  "last_validated_at": null,
  "finding_count": 0,
  "critical_finding_count": 0,
  "high_finding_count": 0,
  "open_finding_ids": []
}
```

### 15.2 Fields

| Field                    | Required | Type        | Description                                   |
| ------------------------ | -------- | ----------- | --------------------------------------------- |
| `validation_status`      | Yes      | enum        | not_run / passed / failed / warning / partial |
| `last_validated_at`      | No       | string/null | ISO timestamp                                 |
| `finding_count`          | Yes      | integer     | Total finding count                           |
| `critical_finding_count` | Yes      | integer     | Critical finding count                        |
| `high_finding_count`     | Yes      | integer     | High finding count                            |
| `open_finding_ids`       | Yes      | array       | Open validation finding IDs                   |

### 15.3 Constraints

|                      Rule ID | Rule                                                                               |
| ---------------------------: | ---------------------------------------------------------------------------------- |
| GL-SCHEMA-003-VSTATE-VAL-001 | Counts must be non-negative integers                                               |
| GL-SCHEMA-003-VSTATE-VAL-002 | `validation_status` must be controlled                                             |
| GL-SCHEMA-003-VSTATE-VAL-003 | `open_finding_ids[]` must reference validation findings when findings are included |

---

## 16. Controlled Values JSON Schema

### 16.1 Controlled Values Artifact Shape

```json id="gl-schema-003-controlled-values-shape"
{
  "schema_version": "Formal Draft V1",
  "schema_id": "GL-SCHEMA-003",
  "artifact_type": "controlled_values",
  "value_sets": {
    "family_code": [],
    "entry_maturity": [],
    "entry_profile": [],
    "evidence_status": [],
    "ownership_scope": [],
    "status": [],
    "severity": [],
    "trace_relation": [],
    "source_type": [],
    "relationship_type": []
  }
}
```

### 16.2 Controlled Value Object Shape

```json id="gl-schema-003-controlled-value-object"
{
  "controlled_value_id": "GL-CV-000001",
  "value_set": "family_code",
  "value_code": "OBJ",
  "value_label": "Governed Object",
  "description": "Carrier objects and governed objects.",
  "status": "active",
  "source_pack_id": "GL-CONT-000"
}
```

### 16.3 Required Value Sets

The JSON controlled values artifact must include at least:

1. `family_code`,
2. `entry_maturity`,
3. `entry_profile`,
4. `evidence_status`,
5. `ownership_scope`,
6. `status`,
7. `severity`,
8. `trace_relation`,
9. `source_type`,
10. `target_type`,
11. `relationship_type`,
12. `collapse_type`,
13. `usage_type`,
14. `validation_status`,
15. `validation_rule_type`,
16. `artifact_type`.

---

## 17. Validation Rule JSON Schema

### 17.1 Validation Rule Object Shape

```json id="gl-schema-003-validation-rule-object"
{
  "validation_rule_id": "GL-VAL-000001",
  "rule_name": "Term ID uniqueness",
  "applies_to_artifact": "glossary.terms.json",
  "applies_to_path": "$.terms[*].term_id",
  "rule_type": "uniqueness",
  "rule_description": "Each term_id must be unique.",
  "severity": "critical",
  "source_pack_id": "GL-SCHEMA-003",
  "status": "active"
}
```

### 17.2 Fields

| Field                 | Required | Type        | Description                                                                            |
| --------------------- | -------- | ----------- | -------------------------------------------------------------------------------------- |
| `validation_rule_id`  | Yes      | string      | Stable validation rule ID                                                              |
| `rule_name`           | Yes      | string      | Short rule name                                                                        |
| `applies_to_artifact` | Yes      | string      | JSON artifact target                                                                   |
| `applies_to_path`     | No       | string/null | JSONPath-like target path                                                              |
| `rule_type`           | Yes      | enum        | required_field / uniqueness / foreign_key / controlled_value / cross_object / semantic |
| `rule_description`    | Yes      | string      | Rule definition                                                                        |
| `severity`            | Yes      | enum        | critical / high / medium / low                                                         |
| `source_pack_id`      | Yes      | string      | Pack establishing rule                                                                 |
| `status`              | Yes      | enum        | active / pending / deprecated                                                          |

---

## 18. Validation Finding JSON Schema

### 18.1 Validation Finding Object Shape

```json id="gl-schema-003-validation-finding-object"
{
  "validation_finding_id": "GL-FIND-000001",
  "validation_rule_id": "GL-VAL-000001",
  "target_artifact": "glossary.terms.json",
  "target_path": "$.terms[12].term_id",
  "target_id": "GL-OBJ-001",
  "finding_severity": "critical",
  "finding_status": "open",
  "finding_message": "Duplicate term_id detected.",
  "recommended_action": "Ensure each term_id appears only once.",
  "detected_at": null,
  "resolved_at": null
}
```

### 18.2 Fields

| Field                   | Required | Type        | Description                               |
| ----------------------- | -------- | ----------- | ----------------------------------------- |
| `validation_finding_id` | Yes      | string      | Stable finding ID                         |
| `validation_rule_id`    | Yes      | string      | Rule that produced finding                |
| `target_artifact`       | Yes      | string      | Affected artifact                         |
| `target_path`           | No       | string/null | JSONPath-like affected path               |
| `target_id`             | No       | string/null | Affected term/rule/relation ID            |
| `finding_severity`      | Yes      | enum        | critical / high / medium / low            |
| `finding_status`        | Yes      | enum        | open / resolved / waived / false_positive |
| `finding_message`       | Yes      | string      | Human-readable message                    |
| `recommended_action`    | No       | string/null | Suggested correction                      |
| `detected_at`           | No       | string/null | ISO timestamp                             |
| `resolved_at`           | No       | string/null | ISO timestamp                             |

---

## 19. Formal JSON Schema Draft

### 19.1 Schema Draft Target

The formal JSON Schema should target:

```text id="gl-schema-003-json-schema-draft-target"
JSON Schema Draft 2020-12
```

This target is selected for modern validation capability, including:

1. `$defs`,
2. `$id`,
3. `$schema`,
4. nested object reuse,
5. conditional validation,
6. enum definitions,
7. array constraints.

### 19.2 Main Schema Skeleton

```json id="gl-schema-003-json-schema-skeleton"
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://assembler-system.local/schemas/glossary.schema.json",
  "title": "Assembler System Glossary JSON Schema",
  "type": "object",
  "required": [
    "schema_version",
    "schema_id",
    "project",
    "artifact_type",
    "generated_from",
    "terms",
    "export_metadata"
  ],
  "properties": {
    "schema_version": {
      "type": "string"
    },
    "schema_id": {
      "const": "GL-SCHEMA-003"
    },
    "project": {
      "const": "Assembler System"
    },
    "artifact_type": {
      "$ref": "#/$defs/artifactType"
    },
    "generated_from": {
      "$ref": "#/$defs/generatedFrom"
    },
    "controlled_values_ref": {
      "type": ["string", "null"]
    },
    "terms": {
      "type": "array",
      "items": {
        "$ref": "#/$defs/term"
      }
    },
    "export_metadata": {
      "$ref": "#/$defs/exportMetadata"
    }
  },
  "$defs": {}
}
```

---

## 20. JSON Schema `$defs`

### 20.1 Common ID Definition

```json id="gl-schema-003-def-id"
{
  "$defs": {
    "stableId": {
      "type": "string",
      "minLength": 1,
      "pattern": "^[A-Z0-9]+(?:-[A-Z0-9]+)*-[0-9A-Z]+$"
    }
  }
}
```

This pattern is intentionally permissive enough to support IDs such as:

1. `GL-OBJ-001`,
2. `GL-CONT-004`,
3. `GL-SCHEMA-003`,
4. `GL-AC-000001`,
5. `UGCC-DOC-001`.

### 20.2 Artifact Type Definition

```json id="gl-schema-003-def-artifact-type"
{
  "$defs": {
    "artifactType": {
      "type": "string",
      "enum": [
        "glossary_terms",
        "glossary_index",
        "controlled_values",
        "validation_rules",
        "validation_findings",
        "anti_collapse_index",
        "source_trace_index",
        "relationship_index",
        "pack_index"
      ]
    }
  }
}
```

### 20.3 Status Definition

```json id="gl-schema-003-def-status"
{
  "$defs": {
    "status": {
      "type": "string",
      "enum": [
        "active",
        "pending",
        "deprecated",
        "superseded"
      ]
    }
  }
}
```

### 20.4 Severity Definition

```json id="gl-schema-003-def-severity"
{
  "$defs": {
    "severity": {
      "type": "string",
      "enum": [
        "critical",
        "high",
        "medium",
        "low"
      ]
    }
  }
}
```

### 20.5 Entry Maturity Definition

```json id="gl-schema-003-def-entry-maturity"
{
  "$defs": {
    "entryMaturity": {
      "type": "string",
      "enum": [
        "canonical_full",
        "canonical_partial",
        "seed",
        "alias",
        "future_derivation"
      ]
    }
  }
}
```

### 20.6 Entry Profile Definition

```json id="gl-schema-003-def-entry-profile"
{
  "$defs": {
    "entryProfile": {
      "type": "string",
      "enum": [
        "full_canonical",
        "partial_canonical",
        "seed",
        "alias",
        "future_derivation"
      ]
    }
  }
}
```

---

## 21. Term `$defs` Schema

```json id="gl-schema-003-def-term"
{
  "$defs": {
    "term": {
      "type": "object",
      "required": [
        "term_id",
        "canonical_term",
        "entry_profile",
        "entry_maturity",
        "status",
        "ownership_scope",
        "evidence_status",
        "primary_family_code",
        "primary_category",
        "definition_short",
        "introduced_in_pack_id",
        "families",
        "categories",
        "aliases",
        "sections",
        "related_terms",
        "source_traces",
        "anti_collapse_rules",
        "usage_examples"
      ],
      "properties": {
        "term_id": {
          "$ref": "#/$defs/stableId"
        },
        "canonical_term": {
          "type": "string",
          "minLength": 1
        },
        "display_term": {
          "type": ["string", "null"]
        },
        "entry_profile": {
          "$ref": "#/$defs/entryProfile"
        },
        "entry_maturity": {
          "$ref": "#/$defs/entryMaturity"
        },
        "status": {
          "$ref": "#/$defs/status"
        },
        "ownership_scope": {
          "type": "string",
          "minLength": 1
        },
        "evidence_status": {
          "type": "string",
          "minLength": 1
        },
        "primary_family_code": {
          "type": "string",
          "minLength": 1
        },
        "primary_category": {
          "type": "string",
          "minLength": 1
        },
        "definition_short": {
          "type": "string",
          "minLength": 1
        },
        "introduced_in_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "consolidated_by_pack_id": {
          "type": ["string", "null"]
        },
        "canonical_target_term_id": {
          "type": ["string", "null"]
        },
        "families": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/familyMembership"
          }
        },
        "categories": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/categoryMembership"
          }
        },
        "aliases": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/alias"
          }
        },
        "sections": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/entrySection"
          }
        },
        "related_terms": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/relatedTerm"
          }
        },
        "source_traces": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/sourceTrace"
          }
        },
        "anti_collapse_rules": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/antiCollapseRule"
          }
        },
        "usage_examples": {
          "type": "array",
          "items": {
            "$ref": "#/$defs/usageExample"
          }
        },
        "validation_state": {
          "$ref": "#/$defs/validationState"
        },
        "notes": {
          "type": ["string", "null"]
        }
      },
      "allOf": [
        {
          "if": {
            "properties": {
              "entry_profile": {
                "const": "alias"
              }
            }
          },
          "then": {
            "required": [
              "canonical_target_term_id"
            ],
            "properties": {
              "canonical_target_term_id": {
                "type": "string",
                "minLength": 1
              }
            }
          }
        }
      ]
    }
  }
}
```

---

## 22. Supporting `$defs` Schemas

### 22.1 Family Membership

```json id="gl-schema-003-def-family-membership"
{
  "$defs": {
    "familyMembership": {
      "type": "object",
      "required": [
        "term_family_id",
        "family_code",
        "family_role",
        "source_pack_id",
        "status"
      ],
      "properties": {
        "term_family_id": {
          "type": "string",
          "minLength": 1
        },
        "family_code": {
          "type": "string",
          "minLength": 1
        },
        "family_role": {
          "type": "string",
          "enum": ["primary", "secondary"]
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.2 Category Membership

```json id="gl-schema-003-def-category-membership"
{
  "$defs": {
    "categoryMembership": {
      "type": "object",
      "required": [
        "term_category_id",
        "category_code",
        "category_role",
        "source_pack_id",
        "status"
      ],
      "properties": {
        "term_category_id": {
          "type": "string",
          "minLength": 1
        },
        "category_code": {
          "type": "string",
          "minLength": 1
        },
        "category_role": {
          "type": "string",
          "enum": ["primary", "secondary"]
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.3 Entry Section

```json id="gl-schema-003-def-entry-section"
{
  "$defs": {
    "entrySection": {
      "type": "object",
      "required": [
        "entry_section_id",
        "section_type",
        "section_order",
        "section_title",
        "section_text",
        "source_pack_id",
        "status"
      ],
      "properties": {
        "entry_section_id": {
          "type": "string",
          "minLength": 1
        },
        "section_type": {
          "type": "string",
          "enum": [
            "definition",
            "architectural_role",
            "working_definition",
            "known_constraints",
            "open_clarifications",
            "future_derivation_role",
            "derivation_preconditions",
            "invalid_premature_use",
            "notes"
          ]
        },
        "section_order": {
          "type": "integer",
          "minimum": 1
        },
        "section_title": {
          "type": "string",
          "minLength": 1
        },
        "section_text": {
          "type": "string",
          "minLength": 1
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.4 Related Term

```json id="gl-schema-003-def-related-term"
{
  "$defs": {
    "relatedTerm": {
      "type": "object",
      "required": [
        "relationship_id",
        "source_term_id",
        "target_term_id",
        "relationship_type",
        "directionality",
        "source_pack_id",
        "status"
      ],
      "properties": {
        "relationship_id": {
          "type": "string",
          "minLength": 1
        },
        "source_term_id": {
          "type": "string",
          "minLength": 1
        },
        "target_term_id": {
          "type": "string",
          "minLength": 1
        },
        "target_term": {
          "type": ["string", "null"]
        },
        "relationship_type": {
          "type": "string",
          "enum": [
            "related",
            "produces",
            "receives",
            "governs",
            "excludes",
            "aliases",
            "depends_on",
            "enables",
            "contrasts_with"
          ]
        },
        "directionality": {
          "type": "string",
          "enum": ["directed", "undirected"]
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "status": {
          "$ref": "#/$defs/status"
        },
        "notes": {
          "type": ["string", "null"]
        }
      }
    }
  }
}
```

### 22.5 Source Trace

```json id="gl-schema-003-def-source-trace"
{
  "$defs": {
    "sourceTrace": {
      "type": "object",
      "required": [
        "source_trace_id",
        "target_id",
        "target_type",
        "source_id",
        "source_type",
        "trace_relation",
        "evidence_status",
        "source_summary",
        "status"
      ],
      "properties": {
        "source_trace_id": {
          "type": "string",
          "minLength": 1
        },
        "target_id": {
          "type": "string",
          "minLength": 1
        },
        "target_type": {
          "type": "string",
          "enum": [
            "term",
            "rule",
            "pack",
            "relation",
            "goal",
            "doctrine",
            "derivation_item",
            "validation_rule"
          ]
        },
        "source_id": {
          "type": "string",
          "minLength": 1
        },
        "source_type": {
          "type": "string",
          "enum": [
            "foundational_document",
            "glossary_pack",
            "consolidation_pack",
            "system_goal",
            "user_decision",
            "anti_collapse_rule",
            "derived_rule"
          ]
        },
        "trace_relation": {
          "type": "string",
          "enum": [
            "direct",
            "derived",
            "supports",
            "constrains",
            "consolidates",
            "aliases",
            "enables",
            "excludes",
            "validates",
            "supersedes"
          ]
        },
        "evidence_status": {
          "type": "string",
          "minLength": 1
        },
        "source_summary": {
          "type": "string",
          "minLength": 1
        },
        "validation_use": {
          "type": ["string", "null"]
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.6 Anti-Collapse Rule

```json id="gl-schema-003-def-anti-collapse"
{
  "$defs": {
    "antiCollapseRule": {
      "type": "object",
      "required": [
        "anti_collapse_rule_id",
        "protected_term_id",
        "protected_term",
        "must_not_collapse_into_label",
        "collapse_type",
        "protected_distinction",
        "severity",
        "source_pack_id",
        "validation_use",
        "status"
      ],
      "properties": {
        "anti_collapse_rule_id": {
          "type": "string",
          "minLength": 1
        },
        "protected_term_id": {
          "type": "string",
          "minLength": 1
        },
        "protected_term": {
          "type": "string",
          "minLength": 1
        },
        "must_not_collapse_into_id": {
          "type": ["string", "null"]
        },
        "must_not_collapse_into_label": {
          "type": "string",
          "minLength": 1
        },
        "collapse_type": {
          "type": "string",
          "enum": [
            "identity",
            "boundary",
            "authority",
            "actor_object",
            "runtime",
            "contract",
            "responsibility",
            "policy",
            "handoff",
            "implementation"
          ]
        },
        "protected_distinction": {
          "type": "string",
          "minLength": 1
        },
        "severity": {
          "$ref": "#/$defs/severity"
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "validation_use": {
          "type": "string",
          "minLength": 1
        },
        "derivation_impact": {
          "type": ["string", "null"]
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.7 Usage Example

```json id="gl-schema-003-def-usage-example"
{
  "$defs": {
    "usageExample": {
      "type": "object",
      "required": [
        "usage_example_id",
        "usage_type",
        "usage_text",
        "source_pack_id",
        "status"
      ],
      "properties": {
        "usage_example_id": {
          "type": "string",
          "minLength": 1
        },
        "usage_type": {
          "type": "string",
          "enum": ["valid", "invalid"]
        },
        "usage_text": {
          "type": "string",
          "minLength": 1
        },
        "reason": {
          "type": ["string", "null"]
        },
        "linked_anti_collapse_rule_id": {
          "type": ["string", "null"]
        },
        "source_pack_id": {
          "type": "string",
          "minLength": 1
        },
        "status": {
          "$ref": "#/$defs/status"
        }
      }
    }
  }
}
```

### 22.8 Validation State

```json id="gl-schema-003-def-validation-state"
{
  "$defs": {
    "validationState": {
      "type": "object",
      "required": [
        "validation_status",
        "finding_count",
        "critical_finding_count",
        "high_finding_count",
        "open_finding_ids"
      ],
      "properties": {
        "validation_status": {
          "type": "string",
          "enum": [
            "not_run",
            "passed",
            "failed",
            "warning",
            "partial"
          ]
        },
        "last_validated_at": {
          "type": ["string", "null"],
          "format": "date-time"
        },
        "finding_count": {
          "type": "integer",
          "minimum": 0
        },
        "critical_finding_count": {
          "type": "integer",
          "minimum": 0
        },
        "high_finding_count": {
          "type": "integer",
          "minimum": 0
        },
        "open_finding_ids": {
          "type": "array",
          "items": {
            "type": "string"
          }
        }
      }
    }
  }
}
```

---

## 23. Export Metadata Schema

### 23.1 Object Shape

```json id="gl-schema-003-export-metadata-object"
{
  "export_id": "GL-EXPORT-000001",
  "exported_at": null,
  "exported_by": null,
  "source_artifacts": [
    "GL-SCHEMA-001",
    "GL-SCHEMA-002"
  ],
  "generation_mode": "manual_formal_draft",
  "validation_status": "not_run",
  "notes": null
}
```

### 23.2 Fields

| Field               | Required | Type        | Description                                     |
| ------------------- | -------- | ----------- | ----------------------------------------------- |
| `export_id`         | Yes      | string      | Export identifier                               |
| `exported_at`       | No       | string/null | ISO timestamp                                   |
| `exported_by`       | No       | string/null | Tool/user/process name                          |
| `source_artifacts`  | Yes      | array       | Source schema/artifact IDs                      |
| `generation_mode`   | Yes      | enum/string | Manual, generated, validated, regenerated, etc. |
| `validation_status` | Yes      | enum        | not_run / passed / failed / warning / partial   |
| `notes`             | No       | string/null | Optional export notes                           |

---

## 24. JSON Validation Rules

### 24.1 File-Level Validation

|                Rule ID | Validation Rule                                                                                                                             | Severity |
| ---------------------: | ------------------------------------------------------------------------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-003-FVAL-001 | Main JSON artifact must include `schema_version`, `schema_id`, `project`, `artifact_type`, `generated_from`, `terms`, and `export_metadata` | Critical |
| GL-SCHEMA-003-FVAL-002 | `schema_id` must equal `GL-SCHEMA-003`                                                                                                      | High     |
| GL-SCHEMA-003-FVAL-003 | `project` must equal `Assembler System`                                                                                                     | High     |
| GL-SCHEMA-003-FVAL-004 | `artifact_type` must be controlled                                                                                                          | High     |
| GL-SCHEMA-003-FVAL-005 | JSON must be valid UTF-8                                                                                                                    | Critical |
| GL-SCHEMA-003-FVAL-006 | JSON must parse without duplicate object keys                                                                                               | Critical |

### 24.2 Term-Level Validation

|                Rule ID | Validation Rule                                                        | Severity |
| ---------------------: | ---------------------------------------------------------------------- | -------- |
| GL-SCHEMA-003-TVAL-001 | Every term object must have a unique `term_id`                         | Critical |
| GL-SCHEMA-003-TVAL-002 | Every term object must have a non-empty `canonical_term`               | Critical |
| GL-SCHEMA-003-TVAL-003 | Every active canonical term must have at least one family membership   | High     |
| GL-SCHEMA-003-TVAL-004 | Every active canonical term must have at least one category membership | High     |
| GL-SCHEMA-003-TVAL-005 | Every `canonical_full` term must have at least one definition section  | Critical |
| GL-SCHEMA-003-TVAL-006 | Every `canonical_full` term must have at least one source trace        | Critical |
| GL-SCHEMA-003-TVAL-007 | Every alias term must include `canonical_target_term_id`               | Critical |
| GL-SCHEMA-003-TVAL-008 | Deprecated terms should include notes or supersession path             | Medium   |

### 24.3 Relation Validation

|                Rule ID | Validation Rule                                                              | Severity |
| ---------------------: | ---------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-003-RVAL-001 | Related-term target IDs must resolve to known terms or permitted seeds       | High     |
| GL-SCHEMA-003-RVAL-002 | Nested relation `source_term_id` should match parent `term_id`               | High     |
| GL-SCHEMA-003-RVAL-003 | Directed relation semantics must not be reversed                             | High     |
| GL-SCHEMA-003-RVAL-004 | `produces` should not point from object to actor unless explicitly justified | High     |
| GL-SCHEMA-003-RVAL-005 | Alias relationships should correspond to alias objects                       | Medium   |

### 24.4 Source Trace Validation

|                Rule ID | Validation Rule                                            | Severity |
| ---------------------: | ---------------------------------------------------------- | -------- |
| GL-SCHEMA-003-SVAL-001 | Critical canonical terms must include active source traces | Critical |
| GL-SCHEMA-003-SVAL-002 | Source trace target must be clear                          | High     |
| GL-SCHEMA-003-SVAL-003 | Source trace relation must be controlled                   | High     |
| GL-SCHEMA-003-SVAL-004 | Evidence status must be explicit                           | High     |
| GL-SCHEMA-003-SVAL-005 | `needs_validation` traces must remain visible in findings  | Medium   |

### 24.5 Anti-Collapse Validation

|                 Rule ID | Validation Rule                                          | Severity |
| ----------------------: | -------------------------------------------------------- | -------- |
| GL-SCHEMA-003-ACVAL-001 | Anti-collapse rules must include protected term ID       | Critical |
| GL-SCHEMA-003-ACVAL-002 | Anti-collapse rules must include collapse target label   | Critical |
| GL-SCHEMA-003-ACVAL-003 | Critical anti-collapse rules must include validation use | High     |
| GL-SCHEMA-003-ACVAL-004 | Collapse type must be controlled                         | High     |
| GL-SCHEMA-003-ACVAL-005 | Protected term must resolve to a known term              | High     |

---

## 25. JSON Population Readiness

### 25.1 Population Order

JSON population should happen after CSV normalization.

Recommended order:

```text id="gl-schema-003-population-order"
1. controlled values
2. pack index
3. base term objects
4. family memberships
5. category memberships
6. aliases
7. entry sections
8. related terms
9. source traces
10. anti-collapse rules
11. usage examples
12. validation rules
13. validation findings
14. export metadata
```

### 25.2 Assembly Rule

```text id="gl-schema-003-assembly-rule"
JSON term objects should be assembled around term_id after all normalized
records have been validated for primary key and foreign key consistency.
```

### 25.3 Why JSON Comes After CSV

CSV defines row grains and join keys.

JSON assembles those rows into nested term objects.

Therefore:

```text id="gl-schema-003-csv-before-json"
CSV normalization before JSON object assembly.
```

This prevents JSON objects from hiding unresolved joins, orphaned aliases, invalid references, or unvalidated source traces.

---

## 26. Markdown / CSV / JSON Relationship

### 26.1 Representation Roles

| Representation     | Role                                                                                   |
| ------------------ | -------------------------------------------------------------------------------------- |
| Markdown           | Human-governed canonical authoring form                                                |
| CSV                | Normalized tabular representation for review, validation, and joins                    |
| JSON               | Structured object representation for tooling, APIs, validation, and database-readiness |
| Validation Reports | Output artifacts produced from schema and content checks                               |

### 26.2 Directional Derivation

```text id="gl-schema-003-directional-derivation"
Canonical meaning
→ Markdown entry schema
→ CSV normalization schema
→ JSON object schema
→ representation mapping
→ population
→ validation
```

### 26.3 Non-Reversal Rule

```text id="gl-schema-003-non-reversal-rule"
Generated JSON must not become the authority that silently rewrites canonical
Markdown meaning.
```

If JSON reveals inconsistency, the correction must return to:

1. content pack,
2. Markdown entry,
3. CSV normalized row,
4. source trace,
5. controlled value,
6. validation rule.

---

## 27. JSON Schema Exit Criteria

|              Record ID | Exit Criterion                                  | Status   |
| ---------------------: | ----------------------------------------------- | -------- |
| GL-SCHEMA-003-EXIT-001 | JSON artifact set is defined                    | Complete |
| GL-SCHEMA-003-EXIT-002 | Top-level JSON document model is defined        | Complete |
| GL-SCHEMA-003-EXIT-003 | Term object schema is defined                   | Complete |
| GL-SCHEMA-003-EXIT-004 | Family and category object schemas are defined  | Complete |
| GL-SCHEMA-003-EXIT-005 | Alias object schema is defined                  | Complete |
| GL-SCHEMA-003-EXIT-006 | Entry section object schema is defined          | Complete |
| GL-SCHEMA-003-EXIT-007 | Related term object schema is defined           | Complete |
| GL-SCHEMA-003-EXIT-008 | Source trace object schema is defined           | Complete |
| GL-SCHEMA-003-EXIT-009 | Anti-collapse object schema is defined          | Complete |
| GL-SCHEMA-003-EXIT-010 | Usage example object schema is defined          | Complete |
| GL-SCHEMA-003-EXIT-011 | Controlled values JSON schema is defined        | Complete |
| GL-SCHEMA-003-EXIT-012 | Validation rule and finding schemas are defined | Complete |
| GL-SCHEMA-003-EXIT-013 | JSON Schema Draft 2020-12 target is declared    | Complete |
| GL-SCHEMA-003-EXIT-014 | Population and assembly order is defined        | Complete |
| GL-SCHEMA-003-EXIT-015 | Markdown / CSV / JSON relationship is defined   | Complete |

---

## 28. Summary

`GL-SCHEMA-003_JSON_Schema_Definitions.md` defines the structured JSON representation model for the Assembler System glossary.

It preserves the governing rule:

```text id="gl-schema-003-summary-rule"
JSON is a derived structured representation.
Markdown remains the human-readable authoring source.
CSV remains the normalized tabular join source.
JSON enables tooling, validation, API-readiness, and future database derivation.
```

This pack prepares the next schema artifact:

```text id="gl-schema-003-next"
GL-SCHEMA-004_Representation_Mapping.md
```

```
```
