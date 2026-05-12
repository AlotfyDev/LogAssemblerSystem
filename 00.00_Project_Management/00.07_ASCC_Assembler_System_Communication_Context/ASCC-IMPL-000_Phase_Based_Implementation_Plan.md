# ASCC-IMPL-000 — Phase-Based Implementation Plan

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASCC-IMPL-000-DOC-001 | Document Title | Phase-Based Implementation Plan |
| ASCC-IMPL-000-DOC-002 | File Name | `ASCC-IMPL-000_Phase_Based_Implementation_Plan.md` |
| ASCC-IMPL-000-DOC-003 | Documentation Pack | ASCC-IMPL — Assembler System Communication Context Realization Pack |
| ASCC-IMPL-000-DOC-004 | Formal Version | Formal Draft V1 |
| ASCC-IMPL-000-DOC-005 | Project | Assembler System |
| ASCC-IMPL-000-DOC-006 | Primary Language | English |
| ASCC-IMPL-000-DOC-007 | Scope Level | Implementation planning, phase ordering, file-fill waves, delivery packaging, validation gates |
| ASCC-IMPL-000-DOC-008 | Implementation Direction | C++17, header-only-first, templates, traits, CRTP-compatible abstractions, static-first contracts |
| ASCC-IMPL-000-DOC-009 | Status | Implementation Planning Draft |
| ASCC-IMPL-000-DOC-010 | Depends On | `ASCC-001` through `ASCC-007`, `ASCC_Communication_Context_Realization_Skeleton_V1.zip`, ASCC Realization Fill Plan |
| ASCC-IMPL-000-DOC-011 | Primary Rule | Dependency foundations must be implemented before abstractions that depend on them |
| ASCC-IMPL-000-DOC-012 | Delivery Rule | Smaller, accurate, dependency-safe packages are preferred over large, risky packages |
| ASCC-IMPL-000-DOC-013 | Non-Goal | This plan does not implement code; it governs the order and delivery structure for code implementation |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the phase-based implementation plan for the `communication_context/` domain of the Assembler System.

It converts the approved Communication Context architecture and filesystem skeleton into an ordered implementation path.

It answers the question:

```text
In what dependency-safe order should the Communication Context skeleton files
be filled, validated, packaged, and delivered so that implementation proceeds
from foundations to dependents without creating circular dependency,
semantic collapse, or endpoint leakage?
```

### 2.2 Why This Document Exists

The Communication Context is a root DDD implementation domain.

It owns bridge-mediated communication semantics, including bridge orchestration, channels, sessions, bindings, participants, abstract port obligations, abstract plugin-adapter obligations, carriers, protocols, protocol state, registries, diagnostics, compatibility, and integration-boundary abstractions.

Because this domain is highly central, implementation must not begin randomly.

Starting directly with `TBridge.hpp` would be incorrect because `TBridge` depends on more primitive layers:

1. carriers,
2. result and error categories,
3. protocol stages and state,
4. participants,
5. channels,
6. port and plugin-adapter obligations,
7. bindings,
8. compatibility,
9. sessions,
10. protocols.

This plan establishes a dependency-first implementation order.

### 2.3 Implementation Doctrine

The governing doctrine is:

```text
Fill dependency foundations first,
then fill the abstractions that depend on them,
then protocols,
then bridge orchestration,
then optional registries and diagnostics,
then integration boundaries,
then concrete domain-side bindings.
```

### 2.4 Delivery Doctrine

The delivery doctrine is:

```text
Each delivery package should be small enough to review accurately,
large enough to represent a coherent dependency layer,
and strict enough to avoid leaking future or endpoint-specific behavior into
abstract communication foundations.
```

Quality and correctness take priority over reducing the number of packages.

---

## 3. Scope

### 3.1 In Scope

This plan covers the implementation-fill order for:

1. `include/assembler/communication_context/`,
2. abstract bridge carriers,
3. bridge result and error categories,
4. protocol-state primitives,
5. participants and roles,
6. channel topology,
7. port obligations,
8. plugin-adapter obligations,
9. bindings,
10. compatibility,
11. sessions,
12. bridge protocols,
13. bridge core orchestration,
14. registries,
15. diagnostics,
16. integration boundary abstract ports,
17. concrete domain-side communication bindings for:
   1. `log_level_api/communication_bindings/`,
   2. `write_side/communication_bindings/`.

### 3.2 Explicitly Deferred Scope

The following are intentionally deferred:

1. full read-side extension implementation,
2. downstream database implementation,
3. OpenTelemetry SDK integration,
4. thin C ABI final export layer,
5. production-grade concurrency,
6. lock-free runtime structures,
7. CMake target finalization,
8. public package release,
9. performance benchmarking,
10. binary ABI commitment,
11. final downstream registry schema,
12. final persistence lifecycle.

### 3.3 First Implementation Target

The first target is not a complete runtime system.

The first target is:

```text
A coherent, compiling, header-only-first abstract Communication Context kernel
that defines the foundational types and contracts required to support the
primary envelope-placement protocol.
```

---

## 4. Global Implementation Rules

### 4.1 Header-Only-First Rule

All initial files should be written as header-only C++17-compatible headers unless a later formal decision introduces `.cpp` units.

The default shape is:

```cpp
#pragma once

namespace assembler::communication_context
{
    // implementation
}
```

