FILE:
`08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md`

CONTENT:

````markdown id="z7n4p8"
# Source Data Integration Decision
## Vendored Canonical Source Data for Portable Assembler Skills

---

# 0. Document Identity

## 0.1 File Path

```text
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
````

## 0.2 Package

```text
08_assembler_skills/
```

## 0.3 Document Type

```text
source_data_integration_decision
```

## 0.4 Status

```text
binding_architectural_correction
```

## 0.5 Applies To

This decision applies to all files in:

```text
08_assembler_skills/
```

including files already drafted before this decision:

```text
08_assembler_skills/00_PACKAGE_MANIFEST.json
08_assembler_skills/01_SKILLS_RELEASE_README.md
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
08_assembler_skills/03_SKILLS_FILE_MAP.csv
```

---

# 1. Decision Summary

## 1.1

The Assembler Skills package must not depend on hardcoded external workspace paths.

## 1.2

All canonical source material required by the skills must be vendored, snapshotted, or mirrored inside the skills package itself.

## 1.3

The canonical internal source root for the skills package is:

```text
08_assembler_skills/00_source_data/
```

## 1.4

All references from skill files to taxonomy, responsibility, delegation, obligation, trace, and rollup sources must resolve through this internal source-data root.

## 1.5

The corrected architecture becomes:

```text
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

## 1.6

The corrected operating law becomes:

```text
Source data is vendored.
Kernel governs.
Core reasons.
CLI expresses.
Adapter executes.
Runtime hosts.
```

---

# 2. Rationale

## 2.1 Portability Requirement

### 2.1.1

The skills are intended to work across multiple environments, including:

1. Codex,
2. Kilo Code,
3. OpenCode,
4. GitHub,
5. Google Drive,
6. Local Runtime,
7. future runtimes.

### 2.1.2

These environments cannot be assumed to share the same filesystem layout.

### 2.1.3

Therefore, the skills must not assume that source material exists in sibling directories such as:

```text
00.01_Architectural_Taxonomy/
00.02_Assembler_Canonical_Responsibilities/
00.03_Canonical_Delegation_Enablement_Matrix_V2/
```

## 2.2 Current Project Tree Evidence

### 2.2.1

The current subsystem tree shows that the upstream canonical sources are distributed across separate folders, including:

```text
00.01_Architectural_Taxonomy/
00.02_Assembler_Canonical_Responsibilities/
00.03_Canonical_Delegation_Enablement_Matrix_V2/
```

The uploaded filesystem tree confirms this distribution and shows the delegation release files under `00.03_Canonical_Delegation_Enablement_Matrix_V2/`, including release manifest, reference markdown, entity indexes, delegation matrix, obligation delegation, trace coverage, and rollup indexes. 

### 2.2.2

That layout is valid for the broader Assembler Subsystem workspace.

### 2.2.3

However, it must not become a runtime assumption inside the skills package.

## 2.3 Skill Package Independence

### 2.3.1

The skills package must be installable and testable as a self-contained package.

### 2.3.2

A future runtime should be able to receive:

```text
08_assembler_skills/
```

and still find the required canonical source data through internal relative paths.

### 2.3.3

This makes the package suitable for:

1. local CLI execution,
2. repository-based execution,
3. Drive-backed execution,
4. coding-agent workspaces,
5. future packaged skill distributions.

---

# 3. Binding Decision

## 3.1 Vendored Source Data Rule

### 3.1.1

All canonical source dependencies required by package `08_assembler_skills/` must exist under:

```text
08_assembler_skills/00_source_data/
```

### 3.1.2

This includes source data copied, exported, snapshotted, or mirrored from upstream canonical packages.

### 3.1.3

No skill-core, CLI, adapter, or execution-contract document may require direct access to external workspace-relative folders.

## 3.2 No Hardcoded External Workspace Paths Rule

### 3.2.1

The following form is no longer allowed as a binding dependency inside package `08`:

```text
../00.03_Canonical_Delegation_Enablement_Matrix_V2/06_Rollup_Indexes/06.03_QUERY_PATTERNS.md
```

### 3.2.2

The following form is also not allowed as a binding dependency:

```text
00.03_Canonical_Delegation_Enablement_Matrix_V2/06_Rollup_Indexes/06.03_QUERY_PATTERNS.md
```

