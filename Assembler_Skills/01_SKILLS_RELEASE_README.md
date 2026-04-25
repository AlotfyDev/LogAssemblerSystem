FILE:
`08_assembler_skills/01_SKILLS_RELEASE_README.md`

CONTENT:

````markdown id="s8k2m4"
# Assembler Skills Architecture Pack
## Release README

---

# 0. Document Identity

## 0.1 File Path

```text
08_assembler_skills/01_SKILLS_RELEASE_README.md
````

## 0.2 Package

```text
08_assembler_skills/
```

## 0.3 Release

```text
Assembler Skills Architecture Pack V1
```

## 0.4 Status

```text
Draft for structured local installation
```

---

# 1. Purpose

## 1.1

This release defines the portable skill architecture required to operate over the Assembler System canonical knowledge base.

## 1.2

It introduces two distinct skills:

1. `Assembler Canonical Content Editor Skill`,
2. `Assembler Rollup Query Expert Skill`.

## 1.3

The purpose of this release is not to change the Assembler System canon.

## 1.4

The purpose is to define how future skill runtimes may:

1. maintain canonical content safely,
2. query canonical knowledge reliably,
3. preserve anti-collapse rules,
4. operate across multiple execution environments,
5. separate semantic reasoning from runtime integration.

---

# 2. Background

## 2.1

The earlier canonical release established a structured knowledge base for responsibilities, obligations, delegation entities, enablement families, governed objects, contracts, gaps, traces, and rollups.

## 2.2

That release produced a queryable architecture organized through packages:

```text id="qg1q63"
00_release_manifest/
01_reference_markdown/
02_entity_enablement_indexes/
03_delegation_matrix/
04_obligation_delegation/
05_trace_coverage_registers/
06_rollup_indexes/
```

## 2.3

The current package, `08_assembler_skills/`, defines the skill layer that will use those packages.

## 2.4

It must therefore respect the existing canonical evidence base and must not redefine it.

---

# 2.5 Source Data Snapshot

The skills package vendors its required canonical source data under:

```text
08_assembler_skills/00_source_data/
```

This prevents the skills from depending on external workspace-specific paths.

---

# 3. Why Two Skills Are Required

## 3.1

The Assembler System knowledge base requires two different operational modes:

1. content editing and release maintenance,
2. read-only querying and trace explanation.

## 3.2

Combining both modes into one skill would create unnecessary risk.

## 3.3

Editing mode requires propagation, validation, and release discipline.

## 3.4

Query mode requires evidence-based answers, stable join paths, and strict no-new-semantics behavior.

## 3.5

Therefore, this release separates the two skills at the architectural level.

---

# 4. Skill 1: Assembler Canonical Content Editor Skill

## 4.1 Role

The Content Editor Skill is responsible for controlled canonical content maintenance.

## 4.2 It may:

1. classify canonical change requests,
2. identify affected files,
3. generate patch plans,
4. generate updated Markdown, CSV, and JSON content,
5. update manifests and counts when required,
6. update schemas where required,
7. produce release delta summaries,
8. preserve canonical ID grammar,
9. enforce propagation rules,
10. validate anti-collapse constraints.

## 4.3 It must not:

1. edit one canonical file without checking downstream effects,
2. introduce a new ID without registering it,
3. silently change row grains,
4. bypass trace coverage,
5. weaken anti-collapse rules,
6. let an adapter decide canonical semantics.

## 4.4 Governing rule

```text id="g2nvqv"
No direct edit without propagation.
```

## 4.5 Typical use

```text id="w8f75b"
Add a new governed artifact, determine all affected files, generate a patch plan, update required indexes, and produce validation notes.
```

---

# 5. Skill 2: Assembler Rollup Query Expert Skill

## 5.1 Role

The Query Expert Skill is responsible for read-only interrogation of the canonical knowledge base.

## 5.2 It may:

1. classify user questions,
2. route queries to the correct query family,
3. select join keys,
4. read rollup and trace files,
5. assemble evidence paths,
6. explain responsibility-to-entity mappings,
7. explain obligation enforcement,
8. explain gap closures,
9. explain contract derivations,
10. emit anti-collapse warnings,
11. report missing or weak evidence.

## 5.3 It must not:

1. edit source files,
2. invent responsibilities,
3. infer unregistered entities,
4. create new obligations,
5. collapse guarded distinctions,
6. answer canonical questions without evidence when evidence is required.

## 5.4 Governing rule

```text id="msovtt"
No new semantics. Only query, trace, explain, validate, and navigate.
```

## 5.5 Typical use

```text id="a2d3rg"
Trace RSP-CAN-027 and explain its delegated entity, obligation, governed object, enablement families, contracts, gaps, and anti-collapse rules.
```

---

# 6. Shared Canonical Kernel

## 6.1

Both skills depend on a shared canonical kernel.

## 6.2

The kernel provides the common rules that neither skill may violate.

## 6.3

It includes:

1. canonical ID grammar,
2. join key expectations,
3. source priority,
4. semantic authority hierarchy,
5. responsibility vs obligation distinction,
6. delegated entity vs governed object distinction,
7. enablement vs implementation distinction,
8. anti-collapse rules,
9. validation baseline,
10. traceability expectations.

## 6.4

The kernel is not itself a runtime executor.

## 6.5

The kernel is the shared governance substrate used by both skills.

---

# 7. Core / CLI / Adapter / Runtime Separation

## 7.1

The main architectural correction in this package is the explicit separation between:

1. Skill Core,
2. Canonical CLI Layer,
3. Environment Adapter Layer,
4. Runtime Environment.

## 7.2

The governing operating law is:

```text id="v22gdx"
Core decides.
CLI expresses.
Adapter executes.
Runtime hosts.
```

## 7.3

This means:

1. the core owns skill reasoning,
2. the CLI owns command grammar,
3. the adapter owns runtime translation,
4. the environment owns actual execution.

## 7.4

No adapter may become a semantic authority.

## 7.5

No runtime environment may redefine the Assembler System canon.

---

# 8. Why the CLI Layer Comes Before Adapters

## 8.1

The CLI layer is not one adapter among many.

## 8.2

It is the canonical operational interface between skill cores and runtime adapters.

## 8.3

It defines a shared command language such as:

```bash id="x62sdc"
assembler-query responsibility RSP-CAN-027
assembler-query gap G-006
assembler-query validate all
assembler-edit propose-change change_request.md
assembler-edit impact change_request.md
assembler-edit generate-patch change_request.md
assembler-edit validate-patch patch.json
```

## 8.4

Adapters then translate these command objects into environment-specific actions.

## 8.5

This prevents duplication of command semantics across Codex, Kilo Code, OpenCode, GitHub, Google Drive, and Local Runtime.

---

# 9. Runtime Adapters

## 9.1

Adapters provide execution bindings for specific environments.

## 9.2

The initial target adapters are:

1. Codex,
2. Kilo Code,
3. OpenCode,
4. GitHub,
5. Google Drive,
6. Local Runtime.

## 9.3

Each adapter must declare its capabilities before executing commands.

## 9.4

Capabilities may include:

1. read files,
2. write files,
3. list files,
4. search files,
5. apply patches,
6. generate diffs,
7. run validations,
8. create branches,
9. create pull requests,
10. export artifacts,
11. report limitations.

## 9.5

An adapter that cannot write must declare itself read-only.

## 9.6

An adapter that cannot validate must report validation as unsupported rather than pretending success.

---

# 10. Supported Target Environments

## 10.1 Codex

Codex is treated as a repository-aware coding and patch execution environment.

Expected support includes:

1. repository file reading,
2. patch generation,
3. diff review,
4. validation commands,
5. branch or pull request workflows.

## 10.2 Kilo Code

Kilo Code is treated as a workspace-aware coding assistant environment.

Expected support includes:

1. workspace discovery,
2. structured editing,
3. local patching,
4. validation feedback,
5. diff presentation.

## 10.3 OpenCode

OpenCode is treated as a terminal and local workspace-oriented agent environment.

Expected support includes:

1. filesystem access,
2. shell execution,
3. validation scripts,
4. local diffs,
5. packaging workflows.

## 10.4 GitHub

GitHub is treated as a repository and review integration environment.

Expected support includes:

1. reading repository files,
2. creating branches,
3. committing changes,
4. opening pull requests,
5. reporting review summaries.

## 10.5 Google Drive

Google Drive is treated as a Drive-backed document, sheet, slide, and file environment.

Expected support includes:

1. searching Drive files,
2. reading Docs,
3. reading Sheets,
4. exporting content,
5. applying structured updates where supported.

## 10.6 Local Runtime

Local Runtime is treated as a plain filesystem and CLI environment.

Expected support includes:

1. local file reads,
2. local file writes,
3. local validation,
4. artifact export,
5. direct CLI execution.

---

# 11. Package Structure

## 11.1

The package is organized as:

```text id="g2k7yr"
08_assembler_skills/
│
├── 00_SOURCE_DATA_INTEGRATION_DECISION.md
├── 00_PACKAGE_MANIFEST.json
├── 01_SKILLS_RELEASE_README.md
├── 02_SKILLS_ARCHITECTURE_OVERVIEW.md
├── 03_SKILLS_FILE_MAP.csv
├── 04_SKILLS_SCHEMA.md
│
├── 00_source_data/
│   ├── 00.00_SOURCE_DATA_MANIFEST.json
│   ├── 00.01_SOURCE_DATA_README.md
│   ├── 00.02_SOURCE_DATA_FILE_MAP.csv
│   ├── 00.03_SOURCE_DATA_REFRESH_POLICY.md
│   │
│   ├── 00.01_architectural_taxonomy/
│   ├── 00.02_canonical_responsibilities/
│   └── 00.03_delegation_enablement_matrix/
│
├── 00_shared_canonical_kernel/
│   ├── 00.01_CANONICAL_KERNEL.md
│   ├── 00.02_ID_GRAMMAR_AND_JOIN_KEYS.md
│   ├── 00.03_SOURCE_PRIORITY_AND_AUTHORITY.md
│   ├── 00.04_ANTI_COLLAPSE_RULES.md
│   └── 00.05_VALIDATION_BASELINE.md
│
├── 01_content_editor_skill/
│   ├── 01.00_CONTENT_EDITOR_SKILL_MANIFEST.json
│   ├── core/
│   ├── cli/
│   └── integrations/
│
├── 02_query_expert_skill/
│   ├── 02.00_QUERY_EXPERT_SKILL_MANIFEST.json
│   ├── core/
│   ├── cli/
│   └── integrations/
│
└── 03_execution_contracts/
```

---

# 11.2 Path Alias Policy

The package uses canonical aliases to avoid long repeated paths:

```text
SOURCE_DATA_ROOT = 08_assembler_skills/00_source_data/
DELEGATION_SOURCE_ROOT = ${SOURCE_DATA_ROOT}/00.03_delegation_enablement_matrix/
```

All skill references to canonical source material must resolve through these aliases, not external workspace paths.

---

# 12. File Groups

## 12.1 Top-Level Files

The top-level files define package-level purpose, architecture, file map, and schema:

```text id="r1kcfm"
00_PACKAGE_MANIFEST.json
01_SKILLS_RELEASE_README.md
02_SKILLS_ARCHITECTURE_OVERVIEW.md
03_SKILLS_FILE_MAP.csv
04_SKILLS_SCHEMA.md
```

## 12.2 Shared Kernel Files

The shared kernel files define canonical rules used by both skills:

```text id="fr48y2"
00_shared_canonical_kernel/00.01_CANONICAL_KERNEL.md
00_shared_canonical_kernel/00.02_ID_GRAMMAR_AND_JOIN_KEYS.md
00_shared_canonical_kernel/00.03_SOURCE_PRIORITY_AND_AUTHORITY.md
00_shared_canonical_kernel/00.04_ANTI_COLLAPSE_RULES.md
00_shared_canonical_kernel/00.05_VALIDATION_BASELINE.md
```

## 12.3 Content Editor Files

The Content Editor Skill files define:

1. editor skill manifest,
2. editor core behavior,
3. change classification,
4. impact analysis,
5. patch generation,
6. propagation rules,
7. editor CLI,
8. editor adapters.

## 12.4 Query Expert Files

The Query Expert Skill files define:

1. query skill manifest,
2. query core behavior,
3. query routing,
4. join and trace protocol,
5. evidence output,
6. answer guards,
7. query CLI,
8. query adapters.

## 12.5 Execution Contract Files

The execution contract files define:

1. core-to-CLI contract,
2. shared CLI command grammar,
3. CLI-to-adapter contract,
4. adapter capability matrix,
5. adapter lifecycle,
6. error and limitation model,
7. integration validation protocol.

---

# 13. Relationship to the Canonical Knowledge Base

## 13.1

Package `08_assembler_skills/` depends on vendored snapshots of the canonical knowledge base but does not replace it.

## 13.2

The semantic evidence base remains:

```text id="kbpqlg"
01_reference_markdown/
02_entity_enablement_indexes/
03_delegation_matrix/
04_obligation_delegation/
05_trace_coverage_registers/
06_rollup_indexes/
```

## 13.3

Package `08` defines how skills operate over vendored snapshots of that evidence base.

## 13.4

The query skill primarily depends on vendored copies under:

```text id="dw2l60"
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.01_DELEGATION_ENABLEMENT_ROLLUP_INDEX.json
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.02_JOIN_KEYS_REFERENCE.csv
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.03_QUERY_PATTERNS.md
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.04_CROSS_BUNDLE_FILE_MAP.csv
${DELEGATION_SOURCE_ROOT}/06_rollup_indexes/06.05_ROLLUP_SCHEMA.md
```

## 13.5

The editor skill additionally depends on vendored source snapshots that must be updated during canonical propagation.

---

# 14. Non-Canonical Behaviors

## 14.1

The package is non-canonical if it allows a skill core to depend directly on a runtime-specific API.

## 14.2

The package is non-canonical if it allows an adapter to decide semantic meaning.

## 14.3

The package is non-canonical if it treats the CLI as merely one adapter among many.

## 14.4

The package is non-canonical if the query skill edits source files.

## 14.5

The package is non-canonical if the editor skill emits edits without propagation analysis.

## 14.6

The package is non-canonical if evidence-required query answers omit source paths.

## 14.7

The package is non-canonical if runtime limitations are hidden.

## 14.8

The package is non-canonical if it requires hardcoded external workspace paths for canonical source data.

---

# 15. Core Anti-Collapse Rules Inherited by the Skills

## 15.1

Both skills must preserve the following inherited rules:

1. `Metadata Injector` is not a policy host.
2. `Queue Runtime Layer` is classification-only.
3. `Delivery-Cycle Flag Set` is not `Dispatcher Feedback Report`.
4. `Queue = Container`.
5. Waiting lists store `Queue Container Identifier`, not `Log Level Envelope`.
6. `Envelope Slot Occupancy` is binding/state only, not envelope lifecycle ownership.
7. `Registry / Delivery Port` does not replace `Dispatcher`.
8. Typed/template contracts are not runtime COM interfaces.

## 15.2

The Content Editor Skill must validate edits against these rules.

## 15.3

The Query Expert Skill must warn when a user question risks violating these rules.

---

# 16. Release Counts

## 16.1

The planned package contains:

```text id="mkb3ra"
planned_total_file_count = 49
planned_top_level_files_count = 5
planned_shared_kernel_file_count = 5
planned_content_editor_skill_files_count = 17
planned_query_expert_skill_files_count = 17
planned_execution_contract_files_count = 7
```

## 16.2

The planned format counts are:

```text id="oddujo"
planned_json_file_count = 3
planned_csv_file_count = 2
planned_markdown_file_count = 44
```

## 16.3

The planned adapter count is:

```text id="cknj8j"
editor_adapter_spec_count = 6
query_adapter_spec_count = 6
total_adapter_spec_count = 12
```

---

# 17. Delivery Method

## 17.1

This release is intended to be delivered file-by-file.

## 17.2

Each file should be copied into the declared filesystem path.

## 17.3

The delivery order should follow the phases declared in:

```text id="m0wg6n"
08_assembler_skills/00_PACKAGE_MANIFEST.json
```

## 17.4

The preferred delivery sequence starts with:

```text id="n3qqxy"
08_assembler_skills/00_SOURCE_DATA_INTEGRATION_DECISION.md
08_assembler_skills/00_PACKAGE_MANIFEST.json
08_assembler_skills/01_SKILLS_RELEASE_README.md
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
08_assembler_skills/03_SKILLS_FILE_MAP.csv
08_assembler_skills/04_SKILLS_SCHEMA.md
08_assembler_skills/00_source_data/00.00_SOURCE_DATA_MANIFEST.json
```

---

# 18. Validation Expectations

## 18.1

A valid installation must confirm:

1. all planned files are present,
2. all file paths match the manifest,
3. the shared kernel is present before either skill is considered complete,
4. both skill manifests are present,
5. CLI files exist for both skills,
6. adapter specs exist for all declared target environments,
7. execution contracts are present,
8. validation rules are not contradicted.

## 18.2

A valid skill output must confirm:

1. whether it is edit-mode or query-mode,
2. which files it uses,
3. which evidence path supports the output,
4. which limitations apply,
5. which anti-collapse rules were checked.

---

# 19. Expected Future Uses

## 19.1

This package prepares future implementation of:

1. a local query CLI,
2. a local editor CLI,
3. Codex-based repository editing,
4. Kilo Code workspace workflows,
5. OpenCode terminal workflows,
6. GitHub pull request workflows,
7. Google Drive-backed documentation workflows,
8. ontology expert-skill behavior,
9. PostgreSQL-backed query execution,
10. graph-backed query execution.

## 19.2

It is a specification package, not an implementation package.

---

# 20. Final Canonical Statement

## 20.1

The `08_assembler_skills/` package defines how two portable skills operate over the Assembler System canonical knowledge base.

## 20.2

It separates:

1. shared canonical governance,
2. skill reasoning,
3. command expression,
4. runtime adaptation,
5. execution hosting.

## 20.3

Its governing law is:

```text id="e0pjkh"
Core decides. CLI expresses. Adapter executes. Runtime hosts.
```

## 20.4

It introduces no new Assembler System canon.

## 20.5

It enables safe maintenance and faithful querying of the canon across multiple future environments.


