
# GL-SCHEMA-004 — Representation Mapping

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-SCHEMA-004-DOC-001 | Document Title | GL-SCHEMA-004_Representation_Mapping.md |
| GL-SCHEMA-004-DOC-002 | Formal Version | Formal Draft V1 |
| GL-SCHEMA-004-DOC-003 | Project | Assembler System |
| GL-SCHEMA-004-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-SCHEMA-004-DOC-005 | Document Type | Schema / Representation Mapping Pack |
| GL-SCHEMA-004-DOC-006 | Language | English |
| GL-SCHEMA-004-DOC-007 | Status | Formal Draft V1 |
| GL-SCHEMA-004-DOC-008 | Depends On | GL-SCHEMA-001_Markdown_Entry_Schema.md, GL-SCHEMA-002_CSV_Schema_Definitions.md, GL-SCHEMA-003_JSON_Schema_Definitions.md, GL-CONT-000 through GL-CONT-010, Unified Glossary Content Consolidation Pack, GL-CONS-002, GL-CONS-003 |
| GL-SCHEMA-004-DOC-009 | Scope | Mapping rules between Markdown, CSV, and JSON representations; field-level mapping; section mapping; join-key mapping; validation checkpoints; round-trip rules |
| GL-SCHEMA-004-DOC-010 | Excluded From This Pack | Actual glossary population, full Markdown generation, CSV file creation, JSON instance generation, PostgreSQL DDL, final database schema, implementation code |
| GL-SCHEMA-004-DOC-011 | Enables | Population Packs, Validation Packs, Coverage Reports, Master Glossary Assembly, JSON generation, database-readiness derivation |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical mapping between the Assembler System glossary representations:

