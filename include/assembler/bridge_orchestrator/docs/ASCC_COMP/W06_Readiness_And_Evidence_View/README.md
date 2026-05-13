# ASCC-COMP-W06 — Generic Readiness And Evidence View

## 1. Purpose

W06 introduces ASCC-level readiness and evidence aggregation surfaces.

It consumes the conceptual outputs of earlier waves:

```text
W03 -> participant capability evidence
W04 -> binding composition metadata evidence
W05 -> protocol requirement evidence
```

W06 does not execute protocols, sessions, bridge runtime, endpoints, pipeline composition, policy logic, LogAPI internals, CME internals, or ReadSide runtime.

## 2. Delivered Headers

```text
include/assembler/bridge_orchestrator/composability/readiness/TAsccReadinessStatus.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccEvidenceDimension.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccReadinessIssue.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccReadinessEvidenceRef.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccParticipantReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccBindingReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccProtocolReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccSessionReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccBridgeReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccCompositionReadinessView.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccReadinessReport.hpp
include/assembler/bridge_orchestrator/composability/readiness/TAsccReadinessSurface.hpp
```

## 3. Smoke Test

```text
include/assembler/bridge_orchestrator/tests/smoke-tests/ascc_comp_w06_readiness_evidence_smoke_test.cpp
```

The smoke test verifies:

```text
- participant readiness can pass and fail
- binding readiness can pass
- protocol readiness can pass
- required session readiness can pass
- required bridge readiness can pass
- composition readiness aggregates required dimensions
- readiness report counts ready evidence
- deferred issue does not fail core readiness
- required missing evidence fails core readiness
```

## 4. Boundary

W06 is an evidence/readiness projection layer only.

It does not own:

```text
endpoint invocation
protocol stepping
session lifecycle
bridge runtime
pipeline composition
policy execution
CME internals
LogAPI internals
ReadSide runtime
```

## 5. Next Wave

The next wave is:

```text
ASCC-COMP-W07_Core_Composable_Component_Readiness_Gate
```

W07 may consume W06 reports to decide whether ASCC core is ready as a composable component.