### 3.2.3

The allowed form is:

```text
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

### 3.2.4

Or, where alias notation is used:

```text
${SOURCE_DATA_ROOT}/00.03_delegation_enablement_matrix/06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

where:

```text
SOURCE_DATA_ROOT = 08_assembler_skills/00_source_data/
```

## 3.3 Source Data Alias Rule

### 3.3.1

The package may use canonical aliases to avoid long repeated paths.

### 3.3.2

The required aliases are:

| Alias                        | Resolves To                                                              |
| ---------------------------- | ------------------------------------------------------------------------ |
| `SKILLS_ROOT`                | `08_assembler_skills/`                                                   |
| `SOURCE_DATA_ROOT`           | `08_assembler_skills/00_source_data/`                                    |
| `TAXONOMY_SOURCE_ROOT`       | `08_assembler_skills/00_source_data/00.01_architectural_taxonomy/`       |
| `RESPONSIBILITY_SOURCE_ROOT` | `08_assembler_skills/00_source_data/00.02_canonical_responsibilities/`   |
| `DELEGATION_SOURCE_ROOT`     | `08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/` |

### 3.3.3

Any file using aliases must define or import the alias vocabulary.

---

# 4. Corrected Source Data Structure

## 4.1 Required Directory Structure

```text
08_assembler_skills/
│
├── 00_SOURCE_DATA_INTEGRATION_DECISION.md
│
├── 00_source_data/
│   ├── 00.00_SOURCE_DATA_MANIFEST.json
│   ├── 00.01_SOURCE_DATA_README.md
│   ├── 00.02_SOURCE_DATA_FILE_MAP.csv
│   ├── 00.03_SOURCE_DATA_REFRESH_POLICY.md
│   │
│   ├── 00.01_architectural_taxonomy/
│   │   ├── taxonomy_source_manifest.json
│   │   ├── 00.00_Unified_Assembler_Architectural_Taxonomy.md
│   │   ├── architectural_taxonomy_csv_indexes/
│   │   ├── assembler_taxonomy_graphviz_files/
│   │   ├── json_01_manifest_layers/
│   │   ├── json_02_external_core_internal_members/
│   │   ├── json_03_runtime_carrier_members/
│   │   ├── json_04_contract_doctrine_relation_family_members/
│   │   ├── json_05_relations_external_policy_envelope/
│   │   ├── json_06_relations_runtime_wait_contracts_doctrine/
│   │   └── taxonomy_adds/
│   │
│   ├── 00.02_canonical_responsibilities/
│   │   ├── responsibilities_source_manifest.json
│   │   ├── Canonical_Responsibility_Obligation_Matrix_V2_1.md
│   │   ├── canonical_responsibility_v2_1_index.json
│   │   ├── coverage_register_v2_1.csv
│   │   ├── obligations_v2_1.csv
│   │   ├── responsibilities_v2_1.csv
│   │   ├── responsibility_obligation_links_v2_1.csv
│   │   └── sub_responsibilities_v2_1.csv
│   │
│   └── 00.03_delegation_enablement_matrix/
│       ├── delegation_source_manifest.json
│       ├── 00_release_manifest/
│       ├── 01_reference_markdown/
│       ├── 02_entity_enablement_indexes/
│       ├── 03_delegation_matrix/
│       ├── 04_obligation_delegation/
│       ├── 05_trace_coverage_registers/
│       └── 06_rollup_indexes/
│
├── 00_shared_canonical_kernel/
├── 01_content_editor_skill/
├── 02_query_expert_skill/
└── 03_execution_contracts/
```

## 4.2 Case Normalization

### 4.2.1

Inside `00_source_data/`, directory names should use lowercase snake case.

### 4.2.2

This avoids runtime inconsistencies across case-sensitive and case-insensitive filesystems.

### 4.2.3

The source-data manifest must preserve original upstream names and normalized local names.

Example:

| Upstream Folder                                                      | Vendored Folder                                                        |
| -------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| `00.03_Canonical_Delegation_Enablement_Matrix_V2/06_Rollup_Indexes/` | `00_source_data/00.03_delegation_enablement_matrix/06_rollup_indexes/` |

---

# 5. Source Data Package Scope

## 5.1 Architectural Taxonomy Source

### 5.1.1

