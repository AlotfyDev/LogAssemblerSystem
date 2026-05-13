# ASCC-COMP-W05 — Protocol Capability And Carrier Requirement Model

## 1. Purpose

W05 introduces a header-only protocol requirement layer for the Bridge Orchestrator / Communication Context domain.

The wave lets a protocol declare, before execution:

```text
- required participant roles
- required carriers
- producer/consumer direction for each carrier
- required binding handoff style
- required binding cardinality
- bridge/session/protocol participation expectations
- match/report evidence for later readiness layers
```

## 2. Delivered Headers

```text
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolCarrierRequirement.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolBindingRequirement.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolRequirementSet.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolRequirementMatchResult.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolRequirementReport.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolRequirementSurface.hpp
```

Earlier W05 foundation files already present:

```text
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolCapabilityKind.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolRequirementKind.hpp
include/assembler/bridge_orchestrator/protocols/requirements/TProtocolParticipantRequirement.hpp
```

## 3. Delivered Smoke Test

```text
include/assembler/bridge_orchestrator/tests/smoke-tests/ascc_comp_w05_protocol_requirements_smoke_test.cpp
```

The smoke test validates:

```text
- envelope-placement requirement set is valid
- content provider and receiver provider participants are required
- carrier requirements are present
- binding requirement is present
- envelope placement requires bridge/session/protocol participation
- complete match report passes
- missing carrier report fails
- binding mismatch report fails
```

## 4. Boundary

W05 does not implement:

```text
- protocol execution
- bridge runtime
- session lifecycle
- endpoint invocation
- carrier movement
- pipeline composition
- policy execution
- CME internals
- LogAPI internals
- ReadSide runtime
```

W05 is a pre-execution requirement declaration and reporting layer only.

## 5. Relationship To Other Waves

```text
W03 -> participant carrier capabilities
W04 -> binding composition metadata
W05 -> protocol carrier/binding requirements
W06 -> generic readiness/evidence aggregation
W07 -> final ASCC composable component readiness gate
```
