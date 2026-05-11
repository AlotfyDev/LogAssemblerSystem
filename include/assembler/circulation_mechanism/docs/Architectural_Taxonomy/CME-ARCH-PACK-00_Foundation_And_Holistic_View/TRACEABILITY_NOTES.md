# TRACEABILITY NOTES — CME-ARCH-PACK-00

## 1. Source Basis

This pack is derived from the current conversation's stabilized architecture for the Circulation Mechanism Engine and from previously established architecture/glossary/file-system doctrines.

## 2. Key Prior Decisions Preserved

1. `write_side` legacy vocabulary maps to the current pre-bridge write-side circulation profile.
2. `Queue = Container`, not message broker.
3. The engine is envelope-aware but payload-content-blind.
4. Log-Level API produces envelopes; circulation receives and circulates them.
5. Circulation exposes toward bridge; it does not own bridge execution.
6. Read-side receiver delay/retry belongs to read-side profile, not the pre-bridge profile.
7. Reference precalculation separates locating from accessing.
8. Every active container is stored in a registry and referenced by index.
9. Containers have state independent of slot state.
10. Safe points gate reset, vertical scaling, eviction, and reference invalidation.

## 3. Future Trace Targets

Later packs should explicitly trace from this pack to:

- component specs,
- state machine specs,
- reference validity specs,
- safe-point specs,
- dispatch boundary specs,
- diagnostics/report specs,
- header derivation candidates.
