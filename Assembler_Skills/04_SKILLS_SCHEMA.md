FILE:
`08_assembler_skills/04_SKILLS_SCHEMA.md`

CONTENT:

````markdown id="n4x8q2"
# Skills Schema
## Schema Reference for Assembler Skills Architecture Pack V1

---

# 0. Document Identity

## 0.1 File Path

```text
08_assembler_skills/04_SKILLS_SCHEMA.md
````

## 0.2 Package

```text id="vph0n4"
08_assembler_skills/
```

## 0.3 Document Type

```text id="m7jqea"
skills_schema
```

## 0.4 Status

```text id="qx5k9m"
draft_schema_with_source_data_snapshot_correction
```

## 0.5 Governing Correction

This schema incorporates the binding correction defined in:

```text id="qo4f9m"
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
```

## 0.6 Corrected Architecture Law

```text id="i1dgpr"
Source data is vendored.
Kernel governs.
Core reasons.
CLI expresses.
Adapter executes.
Runtime hosts.
```

---

# 1. Schema Purpose

## 1.1

This document defines the schema rules for the `08_assembler_skills/` package.

## 1.2

It governs:

1. top-level package files,
2. vendored source-data control files,
3. shared canonical kernel files,
4. content editor skill files,
5. query expert skill files,
6. canonical CLI files,
7. runtime adapter specification files,
8. execution contract files,
9. package-level validation rules,
10. downstream implementation readiness.

## 1.3

It does not define new Assembler System semantics.

## 1.4

It defines how skills operate over the Assembler System canonical source data.

---

# 2. Corrected Layer Model

## 2.1 Layer Order

The canonical layer order is:

```text id="d0f735"
Source Data Snapshot
        ↓
Shared Canonical Kernel
        ↓
Skill Core
        ↓
Canonical CLI Layer
        ↓
Environment Adapter Layer
        ↓
Runtime Environment
```

## 2.2 Layer Responsibilities

| Layer                       | Responsibility                                                                       |
| --------------------------- | ------------------------------------------------------------------------------------ |
| `source_data_snapshot`      | Stores vendored canonical source files and source-data manifests inside package `08` |
| `shared_canonical_kernel`   | Defines shared governance rules used by both skills                                  |
| `skill_core`                | Performs environment-independent editor or query reasoning                           |
| `canonical_cli_layer`       | Expresses core decisions as stable command objects or shell commands                 |
| `environment_adapter_layer` | Executes canonical commands inside runtime-specific environments                     |
| `runtime_environment`       | Hosts repository, workspace, Drive, local filesystem, or agent execution             |
| `execution_contracts`       | Defines boundaries between core, CLI, adapters, and runtimes                         |
| `foundation`                | Defines package identity, overview, file map, schema, and binding decisions          |

## 2.3 Forbidden Layer Collapses

The package is invalid if it collapses:

1. Source Data Snapshot into external workspace paths,
2. Shared Canonical Kernel into runtime adapter behavior,
3. Skill Core into environment-specific implementation,
4. CLI Layer into one adapter among many,
5. Adapter Layer into semantic authority,
6. Runtime Environment into canonical source authority.

---

# 3. Source Data Snapshot Schema

## 3.1 Purpose

### 3.1.1

The Source Data Snapshot layer stores vendored canonical source data required by the skills.

### 3.1.2

It prevents hardcoded dependency on external workspace directories.

### 3.1.3

All skill source dependencies must resolve through:

```text id="ksquhx"
08_assembler_skills/00_source_data/
```

or approved aliases.

---

## 3.2 Required Source Data Aliases

| Alias                        | Resolves To                                                              |
| ---------------------------- | ------------------------------------------------------------------------ |
| `SKILLS_ROOT`                | `08_assembler_skills/`                                                   |
| `SOURCE_DATA_ROOT`           | `08_assembler_skills/00_source_data/`                                    |
| `TAXONOMY_SOURCE_ROOT`       | `08_assembler_skills/00_source_data/00.01_architectural_taxonomy/`       |
| `RESPONSIBILITY_SOURCE_ROOT` | `08_assembler_skills/00_source_data/00.02_canonical_responsibilities/`   |
| `DELEGATION_SOURCE_ROOT`     | `08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/` |

## 3.3 Alias Validation Rule

### 3.3.1

Any file referring to upstream canonical source data must use either:

1. an internal source-data path, or
2. an approved alias.

### 3.3.2

The following is valid:

```text id="fyso1p"
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

### 3.3.3

The following is invalid as a runtime dependency:

```text id="ms0wx2"
00.03_Canonical_Delegation_Enablement_Matrix_V2/06_Rollup_Indexes/06.03_QUERY_PATTERNS.md
```

---

## 3.4 Required Source Data Control Files

The Source Data Snapshot layer must include:

```text id="nn8jks"
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
08_assembler_skills/00_source_data/00.01_SOURCE_DATA_README.md
08_assembler_skills/00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv
08_assembler_skills/00_source_data/00.03_SOURCE_DATA_REFRESH_POLICY.md
```

## 3.5 Required Source-Specific Manifests

The Source Data Snapshot layer must include:

```text id="w1fcxe"
08_assembler_skills/00_source_data/00.01_architectural_taxonomy/taxonomy_source_manifest.json
08_assembler_skills/00_source_data/00.02_canonical_responsibilities/responsibilities_source_manifest.json
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/delegation_source_manifest.json
```

## 3.6 Source Data Directory Grain

