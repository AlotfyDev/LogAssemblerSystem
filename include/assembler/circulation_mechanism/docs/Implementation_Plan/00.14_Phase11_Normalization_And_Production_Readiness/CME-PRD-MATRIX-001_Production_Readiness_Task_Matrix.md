# CME-PRD-MATRIX-001 Production Readiness Task Matrix

## Purpose

This matrix defines the full execution scope required to move the unified `circulation_mechanism` package from:

`merged, tracked, and ready for normalization`

to:

`full production ready and publishable`

It is the orchestration reference for task decomposition, micro-task generation, and sub-agent delegation.

## Final End State

The `circulation_mechanism` package is considered full production ready only when all of the following are true:

1. canonical ownership is unambiguous for shared atoms,
2. public surfaces are tiered and intentional,
3. compatibility assets are contained and non-default,
4. compile verification is repeatable and automated,
5. smoke coverage exists for the production-facing aggregate surfaces,
6. production-readiness gates are represented in code and verified by artifacts,
7. documentation reflects the final public usage story,
8. the package can be published as a header-only C++17 subsystem without structural ambiguity.

## Delivery Streams

The work is organized into five delivery streams:

1. canonical normalization,
2. surface consolidation,
3. subsystem readiness,
4. verification and gates,
5. publishability.

## Task Matrix

| Matrix ID | Stream | Task | Target Files / Roots | Final Objective |
|---|---|---|---|---|
| `PRD-001` | Governance | establish Phase 11 execution board and traceability anchors | `include/assembler/circulation_mechanism/docs/Implementation_Plan/00.14_Phase11_Normalization_And_Production_Readiness/` | every normalization and readiness task has a tracked home, status model, and closure path |
| `PRD-002` | Canonical normalization | canonicalize shared ID ownership | `ids/`, `container/ids/`, `container_registry/ids/`, `dispatcher/ids/`, `eviction/ids/`, `ingress/ids/`, `moderator/ids/`, `reference_precalculator/ids/`, `release_recycle/ids/`, `round_manager/ids/`, `slot/ids/`, `waiting_list/ids/`, `circulation_mechanism_ids.hpp` | one declared public owner exists for every shared ID atom and all non-canonical copies are downgraded |
| `PRD-003` | Canonical normalization | canonicalize shared cross-component states | `state/`, `bundle_agent/state/`, `container/state/`, `dispatcher/state/`, `eviction/state/`, `moderator/state/`, `reference_precalculator/state/`, `release_recycle/state/`, `round_manager/state/`, `slot/state/`, `waiting_list/state/`, `circulation_mechanism_state.hpp` | one declared public owner exists for every shared state atom and cross-component state usage is normalized |
| `PRD-004` | Canonical normalization | canonicalize shared reference-helper atoms | `reference_precalculator/handles/`, `dispatcher/reference_precalculator/handles/`, `ingress/reference_precalculator/handles/`, `circulation_mechanism_reference_precalculator.hpp` | access-ref helper vocabulary has one canonical home and local duplicates become wrappers or compatibility shims |
| `PRD-005` | Canonical normalization | normalize shared include graph after atom ownership cleanup | all root aggregate headers plus any local forwarding wrappers created by `PRD-002` to `PRD-004` | aggregate and local includes depend on canonical atoms instead of parallel live definitions |
| `PRD-006` | Surface consolidation | define aggregate-header tiering and default entrypoints | `circulation_mechanism.hpp`, `circulation_mechanism_*.hpp` root aggregates, `compatibility/legacy_wave_aggregates/` | the package exposes a clear top-level public surface, subsystem surfaces, and compatibility-only surfaces |
| `PRD-007` | Surface consolidation | resolve ReadSide dual-surface model | `circulation_mechanism_read_side_profile.hpp`, `circulation_mechanism_read_side_engine.hpp`, `circulation_mechanism_read_side_runtime_lists.hpp`, `circulation_mechanism_read_side_admission_runtime.hpp`, `circulation_mechanism_read_side_adapter_contracts.hpp`, `read_side/`, `read_side_circulation_profile/`, `compatibility/legacy_read_side_aggregates/` | ReadSide has one canonical public story and one explicitly secondary compatibility/decomposition story |
| `PRD-008` | Surface consolidation | resolve runtime-core versus versioning ownership | `circulation_mechanism_runtime_core.hpp`, `circulation_mechanism_versioning.hpp`, `runtime_core/`, `versioning/` | runtime lifecycle concerns and versioning concerns are cleanly separated with no ambiguous public ownership |
| `PRD-009` | Surface consolidation | clarify diagnostics layering and export boundary | `circulation_mechanism_diagnostics.hpp`, `circulation_mechanism_diagnostic_export.hpp`, `diagnostics/`, `diagnostic_export/` | base diagnostics contracts and production export boundary are clearly separated and documented by surface structure |
| `PRD-010` | Surface consolidation | contain compatibility assets as non-default migration surfaces | `compatibility/`, `circulation_mechanism.hpp`, all canonical root aggregates that may still include compatibility assets indirectly | compatibility headers remain available but cannot be confused with canonical production headers |
| `PRD-011` | Subsystem readiness | consolidate pre-bridge public shape | `circulation_mechanism_pre_bridge.hpp`, `pre_bridge/`, `ingress/`, `dispatcher/`, `waiting_list/`, `round_manager/`, `bundle_agent/`, `moderator/` | the pre-bridge engine story is coherent, minimal, and aligned with the architectural taxonomy |
| `PRD-012` | Subsystem readiness | validate read-side runtime decomposition against intended receiver/addon model | `read_side/`, `read_side_circulation_profile/`, `communication_bindings/`, `production_readiness/` | the post-bridge operational model is internally consistent and maps cleanly to receivers, adapters, retry, delayed release, and backpressure |
| `PRD-013` | Subsystem readiness | formalize production-readiness gate semantics in code-facing documentation | `production_readiness/`, `circulation_mechanism_production_readiness.hpp`, new docs under `00.14_Phase11_Normalization_And_Production_Readiness/` | production readiness stops being a passive type set and becomes an explicit acceptance framework |
| `PRD-014` | Verification and gates | create repeatable compile-matrix verification | new path `include/assembler/circulation_mechanism/tests/compile/`, root aggregate headers, selected subsystem headers | every production-facing aggregate compiles in isolation and in representative combinations under C++17 |
| `PRD-015` | Verification and gates | create smoke tests for canonical usage paths | new path `include/assembler/circulation_mechanism/tests/smoke/`, canonical root aggregates, representative pre-bridge and read-side integration headers | the package proves minimal end-to-end include and type-assembly viability for its intended public entrypoints |
| `PRD-016` | Verification and gates | create production gate report generation path | `production_readiness/`, `diagnostics/`, `diagnostic_export/`, new verification docs and tests | readiness reports can be produced from defined criteria and evidence rather than inferred manually |
| `PRD-017` | Verification and gates | create structural regression checks for compatibility leakage | `compatibility/`, root aggregates, new tests under `include/assembler/circulation_mechanism/tests/compile/` or `tests/smoke/` | accidental reintroduction of compatibility-first includes or duplicate public ownership is detectable |
| `PRD-018` | Verification and gates | define benchmark and stress acceptance scope | new path `include/assembler/circulation_mechanism/tests/benchmarks/`, `capacity/`, `container_registry/`, `reference_precalculator/`, `read_side/runtime_lists/`, `concurrency/` | the package has an explicit performance validation story for high-risk structural areas even if implementation remains header-only |
| `PRD-019` | Publishability | write canonical package usage documentation | new path `include/assembler/circulation_mechanism/docs/Usage/`, `circulation_mechanism.hpp`, subsystem aggregates, `versioning/`, `production_readiness/` | consumers have one clear story for inclusion, layering, compatibility stance, and verification expectations |
| `PRD-020` | Publishability | define release manifest and publication checklist | new docs under `00.14_Phase11_Normalization_And_Production_Readiness/`, `.gitattributes`, `.gitignore`, root aggregate headers, compile/smoke artifacts | publication requires a deterministic checklist covering structure, compile status, tests, docs, and compatibility posture |

