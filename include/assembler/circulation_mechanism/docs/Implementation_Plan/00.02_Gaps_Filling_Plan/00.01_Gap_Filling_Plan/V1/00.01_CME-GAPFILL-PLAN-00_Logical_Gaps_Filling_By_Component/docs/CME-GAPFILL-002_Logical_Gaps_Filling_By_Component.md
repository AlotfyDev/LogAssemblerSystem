# CME-GAPFILL-002 — Logical Gaps Filling By Component


## 1. ReferencePrecalculator `reference_precalculator`

- Total mapped gaps: **10**
- New subcomponents required: **7**
- Existing subcomponent updates: **3**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `locating_engine` — 4 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `supply` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `handles` — 2 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`
- `reference_pool` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `validity` — 1 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-006` reference calculation → `locating_engine` (P1-core)
- `CME-DGAP-024` reference supply → `supply` (P1-core)
- `CME-DGAP-040` ReferencePrecalculator algorithm → `supply` (P1-core)
- `CME-DGAP-041` container/slot locating → `locating_engine` (P1-core)
- `CME-DGAP-044` actual locating algorithm → `locating_engine` (P1-core)
- `CME-DGAP-045` actual reference pool → `reference_pool` (P1-core)
- `CME-DGAP-048` slot selection → `locating_engine` (P1-core)
- `CME-DGAP-049` TIngressAccessRef production → `handles` (P1-core)
- `CME-DGAP-050` TDispatchAccessRef production → `handles` (P1-core)
- `CME-DGAP-064` reference invalidation execution → `validity` (P1-core)

## 2. Container Registry `container_registry`

- Total mapped gaps: **6**
- New subcomponents required: **6**
- Existing subcomponent updates: **0**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `resolution` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `core` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `rebuild` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `diagnostic_inspection` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `mutation_policy` — 1 gap(s), status: `new_subcomponent_required`, action: `create_policy_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-003` registry behavior → `resolution` (P1-core)
- `CME-DGAP-019` container registry → `core` (P1-core)
- `CME-DGAP-032` registry rebuild algorithm → `rebuild` (P1-core)
- `CME-DGAP-047` container registry resolution → `resolution` (P1-core)
- `CME-DGAP-059` container scan → `diagnostic_inspection` (P3-review)
- `CME-DGAP-067` registry mutation → `mutation_policy` (P1-core)

## 3. Communication Binding `communication_binding`

