# EG-POL-CAT-000 — Catalog Roadmap And Doctrine

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| EG-POL-CAT-000-DOC-001 | Document Title | Catalog Roadmap And Doctrine |
| EG-POL-CAT-000-DOC-002 | File Name | `EG-POL-CAT-000_Catalog_Roadmap_And_Doctrine.md` |
| EG-POL-CAT-000-DOC-003 | Catalog Pack | EG-POL-CAT — Ecosystem Governance Policy System Catalog |
| EG-POL-CAT-000-DOC-004 | Catalog Wave | `EG-POL-CAT-CW01_Catalog_Foundation` |
| EG-POL-CAT-000-DOC-005 | Domain | `ecosystem_governance` |
| EG-POL-CAT-000-DOC-006 | Subsystem Scope | Policy System only |
| EG-POL-CAT-000-DOC-007 | Covered Implementation Span | `EG-POL-W01` through `EG-POL-W34` |
| EG-POL-CAT-000-DOC-008 | Covered Architecture Span | `EG-POL-ARCH-001` through `EG-POL-ARCH-008` |
| EG-POL-CAT-000-DOC-009 | Primary Language | English |
| EG-POL-CAT-000-DOC-010 | Status | Catalog Foundation Draft |
| EG-POL-CAT-000-DOC-011 | Implementation Direction | Markdown-first catalog, Mermaid-first diagrams, no runtime behavior |
| EG-POL-CAT-000-DOC-012 | Next Catalog Document | `EG-POL-CAT-001_Policy_System_Layer_Map.md` |
| EG-POL-CAT-000-DOC-013 | Primary Rule | The catalog describes and indexes the Policy System; it does not become a runtime registry, service locator, persistence layer, or execution authority |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the doctrine and roadmap for the **EG-POL Policy System Catalog**.

It answers the question:

```text
What is the Policy System Catalog, what does it own, what does it not own,
how does it relate to EG-POL architecture and implementation waves, and how
should future catalog entries and diagrams be added without turning the
catalog into a runtime subsystem?
```

The catalog is created after the completion of `EG-POL-W01` through `EG-POL-W34` in order to provide a navigable, stable, system-level index of the Policy System.

### 2.2 Current Scope

The current catalog scope is **only** the Policy System.

It covers:

```text
EG-POL-W01 → EG-POL-W34
EG-POL-ARCH-001 → EG-POL-ARCH-008
```

It does not attempt to catalog the whole Assembler System yet.

Other subsystems, such as ASIP, ASCC, ASOP, ASAO, material circulation, or log-level API, may receive their own equivalent catalog packs later after their respective completion points.

---

## 3. What The Catalog Is

### 3.1 Definition

The Policy System Catalog is a documentation and diagram layer that provides:

1. a layer map,
2. a component and type index,
3. an interaction catalog,
4. a gap matrix,
5. a policy add-ons catalog,
6. a wave delivery index,
7. a maturity and readiness view,
8. a diagram index and notation guide.

### 3.2 Catalog Role

The catalog is a **navigation and comprehension surface**.

It helps answer:

```text
What exists?
Where does it live?
Which wave delivered it?
What does it own?
What does it explicitly not own?
What depends on it?
What remains missing?
What diagrams explain it?
```

### 3.3 Catalog Users

The intended users are:

1. system architects,
2. future implementers,
3. reviewers,
4. test/compliance authors,
5. maintainers who need to understand the Policy System without rereading every wave package.

---

## 4. What The Catalog Is Not

### 4.1 Not The Architecture Source Of Truth

The catalog summarizes and indexes architecture.

It does not replace the architecture documents.

Architecture authority remains in:

```text
EG-POL-ARCH-001 → EG-POL-ARCH-008
```

### 4.2 Not The Implementation Source Of Truth

The catalog describes delivered implementation waves.

It does not replace wave packages, headers, manifests, tests, validation notes, or deferred decision files.

Implementation authority remains in:

```text
EG-POL-W01 → EG-POL-W34
```

### 4.3 Not A Runtime Registry

The catalog must not become:

```text
TPolicyRegistry
TPolicyRegistryVersionIndex
runtime lookup service
runtime policy discovery service
```

The catalog may describe registries, but it must not behave like one.

### 4.4 Not A Service Locator

The catalog must not locate live objects, services, endpoints, target instances, realizer instances, or runtime handles.

### 4.5 Not A Dependency Injection Container

The catalog must not wire components together.

### 4.6 Not A Persistence Layer

The catalog may describe persistence boundaries, but it must not persist policies, audit records, snapshots, or runtime reports.

### 4.7 Not A Compliance Engine

The catalog may describe compliance expectations and gap matrices.

It must not execute tests or enforce gates.

---

## 5. Difference Between Catalog, Registry, Architecture Docs, And Waves

