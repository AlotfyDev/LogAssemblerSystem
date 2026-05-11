# CME-ARCH-PACK-03 — Reference Precalculation, Validity, And Access Separation

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-03` |
| Package Name | Reference Precalculation, Validity, And Access Separation |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | Separating locating/reference calculation from access execution |
| Implementation Direction | C++17, header-only-first, static/profile-driven, reference-validity aware |

## 2. Package Purpose

This package specifies the reference model that allows producer-side and dispatcher-side consumers to use the engine through a `next` rhythm without knowing container topology, slot location, registry layout, or selection logic.

The package defines:

```text
ReferencePrecalculator
Reference supply
Ingress references
Dispatch references
Slot access references
Round-scoped references
Next-ref tokens
Reference validity states
Invalidation rules
Stale reference diagnostics
```

## 3. Documents

```text
CME-ARCH-007_Reference_Precalculation_And_Next_Ref_Supply_Model.md
CME-ARCH-008_Reference_Validity_Scope_And_Invalidation_Model.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-007_reference_precalculation_flow.mmd
diagrams/CME-ARCH-007_next_ref_consumer_view.mmd
diagrams/CME-ARCH-008_reference_validity_state_machine.mmd
```

## 5. Package-Level Rules

### 5.1 Separation Rule

```text
ReferencePrecalculator owns locating/reference calculation.
Ingress and Dispatcher own access execution.
```

### 5.2 No Discovery Rule

```text
Consumers do not discover containers, slots, registry indices, or capacity at access time.
```

### 5.3 No Semantic Interpretation Rule

```text
Reference calculation does not inspect or interpret envelope content.
```

### 5.4 Direction Rule

```text
Ingress references are not dispatch references.
Dispatch references are not ingress references.
```

### 5.5 Validity Rule

```text
Every access reference is valid only inside its declared scope.
```
