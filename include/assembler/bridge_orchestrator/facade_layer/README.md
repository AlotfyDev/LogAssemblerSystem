# ASCC Facade Layer

This root-level subdirectory defines the facade layer for the Bridge Orchestrator / Communication Context domain.

The facade layer is the public component-facing boundary that allows ASCC to be admitted, configured, managed, and consumed by a higher-level Pipeline Composer without exposing ASCC internals.

## Surface Families

```text
facade_layer/
├── common/
├── administrative/
├── managerial/
├── consuming/
└── TAsccFacadeLayer.hpp
```

## Administrative Surface

Administrative surface defines component identity, component descriptors, supported profile catalogs, capability catalogs, protocol catalogs, and binding profile catalogs.

It answers:

```text
What is this ASCC component?
What can it declare?
What profiles and protocols are available?
```

Administrative surface does not execute bridge operations.

## Managerial Surface

Managerial surface validates configuration, evaluates readiness, admits selected profiles, reports issues, and prepares the component for operation.

It answers:

```text
Can this configured ASCC component be admitted into a pipeline?
```

Managerial surface does not replace participant consumption.

## Consuming Surface

Consuming surface exposes operation entry points and operation results after administrative setup and managerial admission.

It answers:

```text
How does a participant or Pipeline Composer use the admitted ASCC component?
```

Consuming surface does not reconfigure administrative decisions.

## Policy Relation

Policy belongs primarily to the composition layer. ASCC exposes policy-realizable capabilities and admissible profiles; it does not own governance policy semantics directly.