```text
Markdown
CSV
JSON
````

It answers the question:

```text
How should governed glossary meaning move from human-authored Markdown entries
into normalized CSV rows and then into structured JSON objects without losing
semantic richness, source traceability, anti-collapse constraints, join-key
discipline, or validation readiness?
```

This pack is not another content pack.

It is not a schema replacement.

It is the representation-mapping authority that governs transformation between the existing schema packs.

### 2.2 Mapping Role

The representation mapping layer performs seven roles.

|              Record ID | Role                     | Description                                                                         |
| ---------------------: | ------------------------ | ----------------------------------------------------------------------------------- |
| GL-SCHEMA-004-ROLE-001 | Direction Control        | Defines the valid direction of representation derivation                            |
| GL-SCHEMA-004-ROLE-002 | Field Mapping            | Maps Markdown entry fields to CSV columns and JSON object fields                    |
| GL-SCHEMA-004-ROLE-003 | Section Mapping          | Maps long-form Markdown sections to CSV section rows and JSON section objects       |
| GL-SCHEMA-004-ROLE-004 | Relation Mapping         | Maps related terms, aliases, source traces, usage examples, and anti-collapse rules |
| GL-SCHEMA-004-ROLE-005 | Join-Key Preservation    | Ensures all representations use canonical IDs rather than text similarity           |
| GL-SCHEMA-004-ROLE-006 | Validation Checkpointing | Defines where validation must occur during conversion                               |
| GL-SCHEMA-004-ROLE-007 | Round-Trip Governance    | Defines what can and cannot be regenerated across Markdown, CSV, and JSON           |

### 2.3 Non-Purpose

This pack does not populate glossary data.

It does not generate final `Glossary.md`.

It does not generate CSV files.

It does not generate JSON instances.

It does not define new terms.

It does not modify canonical glossary meaning.

It does not decide final database schema.

It does not define implementation packages or C++ classes.

It defines how representations must map when population and validation begin.

---

## 3. Representation Hierarchy

### 3.1 Canonical Direction

The canonical direction is:

```text id="gl-schema-004-canonical-direction"
Canonical meaning
→ Markdown entry schema
→ CSV normalized representation
→ JSON object representation
→ validation reports
→ database-readiness derivation
```

### 3.2 Representation Authority Rule

```text id="gl-schema-004-authority-rule"
Markdown is the human-governed authoring representation.
CSV is the normalized join and validation representation.
JSON is the assembled structured object representation.
Validation reports are derivative review artifacts.
```

### 3.3 Non-Reversal Rule

```text id="gl-schema-004-non-reversal-rule"
Generated CSV or JSON must not silently become the authority that rewrites
canonical Markdown meaning.
```

If CSV or JSON reveals inconsistency, the correction must return to one of:

1. source content pack,
2. canonical Markdown entry,
3. source trace record,
4. controlled value definition,
5. anti-collapse rule,
6. validation rule.

### 3.4 Representation Grain Rule

```text id="gl-schema-004-grain-rule"
Each representation has a different grain and must preserve that grain explicitly.
```

| Representation    | Primary Grain                                 | Meaning                             |
| ----------------- | --------------------------------------------- | ----------------------------------- |
| Markdown          | One term entry or governance document section | Human-readable semantic unit        |
| CSV               | One normalized row per declared row grain     | Joinable validation unit            |
| JSON              | One assembled object or object collection     | Tooling and structured payload unit |
| Validation Report | One finding per failed or warning condition   | Review and correction unit          |

---

## 4. Mapping Principles

### 4.1 Meaning Preservation Principle

```text id="gl-schema-004-meaning-preservation"
Mapping must preserve existing glossary meaning.
It must not compress, reinterpret, or create meaning.
```

### 4.2 Stable ID Principle

```text id="gl-schema-004-stable-id-principle"
All representation mappings must use stable canonical IDs as join keys.
```

Text labels such as canonical terms, section titles, or display names may support readability.

They must not replace IDs.

### 4.3 One Semantic Field, One Mapping Rule

```text id="gl-schema-004-one-field-rule"
Every semantic field that crosses representations should have one declared
mapping rule.
```

### 4.4 Multi-Valued Field Expansion Principle

```text id="gl-schema-004-multivalue-expansion"
Multi-valued Markdown fields must be expanded into normalized CSV rows before
being assembled into JSON arrays.
```

Examples:

1. `Family = SYS / CPP`
2. `Category = carrier_object / governed_object`
3. multiple related terms,
4. multiple source traces,
5. multiple anti-collapse targets,
6. multiple usage examples.

### 4.5 Long-Form Section Preservation Principle

```text id="gl-schema-004-longform-preservation"
Long-form Markdown sections must not be discarded merely because CSV is tabular.
```

Markdown prose must be preserved in `glossary_entry_sections.csv` and then assembled into JSON `sections[]`.

### 4.6 Controlled Value Principle

```text id="gl-schema-004-controlled-values"
Controlled values must be validated before JSON assembly.
```

This applies to:

1. `entry_maturity`,
2. `entry_profile`,
3. `family_code`,
4. `category_code`,
5. `status`,
6. `severity`,
7. `source_type`,
8. `trace_relation`,
9. `relationship_type`,
10. `collapse_type`,
11. `usage_type`,
12. `validation_status`.

### 4.7 No Hidden Lists Principle

```text id="gl-schema-004-no-hidden-lists"
A semantically important list must not remain hidden inside a single CSV cell
when it requires validation, joining, or JSON array assembly.
```

### 4.8 Round-Trip Limitation Principle

```text id="gl-schema-004-round-trip-limitation"
Round-trip regeneration is controlled, not lossless formatting reconstruction.
```

The target is semantic equivalence, not exact Markdown formatting equivalence.

---

## 5. Representation Mapping Overview

### 5.1 Mapping Path

```text id="gl-schema-004-mapping-path"
Markdown term entry
→ parsed semantic fields
→ normalized CSV rows
→ validated CSV row set
→ assembled JSON term object
→ JSON schema validation
→ validation report
```

### 5.2 Mapping Stages

|               Record ID | Stage          | Input                  | Output                   | Purpose                                                        |
| ----------------------: | -------------- | ---------------------- | ------------------------ | -------------------------------------------------------------- |
| GL-SCHEMA-004-STAGE-001 | Markdown Parse | Markdown entry         | Parsed semantic fields   | Extract term identity, fields, sections, relations, traces     |
| GL-SCHEMA-004-STAGE-002 | CSV Normalize  | Parsed semantic fields | CSV rows                 | Create row-grain-specific normalized tables                    |
| GL-SCHEMA-004-STAGE-003 | CSV Validate   | CSV rows               | CSV validation findings  | Check keys, required fields, controlled values, orphan rows    |
| GL-SCHEMA-004-STAGE-004 | JSON Assemble  | Validated CSV rows     | JSON objects             | Assemble nested term objects around `term_id`                  |
| GL-SCHEMA-004-STAGE-005 | JSON Validate  | JSON objects           | JSON validation findings | Check schema, nested constraints, cross-object rules           |
| GL-SCHEMA-004-STAGE-006 | Report         | Validation findings    | Reviewable report        | Prepare correction workflow                                    |
| GL-SCHEMA-004-STAGE-007 | Correction     | Source artifacts       | Updated source           | Fix meaning or representation errors at proper authority layer |

---

## 6. Markdown to CSV Mapping

### 6.1 Main Term Fields

|       Mapping ID | Markdown Source                                   | CSV File             | CSV Column                 | Required    | Notes                                    |
| ---------------: | ------------------------------------------------- | -------------------- | -------------------------- | ----------- | ---------------------------------------- |
| GL-MAP-MDCSV-001 | `Term ID` field                                   | `glossary_terms.csv` | `term_id`                  | Yes         | Primary term identifier                  |
| GL-MAP-MDCSV-002 | `Canonical Term` field                            | `glossary_terms.csv` | `canonical_term`           | Yes         | Human-readable canonical label           |
| GL-MAP-MDCSV-003 | Optional display title                            | `glossary_terms.csv` | `display_term`             | No          | May duplicate canonical term             |
| GL-MAP-MDCSV-004 | Entry profile inferred from entry type            | `glossary_terms.csv` | `entry_profile`            | Yes         | Must use controlled values               |
| GL-MAP-MDCSV-005 | `Entry Maturity` field                            | `glossary_terms.csv` | `entry_maturity`           | Yes         | Must use controlled values               |
| GL-MAP-MDCSV-006 | Default or declared status                        | `glossary_terms.csv` | `status`                   | Yes         | Usually `active`                         |
| GL-MAP-MDCSV-007 | `Ownership Scope` field                           | `glossary_terms.csv` | `ownership_scope`          | Yes         | May later be normalized                  |
| GL-MAP-MDCSV-008 | `Evidence Status` field                           | `glossary_terms.csv` | `evidence_status`          | Yes         | Explicit evidence classification         |
| GL-MAP-MDCSV-009 | Primary family from `Family`                      | `glossary_terms.csv` | `primary_family_code`      | Yes         | Also normalized to family table          |
| GL-MAP-MDCSV-010 | Primary category from `Category`                  | `glossary_terms.csv` | `primary_category`         | Yes         | Also normalized to category table        |
| GL-MAP-MDCSV-011 | First sentence or curated summary from Definition | `glossary_terms.csv` | `definition_short`         | Yes         | Short definition only                    |
| GL-MAP-MDCSV-012 | Source pack identifier                            | `glossary_terms.csv` | `introduced_in_pack_id`    | Yes         | Pack where term was introduced           |
| GL-MAP-MDCSV-013 | Consolidation pack identifier                     | `glossary_terms.csv` | `consolidated_by_pack_id`  | No          | Usually UGCC or later master pack        |
| GL-MAP-MDCSV-014 | Alias target if alias entry                       | `glossary_terms.csv` | `canonical_target_term_id` | Conditional | Required for alias profile               |
| GL-MAP-MDCSV-015 | Notes section or editorial notes                  | `glossary_terms.csv` | `notes`                    | No          | Should not carry canonical meaning alone |

### 6.2 Family Mapping

|           Mapping ID | Markdown Source         | CSV File                     | CSV Grain                          | Notes                       |
| -------------------: | ----------------------- | ---------------------------- | ---------------------------------- | --------------------------- |
| GL-MAP-MDCSV-FAM-001 | `Family` field          | `glossary_term_families.csv` | One row per term-family membership | Split multi-family values   |
| GL-MAP-MDCSV-FAM-002 | First family code       | `glossary_term_families.csv` | Primary membership row             | `family_role = primary`     |
| GL-MAP-MDCSV-FAM-003 | Additional family codes | `glossary_term_families.csv` | Secondary membership rows          | `family_role = secondary`   |
| GL-MAP-MDCSV-FAM-004 | Pack source             | `glossary_term_families.csv` | Source field                       | Usually source content pack |

### 6.3 Category Mapping

|           Mapping ID | Markdown Source       | CSV File                       | CSV Grain                            | Notes                            |
| -------------------: | --------------------- | ------------------------------ | ------------------------------------ | -------------------------------- |
| GL-MAP-MDCSV-CAT-001 | `Category` field      | `glossary_term_categories.csv` | One row per term-category membership | Split slash-delimited categories |
| GL-MAP-MDCSV-CAT-002 | First category        | `glossary_term_categories.csv` | Primary category row                 | `category_role = primary`        |
| GL-MAP-MDCSV-CAT-003 | Additional categories | `glossary_term_categories.csv` | Secondary category rows              | `category_role = secondary`      |
| GL-MAP-MDCSV-CAT-004 | Pack source           | `glossary_term_categories.csv` | Source field                         | Usually source content pack      |

### 6.4 Long-Form Section Mapping

|           Mapping ID | Markdown Section                | CSV File                      | `section_type`             | Required For             |
| -------------------: | ------------------------------- | ----------------------------- | -------------------------- | ------------------------ |
| GL-MAP-MDCSV-SEC-001 | `#### Definition`               | `glossary_entry_sections.csv` | `definition`               | canonical_full           |
| GL-MAP-MDCSV-SEC-002 | `#### Architectural Role`       | `glossary_entry_sections.csv` | `architectural_role`       | canonical_full           |
| GL-MAP-MDCSV-SEC-003 | `#### Working Definition`       | `glossary_entry_sections.csv` | `working_definition`       | canonical_partial / seed |
| GL-MAP-MDCSV-SEC-004 | `#### Known Constraints`        | `glossary_entry_sections.csv` | `known_constraints`        | partial / future         |
| GL-MAP-MDCSV-SEC-005 | `#### Open Clarifications`      | `glossary_entry_sections.csv` | `open_clarifications`      | seed / partial           |
| GL-MAP-MDCSV-SEC-006 | `#### Future Derivation Role`   | `glossary_entry_sections.csv` | `future_derivation_role`   | future_derivation        |
| GL-MAP-MDCSV-SEC-007 | `#### Derivation Preconditions` | `glossary_entry_sections.csv` | `derivation_preconditions` | future_derivation        |
| GL-MAP-MDCSV-SEC-008 | `#### Invalid Premature Use`    | `glossary_entry_sections.csv` | `invalid_premature_use`    | future_derivation        |
| GL-MAP-MDCSV-SEC-009 | `#### Notes`                    | `glossary_entry_sections.csv` | `notes`                    | optional                 |