- Total mapped gaps: **14**
- New subcomponents required: **7**
- Existing subcomponent updates: **7**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `bridge_facing_boundary` — 5 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `dispatch_output` — 3 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`
- `ingress` — 3 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`
- `exposure_contracts` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `views` — 1 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-011` bridge bindings → `dispatch_output` (P2-review)
- `CME-DGAP-025` bridge drain handling → `views` (P3-deferred)
- `CME-DGAP-037` bridge handoff → `dispatch_output` (P3-deferred)
- `CME-DGAP-042` bridge protocol → `bridge_facing_boundary` (P3-deferred)
- `CME-DGAP-053` Log API envelope assembly → `ingress` (P3-deferred)
- `CME-DGAP-054` payload parsing → `ingress` (P3-deferred)
- `CME-DGAP-066` bridge acknowledgement → `bridge_facing_boundary` (P3-deferred)
- `CME-DGAP-069` bridge recovery → `bridge_facing_boundary` (P3-deferred)
- `CME-DGAP-071` actual adapter invocation → `dispatch_output` (P3-review)
- `CME-DGAP-072` Log API runtime → `ingress` (P3-deferred)
- `CME-DGAP-073` Bridge Orchestrator runtime → `bridge_facing_boundary` (P3-deferred)
- `CME-DGAP-074` bridge sessions/protocols → `bridge_facing_boundary` (P3-deferred)
- `CME-DGAP-075` payload movement → `exposure_contracts` (P3-review)
- `CME-DGAP-076` mutable container exposure → `exposure_contracts` (P3-review)

## 4. Slot `slot`

- Total mapped gaps: **5**
- New subcomponents required: **5**
- Existing subcomponent updates: **0**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `payload_residency` — 4 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `mutation_policy` — 1 gap(s), status: `new_subcomponent_required`, action: `create_policy_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-002` slot storage → `payload_residency` (P1-core)
- `CME-DGAP-027` slot storage array → `payload_residency` (P1-core)
- `CME-DGAP-028` actual envelope payload storage → `payload_residency` (P1-core)
- `CME-DGAP-051` actual slot mutation → `mutation_policy` (P3-review)
- `CME-DGAP-052` payload storage → `payload_residency` (P1-core)

## 5. Dispatcher `dispatcher`

- Total mapped gaps: **5**
- New subcomponents required: **4**
- Existing subcomponent updates: **1**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `exposure_execution` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `output_contract` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `profiles` — 1 gap(s), status: `existing_subcomponent`, action: `update_existing_subcomponent`
- `release_policy` — 1 gap(s), status: `new_subcomponent_required`, action: `create_policy_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-008` dispatch exposure → `exposure_execution` (P1-core)
- `CME-DGAP-043` copy/move semantics → `output_contract` (P3-deferred)
- `CME-DGAP-055` dispatch behavior → `exposure_execution` (P1-core)
- `CME-DGAP-058` push dispatch execution → `profiles` (P1-core)
- `CME-DGAP-060` dispatch release/recycle → `release_policy` (P1-core)

## 6. Waiting List `waiting_list`

- Total mapped gaps: **5**
- New subcomponents required: **5**
- Existing subcomponent updates: **0**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `membership_lifecycle` — 3 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `ordering_policy` — 1 gap(s), status: `new_subcomponent_required`, action: `create_policy_subcomponent`
- `anti_collapse_guards` — 1 gap(s), status: `new_subcomponent_required`, action: `create_guard_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-004` waiting lists → `ordering_policy` (P2-core-support)
- `CME-DGAP-036` waiting-list admission → `membership_lifecycle` (P2-core-support)
- `CME-DGAP-038` envelope storage in waiting lists → `anti_collapse_guards` (P0-guard)
- `CME-DGAP-046` waiting-list consumption → `membership_lifecycle` (P2-core-support)
- `CME-DGAP-068` waiting-list rebuild → `membership_lifecycle` (P2-core-support)

## 7. ReadSide_Circulation_Profile `read_side_circulation_profile`

- Total mapped gaps: **7**
- New subcomponents required: **7**
- Existing subcomponent updates: **0**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `receiver_lifecycle` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `persistence_boundary` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `profile_core` — 1 gap(s), status: `new_subcomponent_required`, action: `create_profile_subcomponent`
- `backpressure` — 1 gap(s), status: `new_subcomponent_required`, action: `create_profile_subcomponent`
- `retry` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-012` read-side profile → `profile_core` (P3-deferred)
- `CME-DGAP-026` read-side backpressure → `backpressure` (P3-deferred)
- `CME-DGAP-056` read-side lifecycle → `receiver_lifecycle` (P3-deferred)
- `CME-DGAP-057` receiver lifecycle → `receiver_lifecycle` (P3-deferred)
- `CME-DGAP-061` persistence → `persistence_boundary` (P3-deferred)
- `CME-DGAP-062` read-side retry → `retry` (P3-deferred)
- `CME-DGAP-070` persistence deletion → `persistence_boundary` (P3-deferred)

## 8. Diagnostics `diagnostics`

- Total mapped gaps: **4**
- New subcomponents required: **4**
- Existing subcomponent updates: **0**
- Sequence band: **A-foundational**

### 2.x.1 New / Target Subcomponents

- `export_adapters` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `collector` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `recovery_classification` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-015` diagnostic storage → `collector` (P2-core-support)
- `CME-DGAP-016` logging → `export_adapters` (P3-review)
- `CME-DGAP-017` telemetry export → `export_adapters` (P3-review)
- `CME-DGAP-018` recovery behavior → `recovery_classification` (P2-review)

## 9. Container `container`

- Total mapped gaps: **3**
- New subcomponents required: **3**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `storage_shape` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `creation_semantics` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `state_transitions` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-001` container storage → `storage_shape` (P1-core)
- `CME-DGAP-033` container creation semantics → `creation_semantics` (P3-review)
- `CME-DGAP-065` container mutation → `state_transitions` (P2-core-support)

