# TRACEABILITY NOTES — CME-ARCH-PACK-04

## 1. Source Basis

This package builds on:

- Core actor/container taxonomy.
- Waiting-list and round behavior.
- Reference validity and invalidation model.
- The decision that the engine is state-rich and single-writer/single-dispatcher in pre-bridge profile.
- The decision that reset, eviction, vertical scaling, profile switch, registry rebuild, and reference invalidation require safe points.

## 2. Preserved Decisions

1. Slot state is independent from container state.
2. Container state is independent from round state.
3. Safe points are local and profile-driven.
4. Release/recycle/reset are state transitions.
5. Moderator executes reset.
6. BundleAgent supplies default empty container profile.
7. Dispatch exposure does not prove final delivery.
8. Reentry makes a container eligible, not immediately used.

## 3. Cross-Pack Dependencies

| This Package | Depends On |
|---|---|
| State ownership | CME-ARCH-PACK-01 |
| Round state and closure | CME-ARCH-PACK-02 |
| Reference invalidation | CME-ARCH-PACK-03 |
| Dispatch exposure | CME-ARCH-PACK-02 / CME-ARCH-PACK-03 |