| Path                                                 | Grain                                                   |
| ---------------------------------------------------- | ------------------------------------------------------- |
| `00_source_data/`                                    | one vendored source-data root                           |
| `00_source_data/00.01_architectural_taxonomy/`       | one vendored taxonomy source package                    |
| `00_source_data/00.02_canonical_responsibilities/`   | one vendored responsibility/obligation source package   |
| `00_source_data/00.03_delegation_enablement_matrix/` | one vendored delegation/enablement matrix release       |
| `00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv`      | one row per vendored source file or source directory    |
| `00_source_data/00.00_SOURCE_DATA_MANIFEST.json`     | one object describing source-data inventory and aliases |

---

# 4. Package File Classes

## 4.1 File Class Table

| File Class                   | Format   | Layer                     | Purpose                                                               |
| ---------------------------- | -------- | ------------------------- | --------------------------------------------------------------------- |
| `package_manifest`           | JSON     | foundation                | Defines package identity, inventory, counts, phases, validation rules |
| `release_readme`             | Markdown | foundation                | Explains package purpose and usage                                    |
| `architecture_overview`      | Markdown | foundation                | Explains layer model and skill separation                             |
| `skills_file_map`            | CSV      | foundation                | Maps package files to roles, dependencies, and usage                  |
| `skills_schema`              | Markdown | foundation                | Defines package schema                                                |
| `source_data_decision`       | Markdown | foundation                | Defines vendored source data correction                               |
| `source_data_manifest`       | JSON     | source_data_snapshot      | Defines vendored source-data inventory                                |
| `source_data_readme`         | Markdown | source_data_snapshot      | Explains source-data layout and usage                                 |
| `source_data_file_map`       | CSV      | source_data_snapshot      | Maps vendored source files                                            |
| `source_data_refresh_policy` | Markdown | source_data_snapshot      | Defines refresh rules                                                 |
| `source_specific_manifest`   | JSON     | source_data_snapshot      | Describes one vendored source group                                   |
| `shared_kernel_doc`          | Markdown | shared_canonical_kernel   | Defines shared skill governance                                       |
| `skill_manifest`             | JSON     | skill_manifest            | Defines one skill package                                             |
| `core_spec`                  | Markdown | skill_core                | Defines environment-independent core behavior                         |
| `core_protocol`              | Markdown | skill_core                | Defines skill-specific reasoning protocol                             |
| `cli_spec`                   | Markdown | canonical_cli_layer       | Defines CLI interface                                                 |
| `cli_command_catalog`        | Markdown | canonical_cli_layer       | Defines supported commands                                            |
| `cli_io_schema`              | Markdown | canonical_cli_layer       | Defines command payloads                                              |
| `cli_examples`               | Markdown | canonical_cli_layer       | Defines example invocations                                           |
| `adapter_spec`               | Markdown | environment_adapter_layer | Defines one runtime adapter                                           |
| `execution_contract`         | Markdown | execution_contracts       | Defines core/CLI/adapter/runtime boundaries                           |
| `adapter_capability_matrix`  | CSV      | execution_contracts       | Defines adapter capability support                                    |

---

# 5. Top-Level Foundation File Schema

## 5.1 `00_PACKAGE_MANIFEST.json`

### 5.1.1 Object Grain

```text id="d65okf"
one object = one package manifest
```

### 5.1.2 Required Fields

1. `package_id`,
2. `package_name`,
3. `release_id`,
4. `release_version`,
5. `package_path`,
6. `package_status`,
7. `document_type`,
8. `created_for`,
9. `0.1_purpose`,
10. `0.2_scope`,
11. `0.3_source_basis`,
12. `1.0_architecture_layers`,
13. `2.0_skill_definitions`,
14. `3.0_file_inventory`,
15. `4.0_counts`,
16. `5.0_delivery_phases`,
17. `6.0_validation_rules`,
18. `7.0_environment_targets`,
19. `8.0_downstream_derivation`,
20. `9.0_final_canonical_statement`.

### 5.1.3 Required Correction

The manifest must include:

```text id="pyugz9"
Source Data Snapshot
```

as the first architecture layer.

### 5.1.4 Required Validation Rules

The manifest must include at least:

1. No Canon Redefinition,
2. Core / CLI / Adapter Separation,
3. CLI Is Not Adapter,
4. Adapter No-Semantic-Authority Rule,
5. Editor Propagation Rule,
6. Query Read-Only Rule,
7. Evidence Required Rule,
8. Anti-Collapse Preservation Rule,
9. Portable Core Rule,
10. Runtime Capability Declaration Rule,
11. Vendored Source Data Rule,
12. No Hardcoded External Workspace Path Rule,
13. Source Data Manifest Rule,
14. Source Data Refresh Trace Rule,
15. Snapshot Operation Rule.

---

## 5.2 `00_SOURCE_DATA_INTEGRATION_DECISION.md`

### 5.2.1 Document Grain

```text id="tr1irk"
one document = binding architecture correction
```

### 5.2.2 Required Sections

1. Document Identity,
2. Decision Summary,
3. Rationale,
4. Binding Decision,
5. Corrected Source Data Structure,
6. Source Data Package Scope,
7. Revised Architecture Layers,
8. Corrections Required in Already Issued Files,
9. Required Corrections to `00_PACKAGE_MANIFEST.json`,
10. Required Corrections to `01_SKILLS_RELEASE_README.md`,
11. Required Corrections to `02_SKILLS_ARCHITECTURE_OVERVIEW.md`,
12. Required Corrections to `03_SKILLS_FILE_MAP.csv`,
13. New Files Required Before Continuing,
14. Source Data Refresh Policy Requirements,
15. Adapter Implications,
16. Query Skill Implications,
17. Content Editor Skill Implications,
18. Validation Rules Introduced by This Decision,
19. Updated Canonical Statements,
20. Final Binding Decision.

