# ASCC-COMP-W07 — Compatibility To Binding, Session, Protocol, And Bridge Relationship

## 1. Compatibility To Binding

Current compatibility evaluates binding declarations through strict binding rules.

```text
TCompatibilityEvaluator
    -> TCompatibilityRuleSet
    -> TCompatibilityMatrix
    -> TCompatibilityView
```

## 2. Compatibility To Session

Session opening should consume compatibility readiness, not recompute all compatibility dimensions.

```text
TCompatibilityRuntimeReport
    -> TSessionOpenRequest
    -> TSession::open()
```

## 3. Compatibility To Protocol

Protocol admission should depend on compatibility across participants, bindings, carriers, and obligations.

```text
TAsccCompatibilityReadinessView
    -> TAsccProtocolAdmissionPolicy
```

## 4. Compatibility To Bridge Core

Bridge Core should consume ready protocol/session evidence, not raw compatibility internals.

## 5. Compatibility To Facade

Pipeline Composer consumes:

```text
TAsccCompatibilityCatalogView
TAsccCompatibilityReadinessView
TAsccCompatibilityAdmissionPolicy
```

It does not inspect compatibility rule internals directly.
