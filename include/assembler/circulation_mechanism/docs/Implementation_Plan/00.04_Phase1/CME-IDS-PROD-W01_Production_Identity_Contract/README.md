# CME-IDS-PROD-W01 — Production Identity Contract

## Purpose

Production-grade delivery of CME identity atoms.

## Delivered Headers

```text
include/assembler/circulation_mechanism/ids/
├── TBoundaryId.hpp
├── TContainerId.hpp
├── TContainerRegistryIndex.hpp
├── TIdentityAtomTraits.hpp
├── TReferenceId.hpp
├── TRoundId.hpp
└── TSlotIndex.hpp

include/assembler/circulation_mechanism/circulation_mechanism_ids.hpp
```

## Delivered Capabilities

```text
typed identity atoms
invalid value policy
invalid() factory
from_raw() factory
raw()
value_or()
is_valid()
explicit bool
comparison operators
locator traits
identity traits
std::hash specialization
one-based / zero-based helpers for locator atoms
negative compliance tests
```

## Explicit Non-Ownership

```text
No runtime storage
No mutation authority
No access permission
No bridge runtime
No receiver lifecycle
No persistence semantics
```