### 6.5 Related Terms Mapping

|           Mapping ID | Markdown Source               | CSV File                     | CSV Grain                     | Notes                                |
| -------------------: | ----------------------------- | ---------------------------- | ----------------------------- | ------------------------------------ |
| GL-MAP-MDCSV-REL-001 | `#### Related Terms` list     | `glossary_related_terms.csv` | One row per related-term link | Use target term IDs where known      |
| GL-MAP-MDCSV-REL-002 | Explicit relationship wording | `glossary_related_terms.csv` | Relationship type field       | May be `related` if unspecified      |
| GL-MAP-MDCSV-REL-003 | Directional relation in prose | `glossary_related_terms.csv` | `directionality = directed`   | Example: produces, receives, governs |
| GL-MAP-MDCSV-REL-004 | Non-directional relation      | `glossary_related_terms.csv` | `directionality = undirected` | Example: related                     |

### 6.6 Alias Mapping

|             Mapping ID | Markdown Source              | CSV File               | CSV Grain                 | Notes                                            |
| ---------------------: | ---------------------------- | ---------------------- | ------------------------- | ------------------------------------------------ |
| GL-MAP-MDCSV-ALIAS-001 | Alias entry                  | `glossary_aliases.csv` | One row per alias mapping | Alias must point to canonical target             |
| GL-MAP-MDCSV-ALIAS-002 | Alias usage rule             | `glossary_aliases.csv` | `valid_usage_policy`      | allowed / discouraged / prohibited / source_only |
| GL-MAP-MDCSV-ALIAS-003 | Legacy/source alias evidence | `glossary_aliases.csv` | `evidence_status`         | Example: `legacy_alias`                          |
| GL-MAP-MDCSV-ALIAS-004 | Alias notes                  | `glossary_aliases.csv` | `notes`                   | Required for deprecated aliases                  |

### 6.7 Source Trace Mapping

|           Mapping ID | Markdown Source           | CSV File                     | CSV Grain                | Notes                                    |
| -------------------: | ------------------------- | ---------------------------- | ------------------------ | ---------------------------------------- |
| GL-MAP-MDCSV-SRC-001 | `#### Source Trace` table | `glossary_source_traces.csv` | One row per source trace | Target may be term, rule, relation, pack |
| GL-MAP-MDCSV-SRC-002 | Source type               | `glossary_source_traces.csv` | `source_type`            | Controlled value                         |
| GL-MAP-MDCSV-SRC-003 | Source description        | `glossary_source_traces.csv` | `source_summary`         | Short contribution summary               |
| GL-MAP-MDCSV-SRC-004 | Evidence status           | `glossary_source_traces.csv` | `evidence_status`        | Required                                 |
| GL-MAP-MDCSV-SRC-005 | Validation use            | `glossary_source_traces.csv` | `validation_use`         | Optional but recommended                 |

### 6.8 Anti-Collapse Mapping

|          Mapping ID | Markdown Source                       | CSV File                           | CSV Grain                         | Notes                                                 |
| ------------------: | ------------------------------------- | ---------------------------------- | --------------------------------- | ----------------------------------------------------- |
| GL-MAP-MDCSV-AC-001 | `#### Must Not Be Confused With` list | `glossary_anti_collapse_rules.csv` | One row per protected distinction | Each item should become a rule where validation-grade |
| GL-MAP-MDCSV-AC-002 | Anti-collapse index rules             | `glossary_anti_collapse_rules.csv` | One row per index rule            | GL-CONS-002 may seed these rows                       |
| GL-MAP-MDCSV-AC-003 | Severity model                        | `glossary_anti_collapse_rules.csv` | `severity`                        | critical / high / medium / low                        |
| GL-MAP-MDCSV-AC-004 | Collapse target                       | `glossary_anti_collapse_rules.csv` | `must_not_collapse_into_label`    | Target ID optional when target is category/system     |
| GL-MAP-MDCSV-AC-005 | Protected distinction                 | `glossary_anti_collapse_rules.csv` | `protected_distinction`           | Required                                              |

### 6.9 Usage Example Mapping

