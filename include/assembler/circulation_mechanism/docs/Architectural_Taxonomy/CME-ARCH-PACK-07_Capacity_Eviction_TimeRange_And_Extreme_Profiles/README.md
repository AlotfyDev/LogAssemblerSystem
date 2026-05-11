# CME-ARCH-PACK-07 — Capacity, Eviction, Time Range, And Extreme Profiles

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-07` |
| Package Name | Capacity, Eviction, Time Range, And Extreme Profiles |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | Capacity planning, uniform capacity, horizontal/vertical scaling, extreme defaults, time-range based eviction |
| Implementation Direction | C++17, header-only-first, capacity-profile-driven, safe-point guarded |

## 2. Package Purpose

This package specifies how the pre-bridge Circulation Mechanism Engine handles capacity and eviction without becoming a backpressure broker.

The package defines:

```text
TCirculationCapacityProfile
TUniformContainerCapacityProfile
horizontal scaling
vertical scaling
extreme default profile
pre-sized intake capacity
pre-sized dispatch capacity
TContainerTimeRange
TEvictionCandidate
OldestTimeRangeEviction
FifoContainerEviction
NoEvictionPreBridgeProfile
DelegateToReadSideProfile
EmergencyEvictionProfile
```

## 3. Documents

```text
CME-ARCH-016_Capacity_Profile_Extreme_Default_And_Scaling_Model.md
CME-ARCH-017_Eviction_By_Container_Time_Range_Model.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-016_capacity_profile_map.mmd
diagrams/CME-ARCH-016_scaling_safe_points.mmd
diagrams/CME-ARCH-017_eviction_decision_flow.mmd
```

## 5. Package-Level Rules

### 5.1 Capacity-First Rule

```text
Capacity is a profile-defined precondition, not an accidental runtime discovery.
```

### 5.2 Uniform Capacity Rule

```text
All active containers in a pre-bridge container family must share the same capacity and slot layout.
```

### 5.3 Extreme Default Rule

```text
The default pre-bridge profile favors pre-sized/extreme capacity sufficient for expected intake and dispatch.
```

### 5.4 No Broker Rule

```text
Capacity pressure does not turn the pre-bridge engine into a message broker, retry engine, or receiver-delay manager.
```

### 5.5 Eviction Safe-Point Rule

```text
Eviction may occur only when the selected container is not active in ingress,
not active in dispatch exposure, not used by a round, and all affected refs are consumed or invalidated.
```
