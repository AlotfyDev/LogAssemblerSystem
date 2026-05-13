# ASCC-COMP-W04 — Implementation And CI Closure Report

## 1. Wave Identity

```text
Wave: ASCC-COMP-W04
Canonical Name: Binding Profile And Composition Metadata
Status: Closed
```

## 2. Purpose

W04 adds a composition metadata layer over binding declarations without modifying the existing `TBindingProfile` or turning ASCC into a pipeline composer.

The wave answers:

```text
How should a binding be understood as a composition shape?
Is it direct, bridge-mediated, passive-pull, push, hybrid, or diagnostic-only?
Does it require protocol/session/bridge participation?
Does it preserve endpoint ownership boundaries?
Can it claim payload delivery?
```

## 3. Architectural Boundary

W04 is descriptive metadata only.

It does not:

```text
- execute bindings
- materialize sessions
- step protocols
- invoke endpoints
- own endpoint internals
- decide pipeline policy
- implement carrier-level protocol requirements
```

The existing `TBindingProfile` remains untouched in this wave.

## 4. Implemented Header Families

### 4.1 Composition Vocabulary

```text
bindings/composition/TBindingCardinality.hpp
bindings/composition/TBindingHandoffStyle.hpp
bindings/composition/TBindingExecutionAssumption.hpp
bindings/composition/TBindingOwnershipBoundary.hpp
```

These headers define the core vocabulary for describing binding composition shape.

### 4.2 Composition Metadata

```text
bindings/composition/TBindingCompositionMetadata.hpp
```

This header introduces the central metadata record:

```text
TBindingCompositionMetadata
```

It includes:

```text
cardinality
handoff_style
execution_assumption
ownership_boundary
requires_protocol
requires_session
requires_bridge
allows_diagnostic_only
allows_payload_delivery_claim
version
metadata_name
```

It also provides presets:

```text
strict_static_one_to_one_bridge_mediated()
direct_single_writer_compatible()
passive_pull_bridge_mediated()
diagnostic_only()
```

### 4.3 Requirement, View, And Report

```text
bindings/composition/TBindingCompositionRequirement.hpp
bindings/composition/TBindingCompositionView.hpp
bindings/composition/TBindingCompositionReport.hpp
```

These types allow later readiness/evidence layers to compare composition metadata against a required binding shape.

### 4.4 Aggregate Surface

```text
bindings/composition/TBindingCompositionSurface.hpp
```

This aggregate surface exposes W04 as a compile-checkable unit.

## 5. Smoke Test

```text
tests/smoke-tests/ascc_comp_w04_binding_composition_smoke_test.cpp
```

The smoke test verifies:

```text
- bridge-mediated one-to-one metadata passes bridge-mediated requirement
- direct single-writer metadata does not require protocol/session/bridge
- passive-pull bridge-mediated metadata requires protocol/session/bridge
- diagnostic-only metadata does not claim payload delivery
- wrong handoff style fails the composition report
- view projection works from metadata
```

## 6. Compile Fix Applied

A compile failure was discovered in:

```text
bindings/composition/TBindingCompositionMetadata.hpp
```

Cause:

```text
Member function can_claim_payload_delivery() hid the namespace helper function can_claim_payload_delivery(TBindingHandoffStyle).
```

Fix:

```cpp
assembler::communication_context::can_claim_payload_delivery(handoff_style)
```

Fix commit:

```text
d8d192b2f140a18130b9aeea29ce9db48f7d6907
```

## 7. CI Evidence

Manual GitHub Actions run reported success after the fix:

```text
Commit: 717c56c
Status: Success
Total duration: 25s
Artifacts: 1
```

This confirms the W04 smoke test passed inside the ASCC smoke-test workflow.

## 8. Relationship To Previous Waves

W04 consumes the conceptual outputs of W03:

```text
Participant -> Role -> Capability -> Carrier -> Direction -> Protocol
```

W04 does not validate all carrier protocol requirements. It only records whether the binding shape expects protocol/session/bridge participation.

## 9. Relationship To Later Waves

W05 should consume W04 metadata and W03 participant carrier capabilities to define protocol capability and carrier requirements.

W06 and W07 should consume W04 views/reports as readiness and evidence inputs.

## 10. Closure Decision

```text
ASCC-COMP-W04 is closed.
```

The next wave may start:

```text
ASCC-COMP-W05_Protocol_Capability_And_Carrier_Requirement_Model
```
