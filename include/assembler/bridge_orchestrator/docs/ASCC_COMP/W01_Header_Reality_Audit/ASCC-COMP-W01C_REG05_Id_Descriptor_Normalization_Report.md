# ASCC-COMP-W01C-REG-05 — ID Types And Registry Normalization Report

## Objective

Correct the REG-02 implementation so participant, plugin-adapter, and port registries use first-class ID types and `TBoundedRegistry` instead of ad-hoc `uint64_t` arrays.

## Added ID Types

```text
participants/ids/TParticipantId.hpp
obligations/plugin_adapters/ids/TPluginAdapterId.hpp
obligations/ports/ids/TPortId.hpp
```

Each ID type provides:

```text
value
is_valid()
invalid()
from_value()
operator==
operator!=
```

## Added Descriptors

```text
obligations/plugin_adapters/descriptors/TPluginAdapterDescriptor.hpp
obligations/ports/descriptors/TPortDescriptor.hpp
```

The descriptor is now the registry subject. The view remains a read-only projection and is not removed.

```text
Descriptor = bridge-visible registry subject
View       = read-only projection
Concrete endpoint object = owned outside ASCC core
```

## Normalized Registries

```text
TParticipantRegistry
    TBoundedRegistry<TParticipantId, TParticipant, Capacity>

TPluginAdapterRegistry
    TBoundedRegistry<TPluginAdapterId, TPluginAdapterDescriptor, Capacity>

TPortRegistry
    TBoundedRegistry<TPortId, TPortDescriptor, Capacity>
```

## Boundary Preserved

These registries do not own endpoint objects and do not become service locators, brokers, schedulers, endpoint invokers, or pipeline composers.

## Smoke Test Update

`ascc_comp_w01_registry_unification_smoke_test.cpp` now checks the new ID types, descriptors, normalized registries, and `TProtocolRegistry` alias.
