# CANONICAL_OWNERSHIP_MAP — CME-PROD-HARDEN-W01

## 1. Purpose

This document records canonical ownership decisions applied during domain consolidation.

## 2. Canonical Ownership Decisions

| Type / Aggregate | Canonical Owner | Former / Legacy Location | Decision |
|---|---|---|---|
| `TContainerTimeRange` | `container/` | `eviction/` shim | `container/` owns; eviction includes container-owned type |
| `TContainerTimeRangeView` | `container/` | `eviction/views/` shim | `container/` owns; eviction uses canonical view |
| `TSafePointState` | `state/` | `safe_points/` shim | `state/` owns; safe_points includes canonical state |
| `read_side_circulation_profile_w01..w04` | `read_side_circulation_profile/` | root-level shims | subfolder owns; root canonical aggregate is `circulation_mechanism_read_side_profile.hpp` |
| `circulation_mechanism_w01..w14` | compatibility layer | root-level wave aggregates | moved under `compatibility/legacy_wave_aggregates/` |
| full domain aggregate | root | new | `circulation_mechanism.hpp` is canonical full-domain aggregate |

## 3. Public API Rule

Canonical public root headers are the production aggregate headers only. Legacy wave aggregates are not part of the canonical public API.

## 4. Compatibility Rule

Legacy wave aggregates are retained under `compatibility/` for migration/reference only.
