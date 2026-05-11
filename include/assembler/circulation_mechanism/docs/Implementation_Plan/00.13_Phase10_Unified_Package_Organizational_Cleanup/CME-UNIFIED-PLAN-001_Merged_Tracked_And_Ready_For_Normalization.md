# CME-UNIFIED-PLAN-001 Merged Tracked And Ready For Normalization

## Purpose

This document defines the formal execution plan for closing the unified-package creation phase and establishing the package as:

`merged, tracked, and ready for normalization`

It is the execution reference for the next phase.

## Target State

The target state is reached only when the unified package is:

1. merged from the external implementation-wave source packages,
2. traceable back to those source packages,
3. staged and reviewable in Git with minimal repository noise,
4. compile-sane at the aggregate-header level,
5. documented well enough to begin structural normalization safely.

## Scope

In scope:

- `include/assembler/circulation_mechanism`
- traceability artifacts under `docs/Implementation_Plan`
- Git preparation for path-scoped review and update
- pre-normalization organizational verification

Out of scope:

- structural cleanup implementation
- semantic refactoring of duplicated types
- aggregate-header redesign
- behavior changes

## Source Of Truth

### External Source Root

`C:\Users\Ahmed\Downloads\Circulation_Mechanism_Engine\Implmentatoin_Waves\Implementation_Phases\Phase10_Hardening`

### External Ordering Rule

All source waves must be processed according to root-level numeric ordering.

### Baseline Rule

`00.01` is the first code baseline unless a later governance document explicitly replaces that decision.

### Local Unified Target

`include/assembler/circulation_mechanism`

## Execution Phases

## Phase 0 - Freeze Working Boundaries

### Objective

Lock the source root, ordering rule, local target, and read-only policy for the external packages.

### Required Steps

1. Confirm the external source root.
2. Confirm root-level numeric ordering as the authoritative sequence.
3. Confirm `00.01` as the first code baseline.
4. Confirm external wave packages are read-only.
5. Confirm the local unified target path.

### Exit Criteria

- No ambiguity remains about source root, ordering, or writable target.

## Phase 1 - Source Intake Baseline

### Objective

Build a complete intake view of all root-level waves before merge logic is applied.

### Required Steps

1. Enumerate all root-level wave directories.
2. Classify each wave as one of:
   - baseline code
   - additive code delta
   - examples or tests only
   - diagnostics or performance or policy addition
   - duplicate or misaligned package
3. Record anomalies such as duplicate package roles or non-additive late waves.
4. Record the decision for handling any duplicate package branch.

### Exit Criteria

- Every wave has an explicit role.
- Anomalies are documented, not implicit.

## Phase 2 - Unified Merge Construction

### Objective

Construct a unified package in an isolated staging workspace without modifying the external source packages.

### Required Steps

1. Create a staging workspace outside the tracked package tree.
2. Copy baseline wave `00.01` into staging.
3. Apply later waves in numeric order as deltas.
4. Use the merge rule:
   - later file wins for the same relative path
   - non-overridden additions from intermediate waves are preserved
5. Exclude `_Archived`.
6. Avoid writing anything back to the external source packages.

### Exit Criteria

- A complete unified staging package exists.

## Phase 3 - Local Target Materialization

### Objective

Copy the unified staging result into the project-local target package.

### Required Steps

1. Copy unified content into `include/assembler/circulation_mechanism`.
2. Preserve `docs/`.
3. Keep temporary merge artifacts outside the target tree.
4. Preserve `_Archived/` as ignored local archive content.

### Exit Criteria

- The local target contains the unified package intended for review and normalization.

## Phase 4 - Provenance And Traceability

### Objective

Make each unified file traceable back to its exact external origin.

### Required Steps

1. Generate a source map containing:
   - `relative_path`
   - `source_wave`
   - `source_file`
