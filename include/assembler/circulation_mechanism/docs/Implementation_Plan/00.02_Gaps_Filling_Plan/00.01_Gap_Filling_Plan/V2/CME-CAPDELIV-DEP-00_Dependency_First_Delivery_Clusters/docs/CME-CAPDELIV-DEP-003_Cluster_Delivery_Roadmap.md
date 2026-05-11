# CME-CAPDELIV-DEP-003 — Cluster Delivery Roadmap


## 0. Vocabulary / Identity Foundations `CME-CL-00`

- Components: `ids|state`
- Depends on: `none`
- Estimated component waves sum: **2**
- Goal: Deliver identity atoms and state vocabularies required by all later components.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 1. Observation / Evidence Foundations `CME-CL-01`

- Components: `reports|views|diagnostics`
- Depends on: `CME-CL-00`
- Estimated component waves sum: **11**
- Goal: Deliver read-only projections, report/evidence carriers, and diagnostic taxonomy.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 2. Capacity / Safety Foundations `CME-CL-02`

- Components: `safe_point|capacity`
- Depends on: `CME-CL-00|CME-CL-01`
- Estimated component waves sum: **7**
- Goal: Deliver capacity envelopes, scaling profile vocabulary, and safe-point guards.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 3. Residency Structures `CME-CL-03`

- Components: `container|container_registry|slot`
- Depends on: `CME-CL-00|CME-CL-01|CME-CL-02`
- Estimated component waves sum: **15**
- Goal: Deliver slot/container residency structures and indexed container registry.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 4. Topology, Moderation, Waiting Lists, And Rounds `CME-CL-04`

- Components: `waiting_list|round_manager|bundle_agent|moderator`
- Depends on: `CME-CL-03`
- Estimated component waves sum: **11**
- Goal: Deliver container family topology, per-container moderation, eligibility lists, and round coordination.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 5. Reference And Movement Execution `CME-CL-05`

- Components: `reference_precalculator|dispatcher|ingress`
- Depends on: `CME-CL-04`
- Estimated component waves sum: **14**
- Goal: Deliver reference supply, ingress placement surface, and dispatch output exposure.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 6. Lifecycle, Eviction, And Boundary Contracts `CME-CL-06`

- Components: `communication_binding|release_recycle|eviction`
- Depends on: `CME-CL-05`
- Estimated component waves sum: **11**
- Goal: Deliver release/recycle, eviction behavior, and communication boundary contracts.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.

## 7. Post-Bridge / Read-Side Circulation Profile `CME-CL-07`

- Components: `read_side_circulation_profile`
- Depends on: `CME-CL-06`
- Estimated component waves sum: **6**
- Goal: Deliver post-bridge/read-side circulation profile, including retry, backpressure, delayed release, receiver/addon boundaries.
- Acceptance gate: All components in cluster delivered or explicitly deferred with downstream-safe guards.