### 4.2 Endpoint Non-Dependency Rule

Core files under `communication_context/` must not include endpoint-domain internals.

The following include directions are forbidden inside abstract Communication Context core:

```text
assembler/log_level_api/...
assembler/write_side/...
assembler/read_side/...
```

Concrete domain-side bindings may depend on their owning domain internals, but only outside the abstract `communication_context/` core.

### 4.3 Narrow Surface Rule

Each file should expose the narrowest meaningful abstraction.

A carrier file should not implement bridge orchestration.

A port obligation file should not implement host internals.

A plugin-adapter obligation file should not implement content-provider internals.

A protocol-state file should not implement endpoint state.

### 4.4 Static-First Rule

Where possible, compatibility and obligation models should support static-first interpretation through:

1. type aliases,
2. traits,
3. enum classes,
4. constexpr predicates,
5. CRTP-compatible contracts,
6. compile-time checks where appropriate.

### 4.5 Minimal Runtime Behavior Rule

Early phases should avoid complex runtime logic.

Initial implementation should focus on:

1. stable types,
2. value objects,
3. enum categories,
4. simple result wrappers,
5. traits defaults,
6. protocol stage declarations,
7. obligation surface shape,
8. non-owning handles,
9. clear compile-time dependency direction.

### 4.6 No Broker Rule

No phase may accidentally implement a broker, queue, scheduler, dispatcher, message bus, database, or downstream registry.

The Communication Context may define communication orchestration abstractions.

It must not become transport infrastructure or persistence infrastructure.

### 4.7 Opaque Handle Rule

Handles must avoid exposing endpoint-private state.

For example, `TPlacementHandle` may carry an opaque identifier or typed token, but it must not expose a `Slot*`, `RoundManager*`, `SlotsContainer*`, or other write-side internal object.

### 4.8 Validation-After-Each-Wave Rule

Each delivery wave must produce:

1. updated files,
2. package zip,
3. manifest,
4. changed-file list,
5. compile-intent notes,
6. dependency check notes,
7. deferred decisions list.

---

## 5. Phase Overview

| Phase | Name | Primary Purpose | Dependency Position |
|---:|---|---|---|
| 0 | Implementation Conventions | Establish coding conventions and guard rules | Before all files |
| 1 | Primitive Carrier Foundations | Define communication vocabulary primitives | First code layer |
| 2 | Protocol State Foundations | Define bridge-visible protocol state | After carriers/results/errors |
| 3 | Participant and Role Foundations | Define endpoint role descriptors | Before channels/bindings |
| 4 | Channel Foundations | Define topology and channel profiles | Before bindings/sessions |
| 5 | Obligation Contracts | Define `TPort` and `TPluginAdapter` abstract surfaces | After carriers and roles |
| 6 | Binding Model | Define adapter-port association | After channels and obligations |
| 7 | Compatibility Model | Define bridge-level compatibility checks | After channels/bindings/obligations |
| 8 | Session Model | Define one exchange instance | After channel, binding, carriers, state |
| 9 | Protocol Model | Define bridge protocols and envelope placement protocol | After sessions and state |
| 10 | Bridge Core | Define bridge orchestration | After all foundations |
| 11 | Registries | Define optional catalog layer | After core concepts |
| 12 | Diagnostics | Define bridge-visible diagnostic surfaces | After core concepts |
| 13 | Integration Boundaries | Define abstract boundary ports | After obligations/protocols |
| 14 | Concrete Domain-Side Bindings | Implement endpoint-specific adapters/ports | After abstract core |
| 15 | First Integration Skeleton | Compile-focused integration pass | After initial concrete bindings |

---

## 6. Phase 0 — Implementation Conventions

### 6.1 Purpose

Phase 0 establishes the rules that every implementation wave must follow.

### 6.2 Files Affected

No existing skeleton file must be filled during this phase unless a convention header is formally introduced.

### 6.3 Decisions

| Decision ID | Decision | Adopted Rule |
|---:|---|---|
| ASCC-IMPL-000-P0-D001 | Include guard style | `#pragma once` |
| ASCC-IMPL-000-P0-D002 | Namespace | `assembler::communication_context` |
| ASCC-IMPL-000-P0-D003 | C++ baseline | C++17 |
| ASCC-IMPL-000-P0-D004 | Default delivery style | Header-only-first |
| ASCC-IMPL-000-P0-D005 | Abstract prefix | `T*` |
| ASCC-IMPL-000-P0-D006 | Core endpoint dependency | Forbidden |
| ASCC-IMPL-000-P0-D007 | Concrete binding dependency | Allowed only in owning domain binding folders |
| ASCC-IMPL-000-P0-D008 | Runtime complexity | Avoided in foundation waves |

### 6.4 Exit Gate

Phase 0 is complete when:

1. namespace rule is stable,
2. include rule is stable,
3. no endpoint dependency rule is accepted,
4. delivery package naming convention is accepted,
5. first wave package format is accepted.

---

## 7. Phase 1 — Primitive Carrier Foundations

### 7.1 Purpose

Phase 1 establishes the basic bridge-visible communication vocabulary.

These files must not depend on bridge orchestration, ports, plugin adapters, sessions, or endpoint internals.

### 7.2 Target Files

