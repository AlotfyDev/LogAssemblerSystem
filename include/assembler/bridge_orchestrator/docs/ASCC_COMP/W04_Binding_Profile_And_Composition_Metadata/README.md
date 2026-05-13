# ASCC-COMP-W04 — Binding Profile And Composition Metadata

## Purpose

W04 adds composition metadata over binding declarations without modifying the existing `TBindingProfile` or executing bindings.

The wave answers:

```text
How should a binding be understood as a composition shape?
Is it direct or bridge-mediated?
Does it require protocol/session/bridge?
Does it preserve endpoint ownership boundaries?
Can it claim payload delivery?
```

## Delivered Surface

```text
bindings/composition/TBindingCardinality.hpp
bindings/composition/TBindingHandoffStyle.hpp
bindings/composition/TBindingExecutionAssumption.hpp
bindings/composition/TBindingOwnershipBoundary.hpp
bindings/composition/TBindingCompositionMetadata.hpp
bindings/composition/TBindingCompositionRequirement.hpp
bindings/composition/TBindingCompositionView.hpp
bindings/composition/TBindingCompositionReport.hpp
bindings/composition/TBindingCompositionSurface.hpp
```

## Smoke Test

```text
tests/smoke-tests/ascc_comp_w04_binding_composition_smoke_test.cpp
```
