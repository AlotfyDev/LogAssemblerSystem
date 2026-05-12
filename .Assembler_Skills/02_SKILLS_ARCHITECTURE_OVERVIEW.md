FILE:
`08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md`

CONTENT:

````markdown id="k7p3m9"
# Skills Architecture Overview
## Assembler Skills Architecture Pack V1

---

# 0. Document Identity

## 0.1 File Path

```text
08_assembler_skills/02_SKILLS_ARCHITECTURE_OVERVIEW.md
````

## 0.2 Package

```text
08_assembler_skills/
```

## 0.3 Document Type

```text
architecture_overview
```

## 0.4 Status

```text
draft_for_structured_local_installation
```

---

# 1. Purpose

## 1.1

This document defines the architecture of the Assembler Skills layer.

## 1.2

The skills layer is not part of the Assembler runtime.

## 1.3

It is a meta-operational layer that allows controlled interaction with the Assembler System canonical knowledge base.

## 1.4

The architecture separates:

1. shared canonical governance,
2. skill reasoning,
3. canonical command expression,
4. runtime-specific execution,
5. external hosting environment.

## 1.5

The governing operating law is:

```text id="cv4yyn"
Core decides.
CLI expresses.
Adapter executes.
Runtime hosts.
```

---

# 2. Architectural Problem

## 2.1

The Assembler System canon now includes:

1. responsibility matrices,
2. obligation delegation matrices,
3. entity and enablement indexes,
4. governed object indexes,
5. contract traces,
6. gap closure coverage,
7. taxonomy updates,
8. rollup indexes,
9. query patterns,
10. cross-bundle file maps.

## 2.2

This creates two distinct operational needs.

### 2.2.1 Content Maintenance Need

The first need is controlled editing.

This includes:

1. updating canonical files,
2. adding or modifying responsibilities,
3. updating obligations,
4. propagating changes across indexes,
5. maintaining counts,
6. updating schemas,
7. validating anti-collapse rules,
8. producing release deltas.

### 2.2.2 Query and Trace Need

The second need is read-only knowledge access.

This includes:

1. answering responsibility questions,
2. tracing obligation enforcement,
3. explaining gap closures,
4. resolving contract derivations,
5. finding entity responsibility loads,
6. navigating rollup indexes,
7. returning source evidence,
8. detecting semantic collapse risks.

## 2.3

These two needs should not be handled by one undifferentiated skill.

## 2.4

A skill that can both freely edit and freely answer would risk:

1. confusing read-only answers with edit proposals,
2. inventing missing semantics,
3. treating inferred content as canonical,
4. bypassing propagation,
5. weakening evidence requirements,
6. allowing runtime adapters to make architectural decisions.

---

# 3. Architectural Solution

## 3.1

The solution is a two-skill architecture with one shared kernel.

## 3.2

The two skills are:

1. `Assembler Canonical Content Editor Skill`,
2. `Assembler Rollup Query Expert Skill`.

## 3.3

Both skills depend on:

```text id="teg487"
Shared Canonical Kernel
```

## 3.4

Both skills expose their operations through a canonical CLI layer.

## 3.5

Both skills are executed in target environments through adapters.

## 3.6

The architecture therefore follows this order:

```text id="jad8qh"
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

---

# 4. Layer 0: Source Data Snapshot

## 4.1 Definition

The Source Data Snapshot is the vendored local copy of upstream canonical sources required by the skills.

## 4.2 It provides:

1. vendored canonical reference Markdown,
2. vendored entity and enablement indexes,
3. vendored delegation matrices,
4. vendored obligation delegation files,
5. vendored trace coverage registers,
6. vendored rollup indexes,
7. source manifests tracking upstream origins.

## 4.3 It enables portability

Skills operate over the snapshot, not external workspace paths.

## 4.4 It supports controlled refresh

The snapshot can be updated from upstream sources through defined refresh workflows.

---

# 5. Layer 1: Shared Canonical Kernel

## 5.1 Definition