### 5.2.3 Validation Rule

This document overrides any earlier package-08 draft statement that assumes external workspace paths.

---

## 5.3 `01_SKILLS_RELEASE_README.md`

### 5.3.1 Document Grain

```text id="dyb5rn"
one document = human-readable release overview
```

### 5.3.2 Required Sections

1. Document Identity,
2. Purpose,
3. Background,
4. Source Data Snapshot,
5. Why Two Skills Are Required,
6. Content Editor Skill,
7. Query Expert Skill,
8. Shared Canonical Kernel,
9. Core / CLI / Adapter / Runtime Separation,
10. Why the CLI Layer Comes Before Adapters,
11. Runtime Adapters,
12. Supported Target Environments,
13. Package Structure,
14. File Groups,
15. Relationship to the Canonical Knowledge Base,
16. Non-Canonical Behaviors,
17. Core Anti-Collapse Rules,
18. Release Counts,
19. Delivery Method,
20. Validation Expectations,
21. Expected Future Uses,
22. Final Canonical Statement.

### 5.3.3 Required Correction

The README must state:

```text id="pmn20u"
Package 08 depends on vendored snapshots of source packages under 00_source_data/.
```

---

## 5.4 `02_SKILLS_ARCHITECTURE_OVERVIEW.md`

### 5.4.1 Document Grain

```text id="feewxj"
one document = architecture overview
```

### 5.4.2 Required Sections

1. Document Identity,
2. Purpose,
3. Architectural Problem,
4. Architectural Solution,
5. Layer 0: Source Data Snapshot,
6. Layer 1: Shared Canonical Kernel,
7. Layer 2: Skill Core,
8. Layer 3: Canonical CLI Layer,
9. Layer 4: Environment Adapter Layer,
10. Layer 5: Runtime Environment,
11. Complete Layer Model,
12. Skill Interaction Model,
13. The Two Skills Compared,
14. Adapter Target Environments,
15. Source Authority Model,
16. Canonical Knowledge Access Modes,
17. Canonical CLI Position,
18. Command Object Model,
19. Adapter Capability Model,
20. Error and Limitation Model,
21. Validation Model,
22. Anti-Collapse Rules,
23. Architecture Invariants,
24. Implementation Readiness,
25. Final Architecture Statement.

### 5.4.3 Required Correction

The architecture overview must represent the layer order as:

```text id="vhup6k"
Source Data Snapshot
→ Shared Canonical Kernel
→ Skill Core
→ Canonical CLI Layer
→ Environment Adapter Layer
→ Runtime Environment
```

---

## 5.5 `03_SKILLS_FILE_MAP.csv`

### 5.5.1 Row Grain

```text id="g6ue7v"
one row = one planned package-08 file
```

### 5.5.2 Primary Key

```text id="dhcxk6"
file_map_id
```

### 5.5.3 Required Columns

1. `file_map_id`,
2. `package_id`,
3. `package_path`,
4. `file_id`,
5. `file_path`,
6. `format`,
7. `document_type`,
8. `architecture_layer`,
9. `owning_skill`,
10. `row_grain_or_document_grain`,
11. `primary_keys`,
12. `secondary_keys_or_refs`,
13. `depends_on_files`,
14. `referenced_by_files`,
15. `canonical_role`,
16. `query_or_edit_usage`,
17. `validation_usage`,
18. `downstream_implementation_usage`,
19. `notes`.

### 5.5.4 Required Correction

The file map must include:

1. `SFM-000` for the source-data decision file,
2. source-data control file rows,
3. source-specific manifest rows,
4. dependencies rewritten through source-data aliases.

---

# 6. Source Data File Schemas

## 6.1 `00_source_data/00.00_SOURCE_DATA_MANIFEST.json`

### 6.1.1 Object Grain

```text id="ofbsxb"
one object = source data manifest for package 08
```

### 6.1.2 Required Fields

1. `source_data_manifest_id`,
2. `package_id`,
3. `source_data_root`,
4. `alias_definitions`,
5. `source_groups`,
6. `vendored_source_policy`,
7. `refresh_policy_ref`,
8. `source_file_map_ref`,
9. `validation_rules`,
10. `snapshot_status`,
11. `last_refresh`,
12. `notes`.

### 6.1.3 Required Source Groups

1. `architectural_taxonomy`,
2. `canonical_responsibilities`,
3. `delegation_enablement_matrix`.

### 6.1.4 Validation Rules

1. Every source group must have a manifest.
2. Every source group must have an upstream origin reference.
3. Every source group must have a normalized local path.
4. All local paths must be under `SOURCE_DATA_ROOT`.

---

## 6.2 `00_source_data/00.01_SOURCE_DATA_README.md`

### 6.2.1 Document Grain

```text id="b9ooy1"
one document = source data user guide
```

### 6.2.2 Required Sections

1. Purpose,
2. Why Source Data Is Vendored,
3. Source Data Root,
4. Alias Vocabulary,
5. Source Groups,
6. Snapshot vs Authority,
7. Read-Only Query Usage,
8. Editor Usage,
9. Refresh Policy Summary,
10. Validation Expectations.

---

## 6.3 `00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv`

### 6.3.1 Row Grain

```text id="b8p1gl"
one row = one vendored source file or source directory
```

### 6.3.2 Primary Key

```text id="wlhf6u"
source_file_map_id
```

### 6.3.3 Required Columns

