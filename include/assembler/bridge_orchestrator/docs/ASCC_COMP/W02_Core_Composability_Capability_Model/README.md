# ASCC-COMP-W02 — Core Composability Capability And Coverage Model

## Purpose

ASCC-COMP-W02 introduces a capability-first model for describing ASCC composability coverage.

This wave does not make “gap” the architectural root concept.  A gap is a derived development/reporting concept produced when coverage is missing or incomplete against declared requirements.

## Primary Vocabulary

```text
capability
requirement
coverage
report
evidence
derived gap
```

## Core Rule

```text
Capability and coverage are architecture.
Gap is a report.
```

## Delivered Areas

```text
composability/capabilities/
composability/requirements/
composability/coverage/
composability/reports/
composability/gaps/
composability/TAsccComposabilitySurface.hpp
```

## Smoke Test

```text
tests/smoke-tests/ascc_comp_w02_composability_coverage_smoke_test.cpp
```

The smoke test verifies that missing core coverage can derive a blocking gap report, while deferred integration coverage does not block core composability readiness.