|           Mapping ID | Markdown Source           | CSV File                      | CSV Grain                      | Notes                         |
| -------------------: | ------------------------- | ----------------------------- | ------------------------------ | ----------------------------- |
| GL-MAP-MDCSV-USE-001 | `#### Valid Usage` list   | `glossary_usage_examples.csv` | One row per valid example      | `usage_type = valid`          |
| GL-MAP-MDCSV-USE-002 | `#### Invalid Usage` list | `glossary_usage_examples.csv` | One row per invalid example    | `usage_type = invalid`        |
| GL-MAP-MDCSV-USE-003 | Invalid usage reason      | `glossary_usage_examples.csv` | `reason`                       | Recommended                   |
| GL-MAP-MDCSV-USE-004 | Linked guard rule         | `glossary_usage_examples.csv` | `linked_anti_collapse_rule_id` | Recommended for invalid usage |

---

## 7. CSV to JSON Mapping

### 7.1 Term Object Assembly

|              Mapping ID | CSV Source                   | JSON Target           | JSON Field                 | Rule                                     |
| ----------------------: | ---------------------------- | --------------------- | -------------------------- | ---------------------------------------- |
| GL-MAP-CSVJSON-TERM-001 | `glossary_terms.csv.term_id` | `glossary.terms.json` | `terms[].term_id`          | One JSON object per term row             |
| GL-MAP-CSVJSON-TERM-002 | `canonical_term`             | term object           | `canonical_term`           | Required                                 |
| GL-MAP-CSVJSON-TERM-003 | `display_term`               | term object           | `display_term`             | Optional                                 |
| GL-MAP-CSVJSON-TERM-004 | `entry_profile`              | term object           | `entry_profile`            | Controlled value                         |
| GL-MAP-CSVJSON-TERM-005 | `entry_maturity`             | term object           | `entry_maturity`           | Controlled value                         |
| GL-MAP-CSVJSON-TERM-006 | `status`                     | term object           | `status`                   | Controlled value                         |
| GL-MAP-CSVJSON-TERM-007 | `ownership_scope`            | term object           | `ownership_scope`          | Required string                          |
| GL-MAP-CSVJSON-TERM-008 | `evidence_status`            | term object           | `evidence_status`          | Required string                          |
| GL-MAP-CSVJSON-TERM-009 | `primary_family_code`        | term object           | `primary_family_code`      | Must match primary family membership     |
| GL-MAP-CSVJSON-TERM-010 | `primary_category`           | term object           | `primary_category`         | Should match primary category membership |
| GL-MAP-CSVJSON-TERM-011 | `definition_short`           | term object           | `definition_short`         | Required                                 |
| GL-MAP-CSVJSON-TERM-012 | `introduced_in_pack_id`      | term object           | `introduced_in_pack_id`    | Required                                 |
| GL-MAP-CSVJSON-TERM-013 | `consolidated_by_pack_id`    | term object           | `consolidated_by_pack_id`  | Optional                                 |
| GL-MAP-CSVJSON-TERM-014 | `canonical_target_term_id`   | term object           | `canonical_target_term_id` | Required when alias                      |
| GL-MAP-CSVJSON-TERM-015 | `notes`                      | term object           | `notes`                    | Optional                                 |

### 7.2 Nested Array Assembly

|              Mapping ID | CSV File                           | Join Key                                | JSON Target                                         |
| ----------------------: | ---------------------------------- | --------------------------------------- | --------------------------------------------------- |
| GL-MAP-CSVJSON-NEST-001 | `glossary_term_families.csv`       | `term_id`                               | `terms[].families[]`                                |
| GL-MAP-CSVJSON-NEST-002 | `glossary_term_categories.csv`     | `term_id`                               | `terms[].categories[]`                              |
| GL-MAP-CSVJSON-NEST-003 | `glossary_aliases.csv`             | `term_id` or `canonical_target_term_id` | `terms[].aliases[]`                                 |
| GL-MAP-CSVJSON-NEST-004 | `glossary_entry_sections.csv`      | `term_id`                               | `terms[].sections[]`                                |
| GL-MAP-CSVJSON-NEST-005 | `glossary_related_terms.csv`       | `source_term_id`                        | `terms[].related_terms[]`                           |
| GL-MAP-CSVJSON-NEST-006 | `glossary_source_traces.csv`       | `target_id`                             | `terms[].source_traces[]` when `target_type = term` |
| GL-MAP-CSVJSON-NEST-007 | `glossary_anti_collapse_rules.csv` | `protected_term_id`                     | `terms[].anti_collapse_rules[]`                     |
| GL-MAP-CSVJSON-NEST-008 | `glossary_usage_examples.csv`      | `term_id`                               | `terms[].usage_examples[]`                          |
| GL-MAP-CSVJSON-NEST-009 | `glossary_validation_findings.csv` | `target_id`                             | `terms[].validation_state.open_finding_ids[]`       |

### 7.3 Controlled Values Assembly

|            Mapping ID | CSV Source                       | JSON Artifact                     | JSON Target                     |
| --------------------: | -------------------------------- | --------------------------------- | ------------------------------- |
| GL-MAP-CSVJSON-CV-001 | `glossary_controlled_values.csv` | `glossary.controlled-values.json` | `value_sets`                    |
| GL-MAP-CSVJSON-CV-002 | `value_set` column               | controlled values artifact        | object key under `value_sets`   |
| GL-MAP-CSVJSON-CV-003 | controlled value rows            | controlled values artifact        | array entries                   |
| GL-MAP-CSVJSON-CV-004 | status column                    | controlled values artifact        | active/pending/deprecated state |

### 7.4 Validation Rule Assembly

|             Mapping ID | CSV Source                         | JSON Artifact                       | JSON Target                           |
| ---------------------: | ---------------------------------- | ----------------------------------- | ------------------------------------- |
| GL-MAP-CSVJSON-VAL-001 | `glossary_validation_rules.csv`    | `glossary.validation-rules.json`    | validation rule objects               |
| GL-MAP-CSVJSON-VAL-002 | `glossary_validation_findings.csv` | `glossary.validation-findings.json` | validation finding objects            |
| GL-MAP-CSVJSON-VAL-003 | validation findings by target      | term object                         | `validation_state` summary            |
| GL-MAP-CSVJSON-VAL-004 | open finding IDs                   | term object                         | `validation_state.open_finding_ids[]` |

---