| Order | File |
|---:|---|
| 1.1 | `bridge_carriers/correlation/TCorrelationToken.hpp` |
| 1.2 | `bridge_core/errors/TBridgeError.hpp` |
| 1.3 | `bridge_core/results/TBridgeResult.hpp` |
| 1.4 | `bridge_carriers/results/TBridgeCarrierResult.hpp` |
| 1.5 | `bridge_carriers/errors/TBridgeCarrierError.hpp` |
| 1.6 | `bridge_carriers/readiness/TReadinessView.hpp` |
| 1.7 | `bridge_carriers/admission/TAdmissionResult.hpp` |
| 1.8 | `bridge_carriers/signals/TLoadSignal.hpp` |
| 1.9 | `bridge_carriers/requests/TPlacementRequest.hpp` |
| 1.10 | `bridge_carriers/handles/TPlacementHandle.hpp` |
| 1.11 | `bridge_carriers/destination/TNextDestinationRequest.hpp` |
| 1.12 | `bridge_carriers/views/TCarrierView.hpp` |

### 7.3 Design Intent

Phase 1 should produce:

1. opaque correlation token,
2. bridge-level result category,
3. bridge-level error category,
4. carrier-level result category,
5. carrier-level error category,
6. readiness view,
7. admission result,
8. load signal,
9. placement request,
10. opaque placement handle,
11. next destination request,
12. minimal carrier view.

### 7.4 Constraints

Phase 1 must not introduce:

1. `TBridge`,
2. `TPort`,
3. `TPluginAdapter`,
4. `TSession`,
5. `TChannel`,
6. `TBinding`,
7. endpoint includes,
8. host-internal references,
9. dynamic registries,
10. dispatch logic.

### 7.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W01_Primitive_Carrier_Foundations.zip
```

### 7.6 Exit Gate

Phase 1 is complete when all primitive carrier files compile independently and contain no endpoint dependency.

---

## 8. Phase 2 — Protocol State Foundations

### 8.1 Purpose

Phase 2 establishes bridge-visible protocol progress and lifecycle state.

It does not define endpoint lifecycle.

### 8.2 Target Files

| Order | File |
|---:|---|
| 2.1 | `protocol_state/stages/TBridgeStage.hpp` |
| 2.2 | `protocol_state/terminal_states/TBridgeTerminalState.hpp` |
| 2.3 | `protocol_state/transitions/TBridgeTransition.hpp` |
| 2.4 | `protocol_state/snapshots/TBridgeProtocolSnapshot.hpp` |
| 2.5 | `protocol_state/lifecycle/TBridgeProtocolState.hpp` |

### 8.3 Design Intent

Phase 2 should produce:

1. bridge stage enum,
2. terminal state enum,
3. transition object,
4. protocol snapshot view,
5. protocol state object.

### 8.4 Constraints

Phase 2 must not expose:

1. write-side round state,
2. slot lifecycle state,
3. queue container internals,
4. content validation state,
5. persistence lifecycle,
6. telemetry SDK state.

### 8.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W02_Protocol_State_Foundations.zip
```

### 8.6 Exit Gate

Phase 2 is complete when protocol-state files depend only on primitive carriers and standard library types.

---

## 9. Phase 3 — Participant and Role Foundations

### 9.1 Purpose

Phase 3 defines communication participants without exposing endpoint internals.

### 9.2 Target Files

| Order | File |
|---:|---|
| 3.1 | `participants/roles/TParticipantRole.hpp` |
| 3.2 | `participants/descriptors/TParticipant.hpp` |
| 3.3 | `participants/views/TParticipantView.hpp` |

### 9.3 Design Intent

Phase 3 should represent:

1. content provider role,
2. host provider role,
3. receiver provider role,
4. boundary provider role,
5. observer role,
6. registry role,
7. participant identity,
8. participant view.

### 9.4 Constraints

Participants are descriptors.

They are not endpoint implementations.

### 9.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W03_Participant_And_Role_Foundations.zip
```

### 9.6 Exit Gate

Phase 3 is complete when participant descriptors can be used by channel and binding models without endpoint includes.

---

## 10. Phase 4 — Channel Foundations

### 10.1 Purpose

Phase 4 defines topology.

A channel is an allowed communication road.

A channel is not a runtime exchange.

### 10.2 Target Files

| Order | File |
|---:|---|
| 4.1 | `channels/profiles/TChannelProfile.hpp` |
| 4.2 | `channels/profiles/TSingleAdapterSinglePortProfile.hpp` |
| 4.3 | `channels/policies/TChannelBindingPolicy.hpp` |
| 4.4 | `channels/topology/TChannel.hpp` |

### 10.3 Design Intent

Phase 4 should produce:

1. channel profile vocabulary,
2. initial single-adapter/single-port profile,
3. channel binding policy,
4. channel topology object.

### 10.4 Constraints

Phase 4 must not implement:

1. session execution,
2. runtime routing,
3. brokers,
4. dynamic scheduling,
5. endpoint logic.

### 10.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W04_Channel_Foundations.zip
```

### 10.6 Exit Gate

Phase 4 is complete when a channel can describe topology without executing communication.

---

## 11. Phase 5 — Obligation Contracts

### 11.1 Purpose

Phase 5 defines the abstract bridge-facing obligation surfaces for host providers and content providers.

This is the central contract layer.

### 11.2 Target Files — Port Obligations

