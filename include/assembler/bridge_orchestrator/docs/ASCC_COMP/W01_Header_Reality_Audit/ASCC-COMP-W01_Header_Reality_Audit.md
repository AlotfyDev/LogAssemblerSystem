# ASCC-COMP-W01 — Header Reality Audit And Structural Cleanup

## 1. Objective

ASCC-COMP-W01 audits the existing W01-W15 Bridge Orchestrator / Communication Context component layers against the actual header tree and immediately fixes confirmed structural gaps.

This wave is code-first. Documentation is evidence; headers and compile smoke tests are the deliverables.

## 2. Architectural Position

ASCC core is treated as a participant-neutral composable component. It must not hard-code LogAPI, CME, ReadSide, policy execution, or pipeline composition decisions.

The Pipeline Composer may later decide how to use ASCC. ASCC itself must provide clean types, contracts, capabilities, profiles, requirements, readiness/evidence, and diagnostics.

## 3. Evidence Sources

The audit starts from the empirical layer evidence under:

```text
include/assembler/bridge_orchestrator/docs/SmokeTests_SystemView/
```

Those W01-W15 files document the observed smoke-test component layers and form the baseline inventory for later full audit expansion.

## 4. Confirmed Structural Gaps Closed In This Slice

| Gap ID | Header | Previous State | Remediation | Status |
|---|---|---|---|---|
| ASCC-COMP-W01-GAP-001 | `obligations/ports/contracts/TPort.hpp` | Empty public/canonical-looking header | Forward to implemented `obligations/ports/TPort.hpp` | Closed |
| ASCC-COMP-W01-GAP-002 | `bridge_core/orchestration/TBridge.hpp` | Empty public/canonical-looking header | Forward to implemented `bridge_core/TBridge.hpp` | Closed |

## 5. Cleanup Rule

An empty header is allowed only if it is a private placeholder not reachable as a public/canonical include. Otherwise it must be converted into one of:

```text
real implementation header
forwarding include
formal deprecated alias
removed path after compatibility decision
```

## 6. Deferred Audit Work

The full W01-W15 inventory pass remains open for expansion:

```text
- component/header existence matrix
- path drift matrix: bridge_orchestrator vs communication_context
- namespace consistency check
- aggregate include compile sweep
- smoke-test inventory reconciliation
```

## 7. Acceptance For This Slice

This slice is accepted if:

```text
1. both confirmed empty headers are non-empty;
2. both headers preserve the public include paths;
3. neither header defines duplicate core types;
4. both headers avoid endpoint-domain dependencies;
5. a smoke test includes both forwarding paths.
```
