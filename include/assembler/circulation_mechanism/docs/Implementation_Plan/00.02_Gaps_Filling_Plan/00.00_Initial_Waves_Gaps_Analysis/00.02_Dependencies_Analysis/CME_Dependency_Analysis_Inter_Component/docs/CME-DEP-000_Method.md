# CME-DEP-000 — Inter-Component Dependency Analysis Method

## 1. Purpose

This document defines the inter-component dependency analysis method for the 21 parent components of the Circulation Mechanism Engine.

## 2. Questions Answered

For each component:

```text
Is it a dependency for others?
Who depends on it?
Is it itself dependent?
What does it depend on?
What type and strength is the dependency?
```

## 3. Edge Direction

```text
source_component → target_component
```

Means:

```text
source_component depends on target_component
```

## 4. Dependency Types

Examples:

```text
identity
state_vocabulary
observation_surface
evidence_surface
storage
profile
runtime_use
boundary_contract
safe_scaling
reference_model
```

## 5. Two-Phase Plan

This package covers:

```text
Phase 1: Inter-components dependencies
```

Next package should cover:

```text
Phase 2: Intra-component subcomponent dependencies
```
