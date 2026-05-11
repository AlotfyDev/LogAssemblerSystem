# CME-DEP-001 — Inter-Component Dependency Findings


## IDs `ids`

- Is dependency: **true**
- Depended on by count: **17**
- Depended on by: `bundle_agent|capacity|communication_binding|container|container_registry|diagnostics|dispatcher|eviction|ingress|moderator|read_side_circulation_profile|reference_precalculator|release_recycle|round_manager|safe_point|slot|waiting_list`
- Is dependent: **false**
- Depends on count: **0**
- Depends on: `none`

## Reports `reports`

- Is dependency: **true**
- Depended on by count: **17**
- Depended on by: `bundle_agent|capacity|communication_binding|container|container_registry|diagnostics|dispatcher|eviction|ingress|moderator|read_side_circulation_profile|reference_precalculator|release_recycle|round_manager|safe_point|slot|waiting_list`
- Is dependent: **false**
- Depends on count: **0**
- Depends on: `none`

## Views `views`

- Is dependency: **true**
- Depended on by count: **17**
- Depended on by: `bundle_agent|capacity|communication_binding|container|container_registry|diagnostics|dispatcher|eviction|ingress|moderator|read_side_circulation_profile|reference_precalculator|release_recycle|round_manager|safe_point|slot|waiting_list`
- Is dependent: **false**
- Depends on count: **0**
- Depends on: `none`

## State `state`

- Is dependency: **true**
- Depended on by count: **16**
- Depended on by: `bundle_agent|communication_binding|container|container_registry|diagnostics|dispatcher|eviction|ingress|moderator|read_side_circulation_profile|reference_precalculator|release_recycle|round_manager|safe_point|slot|waiting_list`
- Is dependent: **false**
- Depends on count: **0**
- Depends on: `none`

## Container `container`

- Is dependency: **true**
- Depended on by count: **9**
- Depended on by: `bundle_agent|container_registry|eviction|moderator|read_side_circulation_profile|reference_precalculator|release_recycle|round_manager|waiting_list`
- Is dependent: **true**
- Depends on count: **6**
- Depends on: `capacity|ids|reports|slot|state|views`

## Container Registry `container_registry`

- Is dependency: **true**
- Depended on by count: **7**
- Depended on by: `bundle_agent|eviction|moderator|read_side_circulation_profile|reference_precalculator|round_manager|waiting_list`
- Is dependent: **true**
- Depends on count: **6**
- Depends on: `capacity|container|ids|reports|state|views`

## Safe Point `safe_point`

- Is dependency: **true**
- Depended on by count: **7**
- Depended on by: `bundle_agent|dispatcher|eviction|moderator|reference_precalculator|release_recycle|round_manager`
- Is dependent: **true**
- Depends on count: **4**
- Depends on: `ids|reports|state|views`

## Capacity `capacity`

- Is dependency: **true**
- Depended on by count: **6**
- Depended on by: `bundle_agent|container|container_registry|eviction|moderator|read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **3**
- Depends on: `ids|reports|views`

## Slot `slot`

- Is dependency: **true**
- Depended on by count: **5**
- Depended on by: `container|dispatcher|ingress|reference_precalculator|release_recycle`
- Is dependent: **true**
- Depends on count: **4**
- Depends on: `ids|reports|state|views`

## ReferencePrecalculator `reference_precalculator`

- Is dependency: **true**
- Depended on by count: **4**
- Depended on by: `dispatcher|eviction|ingress|release_recycle`
- Is dependent: **true**
- Depends on count: **10**
- Depends on: `container|container_registry|ids|reports|round_manager|safe_point|slot|state|views|waiting_list`

## Waiting List `waiting_list`

- Is dependency: **true**
- Depended on by count: **4**
- Depended on by: `eviction|read_side_circulation_profile|reference_precalculator|round_manager`
- Is dependent: **true**
- Depends on count: **6**
- Depends on: `container|container_registry|ids|reports|state|views`

## Communication Binding `communication_binding`

- Is dependency: **true**
- Depended on by count: **3**
- Depended on by: `dispatcher|ingress|read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **6**
- Depends on: `dispatcher|ids|ingress|reports|state|views`

## Release / Recycle `release_recycle`

- Is dependency: **true**
- Depended on by count: **3**
- Depended on by: `dispatcher|moderator|read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **8**
- Depends on: `container|ids|reference_precalculator|reports|safe_point|slot|state|views`

## Dispatcher `dispatcher`

- Is dependency: **true**
- Depended on by count: **2**
- Depended on by: `communication_binding|read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **9**
- Depends on: `communication_binding|ids|reference_precalculator|release_recycle|reports|safe_point|slot|state|views`

## Round Manager `round_manager`

- Is dependency: **true**
- Depended on by count: **2**
- Depended on by: `read_side_circulation_profile|reference_precalculator`
- Is dependent: **true**
- Depends on count: **8**
- Depends on: `container|container_registry|ids|reports|safe_point|state|views|waiting_list`

## Diagnostics `diagnostics`

- Is dependency: **true**
- Depended on by count: **1**
- Depended on by: `read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **4**
- Depends on: `ids|reports|state|views`

## Eviction `eviction`

- Is dependency: **true**
- Depended on by count: **1**
- Depended on by: `read_side_circulation_profile`
- Is dependent: **true**
- Depends on count: **10**
- Depends on: `capacity|container|container_registry|ids|reference_precalculator|reports|safe_point|state|views|waiting_list`

## Ingress `ingress`

- Is dependency: **true**
- Depended on by count: **1**
- Depended on by: `communication_binding`
- Is dependent: **true**
- Depends on count: **7**
- Depends on: `communication_binding|ids|reference_precalculator|reports|slot|state|views`

## Bundle Agent `bundle_agent`

- Is dependency: **false**
- Depended on by count: **0**
- Depended on by: `none`
- Is dependent: **true**
- Depends on count: **8**
- Depends on: `capacity|container|container_registry|ids|reports|safe_point|state|views`

## Moderator `moderator`

- Is dependency: **false**
- Depended on by count: **0**
- Depended on by: `none`
- Is dependent: **true**
- Depends on count: **9**
- Depends on: `capacity|container|container_registry|ids|release_recycle|reports|safe_point|state|views`

## ReadSide Circulation Profile `read_side_circulation_profile`

- Is dependency: **false**
- Depended on by count: **0**
- Depended on by: `none`
- Is dependent: **true**
- Depends on count: **14**
- Depends on: `capacity|communication_binding|container|container_registry|diagnostics|dispatcher|eviction|ids|release_recycle|reports|round_manager|state|views|waiting_list`