| Order | File |
|---:|---|
| 5.1 | `obligations/ports/traits/TPortTraits.hpp` |
| 5.2 | `obligations/ports/views/TPortView.hpp` |
| 5.3 | `obligations/ports/contracts/TPort.hpp` |

### 11.3 Target Files — Plugin Adapter Obligations

| Order | File |
|---:|---|
| 5.4 | `obligations/plugin_adapters/traits/TPluginAdapterTraits.hpp` |
| 5.5 | `obligations/plugin_adapters/views/TPluginAdapterView.hpp` |
| 5.6 | `obligations/plugin_adapters/contracts/TPluginAdapter.hpp` |

### 11.4 Design Intent

`TPort` should express host-side obligations such as:

1. identify port,
2. declare compatibility,
3. expose readiness,
4. admit, reject, or defer request,
5. produce opaque handle,
6. accept bridge-visible signal,
7. return bridge-visible result.

`TPluginAdapter` should express content-side obligations such as:

1. identify adapter,
2. declare compatibility,
3. prepare request,
4. expose or attach correlation,
5. interpret handle,
6. emit load/delivery signal,
7. interpret result or error.

### 11.5 Constraints

Phase 5 must not implement:

1. write-side placement internals,
2. log-level API content assembly internals,
3. validation behavior,
4. slot allocation,
5. round management,
6. persistence behavior.

### 11.6 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W05_Port_And_PluginAdapter_Obligations.zip
```

### 11.7 Exit Gate

Phase 5 is complete when the abstract endpoint-facing obligation surfaces exist and compile against carriers, participants, and channel profiles.

---

## 12. Phase 6 — Binding Model

### 12.1 Purpose

Phase 6 defines the association between plugin adapters and ports under a channel.

### 12.2 Target Files

| Order | File |
|---:|---|
| 6.1 | `bindings/binding_policies/TBindingPolicy.hpp` |
| 6.2 | `bindings/binding_results/TBindingResult.hpp` |
| 6.3 | `bindings/binding_views/TBindingView.hpp` |
| 6.4 | `bindings/adapter_port_bindings/TBinding.hpp` |

### 12.3 Skeleton Adjustment

`TBindingResult.hpp` should be added to the skeleton because binding can fail before session execution.

Recommended path:

```text
include/assembler/communication_context/bindings/binding_results/TBindingResult.hpp
```

### 12.4 Design Intent

Phase 6 should represent:

1. adapter-port association,
2. binding validity,
3. binding policy,
4. binding result,
5. binding view.

### 12.5 Constraints

Binding is association.

It must not become endpoint behavior.

### 12.6 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W06_Binding_Model.zip
```

### 12.7 Exit Gate

Phase 6 is complete when a binding can associate an adapter and a port under a channel without invoking either endpoint.

---

## 13. Phase 7 — Compatibility Model

### 13.1 Purpose

Phase 7 defines bridge-level compatibility.

### 13.2 Target Files

| Order | File |
|---:|---|
| 7.1 | `compatibility/traits/TCompatibilityTraits.hpp` |
| 7.2 | `compatibility/channel_compatibility/TChannelCompatibility.hpp` |
| 7.3 | `compatibility/protocol_compatibility/TProtocolCompatibility.hpp` |
| 7.4 | `compatibility/carrier_compatibility/TCarrierCompatibility.hpp` |
| 7.5 | `compatibility/binding_compatibility/TBindingCompatibility.hpp` |
| 7.6 | `compatibility/visibility_compatibility/TVisibilityCompatibility.hpp` |
| 7.7 | `compatibility/performance_compatibility/TPerformanceCompatibility.hpp` |
| 7.8 | `compatibility/ownership_compatibility/TOwnershipCompatibility.hpp` |

### 13.3 Design Intent

Compatibility should cover:

1. channel compatibility,
2. protocol compatibility,
3. carrier compatibility,
4. binding compatibility,
5. visibility compatibility,
6. performance compatibility,
7. ownership compatibility.

### 13.4 Constraints

Compatibility must not become endpoint validation.

It validates bridge-level relationships only.

### 13.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W07_Compatibility_Model.zip
```

### 13.6 Exit Gate

Phase 7 is complete when compatibility checks can be expressed without endpoint internals.

---

## 14. Phase 8 — Session Model

### 14.1 Purpose

Phase 8 defines a communication session.

A session is one execution exchange under a channel and binding.

It is not a web session.

It is not endpoint lifecycle.

### 14.2 Target Files

| Order | File |
|---:|---|
| 8.1 | `sessions/correlation/TSessionCorrelation.hpp` |
| 8.2 | `sessions/views/TSessionView.hpp` |
| 8.3 | `sessions/lifecycle/TSession.hpp` |

### 14.3 Design Intent

Phase 8 should represent:

1. session identity,
2. correlation,
3. channel reference,
4. binding reference,
5. protocol-state reference,
6. bridge-visible result,
7. safe session view.

### 14.4 Constraints

Session must not own:

1. round manager,
2. slot,
3. slot container,
4. endpoint lifecycle,
5. queue lifecycle,
6. persistence lifecycle.

### 14.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W08_Session_Model.zip
```

### 14.6 Exit Gate

Phase 8 is complete when a session can represent one communication exchange without endpoint ownership.

---

## 15. Phase 9 — Protocol Model

