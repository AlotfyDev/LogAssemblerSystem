# ASCC-COMP-W10 — Bridge Core Operational Analysis

## 1. Purpose

This folder records the operational analytical view for:

```text
include/assembler/bridge_orchestrator/bridge_core/
```

The goal is to distinguish descriptor-only files from real header-only operational model logic, and to identify the missing operational components required to turn the current Bridge Core model into a fuller executable bridge runtime if that later becomes an ASCC responsibility.

## 2. Context

The Assembler System uses a C++17 header-only-first approach. Therefore, a `.hpp` file may contain actual model execution logic, not merely type descriptors.

This analysis treats header-only operational logic as first-class logic.

## 3. Files In This Pack

| File | Purpose |
|---|---|
| `ASCC-COMP-W10_Bridge_Core_Operational_Analysis.md` | Formal domain documentation for the `bridge_core/` operational analysis |
| `ASCC-COMP-W10_Bridge_Core_Operational_Matrix.csv` | Detailed CSV matrix for each observed Bridge Core file, including classification, operational gaps, and recommended action |

## 4. Core Finding

`bridge_core/` is not a descriptor-only folder.

It contains endpoint-neutral bridge model runtime logic centered on `TBridge.hpp`, with bounded step execution, declaration preflight policy, status transitions, result mapping, and read-only evidence production.

However, the current Bridge Core intentionally does not execute concrete endpoints, ports, plugin adapters, schedulers, IO, persistence, telemetry, or LogAPI/CME/read-side internals.

## 5. Boundary Rule

```text
Bridge Core currently owns model-step orchestration.
Bridge Core does not currently own endpoint runtime execution.
```

## 6. Next Analysis Dependency

The next required subdirectory analysis is:

```text
include/assembler/bridge_orchestrator/protocols/
```

Reason: `TBridge::step_model_once()` delegates the central model advancement to `TBridgeProtocol<PlanCapacity>::advance_model_step()`.
