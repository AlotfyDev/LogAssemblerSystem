# ASCC-COMP-W01C — Registry Unification Report

## 1. Objective

Unify ASCC registry logic under the canonical `registries/` tree while preserving all behavior originally implemented under `registries/optional_registries/`.

## 2. Decision Applied

```text
registries = core ASCC composability/evidence surface
optional_registries = historical compatibility path
```

Registries remain bounded catalog/evidence structures. They are not service locators, brokers, schedulers, endpoint invokers, or pipeline composers.

## 3. Canonical Files Added Or Filled

### Shared primitives

```text
registries/base/TBoundedRegistry.hpp
registries/entries/TRegistryEntry.hpp
registries/lookups/TRegistryLookupResult.hpp
registries/snapshots/TRegistrySnapshot.hpp
registries/status/TRegistryEntryStatus.hpp
```

### Typed model registries

```text
registries/channel_registry/TChannelRegistry.hpp
registries/binding_registry/TBindingRegistry.hpp
registries/session_registry/TSessionRegistry.hpp
registries/bridge_protocol_registry/TBridgeProtocolRegistry.hpp
registries/bridge_registry/TBridgeRegistry.hpp
registries/sets/TCommunicationContextRegistrySet.hpp
```

### View / descriptor registries added in REG-02

```text
registries/participant_registry/TParticipantRegistry.hpp
registries/plugin_adapter_registry/TPluginAdapterRegistry.hpp
registries/port_registry/TPortRegistry.hpp
```

These are intentionally registries of bridge-visible descriptors/views:

```text
TParticipantRegistry        -> TParticipant descriptors
TPluginAdapterRegistry     -> TPluginAdapterView values
TPortRegistry              -> TPortView values
```

They do not own endpoint instances.

### Protocol registry alias added in REG-03

```text
registries/protocol_registry/TProtocolRegistry.hpp
```

`TProtocolRegistry<Capacity, PlanCapacity>` is an alias to:

```text
TBridgeProtocolRegistry<Capacity, PlanCapacity>
```

This preserves the generic historical/public path while keeping the precise canonical implementation name.

## 4. Compatibility Paths Converted

The following historical optional paths now forward to canonical registry files:

```text
registries/optional_registries/base/TBoundedRegistry.hpp
registries/optional_registries/entries/TRegistryEntry.hpp
registries/optional_registries/lookups/TRegistryLookupResult.hpp
registries/optional_registries/snapshots/TRegistrySnapshot.hpp
registries/optional_registries/status/TRegistryEntryStatus.hpp
registries/optional_registries/typed/TChannelRegistry.hpp
registries/optional_registries/typed/TBindingRegistry.hpp
registries/optional_registries/typed/TSessionRegistry.hpp
registries/optional_registries/typed/TBridgeProtocolRegistry.hpp
registries/optional_registries/typed/TBridgeRegistry.hpp
registries/optional_registries/sets/TCommunicationContextRegistrySet.hpp
```

## 5. Behavior Preserved

The following behavior was preserved from the previous typed registry layer:

```text
register/find/contains/snapshot helpers
capacity templates
bounded/static-friendly storage
rejected insertion count
registry snapshot evidence
non-broker / non-scheduler / non-service-locator boundary
```

## 6. Remaining Registry Decisions

No first-level registry header remains intentionally empty in the completed REG-02/REG-03 registry scope.

Open future work belongs outside W01C registry unification:

```text
- richer participant capability indexing belongs to ASCC-COMP-W03;
- binding-composition-aware lookup belongs to ASCC-COMP-W04;
- protocol-requirement-aware lookup belongs to ASCC-COMP-W05;
- readiness/evidence aggregation belongs to ASCC-COMP-W06/W07.
```

## 7. Smoke Test

Updated:

```text
tests/smoke-tests/ascc_comp_w01_registry_unification_smoke_test.cpp
```

The smoke test includes:

```text
- canonical shared registry primitives;
- canonical channel/binding/session/bridge-protocol/bridge registries;
- participant/plugin-adapter-view/port-view registries;
- TProtocolRegistry alias;
- historical optional_registries compatibility paths.
```

## 8. Non-Goals

This unification does not introduce:

```text
broker behavior
service locator behavior
scheduler / worker / async behavior
endpoint invocation
pipeline composition
policy execution
persistence / telemetry / ABI behavior
```

## 9. CI Follow-Up

The ASCC smoke-test workflow should compile and run:

```text
tests/smoke-tests/ascc_comp_w01_registry_unification_smoke_test.cpp
```

If the workflow fails, the failure should be treated as an include-graph or migration issue before proceeding to ASCC-COMP-W02.