### 15.1 Purpose

Phase 9 defines bridge protocols and the first active protocol family.

### 15.2 Target Files — Core Protocol

| Order | File |
|---:|---|
| 9.1 | `protocols/common/TBridgeProtocolTraits.hpp` |
| 9.2 | `protocols/common/TBridgeProtocol.hpp` |

### 15.3 Target Files — Current Active Protocol

| Order | File |
|---:|---|
| 9.3 | `protocols/envelope_placement/TEnvelopePlacementProtocol.hpp` |

### 15.4 Deferred Protocol Files

The following should remain stubbed or minimally declared until their own extension waves:

1. `protocols/registry_delivery/TRegistryDeliveryProtocol.hpp`,
2. `protocols/receiver_delivery/TReceiverDeliveryProtocol.hpp`,
3. `protocols/persistence_delivery/TPersistenceDeliveryProtocol.hpp`,
4. `protocols/telemetry_export/TTelemetryExportProtocol.hpp`,
5. `protocols/thin_c_abi/TThinCAbiProtocol.hpp`,
6. `protocols/diagnostic_exchange/TDiagnosticExchangeProtocol.hpp`.

### 15.5 Design Intent

Phase 9 should define:

1. protocol traits,
2. protocol stage order,
3. protocol carrier requirements,
4. envelope placement protocol family.

### 15.6 Constraints

Protocols define orchestration shape.

They must not implement endpoint algorithms.

### 15.7 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W09_Bridge_Protocol_Model.zip
```

### 15.8 Exit Gate

Phase 9 is complete when the envelope placement protocol can reference carriers, state, session, channel, binding, port, and adapter obligations without endpoint internals.

---

## 16. Phase 10 — Bridge Core

### 16.1 Purpose

Phase 10 defines the bridge itself.

This phase comes late because the bridge orchestrates previously defined abstractions.

### 16.2 Target Files

| Order | File |
|---:|---|
| 10.1 | `bridge_core/traits/TBridgeTraits.hpp` |
| 10.2 | `bridge_core/orchestration/TBridge.hpp` |

### 16.3 Optional Later Bridge-Core Files

The following may remain deferred until the bridge execution model needs them:

1. files under `bridge_core/execution/`,
2. additional files under `bridge_core/detail/`,
3. advanced orchestration helpers.

### 16.4 Design Intent

`TBridge` should coordinate:

1. session,
2. channel,
3. binding,
4. compatibility,
5. protocol,
6. carriers,
7. port obligations,
8. plugin-adapter obligations,
9. bridge-visible result.

### 16.5 Constraints

`TBridge` must not:

1. validate content directly,
2. allocate slots directly,
3. call write-side internals directly,
4. own payload lifecycle,
5. own downstream persistence,
6. become a broker,
7. become a dispatcher.

### 16.6 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W10_Bridge_Core.zip
```

### 16.7 Exit Gate

Phase 10 is complete when `TBridge` can be instantiated or reasoned about in abstract form against the established protocol and obligation surfaces.

---

## 17. Phase 11 — Registries

### 17.1 Purpose

Phase 11 defines optional catalogs.

Registries are not required for the first one-to-one static profile but prepare future scaling.

### 17.2 Target Files

| Order | File |
|---:|---|
| 11.1 | `registries/channel_registry/TChannelRegistry.hpp` |
| 11.2 | `registries/participant_registry/TParticipantRegistry.hpp` |
| 11.3 | `registries/binding_registry/TBindingRegistry.hpp` |
| 11.4 | `registries/port_registry/TPortRegistry.hpp` |
| 11.5 | `registries/plugin_adapter_registry/TPluginAdapterRegistry.hpp` |
| 11.6 | `registries/session_registry/TSessionRegistry.hpp` |
| 11.7 | `registries/protocol_registry/TProtocolRegistry.hpp` |

### 17.3 Design Intent

Registries should catalog metadata.

They should not route messages.

### 17.4 Constraints

Registries must not become:

1. broker,
2. queue,
3. scheduler,
4. lifecycle owner,
5. dispatcher,
6. persistence engine.

### 17.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W11_Optional_Registries.zip
```

### 17.6 Exit Gate

Phase 11 is complete when registries are optional and non-invasive.

---

## 18. Phase 12 — Diagnostics

### 18.1 Purpose

Phase 12 defines bridge-visible diagnostics.

### 18.2 Target Files

| Order | File |
|---:|---|
| 12.1 | `diagnostics/channel_views/TChannelDiagnosticView.hpp` |
| 12.2 | `diagnostics/binding_views/TBindingDiagnosticView.hpp` |
| 12.3 | `diagnostics/session_views/TSessionDiagnosticView.hpp` |
| 12.4 | `diagnostics/carrier_snapshots/TCarrierSnapshot.hpp` |
| 12.5 | `diagnostics/protocol_snapshots/TProtocolSnapshot.hpp` |
| 12.6 | `diagnostics/error_views/TErrorDiagnosticView.hpp` |
| 12.7 | `diagnostics/timing_views/TTimingDiagnosticView.hpp` |

### 18.3 Design Intent

Diagnostics should expose safe views of communication context state.

### 18.4 Constraints

Diagnostics must not expose endpoint-private internals.

### 18.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W12_Diagnostics.zip
```

### 18.6 Exit Gate

