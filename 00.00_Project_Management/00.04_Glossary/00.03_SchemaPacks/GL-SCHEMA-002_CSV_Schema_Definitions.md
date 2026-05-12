
# GL-SCHEMA-002 — CSV Schema Definitions

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-SCHEMA-002-DOC-001 | Document Title | GL-SCHEMA-002_CSV_Schema_Definitions.md |
| GL-SCHEMA-002-DOC-002 | Formal Version | Formal Draft V1 |
| GL-SCHEMA-002-DOC-003 | Project | Assembler System |
| GL-SCHEMA-002-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-SCHEMA-002-DOC-005 | Document Type | Schema / Representation Definition Pack |
| GL-SCHEMA-002-DOC-006 | Language | English |
| GL-SCHEMA-002-DOC-007 | Status | Formal Draft V1 |
| GL-SCHEMA-002-DOC-008 | Depends On | GL-SCHEMA-001_Markdown_Entry_Schema.md, GL-CONT-000 through GL-CONT-010, Unified Glossary Content Consolidation Pack, GL-CONS-002, GL-CONS-003 |
| GL-SCHEMA-002-DOC-009 | Scope | CSV table model, normalized CSV files, columns, keys, required fields, controlled values, relation tables, validation tables, import/export rules |
| GL-SCHEMA-002-DOC-010 | Excluded From This Pack | JSON Schema definitions, actual CSV population, full glossary extraction, database DDL, PostgreSQL derivation, final validation execution |
| GL-SCHEMA-002-DOC-011 | Enables | GL-SCHEMA-003_JSON_Schema_Definitions.md, GL-SCHEMA-004_Representation_Mapping.md, CSV population packs, validation packs, database-readiness packs |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical CSV schema for representing the Assembler System glossary.

It answers the question:

