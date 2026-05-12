# EG-POL-CAT-008 — Diagram Index And Notation Guide

## 1. Document Control

| Field | Value |
|---|---|
| Document Title | Diagram Index And Notation Guide |
| File Name | `EG-POL-CAT-008_Diagram_Index_And_Notation_Guide.md` |
| Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| Scope | Diagram inventory and notation rules for the policy system catalog |
| Status | Catalog Draft V1 |

## 2. Purpose

This document indexes the Mermaid diagrams in the policy system catalog and defines the notation rules used by those diagrams.

The diagrams are intended to be repository-friendly, diff-friendly, and easy to export later to SVG, PNG, or PDF.

## 3. Diagram Inventory

| Diagram File | Purpose | Related Document |
|---|---|---|
| `EG-POL-CAT-000_catalog_position.mmd` | shows the catalog as an observability/navigation layer over EG-POL | CAT-000 |
| `EG-POL-CAT-001_layer_map.mmd` | shows policy system layer phases W01–W34 | CAT-001 |
| `EG-POL-CAT-002_component_type_map.mmd` | shows core component/type groups | CAT-002 |
| `EG-POL-CAT-003_interaction_map.mmd` | shows major interactions among policy system layers | CAT-003 |
| `EG-POL-CAT-004_gap_heatmap.mmd` | shows gap clusters and severity | CAT-004 |
| `EG-POL-CAT-005_policy_addons_map.mmd` | shows policy add-on extension classes | CAT-005 |
| `EG-POL-CAT-006_wave_dependency_graph.mmd` | shows dependency order by wave groups | CAT-006 |
| `EG-POL-CAT-007_readiness_ladder.mmd` | shows maturity progression | CAT-007 |

## 4. File Naming Rules

Diagram files use this pattern:

```text
EG-POL-CAT-<doc-number>_<short_diagram_name>.mmd
```

Examples:

```text
EG-POL-CAT-006_wave_dependency_graph.mmd
EG-POL-CAT-007_readiness_ladder.mmd
```

## 5. Notation Rules

### 5.1 Allowed Arrow Meaning

| Arrow | Meaning |
|---|---|
| `-->` | dependency, progression, or allowed flow |
| `-.->` | advisory, observation, or catalog reference |
| `-->|label|` | typed relationship |

### 5.2 Forbidden Ambiguity

A diagram must not imply:

```text
catalog = runtime registry
policy assignment = target invocation
runtime readiness = execution
engine skeleton = production engine
persistence boundary = storage engine
audit boundary = telemetry exporter
```

### 5.3 Boundary Labels

When a node is a boundary or skeleton, its label should include that word:

```text
Persistence Boundary
Audit Export Boundary
Realization Engine Skeleton
Production Readiness Gate
```

### 5.4 Maturity Labels

Prefer explicit maturity labels:

```text
primitive
foundation
descriptor
boundary
skeleton
gate
```

## 6. Diagram Maintenance Rules

1. Add one diagram entry for every new `.mmd` file.
2. Do not draw runtime arrows unless the runtime is implemented.
3. Use dashed arrows for catalog/reference relationships.
4. Use explicit labels for forbidden or deferred relationships.
5. Keep diagrams readable; split large diagrams into focused diagrams rather than making one giant map.

## 7. Export Policy

Current source format is Mermaid `.mmd`.

Future exports may generate:

```text
SVG
PNG
PDF
```

Exported artifacts should never become the canonical source; `.mmd` remains canonical.
