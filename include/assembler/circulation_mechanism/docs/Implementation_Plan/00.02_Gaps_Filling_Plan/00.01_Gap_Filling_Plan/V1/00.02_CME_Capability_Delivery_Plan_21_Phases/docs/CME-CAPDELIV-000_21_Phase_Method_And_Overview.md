# CME-CAPDELIV-000 — 21-Phase Capability Delivery Plan

## 1. Purpose

This plan converts logical gaps into vertical component delivery phases.

The earlier implementation waves expanded horizontally across skeleton types.
This plan expands vertically inside each of the 21 parent components until each component reaches full production-functional coverage.

## 2. Method

```text
Component → mapped gaps → internal redistribution → new subcomponents first → existing updates second → review/deferred/guards → integration tests
```

## 3. Counts

```text
Parent components / phases: 21
Estimated delivery waves: 80
Proposed new subcomponent deliveries: 41
Components with no mapped gaps: 3
Components with new subcomponents: 18
```

## 4. Delivery Principle

```text
Create new subcomponents first.
Update existing subcomponents second.
Never silently implement deferred, external, or anti-collapse items as runtime behavior.
```

## 5. Main CSVs

```text
csv/CME-CAPDELIV-001_21_Component_Phases.csv
csv/CME-CAPDELIV-002_Waves_By_Component.csv
csv/CME-CAPDELIV-003_New_Subcomponents_By_Phase.csv
```
