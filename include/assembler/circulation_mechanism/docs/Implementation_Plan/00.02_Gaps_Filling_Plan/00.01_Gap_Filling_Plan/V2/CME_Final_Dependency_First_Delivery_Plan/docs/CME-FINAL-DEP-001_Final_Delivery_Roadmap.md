# CME-FINAL-DEP-001 — Final Dependency-First Delivery Roadmap


## 0. Vocabulary / Identity Foundations `CME-CL-00`

- Depends on: `none`
- Component count: **2**
- Wave count: **4**
- Components in order: `ids|state`
- Goal: Deliver identity atoms and state vocabularies required by all later components.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 1. Observation / Evidence Foundations `CME-CL-01`

- Depends on: `CME-CL-00`
- Component count: **3**
- Wave count: **11**
- Components in order: `reports|views|diagnostics`
- Goal: Deliver read-only projections, report/evidence carriers, and diagnostic taxonomy.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 2. Capacity / Safety Foundations `CME-CL-02`

- Depends on: `CME-CL-00|CME-CL-01`
- Component count: **2**
- Wave count: **7**
- Components in order: `safe_point|capacity`
- Goal: Deliver capacity envelopes, scaling profile vocabulary, and safe-point guards.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 3. Residency Structures `CME-CL-03`

- Depends on: `CME-CL-00|CME-CL-01|CME-CL-02`
- Component count: **3**
- Wave count: **15**
- Components in order: `container|container_registry|slot`
- Goal: Deliver slot/container residency structures and indexed container registry.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 4. Topology, Moderation, Waiting Lists, And Rounds `CME-CL-04`

- Depends on: `CME-CL-03`
- Component count: **4**
- Wave count: **12**
- Components in order: `waiting_list|round_manager|bundle_agent|moderator`
- Goal: Deliver container family topology, per-container moderation, eligibility lists, and round coordination.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 5. Reference And Movement Execution `CME-CL-05`

- Depends on: `CME-CL-04`
- Component count: **3**
- Wave count: **14**
- Components in order: `reference_precalculator|dispatcher|ingress`
- Goal: Deliver reference supply, ingress placement surface, and dispatch output exposure.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 6. Lifecycle, Eviction, And Boundary Contracts `CME-CL-06`

- Depends on: `CME-CL-05`
- Component count: **3**
- Wave count: **11**
- Components in order: `communication_binding|release_recycle|eviction`
- Goal: Deliver release/recycle, eviction behavior, and communication boundary contracts.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.

## 7. Post-Bridge / Read-Side Circulation Profile `CME-CL-07`

- Depends on: `CME-CL-06`
- Component count: **1**
- Wave count: **6**
- Components in order: `read_side_circulation_profile`
- Goal: Deliver post-bridge/read-side circulation profile, including retry, backpressure, delayed release, receiver/addon boundaries.
- Acceptance gate: All phases in cluster pass before dependent clusters start, unless explicitly marked safe-to-overlap.