1. `source_file_map_id`,
2. `source_group_id`,
3. `upstream_path`,
4. `vendored_path`,
5. `normalized_path`,
6. `format`,
7. `source_role`,
8. `required_for_editor`,
9. `required_for_query`,
10. `required_for_kernel`,
11. `refresh_mode`,
12. `checksum_or_hash`,
13. `last_synced_at`,
14. `validation_status`,
15. `notes`.

### 6.3.4 Validation Rules

1. `vendored_path` must begin with `08_assembler_skills/00_source_data/`.
2. `upstream_path` must be reference metadata only, not a runtime dependency.
3. `required_for_query` rows must be readable by query adapters.
4. `required_for_editor` rows must be included in impact analysis.

---

## 6.4 `00_source_data/00.03_SOURCE_DATA_REFRESH_POLICY.md`

### 6.4.1 Document Grain

```text id="of6ubj"
one document = source data refresh policy
```

### 6.4.2 Required Sections

1. Refresh Purpose,
2. Refresh Modes,
3. Allowed Sources,
4. Disallowed Runtime Dependencies,
5. Refresh Record Requirements,
6. Validation After Refresh,
7. Staleness Detection,
8. Adapter Responsibilities,
9. Human Review Requirements,
10. Failure Modes.

### 6.4.3 Refresh Modes

Allowed modes:

1. `manual_copy`,
2. `drive_export`,
3. `git_checkout_copy`,
4. `repository_subtree_snapshot`,
5. `generated_export`,
6. `read_only_live_inspection_with_snapshot_output`.

### 6.4.4 Disallowed Modes

Disallowed modes:

1. `silent_live_external_read`,
2. `unrecorded_overwrite`,
3. `adapter_defined_source_selection`,
4. `runtime_path_assumption`.

---

## 6.5 Source-Specific Manifests

### 6.5.1 Object Grain

```text id="fr6d1b"
one object = manifest for one vendored source group
```

### 6.5.2 Required Files

1. `taxonomy_source_manifest.json`,
2. `responsibilities_source_manifest.json`,
3. `delegation_source_manifest.json`.

### 6.5.3 Required Fields

1. `source_group_id`,
2. `source_group_name`,
3. `upstream_name`,
4. `upstream_reference_path`,
5. `vendored_root`,
6. `normalization_rules`,
7. `included_files`,
8. `excluded_files`,
9. `required_by_skills`,
10. `refresh_policy`,
11. `validation_rules`,
12. `known_limitations`.

---

# 7. Shared Canonical Kernel Schema

## 7.1 Kernel File Grain

```text id="bgx372"
one markdown document = one kernel governance topic
```

## 7.2 Required Kernel Files

```text id="s5avwz"
00_shared_canonical_kernel/00.01_CANONICAL_KERNEL.md
00_shared_canonical_kernel/00.02_ID_GRAMMAR_AND_JOIN_KEYS.md
00_shared_canonical_kernel/00.03_SOURCE_PRIORITY_AND_AUTHORITY.md
00_shared_canonical_kernel/00.04_ANTI_COLLAPSE_RULES.md
00_shared_canonical_kernel/00.05_VALIDATION_BASELINE.md
```

## 7.3 Kernel Dependency Rule

### 7.3.1

Kernel files may depend on vendored source data.

### 7.3.2

Kernel files must not depend on runtime adapter behavior.

### 7.3.3

Kernel files must not include environment-specific commands.

---

## 7.4 `00.01_CANONICAL_KERNEL.md`

### 7.4.1 Required Sections

1. Purpose,
2. Source Data Snapshot Dependency,
3. Canonical Concept Set,
4. Responsibility vs Obligation,
5. Delegated Entity vs Governed Object,
6. Enablement vs Implementation,
7. Surface vs Port vs Runtime Actor,
8. Contract vs Runtime Interface,
9. Trace and Evidence Rules,
10. Kernel Rules for Editor Skill,
11. Kernel Rules for Query Skill,
12. Final Kernel Law.

### 7.4.2 Required Rule

```text id="qkw047"
The kernel governs both skills but does not execute either skill.
```

---

## 7.5 `00.02_ID_GRAMMAR_AND_JOIN_KEYS.md`

### 7.5.1 Required Sections

1. Purpose,
2. Source of ID Grammar,
3. Source Data Aliases,
4. Canonical ID Namespaces,
5. Join Key Families,
6. Multi-Value Field Rules,
7. Query Join Rules,
8. Editor Propagation Join Rules,
9. Invalid ID Patterns,
10. Validation Checklist.

### 7.5.2 Required Source Reference

This file must refer to:

```text id="s9hf7x"
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.02_JOIN_KEYS_REFERENCE.csv
```

---

## 7.6 `00.03_SOURCE_PRIORITY_AND_AUTHORITY.md`

### 7.6.1 Required Sections

1. Purpose,
2. Snapshot vs Authority,
3. Source Priority Order,
4. Reference Markdown Authority,
5. CSV Record Authority,
6. JSON Rollup Authority,
7. Schema Authority,
8. Conflict Resolution,
9. Staleness Handling,
10. Runtime Limitation Handling.

### 7.6.2 Required Rule

```text id="jqpefr"
External upstream paths may be recorded as origin metadata but must not be required for runtime operation.
```

---

## 7.7 `00.04_ANTI_COLLAPSE_RULES.md`

### 7.7.1 Required Sections

