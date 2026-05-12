# ASCC-COMP-W01C — Registry Unification Report

## 1. Objective

Unify ASCC registry logic under the canonical `registries/` tree while preserving all behavior originally implemented under `registries/optional_registries/`.

## 2. Decision Applied

```text
registries = core ASCC composability/evidence surface
optional_registries = historical compatibility path
```

## 3. Canonical Files Added Or Filled

### Shared primitives

```text
registries/base/TBoundedRegistry.hpp
registries/entries/TRegistryEntry.hpp
registries/lookups/TRegistryLookupResult.hpp
registries/snapshots/TRegistrySnapshot.hpp
registries/status/TRegistryEntryStatus.hpp
```

### Typed registries

```text
registries/channel_registry/TChannelRegistry.hpp
registries/binding_registry/TBindingRegistry.hpp
registries/session_registry/TSessionRegistry.hpp
registries/bridge_protocol_registry/TBridgeProtocolRegistry.hpp
registries/bridge_registry/TBridgeRegistry.hpp
registries/sets/TCommunicationContextRegistrySet.hpp
```

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

The following first-level registry paths remain unresolved because no implemented typed counterpart exists in the previous optional layer:

```text
registries/participant_registry/TParticipantRegistry.hpp
registries/plugin_adapter_registry/TPluginAdapterRegistry.hpp
registries/port_registry/TPortRegistry.hpp
```

The following naming mismatch remains a manual decision:

```text
registries/protocol_registry/TProtocolRegistry.hpp
```

It may map to `TBridgeProtocolRegistry`, but the name mismatch should not be hidden by an automatic alias without an architecture decision.

## 7. Smoke Test

Added:

```text
tests/smoke-tests/ascc_comp_w01_registry_unification_smoke_test.cpp
```

The smoke test includes both canonical registry paths and historical optional paths to verify compatibility includes expose the canonical types.

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

## 9. Next Step

Run the ASCC header audit GitHub Action and compile the registry unification smoke test.  If compile passes, update the W01C backlog statuses for the completed registry items.
