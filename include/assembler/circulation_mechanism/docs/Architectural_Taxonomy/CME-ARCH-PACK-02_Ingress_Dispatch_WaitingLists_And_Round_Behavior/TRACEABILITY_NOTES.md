# TRACEABILITY NOTES — CME-ARCH-PACK-02

## 1. Source Basis

This package builds on the agreed circulation taxonomy and high-value models:

- Core actors and structures: BundleAgent, Moderator, Registry, Container, Slot, WaitingLists, RoundManager, ReferencePrecalculator, Ingress, Dispatcher.
- High-value models: reference validity, safe points, release/recycle, views/reports, passive pull dispatch, pre-bridge vs read-side profiles, eviction by time range.
- Boundary rule: pre-bridge circulation is not bridge runtime, not read-side receiver lifecycle, not message broker.

## 2. Key Preserved Decisions

1. Ingress direction is outside → engine.
2. Dispatch direction is engine → outside.
3. Waiting lists store container registry indices, not envelopes.
4. RoundManager admits candidates based on state/readiness.
5. ReferencePrecalculator owns locating/reference calculation.
6. Ingress and Dispatcher consume references; they do not locate.
7. Dispatcher exposes by passive pull default.
8. Bridge-side contract owns copy/move semantics.

## 3. Terms Mapped From Earlier Vocabulary

| Earlier / Legacy | Current |
|---|---|
| Writing / Feeding Round | Ingress / Container-Providing Round |
| Delivery Round | Dispatch Round |
| Queue Container | TContainer |
| Queue Container Identifier | TContainerRegistryIndex or TContainerId depending context |
| Write-side | Pre-bridge circulation profile |
