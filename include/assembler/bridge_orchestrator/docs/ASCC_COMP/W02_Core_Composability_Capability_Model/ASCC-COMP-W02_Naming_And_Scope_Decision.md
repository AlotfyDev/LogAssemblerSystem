# ASCC-COMP-W02 — Naming And Scope Decision

## 1. Decision

ASCC-COMP-W02 must not be architected around the word `gap` as the primary domain concept.

A gap is a development-time diagnostic report produced by comparing desired composability coverage against current implementation coverage. It is not the architectural foundation of the component.

## 2. Correct Architectural Framing

The wave should be reframed from:

```text
ASCC-COMP-W02_Core_Type_And_Capability_Gap_Model
```

to:

```text
ASCC-COMP-W02_Core_Composability_Capability_And_Coverage_Model
```

The primary architectural vocabulary should be:

```text
capability
coverage
requirement
scope
surface
readiness
classification
report
```

The gap vocabulary remains available only as an audit/reporting layer:

```text
gap = missing or incomplete coverage against declared requirements
```

## 3. Functional Role Of W02

W02 should define the typed vocabulary that allows ASCC to describe itself as a clean, stable, scalable, integrable, participant-neutral component.

It should describe what ASCC can expose to later layers:

```text
- component capability categories
- coverage state
- requirement categories
- composability surface categories
- ownership/non-ownership classification
- deferred-layer classification
- report/evidence records
```

## 4. What W02 Must Not Do

W02 must not become a list of complaints about the codebase.

It must not encode temporary development backlog as the core model.

It must not force implementation decisions that belong to later waves:

```text
ASCC-COMP-W03 participant capability set
ASCC-COMP-W04 binding composition metadata
ASCC-COMP-W05 protocol requirement model
ASCC-COMP-W06 readiness/evidence views
ASCC-COMP-W07 composable readiness gate
ASCC-INT concrete integration packs
PIPE-COMP pipeline composition profiles
```

## 5. Revised File Family Direction

Instead of placing the primary files under only:

```text
composability/gaps/
```

W02 should use a functional structure such as:

```text
composability/capabilities/
composability/coverage/
composability/requirements/
composability/reports/
```

A `gaps/` folder may exist only as a derived reporting surface, not as the root of the wave.

## 6. Revised Core Types

Primary types should be renamed toward functional meaning:

```text
TAsccComposableCapabilityId
TAsccComposableCapabilityKind
TAsccCoverageState
TAsccRequirementKind
TAsccComposableCoverageItem
TAsccComposableCoverageMatrix
TAsccComposableCoverageReport
TAsccComposabilitySurface
```

Optional derived diagnostic types may be added later:

```text
TAsccCoverageGap
TAsccCoverageGapReport
```

## 7. Consequence

W02 becomes the foundation for composability capability coverage.

Gap reports become one use of that foundation, not the architecture itself.