The vendored taxonomy source must include the unified taxonomy and its machine-oriented indexes.

### 5.1.2

The unified taxonomy defines the layers, entities, runtime/state objects, carrier objects, contract/template families, doctrine rules, and relation families used by the skills. The uploaded taxonomy content shows these layer groups and member classes, including `L-001` through `L-007`. 

### 5.1.3

The taxonomy source is required by:

1. Shared Canonical Kernel,
2. Content Editor Skill,
3. Query Expert Skill,
4. future ontology expert skill,
5. future graph derivation.

## 5.2 Canonical Responsibilities Source

### 5.2.1

The vendored responsibility source must include the canonical responsibility and obligation matrix files.

### 5.2.2

It provides the responsibility and obligation IDs that the delegation and query layers must not invent.

### 5.2.3

It is required by:

1. change classification,
2. responsibility validation,
3. obligation validation,
4. trace validation,
5. query answer grounding.

## 5.3 Delegation and Enablement Source

### 5.3.1

The vendored delegation source must include the complete delegation-enablements release, including:

1. release manifest,
2. reference markdown,
3. entity and enablement indexes,
4. delegation matrix,
5. obligation delegation,
6. trace coverage registers,
7. rollup indexes.

### 5.3.2

The delegation release is explicitly designed to map:

```text
Responsibility / Obligation
→ Primary Delegated Entity
→ Supporting Entities
→ Governed Objects
→ Enablement Family
→ Surface Type
→ Trace
```

The corrected reference matrix defines this mapping purpose directly. 

### 5.3.3

The rollup package is especially important for query skill operation because it provides cross-package navigation, validation, query guidance, and derivation readiness without adding new semantics. 

---

# 6. Revised Architecture Layers

## 6.1 Previous Layer Model

Before this correction, the architecture was stated as:

```text
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

## 6.2 Corrected Layer Model

The corrected architecture is:

```text
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

## 6.3 Layer Responsibilities

| Layer                     | Responsibility                                                                     |
| ------------------------- | ---------------------------------------------------------------------------------- |
| Source Data Snapshot      | Stores vendored canonical source files inside the skills package                   |
| Shared Canonical Kernel   | Governs ID grammar, source authority, anti-collapse rules, and validation baseline |
| Skill Core                | Performs editor or query reasoning without runtime assumptions                     |
| Canonical CLI Layer       | Expresses core decisions as portable commands                                      |
| Environment Adapter Layer | Executes commands in a target runtime                                              |
| Runtime Environment       | Hosts actual filesystem, repository, Drive, or workspace operations                |

## 6.4 Dependency Rule

### 6.4.1

The correct dependency direction is:

```text
Source Data Snapshot
← Shared Canonical Kernel
← Skill Core
← Canonical CLI Layer
← Environment Adapter Layer
← Runtime Environment
```

### 6.4.2

The source data must not depend on the skill core.

### 6.4.3

The skill core must not depend on runtime-specific paths.

### 6.4.4

Adapters may locate or refresh source data only through defined source-data contracts.

---

# 7. Corrections Required in Already Issued Files

## 7.1 Correction Scope

### 7.1.1

The following files were issued before this decision and must be treated as requiring revision:

```text
08_assembler_skills/00_PACKAGE_MANIFEST.json
08_assembler_skills/01_SKILLS_RELEASE_README.md
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
08_assembler_skills/03_SKILLS_FILE_MAP.csv
```

### 7.1.2

These files remain useful, but their references to upstream source files must be corrected to internal vendored paths.

---

# 8. Required Corrections to `00_PACKAGE_MANIFEST.json`

## 8.1 Add Source Data Layer

### 8.1.1

Add a new architecture layer before the shared kernel:

```json
"1.0_architecture_layers": {
  "1.0_source_data_snapshot": {
    "role": "Vendored canonical source data used by the skills package.",
    "authority": "Provides local source evidence copied or snapshotted from upstream canonical Assembler packages.",
    "path": "08_assembler_skills/00_source_data/",
    "must_not_do": "Must not depend on external workspace-relative paths at runtime."
  }
}
```

## 8.2 Add Source Data Scope

### 8.2.1

Add to `0.2_scope.in_scope`:

```json
"vendored canonical source data under 00_source_data",
"source data manifests and refresh policy",
"portable internal source path aliases"
```

