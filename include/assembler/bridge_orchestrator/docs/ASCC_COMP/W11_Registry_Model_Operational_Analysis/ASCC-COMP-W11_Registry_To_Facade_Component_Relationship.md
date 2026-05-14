# ASCC-COMP-W11 — Registry To Facade And Component Relationship

## 1. Purpose

This document explains how ASCC registries relate to:

```text
facade_layer/
Pipeline Composer
component admission
component readiness
```

## 2. Registry Role

Registries store bounded declarations and evidence for ASCC model objects:

```text
channels
bindings
sessions
protocols
bridges
```

They should prove that something is declared, present, usable, suspended, retired, or missing.

They should not perform the operation represented by that model object.

## 3. Facade Role

Facade layer exposes controlled registry information to Pipeline Composer:

```text
Administrative facade:
    What catalogs exist?

Managerial facade:
    Are required declarations present and usable?

Consuming facade:
    Should not mutate registries directly.
```

## 4. Component Model Impact

ASCC as a composable component needs registry evidence for admission:

```text
required binding registered
required session registered/openable
required protocol registered/ready
required bridge registered/ready
```

A component readiness gate should consume registry readiness reports, not raw mutable registries.

## 5. Closure

Registries are internal bounded evidence stores. The facade supplies their component-facing projections.