1. Purpose,
2. Anti-Collapse Rule Registry,
3. Metadata Injector Rule,
4. Queue Runtime Layer Rule,
5. Delivery-Cycle Flag Set vs Dispatcher Feedback Report Rule,
6. Queue-as-Container Rule,
7. Waiting List Locator Rule,
8. Envelope Slot Occupancy vs Lifecycle Rule,
9. Registry / Delivery Port vs Dispatcher Rule,
10. Contract Template vs Runtime COM Interface Rule,
11. Editor Enforcement,
12. Query Enforcement,
13. Adapter Enforcement Boundary.

### 7.7.2 Required Rule

```text id="o90d43"
Adapters may report anti-collapse violations but must not rewrite canonical semantics.
```

---

## 7.8 `00.05_VALIDATION_BASELINE.md`

### 7.8.1 Required Sections

1. Purpose,
2. Shared Validation Classes,
3. Source Data Validation,
4. Kernel Validation,
5. Editor Validation,
6. Query Validation,
7. CLI Validation,
8. Adapter Validation,
9. Runtime Validation,
10. Blocking Rules,
11. Warning Rules,
12. Validation Output Shape.

---

# 8. Skill Manifest Schema

## 8.1 Skill Manifest Grain

```text id="v0l3ia"
one JSON object = one skill manifest
```

## 8.2 Required Skill Manifests

```text id="q5ke34"
01_content_editor_skill/01.00_CONTENT_EDITOR_SKILL_MANIFEST.json
02_query_expert_skill/02.00_QUERY_EXPERT_SKILL_MANIFEST.json
```

## 8.3 Required Fields

1. `skill_id`,
2. `skill_name`,
3. `skill_type`,
4. `skill_mode`,
5. `package_path`,
6. `depends_on_kernel`,
7. `depends_on_source_data`,
8. `core_files`,
9. `cli_files`,
10. `adapter_files`,
11. `execution_contract_refs`,
12. `validation_rules`,
13. `forbidden_behaviors`,
14. `output_contracts`,
15. `implementation_notes`.

## 8.4 Skill Manifest Validation Rules

1. Each skill must depend on the shared kernel.
2. Each skill must depend on source-data aliases, not external paths.
3. Each skill must have a core.
4. Each skill must have a CLI layer.
5. Each skill may have multiple adapters.
6. No adapter may be listed as a semantic dependency.

---

# 9. Content Editor Skill Schema

## 9.1 Content Editor Core Grain

```text id="b4fy7u"
one markdown document = one editor core protocol or specification
```

## 9.2 Required Core Files

```text id="b1wk0i"
01_content_editor_skill/core/01.01_CONTENT_EDITOR_CORE_SPEC.md
01_content_editor_skill/core/01.02_CHANGE_CLASSIFICATION.md
01_content_editor_skill/core/01.03_IMPACT_ANALYSIS_PROTOCOL.md
01_content_editor_skill/core/01.04_PATCH_GENERATION_PROTOCOL.md
01_content_editor_skill/core/01.05_PROPAGATION_RULES.md
01_content_editor_skill/core/01.06_EDITOR_VALIDATION_CHECKLIST.md
```

## 9.3 Editor Core Required Behaviors

The editor core must:

1. classify change requests,
2. identify affected source-data files,
3. identify affected package-08 files when skill specs change,
4. generate propagation plans,
5. generate patch plans,
6. validate anti-collapse rules,
7. emit review-ready output,
8. distinguish snapshot update from upstream canonical update,
9. distinguish refresh operation from edit operation.

## 9.4 Editor Core Forbidden Behaviors

The editor core must not:

1. silently mutate source data,
2. emit single-file canonical edits without propagation analysis,
3. introduce IDs without registration,
4. treat adapters as semantic authorities,
5. assume external workspace paths,
6. bypass the source-data refresh policy.

---

## 9.5 Editor CLI Files

```text id="nbq85i"
01_content_editor_skill/cli/01.07_EDITOR_CLI_SPEC.md
01_content_editor_skill/cli/01.08_EDITOR_COMMANDS.md
01_content_editor_skill/cli/01.09_EDITOR_COMMAND_IO_SCHEMA.md
01_content_editor_skill/cli/01.10_EDITOR_CLI_EXAMPLES.md
```

## 9.6 Editor CLI Command Family

```text id="gc7h8j"
assembler-edit
```

## 9.7 Required Editor Commands

At minimum:

1. `propose-change`,
2. `classify-change`,
3. `impact`,
4. `generate-patch`,
5. `validate-patch`,
6. `apply-patch`,
7. `release-delta`,
8. `update-manifests`,
9. `refresh-source-data`,
10. `validate-source-data`,
11. `export-review-bundle`.

## 9.8 Editor CLI Required Constraint

Every editor command that can mutate or propose mutation must declare:

1. target scope,
2. source-data impact,
3. propagation requirement,
4. validation requirement,
5. review output mode.

---

# 10. Query Expert Skill Schema

## 10.1 Query Core Grain

```text id="dm08vu"
one markdown document = one query core protocol or specification
```

## 10.2 Required Core Files

```text id="hd6fd1"
02_query_expert_skill/core/02.01_QUERY_EXPERT_CORE_SPEC.md
02_query_expert_skill/core/02.02_QUERY_ROUTING_PROTOCOL.md
02_query_expert_skill/core/02.03_JOIN_AND_TRACE_PROTOCOL.md
02_query_expert_skill/core/02.04_EVIDENCE_OUTPUT_PROTOCOL.md
02_query_expert_skill/core/02.05_ANSWER_GUARDS.md
02_query_expert_skill/core/02.06_QUERY_VALIDATION_CHECKLIST.md
```

## 10.3 Query Core Required Behaviors

The query core must:

