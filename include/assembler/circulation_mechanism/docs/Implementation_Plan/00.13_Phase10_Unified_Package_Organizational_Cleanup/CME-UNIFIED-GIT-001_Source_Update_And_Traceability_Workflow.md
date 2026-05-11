# CME-UNIFIED-GIT-001 Source Update And Traceability Workflow

## Purpose

This document defines the Git-facing update workflow for synchronizing the unified local package with the external implementation-wave source packages without modifying those external source packages.

## Local Target

Canonical local target:

`include/assembler/circulation_mechanism`

## External Source Root

Current external source root:

`C:\Users\Ahmed\Downloads\Circulation_Mechanism_Engine\Implmentatoin_Waves\Implementation_Phases\Phase10_Hardening`

## Tracking Artifacts

The following artifacts must be maintained for every refresh cycle:

1. Unified package content under the local target.
2. A source map that records the originating wave and source file for each unified relative path.
3. A cleanup report that records structural duplication findings and cleanup decisions.

## Mandatory Rules

1. External source packages are read-only.
2. Unified local content is the only writable merge target inside this repository.
3. Every refresh must preserve `docs/`.
4. `_Archived/` remains ignored and excluded from merge inputs unless explicitly requested.
5. Temporary merge workspaces must remain outside the tracked package tree.

## Refresh Workflow

1. Read the external root-level waves in numeric order.
2. Treat `00.01` as the first code baseline unless a newer governance document replaces that rule.
3. Apply each later wave as a delta over the baseline.
4. Preserve non-overridden additions from intermediate waves.
5. Rebuild the unified source map.
6. Copy the refreshed unified result into the local target.
7. Run syntax-only compile checks against the root aggregate and the subsystem aggregates.
8. Review Git diff only for:
   - `include/assembler/circulation_mechanism`
   - `.gitignore`
   - `.gitattributes`
   - tracking docs in this directory

## Git Scope Discipline

Use path-scoped Git commands during refresh and review:

```powershell
git status --short -- .gitignore .gitattributes include/assembler/circulation_mechanism
git diff -- .gitignore .gitattributes include/assembler/circulation_mechanism
git add -- .gitignore .gitattributes include/assembler/circulation_mechanism
```

This prevents unrelated repository noise from being mixed into the circulation-mechanism update set.

## Source Map Requirement

The source map must contain:

- `relative_path`
- `source_wave`
- `source_file`

This makes each unified file traceable back to its exact external origin.

## Cleanup Boundary

Structural cleanup inside the unified package must happen in a separate logical step after:

1. the source refresh is complete,
2. the source map is updated,
3. the refreshed package is staged or at least diff-reviewed.

This keeps merge provenance separate from local cleanup decisions.

## Current Baseline

At the time of writing:

- the unified package has already been copied into the local target,
- the organizational cleanup report exists,
- Git long path support is enabled locally,
- the source map exists in the temporary merge workspace and should be mirrored into tracked docs for repository-local traceability.