The Shared Canonical Kernel is the common governance substrate used by both skills.

## 4.2 It defines:

1. canonical ID grammar,
2. join-key rules,
3. source priority,
4. semantic authority,
5. responsibility vs obligation distinction,
6. delegated entity vs governed object distinction,
7. entity vs surface vs port distinction,
8. enablement vs implementation distinction,
9. anti-collapse rules,
10. validation baseline.

## 4.3 It is shared because both skills must preserve the same canon.

## 4.4 The kernel does not execute editing or querying by itself.

## 4.5 The kernel is not a runtime adapter.

## 4.6 The kernel is not an implementation library in this release.

## 4.7 It is a specification and governance layer.

---

# 5. Layer 2: Skill Core

## 5.1 Definition

A Skill Core is the environment-independent reasoning layer for one skill.

## 5.2

A Skill Core knows the canonical model.

## 5.3

A Skill Core does not know the runtime environment.

## 5.4

A Skill Core must not contain assumptions about:

1. Codex,
2. Kilo Code,
3. OpenCode,
4. GitHub,
5. Google Drive,
6. Local Runtime,
7. future execution environments.

---

## 5.5 Content Editor Core

### 5.5.1

The Content Editor Core owns authoring and release-maintenance logic.

### 5.5.2

It performs:

1. change classification,
2. impact analysis,
3. affected file discovery,
4. patch planning,
5. patch generation,
6. propagation validation,
7. release delta generation,
8. anti-collapse validation.

### 5.5.3

It may propose canonical edits.

### 5.5.4

It must not directly execute those edits against a runtime.

### 5.5.5

Its governing rule is:

```text id="rttxmk"
No direct edit without propagation.
```

---

## 5.6 Query Expert Core

### 5.6.1

The Query Expert Core owns read-only query and trace reasoning.

### 5.6.2

It performs:

1. query classification,
2. query-family routing,
3. join-key selection,
4. trace path planning,
5. evidence requirement checks,
6. answer shape selection,
7. anti-collapse warning generation,
8. validation of answer sufficiency.

### 5.6.3

It may explain canonical records.

### 5.6.4

It must not modify canonical records.

### 5.6.5

Its governing rule is:

```text id="m83p0k"
No new semantics. Only query, trace, explain, validate, and navigate.
```

---

# 6. Layer 3: Canonical CLI Layer

## 6.1 Definition

The Canonical CLI Layer is the shared operational interface between Skill Cores and Environment Adapters.

## 6.2

The CLI layer is not one adapter among many.

## 6.3

It is a canonical command grammar.

## 6.4

The architecture therefore follows this order:

```text id="jad8qh"
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

---

## 6.9 Editor CLI Examples

```bash id="o5y0xg"
assembler-edit propose-change change_request.md
assembler-edit impact change_request.md
assembler-edit generate-patch change_request.md
assembler-edit validate-patch patch.json
assembler-edit apply-patch patch.json
assembler-edit release-delta patch.json
assembler-edit update-manifests patch.json
assembler-edit export-review-bundle patch.json
```

## 6.10 Query CLI Examples

```bash id="zyr5gn"
assembler-query responsibility RSP-CAN-027
assembler-query obligation OBL-CAN-025
assembler-query entity E-INT-002
assembler-query object BCO-014
assembler-query enablement EN-FAM-004
assembler-query gap G-006
assembler-query contract CC-REG-002
assembler-query guard GUARD-003
assembler-query validate all
assembler-query ontology seeds
```

---

# 7. Layer 4: Environment Adapter Layer

## 7.1 Definition

The Environment Adapter Layer binds the canonical CLI command model to a specific runtime environment.

## 7.2

An adapter knows how to execute in its environment.

## 7.3

An adapter does not own canonical semantics.

## 7.4

An adapter may provide capabilities such as:

1. reading files,
2. writing files,
3. listing files,
4. searching files,
5. applying patches,
6. generating diffs,
7. running validations,
8. creating branches,
9. opening pull requests,
10. exporting artifacts,
11. reporting unsupported operations.

## 7.5

Before execution, an adapter must declare its capabilities.

## 7.6

If an adapter is read-only, it must say so.

## 7.7

If an adapter cannot validate, it must not claim validation success.

## 7.8

If an adapter cannot write, it must not pretend to apply a patch.

---

# 8. Layer 5: Runtime Environment

## 8.1 Definition

The Runtime Environment is the external place where execution happens.

## 8.2 Examples include:

1. Codex repository environment,
2. Kilo Code workspace,
3. OpenCode terminal workspace,
4. GitHub repository,
5. Google Drive folder or document set,
6. local filesystem.

## 8.3

The runtime may host files and execute commands.

## 8.4

The runtime may expose repository, filesystem, Drive, or workspace APIs.

## 8.5

The runtime is not a semantic authority.

## 8.6

If runtime content contradicts the canonical source hierarchy, the conflict must be surfaced and not silently resolved.

---

# 9. Complete Layer Model

## 9.1 Abstract Model

```text id="co2dkq"
+---------------------------------------------------+
| Runtime Environment                               |
| Codex / Kilo Code / OpenCode / GitHub / Drive     |
+---------------------------------------------------+
                          ↑