## Dependency Order

Execution order should follow this dependency chain:

1. `PRD-001`
2. `PRD-002` -> `PRD-003` -> `PRD-004` -> `PRD-005`
3. `PRD-006` -> `PRD-007` -> `PRD-008` -> `PRD-009` -> `PRD-010`
4. `PRD-011` -> `PRD-012` -> `PRD-013`
5. `PRD-014` -> `PRD-015` -> `PRD-016` -> `PRD-017` -> `PRD-018`
6. `PRD-019` -> `PRD-020`

## Micro-Task Decomposition Rule

Each matrix item must be decomposed into micro-tasks before implementation begins.

Every micro-task must include:

1. one narrow objective,
2. exact file targets,
3. a compile or review checkpoint,
4. a clear completion condition,
5. no hidden dependency on undocumented assumptions.

## Sub-Agent Delegation Rule

Sub-agents should be assigned by workstream, not by broad phase title.

Initial delegation boundaries:

1. canonical atoms specialist:
   - `PRD-002`
   - `PRD-003`
   - `PRD-004`
   - `PRD-005`
2. public-surface specialist:
   - `PRD-006`
   - `PRD-007`
   - `PRD-008`
   - `PRD-009`
   - `PRD-010`
3. subsystem-shape specialist:
   - `PRD-011`
   - `PRD-012`
   - `PRD-013`
4. verification specialist:
   - `PRD-014`
   - `PRD-015`
   - `PRD-016`
   - `PRD-017`
   - `PRD-018`
5. release and publishability specialist:
   - `PRD-019`
   - `PRD-020`

## Success Condition

This matrix is complete only when it is followed by:

1. a micro-task breakdown,
2. sub-agent delegation records,
3. iterative implementation and review,
4. final production-readiness closure evidence.
