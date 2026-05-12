# ASCC-COMP-W01 — Canonical Path Decisions

## Current decision status

The project currently stores ASCC implementation files under:

```text
include/assembler/bridge_orchestrator/
```

Many headers include the same domain through:

```text
assembler/communication_context/...
```

This W01 slice does not rename the physical root.  It establishes a conservative compatibility rule:

```text
Do not duplicate canonical types.
Public/canonical-looking alternate paths must forward to the implemented type
until a full root-name migration decision is made.
```

## Decisions applied in this slice

| Decision ID | Decision | Applied To |
|---|---|---|
| ASCC-COMP-W01-PATH-001 | Convert empty contract path to forwarding header | `obligations/ports/contracts/TPort.hpp` |
| ASCC-COMP-W01-PATH-002 | Convert empty bridge orchestration path to forwarding header | `bridge_core/orchestration/TBridge.hpp` |

## Deferred decision

| Decision ID | Open Question | Deferred To |
|---|---|---|
| ASCC-COMP-W01-PATH-003 | Should the physical root become `communication_context/`, remain `bridge_orchestrator/`, or support both through compatibility includes? | Full W01 inventory expansion |
