# ASCC-COMP-W01 — Internal Subwave Plan

## Purpose

ASCC-COMP-W01 is intentionally split into internal subwaves.  The goal is a clean, stable, scalable, integrable ASCC core, not rushed patching.

## Subwaves

### W01A — Empirical Inventory Extraction

Source:

```text
include/assembler/bridge_orchestrator/docs/SmokeTests_SystemView/w01_smoke_test ... w15_smoke_test
```

Output:

```text
ASCC-COMP-W01A_Component_Inventory.csv
```

Rules:

```text
- Include all CSV-listed components.
- Preserve wave, category, documented path when available.
- Mark whether the CSV row is path-backed or analysis-only.
```

### W01B — Header Existence And Path Reality Check

Output:

```text
ASCC-COMP-W01B_Header_Reality_Matrix.csv
```

Checks:

```text
- header exists
- header non-empty
- header is canonical implementation
- header is forwarding include
- header is missing
- header is analysis-only concept without required header
```

### W01C — Safe Structural Cleanup

Allowed actions:

```text
- convert empty public headers into forwarding headers
- add missing safe aggregate headers only when canonical implementation exists
- do not invent new domain concepts in W01
- do not add participant capabilities, binding metadata, protocol requirements, or readiness gates
```

### W01D — Canonical Root Decision Preparation

Question:

```text
Should ASCC physical root remain bridge_orchestrator, migrate to communication_context,
or support both through compatibility forwarding includes?
```

Output:

```text
ASCC-COMP-W01D_Root_Path_Decision_Input.md
```

### W01E — Compile Smoke Sweep

Output:

```text
ascc_comp_w01_header_reality_audit_smoke_test.cpp
ASCC-COMP-W01E_Compile_Notes.md
```

The smoke test must include the public paths fixed or classified by W01.

## Current State

Already completed in the first cleanup slice:

```text
- obligations/ports/contracts/TPort.hpp converted from empty header to local forwarding include
- bridge_core/orchestration/TBridge.hpp converted from empty header to local forwarding include
```

## Boundary

W01 does not implement:

```text
participant capability set
binding composition metadata
protocol requirements
generic readiness reports
composable production gate
integration packs
pipeline composer
```

Those begin at ASCC-COMP-W02 and later.
