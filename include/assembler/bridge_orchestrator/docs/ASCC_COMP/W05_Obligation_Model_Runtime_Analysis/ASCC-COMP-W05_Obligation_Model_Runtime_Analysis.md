# ASCC-COMP-W05 — Obligation Model Runtime Analysis

## 1. Purpose

This package corrects the architectural interpretation of:

```text
include/assembler/bridge_orchestrator/obligations/
```

The current obligation layer already contains static CRTP call-through facades:

```text
TPort
TPluginAdapter
```

Those are not merely descriptors. They can call derived adapter/port obligation methods.

However, they are still not the full obligation runtime.

The missing production layer is:

```text
obligation invocation context
obligation invocation policy
obligation invocation sequencing
obligation result/reporting
surface readiness evaluation
trait audit as readiness evidence
carrier-flow bridge
obligation runtime view
facade-safe obligation readiness/evidence
```

## 2. Correct Classification

```text
TPort / TPluginAdapter
    = static obligation call-through facades

TObligationSurfacePair
    = surface pair descriptor + readiness helper

TObligationReport
    = obligation evidence primitive

Missing:
    = obligation runtime orchestration and evidence layer
```

## 3. Runtime Rule

```text
Call-through method availability is not enough.

A production obligation runtime must decide:
    whether an obligation may be invoked,
    in what sequence,
    under which protocol/carrier/participant/binding context,
    how carrier flow is recorded,
    and what evidence/report is produced.
```

## 4. Relationship To Other Layers

```text
participants/
    provides role/capability and obligation-surface binding

bindings/
    provides obligation surface maps and concrete binding descriptors

bridge_carriers/
    provides carriers and carrier-flow runtime

protocols/
    provides protocol steps and carrier/participant/binding requirements

bridge_core/
    should invoke obligations only through explicit executor/runtime path

facade_layer/
    exposes readiness/evidence only
```

## 5. Closure

`obligations/` should evolve from static call-through contracts to:

```text
static obligation facades
+ obligation runtime
+ carrier-flow bridge
+ invocation reports
+ facade readiness/evidence
```