### 8.2.2

Add to `0.2_scope.out_of_scope`:

```json
"hardcoded dependency on external sibling workspace folders",
"runtime assumption that upstream source folders exist outside 08_assembler_skills"
```

## 8.3 Replace External Source Basis Paths

### 8.3.1

Any path such as:

```text
06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

must become:

```text
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

or:

```text
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.03_QUERY_PATTERNS.md
```

## 8.4 Add Source Data Files to Inventory

### 8.4.1

Add the following files to the package inventory:

```text
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
08_assembler_skills/00_source_data/00.01_SOURCE_DATA_README.md
08_assembler_skills/00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv
08_assembler_skills/00_source_data/00.03_SOURCE_DATA_REFRESH_POLICY.md
```

### 8.4.2

Add source-specific manifests:

```text
08_assembler_skills/00_source_data/00.01_architectural_taxonomy/taxonomy_source_manifest.json
08_assembler_skills/00_source_data/00.02_canonical_responsibilities/responsibilities_source_manifest.json
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/delegation_source_manifest.json
```

## 8.5 Update Counts

### 8.5.1

The planned total file count must increase.

### 8.5.2

At minimum, add:

| Added Item                          | Count |
| ----------------------------------- | ----: |
| Source data integration decision    |     1 |
| Source data top-level control files |     4 |
| Source-specific manifests           |     3 |
| Total required control additions    |     8 |

### 8.5.3

If the previous planned total was:

```text
planned_total_file_count = 49
```

then the corrected minimum planned total becomes:

```text
planned_total_file_count = 57
```

### 8.5.4

This count does not include every vendored source file. It counts only the package-08 specification/control files.

### 8.5.5

The vendored source file count should be tracked separately as:

```text
vendored_source_file_count
```

## 8.6 Add Validation Rules

### 8.6.1

Add:

```json
{
  "rule_id": "SKILL-VAL-011",
  "rule_name": "Vendored Source Data Rule",
  "severity": "blocking",
  "statement": "All skill source dependencies must resolve through 08_assembler_skills/00_source_data/ or approved source-data aliases."
}
```

### 8.6.2

Add:

```json
{
  "rule_id": "SKILL-VAL-012",
  "rule_name": "No Hardcoded External Workspace Path Rule",
  "severity": "blocking",
  "statement": "Package 08 files must not require external sibling workspace folders at runtime."
}
```

## 8.7 Update Final Canonical Statement

### 8.7.1

Replace the old layer order with:

```json
"canonical_layer_order": [
  "Source Data Snapshot",
  "Shared Canonical Kernel",
  "Skill Core",
  "Canonical CLI Layer",
  "Environment Adapter Layer",
  "Runtime Environment"
]
```

### 8.7.2

Replace the operating law with:

```json
"canonical_operating_law": "Source data is vendored. Kernel governs. Core reasons. CLI expresses. Adapter executes. Runtime hosts."
```

---

# 9. Required Corrections to `01_SKILLS_RELEASE_README.md`

## 9.1 Add Source Data Section

### 9.1.1

Add a new section after the Background section:

```markdown
# Source Data Snapshot

The skills package vendors its required canonical source data under:

`08_assembler_skills/00_source_data/`

This prevents the skills from depending on external workspace-specific paths.
```

## 9.2 Update Package Structure

### 9.2.1

The package structure section must include:

```text
00_SOURCE_DATA_INTEGRATION_DECISION.md
00_source_data/
```

before:

```text
00_shared_canonical_kernel/
```

## 9.3 Replace Source Basis Wording

### 9.3.1

Where the README says package `08` depends on source packages, clarify:

```text
Package 08 depends on vendored snapshots of the source packages placed under 00_source_data/.
```

## 9.4 Add Path Alias Policy

### 9.4.1

Add:

```text
SOURCE_DATA_ROOT = 08_assembler_skills/00_source_data/
DELEGATION_SOURCE_ROOT = ${SOURCE_DATA_ROOT}/00.03_delegation_enablement_matrix/
```

## 9.5 Update Delivery Method

### 9.5.1

The preferred delivery sequence must become:

```text
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
08_assembler_skills/00_PACKAGE_MANIFEST.json
08_assembler_skills/01_SKILLS_RELEASE_README.md
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
08_assembler_skills/03_SKILLS_FILE_MAP.csv
08_assembler_skills/04_SKILLS_SCHEMA.md
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
```