2. Mirror the source map into tracked project docs.
3. Create a workflow document that explains future refresh mechanics.
4. Create an organizational cleanup report describing structural duplication and overlap.

### Exit Criteria

- Traceability is repository-local and reviewable.

## Phase 5 - Git Readiness

### Objective

Prepare Git so the unified package can be reviewed and updated with low noise and repeatable scope control.

### Required Steps

1. Enable Git long path support locally.
2. Ignore `_Archived/`.
3. Ignore temporary merge workspace paths.
4. Add `.gitattributes` rules for stable text normalization.
5. Use path-scoped Git commands for status, diff, and add.
6. Stage only the intended unified package paths and traceability artifacts.

### Exit Criteria

- Git review can focus on the unified package without unrelated repository churn.

## Phase 6 - Compile And Surface Sanity

### Objective

Verify that the unified package is compile-sane at the top-level aggregate surface before normalization begins.

### Required Steps

1. Run syntax-only compile verification for:
   - `circulation_mechanism.hpp`
   - `circulation_mechanism_runtime_core.hpp`
   - `circulation_mechanism_pre_bridge.hpp`
   - `circulation_mechanism_read_side_engine.hpp`
   - `circulation_mechanism_read_side_runtime_lists.hpp`
   - `circulation_mechanism_read_side_admission_runtime.hpp`
   - `circulation_mechanism_read_side_adapter_contracts.hpp`
   - `circulation_mechanism_diagnostic_export.hpp`
   - `circulation_mechanism_concurrency.hpp`
   - `circulation_mechanism_versioning.hpp`
2. Record any surface ambiguity discovered during compile verification.
3. Do not begin cleanup during this phase.

### Exit Criteria

- The unified package is compile-sane enough to proceed.

## Phase 7 - Organizational Audit Before Normalization

### Objective

Convert the current structural observations into an explicit normalization backlog.

### Required Steps

1. Identify live duplicated shared atoms:
   - IDs
   - states
   - ref helpers
2. Identify aggregate-header overlap and competing public surfaces.
3. Separate the package surface into:
   - canonical API
   - subsystem API
   - compatibility API
4. Identify conceptual overlap zones, including:
   - `read_side_profile` versus `read_side/*`
   - `runtime_core` versus `versioning`
   - `diagnostics` versus `diagnostic_export`
5. Convert findings into explicit cleanup work items.

### Exit Criteria

- A bounded normalization backlog exists.

## Definition Of Done

The package is formally considered:

`merged, tracked, and ready for normalization`

only when all of the following are true:

1. The unified package exists under `include/assembler/circulation_mechanism`.
2. The external waves were processed using root-level numeric ordering.
3. The external source packages were not modified.
4. A source map exists inside tracked project docs.
5. A Git workflow document exists inside tracked project docs.
6. An organizational cleanup report exists inside tracked project docs.
7. `.gitignore` and `.gitattributes` support the workflow.
8. The intended unified package paths are staged or diff-reviewable in Git.
9. Temporary merge workspace paths do not pollute Git review.
10. Aggregate-header syntax-only compile verification passes.
11. Structural duplication has been documented but not yet normalized.

## Current Status Model

This plan defines the phase boundary:

- Before this plan is closed: unified creation is still considered an active integration phase.
- After this plan is closed: the next active phase is normalization.

## Next Phase Trigger

Normalization may begin only after this plan's Definition Of Done is checked and accepted.

The first normalization wave should target:

1. canonical ownership for shared IDs,
2. canonical ownership for shared states,
3. canonical ownership for reference-helper atoms,
4. conversion of non-canonical duplicates into wrappers, forwarding headers, or compatibility surfaces where appropriate.

## Related Documents

- `CME-UNIFIED-ORG-001_Unified_Package_Organizational_Cleanup_Report.md`
- `CME-UNIFIED-GIT-001_Source_Update_And_Traceability_Workflow.md`
- `CME-UNIFIED-SOURCE-MAP-001.csv`