1. classify query intent,
2. route to known query families,
3. resolve source paths through source-data aliases,
4. select join keys,
5. assemble trace evidence,
6. emit source paths,
7. emit confidence or sufficiency status,
8. emit anti-collapse warnings where relevant,
9. remain read-only.

## 10.4 Query Core Forbidden Behaviors

The query core must not:

1. write files,
2. mutate vendored source data,
3. invent missing records,
4. infer new canonical entities,
5. collapse guarded concepts,
6. assume external workspace paths,
7. bypass evidence requirements.

---

## 10.5 Query CLI Files

```text id="mf3h0k"
02_query_expert_skill/cli/02.07_QUERY_CLI_SPEC.md
02_query_expert_skill/cli/02.08_QUERY_COMMANDS.md
02_query_expert_skill/cli/02.09_QUERY_COMMAND_IO_SCHEMA.md
02_query_expert_skill/cli/02.10_QUERY_CLI_EXAMPLES.md
```

## 10.6 Query CLI Command Family

```text id="jnoeea"
assembler-query
```

## 10.7 Required Query Commands

At minimum:

1. `responsibility`,
2. `obligation`,
3. `sub-responsibility`,
4. `entity`,
5. `object`,
6. `enablement`,
7. `surface`,
8. `gap`,
9. `contract`,
10. `doctrine`,
11. `guard`,
12. `file`,
13. `source-data`,
14. `validate`,
15. `ontology-seeds`.

## 10.8 Query CLI Required Constraint

Every query command must declare:

1. read-only mode,
2. input ID or search pattern,
3. evidence requirement,
4. source-data root,
5. output format,
6. anti-collapse check setting.

---

# 11. CLI Schema

## 11.1 CLI Layer Grain

```text id="m5bg00"
one markdown document = one CLI command or I/O specification
```

## 11.2 Shared CLI Command Object

A canonical CLI command object should include:

```json id="ew8ztn"
{
  "command_family": "assembler-query | assembler-edit",
  "command_name": "string",
  "input": {},
  "execution_constraints": {},
  "source_data_context": {
    "source_data_root": "08_assembler_skills/00_source_data/",
    "aliases": {}
  },
  "output_format": "markdown | json | csv | text",
  "requested_capabilities": []
}
```

## 11.3 CLI Result Object

A canonical CLI result object should include:

```json id="v2r3cg"
{
  "command_family": "assembler-query | assembler-edit",
  "command_name": "string",
  "status": "success | partial | failed | unsupported",
  "result": {},
  "evidence": [],
  "changed_files": [],
  "validation": [],
  "warnings": [],
  "errors": [],
  "adapter_report": {},
  "source_data_report": {}
}
```

## 11.4 CLI Validation Rules

1. CLI commands must be environment-neutral.
2. CLI commands must include source-data context.
3. CLI commands must not call runtime APIs directly.
4. CLI outputs must report unsupported capabilities.
5. CLI outputs must preserve evidence and validation results.

---

# 12. Adapter Specification Schema

## 12.1 Adapter File Grain

```text id="b8d6q9"
one markdown document = one adapter specification for one skill and one environment
```

## 12.2 Required Adapter Files

### 12.2.1 Editor Adapters

```text id="xozule"
CODEX_EDITOR_ADAPTER.md
KILO_CODE_EDITOR_ADAPTER.md
OPENCODE_EDITOR_ADAPTER.md
GITHUB_EDITOR_ADAPTER.md
GOOGLE_DRIVE_EDITOR_ADAPTER.md
LOCAL_EDITOR_ADAPTER.md
```

### 12.2.2 Query Adapters

```text id="du1wkw"
CODEX_QUERY_ADAPTER.md
KILO_CODE_QUERY_ADAPTER.md
OPENCODE_QUERY_ADAPTER.md
GITHUB_QUERY_ADAPTER.md
GOOGLE_DRIVE_QUERY_ADAPTER.md
LOCAL_QUERY_ADAPTER.md
```

## 12.3 Required Adapter Sections

1. Adapter Identity,
2. Target Environment,
3. Supported Skill,
4. Supported Command Families,
5. Source Data Resolution,
6. Capability Declaration,
7. Command Execution Mapping,
8. Read/Write Constraints,
9. Validation Support,
10. Error Reporting,
11. Limitation Reporting,
12. Anti-Semantic-Authority Rule,
13. Examples,
14. Final Adapter Rule.

## 12.4 Adapter Source Data Rule

Every adapter must resolve source data through:

```text id="xi4ose"
SOURCE_DATA_ROOT
```

and not through environment-specific external paths.

## 12.5 Adapter No-Semantic-Authority Rule

```text id="hubzdc"
Adapters execute commands. They do not decide canonical meaning.
```

---

# 13. Execution Contract Schema

## 13.1 Required Execution Contract Files

```text id="ywwbcz"
03_execution_contracts/03.01_CORE_TO_CLI_CONTRACT.md
03_execution_contracts/03.02_CLI_COMMAND_GRAMMAR.md
03_execution_contracts/03.03_CLI_TO_ADAPTER_CONTRACT.md
03_execution_contracts/03.04_ADAPTER_CAPABILITY_MATRIX.csv
03_execution_contracts/03.05_ADAPTER_LIFECYCLE.md
03_execution_contracts/03.06_ERROR_AND_LIMITATION_MODEL.md
03_execution_contracts/03.07_INTEGRATION_VALIDATION_PROTOCOL.md
```

## 13.2 `03.01_CORE_TO_CLI_CONTRACT.md`

### 13.2.1 Required Sections