or the decision file may be treated as retroactive correction before continuing.

## 9.6 Add Non-Canonical Behavior

### 9.6.1

Add to non-canonical behaviors:

```text
The package is non-canonical if it requires hardcoded external workspace paths for canonical source data.
```

---

# 10. Required Corrections to `02_SKILLS_ARCHITECTURE_OVERVIEW.md`

## 10.1 Add Layer 0: Source Data Snapshot

### 10.1.1

Add a new architecture layer before the shared canonical kernel:

```markdown
# Layer 0: Source Data Snapshot

The Source Data Snapshot is the vendored local copy of upstream canonical sources required by the skills.
```

## 10.2 Update Layer Model Diagrams

### 10.2.1

Replace:

```text
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

with:

```text
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

## 10.3 Update Dependency Direction

### 10.3.1

Replace:

```text
Kernel ← Core ← CLI ← Adapter ← Runtime
```

with:

```text
Source Data Snapshot ← Kernel ← Core ← CLI ← Adapter ← Runtime
```

## 10.4 Add Forbidden Dependency

### 10.4.1

Add:

```text
Core depends on external sibling workspace paths
Adapter silently rewrites source paths without source-data manifest
Runtime mutates vendored source data without refresh policy
```

## 10.5 Update Implementation Readiness

### 10.5.1

Implementation should begin from:

```text
00_source_data/
00_shared_canonical_kernel/
03_execution_contracts/
```

not from external workspace paths.

---

# 11. Required Corrections to `03_SKILLS_FILE_MAP.csv`

## 11.1 Add Source Data Decision Row

### 11.1.1

Add a row for:

```text
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
```

Suggested row values:

```csv
SFM-000,08_assembler_skills,08_assembler_skills/,08.SOURCE_DECISION,08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md,markdown,source_data_integration_decision,foundation,all_skills,"one document = binding source-data decision",document_path,source_alias;source_data_root;vendored_source_policy,08_assembler_skills/03_SKILLS_FILE_MAP.csv,all_package_08_files,"Defines the binding correction requiring vendored source data under 00_source_data and forbidding hardcoded external workspace paths.","Use to determine correct path policy before reading any source dependency.","Validate all references resolve through SOURCE_DATA_ROOT aliases.","Portability rule source; package correction record.","This row should precede SFM-001."
```

## 11.2 Add Source Data Control Rows

### 11.2.1

Add rows for:

```text
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
08_assembler_skills/00_source_data/00.01_SOURCE_DATA_README.md
08_assembler_skills/00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv
08_assembler_skills/00_source_data/00.03_SOURCE_DATA_REFRESH_POLICY.md
```

## 11.3 Add Source-Specific Manifest Rows

### 11.3.1

Add rows for:

```text
08_assembler_skills/00_source_data/00.01_architectural_taxonomy/taxonomy_source_manifest.json
08_assembler_skills/00_source_data/00.02_canonical_responsibilities/responsibilities_source_manifest.json
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/delegation_source_manifest.json
```

## 11.4 Change Dependencies

### 11.4.1

Any `depends_on_files` value that points directly to:

```text
01_reference_markdown/
02_entity_enablement_indexes/
03_delegation_matrix/
04_obligation_delegation/
05_trace_coverage_registers/
06_rollup_indexes/
```

must be rewritten to:

```text
${DELEGATION_SOURCE_ROOT}/01_reference_markdown/
${DELEGATION_SOURCE_ROOT}/02_entity_enablement_indexes/
${DELEGATION_SOURCE_ROOT}/03_delegation_matrix/
${DELEGATION_SOURCE_ROOT}/04_obligation_delegation/
${DELEGATION_SOURCE_ROOT}/05_trace_coverage_registers/
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/
```

## 11.5 Update Architecture Layer Values

### 11.5.1

New source data rows must use:

```text
architecture_layer = source_data_snapshot
```

### 11.5.2

Foundation files may depend on `source_data_snapshot` but must not be classified as source data unless they are inside `00_source_data/`.

## 11.6 Update Notes

### 11.6.1

For all rows relying on canonical source material, add a note:

```text
Source references must resolve through SOURCE_DATA_ROOT aliases, not external workspace paths.
```