```text
How should glossary terms, aliases, anti-collapse rules, related-term links,
source traces, usage examples, controlled vocabularies, and validation metadata
be represented as CSV tables without losing the architectural meaning defined
in Markdown?
````

CSV is not the primary meaning authority.

CSV is a normalized representation derived from governed Markdown entries.

The CSV schema exists to support:

1. structured review,
2. spreadsheet inspection,
3. lightweight imports,
4. validation checks,
5. coverage reports,
6. source trace audits,
7. later JSON generation,
8. database derivation readiness.

### 2.2 CSV Representation Role

CSV representation serves seven roles.

|              Record ID | Role                        | Description                                                                |
| ---------------------: | --------------------------- | -------------------------------------------------------------------------- |
| GL-SCHEMA-002-ROLE-001 | Normalized Term Inventory   | Represents glossary terms as rows with stable IDs                          |
| GL-SCHEMA-002-ROLE-002 | Reviewable Spreadsheet Form | Allows reviewers to inspect terms, families, categories, and maturity      |
| GL-SCHEMA-002-ROLE-003 | Relation Extraction         | Separates multi-valued relations into dedicated tables                     |
| GL-SCHEMA-002-ROLE-004 | Validation Input            | Provides tabular input for coverage, consistency, and anti-collapse checks |
| GL-SCHEMA-002-ROLE-005 | Source Trace Matrix         | Preserves term-to-source and rule-to-source traceability                   |
| GL-SCHEMA-002-ROLE-006 | JSON Derivation Source      | Provides normalized rows that can be assembled into JSON objects           |
| GL-SCHEMA-002-ROLE-007 | Database Readiness          | Prepares stable row grains and join keys for future relational derivation  |

### 2.3 CSV Non-Purpose

CSV representation does not replace the Markdown glossary.

It does not define new meanings.

It does not create new term categories.

It does not collapse multi-section Markdown entries into a single overloaded row.

It does not decide final database schema.

It does not finalize JSON object shape.

It defines the normalized tabular representation that later population packs must follow.

---

## 3. CSV Schema Principles

### 3.1 Meaning Preservation Principle

```text
CSV rows must preserve glossary meaning already defined by Markdown entries.
CSV must not invent, compress, or reinterpret canonical meaning.
```

### 3.2 One Row, One Grain Principle

```text
Each CSV file must define one explicit row grain.
A row must not mix term identity, aliases, source traces, usage examples,
anti-collapse rules, and related-term links in the same physical row.
```

### 3.3 Stable Join-Key Principle

```text
All joins must use canonical IDs, not textual similarity.
```

Allowed join keys include:

1. `term_id`,
2. `alias_id`,
3. `source_trace_id`,
4. `anti_collapse_rule_id`,
5. `relationship_id`,
6. `usage_example_id`,
7. `controlled_value_id`,
8. `validation_rule_id`.

### 3.4 CSV Normalization Principle

```text
Multi-valued fields should be normalized into relation tables unless the field
is explicitly marked as display-only.
```

For example:

```text
Family = SYS / CPP
```

may appear as a display value in the main term table, but authoritative family membership should also be represented in a term-family join table.

### 3.5 No Hidden Lists Principle

A CSV cell should not hide a semantically important list when that list needs validation.

The following must be represented in separate tables:

1. related terms,
2. source traces,
3. anti-collapse targets,
4. usage examples,
5. family memberships,
6. category memberships,
7. alias mappings,
8. validation findings.

### 3.6 Round-Trip Readiness Principle

CSV must support controlled round-trip interpretation:

```text
Markdown Entry
→ CSV normalized rows
→ JSON object assembly
→ validation reports
```

CSV does not need to reproduce Markdown formatting exactly, but it must preserve enough data to regenerate equivalent structured content.

---

## 4. CSV File Set

### 4.1 Required CSV Files

The canonical CSV schema consists of the following required files.

|              Record ID | CSV File                           | Row Grain                                                          | Purpose                                        |
| ---------------------: | ---------------------------------- | ------------------------------------------------------------------ | ---------------------------------------------- |
| GL-SCHEMA-002-FILE-001 | `glossary_terms.csv`               | One row per canonical, partial, seed, alias, or future term record | Main term inventory                            |
| GL-SCHEMA-002-FILE-002 | `glossary_term_families.csv`       | One row per term-family membership                                 | Normalizes family codes                        |
| GL-SCHEMA-002-FILE-003 | `glossary_term_categories.csv`     | One row per term-category membership                               | Normalizes architectural categories            |
| GL-SCHEMA-002-FILE-004 | `glossary_aliases.csv`             | One row per alias mapping                                          | Maps aliases to canonical targets              |
| GL-SCHEMA-002-FILE-005 | `glossary_related_terms.csv`       | One row per related-term link                                      | Represents semantic relationships              |
| GL-SCHEMA-002-FILE-006 | `glossary_source_traces.csv`       | One row per source trace                                           | Preserves evidence and traceability            |
| GL-SCHEMA-002-FILE-007 | `glossary_anti_collapse_rules.csv` | One row per anti-collapse rule                                     | Preserves guard rules                          |
| GL-SCHEMA-002-FILE-008 | `glossary_usage_examples.csv`      | One row per usage example                                          | Stores valid and invalid usage                 |
| GL-SCHEMA-002-FILE-009 | `glossary_entry_sections.csv`      | One row per long-form Markdown section                             | Preserves definitions and prose sections       |
| GL-SCHEMA-002-FILE-010 | `glossary_controlled_values.csv`   | One row per allowed controlled value                               | Defines enumerations                           |
| GL-SCHEMA-002-FILE-011 | `glossary_validation_rules.csv`    | One row per validation rule                                        | Defines checks applicable to CSV/Markdown/JSON |
| GL-SCHEMA-002-FILE-012 | `glossary_validation_findings.csv` | One row per validation finding                                     | Stores future validation results               |

### 4.2 Optional CSV Files

|              Record ID | CSV File                            | Row Grain                               | Purpose                                           |
| ---------------------: | ----------------------------------- | --------------------------------------- | ------------------------------------------------- |
| GL-SCHEMA-002-FILE-013 | `glossary_pack_index.csv`           | One row per glossary pack               | Tracks source pack metadata                       |
| GL-SCHEMA-002-FILE-014 | `glossary_term_pack_membership.csv` | One row per term-to-pack relationship   | Shows where a term was introduced or consolidated |
| GL-SCHEMA-002-FILE-015 | `glossary_derivation_readiness.csv` | One row per term or rule readiness item | Tracks future derivation status                   |
| GL-SCHEMA-002-FILE-016 | `glossary_change_log.csv`           | One row per schema or content change    | Tracks evolution                                  |

---

## 5. CSV Naming Rules

### 5.1 File Naming Rule

All CSV files must use lowercase snake_case names.

Correct:

```text
glossary_terms.csv
glossary_source_traces.csv
glossary_anti_collapse_rules.csv
```

Incorrect:

```text
GlossaryTerms.csv
glossary-source-traces.csv
GL_Terms.csv
```

### 5.2 Column Naming Rule

All CSV columns must use lowercase snake_case.

Correct:

```text
term_id
canonical_term
entry_maturity
evidence_status
```

Incorrect:

```text
Term ID
CanonicalTerm
entry-maturity
Evidence Status
```

### 5.3 ID Column Rule

Every CSV table must have a stable primary ID column unless the table is explicitly a join table whose composite key is declared.

Examples:

| CSV File                           | Primary Key             |
| ---------------------------------- | ----------------------- |
| `glossary_terms.csv`               | `term_id`               |
| `glossary_aliases.csv`             | `alias_id`              |
| `glossary_source_traces.csv`       | `source_trace_id`       |
| `glossary_anti_collapse_rules.csv` | `anti_collapse_rule_id` |
| `glossary_usage_examples.csv`      | `usage_example_id`      |
| `glossary_validation_rules.csv`    | `validation_rule_id`    |

---

## 6. `glossary_terms.csv`

### 6.1 Row Grain

```text
One row per glossary term record.
```

This includes:

1. canonical full terms,
2. canonical partial terms,
3. seed terms,
4. alias records when represented as term records,
5. future derivation terms.

### 6.2 Columns

| Column                     | Required | Type        | Description                                                           |
| -------------------------- | -------- | ----------- | --------------------------------------------------------------------- |
| `term_id`                  | Yes      | string      | Stable glossary term ID                                               |
| `canonical_term`           | Yes      | string      | Canonical term label                                                  |
| `display_term`             | No       | string      | Display label if different from canonical term                        |
| `entry_profile`            | Yes      | enum        | full_canonical / partial_canonical / seed / alias / future_derivation |
| `entry_maturity`           | Yes      | enum        | canonical_full / canonical_partial / seed / alias / future_derivation |
| `primary_family_code`      | Yes      | enum        | Main family code                                                      |
| `primary_category`         | Yes      | string      | Main architectural category                                           |
| `ownership_scope`          | Yes      | enum/string | Ownership or authority scope                                          |
| `evidence_status`          | Yes      | enum        | Evidence classification                                               |
| `definition_short`         | Yes      | string      | Short definition suitable for inventory display                       |
| `status`                   | Yes      | enum        | active / pending / deprecated / superseded                            |
| `introduced_in_pack_id`    | Yes      | string      | GL-CONT or GL-SCHEMA pack where term was introduced                   |
| `consolidated_by_pack_id`  | No       | string      | Pack that consolidated this term                                      |
| `canonical_target_term_id` | No       | string      | Required when this row is an alias                                    |
| `notes`                    | No       | string      | Editorial or migration notes                                          |

### 6.3 Primary Key

```text
term_id
```

### 6.4 Required Constraints

|                    Rule ID | Rule                                                                   |
| -------------------------: | ---------------------------------------------------------------------- |
| GL-SCHEMA-002-TERM-VAL-001 | `term_id` must be unique                                               |
| GL-SCHEMA-002-TERM-VAL-002 | `canonical_term` must not be empty                                     |
| GL-SCHEMA-002-TERM-VAL-003 | `entry_maturity` must use controlled values                            |
| GL-SCHEMA-002-TERM-VAL-004 | `entry_profile` must use controlled values                             |
| GL-SCHEMA-002-TERM-VAL-005 | `primary_family_code` must resolve to `glossary_controlled_values.csv` |
| GL-SCHEMA-002-TERM-VAL-006 | `canonical_target_term_id` is required when `entry_profile = alias`    |
| GL-SCHEMA-002-TERM-VAL-007 | `canonical_target_term_id` must be empty unless the row is an alias    |
| GL-SCHEMA-002-TERM-VAL-008 | `introduced_in_pack_id` must not be empty                              |
| GL-SCHEMA-002-TERM-VAL-009 | `status` must be active, pending, deprecated, or superseded            |

### 6.5 Example Rows

```csv
term_id,canonical_term,display_term,entry_profile,entry_maturity,primary_family_code,primary_category,ownership_scope,evidence_status,definition_short,status,introduced_in_pack_id,consolidated_by_pack_id,canonical_target_term_id,notes
GL-OBJ-001,Log Level Envelope,Log Level Envelope,full_canonical,canonical_full,OBJ,carrier_object,assembler_owned / transferable,direct / user_decision / derived,Authoritative assembler-side carrier object produced by Envelope Assembler.,active,GL-CONT-004,UGCC,,Central envelope carrier term.
GL-ALIAS-001,Log Envelope,Log Envelope,alias,alias,ALIAS,alias,governed,legacy_alias,Legacy alias for Log Level Envelope.,active,GL-CONT-004,UGCC,GL-OBJ-001,Formal documents should prefer Log Level Envelope.
```

---

## 7. `glossary_term_families.csv`

### 7.1 Row Grain

```text
One row per term-family membership.
```

A term may belong to multiple families.

### 7.2 Columns

| Column           | Required | Type   | Description                          |
| ---------------- | -------- | ------ | ------------------------------------ |
| `term_family_id` | Yes      | string | Stable row ID                        |
| `term_id`        | Yes      | string | Term being classified                |
| `family_code`    | Yes      | enum   | Family code                          |
| `family_role`    | Yes      | enum   | primary / secondary                  |
| `source_pack_id` | Yes      | string | Pack that established the membership |
| `status`         | Yes      | enum   | active / pending / deprecated        |

### 7.3 Primary Key

```text
term_family_id
```

### 7.4 Join Rules

| Column        | References                                                              |
| ------------- | ----------------------------------------------------------------------- |
| `term_id`     | `glossary_terms.term_id`                                                |
| `family_code` | `glossary_controlled_values.value_code` where `value_set = family_code` |

### 7.5 Example Rows

```csv
term_family_id,term_id,family_code,family_role,source_pack_id,status
GL-TF-000001,GL-OBJ-001,OBJ,primary,GL-CONT-004,active
GL-TF-000002,GL-OBJ-009,RUN,secondary,GL-CONT-004,active
GL-TF-000003,GL-CON-002,CON,primary,GL-CONT-006,active
GL-TF-000004,GL-CON-002,CPP,secondary,GL-CONT-006,active
```

---

## 8. `glossary_term_categories.csv`

### 8.1 Row Grain

```text
One row per term-category membership.
```

A term may have multiple architectural categories.

### 8.2 Columns

| Column             | Required | Type   | Description                        |
| ------------------ | -------- | ------ | ---------------------------------- |
| `term_category_id` | Yes      | string | Stable row ID                      |
| `term_id`          | Yes      | string | Term being categorized             |
| `category_code`    | Yes      | string | Architectural category             |
| `category_role`    | Yes      | enum   | primary / secondary                |
| `source_pack_id`   | Yes      | string | Pack that established the category |
| `status`           | Yes      | enum   | active / pending / deprecated      |

### 8.3 Primary Key

```text
term_category_id
```

### 8.4 Example Rows

```csv
term_category_id,term_id,category_code,category_role,source_pack_id,status
GL-TC-000001,GL-OBJ-001,carrier_object,primary,GL-CONT-004,active
GL-TC-000002,GL-OBJ-001,governed_object,secondary,GL-CONT-004,active
GL-TC-000003,GL-ENT-002,actor,primary,GL-CONT-003,active
GL-TC-000004,GL-ENT-002,delegated_entity,secondary,GL-CONT-003,active
```

---

## 9. `glossary_aliases.csv`

### 9.1 Row Grain

```text
One row per alias-to-canonical-term mapping.
```

### 9.2 Columns

| Column                     | Required | Type   | Description                                                       |
| -------------------------- | -------- | ------ | ----------------------------------------------------------------- |
| `alias_id`                 | Yes      | string | Stable alias row ID                                               |
| `alias_term`               | Yes      | string | Alias wording                                                     |
| `canonical_target_term_id` | Yes      | string | Canonical term ID                                                 |
| `canonical_target_term`    | Yes      | string | Canonical term label                                              |
| `alias_type`               | Yes      | enum   | legacy / shorthand / source_alias / spelling_variant / deprecated |
| `evidence_status`          | Yes      | enum   | Usually legacy_alias / direct / derived                           |
| `valid_usage_policy`       | Yes      | enum   | allowed / discouraged / prohibited / source_only                  |
| `source_pack_id`           | Yes      | string | Pack establishing the alias                                       |
| `status`                   | Yes      | enum   | active / deprecated / superseded                                  |
| `notes`                    | No       | string | Alias handling notes                                              |

### 9.3 Primary Key

```text
alias_id
```

### 9.4 Constraints

|                     Rule ID | Rule                                                                              |
| --------------------------: | --------------------------------------------------------------------------------- |
| GL-SCHEMA-002-ALIAS-VAL-001 | `alias_id` must be unique                                                         |
| GL-SCHEMA-002-ALIAS-VAL-002 | `canonical_target_term_id` must resolve to a non-alias canonical term             |
| GL-SCHEMA-002-ALIAS-VAL-003 | Alias must not point to another alias unless explicitly allowed by migration rule |
| GL-SCHEMA-002-ALIAS-VAL-004 | `valid_usage_policy` must be controlled                                           |
| GL-SCHEMA-002-ALIAS-VAL-005 | Deprecated aliases must include notes                                             |

### 9.5 Example Rows

```csv
alias_id,alias_term,canonical_target_term_id,canonical_target_term,alias_type,evidence_status,valid_usage_policy,source_pack_id,status,notes
GL-ALIAS-MAP-000001,Log Envelope,GL-OBJ-001,Log Level Envelope,legacy,legacy_alias,source_only,GL-CONT-004,active,Preserved as legacy/source alias but formal docs should prefer canonical term.
```

---

## 10. `glossary_related_terms.csv`

### 10.1 Row Grain

```text
One row per relationship between two glossary terms.
```

### 10.2 Columns

| Column              | Required | Type   | Description                                                                                          |
| ------------------- | -------- | ------ | ---------------------------------------------------------------------------------------------------- |
| `relationship_id`   | Yes      | string | Stable relation ID                                                                                   |
| `source_term_id`    | Yes      | string | Term containing the related-term reference                                                           |
| `target_term_id`    | Yes      | string | Related term                                                                                         |
| `relationship_type` | Yes      | enum   | related / produces / receives / governs / excludes / aliases / depends_on / enables / contrasts_with |
| `directionality`    | Yes      | enum   | directed / undirected                                                                                |
| `source_pack_id`    | Yes      | string | Pack establishing the relation                                                                       |
| `status`            | Yes      | enum   | active / pending / deprecated                                                                        |
| `notes`             | No       | string | Optional relation explanation                                                                        |

### 10.3 Primary Key

```text
relationship_id
```

### 10.4 Relationship Type Values

| Value            | Meaning                                          |
| ---------------- | ------------------------------------------------ |
| `related`        | General semantic relationship                    |
| `produces`       | Source term produces target term                 |
| `receives`       | Source term receives target term                 |
| `governs`        | Source term governs target term                  |
| `excludes`       | Source term excludes target authority or meaning |
| `aliases`        | Source term aliases target term                  |
| `depends_on`     | Source term depends on target term               |
| `enables`        | Source term enables target term                  |
| `contrasts_with` | Terms are intentionally distinct                 |

### 10.5 Example Rows

```csv
relationship_id,source_term_id,target_term_id,relationship_type,directionality,source_pack_id,status,notes
GL-REL-000001,GL-ENT-001,GL-OBJ-001,produces,directed,GL-CONT-003,active,Envelope Assembler produces Log Level Envelope.
GL-REL-000002,GL-BND-006,GL-OBJ-001,receives,directed,GL-CONT-002,active,Assembler Ingress Port receives Log Level Envelope.
GL-REL-000003,GL-DISP-001,GL-REG-001,depends_on,directed,GL-CONT-009,active,Dispatcher uses Registry / Delivery Port as outbound contract surface.
```

---

## 11. `glossary_source_traces.csv`

### 11.1 Row Grain

```text
One row per source trace attached to a term, rule, relationship, pack, or validation item.
```

### 11.2 Columns

| Column            | Required | Type   | Description                                                                                                                    |
| ----------------- | -------- | ------ | ------------------------------------------------------------------------------------------------------------------------------ |
| `source_trace_id` | Yes      | string | Stable trace row ID                                                                                                            |
| `target_id`       | Yes      | string | Term, rule, pack, relation, or validation item being traced                                                                    |
| `target_type`     | Yes      | enum   | term / rule / pack / relation / goal / doctrine / derivation_item / validation_rule                                            |
| `source_id`       | Yes      | string | Source document, pack, rule, goal, or decision ID                                                                              |
| `source_type`     | Yes      | enum   | foundational_document / glossary_pack / consolidation_pack / system_goal / user_decision / anti_collapse_rule / derived_rule   |
| `trace_relation`  | Yes      | enum   | direct / derived / supports / constrains / consolidates / aliases / enables / excludes / validates / supersedes                |
| `evidence_status` | Yes      | enum   | direct / derived / user_decision / legacy_alias / inferred / needs_validation / consolidation_authority / validation_authority |
| `source_summary`  | Yes      | string | Short explanation of what the source contributes                                                                               |
| `validation_use`  | No       | string | How validators should use this trace                                                                                           |
| `status`          | Yes      | enum   | active / pending / superseded / deprecated                                                                                     |

### 11.3 Primary Key

```text
source_trace_id
```

### 11.4 Constraints

|                   Rule ID | Rule                                                                |
| ------------------------: | ------------------------------------------------------------------- |
| GL-SCHEMA-002-SRC-VAL-001 | `source_trace_id` must be unique                                    |
| GL-SCHEMA-002-SRC-VAL-002 | `target_id` must not be empty                                       |
| GL-SCHEMA-002-SRC-VAL-003 | `target_type` must be controlled                                    |
| GL-SCHEMA-002-SRC-VAL-004 | `source_type` must be controlled                                    |
| GL-SCHEMA-002-SRC-VAL-005 | `trace_relation` must be controlled                                 |
| GL-SCHEMA-002-SRC-VAL-006 | `evidence_status` must be controlled                                |
| GL-SCHEMA-002-SRC-VAL-007 | Critical canonical terms must have at least one active source trace |

### 11.5 Example Rows

```csv
source_trace_id,target_id,target_type,source_id,source_type,trace_relation,evidence_status,source_summary,validation_use,status
GL-SRC-000001,GL-OBJ-001,term,GL-CONT-004,glossary_pack,direct,direct,Defines Log Level Envelope as authoritative carrier object.,Validate envelope carrier semantics.,active
GL-SRC-000002,GL-OBJ-001,term,GL-CONT-003,glossary_pack,supports,derived,Defines Envelope Assembler as producer of Log Level Envelope.,Validate producer/carrier separation.,active
GL-SRC-000003,GL-DISP-001,term,GL-CONT-009,glossary_pack,direct,direct,Defines Dispatcher as final outbound actor.,Validate dispatcher finality.,active
```

---

## 12. `glossary_anti_collapse_rules.csv`

### 12.1 Row Grain

```text
One row per anti-collapse rule.
```

### 12.2 Columns

| Column                         | Required | Type   | Description                                                                                                              |
| ------------------------------ | -------- | ------ | ------------------------------------------------------------------------------------------------------------------------ |
| `anti_collapse_rule_id`        | Yes      | string | Stable anti-collapse rule ID                                                                                             |
| `protected_term_id`            | Yes      | string | Term being protected                                                                                                     |
| `protected_term`               | Yes      | string | Display name of protected term                                                                                           |
| `must_not_collapse_into_id`    | No       | string | Target term ID if target is a known term                                                                                 |
| `must_not_collapse_into_label` | Yes      | string | Target term/category/system/artifact label                                                                               |
| `collapse_type`                | Yes      | enum   | identity / boundary / authority / actor_object / runtime / contract / responsibility / policy / handoff / implementation |
| `protected_distinction`        | Yes      | string | The distinction preserved by the rule                                                                                    |
| `severity`                     | Yes      | enum   | critical / high / medium / low                                                                                           |
| `source_pack_id`               | Yes      | string | Main pack establishing the rule                                                                                          |
| `validation_use`               | Yes      | string | How the rule should be checked                                                                                           |
| `derivation_impact`            | No       | string | What breaks if violated                                                                                                  |
| `status`                       | Yes      | enum   | active / pending / deprecated                                                                                            |

### 12.3 Primary Key

```text
anti_collapse_rule_id
```

### 12.4 Example Rows

```csv
anti_collapse_rule_id,protected_term_id,protected_term,must_not_collapse_into_id,must_not_collapse_into_label,collapse_type,protected_distinction,severity,source_pack_id,validation_use,derivation_impact,status
GL-AC-000001,GL-ENT-001,Envelope Assembler,GL-OBJ-001,Log Level Envelope,actor_object,Producer must not collapse into produced carrier.,high,GL-CONT-003,Check actor/object separation.,Would corrupt envelope lifecycle and responsibility ownership.,active
GL-AC-000002,GL-DISP-001,Dispatcher,GL-REG-001,Registry / Delivery Port,boundary,Final outbound actor must not collapse into outbound contract surface.,critical,GL-CONT-009,Check handoff language.,Would remove dispatcher finality.,active
GL-AC-000003,GL-RUN-001,Queue Container,,Message Broker,runtime,Queue is container not broker infrastructure.,critical,GL-CONT-005,Check runtime vocabulary.,Would expand system into messaging platform.,active
```

---

## 13. `glossary_usage_examples.csv`

### 13.1 Row Grain

```text
One row per valid or invalid usage example.
```

### 13.2 Columns

| Column                         | Required | Type   | Description                                  |
| ------------------------------ | -------- | ------ | -------------------------------------------- |
| `usage_example_id`             | Yes      | string | Stable usage example ID                      |
| `term_id`                      | Yes      | string | Term the usage example belongs to            |
| `usage_type`                   | Yes      | enum   | valid / invalid                              |
| `usage_text`                   | Yes      | string | Sentence-like usage example                  |
| `reason`                       | No       | string | Explanation of why usage is valid or invalid |
| `linked_anti_collapse_rule_id` | No       | string | Related anti-collapse rule                   |
| `source_pack_id`               | Yes      | string | Pack establishing the usage                  |
| `status`                       | Yes      | enum   | active / pending / deprecated                |

### 13.3 Primary Key

```text
usage_example_id
```

### 13.4 Example Rows

```csv
usage_example_id,term_id,usage_type,usage_text,reason,linked_anti_collapse_rule_id,source_pack_id,status
GL-USE-000001,GL-OBJ-001,valid,"Envelope Assembler produces the Log Level Envelope.",Correct producer/carrier distinction.,GL-AC-000001,GL-CONT-004,active
GL-USE-000002,GL-OBJ-001,invalid,"Log Level Envelope dispatches itself to the registry.",Carrier object is not an actor.,GL-AC-000001,GL-CONT-004,active
GL-USE-000003,GL-DISP-001,invalid,"Dispatcher owns downstream registry internals.",Violates post-handoff non-ownership.,GL-AC-000002,GL-CONT-009,active
```

---

## 14. `glossary_entry_sections.csv`

### 14.1 Row Grain

```text
One row per long-form section attached to a glossary term.
```

This table stores larger Markdown-derived prose blocks that should not be compressed into `glossary_terms.csv`.

### 14.2 Columns

| Column             | Required | Type    | Description                                                                                                                                                                        |
| ------------------ | -------- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `entry_section_id` | Yes      | string  | Stable section row ID                                                                                                                                                              |
| `term_id`          | Yes      | string  | Parent term                                                                                                                                                                        |
| `section_type`     | Yes      | enum    | definition / architectural_role / working_definition / known_constraints / open_clarifications / future_derivation_role / derivation_preconditions / invalid_premature_use / notes |
| `section_order`    | Yes      | integer | Display order                                                                                                                                                                      |
| `section_title`    | Yes      | string  | Human-readable section title                                                                                                                                                       |
| `section_text`     | Yes      | string  | Markdown-compatible prose                                                                                                                                                          |
| `source_pack_id`   | Yes      | string  | Pack establishing the section                                                                                                                                                      |
| `status`           | Yes      | enum    | active / pending / deprecated                                                                                                                                                      |

### 14.3 Primary Key

```text
entry_section_id
```

### 14.4 Example Rows

```csv
entry_section_id,term_id,section_type,section_order,section_title,section_text,source_pack_id,status
GL-SEC-000001,GL-OBJ-001,definition,1,Definition,"The Log Level Envelope is the authoritative assembler-side carrier object produced by the Envelope Assembler after governed content has passed through the required preparation path.",GL-CONT-004,active
GL-SEC-000002,GL-OBJ-001,architectural_role,2,Architectural Role,"The Log Level Envelope carries assembler-prepared content and associated governance material through runtime coordination until it becomes eligible for dispatcher-mediated handoff.",GL-CONT-004,active
```

---

## 15. `glossary_controlled_values.csv`

### 15.1 Row Grain

```text
One row per controlled value.
```

### 15.2 Columns

| Column                | Required | Type   | Description                   |
| --------------------- | -------- | ------ | ----------------------------- |
| `controlled_value_id` | Yes      | string | Stable controlled value ID    |
| `value_set`           | Yes      | string | Controlled vocabulary group   |
| `value_code`          | Yes      | string | Machine-readable value        |
| `value_label`         | Yes      | string | Human-readable label          |
| `description`         | Yes      | string | Meaning of the value          |
| `status`              | Yes      | enum   | active / pending / deprecated |
| `source_pack_id`      | Yes      | string | Pack defining the value       |

### 15.3 Primary Key

```text
controlled_value_id
```

### 15.4 Required Value Sets

| Value Set           | Purpose                                                                                                                        |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `family_code`       | SYS / DOC / BND / EXT / ENT / OBJ / RUN / CON / POL / TRC / CPP / EXC / ALIAS / DER / GUARD / DOM                              |
| `entry_maturity`    | canonical_full / canonical_partial / seed / alias / future_derivation                                                          |
| `entry_profile`     | full_canonical / partial_canonical / seed / alias / future_derivation                                                          |
| `evidence_status`   | direct / derived / user_decision / legacy_alias / inferred / needs_validation / consolidation_authority / validation_authority |
| `ownership_scope`   | assembler_owned / external / downstream_not_owned / governed / future / pending / not_owned                                    |
| `status`            | active / pending / deprecated / superseded                                                                                     |
| `severity`          | critical / high / medium / low                                                                                                 |
| `trace_relation`    | direct / derived / supports / constrains / consolidates / aliases / enables / excludes / validates / supersedes                |
| `source_type`       | foundational_document / glossary_pack / consolidation_pack / system_goal / user_decision / anti_collapse_rule / derived_rule   |
| `relationship_type` | related / produces / receives / governs / excludes / aliases / depends_on / enables / contrasts_with                           |

### 15.5 Example Rows

```csv
controlled_value_id,value_set,value_code,value_label,description,status,source_pack_id
GL-CV-000001,family_code,SYS,System Identity,System-level identity and bounded subsystem terms.,active,GL-CONT-000
GL-CV-000002,family_code,OBJ,Governed Object,Carrier objects and governed objects.,active,GL-CONT-000
GL-CV-000003,entry_maturity,canonical_full,Canonical Full,Fully accepted canonical entry with complete definition and constraints.,active,GL-SCHEMA-001
GL-CV-000004,evidence_status,direct,Direct,Target appears directly in source.,active,GL-CONS-003
```

---

## 16. `glossary_validation_rules.csv`

### 16.1 Row Grain

```text
One row per validation rule.
```

### 16.2 Columns

| Column               | Required | Type   | Description                                                                                      |
| -------------------- | -------- | ------ | ------------------------------------------------------------------------------------------------ |
| `validation_rule_id` | Yes      | string | Stable validation rule ID                                                                        |
| `rule_name`          | Yes      | string | Short rule name                                                                                  |
| `applies_to_file`    | Yes      | string | CSV file or representation target                                                                |
| `applies_to_column`  | No       | string | Specific column if applicable                                                                    |
| `rule_type`          | Yes      | enum   | required_field / uniqueness / foreign_key / controlled_value / cross_row / cross_file / semantic |
| `rule_description`   | Yes      | string | Rule definition                                                                                  |
| `severity`           | Yes      | enum   | critical / high / medium / low                                                                   |
| `source_pack_id`     | Yes      | string | Pack establishing the rule                                                                       |
| `status`             | Yes      | enum   | active / pending / deprecated                                                                    |

### 16.3 Primary Key

```text
validation_rule_id
```

### 16.4 Example Rows

```csv
validation_rule_id,rule_name,applies_to_file,applies_to_column,rule_type,rule_description,severity,source_pack_id,status
GL-VAL-000001,Term ID uniqueness,glossary_terms.csv,term_id,uniqueness,Each term_id must be unique.,critical,GL-SCHEMA-002,active
GL-VAL-000002,Alias target required,glossary_aliases.csv,canonical_target_term_id,required_field,Every alias must point to a canonical target term.,critical,GL-SCHEMA-002,active
GL-VAL-000003,Source trace required,glossary_source_traces.csv,target_id,cross_file,Critical canonical terms must have at least one active source trace.,critical,GL-SCHEMA-002,active
```

---

## 17. `glossary_validation_findings.csv`

### 17.1 Row Grain

```text
One row per validation finding.
```

This table is populated later by validation packs or tooling.

### 17.2 Columns

| Column                  | Required | Type   | Description                               |
| ----------------------- | -------- | ------ | ----------------------------------------- |
| `validation_finding_id` | Yes      | string | Stable finding ID                         |
| `validation_rule_id`    | Yes      | string | Rule that produced the finding            |
| `target_file`           | Yes      | string | CSV file where issue was found            |
| `target_row_id`         | No       | string | Primary key of affected row               |
| `target_column`         | No       | string | Affected column                           |
| `finding_severity`      | Yes      | enum   | critical / high / medium / low            |
| `finding_status`        | Yes      | enum   | open / resolved / waived / false_positive |
| `finding_message`       | Yes      | string | Human-readable finding                    |
| `recommended_action`    | No       | string | Suggested correction                      |
| `detected_at`           | No       | string | ISO timestamp                             |
| `resolved_at`           | No       | string | ISO timestamp                             |

### 17.3 Primary Key

```text
validation_finding_id
```

### 17.4 Example Rows

```csv
validation_finding_id,validation_rule_id,target_file,target_row_id,target_column,finding_severity,finding_status,finding_message,recommended_action,detected_at,resolved_at
GL-FIND-000001,GL-VAL-000002,glossary_aliases.csv,GL-ALIAS-MAP-000009,canonical_target_term_id,critical,open,Alias row has no canonical target.,Add canonical_target_term_id or mark alias row invalid.,,
```

---

## 18. Optional Pack Index Tables

## 18.1 `glossary_pack_index.csv`

### Row Grain

```text
One row per glossary-related pack.
```

### Columns

| Column           | Required | Type   | Description                                                |
| ---------------- | -------- | ------ | ---------------------------------------------------------- |
| `pack_id`        | Yes      | string | Pack ID                                                    |
| `pack_name`      | Yes      | string | Pack name                                                  |
| `pack_type`      | Yes      | enum   | content / schema / consolidation / validation / population |
| `formal_version` | Yes      | string | Formal version                                             |
| `status`         | Yes      | enum   | active / draft / superseded / deprecated                   |
| `depends_on`     | No       | string | Display-only dependency summary                            |
| `enables`        | No       | string | Display-only enabled artifacts                             |
| `notes`          | No       | string | Optional notes                                             |

### Example Rows

```csv
pack_id,pack_name,pack_type,formal_version,status,depends_on,enables,notes
GL-CONT-000,Glossary Governance & Entry Model Pack,content,Formal Draft V1,active,Foundational documents,GL-CONT-001 through GL-CONT-010,Defines glossary constitution.
GL-SCHEMA-001,Markdown Entry Schema,schema,Formal Draft V1,active,GL-CONT-000 through GL-CONT-010,GL-SCHEMA-002,Defines canonical Markdown entry schema.
GL-SCHEMA-002,CSV Schema Definitions,schema,Formal Draft V1,active,GL-SCHEMA-001,GL-SCHEMA-003 and GL-SCHEMA-004,Defines normalized CSV schema.
```

---

## 19. Required Foreign-Key Model

### 19.1 Core References

| Source File                        | Source Column                  | Target File                        | Target Column            |
| ---------------------------------- | ------------------------------ | ---------------------------------- | ------------------------ |
| `glossary_term_families.csv`       | `term_id`                      | `glossary_terms.csv`               | `term_id`                |
| `glossary_term_categories.csv`     | `term_id`                      | `glossary_terms.csv`               | `term_id`                |
| `glossary_aliases.csv`             | `canonical_target_term_id`     | `glossary_terms.csv`               | `term_id`                |
| `glossary_related_terms.csv`       | `source_term_id`               | `glossary_terms.csv`               | `term_id`                |
| `glossary_related_terms.csv`       | `target_term_id`               | `glossary_terms.csv`               | `term_id`                |
| `glossary_source_traces.csv`       | `target_id`                    | polymorphic                        | depends on `target_type` |
| `glossary_anti_collapse_rules.csv` | `protected_term_id`            | `glossary_terms.csv`               | `term_id`                |
| `glossary_usage_examples.csv`      | `term_id`                      | `glossary_terms.csv`               | `term_id`                |
| `glossary_usage_examples.csv`      | `linked_anti_collapse_rule_id` | `glossary_anti_collapse_rules.csv` | `anti_collapse_rule_id`  |
| `glossary_entry_sections.csv`      | `term_id`                      | `glossary_terms.csv`               | `term_id`                |
| `glossary_validation_findings.csv` | `validation_rule_id`           | `glossary_validation_rules.csv`    | `validation_rule_id`     |

### 19.2 Controlled Value References

| Source File                        | Source Column         | Controlled Value Set   |
| ---------------------------------- | --------------------- | ---------------------- |
| `glossary_terms.csv`               | `entry_maturity`      | `entry_maturity`       |
| `glossary_terms.csv`               | `entry_profile`       | `entry_profile`        |
| `glossary_terms.csv`               | `primary_family_code` | `family_code`          |
| `glossary_terms.csv`               | `evidence_status`     | `evidence_status`      |
| `glossary_terms.csv`               | `status`              | `status`               |
| `glossary_aliases.csv`             | `alias_type`          | `alias_type`           |
| `glossary_aliases.csv`             | `valid_usage_policy`  | `valid_usage_policy`   |
| `glossary_related_terms.csv`       | `relationship_type`   | `relationship_type`    |
| `glossary_source_traces.csv`       | `source_type`         | `source_type`          |
| `glossary_source_traces.csv`       | `trace_relation`      | `trace_relation`       |
| `glossary_anti_collapse_rules.csv` | `severity`            | `severity`             |
| `glossary_validation_rules.csv`    | `rule_type`           | `validation_rule_type` |

---

## 20. CSV Encoding and Formatting Rules

### 20.1 Encoding

All CSV files must use:

```text
UTF-8
```

### 20.2 Header Row

Each CSV file must include a header row.

The header row must use exact column names defined in this pack.

### 20.3 Delimiter

The delimiter must be:

```text
comma ,
```

### 20.4 Quoting

Fields containing commas, quotes, or line breaks must be quoted according to standard CSV rules.

Example:

```csv
term_id,definition_short
GL-OBJ-001,"The Log Level Envelope carries content, metadata, timestamp semantics, and policy assignment."
```

### 20.5 Newlines Inside Cells

Long prose fields may contain line breaks only when the CSV writer supports proper quoting.

For portability, population packs should prefer single-line prose where possible.

### 20.6 Markdown Inside CSV

Markdown may appear in long text columns only when needed.

Allowed:

1. backtick-wrapped term names,
2. simple inline code,
3. short Markdown emphasis.

Avoid:

1. Markdown tables inside CSV cells,
2. complex nested lists,
3. headings inside CSV cells.

---

## 21. CSV Import/Export Rules

### 21.1 Markdown-to-CSV Extraction

Markdown entries should be extracted into CSV as follows.

| Markdown Element          | CSV Target                                                |
| ------------------------- | --------------------------------------------------------- |
| Term heading              | `glossary_terms.term_id`, `glossary_terms.canonical_term` |
| Field table               | `glossary_terms.csv`, family/category join tables         |
| Definition                | `glossary_entry_sections.csv`                             |
| Architectural Role        | `glossary_entry_sections.csv`                             |
| Must Not Be Confused With | `glossary_anti_collapse_rules.csv`                        |
| Valid Usage               | `glossary_usage_examples.csv`                             |
| Invalid Usage             | `glossary_usage_examples.csv`                             |
| Related Terms             | `glossary_related_terms.csv`                              |
| Source Trace              | `glossary_source_traces.csv`                              |

### 21.2 CSV-to-JSON Assembly

CSV rows should be assembled into JSON using `term_id` as the primary grouping key.

The JSON object for a term should collect:

1. main term row,
2. family memberships,
3. category memberships,
4. aliases,
5. related terms,
6. source traces,
7. anti-collapse rules,
8. usage examples,
9. long-form entry sections.

### 21.3 CSV-to-Markdown Regeneration

CSV can regenerate structured Markdown only if:

1. `glossary_entry_sections.csv` preserves prose sections,
2. `glossary_usage_examples.csv` preserves valid/invalid usage,
3. `glossary_anti_collapse_rules.csv` preserves confusion targets,
4. `glossary_related_terms.csv` preserves semantic links,
5. `glossary_source_traces.csv` preserves trace rows.

CSV regeneration should be considered structured reconstruction, not the canonical authoring source.

---

## 22. Validation Rules

### 22.1 File-Level Validation

|                Rule ID | Validation Rule                                                                     | Severity |
| ---------------------: | ----------------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-002-FVAL-001 | All required CSV files must exist before full CSV population is considered complete | Critical |
| GL-SCHEMA-002-FVAL-002 | Every CSV file must include a header row                                            | Critical |
| GL-SCHEMA-002-FVAL-003 | Column names must match schema exactly                                              | High     |
| GL-SCHEMA-002-FVAL-004 | CSV files must be UTF-8 encoded                                                     | High     |
| GL-SCHEMA-002-FVAL-005 | Required columns must not be missing                                                | Critical |

### 22.2 Term-Level Validation

|                Rule ID | Validation Rule                                                        | Severity |
| ---------------------: | ---------------------------------------------------------------------- | -------- |
| GL-SCHEMA-002-TVAL-001 | Every term must have a unique `term_id`                                | Critical |
| GL-SCHEMA-002-TVAL-002 | Every active canonical term must have at least one family membership   | High     |
| GL-SCHEMA-002-TVAL-003 | Every active canonical term must have at least one category membership | High     |
| GL-SCHEMA-002-TVAL-004 | Every `canonical_full` term must have a definition section             | Critical |
| GL-SCHEMA-002-TVAL-005 | Every `canonical_full` term must have at least one source trace        | Critical |
| GL-SCHEMA-002-TVAL-006 | Every high-risk term should have at least one anti-collapse rule       | High     |
| GL-SCHEMA-002-TVAL-007 | Every alias must resolve to a canonical target                         | Critical |
| GL-SCHEMA-002-TVAL-008 | Deprecated terms must include notes or supersession path               | Medium   |

### 22.3 Relationship-Level Validation

|                Rule ID | Validation Rule                                                                            | Severity |
| ---------------------: | ------------------------------------------------------------------------------------------ | -------- |
| GL-SCHEMA-002-RVAL-001 | Related term source must resolve to known term                                             | High     |
| GL-SCHEMA-002-RVAL-002 | Related term target must resolve to known term or seed                                     | High     |
| GL-SCHEMA-002-RVAL-003 | Directed relationships must have meaningful source and target direction                    | Medium   |
| GL-SCHEMA-002-RVAL-004 | `produces` relationships should not point from object to actor unless explicitly justified | High     |
| GL-SCHEMA-002-RVAL-005 | `aliases` relationships should correspond to alias table entries                           | Medium   |

### 22.4 Source Trace Validation

|                Rule ID | Validation Rule                                                                        | Severity |
| ---------------------: | -------------------------------------------------------------------------------------- | -------- |
| GL-SCHEMA-002-SVAL-001 | Critical canonical terms must have source traces                                       | Critical |
| GL-SCHEMA-002-SVAL-002 | Source trace relation must be controlled                                               | High     |
| GL-SCHEMA-002-SVAL-003 | Evidence status must be controlled                                                     | High     |
| GL-SCHEMA-002-SVAL-004 | Source traces marked `needs_validation` must remain visible in validation reports      | Medium   |
| GL-SCHEMA-002-SVAL-005 | Consolidation authority alone is insufficient for critical identity and boundary terms | High     |

### 22.5 Anti-Collapse Validation

|                 Rule ID | Validation Rule                                             | Severity |
| ----------------------: | ----------------------------------------------------------- | -------- |
| GL-SCHEMA-002-ACVAL-001 | Every anti-collapse rule must have a protected term         | Critical |
| GL-SCHEMA-002-ACVAL-002 | Every anti-collapse rule must state a collapse target label | Critical |
| GL-SCHEMA-002-ACVAL-003 | Critical anti-collapse rules must include validation use    | High     |
| GL-SCHEMA-002-ACVAL-004 | Protected term must resolve to known term                   | High     |
| GL-SCHEMA-002-ACVAL-005 | Collapse type must be controlled                            | High     |

---

## 23. CSV Population Readiness

### 23.1 Population Order

CSV population should happen in the following order:

```text
1. glossary_controlled_values.csv
2. glossary_pack_index.csv
3. glossary_terms.csv
4. glossary_term_families.csv
5. glossary_term_categories.csv
6. glossary_aliases.csv
7. glossary_entry_sections.csv
8. glossary_related_terms.csv
9. glossary_source_traces.csv
10. glossary_anti_collapse_rules.csv
11. glossary_usage_examples.csv
12. glossary_validation_rules.csv
13. glossary_validation_findings.csv
```

### 23.2 Why Controlled Values Come First

Controlled values must be populated before term rows because term rows depend on:

1. family code values,
2. entry maturity values,
3. evidence status values,
4. status values,
5. ownership scope values,
6. relationship type values,
7. source type values,
8. trace relation values.

### 23.3 Why Terms Come Before Relations

Relations cannot be validated until term IDs exist.

Therefore:

```text
terms before related_terms
terms before aliases
terms before source_traces
terms before anti_collapse_rules
terms before usage_examples
```

---

## 24. CSV Schema Exit Criteria

|              Record ID | Exit Criterion                                   | Status   |
| ---------------------: | ------------------------------------------------ | -------- |
| GL-SCHEMA-002-EXIT-001 | Required CSV file set is defined                 | Complete |
| GL-SCHEMA-002-EXIT-002 | Main term table schema is defined                | Complete |
| GL-SCHEMA-002-EXIT-003 | Family and category join tables are defined      | Complete |
| GL-SCHEMA-002-EXIT-004 | Alias table is defined                           | Complete |
| GL-SCHEMA-002-EXIT-005 | Related-term relation table is defined           | Complete |
| GL-SCHEMA-002-EXIT-006 | Source trace table is defined                    | Complete |
| GL-SCHEMA-002-EXIT-007 | Anti-collapse rule table is defined              | Complete |
| GL-SCHEMA-002-EXIT-008 | Usage example table is defined                   | Complete |
| GL-SCHEMA-002-EXIT-009 | Long-form section table is defined               | Complete |
| GL-SCHEMA-002-EXIT-010 | Controlled values table is defined               | Complete |
| GL-SCHEMA-002-EXIT-011 | Validation rules and findings tables are defined | Complete |
| GL-SCHEMA-002-EXIT-012 | Join-key model is defined                        | Complete |
| GL-SCHEMA-002-EXIT-013 | Import/export mapping rules are defined          | Complete |
| GL-SCHEMA-002-EXIT-014 | CSV population order is defined                  | Complete |

---

## 25. Summary

`GL-SCHEMA-002_CSV_Schema_Definitions.md` defines the normalized CSV representation of the Assembler System glossary.

It preserves the governing rule:

```text
CSV is a derived, normalized, tabular representation.
Markdown remains the human-readable authoring source.
CSV enables validation, review, JSON assembly, and future database readiness.
```

This pack prepares the next schema artifact:

```text
GL-SCHEMA-003_JSON_Schema_Definitions.md
```

```
```
