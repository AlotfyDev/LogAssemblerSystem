# CME-ARCH-PACK-06 — Diagnostics, Reports, Views, And Invariant Evidence

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-06` |
| Package Name | Diagnostics, Reports, Views, And Invariant Evidence |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | Read-only projections, evidence reports, diagnostics, invariant violations, operational trace |
| Implementation Direction | C++17, header-only-first, state-rich, diagnostic-visible, view/report separated |

## 2. Package Purpose

This package defines the observability model of the Circulation Mechanism Engine.

It separates:

```text
View
    read-only current-state projection

Report
    evidence of action, transition, diagnostic, or invariant event

Diagnostic
    classified observation of abnormal condition or invariant break
```

The package ensures the engine can be inspected, tested, and diagnosed without exposing private mutable internals.

## 3. Documents

```text
CME-ARCH-014_Views_Reports_And_Read_Only_Projection_Model.md
CME-ARCH-015_Diagnostics_Invariant_Violations_And_Operational_Reports.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-014_view_report_classification.mmd
diagrams/CME-ARCH-015_diagnostic_event_flow.mmd
diagrams/CME-ARCH-015_invariant_violation_matrix.mmd
```

## 5. Package-Level Rules

### 5.1 View Rule

```text
A View is a safe read-only projection of current state or readiness.
A View must not expose mutable internals.
```

### 5.2 Report Rule

```text
A Report is evidence of an action, transition, diagnostic, or boundary event.
A Report must not imply ownership beyond its declared scope.
```

### 5.3 Diagnostic Rule

```text
Diagnostics classify invariant violations, profile failures, boundary assumption breaks, and operational anomalies.
Diagnostics are not hidden control flow.
```

### 5.4 Trace Rule

```text
Every meaningful state transition or invariant violation should be reportable.
```