---

# 12. New Files Required Before Continuing

## 12.1 Source Data Control Files

### 12.1.1

Before continuing deep skill definitions, the following files should be produced:

```text
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
08_assembler_skills/00_source_data/00.01_SOURCE_DATA_README.md
08_assembler_skills/00_source_data/00.02_SOURCE_DATA_FILE_MAP.csv
08_assembler_skills/00_source_data/00.03_SOURCE_DATA_REFRESH_POLICY.md
```

## 12.2 Source-Specific Manifests

### 12.2.1

Then produce:

```text
08_assembler_skills/00_source_data/00.01_architectural_taxonomy/taxonomy_source_manifest.json
08_assembler_skills/00_source_data/00.02_canonical_responsibilities/responsibilities_source_manifest.json
08_assembler_skills/00_source_data/00.03_delegation_enablement_matrix/delegation_source_manifest.json
```

## 12.3 Revised Foundation Files

### 12.3.1

After source-data control files are defined, issue revised versions of:

```text
08_assembler_skills/00_PACKAGE_MANIFEST.json
08_assembler_skills/01_SKILLS_RELEASE_README.md
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
08_assembler_skills/03_SKILLS_FILE_MAP.csv
```

or issue explicit patch documents for each.

---

# 13. Source Data Refresh Policy Requirements

## 13.1 Refresh Is Controlled

### 13.1.1

Vendored source data must not be silently overwritten.

### 13.1.2

Any refresh from upstream source directories must record:

1. source package name,
2. source path,
3. source version or timestamp,
4. copied files,
5. removed files,
6. changed files,
7. checksum or content hash if available,
8. refresh reason,
9. validation result,
10. operator or tool context.

## 13.2 Refresh Must Preserve Skill Portability

### 13.2.1

A refresh operation may read from external locations.

### 13.2.2

But after refresh, runtime skill operation must only depend on internal source-data paths.

## 13.3 Refresh Must Not Change Semantics by Itself

### 13.3.1

Refreshing source data updates the local snapshot.

### 13.3.2

It does not authorize new skill semantics.

### 13.3.3

If refreshed source data changes canonical meaning, the Content Editor Skill must trigger impact analysis and validation.

---

# 14. Adapter Implications

## 14.1 Adapter Source Data Responsibility

### 14.1.1

Adapters may help locate, copy, export, or refresh source data.

### 14.1.2

However, adapters must not decide which source facts are canonical.

## 14.2 Codex Adapter

### 14.2.1

Codex should treat `00_source_data/` as part of the repository checkout.

### 14.2.2

If source data is stale, Codex may report a stale snapshot error or run a defined refresh workflow.

## 14.3 Kilo Code Adapter

### 14.3.1

Kilo Code should use workspace files only after resolving `SOURCE_DATA_ROOT`.

## 14.4 OpenCode Adapter

### 14.4.1

OpenCode may operate directly on local filesystem paths under `00_source_data/`.

## 14.5 GitHub Adapter

### 14.5.1

GitHub adapter must read vendored source files from repository paths under:

```text
08_assembler_skills/00_source_data/
```

## 14.6 Google Drive Adapter

### 14.6.1

Google Drive adapter may export canonical Docs, Sheets, or Drive files into source-data snapshots.

### 14.6.2

After export, skill operation should use the snapshot model, not live Drive paths, unless a read-only live-source mode is explicitly declared.

## 14.7 Local Runtime Adapter

### 14.7.1

Local runtime must resolve source data through local relative paths under `08_assembler_skills/00_source_data/`.

---

# 15. Query Skill Implications

## 15.1 Query Path Resolution

### 15.1.1

The Query Expert Skill must resolve all source reads through source-data aliases.

### 15.1.2

Example:

```text
assembler-query responsibility RSP-CAN-027
```

should read from:

```text
${DELEGATION_SOURCE_ROOT}/03_delegation_matrix/03.01_delegation_matrix_v2.csv
${DELEGATION_SOURCE_ROOT}/05_trace_coverage_registers/05.01_delegation_trace_v2.csv
```

not from external sibling directories.

## 15.2 Rollup Query Pattern Alignment

### 15.2.1

The query patterns reference defines upstream packages used for query work, including reference markdown, entity indexes, delegation matrix, obligation delegation, and trace coverage registers. 

