# CME-UNIFIED-ORG-001 - Unified Package Organizational Cleanup Report

## 1. Purpose

This document records the organizational cleanup decisions required before starting implementation upgrades on the unified `circulation_mechanism` package.

The goal is to preserve the current unified package as a valid, compilable integration point while identifying and tracking conceptual duplication that should be cleaned in a controlled, traceable way.

## 2. Scope

This report covers:

1. canonical ownership of repeated IDs, states, and reference helper types,
2. aggregate-header overlap,
3. compatibility-surface containment,
4. subsystem-surface separation,
5. sequencing constraints for later cleanup work.

This report does not modify runtime behavior or add new implementation logic.

## 3. Current Unified Baseline

The current unified package under:

```text
include/assembler/circulation_mechanism/
```

is a merged product of:

1. canonical domain consolidation,
2. shared runtime core,
3. pre-bridge subsystem packaging,
4. read-side subsystem packaging,
5. diagnostics export additions,
6. concurrency policy,
7. versioning and compatibility policy.

The package currently compiles at aggregate-header level and is treated as the pre-cleanup baseline.

## 4. Primary Findings

### 4.1 Repeated Canonical Atoms Across Multiple Local Roots

The unified package contains repeated live definitions for the same semantic atoms under:

```text
ids/
component-local ids/
component-local state/
component-local reference_precalculator/handles/
```

Examples include:

1. `TContainerRegistryIndex`
2. `TContainerId`
3. `TRoundId`
4. `TSlotIndex`
5. `TReferenceValidityState`
6. `TSafePointState`
7. `TAccessRefDirection`
8. `TAccessRefId`
9. `TAccessRefKind`
10. `TAccessRefScope`

This is the highest-priority cleanup area because it creates ambiguous ownership and risks accidental duplicate type contracts across the same namespace.

### 4.2 ReadSide Public Surface Is Split Into Two Models

The package currently exposes both:

1. `circulation_mechanism_read_side_profile.hpp`
2. `circulation_mechanism_read_side_engine.hpp`
3. `circulation_mechanism_read_side_runtime_lists.hpp`
4. `circulation_mechanism_read_side_admission_runtime.hpp`
5. `circulation_mechanism_read_side_adapter_contracts.hpp`

This means the public ReadSide story is split between:

1. a wave/profile aggregate model,
2. an injectable subsystem model.

This must be normalized into one canonical public path and one compatibility/decomposition path.

### 4.3 Runtime Core And Versioning Have Public-Surface Overlap

The following concepts appear under both runtime-core and versioning-oriented surfaces:

1. API version,
2. profile version,
3. compatibility status,
4. compatibility reporting.

This is not an immediate compile defect, but it is a conceptual ownership conflict that should be resolved before downstream code starts depending on both surfaces independently.

### 4.4 Diagnostics And Diagnostic Export Need Boundary Clarification

The package exposes both:

1. contract-level diagnostics under `diagnostics/`,
2. unified collector/export boundary under `diagnostic_export/`.

The separation is architecturally valid, but naming and public-surface guidance should explicitly state:

1. which layer is the base issue/invariant contract,
2. which layer is the production aggregation/export boundary.

### 4.5 Compatibility Assets Are Still Publicly Visible In The Same Tree

Legacy wave aggregates and legacy type shims remain under:

```text
compatibility/
```

This is acceptable for preservation and migration, but they must not remain visually equivalent to canonical surfaces in cleanup decisions or future includes.

## 5. Cleanup Decision Set

### Decision D1 - Global Canonical Ownership For Shared Atoms

The following families should have one canonical home only:

1. IDs -> `ids/`
2. cross-component state enums -> `state/`
3. shared access-ref helpers -> `reference_precalculator/handles/`

Component-local copies should become one of:

1. forwarding includes,
2. compatibility wrappers,
3. removed duplicates after migration.

### Decision D2 - ReadSide Canonical Surface Split

ReadSide should be documented as:

1. canonical domain/profile surface,
2. canonical injectable subsystem surface,
3. compatibility legacy wave surface.

Only one of the first two may be treated as the top-level default public entrypoint.

### Decision D3 - Runtime Core vs Versioning Boundary

`runtime_core/` should own runtime-instance lifecycle/configuration concerns.

`versioning/` should own:

1. compatibility policy,
2. schema/profile/api version contracts,
3. feature-flag exposure.

If a type appears in both areas today, one side must become the declared public owner.

### Decision D4 - Diagnostics Layering Rule

`diagnostics/` should remain the base issue/report/invariant contract layer.

`diagnostic_export/` should remain the production collector/export boundary layer.

The names and includes should make that layering explicit.

### Decision D5 - Compatibility Containment Rule

Everything under `compatibility/` must be treated as non-canonical by default.

No new production-facing upgrade should target compatibility headers unless the explicit task is migration support.

## 6. Tracked Cleanup Work Items

| Cleanup ID | Area | Action | Status |
|---|---|---|---|
| `CME-UNIFIED-CLEAN-001` | IDs | choose canonical global ID owners and downgrade component-local copies | pending |
| `CME-UNIFIED-CLEAN-002` | States | choose canonical global state owners and downgrade component-local copies | pending |
| `CME-UNIFIED-CLEAN-003` | Access refs | choose canonical ref-helper owners under `reference_precalculator/handles/` | pending |
| `CME-UNIFIED-CLEAN-004` | ReadSide | declare canonical top-level ReadSide entry strategy | pending |
| `CME-UNIFIED-CLEAN-005` | Runtime/versioning | resolve overlapping ownership of compatibility/version contracts | pending |
| `CME-UNIFIED-CLEAN-006` | Diagnostics | document and enforce diagnostics vs export layering | pending |
| `CME-UNIFIED-CLEAN-007` | Compatibility | reduce accidental use of compatibility aggregates in canonical surfaces | pending |

## 7. Execution Order

Cleanup should proceed in this order:

1. shared IDs,
2. shared states,
3. shared ref-helper atoms,
4. aggregate-header normalization,
5. ReadSide public-surface normalization,
6. runtime-core/versioning normalization,
7. diagnostics/export clarification,
8. compatibility containment pass.

This order minimizes cross-header churn and keeps compile-sanity checks easy to repeat after each step.

## 8. Safety Rules

During cleanup:

1. do not change external source-wave packages,
2. do not remove `_Archived`,
3. do not modify architectural docs to fit code shortcuts,
4. do not delete compatibility assets until canonical replacements are confirmed,
5. do not begin behavioral upgrades before canonical ownership cleanup starts.

## 9. Baseline Rule

The current unified package is the organizational baseline.

All cleanup changes should be expressed as tracked deltas from this baseline, not as a fresh rebuild from the external waves.

## 10. Final Note

The unified package is currently suitable as a merge baseline.

It is not yet organizationally clean enough to serve as the long-term public surface without a focused canonical-ownership cleanup pass.