## 8. JSON to Markdown Regeneration Mapping

### 8.1 Regeneration Scope

JSON may be used to regenerate structured Markdown views.

However, regenerated Markdown is a review artifact unless explicitly promoted back into the canonical authoring layer.

### 8.2 Regeneration Rule

```text id="gl-schema-004-json-to-md-rule"
JSON-to-Markdown regeneration must preserve semantic fields and section content,
but it is not allowed to silently overwrite canonical authoring Markdown.
```

### 8.3 Regenerable Markdown Sections

| JSON Source                                            | Markdown Target                  |
| ------------------------------------------------------ | -------------------------------- |
| `term_id` + `canonical_term`                           | Entry heading                    |
| core term fields                                       | Entry field table                |
| `sections[]` where `section_type = definition`         | `#### Definition`                |
| `sections[]` where `section_type = architectural_role` | `#### Architectural Role`        |
| `anti_collapse_rules[]`                                | `#### Must Not Be Confused With` |
| `usage_examples[]` where valid                         | `#### Valid Usage`               |
| `usage_examples[]` where invalid                       | `#### Invalid Usage`             |
| `related_terms[]`                                      | `#### Related Terms`             |
| `source_traces[]`                                      | `#### Source Trace`              |

### 8.4 Non-Regenerable Without Review

The following must not be regenerated into canonical Markdown without human review:

1. inferred definitions,
2. auto-generated anti-collapse explanations,
3. missing source trace replacements,
4. inferred categories,
5. inferred family memberships,
6. validation-derived corrections,
7. alias deprecation decisions,
8. term merges or splits.

---

## 9. Mapping by Entry Profile

### 9.1 Full Canonical Entry

| Markdown Profile | CSV Requirements                                                                                                                                  | JSON Requirements                                |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
| `canonical_full` | Main term row, family rows, category rows, definition section, architectural role section, source trace rows, usage examples, anti-collapse rules | Complete term object with required nested arrays |

### 9.2 Partial Canonical Entry

| Markdown Profile    | CSV Requirements                                                                                             | JSON Requirements                                                     |
| ------------------- | ------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------- |
| `canonical_partial` | Main term row, family/category rows, known sections, source trace if available, open clarification if needed | Term object may have partial sections but must expose evidence status |

### 9.3 Seed Entry

| Markdown Profile | CSV Requirements                                                       | JSON Requirements                                                               |
| ---------------- | ---------------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| `seed`           | Main term row, minimal source/evidence row, open clarification section | Term object must remain visibly incomplete and not be treated as full canonical |

### 9.4 Alias Entry

| Markdown Profile | CSV Requirements                                                 | JSON Requirements                                          |
| ---------------- | ---------------------------------------------------------------- | ---------------------------------------------------------- |
| `alias`          | Main term row with `canonical_target_term_id`, alias mapping row | Term object must include canonical target and alias policy |

### 9.5 Future Derivation Entry

| Markdown Profile    | CSV Requirements                                                                        | JSON Requirements                                                       |
| ------------------- | --------------------------------------------------------------------------------------- | ----------------------------------------------------------------------- |
| `future_derivation` | Main term row, future derivation sections, invalid premature use section, source traces | Term object must preserve future status and non-prematurity constraints |

---

## 10. Mapping Validation Checkpoints

### 10.1 Markdown Parse Validation

|                 Rule ID | Check                                                                     | Severity |
| ----------------------: | ------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-004-MDVAL-001 | Every canonical entry must have a heading with `TERM_ID — Canonical Term` | Critical |
| GL-SCHEMA-004-MDVAL-002 | Field table must include required fields for entry profile                | Critical |
| GL-SCHEMA-004-MDVAL-003 | `canonical_full` entries must include Definition                          | Critical |
| GL-SCHEMA-004-MDVAL-004 | High-risk entries must include anti-collapse content                      | High     |
| GL-SCHEMA-004-MDVAL-005 | Source Trace should be present or explicitly marked incomplete            | High     |

### 10.2 CSV Normalization Validation

|                  Rule ID | Check                                                                | Severity |
| -----------------------: | -------------------------------------------------------------------- | -------- |
| GL-SCHEMA-004-CSVVAL-001 | Every `term_id` in child tables must resolve to `glossary_terms.csv` | Critical |
| GL-SCHEMA-004-CSVVAL-002 | Every term must have exactly one primary family                      | Critical |
| GL-SCHEMA-004-CSVVAL-003 | Every active canonical term must have at least one category          | High     |
| GL-SCHEMA-004-CSVVAL-004 | Alias rows must resolve to canonical target terms                    | Critical |
| GL-SCHEMA-004-CSVVAL-005 | Source trace target IDs must resolve or be marked pending            | High     |
| GL-SCHEMA-004-CSVVAL-006 | Anti-collapse protected term IDs must resolve                        | High     |
| GL-SCHEMA-004-CSVVAL-007 | Controlled values must be valid before JSON assembly                 | Critical |

### 10.3 JSON Assembly Validation

|                   Rule ID | Check                                                                | Severity |
| ------------------------: | -------------------------------------------------------------------- | -------- |
| GL-SCHEMA-004-JSONVAL-001 | JSON term count must match active CSV term row count unless filtered | Critical |
| GL-SCHEMA-004-JSONVAL-002 | Nested arrays must preserve all matching CSV child rows              | Critical |
| GL-SCHEMA-004-JSONVAL-003 | JSON Schema validation must pass for required fields                 | Critical |
| GL-SCHEMA-004-JSONVAL-004 | Alias term objects must include `canonical_target_term_id`           | Critical |
| GL-SCHEMA-004-JSONVAL-005 | `primary_family_code` must match nested primary family               | High     |
| GL-SCHEMA-004-JSONVAL-006 | Critical source traces must not be dropped                           | Critical |
| GL-SCHEMA-004-JSONVAL-007 | Critical anti-collapse rules must not be dropped                     | Critical |

### 10.4 Round-Trip Validation

|                 Rule ID | Check                                                                                     | Severity |
| ----------------------: | ----------------------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-004-RTVAL-001 | Markdown → CSV → JSON must preserve term IDs                                              | Critical |
| GL-SCHEMA-004-RTVAL-002 | Markdown → CSV → JSON must preserve canonical terms                                       | Critical |
| GL-SCHEMA-004-RTVAL-003 | Markdown long-form sections must survive as JSON sections                                 | High     |
| GL-SCHEMA-004-RTVAL-004 | Source traces must preserve target/source relation                                        | High     |
| GL-SCHEMA-004-RTVAL-005 | Anti-collapse rules must preserve protected distinction                                   | High     |
| GL-SCHEMA-004-RTVAL-006 | JSON regenerated Markdown must be semantically equivalent, not necessarily text-identical | Medium   |