+---------------------------------------------------+
| Environment Adapter Layer                         |
| Executes commands using runtime-specific APIs      |
+---------------------------------------------------+
                          ↑
+---------------------------------------------------+
| Canonical CLI Layer                               |
| Stable command grammar and command I/O contracts   |
+---------------------------------------------------+
                          ↑
+---------------------------------------------------+
| Skill Core                                        |
| Editor Core or Query Core                          |
+---------------------------------------------------+
                          ↑
+---------------------------------------------------+
| Shared Canonical Kernel                            |
| ID grammar, authority, anti-collapse, validation   |
+---------------------------------------------------+
                          ↑
+---------------------------------------------------+
| Source Data Snapshot                               |
| Vendored canonical source files                    |
+---------------------------------------------------+
```

## 9.2 Dependency Direction

### 9.2.1

Upper execution layers depend downward for semantic rules.

### 9.2.2

Lower semantic layers must not depend upward on runtime details.

### 9.2.3

The dependency rule is:

```text id="mqace7"
Kernel ← Core ← CLI ← Adapter ← Runtime
```

### 9.2.4

The forbidden dependency is:

```text id="fg6j6x"
Kernel depends on Adapter
Core depends on Runtime
Core depends on external sibling workspace paths
Adapter silently rewrites source paths without source-data manifest
CLI depends on Codex-specific APIs
Adapter decides canonical meaning
Runtime mutates semantics
Runtime mutates vendored source data without refresh policy
```

---

# 10. Skill Interaction Model

## 10.1 Content Editing Flow

```text id="mgui5v"
User Change Request
        ↓
Content Editor Core
        ↓
Change Classification
        ↓
Impact Analysis
        ↓
Patch Plan
        ↓
Editor CLI Command Object
        ↓
Environment Adapter
        ↓
Runtime Execution
        ↓
Validation Report
        ↓
Review Bundle
```

## 10.2 Query Flow

```text id="tt40cn"
User Query
        ↓
Query Expert Core
        ↓
Query Classification
        ↓
Query Family Routing
        ↓
Join / Trace Plan
        ↓
Query CLI Command Object
        ↓
Environment Adapter
        ↓
Runtime File Access
        ↓
Evidence Records
        ↓
