# CME-W15 — Integrated Smoke And Negative Compliance Suite

## 1. Wave Identity

| Field | Value |
|---|---|
| Wave ID | `CME-W15` |
| Wave Name | Integrated Smoke And Negative Compliance Suite |
| Domain | `circulation_mechanism` |
| Implementation Style | C++17, header-only-first test/compliance wave |
| Status | Integration / Compliance Skeleton |
| Purpose | Validate cross-wave integration and protect architecture anti-collapse rules across CME-W01 through CME-W14 |

## 2. What This Wave Implements

This wave introduces **tests and compliance documentation only**.

It does not add production headers.

It includes:

```text
tests/
  cme_w15_integrated_compile_smoke_test.cpp
  cme_w15_anti_collapse_compliance_test.cpp

docs/
  NEGATIVE_COMPLIANCE_CATALOG.md
  INTEGRATED_COVERAGE_MATRIX.md
```

## 3. What This Wave Verifies

```text
- Foundational IDs and states compile together.
- Capacity profiles compose with container and registry skeletons.
- BundleAgent and Moderator surfaces compile with registry/container types.
- Waiting lists and RoundManager preserve index-based candidate flow.
- Reference handles and ReferencePrecalculator surfaces compile together.
- Ingress and Dispatcher consume direction-specific reference shapes.
- Safe-point/release/recycle and eviction skeletons remain boundary-safe.
- Communication bindings reject mutable internal exposure.
```

## 4. What This Wave Does Not Implement

```text
actual container algorithms
actual reference calculation
actual ingress placement
actual dispatch exposure
actual bridge runtime
actual read-side retry
actual eviction execution
production diagnostics collector
```

## 5. Compliance Theme

This wave is designed to protect against category collapse:

```text
Container ≠ Broker
WaitingList ≠ EnvelopeStore
Reference ≠ RawPointer
Dispatcher ≠ Bridge
Report ≠ DownstreamProof
View ≠ MutableHandle
SafePoint ≠ GlobalStopTheWorld by default
EvictionProfile ≠ RetryEngine
```
