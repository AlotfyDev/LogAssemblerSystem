# TRACEABILITY NOTES — CME-ARCH-PACK-07

## 1. Source Basis

This package builds on:

- BundleAgent ownership of container family, uniform capacity, and scaling.
- Moderator reset/reinitialization responsibilities.
- TContainerRegistry indexed storage model.
- State and safe-point models.
- Reference validity and invalidation model.
- Pre-bridge vs read-side profile separation.

## 2. Preserved Decisions

1. All active containers are uniform in capacity and slot layout.
2. Vertical scaling is family-wide.
3. Capacity should be configured and pre-sized before hot path.
4. Extreme default profile is preferred for pre-bridge behavior.
5. Eviction is exceptional and safe-point guarded.
6. Time range is ordering metadata, not timestamp semantics ownership.
7. Receiver delay and retry mostly belong to read-side profile.