1. Purpose,
2. Boundary Definition,
3. Core Responsibilities,
4. CLI Responsibilities,
5. Source Data Context Passing,
6. Editor Core Output Contract,
7. Query Core Output Contract,
8. Command Object Schema,
9. Result Object Schema,
10. Forbidden Direct Dependencies.

## 13.3 `03.02_CLI_COMMAND_GRAMMAR.md`

### 13.3.1 Required Sections

1. Purpose,
2. Command Family Grammar,
3. Editor Command Grammar,
4. Query Command Grammar,
5. Shared Options,
6. Source Data Options,
7. Output Format Options,
8. Error Grammar,
9. Examples.

## 13.4 `03.03_CLI_TO_ADAPTER_CONTRACT.md`

### 13.4.1 Required Sections

1. Purpose,
2. Boundary Definition,
3. CLI Responsibilities,
4. Adapter Responsibilities,
5. Source Data Resolution,
6. Capability Negotiation,
7. Execution Request Object,
8. Execution Result Object,
9. Unsupported Capability Handling,
10. Forbidden Adapter Behaviors.

## 13.5 `03.04_ADAPTER_CAPABILITY_MATRIX.csv`

### 13.5.1 Row Grain

```text id="d2bzi9"
one row = one adapter capability declaration
```

### 13.5.2 Primary Key

```text id="ng75k9"
capability_matrix_row_id
```

### 13.5.3 Required Columns

1. `capability_matrix_row_id`,
2. `adapter_id`,
3. `skill_id`,
4. `environment_id`,
5. `capability_id`,
6. `support_level`,
7. `read_only_allowed`,
8. `write_allowed`,
9. `source_data_access_mode`,
10. `requires_credentials`,
11. `failure_mode`,
12. `notes`.

## 13.6 `03.05_ADAPTER_LIFECYCLE.md`

Required lifecycle stages:

1. initialize,
2. declare capabilities,
3. resolve source data root,
4. accept CLI command object,
5. validate requested capabilities,
6. execute runtime operation,
7. collect result,
8. report limitations,
9. return canonical result object,
10. shutdown or release resources.

## 13.7 `03.06_ERROR_AND_LIMITATION_MODEL.md`

Required error layers:

1. source-data error,
2. kernel error,
3. core error,
4. CLI error,
5. adapter error,
6. runtime error,
7. validation error,
8. evidence error.

## 13.8 `03.07_INTEGRATION_VALIDATION_PROTOCOL.md`

Required validation categories:

1. source-data resolution,
2. CLI command compliance,
3. adapter capability honesty,
4. read-only query enforcement,
5. editor propagation enforcement,
6. no-semantic-authority enforcement,
7. error reporting correctness,
8. evidence output correctness.

---

# 14. Counts and Inventory Rules

## 14.1 Corrected Minimum Specification File Count

The corrected package-08 specification/control file count must include:

| Group                                         | Count |
| --------------------------------------------- | ----: |
| Top-level foundation files from original plan |     5 |
| Source data integration decision              |     1 |
| Source data control files                     |     4 |
| Source-specific manifests                     |     3 |
| Shared kernel files                           |     5 |
| Content editor skill files                    |    17 |
| Query expert skill files                      |    17 |
| Execution contract files                      |     7 |
| Corrected minimum total                       |    59 |

## 14.2 Count Clarification

### 14.2.1

The corrected minimum total counts package-08 specification and control files.

### 14.2.2

It does not count every vendored canonical source file.

### 14.2.3

Vendored source files must be counted separately in:

```text id="kz6f8a"
00_source_data/00.00_SOURCE_DATA_MANIFEST.json
00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv
```

## 14.3 Format Count Expectations

The corrected minimum package-08 control/specification files should include at least:

| Format   | Minimum Count |
| -------- | ------------: |
| JSON     |             6 |
| CSV      |             3 |
| Markdown |            50 |

## 14.4 Validation Rule

If the manifest reports old counts without the Source Data Snapshot correction, it must be treated as:

```text id="ldugni"
valid_draft_pre_source_data_correction
```

not final.

---

# 15. Source Path Validation Rules

## 15.1 Valid Path Classes

Valid source references include:

1. direct package-08 paths,
2. `SOURCE_DATA_ROOT` alias paths,
3. `TAXONOMY_SOURCE_ROOT` alias paths,
4. `RESPONSIBILITY_SOURCE_ROOT` alias paths,
5. `DELEGATION_SOURCE_ROOT` alias paths,
6. upstream paths only when recorded as metadata in source-data manifests.

## 15.2 Invalid Runtime Path Classes

Invalid runtime dependencies include:

1. sibling workspace folders,
2. user-local absolute filesystem paths,
3. machine-specific drive letters,
4. unversioned Drive search results as canonical path references,
5. adapter-selected live source paths,
6. paths not recorded in source-data manifest.

## 15.3 Examples

### 15.3.1 Valid

```text id="wqyskd"
${DELEGATION_SOURCE_ROOT}/05_trace_coverage_registers/05.01_delegation_trace_v2.csv
```

### 15.3.2 Valid as Metadata Only

```text id="sps02o"
00.03_Canonical_Delegation_Enablement_Matrix_V2/05_Trace_Coverage_Registers/05.01_delegation_trace_v2.csv
```

### 15.3.3 Invalid as Runtime Dependency

```text id="jsm8re"
../00.03_Canonical_Delegation_Enablement_Matrix_V2/05_Trace_Coverage_Registers/05.01_delegation_trace_v2.csv
```

---

# 16. Skill Output Schema Rules

## 16.1 Editor Output Must Include

1. operation type,
2. change classification,
3. source-data status,
4. affected files,
5. propagation plan,
6. generated patch or proposed patch,
7. validation results,
8. anti-collapse checks,
9. review notes,
10. limitations.

