# CME-ARCH-PACK-05 — Boundary Profiles And Pre-Bridge / Read-Side Separation

## 1. Package Identity

| Field | Value |
|---|---|
| Package ID | `CME-ARCH-PACK-05` |
| Package Name | Boundary Profiles And Pre-Bridge / Read-Side Separation |
| Domain | `circulation_mechanism` |
| Parent System | Log-Level Assembler System |
| Status | Architecture Specification Draft |
| Primary Focus | Dispatch output boundary, passive-pull profile, optional push profile, pre-bridge vs read-side separation |
| Implementation Direction | C++17, header-only-first, profile-driven, boundary-safe |

## 2. Package Purpose

This package prevents collapse between:

```text
Circulation Mechanism Engine
Bridge Orchestrator
Read-Side Circulation Profile
End Receiver / Add-on
```

It defines how the pre-bridge engine exposes dispatch-ready material without becoming:

1. bridge runtime,
2. bridge protocol executor,
3. receiver lifecycle owner,
4. persistence owner,
5. retry scheduler,
6. message broker.

## 3. Documents

```text
CME-ARCH-012_Dispatch_Output_Boundary_And_Passive_Pull_Profile.md
CME-ARCH-013_PreBridge_WriteSide_Profile_And_ReadSide_Profile_Separation.md
```

## 4. Diagrams

```text
diagrams/CME-ARCH-012_passive_pull_dispatch.mmd
diagrams/CME-ARCH-012_optional_push_dispatch.mmd
diagrams/CME-ARCH-013_prebridge_vs_readside_profiles.mmd
```

## 5. Package-Level Rules

### 5.1 Output Exposure Rule

```text
Dispatcher exposes dispatch-ready material.
It does not own bridge transfer or receiver-side lifecycle.
```

### 5.2 Passive Pull Default Rule

```text
Passive pull is the default output profile.
```

### 5.3 Optional Push Rule

```text
Push dispatch is optional and profile-bound.
It must not become the core identity of CME.
```

### 5.4 Profile Separation Rule

```text
Pre-bridge write-side circulation profile is not the same as read-side circulation profile.
```

### 5.5 Drain Assumption Rule

```text
Pre-bridge profile may assume bridge drain under configured conditions.
If the assumption fails, the responsibility should normally move to read-side profile modeling.
```