---

## 11. Error Handling and Correction Routing

### 11.1 Correction Routing Rule

```text id="gl-schema-004-correction-routing"
A mapping error must be corrected at the earliest authoritative layer where
the error originates.
```

### 11.2 Error Classes

| Error Class              | Example                                     | Correct At                              |
| ------------------------ | ------------------------------------------- | --------------------------------------- |
| Meaning error            | Definition contradicts source pack          | Content pack / Markdown                 |
| Missing required field   | No `term_id`                                | Markdown or CSV extraction              |
| Invalid controlled value | `canonicalFull` instead of `canonical_full` | CSV controlled value normalization      |
| Orphan relation          | Related term ID does not exist              | CSV relation table or term inventory    |
| Lost section             | Definition not copied into CSV section row  | Markdown-to-CSV parser/mapping          |
| JSON nesting loss        | Source trace missing from term object       | JSON assembly process                   |
| Invalid schema shape     | JSON fails schema validation                | JSON generation process                 |
| Authority drift          | JSON implies ownership not in Markdown      | Markdown source and JSON mapping review |

### 11.3 No Silent Repair Rule

```text id="gl-schema-004-no-silent-repair"
Mapping tools must not silently repair canonical IDs, categories, source traces,
or anti-collapse rules without producing validation findings.
```

---

## 12. Mapping Artifacts

### 12.1 Required Mapping Artifacts

|             Record ID | Artifact                          | Purpose                                                    |
| --------------------: | --------------------------------- | ---------------------------------------------------------- |
| GL-SCHEMA-004-ART-001 | `representation_mapping.md`       | Human-readable mapping authority                           |
| GL-SCHEMA-004-ART-002 | `markdown_to_csv_mapping.csv`     | Machine-readable mapping of Markdown fields to CSV columns |
| GL-SCHEMA-004-ART-003 | `csv_to_json_mapping.csv`         | Machine-readable mapping of CSV tables to JSON fields      |
| GL-SCHEMA-004-ART-004 | `json_to_markdown_mapping.csv`    | Controlled regeneration map                                |
| GL-SCHEMA-004-ART-005 | `mapping_validation_rules.csv`    | Mapping-specific validation rules                          |
| GL-SCHEMA-004-ART-006 | `mapping_validation_findings.csv` | Future mapping validation output                           |

### 12.2 Optional Mapping Artifacts

|             Record ID | Artifact                     | Purpose                                           |
| --------------------: | ---------------------------- | ------------------------------------------------- |
| GL-SCHEMA-004-ART-007 | `mapping_manifest.json`      | JSON index of mapping artifacts                   |
| GL-SCHEMA-004-ART-008 | `round_trip_test_cases.json` | Test cases for conversion consistency             |
| GL-SCHEMA-004-ART-009 | `field_lineage_matrix.csv`   | Field-level lineage from Markdown to CSV to JSON  |
| GL-SCHEMA-004-ART-010 | `lossy_fields_report.md`     | Documents fields that cannot round-trip perfectly |

---

## 13. Field Lineage Model

### 13.1 Field Lineage Record

Every mapped field may be represented with the following lineage model.

| Field                 | Meaning                                                 |
| --------------------- | ------------------------------------------------------- |
| `lineage_id`          | Stable field-lineage record ID                          |
| `semantic_field`      | Conceptual field being mapped                           |
| `markdown_source`     | Markdown section or field source                        |
| `csv_file`            | CSV file receiving the data                             |
| `csv_column`          | CSV column receiving the data                           |
| `json_artifact`       | JSON artifact receiving the data                        |
| `json_path`           | JSONPath-like location                                  |
| `mapping_type`        | direct / split / assembled / derived / display_only     |
| `lossiness`           | none / formatting_loss / summary_loss / requires_review |
| `validation_rule_ids` | Related validation rules                                |
| `notes`               | Mapping notes                                           |

### 13.2 Mapping Types

| Mapping Type      | Meaning                                                  |
| ----------------- | -------------------------------------------------------- |
| `direct`          | One source field maps directly to one target field       |
| `split`           | One source field expands into multiple rows or objects   |
| `assembled`       | Multiple CSV rows assemble into one JSON object or array |
| `derived`         | Field is derived from source context or controlled rules |
| `display_only`    | Field supports readability but is not authoritative      |
| `requires_review` | Mapping cannot be automated safely without human review  |

### 13.3 Lossiness Model

| Lossiness             | Meaning                                           |
| --------------------- | ------------------------------------------------- |
| `none`                | Semantic value is preserved exactly               |
| `formatting_loss`     | Markdown formatting may not be reproduced exactly |
| `summary_loss`        | Short summary does not preserve full prose        |
| `requires_review`     | Automated mapping may be incomplete or ambiguous  |
| `not_round_trippable` | Field cannot regenerate canonical source safely   |

---

## 14. Critical Field Lineage Matrix

