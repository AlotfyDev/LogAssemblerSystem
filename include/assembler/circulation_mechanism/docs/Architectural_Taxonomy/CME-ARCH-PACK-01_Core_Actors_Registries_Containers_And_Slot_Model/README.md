# CME-ARCH-PACK-01 — Core Actors, Registries, Containers, And Slot Model

## 1. Package Control

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-01` |
| Package Title | Core Actors, Registries, Containers, And Slot Model |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Implementation Direction | C++17, header-only-first where appropriate, templates, traits, CRTP-compatible abstraction layers |
| Follows | `CME-ARCH-PACK-00_Foundation_And_Holistic_View` |
| Primary Purpose | Convert the agreed taxonomy into detailed architectural specs for foundational components |
| Non-Purpose | Final headers, final type names, implementation code, bridge runtime, final receiver lifecycle |

## 2. Package Contents

```text
CME-ARCH-PACK-01_Core_Actors_Registries_Containers_And_Slot_Model/
├── CME-ARCH-001_Core_Taxonomy_And_Component_Ownership.md
├── CME-ARCH-002_Container_Family_Registry_And_Uniform_Capacity_Model.md
├── CME-ARCH-003_Slot_Container_State_And_Residency_Model.md
├── README.md
├── WAVE_MANIFEST.json
├── TRACEABILITY_NOTES.md
├── DEFERRED_DECISIONS.md
└── diagrams/
    ├── CME-ARCH-001_taxonomy_tree.mmd
    ├── CME-ARCH-002_container_registry_indexing.mmd
    ├── CME-ARCH-002_bundle_agent_moderator_registry.mmd
    └── CME-ARCH-003_container_slot_state_separation.mmd
```

## 3. Package Thesis

The Circulation Mechanism Engine is a pre-bridge, write-side circulation engine that coordinates envelope residency and exposure through a small set of well-bounded actors and data structures.

The core is:

```text
BundleAgent
→ ContainerRegistry
→ Moderator
→ TContainer
→ TSlot
→ WaitingLists
→ RoundManager
→ ReferencePrecalculator
→ Ingress / Dispatcher
```

The package defines component ownership before file names or C++ declarations are derived.

## 4. Package-Level Rules

### 4.1 Component Ownership Before Header Derivation

Every component must have explicit:

```text
definition
category
responsibilities
non-responsibilities
identity
state
inputs
outputs
dependencies
views
reports
safe points
configuration profiles
```

### 4.2 Container State Is Not Slot State

`TContainerState` and `TSlotState` are different state models.

`TContainerState` governs cycle eligibility and operational participation.

`TSlotState` governs the local placement/access condition of a slot.

### 4.3 Registry Indexing Is Internal

The engine may use `TContainerRegistryIndex` as the main locator internally.

External consumers still consume prepared access references and do not locate containers or slots.

### 4.4 Uniform Capacity Is a Structural Invariant

All active `TContainer` instances inside the active registry profile share the same capacity and slot layout.

This enables move-semantics-oriented circulation by construction.

### 4.5 Reports And Views Are Specification Surfaces

Views expose safe read-only projections.

Reports provide action, transition, and diagnostic evidence.

Neither is a mutation surface unless explicitly stated in a later spec.

## 5. Recommended Next Package

```text
CME-ARCH-PACK-02_Ingress_Dispatch_WaitingLists_And_Round_Behavior
```