### 15.2.2

Inside package `08`, those query paths must be interpreted as paths under:

```text
${DELEGATION_SOURCE_ROOT}/
```

## 15.3 No New Semantics

### 15.3.1

The rollup schema states that the rollup package must not introduce new semantics and only provides navigation, validation, query guidance, and derivation readiness. 

### 15.3.2

The Query Skill must inherit the same law.

---

# 16. Content Editor Skill Implications

## 16.1 Edit Target Clarity

### 16.1.1

The Content Editor Skill must distinguish between:

1. editing the vendored source snapshot,
2. proposing changes to upstream canonical source,
3. refreshing the snapshot from upstream,
4. generating a patch bundle for review.

## 16.2 No Silent Snapshot Mutation

### 16.2.1

A content edit must not silently mutate `00_source_data/` without:

1. impact analysis,
2. propagation plan,
3. validation report,
4. source-data refresh or patch decision,
5. release delta note.

## 16.3 Snapshot vs Authority

### 16.3.1

The vendored snapshot is the local operating evidence for the skill.

### 16.3.2

The semantic authority remains the canonical source content represented by the snapshot.

### 16.3.3

If the snapshot is stale, the correct behavior is to report staleness or refresh under policy, not to infer missing facts.

---

# 17. Validation Rules Introduced by This Decision

## 17.1 SKILL-VAL-011 — Vendored Source Data Rule

```text
All skill source dependencies must resolve through 08_assembler_skills/00_source_data/ or approved source-data aliases.
```

Severity:

```text
blocking
```

## 17.2 SKILL-VAL-012 — No Hardcoded External Workspace Path Rule

```text
Package 08 files must not require external sibling workspace folders at runtime.
```

Severity:

```text
blocking
```

## 17.3 SKILL-VAL-013 — Source Data Manifest Rule

```text
Every vendored source-data group must have a source-specific manifest identifying upstream origin, normalized local path, file inventory, and refresh policy.
```

Severity:

```text
required
```

## 17.4 SKILL-VAL-014 — Source Data Refresh Trace Rule

```text
Any source-data refresh must record source, changed files, reason, and validation result.
```

Severity:

```text
required
```

## 17.5 SKILL-VAL-015 — Snapshot Operation Rule

```text
Skill runtime operation may read vendored source data, but source-data mutation requires explicit editor workflow or refresh workflow.
```

Severity:

```text
blocking
```

---

# 18. Updated Canonical Statements

## 18.1 Updated Layer Order

```text
Source Data Snapshot
Shared Canonical Kernel
Skill Core
Canonical CLI Layer
Environment Adapter Layer
Runtime Environment
```

## 18.2 Updated Operating Law

```text
Source data is vendored.
Kernel governs.
Core reasons.
CLI expresses.
Adapter executes.
Runtime hosts.
```

## 18.3 Updated Non-Canonical Conditions

The package is non-canonical if:

1. it requires external sibling workspace paths at runtime,
2. it omits `00_source_data/` while claiming portable operation,
3. it treats a live runtime folder as semantic authority without snapshot policy,
4. it allows adapters to rewrite source references without manifest trace,
5. it allows query skill to read outside source-data aliases by default,
6. it allows editor skill to mutate source data without propagation and validation,
7. it treats vendored source data as implementation code rather than canonical evidence,
8. it fails to record source-data refreshes.

---

# 19. Implementation Consequence

## 19.1

The next package files should be generated with this decision already applied.

## 19.2

The next recommended file is:

```text
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
```

## 19.3

After source-data control files are completed, the foundation files should be revised.

## 19.4

Until that revision is issued, the previously delivered files are considered:

```text
valid_draft_pre_source_data_correction
```

not final package foundation files.

---

# 20. Final Binding Decision

## 20.1

The Assembler Skills package must be self-contained with respect to canonical source data.

## 20.2

The package may remember upstream origins, but runtime operation must resolve through internal source-data paths.

## 20.3

The source-data snapshot layer is now the first layer of the skills architecture.

## 20.4

The corrected architecture is:

```text
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

## 20.5

The corrected operating law is:

```text
Source data is vendored. Kernel governs. Core reasons. CLI expresses. Adapter executes. Runtime hosts.
```

```
