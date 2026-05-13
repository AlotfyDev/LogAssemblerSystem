# ASCC-COMP-W02 — Implementation And CI Closure Report

## 1. Wave Identity

```text
Wave: ASCC-COMP-W02
Canonical Name: Core Composability Capability And Coverage Model
Status: Closed
```

## 2. Architectural Correction

W02 was closed under the capability-first framing:

```text
Capability / Requirement / Coverage = architectural model
Gap = derived development/reporting result
```

This means W02 does not use `gap` as the root architectural concept.  Gap reporting is allowed only as a derived view over missing or incomplete coverage.

## 3. Implemented Header Families

### 3.1 Capabilities

```text
composability/capabilities/TAsccComposableCapabilityId.hpp
composability/capabilities/TAsccComposableCapabilityKind.hpp
composability/capabilities/TAsccComposableCapability.hpp
composability/capabilities/TAsccComposableCapabilitySet.hpp
```

### 3.2 Requirements

```text
composability/requirements/TAsccRequirementKind.hpp
composability/requirements/TAsccRequirement.hpp
composability/requirements/TAsccRequirementSet.hpp
```

### 3.3 Coverage

```text
composability/coverage/TAsccCoverageState.hpp
composability/coverage/TAsccCoverageItem.hpp
composability/coverage/TAsccCoverageMatrix.hpp
```

### 3.4 Reports

```text
composability/reports/TAsccComposabilitySeverity.hpp
composability/reports/TAsccComposabilityIssue.hpp
composability/reports/TAsccComposabilityReport.hpp
```

### 3.5 Derived Gaps

```text
composability/gaps/TAsccCoverageGap.hpp
composability/gaps/TAsccCoverageGapReport.hpp
```

### 3.6 Aggregate Surface

```text
composability/TAsccComposabilitySurface.hpp
```

## 4. Smoke Test

```text
tests/smoke-tests/ascc_comp_w02_composability_coverage_smoke_test.cpp
```

The smoke test verifies:

```text
- capability creation and registration
- requirement creation and registration
- coverage item and matrix behavior
- deferred integration coverage does not block core readiness
- missing core coverage can derive a blocking gap report
- derived gap reporting is not the architectural source of truth
```

## 5. Compile Fix Applied

A compile failure was fixed in:

```text
composability/coverage/TAsccCoverageItem.hpp
```

Cause:

```text
Member functions named blocks_core_readiness() and is_deferred() hid namespace helper functions with the same names.
```

Fix:

```cpp
assembler::communication_context::blocks_core_readiness(state)
assembler::communication_context::is_deferred(state)
```

## 6. CI Evidence

Manual GitHub Actions run reported success after the compile fix:

```text
Commit: f669d10
Status: Success
```

A later manual action run also reported success:

```text
Commit: 3923ac9
Status: Success
```

## 7. Boundary Preserved

W02 did not implement:

```text
- participant capability set details
- binding composition metadata
- protocol carrier requirement model
- readiness/evidence views
- final readiness gate
- pipeline composer
- policy execution
- concrete integration packs
```

These remain assigned to later ASCC-COMP waves.

## 8. Closure Decision

```text
ASCC-COMP-W02 is closed.
```

W03 may consume the capability/requirement/coverage vocabulary introduced by W02.
