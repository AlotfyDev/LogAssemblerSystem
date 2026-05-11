# DEFERRED_DECISIONS — CME-ARCH-PACK-01

| ID | Decision | Deferred Until | Reason |
|---:|---|---|---|
| CME-PACK01-DEF-001 | Final C++ class/type names | Header derivation pack | Current names are architectural working names |
| CME-PACK01-DEF-002 | Exact registry storage form | Implementation readiness | Could be fixed array, bounded vector, ring-like storage, or profile-sized block |
| CME-PACK01-DEF-003 | Whether `TContainerRef` is materialized | Reference model and header map | Registry index may be sufficient |
| CME-PACK01-DEF-004 | Exact slot state enum values | State machine pack | Current states are candidate semantics |
| CME-PACK01-DEF-005 | Whether waiting lists are template specializations or concrete types | Header derivation pack | Architectural distinction is stable; representation not final |
| CME-PACK01-DEF-006 | Whether time range is mandatory | Capacity/eviction pack | Required for time-range eviction, optional otherwise |
| CME-PACK01-DEF-007 | Whether eviction is disabled in pre-bridge profile | Capacity/eviction pack | Pre-bridge extreme profile may disable it by default |
| CME-PACK01-DEF-008 | Exact push dispatch profile support | Boundary profile pack | Passive pull remains default |