Guarded Answer
```

## 10.3 Editing Flow Rule

The editing flow must always produce:

1. change classification,
2. affected files,
3. propagation plan,
4. generated patch or proposed patch,
5. validation checklist,
6. review summary.

## 10.4 Query Flow Rule

The query flow must always produce:

1. direct answer,
2. evidence path,
3. joined records or IDs,
4. confidence or sufficiency assessment,
5. anti-collapse warnings when relevant.

---

# 11. The Two Skills Compared

| Dimension             | Content Editor Skill                                          | Query Expert Skill             |
| --------------------- | ------------------------------------------------------------- | ------------------------------ |
| Mode                  | Authoring and maintenance                                     | Read-only query and trace      |
| Can edit files?       | Yes, through propagation and validation                       | No                             |
| Can answer questions? | Only as part of edit context                                  | Yes                            |
| Can invent semantics? | No; may propose governed additions through formal change flow | No                             |
| Uses CLI?             | `assembler-edit`                                              | `assembler-query`              |
| Primary risk          | Unpropagated change                                           | Unsupported inference          |
| Required evidence     | Affected-file and validation evidence                         | Source-path and trace evidence |
| Output type           | Patch plan / patch / release delta                            | Answer / trace / evidence path |
| Runtime binding       | Through editor adapters                                       | Through query adapters         |

---

# 12. Adapter Target Environments

## 12.1 Codex Adapter

### 12.1.1

Codex is treated as repository-aware.

### 12.1.2

Expected capabilities:

1. read repository files,
2. create patches,
3. generate diffs,
4. run validations,
5. prepare branch or PR summaries.

### 12.1.3

Codex must not decide canonical semantics.

---

## 12.2 Kilo Code Adapter

### 12.2.1

Kilo Code is treated as workspace-aware.

### 12.2.2

Expected capabilities:

1. discover workspace files,
2. perform structured edits,
3. present diffs,
4. run available validation commands,
5. report workspace limitations.

### 12.2.3

Kilo Code must not decide canonical semantics.

---

## 12.3 OpenCode Adapter

### 12.3.1

OpenCode is treated as terminal and filesystem-oriented.

### 12.3.2

Expected capabilities:

1. read local filesystem,
2. write local files,
3. run shell validations,
4. generate diffs,
5. package outputs.

### 12.3.3

OpenCode must not decide canonical semantics.

---

## 12.4 GitHub Adapter

### 12.4.1

GitHub is treated as repository and review workflow environment.

### 12.4.2

Expected capabilities:

1. fetch repository files,
2. create branches,
3. commit changes,
4. open pull requests,
5. add review summaries,
6. report CI or validation state.

### 12.4.3

GitHub must not decide canonical semantics.

---

## 12.5 Google Drive Adapter

### 12.5.1

Google Drive is treated as document, sheet, slide, and file environment.

### 12.5.2

Expected capabilities:

1. search files,
2. fetch Docs,
3. fetch Sheets,
4. export files,
5. update structured content where supported,
6. report unsupported edit operations.

### 12.5.3

Google Drive must not decide canonical semantics.

---

## 12.6 Local Runtime Adapter

### 12.6.1

Local Runtime is treated as plain filesystem and command execution environment.

### 12.6.2

Expected capabilities:

1. read local files,
2. write local files,
3. run local validation,
4. generate local diffs,
5. export artifacts.

### 12.6.3

Local Runtime must not decide canonical semantics.

---

# 13. Source Authority Model

## 13.1

Package `08_assembler_skills/` depends on the canonical knowledge base.

## 13.2

It does not replace it.

## 13.3

The main semantic evidence base remains:

```text id="j9v5u7"
01_reference_markdown/
02_entity_enablement_indexes/
03_delegation_matrix/
04_obligation_delegation/
05_trace_coverage_registers/
06_rollup_indexes/
```

## 13.4

The Query Expert Skill primarily uses package `06_rollup_indexes/`.

## 13.5

The Content Editor Skill uses the full source stack because edits may need propagation across all packages.

## 13.6

If package `08` contradicts packages `01` through `06`, package `08` must be corrected.

---

# 14. Canonical Knowledge Access Modes

## 14.1 Read Mode

Read Mode is used by the Query Expert Skill.

It permits:

1. lookup,
2. trace,
3. join,
4. explain,
5. validate,
6. warn.

It forbids:

1. edit,
2. promotion,
3. new ID creation,
4. semantic invention.

## 14.2 Edit Mode

Edit Mode is used by the Content Editor Skill.

It permits:

1. proposed changes,
2. controlled new records,
3. patch generation,
4. propagation,
5. manifest updates,
6. schema updates,
7. release delta generation.

It forbids:

1. silent single-file edits,
2. unregistered IDs,
3. untraced changes,
4. adapter-defined semantics,
5. unvalidated release output.

---

# 15. Canonical CLI Position

## 15.1

The CLI layer sits after the Skill Core and before the Adapter Layer.

## 15.2

This is deliberate.

## 15.3

The CLI layer:

1. standardizes operations,
2. preserves command vocabulary,
3. enables local execution,
4. supports adapter portability,
5. prevents duplicated semantics across adapters,
6. makes command behavior testable.

## 15.4

The CLI layer must be documented independently for both skills.

## 15.5

The CLI layer is the operational contract.

## 15.6

The adapter layer is the runtime binding.

---

# 16. Command Object Model

## 16.1

The CLI layer may be represented as shell commands or as structured command objects.

## 16.2

A shell-like editor command:

```bash id="asfo21"
assembler-edit generate-patch change_request.md --format json
```

## 16.3

May correspond to a structured command object:

```json id="vjf8g2"
{
  "command_family": "assembler-edit",
  "command_name": "generate-patch",
  "input": {
    "change_request_path": "change_request.md",
    "format": "json"
  },
  "execution_constraints": {
    "require_impact_analysis": true,
    "require_propagation_plan": true,
    "require_validation": true
  }
}
```

## 16.4

A shell-like query command:

```bash id="e7b28z"
assembler-query gap G-006 --evidence --format markdown
```

## 16.5

May correspond to:

```json id="zex8cb"
{
  "command_family": "assembler-query",
  "command_name": "gap",
  "input": {
    "gap_id": "G-006",
    "evidence_required": true,
    "format": "markdown"
  },
  "execution_constraints": {
    "read_only": true,
    "anti_collapse_check": true
  }
}
```

---

# 17. Adapter Capability Model

## 17.1

Adapters must declare what they can do.

## 17.2

Capability categories include:

1. `read_file`,
2. `write_file`,
3. `list_files`,
4. `search_files`,
5. `apply_patch`,
6. `generate_diff`,
7. `run_validation`,
8. `create_branch`,
9. `create_pull_request`,
10. `export_artifact`,
11. `read_comments`,
12. `write_comments`.

## 17.3

A command may be executable in one environment and unsupported in another.

## 17.4

Unsupported operations must be reported explicitly.

## 17.5

Capability failure must not be treated as semantic failure.

---

# 18. Error and Limitation Model

## 18.1

Errors should be classified by layer.

## 18.2 Kernel Errors

Examples:

1. invalid ID grammar,
2. missing source priority,
3. anti-collapse violation.

## 18.3 Core Errors

Examples:

1. unclassified change request,
2. unresolved query family,
3. missing propagation path,
4. insufficient evidence.

## 18.4 CLI Errors

Examples:

1. invalid command grammar,
2. missing required argument,
3. unsupported output format.

## 18.5 Adapter Errors

Examples:

1. missing file capability,
2. write not supported,
3. validation command unavailable,
4. repository permission failure,
5. Drive export failure.

## 18.6 Runtime Errors

Examples:

1. file not found,
2. branch conflict,
3. network failure,
4. document permission denied,
5. local process failure.

---

# 19. Validation Model

## 19.1

Validation must occur at multiple layers.

## 19.2 Kernel Validation

Checks:

1. ID grammar,
2. source priority,
3. anti-collapse rules,
4. canonical distinction rules.

## 19.3 Core Validation

Checks:

1. change classification,
2. query routing,
3. propagation sufficiency,
4. evidence sufficiency,
5. output completeness.

## 19.4 CLI Validation

Checks:

1. command grammar,
2. argument completeness,
3. operation constraints,
4. output format.

## 19.5 Adapter Validation

Checks:

1. declared capabilities,
2. runtime permissions,
3. command mapping,
4. execution result integrity.

## 19.6 Runtime Validation

Checks:

1. file existence,
2. successful write,
3. successful patch,
4. successful command execution,
5. exported artifact availability.

---

# 20. Anti-Collapse Rules Shared by the Architecture

## 20.1

Both skills must preserve the following canonical distinctions.

## 20.2 Metadata Injector Rule

```text id="i5dycq"
Metadata Injector is schema/directive-governed.
It is not a policy host.
```

## 20.3 Queue Runtime Layer Rule

```text id="za4d0q"
Queue Runtime Layer is classification-only.
Actual responsibility carriers are Queue Bundle Agent, Single Queue Moderator, and round managers.
```

## 20.4 Flag / Report Rule

```text id="oh2mwb"
Delivery-Cycle Flag Set and Dispatcher Feedback Report are distinct governed artifacts.
```

## 20.5 Queue-as-Container Rule

```text id="fj2urx"
Queue equals Container.
No separate runtime container is introduced above Queue Container.
```

## 20.6 Waiting List Locator Rule

```text id="lo6k96"
Waiting lists store Queue Container Identifiers, not Log Level Envelopes.
```

## 20.7 Occupancy / Lifecycle Rule

```text id="rptk84"
Envelope Slot Occupancy is binding/state only.
It is not Log Level Envelope lifecycle ownership.
```

## 20.8 Registry Port / Dispatcher Rule

```text id="iu1rsd"
Registry / Delivery Port is a contract surface.
Dispatcher remains the final assembler-side outbound actor.
```

## 20.9 Contract Template Rule

```text id="grh1yu"
Typed/template contracts are not runtime COM interfaces.
```

---

# 21. Architecture Invariants

## 21.1 Invariant 1

```text id="rl769y"
The Query Expert Skill is read-only.
```

## 21.2 Invariant 2

```text id="s3f1oe"
The Content Editor Skill cannot emit canonical edits without propagation analysis.
```

## 21.3 Invariant 3

```text id="n8f1qi"
The CLI layer is not an adapter.
```

## 21.4 Invariant 4

```text id="ftb3lb"
Adapters do not decide canonical semantics.
```

## 21.5 Invariant 5

```text id="hb0h6q"
Runtime environments do not redefine the canon.
```

## 21.6 Invariant 6

```text id="wd1spz"
Package 08 depends on packages 01 through 06 for semantic authority.
```

## 21.7 Invariant 7

```text id="kih8jr"
All evidence-required answers must include evidence paths.
```

## 21.8 Invariant 8

```text id="g9yzh0"
All canonical edits must preserve or update traceability.
```

---

# 22. Implementation Readiness

## 22.1

This package is not implementation code.

## 22.2

However, it prepares implementation of:

1. local CLI tools,
2. repository-based editing workflows,
3. read-only query workflows,
4. runtime adapter test harnesses,
5. GitHub pull-request workflows,
6. Google Drive document workflows,
7. PostgreSQL-backed query systems,
8. graph-backed query systems,
9. ontology expert skill behavior.

## 22.3

Implementation should begin from the contracts in:

```text id="l6j4xt"
08_assembler_skills/03_execution_contracts/
```

## 22.4

Implementation should begin from:

```text
00_source_data/
00_shared_canonical_kernel/
03_execution_contracts/
```

not from external workspace paths.

## 22.5

Implementation should not begin by hardcoding adapter behavior into the core.

---

# 23. Final Architecture Statement

## 23.1

The Assembler Skills architecture creates two portable skills over the canonical knowledge base.

## 23.2

It separates content editing from read-only querying.

## 23.3

It separates semantic reasoning from runtime execution.

## 23.4

It places the canonical CLI layer before adapters so all environments share the same command model.

## 23.5

It prevents adapters and runtimes from becoming semantic authorities.

## 23.6

Its governing law is now:

```text id="lhk0cm"
Source data is vendored. Kernel governs. Core reasons. CLI expresses. Adapter executes. Runtime hosts.
```

## 23.7

Any future implementation must preserve this layer order to remain canonical.