|  Lineage ID | Semantic Field            | Markdown Source            | CSV Target                                                     | JSON Target                        | Mapping Type            | Lossiness       |
| ----------: | ------------------------- | -------------------------- | -------------------------------------------------------------- | ---------------------------------- | ----------------------- | --------------- |
| GL-LINE-001 | Term ID                   | Field table                | `glossary_terms.term_id`                                       | `terms[].term_id`                  | direct                  | none            |
| GL-LINE-002 | Canonical Term            | Field table / heading      | `glossary_terms.canonical_term`                                | `terms[].canonical_term`           | direct                  | none            |
| GL-LINE-003 | Family                    | Field table                | `glossary_term_families`                                       | `terms[].families[]`               | split / assembled       | none            |
| GL-LINE-004 | Category                  | Field table                | `glossary_term_categories`                                     | `terms[].categories[]`             | split / assembled       | none            |
| GL-LINE-005 | Ownership Scope           | Field table                | `glossary_terms.ownership_scope`                               | `terms[].ownership_scope`          | direct                  | none            |
| GL-LINE-006 | Evidence Status           | Field table                | `glossary_terms.evidence_status`                               | `terms[].evidence_status`          | direct                  | none            |
| GL-LINE-007 | Definition                | Definition section         | `glossary_entry_sections`                                      | `terms[].sections[]`               | section row / assembled | formatting_loss |
| GL-LINE-008 | Definition Short          | Definition section summary | `glossary_terms.definition_short`                              | `terms[].definition_short`         | derived                 | summary_loss    |
| GL-LINE-009 | Architectural Role        | Architectural Role section | `glossary_entry_sections`                                      | `terms[].sections[]`               | section row / assembled | formatting_loss |
| GL-LINE-010 | Related Terms             | Related Terms list         | `glossary_related_terms`                                       | `terms[].related_terms[]`          | split / assembled       | none            |
| GL-LINE-011 | Source Trace              | Source Trace table         | `glossary_source_traces`                                       | `terms[].source_traces[]`          | split / assembled       | none            |
| GL-LINE-012 | Must Not Be Confused With | Anti-collapse section      | `glossary_anti_collapse_rules`                                 | `terms[].anti_collapse_rules[]`    | split / assembled       | requires_review |
| GL-LINE-013 | Valid Usage               | Valid Usage section        | `glossary_usage_examples`                                      | `terms[].usage_examples[]`         | split / assembled       | formatting_loss |
| GL-LINE-014 | Invalid Usage             | Invalid Usage section      | `glossary_usage_examples`                                      | `terms[].usage_examples[]`         | split / assembled       | formatting_loss |
| GL-LINE-015 | Alias Target              | Alias entry                | `glossary_aliases` / `glossary_terms.canonical_target_term_id` | `terms[].canonical_target_term_id` | direct                  | none            |
| GL-LINE-016 | Validation State          | Validation findings        | `glossary_validation_findings`                                 | `terms[].validation_state`         | derived / assembled     | none            |

---

## 15. Round-Trip Test Cases

### 15.1 Required Test Case Families

|            Record ID | Test Family                       | Purpose                                             |
| -------------------: | --------------------------------- | --------------------------------------------------- |
| GL-SCHEMA-004-RT-001 | Full Canonical Term Round Trip    | Verify complete term survives Markdown → CSV → JSON |
| GL-SCHEMA-004-RT-002 | Alias Term Round Trip             | Verify alias target and usage policy survive        |
| GL-SCHEMA-004-RT-003 | Multi-Family Term Round Trip      | Verify family splitting and reassembly              |
| GL-SCHEMA-004-RT-004 | Multi-Category Term Round Trip    | Verify category splitting and reassembly            |
| GL-SCHEMA-004-RT-005 | Source Trace Round Trip           | Verify trace relation preservation                  |
| GL-SCHEMA-004-RT-006 | Anti-Collapse Rule Round Trip     | Verify protected distinction preservation           |
| GL-SCHEMA-004-RT-007 | Future Derivation Term Round Trip | Verify non-prematurity constraints survive          |
| GL-SCHEMA-004-RT-008 | Seed Term Round Trip              | Verify incomplete evidence remains visible          |
| GL-SCHEMA-004-RT-009 | JSON Regenerated Markdown Review  | Verify semantic equivalence of regenerated Markdown |
| GL-SCHEMA-004-RT-010 | Validation Finding Propagation    | Verify findings attach to correct target IDs        |

### 15.2 Minimal Test Case Shape

```json id="gl-schema-004-round-trip-test-case"
{
  "test_case_id": "GL-RT-000001",
  "test_family": "Full Canonical Term Round Trip",
  "source_markdown_entry_id": "GL-OBJ-001",
  "expected_csv_rows": [
    "glossary_terms:GL-OBJ-001",
    "glossary_term_families:GL-OBJ-001:OBJ",
    "glossary_term_categories:GL-OBJ-001:carrier_object"
  ],
  "expected_json_paths": [
    "$.terms[?(@.term_id=='GL-OBJ-001')]",
    "$.terms[?(@.term_id=='GL-OBJ-001')].families",
    "$.terms[?(@.term_id=='GL-OBJ-001')].sections"
  ],
  "expected_validation_status": "passed"
}
```

---

## 16. Mapping Governance Rules

### 16.1 Source-of-Truth Rule

```text id="gl-schema-004-source-of-truth"
Canonical meaning is governed by content packs and Markdown authoring entries.
Representation artifacts must preserve that meaning.
```

### 16.2 Mapping Change Rule

```text id="gl-schema-004-mapping-change-rule"
Any change to a mapping rule must identify which schema pack it affects:
Markdown, CSV, JSON, validation, or future database derivation.
```

### 16.3 Backward Compatibility Rule

```text id="gl-schema-004-backward-compatibility"
Representation mapping changes should avoid breaking existing stable IDs.
```

If a breaking change is unavoidable, the mapping change must include:

1. affected fields,
2. affected artifacts,
3. migration rule,
4. validation rule update,
5. deprecation/supersession note.

### 16.4 No ID Reassignment Rule

```text id="gl-schema-004-no-id-reassignment"
A mapping process must never reassign stable IDs based on row order, heading order,
or display text.
```

### 16.5 Review Before Promotion Rule

```text id="gl-schema-004-review-before-promotion"
Generated artifacts must be reviewed before they become authoritative population
artifacts.
```

---

## 17. Population Readiness Gate

### 17.1 Gate Purpose

Before glossary population begins, this mapping pack requires a readiness gate.

The gate answers:

```text
Are the content packs, schema definitions, mapping rules, controlled values,
and validation checkpoints stable enough to begin population?
```

### 17.2 Readiness Criteria

|              Record ID | Criterion                                        | Required Status |
| ---------------------: | ------------------------------------------------ | --------------- |
| GL-SCHEMA-004-GATE-001 | GL-CONT-000 through GL-CONT-010 available        | Required        |
| GL-SCHEMA-004-GATE-002 | Unified Glossary Content Consolidation available | Required        |
| GL-SCHEMA-004-GATE-003 | Anti-Collapse Index available                    | Required        |
| GL-SCHEMA-004-GATE-004 | Source Trace Index available                     | Required        |
| GL-SCHEMA-004-GATE-005 | Markdown Entry Schema available                  | Required        |
| GL-SCHEMA-004-GATE-006 | CSV Schema Definitions available                 | Required        |
| GL-SCHEMA-004-GATE-007 | JSON Schema Definitions available                | Required        |
| GL-SCHEMA-004-GATE-008 | Representation Mapping approved                  | Required        |
| GL-SCHEMA-004-GATE-009 | Controlled values minimally defined              | Required        |
| GL-SCHEMA-004-GATE-010 | Validation rule families minimally defined       | Required        |