| Concern | Owns | Does Not Own |
|---|---|---|
| Architecture docs | Conceptual rules, boundaries, doctrine | Delivered file inventory, compile status |
| Implementation waves | Headers, tests, manifests, validation notes | Global catalog view |
| Policy registry | Catalog-facing policy entries at ecosystem governance layer | System documentation navigation |
| Policy System Catalog | Navigation, maps, summaries, diagrams, gaps | Runtime lookup, storage, execution, service location |

---

## 6. Catalog Update Rules

### 6.1 Update Trigger

The catalog should be updated when:

1. a new EG-POL wave is delivered,
2. a phase closes,
3. a boundary is renamed,
4. a major deferred decision is resolved,
5. a new policy add-on category is approved,
6. a diagram becomes stale.

### 6.2 Stable Entry Rule

Each catalog entry should contain:

```text
- name
- owning domain
- wave/source document
- responsibility
- owns
- explicitly does not own
- depends on
- used by
- status/maturity
- diagram references
```

### 6.3 Non-Execution Rule

No catalog entry may describe itself as executing, invoking, mutating, storing, exporting, or enforcing runtime behavior.

### 6.4 Boundary Preservation Rule

Every catalog document must preserve the known EG-POL boundaries:

```text
Policy object ≠ executor
Assignment ≠ realization
Compatibility ≠ assignment
Runtime readiness ≠ runtime execution
Realization contract ≠ realizer
Realizer ≠ target owner
Persistence boundary ≠ persistence engine
Audit export boundary ≠ audit exporter
Production readiness gate ≠ deployment
```

---

## 7. Diagram Doctrine

### 7.1 Diagram Format

Catalog diagrams should be delivered as Mermaid files:

```text
*.mmd
```

Reasons:

1. reviewable in text diffs,
2. embeddable in Markdown,
3. exportable later to SVG/PNG/PDF,
4. independent from drawing tools.

### 7.2 Diagram Naming

Diagram names must follow:

```text
EG-POL-CAT-<doc-number>_<diagram-purpose>.mmd
```

Example:

```text
EG-POL-CAT-001_layer_map.mmd
```

### 7.3 Diagram Boundaries

Diagrams must visually distinguish:

1. foundation layers,
2. descriptor layers,
3. boundary layers,
4. skeleton layers,
5. gates,
6. future/explicitly deferred runtime behavior.

---

## 8. Catalog Roadmap

### 8.1 Catalog Wave 1 — Foundation

Delivered by this wave:

```text
EG-POL-CAT-000_Catalog_Roadmap_And_Doctrine.md
EG-POL-CAT-001_Policy_System_Layer_Map.md
diagrams/EG-POL-CAT-000_catalog_position.mmd
diagrams/EG-POL-CAT-001_layer_map.mmd
```

### 8.2 Catalog Wave 2 — Components And Interactions

Planned:

```text
EG-POL-CAT-002_Component_And_Type_Catalog.md
EG-POL-CAT-003_Policy_System_Interaction_Catalog.md
diagrams/EG-POL-CAT-002_component_type_map.mmd
diagrams/EG-POL-CAT-003_interaction_map.mmd
```

### 8.3 Catalog Wave 3 — Gaps And Add-ons

Planned:

```text
EG-POL-CAT-004_Gap_Matrix.md
EG-POL-CAT-005_Policy_Addons_Catalog.md
diagrams/EG-POL-CAT-004_gap_heatmap.mmd
diagrams/EG-POL-CAT-005_policy_addons_map.mmd
```

### 8.4 Catalog Wave 4 — Waves, Readiness, Diagrams

Planned:

```text
EG-POL-CAT-006_Wave_Index_And_Delivery_Map.md
EG-POL-CAT-007_Readiness_And_Maturity_Catalog.md
EG-POL-CAT-008_Diagram_Index_And_Notation_Guide.md
diagrams/EG-POL-CAT-006_wave_dependency_graph.mmd
diagrams/EG-POL-CAT-007_readiness_ladder.mmd
```

---

## 9. Acceptance Criteria

This catalog foundation is accepted when:

1. the catalog scope is limited to the Policy System,
2. the catalog is not confused with the whole Assembler System catalog,
3. the catalog is not confused with policy registry,
4. the catalog roadmap is accepted,
5. Mermaid is accepted as the initial diagram format,
6. future catalog waves can proceed from this doctrine.

---

## 10. Final Summary

The Policy System Catalog is a documentation and diagram layer for the completed EG-POL subsystem.

Its central rules are:

```text
Catalog ≠ Runtime Registry
Catalog ≠ Service Locator
Catalog ≠ Dependency Injection Container
Catalog ≠ Persistence Layer
Catalog ≠ Compliance Engine
Catalog ≠ Architecture Source Of Truth
Catalog ≠ Implementation Source Of Truth
```

The next catalog document is:

```text
EG-POL-CAT-001_Policy_System_Layer_Map.md
```
