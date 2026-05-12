# ASCC-COMP-W01C — Registry Unification Decision

## 1. Decision

The ASCC registry layer must be treated as a core composability surface, not as a permanently optional side layer.

The current path name:

```text
registries/optional_registries/
```

is historical / wave-local terminology from W11.  It must not be interpreted as an architectural statement that registries are non-essential for a clean, stable, scalable, integrable ASCC component.

## 2. Reason

ASCC as a participant-neutral composable component needs registries for:

```text
channel declarations
binding declarations
session declarations
bridge protocol declarations
bridge declarations
registry snapshots
diagnostic evidence
pipeline-composer-readable state
```

This does not make ASCC a broker, service locator, dependency injection container, scheduler, or runtime owner.  It only means the registry surfaces are core catalog/evidence surfaces.

## 3. Current Reality

The current implemented logic lives under:

```text
registries/optional_registries/base/TBoundedRegistry.hpp
registries/optional_registries/entries/TRegistryEntry.hpp
registries/optional_registries/lookups/TRegistryLookupResult.hpp
registries/optional_registries/snapshots/TRegistrySnapshot.hpp
registries/optional_registries/status/TRegistryEntryStatus.hpp
registries/optional_registries/sets/TCommunicationContextRegistrySet.hpp
registries/optional_registries/typed/TChannelRegistry.hpp
registries/optional_registries/typed/TBindingRegistry.hpp
registries/optional_registries/typed/TSessionRegistry.hpp
registries/optional_registries/typed/TBridgeProtocolRegistry.hpp
registries/optional_registries/typed/TBridgeRegistry.hpp
```

The first-level registry folders currently exist but are empty or placeholder paths:

```text
registries/channel_registry/TChannelRegistry.hpp
registries/binding_registry/TBindingRegistry.hpp
registries/session_registry/TSessionRegistry.hpp
registries/protocol_registry/TProtocolRegistry.hpp
registries/participant_registry/TParticipantRegistry.hpp
registries/plugin_adapter_registry/TPluginAdapterRegistry.hpp
registries/port_registry/TPortRegistry.hpp
```

## 4. Migration Direction

The stable architectural namespace/folder direction should be:

```text
registries/base/
registries/entries/
registries/lookups/
registries/snapshots/
registries/status/
registries/sets/
registries/channel_registry/
registries/binding_registry/
registries/session_registry/
registries/bridge_protocol_registry/
registries/bridge_registry/
```

The existing `optional_registries` path should become a compatibility layer or be formally deprecated after migration, not the long-term canonical home.

## 5. Preservation Rule

No logic currently implemented under `optional_registries` may be lost.

Before any file move or replacement:

```text
1. compare the optional typed registry implementation;
2. copy or preserve its exact register/find/contains/snapshot behavior;
3. preserve capacity templates;
4. preserve bounded/static-friendly storage;
5. preserve non-broker / non-scheduler / non-service-locator boundaries;
6. add compatibility forwarding headers from optional paths to canonical paths, or vice versa, during transition.
```

## 6. Immediate W01C Implication

The existing W01C backlog entries that suggested simple forwarders from the first-level empty registry paths into `optional_registries/typed` are only a short-term compatibility option.

The preferred remediation is now:

```text
Phase 1: classify and compare all registry paths.
Phase 2: establish canonical first-level registry folders.
Phase 3: move or duplicate-preserve implemented logic into canonical folders.
Phase 4: turn optional_registries paths into compatibility forwarders.
Phase 5: update docs and smoke tests.
```

## 7. Non-Goals

This decision does not authorize:

```text
runtime service discovery
message broker behavior
endpoint invocation
pipeline composition decisions
policy execution
threading or scheduling behavior
```

Registries are core ASCC catalog/evidence structures, not runtime super-actors.
