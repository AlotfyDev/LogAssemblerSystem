# CME-IMPL-PLAN-00 — Implementation Wave Planning

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-IMPL-PLAN-00` |
| Package Name | Implementation Wave Planning |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Implementation Planning Draft |
| Primary Focus | Wave sequencing, dependency order, candidate headers, smoke tests, architectural protection gates |
| Implementation Direction | C++17, header-only-first, templates/traits/static polymorphism, architecture-before-code |

## 2. Purpose

This package transitions the Circulation Mechanism Engine from architecture packs to implementation wave planning.

It does not implement code.

It defines:

```text
wave order
wave dependencies
wave contents
candidate headers
compile smoke expectations
negative tests
deferred decisions
readiness gates
```

## 3. Documents

```text
CME-IMPL-000_Implementation_Wave_Planning_Roadmap.md
CME-IMPL-001_Wave_Sequencing_And_Dependency_Model.md
CME-IMPL-002_First_Waves_Header_Skeleton_Plan.md
CME-IMPL-003_Test_And_Compliance_Derivation_Plan.md
```

## 4. Diagrams

```text
diagrams/CME-IMPL-000_wave_dependency_map.mmd
diagrams/CME-IMPL-001_layered_wave_stack.mmd
diagrams/CME-IMPL-002_first_wave_header_map.mmd
diagrams/CME-IMPL-003_test_gate_flow.mmd
```

## 5. Package-Level Rules

### 5.1 Implementation Planning Rule

```text
Planning is not implementation.
```

### 5.2 Dependency Rule

```text
Foundational identifiers, states, handles, and views must precede behavior-bearing components.
```

### 5.3 Header-Only First Rule

```text
Initial implementation waves should produce lightweight headers and compile-only tests before behavior-heavy algorithms.
```

### 5.4 Anti-Collapse Rule

```text
Implementation waves must preserve the boundaries established in CME-ARCH-PACK-00 through CME-ARCH-PACK-08.
```
