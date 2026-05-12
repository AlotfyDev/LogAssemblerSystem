# ASCC-COMP-W02 — Revised Implementation Map

## 1. Governing Correction

W02 must not use `gap` as the architectural root concept.

A gap is a development-time diagnostic conclusion.  It is produced by comparing required coverage against actual coverage.  It is not the foundation of ASCC composability architecture.

Therefore W02 is named and scoped as:

```text
ASCC-COMP-W02_Core_Composability_Capability_And_Coverage_Model
```

## 2. Functional Architecture Vocabulary

Primary W02 vocabulary:

```text
capability
coverage
requirement
surface
scope
classification
report
evidence
```

Derived vocabulary:

```text
gap = missing or incomplete coverage against a declared requirement
```

## 3. Folder Structure

W02 should introduce these functional folders:

```text
include/assembler/bridge_orchestrator/composability/
├── capabilities/
├── coverage/
├── requirements/
├── reports/
└── gaps/                 # derived/reporting only, optional in W02
```

## 4. Primary Header Set

### Capabilities

```text
composability/capabilities/TAsccComposableCapabilityId.hpp
composability/capabilities/TAsccComposableCapabilityKind.hpp
composability/capabilities/TAsccComposableCapability.hpp
composability/capabilities/TAsccComposableCapabilitySet.hpp
```

Purpose:

```text
Describe what ASCC can provide as a composable component without tying that
capability to a temporary development gap.
```

### Coverage

```text
composability/coverage/TAsccCoverageState.hpp
composability/coverage/TAsccCoverageItem.hpp
composability/coverage/TAsccCoverageMatrix.hpp
```

Purpose:

```text
Record whether a capability/requirement is covered, partially covered,
missing, intentionally deferred, or outside ASCC core.
```

### Requirements

```text
composability/requirements/TAsccRequirementKind.hpp
composability/requirements/TAsccRequirement.hpp
composability/requirements/TAsccRequirementSet.hpp
```

Purpose:

```text
Represent what a later composer, readiness gate, protocol, binding, or
integration pack requires from ASCC.
```

### Reports

```text
composability/reports/TAsccComposabilityReport.hpp
composability/reports/TAsccComposabilityIssue.hpp
composability/reports/TAsccComposabilitySeverity.hpp
```

Purpose:

```text
Report coverage and issue summaries without making issue/gap vocabulary the
core model.
```

### Surface

```text
composability/TAsccComposabilitySurface.hpp
```

Purpose:

```text
Aggregate include for W02 and availability marker.
```

## 5. Optional Derived Gap Reporting

If W02 includes a gap report, it should live under:

```text
composability/gaps/TAsccCoverageGap.hpp
composability/gaps/TAsccCoverageGapReport.hpp
```

Rule:

```text
Gap types must consume capability/coverage/requirement data. They must not be
the source of truth.
```

## 6. Example Conceptual Flow

```text
TAsccRequirement
    states that ASCC should expose a capability or surface

TAsccComposableCapability
    states that ASCC provides that capability

TAsccCoverageItem
    records coverage state between requirement and capability

TAsccComposabilityReport
    summarizes whether ASCC core is covered, partially covered, or blocked

TAsccCoverageGap
    optionally reports missing/incomplete coverage
```

## 7. Coverage States

Required coverage states:

```text
unknown
covered
partially_covered
missing
intentionally_deferred
deferred_to_integration
deferred_to_pipeline_composer
deferred_to_policy_layer
out_of_scope
```

## 8. Capability Kinds

Initial capability kinds should describe ASCC's functional roles:

```text
participant_identity
participant_role_classification
plugin_adapter_surface
port_surface
channel_topology
binding_declaration
session_lifecycle
protocol_model
carrier_vocabulary
registry_catalog
diagnostic_reporting
integration_boundary_surface
readiness_evidence
composition_metadata
```

## 9. Requirement Kinds

Initial requirement kinds should include:

```text
requires_participant_identity
requires_adapter_port_surfaces
requires_channel_binding_model
requires_session_protocol_model
requires_carrier_set
requires_registry_evidence
requires_diagnostic_evidence
requires_readiness_surface
requires_integration_boundary
requires_pipeline_composer_decision
```

## 10. Issue / Severity Model

Issue/severity belongs to reports, not to root architecture.

Suggested severity values:

```text
info
warning
blocking
critical
```

A blocked core readiness report means:

```text
An ASCC-owned capability required for composability is missing or invalid.
```

A deferred report means:

```text
The item belongs to ASCC-INT, PIPE-COMP, policy layer, or later ASCC-COMP wave.
```

## 11. Smoke Test

Add:

```text
include/assembler/bridge_orchestrator/tests/smoke-tests/ascc_comp_w02_composability_coverage_smoke_test.cpp
```

The smoke test should verify:

```text
1. capability id creation
2. capability kind helpers
3. requirement kind helpers
4. coverage item creation
5. coverage matrix add/count
6. report generation
7. missing core coverage blocks report
8. deferred integration coverage does not block core report
9. gap report, if present, is derived from coverage state
```

## 12. Boundary

W02 does not implement:

```text
participant capability set details
binding composition metadata
protocol carrier requirement model
readiness/evidence views
final readiness gate
pipeline composer
policy execution
integration packs
```

These belong to W03-W07 and later tracks.

## 13. Acceptance Criteria

W02 is accepted when:

```text
- all W02 headers compile;
- smoke test passes;
- no endpoint-domain includes are introduced;
- no dynamic container is required;
- coverage-first model is used;
- gap reporting is derived, not foundational;
- W03-W07 can consume the capability/coverage/requirement vocabulary.
```