## 10. Capacity `capacity`

- Total mapped gaps: **3**
- New subcomponents required: **3**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `horizontal_scaling` — 1 gap(s), status: `new_subcomponent_required`, action: `create_profile_subcomponent`
- `vertical_scaling` — 1 gap(s), status: `new_subcomponent_required`, action: `create_profile_subcomponent`
- `capacity_profiles` — 1 gap(s), status: `new_subcomponent_required`, action: `create_profile_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-020` actual horizontal scaling → `horizontal_scaling` (P2-core-support)
- `CME-DGAP-021` actual vertical scaling → `vertical_scaling` (P2-core-support)
- `CME-DGAP-031` dynamic scaling → `capacity_profiles` (P2-core-support)

## 11. Ingress `ingress`

- Total mapped gaps: **2**
- New subcomponents required: **2**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `placement_execution` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-007` ingress placement → `placement_execution` (P1-core)
- `CME-DGAP-029` ingress placement algorithm → `placement_execution` (P1-core)

## 12. Release / Recycle `release_recycle`

- Total mapped gaps: **3**
- New subcomponents required: **3**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `reset_recycle_execution` — 3 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-030` container reset → `reset_recycle_execution` (P2-core-support)
- `CME-DGAP-035` container reset algorithm → `reset_recycle_execution` (P2-core-support)
- `CME-DGAP-063` actual recycle algorithm → `reset_recycle_execution` (P2-core-support)

## 13. Safe Point `safe_point`

- Total mapped gaps: **2**
- New subcomponents required: **2**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `evaluation` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-009` safe-point algorithms → `evaluation` (P1-core)
- `CME-DGAP-022` safe-point execution → `evaluation` (P1-core)

## 14. Eviction `eviction`

- Total mapped gaps: **2**
- New subcomponents required: **2**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `eviction_execution` — 2 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-010` eviction → `eviction_execution` (P2-core-support)
- `CME-DGAP-023` eviction execution → `eviction_execution` (P2-core-support)

## 15. Round Manager `round_manager`

- Total mapped gaps: **2**
- New subcomponents required: **2**
- Existing subcomponent updates: **0**
- Sequence band: **B-core**

### 2.x.1 New / Target Subcomponents

- `membership` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`
- `round_policy` — 1 gap(s), status: `new_subcomponent_required`, action: `create_policy_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-005` round management → `membership` (P2-core-support)
- `CME-DGAP-039` dynamic scheduling → `round_policy` (P2-review)

## 16. Bundle Agent `bundle_agent`

- Total mapped gaps: **1**
- New subcomponents required: **1**
- Existing subcomponent updates: **0**
- Sequence band: **C-support**

### 2.x.1 New / Target Subcomponents

- `topology_scaling` — 1 gap(s), status: `new_subcomponent_required`, action: `create_new_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-034` bundle topology authority → `topology_scaling` (P2-core-support)

## 17. Reports `reports`

- Total mapped gaps: **1**
- New subcomponents required: **1**
- Existing subcomponent updates: **0**
- Sequence band: **C-support**

### 2.x.1 New / Target Subcomponents

- `component_specific_reports` — 1 gap(s), status: `new_subcomponent_required`, action: `create_report_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-014` component-specific reports → `component_specific_reports` (P2-core-support)

## 18. Views `views`

- Total mapped gaps: **1**
- New subcomponents required: **1**
- Existing subcomponent updates: **0**
- Sequence band: **C-support**

### 2.x.1 New / Target Subcomponents

- `component_specific_views` — 1 gap(s), status: `new_subcomponent_required`, action: `create_view_subcomponent`

### 2.x.2 Gaps

- `CME-DGAP-013` component-specific views → `component_specific_views` (P2-core-support)