Phase 12 is complete when diagnostic views can inspect bridge-visible material only.

---

## 19. Phase 13 — Integration Boundary Abstract Ports

### 19.1 Purpose

Phase 13 defines future-facing abstract boundary ports.

### 19.2 Target Files

| Order | File |
|---:|---|
| 13.1 | `integration_boundaries/in_process_receivers/TInProcessReceiverPort.hpp` |
| 13.2 | `integration_boundaries/persistence_ports/TPersistencePort.hpp` |
| 13.3 | `integration_boundaries/registry_delivery/TRegistryDeliveryPort.hpp` |
| 13.4 | `integration_boundaries/open_telemetry_ports/TOpenTelemetryPort.hpp` |
| 13.5 | `integration_boundaries/thin_c_abi_ports/TThinCAbiPort.hpp` |

### 19.3 Design Intent

These files should define abstract bridge-facing boundary obligations.

They should not implement actual external systems.

### 19.4 Constraints

Phase 13 must not own:

1. database schema,
2. OpenTelemetry SDK internals,
3. receiver application logic,
4. thin C ABI final memory model,
5. external transport.

### 19.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W13_Integration_Boundary_Abstract_Ports.zip
```

### 19.6 Exit Gate

Phase 13 is complete when boundary ports remain abstract and non-owning.

---

## 20. Phase 14 — Concrete Domain-Side Bindings

### 20.1 Purpose

Phase 14 implements concrete bindings outside the abstract `communication_context/` core.

These bindings may depend on owning domain internals.

### 20.2 Log Level API Binding Files

| Order | File |
|---:|---|
| 14.1 | `log_level_api/communication_bindings/envelope_plugin_adapter/traits/TLogLevelEnvelopePluginAdapterTraits.hpp` |
| 14.2 | `log_level_api/communication_bindings/envelope_plugin_adapter/views/TLogLevelEnvelopePluginAdapterView.hpp` |
| 14.3 | `log_level_api/communication_bindings/envelope_plugin_adapter/adapter/TLogLevelEnvelopePluginAdapter.hpp` |

### 20.3 Write Side Placement Port Files

| Order | File |
|---:|---|
| 14.4 | `write_side/communication_bindings/envelope_placement_port/traits/TWriteSideEnvelopePlacementPortTraits.hpp` |
| 14.5 | `write_side/communication_bindings/envelope_placement_port/views/TWriteSideEnvelopePlacementPortView.hpp` |
| 14.6 | `write_side/communication_bindings/envelope_placement_port/port/TWriteSideEnvelopePlacementPort.hpp` |

### 20.4 Write Side Registry Delivery Adapter Files

| Order | File |
|---:|---|
| 14.7 | `write_side/communication_bindings/registry_delivery_plugin_adapter/traits/TWriteSideRegistryDeliveryPluginAdapterTraits.hpp` |
| 14.8 | `write_side/communication_bindings/registry_delivery_plugin_adapter/views/TWriteSideRegistryDeliveryPluginAdapterView.hpp` |
| 14.9 | `write_side/communication_bindings/registry_delivery_plugin_adapter/adapter/TWriteSideRegistryDeliveryPluginAdapter.hpp` |

### 20.5 Design Intent

Concrete bindings translate endpoint-domain behavior into abstract bridge-facing surfaces.

### 20.6 Constraints

Concrete bindings must not push endpoint internals back into abstract `communication_context/`.

### 20.7 Delivery Packages

Recommended package names:

```text
ASCC-IMPL-W14A_LogLevelAPI_Envelope_PluginAdapter.zip
ASCC-IMPL-W14B_WriteSide_Envelope_Placement_Port.zip
ASCC-IMPL-W14C_WriteSide_Registry_Delivery_PluginAdapter.zip
```

### 20.8 Exit Gate

Phase 14 is complete when concrete bindings compile against the abstract core while preserving endpoint ownership boundaries.

---

## 21. Phase 15 — First Integration Skeleton

### 21.1 Purpose

Phase 15 creates a minimal compile-focused integration pass.

It should not add full runtime behavior.

### 21.2 Target

The target is a minimal example or test harness that proves:

```text
Log Level API plugin adapter
→ Bridge
→ Write Side placement port
```

can be represented through the abstract types.

### 21.3 Candidate Files

The exact file paths may be decided later, but candidate locations include:

```text
tests/communication_context/envelope_placement_smoke_test.cpp
examples/communication_context/envelope_placement_minimal.cpp
```

### 21.4 Constraints

The first integration skeleton must not implement production dispatch, persistence, telemetry, read-side, or ABI behavior.

### 21.5 Delivery Package

Recommended package name:

```text
ASCC-IMPL-W15_First_Integration_Skeleton.zip
```

### 21.6 Exit Gate

Phase 15 is complete when the minimal abstract flow can compile or be statically reasoned about without violating endpoint ownership.

---

## 22. Delivery Plan

### 22.1 Delivery Strategy

The recommended delivery strategy is one package per implementation wave.

Small waves are preferred.

A wave should be split further if:

1. it touches too many conceptual layers,
2. it introduces multiple dependency directions,
3. it creates public surfaces that require careful review,
4. it adds protocol behavior,
5. it touches endpoint-specific bindings,
6. it risks semantic collapse,
7. it risks endpoint leakage.

### 22.2 Package Naming Convention

Each package should use:

```text
ASCC-IMPL-WNN_<Wave_Name>.zip
```

Where:

1. `WNN` is the wave number,
2. `<Wave_Name>` is descriptive,
3. package includes only the files touched by that wave plus manifest,
4. package preserves full relative paths.

### 22.3 Required Package Contents

Every package should include:

| Record ID | Required Item | Description |
|---:|---|---|
| ASCC-IMPL-000-PKG-001 | Updated files | Files filled or added in the wave |
| ASCC-IMPL-000-PKG-002 | `.keep` preservation | Keep files preserved where relevant |
| ASCC-IMPL-000-PKG-003 | `WAVE_MANIFEST.json` | Machine-readable package manifest |
| ASCC-IMPL-000-PKG-004 | `WAVE_README.md` | Human-readable summary |
| ASCC-IMPL-000-PKG-005 | `CHANGED_FILES.txt` | Relative path list |
| ASCC-IMPL-000-PKG-006 | `DEPENDENCY_NOTES.md` | Dependency and include notes |
| ASCC-IMPL-000-PKG-007 | `DEFERRED_DECISIONS.md` | What remains intentionally unresolved |
| ASCC-IMPL-000-PKG-008 | `VALIDATION_NOTES.md` | Checks performed or planned |

### 22.4 Recommended Delivery Waves

| Wave | Package | Phase Coverage | Status |
|---:|---|---|---|
| W00 | `ASCC-IMPL-W00_Implementation_Conventions.zip` | Phase 0 | Optional documentation package |
| W01 | `ASCC-IMPL-W01_Primitive_Carrier_Foundations.zip` | Phase 1 | First code wave |
| W02 | `ASCC-IMPL-W02_Protocol_State_Foundations.zip` | Phase 2 | Code wave |
| W03 | `ASCC-IMPL-W03_Participant_And_Role_Foundations.zip` | Phase 3 | Code wave |
| W04 | `ASCC-IMPL-W04_Channel_Foundations.zip` | Phase 4 | Code wave |
| W05 | `ASCC-IMPL-W05_Port_And_PluginAdapter_Obligations.zip` | Phase 5 | Critical code wave |
| W06 | `ASCC-IMPL-W06_Binding_Model.zip` | Phase 6 | Code wave |
| W07 | `ASCC-IMPL-W07_Compatibility_Model.zip` | Phase 7 | Code wave |
| W08 | `ASCC-IMPL-W08_Session_Model.zip` | Phase 8 | Code wave |
| W09 | `ASCC-IMPL-W09_Bridge_Protocol_Model.zip` | Phase 9 | Critical code wave |
| W10 | `ASCC-IMPL-W10_Bridge_Core.zip` | Phase 10 | Critical code wave |
| W11 | `ASCC-IMPL-W11_Optional_Registries.zip` | Phase 11 | Deferred/optional |
| W12 | `ASCC-IMPL-W12_Diagnostics.zip` | Phase 12 | Deferred after core |
| W13 | `ASCC-IMPL-W13_Integration_Boundary_Abstract_Ports.zip` | Phase 13 | Deferred/future-facing |
| W14A | `ASCC-IMPL-W14A_LogLevelAPI_Envelope_PluginAdapter.zip` | Phase 14.1 | Concrete binding |
| W14B | `ASCC-IMPL-W14B_WriteSide_Envelope_Placement_Port.zip` | Phase 14.2 | Concrete binding |
| W14C | `ASCC-IMPL-W14C_WriteSide_Registry_Delivery_PluginAdapter.zip` | Phase 14.3 | Concrete binding |
| W15 | `ASCC-IMPL-W15_First_Integration_Skeleton.zip` | Phase 15 | Integration skeleton |

### 22.5 Recommended Execution Path

The recommended execution path is:

```text
W01 → W02 → W03 → W04 → W05 → W06 → W07 → W08 → W09 → W10
```

Then:

```text
W14A → W14B → W15
```

The following may be delayed:

```text
W11, W12, W13, W14C
```

unless their need becomes immediate.

---

## 23. Validation Gates

### 23.1 Gate 1 — Carrier Independence

After W01:

```text
Primitive carriers must compile without depending on bridge, channel, session,
port, plugin adapter, protocol, or endpoint domains.
```

### 23.2 Gate 2 — Protocol-State Non-Leakage

After W02:

```text
Protocol state must remain bridge-visible only and must not expose endpoint state.
```

### 23.3 Gate 3 — Participant Abstraction

After W03:

```text
Participants must describe roles, not implementations.
```

### 23.4 Gate 4 — Topology/Session Separation

After W04 and W08:

```text
Channel topology and session exchange must remain distinct.
```

### 23.5 Gate 5 — Obligation Surface Review

After W05:

```text
TPort and TPluginAdapter must be reviewed for correct obligation separation.
```

### 23.6 Gate 6 — Binding Non-Behavior

After W06:

```text
Binding must remain association, not endpoint execution.
```

### 23.7 Gate 7 — Compatibility Boundary

After W07:

```text
Compatibility must remain bridge-level and must not become endpoint validation.
```

### 23.8 Gate 8 — Protocol Orchestration Shape

After W09:

```text
Protocols must define orchestration shape without implementing endpoint algorithms.
```

### 23.9 Gate 9 — Bridge Non-Ownership

After W10:

```text
TBridge must orchestrate only and must not own content, host placement,
persistence, dispatch, validation internals, or endpoint lifecycle.
```

### 23.10 Gate 10 — Concrete Binding Containment

After W14A/W14B/W14C:

```text
Concrete bindings may depend on owning endpoint internals, but those internals
must not leak back into communication_context core.
```

---

## 24. Include Dependency Policy

### 24.1 Allowed Direction

The abstract core may depend on:

1. C++ standard library,
2. primitive carriers,
3. bridge result/error categories,
4. protocol state,
5. participants,
6. channel abstractions,
7. obligation abstractions,
8. binding abstractions,
9. compatibility abstractions,
10. session abstractions,
11. protocol abstractions.

### 24.2 Forbidden Direction

The abstract core must not include:

1. `assembler/log_level_api/...`,
2. `assembler/write_side/...`,
3. `assembler/read_side/...`,
4. database-specific headers,
5. telemetry SDK headers,
6. C ABI implementation headers,
7. application receiver internals.

### 24.3 Concrete Binding Direction

Concrete bindings may include:

1. `communication_context` abstract headers,
2. their owning domain headers,
3. standard library headers.

Concrete bindings must not be included by core `communication_context` headers.

---

## 25. File Addition Policy

### 25.1 Allowed Additions

A new file may be added if it satisfies all of the following:

1. it has a clear folder owner,
2. it fills a missing dependency layer,
3. it avoids endpoint leakage,
4. it has a clear relation to the phase,
5. it is listed in the wave manifest,
6. it is justified in `DEFERRED_DECISIONS.md` or `VALIDATION_NOTES.md`.

### 25.2 Known Required Addition

The first known required addition is:

```text
include/assembler/communication_context/bindings/binding_results/TBindingResult.hpp
```

Reason:

```text
Binding may fail or be rejected before session execution.
```

### 25.3 Forbidden Additions

A file must not be added merely because:

1. it is convenient,
2. it resembles a common framework pattern,
3. it hides unclear behavior,
4. it creates a generic utility bucket,
5. it bypasses the dependency order,
6. it introduces endpoint behavior into abstract core.

---

## 26. Testing Strategy

### 26.1 Test Timing

Tests should begin early but remain phase-appropriate.

The first tests should be compile-oriented and static-behavior-oriented.

### 26.2 Recommended Test Categories

| Test Category | Purpose |
|---|---|
| Compile smoke tests | Ensure headers compile independently |
| Static trait tests | Validate trait defaults and type aliases |
| Enum coverage tests | Ensure stages/results/errors are stable |
| Non-dependency tests | Detect forbidden endpoint includes |
| Opaque handle tests | Ensure handles do not expose endpoint internals |
| Contract shape tests | Validate port/adapter obligation surface shape |
| Protocol stage tests | Validate expected stage order |
| Bridge orchestration tests | Validate bridge does not own endpoint internals |

### 26.3 Deferred Tests

The following are deferred:

1. performance tests,
2. concurrency tests,
3. real endpoint integration tests,
4. database tests,
5. telemetry export tests,
6. C ABI tests,
7. read-side extension tests.

---

## 27. First Practical Delivery Recommendation

### 27.1 First Package

The first package to produce after this plan should be:

```text
ASCC-IMPL-W01_Primitive_Carrier_Foundations.zip
```

### 27.2 First Package Target Files

```text
include/assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp
include/assembler/communication_context/bridge_core/errors/TBridgeError.hpp
include/assembler/communication_context/bridge_core/results/TBridgeResult.hpp
include/assembler/communication_context/bridge_carriers/results/TBridgeCarrierResult.hpp
include/assembler/communication_context/bridge_carriers/errors/TBridgeCarrierError.hpp
include/assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp
include/assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp
include/assembler/communication_context/bridge_carriers/signals/TLoadSignal.hpp
include/assembler/communication_context/bridge_carriers/requests/TPlacementRequest.hpp
include/assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp
include/assembler/communication_context/bridge_carriers/destination/TNextDestinationRequest.hpp
include/assembler/communication_context/bridge_carriers/views/TCarrierView.hpp
```

### 27.3 First Package Quality Bar

The first package should:

1. compile standalone,
2. avoid endpoint includes,
3. define stable primitive value types,
4. use clear enum categories,
5. keep handles opaque,
6. avoid orchestration behavior,
7. include manifest and validation notes.

---

## 28. Summary

This document defines the dependency-first implementation plan for the Assembler System Communication Context.

The implementation must proceed in phases:

```text
0. Implementation conventions
1. Primitive carrier foundations
2. Protocol state foundations
3. Participants
4. Channels
5. Port and plugin-adapter obligations
6. Bindings
7. Compatibility
8. Sessions
9. Protocols
10. Bridge core
11. Registries
12. Diagnostics
13. Integration boundary ports
14. Concrete domain-side bindings
15. First integration skeleton
```

The first actual code delivery should be:

```text
ASCC-IMPL-W01_Primitive_Carrier_Foundations.zip
```

The most important rule remains:

```text
Dependency first,
then what depends on it.
```

This plan authorizes phased delivery planning.

It does not authorize random file filling, endpoint leakage, broker behavior, downstream ownership, or implementation shortcuts.