## 16.2 Query Output Must Include

1. query type,
2. query family,
3. source-data status,
4. direct answer,
5. evidence path,
6. joined IDs or records,
7. anti-collapse warnings,
8. confidence or sufficiency status,
9. limitations.

## 16.3 Adapter Output Must Include

1. adapter ID,
2. environment ID,
3. command executed,
4. capabilities used,
5. source-data root resolved,
6. runtime operations performed,
7. outputs produced,
8. unsupported capabilities,
9. errors,
10. warnings.

---

# 17. Validation Rule Registry

## 17.1 Blocking Rules

| Rule ID         | Rule                                      |
| --------------- | ----------------------------------------- |
| `SKILL-VAL-001` | No Canon Redefinition                     |
| `SKILL-VAL-002` | Core / CLI / Adapter Separation           |
| `SKILL-VAL-003` | CLI Is Not Adapter                        |
| `SKILL-VAL-004` | Adapter No-Semantic-Authority Rule        |
| `SKILL-VAL-005` | Editor Propagation Rule                   |
| `SKILL-VAL-006` | Query Read-Only Rule                      |
| `SKILL-VAL-007` | Evidence Required Rule                    |
| `SKILL-VAL-008` | Anti-Collapse Preservation Rule           |
| `SKILL-VAL-009` | Portable Core Rule                        |
| `SKILL-VAL-011` | Vendored Source Data Rule                 |
| `SKILL-VAL-012` | No Hardcoded External Workspace Path Rule |
| `SKILL-VAL-015` | Snapshot Operation Rule                   |

## 17.2 Required Rules

| Rule ID         | Rule                                |
| --------------- | ----------------------------------- |
| `SKILL-VAL-010` | Runtime Capability Declaration Rule |
| `SKILL-VAL-013` | Source Data Manifest Rule           |
| `SKILL-VAL-014` | Source Data Refresh Trace Rule      |

## 17.3 Rule Severity Meaning

| Severity        | Meaning                                         |
| --------------- | ----------------------------------------------- |
| `blocking`      | Output is invalid if violated                   |
| `required`      | Must be satisfied before release-ready status   |
| `warning`       | Must be reported but may not block draft output |
| `informational` | Provides implementation guidance                |

---

# 18. Downstream Implementation Schema Guidance

## 18.1 Candidate Modules

A future implementation may derive modules:

1. `source_data_resolver`,
2. `source_data_manifest_loader`,
3. `canonical_kernel`,
4. `id_grammar_validator`,
5. `anti_collapse_checker`,
6. `editor_core`,
7. `query_core`,
8. `cli_parser`,
9. `cli_command_serializer`,
10. `adapter_manager`,
11. `capability_negotiator`,
12. `validation_engine`,
13. `evidence_formatter`.

## 18.2 Candidate Data Structures

A future implementation may derive:

1. `SourceDataManifest`,
2. `SourceDataGroup`,
3. `SourceDataFileRef`,
4. `CanonicalAliasMap`,
5. `SkillManifest`,
6. `CommandObject`,
7. `CommandResult`,
8. `AdapterCapabilities`,
9. `ValidationResult`,
10. `EvidencePath`,
11. `PatchPlan`,
12. `ReviewBundle`.

## 18.3 Candidate CLI Packages

A future implementation may expose:

```bash id="d9lsil"
assembler-source-data validate
assembler-source-data refresh --group delegation_enablement_matrix
assembler-edit propose-change change_request.md
assembler-edit generate-patch change_request.md
assembler-query responsibility RSP-CAN-027
assembler-query gap G-006 --evidence
```

---

# 19. Non-Canonical Patterns

## 19.1 External Path Assumption

Invalid:

```text id="drx9qz"
The query skill reads directly from ../00.03_Canonical_Delegation_Enablement_Matrix_V2/.
```

Valid:

```text id="v4g6fk"
The query skill reads from ${DELEGATION_SOURCE_ROOT}/.
```

## 19.2 Adapter Semantic Authority

Invalid:

```text id="jzrq58"
The GitHub adapter decides that a missing responsibility should be created.
```

Valid:

```text id="q764m0"
The GitHub adapter reports a missing source record and returns a failed or partial result.
```

## 19.3 CLI as Adapter

Invalid:

```text id="j5m573"
The Local CLI adapter defines the assembler-query command set.
```

Valid:

```text id="kup14p"
The canonical CLI layer defines assembler-query; Local Runtime adapter executes it.
```

## 19.4 Silent Source Refresh

Invalid:

```text id="yi4c2m"
The Google Drive adapter silently overwrites vendored source data from a live document.
```

Valid:

```text id="pncs1v"
The Google Drive adapter exports source data through a declared refresh workflow with recorded source, files changed, and validation result.
```

---

# 20. Final Schema Statement

## 20.1

This schema defines the corrected structure of `08_assembler_skills/`.

## 20.2

The package is not complete unless it includes the Source Data Snapshot layer.

## 20.3

All source dependencies must resolve through internal vendored source-data paths or approved aliases.

## 20.4

The package defines two portable skills:

1. Content Editor Skill,
2. Query Expert Skill.

## 20.5

Both skills share a canonical kernel.

## 20.6

Both skills express operations through canonical CLI layers.

## 20.7

Adapters execute commands but never decide canonical semantics.

## 20.8

The final governing law is:

```text id="arqixe"
Source data is vendored.
Kernel governs.
Core reasons.
CLI expresses.
Adapter executes.
Runtime hosts.
```

