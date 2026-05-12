# DUPLICATE_TYPE_RESOLUTION_REPORT — CME-PROD-HARDEN-W01

## 1. Resolved Duplicate / Shim Cases

| Case | Resolution |
|---|---|
| `eviction/TContainerTimeRange.hpp` | moved to compatibility; includes must target `container/TContainerTimeRange.hpp` |
| `eviction/views/TContainerTimeRangeView.hpp` | moved to compatibility; includes must target `container/TContainerTimeRangeView.hpp` |
| `safe_points/TSafePointState.hpp` | moved to compatibility; includes must target `state/TSafePointState.hpp` |
| root `read_side_circulation_profile_w01..w04.hpp` | moved to compatibility; new canonical root aggregate added |
| root `circulation_mechanism_w01..w14.hpp` | moved to compatibility legacy wave aggregates |

## 2. Compile Result

```text
canonical root headers checked: 22
status: passed
```

## 3. Compatibility Files Retained

```text
compatibility/legacy_read_side_aggregates/read_side_circulation_profile_w01.hpp
compatibility/legacy_read_side_aggregates/read_side_circulation_profile_w02.hpp
compatibility/legacy_read_side_aggregates/read_side_circulation_profile_w03.hpp
compatibility/legacy_read_side_aggregates/read_side_circulation_profile_w04.hpp
compatibility/legacy_type_shims/TContainerTimeRange.hpp
compatibility/legacy_type_shims/TContainerTimeRangeView.hpp
compatibility/legacy_type_shims/TSafePointState.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w01.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w02.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w03.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w04.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w05.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w06.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w07.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w08.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w09.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w10.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w11.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w12.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w13.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_w14.hpp
compatibility/legacy_wave_aggregates/circulation_mechanism_waiting_list.hpp
```