### 17.3 Population Start Rule

```text id="gl-schema-004-population-start-rule"
Population must not begin until representation mapping is stable enough to
prevent uncontrolled drift between Markdown, CSV, and JSON.
```

---

## 18. Validation Pack Enablement

### 18.1 Validation Packs Enabled

This mapping pack enables later validation packs including:

|                Record ID | Future Pack                               | Purpose                                        |
| -----------------------: | ----------------------------------------- | ---------------------------------------------- |
| GL-SCHEMA-004-VAL-EN-001 | Glossary Coverage Validation Pack         | Checks that all required terms are represented |
| GL-SCHEMA-004-VAL-EN-002 | Source Trace Validation Pack              | Checks that terms and rules are not orphaned   |
| GL-SCHEMA-004-VAL-EN-003 | Anti-Collapse Validation Pack             | Checks guard rule preservation                 |
| GL-SCHEMA-004-VAL-EN-004 | Controlled Values Validation Pack         | Checks enum and value consistency              |
| GL-SCHEMA-004-VAL-EN-005 | Representation Round-Trip Validation Pack | Checks Markdown/CSV/JSON mapping integrity     |
| GL-SCHEMA-004-VAL-EN-006 | JSON Schema Validation Pack               | Checks JSON instance conformance               |
| GL-SCHEMA-004-VAL-EN-007 | Database-Readiness Validation Pack        | Checks future relational derivation readiness  |

### 18.2 Validation Finding Routing

| Finding Source            | Route To                                        |
| ------------------------- | ----------------------------------------------- |
| Markdown parse failure    | Markdown authoring correction                   |
| CSV normalization failure | CSV mapping or extraction correction            |
| JSON assembly failure     | JSON generation correction                      |
| Controlled value failure  | Controlled value registry correction            |
| Source trace orphan       | Source trace index or term inventory correction |
| Anti-collapse loss        | Anti-collapse index or term entry correction    |
| Round-trip semantic drift | Representation mapping review                   |

---

## 19. Database Derivation Readiness

### 19.1 Readiness Role

This pack prepares later database derivation by preserving:

1. stable primary keys,
2. join tables,
3. row grains,
4. object assembly rules,
5. controlled values,
6. validation rule records,
7. source trace records,
8. anti-collapse records,
9. field lineage.

### 19.2 Database Non-Purpose Rule

```text id="gl-schema-004-db-non-purpose"
Representation mapping does not define final database schema.
It only preserves the information needed for later PostgreSQL derivation.
```

### 19.3 Likely Future Relational Candidates

| Future Table Candidate         | Derived From                       |
| ------------------------------ | ---------------------------------- |
| `glossary_terms`               | `glossary_terms.csv`               |
| `glossary_term_families`       | `glossary_term_families.csv`       |
| `glossary_term_categories`     | `glossary_term_categories.csv`     |
| `glossary_aliases`             | `glossary_aliases.csv`             |
| `glossary_related_terms`       | `glossary_related_terms.csv`       |
| `glossary_source_traces`       | `glossary_source_traces.csv`       |
| `glossary_anti_collapse_rules` | `glossary_anti_collapse_rules.csv` |
| `glossary_usage_examples`      | `glossary_usage_examples.csv`      |
| `glossary_entry_sections`      | `glossary_entry_sections.csv`      |
| `glossary_controlled_values`   | `glossary_controlled_values.csv`   |
| `glossary_validation_rules`    | `glossary_validation_rules.csv`    |
| `glossary_validation_findings` | `glossary_validation_findings.csv` |
| `glossary_field_lineage`       | Mapping lineage model              |
| `glossary_round_trip_tests`    | Round-trip test case model         |

---

## 20. Exit Criteria

|              Record ID | Exit Criterion                                    | Status   |
| ---------------------: | ------------------------------------------------- | -------- |
| GL-SCHEMA-004-EXIT-001 | Representation hierarchy is defined               | Complete |
| GL-SCHEMA-004-EXIT-002 | Markdown-to-CSV mapping is defined                | Complete |
| GL-SCHEMA-004-EXIT-003 | CSV-to-JSON mapping is defined                    | Complete |
| GL-SCHEMA-004-EXIT-004 | JSON-to-Markdown regeneration rules are defined   | Complete |
| GL-SCHEMA-004-EXIT-005 | Entry profile mapping rules are defined           | Complete |
| GL-SCHEMA-004-EXIT-006 | Mapping validation checkpoints are defined        | Complete |
| GL-SCHEMA-004-EXIT-007 | Error handling and correction routing are defined | Complete |
| GL-SCHEMA-004-EXIT-008 | Mapping artifacts are identified                  | Complete |
| GL-SCHEMA-004-EXIT-009 | Field lineage model is defined                    | Complete |
| GL-SCHEMA-004-EXIT-010 | Round-trip test case families are defined         | Complete |
| GL-SCHEMA-004-EXIT-011 | Population readiness gate is defined              | Complete |
| GL-SCHEMA-004-EXIT-012 | Validation pack enablement is defined             | Complete |
| GL-SCHEMA-004-EXIT-013 | Database derivation readiness boundary is defined | Complete |

---

## 21. Summary

`GL-SCHEMA-004_Representation_Mapping.md` defines the governed transformation layer between the Assembler System glossary representations.

It preserves the core rule:

```text id="gl-schema-004-summary-rule"
Markdown preserves canonical authoring meaning.
CSV preserves normalized row grain and join discipline.
JSON preserves structured object assembly.
Representation mapping preserves the rules that keep all three aligned.
```

This closes the current Schema & Representation Definition sequence:

```text id="gl-schema-004-schema-sequence"
GL-SCHEMA-001_Markdown_Entry_Schema.md
GL-SCHEMA-002_CSV_Schema_Definitions.md
GL-SCHEMA-003_JSON_Schema_Definitions.md
GL-SCHEMA-004_Representation_Mapping.md
```

The next correct workstream is no longer another schema-definition pack.

The next correct workstream is one of:

```text id="gl-schema-004-next-options"
1. Glossary Population Pack — Formal Draft V1
2. Glossary Validation & Coverage Pack — Formal Draft V1
3. Roadmap return point: schema-ready continuation into implementation derivation planning
```

```
```
