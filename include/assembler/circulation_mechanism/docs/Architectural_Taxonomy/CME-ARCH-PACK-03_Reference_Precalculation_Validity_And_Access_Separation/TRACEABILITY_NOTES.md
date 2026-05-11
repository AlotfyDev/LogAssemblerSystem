# TRACEABILITY NOTES — CME-ARCH-PACK-03

## 1. Source Basis

This package builds on:

- CME holistic foundation.
- Core component coverage for `ReferencePrecalculator`.
- Waiting-list and round behavior from CME-ARCH-PACK-02.
- The architectural decision that the pre-bridge engine is single-producer / single-dispatcher.
- The decision that bridge-side copy/move semantics are outside the engine.

## 2. Preserved Rules

1. Locating/calculation is not access.
2. Access is not bridge delivery.
3. Ingress references and dispatch references are direction-specific.
4. ReferencePrecalculator does not inspect envelope content.
5. ReferencePrecalculator does not depend on bridge protocol.
6. Consumers see a next-ref rhythm, not container topology.

## 3. Terminology Mapping

| Term | Meaning |
|---|---|
| locating | selecting/resolving container and slot target |
| reference calculation | preparing a ref from registry index + state + round |
| access | using a valid reference to place or expose material |
| stale ref | once-valid ref used after scope loss |
| invalidation | active cancellation due to state/profile/safe-point change |
