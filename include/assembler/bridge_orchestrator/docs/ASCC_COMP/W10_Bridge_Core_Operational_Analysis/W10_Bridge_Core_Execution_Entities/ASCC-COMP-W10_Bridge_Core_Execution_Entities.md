# ASCC-COMP-W10 — Bridge Core Execution Entities

## Purpose

This package adds the missing operational layer above the existing Bridge Core model runtime.

The existing `TBridge` already performs header-only model execution:

```text
declare
step_model_once
step_model_report
run_model_to_terminal
```

The missing layer is not a `.cpp` runtime. The missing layer is a set of
header-level operational entities that distinguish:

```text
model-only bridge execution
model-plus-endpoint-invocation profile
execution report
readiness gate
run-mode compatibility
status transition legality
bounded run evidence
diagnostic collectors
static profile
```

## Core Rule

```text
TBridge remains the model runtime.
TBridgeStepExecutor becomes the operational entry surface.
TBridgeEndpointInvocation describes optional endpoint invocation.
Facade receives readiness/evidence, not mutable bridge internals.
```
