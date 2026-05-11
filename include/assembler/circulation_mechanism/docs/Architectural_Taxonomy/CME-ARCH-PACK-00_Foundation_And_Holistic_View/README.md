# CME-ARCH-PACK-00 — Foundation And Holistic Architecture View

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-00` |
| Package Name | `Foundation And Holistic Architecture View` |
| Domain | `circulation_mechanism` |
| System Umbrella | Log-Level Assembler System |
| Status | Architecture Draft V1 |
| Primary Output | Holistic architecture document and context diagrams |
| Implementation Direction | C++17, header-only-first where appropriate, templates, traits, CRTP-compatible static abstractions |

## 2. Package Purpose

This package establishes the first holistic architecture view of the `Circulation Mechanism Engine`.

It does **not** define final C++ headers.

It does **not** freeze final class names.

It does **not** implement the engine.

It provides the foundation needed before component-specific architecture documents, state-machine documents, reference-validity documents, boundary documents, and implementation-readiness specs.

## 3. Package Contents

```text
CME-ARCH-PACK-00_Foundation_And_Holistic_View/
├── CME-ARCH-000_Holistic_Foundation_And_System_View.md
├── README.md
├── WAVE_MANIFEST.json
├── DEFERRED_DECISIONS.md
├── TRACEABILITY_NOTES.md
└── diagrams/
    ├── CME-ARCH-000_context_boundary_map.mmd
    ├── CME-ARCH-000_holistic_component_map.mmd
    ├── CME-ARCH-000_two_cycle_payload_direction.mmd
    ├── CME-ARCH-000_reference_precalculation_pipeline.mmd
    ├── CME-ARCH-000_state_and_safe_point_map.mmd
    └── CME-ARCH-000_pre_bridge_vs_read_side_profile.mmd
```

## 4. Main Document

Start with:

```text
CME-ARCH-000_Holistic_Foundation_And_System_View.md
```

## 5. Diagram Rendering

The `.mmd` files are Mermaid source diagrams and can be rendered later by any Mermaid-compatible tool.

## 6. Current Coverage

This pack covers:

1. engine identity,
2. pre-bridge write-side profile,
3. boundary position,
4. payload direction thesis,
5. actor / registry / container / state / reference taxonomy,
6. two-cycle model,
7. container registry foundation,
8. reference precalculation principle,
9. reports/views principle,
10. safe-point principle,
11. passive pull default,
12. pre-bridge vs read-side profile separation,
13. anti-collapse rules,
14. next architecture pack roadmap.
