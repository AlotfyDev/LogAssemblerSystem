# ASCC-003 — TPort and TPluginAdapter Contract Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASCC-003-DOC-001 | Document Title | TPort and TPluginAdapter Contract Model |
| ASCC-003-DOC-002 | File Name | `ASCC-003_TPort_TPluginAdapter_Contract_Model.md` |
| ASCC-003-DOC-003 | Documentation Pack | ASCC — Assembler System Communication Context Documentation Pack |
| ASCC-003-DOC-004 | Formal Version | Formal Draft V1 |
| ASCC-003-DOC-005 | Project | Assembler System |
| ASCC-003-DOC-006 | Primary Language | English |
| ASCC-003-DOC-007 | Scope Level | Port contract, plugin-adapter contract, obligation surfaces, bridge-visible carrier mapping, endpoint non-leakage |
| ASCC-003-DOC-008 | Implementation Direction | C++17, templates, traits, CRTP-compatible abstractions, static-first communication bindings |
| ASCC-003-DOC-009 | Status | Contract Model Architecture Draft |
| ASCC-003-DOC-010 | Depends On | `ASCC-001_Communication_Context_Foundation.md`, `ASCC-002_Bridge_Channel_Session_Core_Model.md` |
| ASCC-003-DOC-011 | Previous Document | `ASCC-002_Bridge_Channel_Session_Core_Model.md` |
| ASCC-003-DOC-012 | Next Candidate Document | `ASCC-004_Bridge_Carrier_Protocol_Model.md` |
| ASCC-003-DOC-013 | Primary Rule | `TPort` and `TPluginAdapter` expose obligations to the bridge without leaking endpoint internals |
| ASCC-003-DOC-014 | Core Contract Pair | `TPort` = host-side obligation surface; `TPluginAdapter` = content-side obligation surface |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the contract model for `TPort` and `TPluginAdapter` inside the Assembler System Communication Context.

It answers the question:

```text
What obligations must a host-side port and a content-side plugin adapter expose
so that TBridge can orchestrate communication without owning endpoint internals,
content preparation internals, host placement internals, queue internals,
persistence internals, telemetry internals, or ABI translation internals?
```

`ASCC-002` defined `TBridge`, `TChannel`, `TSession`, `TBinding`, `TPort`, `TPluginAdapter`, `TBridgeProtocol`, and `TBridgeCarriers` as the core model.

This document now deepens the two endpoint-facing contract surfaces:

```text
TPort
TPluginAdapter
```

### 2.2 Why This Document Exists

The bridge model is only safe if the two endpoint-facing surfaces are precisely governed.

Without a formal `TPort` / `TPluginAdapter` contract model, future implementation could accidentally do one of the following:

1. make the bridge perform endpoint validation,
2. make the bridge know queue/container internals,
3. make plugin adapters mutate host state directly,
4. make ports depend on content provider internals,
5. treat adapter and port as the same abstraction,
6. collapse bridge carriers into endpoint-private state,
7. hide admission or readiness semantics behind vague callbacks,
8. turn the Communication Context into a generic message broker.

This document prevents those failures.

### 2.3 Document Position

This document follows the ASCC sequence:

```text
ASCC-001
  Communication Context Foundation

ASCC-002
  Bridge, Channel, and Session Core Model

ASCC-003
  TPort and TPluginAdapter Contract Model
```

The next document should focus on carrier and protocol detail:

```text
ASCC-004_Bridge_Carrier_Protocol_Model.md
```

### 2.4 Non-Purpose

This document does not define:

1. final C++ signatures,
2. final class names,
3. final template constraints,
4. final CRTP base bodies,
5. final queue implementation,
6. final validation implementation,
7. final persistence adapter,
8. final OpenTelemetry adapter,
9. final C ABI adapter,
10. final registry implementation,
11. final transport protocol,
12. final runtime scheduling algorithm.

This document defines contract obligations and boundaries only.

---

## 3. Core Contract Thesis

### 3.1 Thesis Statement

`TPort` and `TPluginAdapter` are complementary bridge-facing contract surfaces.

They do not represent the same side of communication.

They do not own the bridge.

They do not own each other.

They allow the bridge to orchestrate communication without direct knowledge of endpoint internals.

```text
Content Provider Domain
  exposes TPluginAdapter
    ↓
TBridge
  orchestrates bridge-visible carriers
    ↓
TPort
  exposes Host / Container / Receiver Provider obligations
```

### 3.2 Contract Pair Rule

```text
TPluginAdapter expresses content-side obligations.
TPort expresses host-side obligations.
TBridge composes the two surfaces through channel, session, binding,
protocol, and carriers.
```

### 3.3 Endpoint Non-Leakage Rule

```text
Endpoint internals must remain behind their contract surfaces.

The bridge may observe declared carriers, readiness views, handles, signals,
and results.

The bridge must not inspect or mutate endpoint-private state.
```

### 3.4 Asymmetry Rule

`TPort` and `TPluginAdapter` are not symmetric copies.

They are complementary.

| Surface | Side | Primary Orientation |
|---|---|---|
| `TPluginAdapter` | content side | prepares, maps, reacts, and interprets content-side bridge material |
| `TPort` | host side | admits, locates, signals, exposes readiness, and returns host-side bridge material |

---

## 4. Contract Surface Map

### 4.1 High-Level Map

```mermaid
flowchart LR
    CP["Content Provider Domain"]
    AD["TPluginAdapter"]
    BR["TBridge"]
    PT["TPort"]
    HP["Host / Container / Receiver Provider Domain"]

    CP -->|"content-side internals hidden"| AD
    AD -->|"bridge-visible carriers"| BR
    BR -->|"bridge-visible carriers"| PT
    PT -->|"host-side internals hidden"| HP
```

### 4.2 Contract Surface Responsibilities

| Record ID | Surface | Owns | Does Not Own |
|---:|---|---|---|
| ASCC-003-SURF-001 | `TPluginAdapter` | Content-side bridge obligations, request preparation, adapter-side interpretation | Bridge orchestration, host internals, queue internals, persistence lifecycle |
| ASCC-003-SURF-002 | `TPort` | Host-side bridge obligations, admission surface, readiness view, handle/result production | Bridge orchestration, content internals, adapter internals, content preparation lifecycle |
| ASCC-003-SURF-003 | `TBridge` | Communication orchestration, carrier sequencing, session/channel/binding use | Endpoint validation internals, host mutation internals, content preparation internals |

### 4.3 Bridge Visibility Rule

The bridge may only depend on contract-visible material.

Contract-visible material includes:

1. carrier types,
2. declared operations,
3. declared result categories,
4. declared readiness views,
5. declared handles,
6. declared signal objects,
7. declared compatibility metadata,
8. declared errors,
9. declared correlation tokens.

Contract-visible material excludes:

1. endpoint-private state,
2. endpoint-local caches,
3. queue implementation internals,
4. host scheduler internals,
5. persistence storage internals,
6. telemetry SDK internals,
7. content-provider validation internals,
8. ABI translation internals.

---

## 5. TPort Definition

### 5.1 Definition

`TPort` is the host-side bridge-facing contract surface exposed by a host, container, receiver, persistence boundary, telemetry boundary, ABI boundary, or future receiver domain.

It declares what the host side is willing to provide to the bridge.

### 5.2 Architectural Role

`TPort` allows `TBridge` to communicate with a host-side provider without depending on host internals.

It may represent:

1. write-side placement surface,
2. queue/container admission surface,
3. registry-delivery receiving surface,
4. read-side receiver surface,
5. persistence boundary surface,
6. OpenTelemetry export surface,
7. thin C ABI receiving surface,
8. diagnostic receiver surface.

### 5.3 TPort Contract Identity

A `TPort` is:

1. a contract surface,
2. a host-side obligation boundary,
3. a bridge-visible receiver or host interaction point,
4. a provider of handles, readiness views, signals, and results where applicable.

A `TPort` is not:

1. the host provider itself,
2. the whole queue container,
3. the bridge,
4. a plugin adapter,
5. an endpoint implementation,
6. a persistence engine,
7. a telemetry SDK,
8. a C ABI layer,
9. a message broker.

---

## 6. TPort Obligation Families

### 6.1 Obligation Family Table

| Record ID | Obligation Family | Requiredness | Description |
|---:|---|---|---|
| ASCC-003-PORT-OBL-001 | Identity Obligation | Required | Exposes stable port identity and kind |
| ASCC-003-PORT-OBL-002 | Compatibility Obligation | Required | Declares supported carrier/protocol/channel compatibility |
| ASCC-003-PORT-OBL-003 | Admission Obligation | Contextual | Accepts, rejects, or defers bridge-visible requests |
| ASCC-003-PORT-OBL-004 | Handle Obligation | Contextual | Produces placement or receiver handles when admission succeeds |
| ASCC-003-PORT-OBL-005 | Readiness Obligation | Contextual | Exposes readiness view without leaking private state |
| ASCC-003-PORT-OBL-006 | Load Signal Obligation | Optional / Contextual | Exposes load, pressure, capacity, or availability signals |
| ASCC-003-PORT-OBL-007 | Destination Selection Obligation | Optional / Contextual | Helps select next host-side destination where allowed |
| ASCC-003-PORT-OBL-008 | Result Obligation | Required | Returns a contract-visible result category |
| ASCC-003-PORT-OBL-009 | Error Obligation | Required | Returns bridge-visible error information without leaking internals |
| ASCC-003-PORT-OBL-010 | Non-Ownership Obligation | Required | Preserves endpoint-private state and downstream non-ownership boundaries |

### 6.2 Required vs Contextual

A port does not need to implement every possible operation.

A port must implement only the obligations required by its declared port kind, channel, protocol family, and carrier set.

For example:

1. a write-side placement port needs admission and placement handle behavior,
2. a telemetry export port may expose export readiness and export result behavior,
3. a diagnostic observer port may expose readiness and signal views without admitting placement,
4. a thin C ABI receiver port may expose ABI-safe boundary mapping but not queue internals.

### 6.3 TPort Obligation Rule

```text
TPort obligations are selected by declared channel, protocol family,
carrier set, and port kind.

They must not be invented implicitly by concrete implementation convenience.
```

---

## 7. TPort Contract Record Model

Each concrete `TPort` candidate should be describable by the following model.

| Record ID | Field | Meaning |
|---:|---|---|
| ASCC-003-PORT-MODEL-001 | `port_id` | Stable port identifier |
| ASCC-003-PORT-MODEL-002 | `port_kind` | placement, receiver, persistence, telemetry, abi, diagnostic, registry_delivery |
| ASCC-003-PORT-MODEL-003 | `host_domain` | Domain that owns the actual host/receiver implementation |
| ASCC-003-PORT-MODEL-004 | `channel_compatibility` | Channels the port may participate in |
| ASCC-003-PORT-MODEL-005 | `protocol_compatibility` | Protocol families supported by the port |
| ASCC-003-PORT-MODEL-006 | `carrier_compatibility` | Carrier set supported by the port |
| ASCC-003-PORT-MODEL-007 | `required_obligations` | Port obligations required by this contract |
| ASCC-003-PORT-MODEL-008 | `optional_obligations` | Contextual or extension obligations |
| ASCC-003-PORT-MODEL-009 | `visibility` | public_bridge_surface, local_bridge_surface, test_only |
| ASCC-003-PORT-MODEL-010 | `private_boundary` | State or internals hidden behind the port |
| ASCC-003-PORT-MODEL-011 | `result_model` | Result categories the port can return |
| ASCC-003-PORT-MODEL-012 | `error_model` | Error categories the port can expose |
| ASCC-003-PORT-MODEL-013 | `non_ownership_statement` | What the port explicitly does not own |

---

## 8. TPort Contract Operations

### 8.1 Operation Classes

This section describes operation classes, not final C++ signatures.

| Record ID | Operation Class | Meaning |
|---:|---|---|
| ASCC-003-PORT-OP-001 | identify_port | Expose stable identity and kind |
| ASCC-003-PORT-OP-002 | declare_compatibility | Expose compatible channels, protocols, and carriers |
| ASCC-003-PORT-OP-003 | accept_or_reject | Accept, reject, defer, or fail a bridge-visible request |
| ASCC-003-PORT-OP-004 | produce_handle | Return placement or receiver handle when applicable |
| ASCC-003-PORT-OP-005 | expose_readiness | Return readiness view without leaking internals |
| ASCC-003-PORT-OP-006 | expose_load_signal | Return load, pressure, or availability signal |
| ASCC-003-PORT-OP-007 | select_destination | Return a next destination decision where supported |
| ASCC-003-PORT-OP-008 | emit_result | Return a bridge-visible result |
| ASCC-003-PORT-OP-009 | emit_error | Return bridge-visible error category |
| ASCC-003-PORT-OP-010 | expose_view | Return a view object rather than internal mutable state |

### 8.2 TPort Operation Non-Freeze Rule

The operation classes above are architectural obligations.

They are not final method names.

They are not final function signatures.

They are not final template constraints.

They are not final runtime algorithms.

---

## 9. TPluginAdapter Definition

### 9.1 Definition

`TPluginAdapter` is the content-side bridge-facing contract surface exposed by a content provider, producer, read-side source, telemetry source, persistence source, ABI-selected source, or diagnostic source.

It declares what the content side is willing to provide to the bridge.

### 9.2 Architectural Role

`TPluginAdapter` allows `TBridge` to communicate with a content-side provider without depending on content provider internals.

It may represent:

1. log-level envelope provider adapter,
2. content preparation adapter,
3. read-side receiver-source adapter,
4. persistence export adapter,
5. telemetry source adapter,
6. replay/projection adapter,
7. thin C ABI source adapter,
8. diagnostic source adapter.

### 9.3 TPluginAdapter Contract Identity

A `TPluginAdapter` is:

1. a contract surface,
2. a content-side obligation boundary,
3. a producer of bridge-visible request material,
4. an interpreter of bridge-visible handles, signals, readiness views, and results where applicable.

A `TPluginAdapter` is not:

1. the bridge,
2. the port,
3. the whole content provider,
4. a host provider,
5. a queue container,
6. a downstream registry,
7. a validator by default,
8. a metadata injector by default,
9. a timestamp stabilizer by default,
10. a message broker.

---

## 10. TPluginAdapter Obligation Families

### 10.1 Obligation Family Table

| Record ID | Obligation Family | Requiredness | Description |
|---:|---|---|---|
| ASCC-003-ADAPT-OBL-001 | Identity Obligation | Required | Exposes stable adapter identity and kind |
| ASCC-003-ADAPT-OBL-002 | Compatibility Obligation | Required | Declares supported carrier/protocol/channel compatibility |
| ASCC-003-ADAPT-OBL-003 | Request Preparation Obligation | Contextual | Prepares bridge-visible request carriers |
| ASCC-003-ADAPT-OBL-004 | Handle Interpretation Obligation | Contextual | Interprets placement or receiver handles where applicable |
| ASCC-003-ADAPT-OBL-005 | Result Interpretation Obligation | Required | Interprets bridge-visible result categories |
| ASCC-003-ADAPT-OBL-006 | Signal Reaction Obligation | Optional / Contextual | Reacts to load signals, pressure signals, or readiness changes |
| ASCC-003-ADAPT-OBL-007 | Destination Request Obligation | Optional / Contextual | Requests next destination where protocol allows |
| ASCC-003-ADAPT-OBL-008 | Correlation Obligation | Required where sessions exist | Supplies or propagates correlation token |
| ASCC-003-ADAPT-OBL-009 | Error Interpretation Obligation | Required | Interprets bridge-visible errors without owning host internals |
| ASCC-003-ADAPT-OBL-010 | Non-Ownership Obligation | Required | Avoids mutating host internals or claiming port authority |

### 10.2 Required vs Contextual

A plugin adapter does not need to implement every possible operation.

A plugin adapter must implement only the obligations required by its declared adapter kind, channel, protocol family, and carrier set.

For example:

1. a log-level envelope adapter prepares placement requests,
2. a telemetry source adapter may prepare export requests,
3. a read-side source adapter may prepare receiver-bound material,
4. a thin C ABI adapter may map ABI-safe material into bridge-visible carriers,
5. a diagnostic adapter may produce observations or test signals.

### 10.3 TPluginAdapter Obligation Rule

```text
TPluginAdapter obligations are selected by declared channel, protocol family,
carrier set, and adapter kind.

They must not be invented implicitly by concrete implementation convenience.
```

---

## 11. TPluginAdapter Contract Record Model

Each concrete `TPluginAdapter` candidate should be describable by the following model.

| Record ID | Field | Meaning |
|---:|---|---|
| ASCC-003-ADAPT-MODEL-001 | `adapter_id` | Stable adapter identifier |
| ASCC-003-ADAPT-MODEL-002 | `adapter_kind` | envelope_source, content_source, read_source, telemetry_source, persistence_source, abi_source, diagnostic_source |
| ASCC-003-ADAPT-MODEL-003 | `content_domain` | Domain that owns the actual content/source implementation |
| ASCC-003-ADAPT-MODEL-004 | `channel_compatibility` | Channels the adapter may participate in |
| ASCC-003-ADAPT-MODEL-005 | `protocol_compatibility` | Protocol families supported by the adapter |
| ASCC-003-ADAPT-MODEL-006 | `carrier_compatibility` | Carrier set supported by the adapter |
| ASCC-003-ADAPT-MODEL-007 | `required_obligations` | Adapter obligations required by this contract |
| ASCC-003-ADAPT-MODEL-008 | `optional_obligations` | Contextual or extension obligations |
| ASCC-003-ADAPT-MODEL-009 | `visibility` | public_bridge_surface, local_bridge_surface, test_only |
| ASCC-003-ADAPT-MODEL-010 | `private_boundary` | State or internals hidden behind the adapter |
| ASCC-003-ADAPT-MODEL-011 | `request_model` | Request carriers the adapter can produce |
| ASCC-003-ADAPT-MODEL-012 | `result_interpretation_model` | Result categories the adapter can interpret |
| ASCC-003-ADAPT-MODEL-013 | `non_ownership_statement` | What the adapter explicitly does not own |

---

## 12. TPluginAdapter Contract Operations

### 12.1 Operation Classes

This section describes operation classes, not final C++ signatures.

| Record ID | Operation Class | Meaning |
|---:|---|---|
| ASCC-003-ADAPT-OP-001 | identify_adapter | Expose stable identity and kind |
| ASCC-003-ADAPT-OP-002 | declare_compatibility | Expose compatible channels, protocols, and carriers |
| ASCC-003-ADAPT-OP-003 | prepare_request | Produce bridge-visible request carrier |
| ASCC-003-ADAPT-OP-004 | attach_correlation | Supply or propagate correlation token |
| ASCC-003-ADAPT-OP-005 | interpret_handle | Interpret placement or receiver handle where applicable |
| ASCC-003-ADAPT-OP-006 | react_to_signal | React to load or readiness signal |
| ASCC-003-ADAPT-OP-007 | request_destination | Request next destination where allowed |
| ASCC-003-ADAPT-OP-008 | interpret_result | Interpret bridge-visible result |
| ASCC-003-ADAPT-OP-009 | interpret_error | Interpret bridge-visible error category |
| ASCC-003-ADAPT-OP-010 | expose_view | Return bridge-visible view, not private mutable state |

### 12.2 Adapter Operation Non-Freeze Rule

The operation classes above are architectural obligations.

They are not final method names.

They are not final function signatures.

They are not final template constraints.

They are not final runtime algorithms.

---

## 13. Shared Compatibility Model

### 13.1 Why Compatibility Exists

`TBridge` must not blindly connect any adapter to any port.

Compatibility must be explicit.

Compatibility protects:

1. carrier type safety,
2. protocol sequence correctness,
3. channel topology validity,
4. multiplicity constraints,
5. endpoint non-leakage,
6. result interpretation,
7. error handling,
8. hot-path safety.

### 13.2 Compatibility Dimensions

| Record ID | Dimension | Meaning |
|---:|---|---|
| ASCC-003-COMPAT-001 | Channel Compatibility | Adapter and port are valid under the same channel |
| ASCC-003-COMPAT-002 | Protocol Compatibility | Adapter and port speak the same bridge protocol family |
| ASCC-003-COMPAT-003 | Carrier Compatibility | Adapter and port support the required carrier set |
| ASCC-003-COMPAT-004 | Multiplicity Compatibility | Binding shape is valid for the channel |
| ASCC-003-COMPAT-005 | Direction Compatibility | Sender/receiver direction is valid |
| ASCC-003-COMPAT-006 | Result Compatibility | Port result categories can be interpreted by adapter |
| ASCC-003-COMPAT-007 | Error Compatibility | Errors are expressible without endpoint-private leakage |
| ASCC-003-COMPAT-008 | Performance Compatibility | Hot-path/cold-path expectations do not conflict |
| ASCC-003-COMPAT-009 | Ownership Compatibility | Neither side claims the other side’s internals |
| ASCC-003-COMPAT-010 | Visibility Compatibility | Surfaces are approved for bridge use |

### 13.3 Compatibility Rule

```text
A binding is valid only when adapter, port, channel, protocol, carrier,
multiplicity, direction, result, error, performance, ownership, and visibility
compatibility checks pass or are explicitly deferred by a review gate.
```

---

## 14. Shared Carrier Mapping

### 14.1 Carrier Mapping Table

| Carrier | Adapter Responsibility | Bridge Responsibility | Port Responsibility |
|---|---|---|---|
| `placement_request` | Prepare or expose request material | Transfer according to protocol | Accept, reject, defer, or fail |
| `placement_handle` | Interpret handle | Transfer to adapter | Produce handle where applicable |
| `admission_result` | Interpret result | Consolidate and route result | Produce admission result |
| `load_signal` | React or adapt | Observe and route | Expose load signal |
| `next_destination_request` | Request destination where allowed | Route request | Select or reject destination request |
| `readiness_view` | Interpret readiness | Request and route | Expose readiness view |
| `bridge_result` | Interpret final outcome | Produce or consolidate | Contribute result material |
| `correlation_token` | Supply or propagate | Preserve correlation | Preserve or return correlation |
| `binding_view` | Consume view where allowed | Provide view | May contribute port-side binding status |
| `session_view` | Consume view where allowed | Provide session view | May contribute port-side session status |

### 14.2 Carrier Mapping Rule

Bridge carriers are shared communication artifacts.

They must not become endpoint-private state.

They must not be expanded into ungoverned payload blobs.

---

## 15. Error Model

### 15.1 Error Model Purpose

The bridge requires error categories that are visible enough for orchestration but not so detailed that they expose endpoint internals.

### 15.2 Error Categories

| Record ID | Error Category | Meaning |
|---:|---|---|
| ASCC-003-ERR-001 | incompatible_channel | Adapter and port are not valid under the selected channel |
| ASCC-003-ERR-002 | incompatible_protocol | Protocol family mismatch |
| ASCC-003-ERR-003 | incompatible_carrier_set | Required carrier set is unsupported |
| ASCC-003-ERR-004 | binding_rejected | Binding is explicitly rejected |
| ASCC-003-ERR-005 | admission_rejected | Port rejects admission |
| ASCC-003-ERR-006 | readiness_unavailable | Readiness view unavailable |
| ASCC-003-ERR-007 | load_limit_reached | Port reports load/capacity limitation |
| ASCC-003-ERR-008 | destination_unavailable | Next destination cannot be provided |
| ASCC-003-ERR-009 | adapter_preparation_failed | Adapter failed to produce required carrier |
| ASCC-003-ERR-010 | port_operation_failed | Port failed to complete required obligation |
| ASCC-003-ERR-011 | correlation_mismatch | Correlation token mismatch |
| ASCC-003-ERR-012 | session_expired | Session no longer valid |
| ASCC-003-ERR-013 | endpoint_private_failure | Endpoint failed internally but details remain hidden |
| ASCC-003-ERR-014 | unsupported_operation | Required operation is unsupported for this contract |
| ASCC-003-ERR-015 | contract_violation | Declared contract obligations were violated |

### 15.3 Error Non-Leakage Rule

```text
Bridge-visible errors should identify orchestration-relevant failure categories.
They must not expose endpoint-private implementation details unless an explicit
diagnostic contract permits it.
```

---

## 16. Result Model

### 16.1 Result Model Purpose

The bridge requires result categories that allow adapters, ports, and sessions to complete without confusing bridge outcome with downstream lifecycle ownership.

### 16.2 Result Categories

| Record ID | Result Category | Meaning |
|---:|---|---|
| ASCC-003-RES-001 | accepted | Port accepted the request or exchange |
| ASCC-003-RES-002 | rejected | Port or compatibility rule rejected the exchange |
| ASCC-003-RES-003 | deferred | Exchange should be retried or delayed |
| ASCC-003-RES-004 | failed | Exchange failed under declared contract |
| ASCC-003-RES-005 | completed | Bridge protocol completed successfully |
| ASCC-003-RES-006 | partial | Some but not all obligations completed |
| ASCC-003-RES-007 | degraded | Exchange completed under reduced capability |
| ASCC-003-RES-008 | no_destination | No valid destination was available |
| ASCC-003-RES-009 | not_ready | Port or host side is not ready |
| ASCC-003-RES-010 | unsupported | Operation or carrier is unsupported |

### 16.3 Result Non-Ownership Rule

```text
A bridge result records communication outcome.
It does not prove downstream persistence, downstream query readiness,
storage lifecycle completion, telemetry delivery finality, or ABI-side lifecycle ownership.
```

---

## 17. Lifecycle and State Boundaries

### 17.1 Adapter Lifecycle

The lifecycle of a `TPluginAdapter` belongs to the content-side owning context.

The Communication Context may know whether an adapter is available or bound.

It does not own the internal lifecycle of the content provider.

### 17.2 Port Lifecycle

The lifecycle of a `TPort` belongs to the host-side owning context.

The Communication Context may know whether a port is available, ready, or compatible.

It does not own the internal lifecycle of the host provider.

### 17.3 Bridge Session Lifecycle

A `TSession` may frame runtime communication.

However, session lifecycle is communication lifecycle only.

It is not content lifecycle.

It is not host lifecycle.

It is not storage lifecycle.

It is not registry record lifecycle.

### 17.4 Lifecycle Boundary Rule

```text
Communication lifecycle must not be confused with endpoint lifecycle,
payload lifecycle, queue lifecycle, registry lifecycle, persistence lifecycle,
telemetry lifecycle, or ABI lifecycle.
```

---

## 18. Hot-Path and Cold-Path Contract Policy

### 18.1 Motivation

Some communication paths may be performance-sensitive.

Other paths may be configuration, diagnostic, registry, or extension paths.

The contract model must support both without forcing one implementation policy onto all paths.

### 18.2 Path Classes

| Record ID | Path Class | Meaning |
|---:|---|---|
| ASCC-003-PATH-001 | hot_path | Minimal overhead; prevalidated bindings; limited allocation; static-first compatibility |
| ASCC-003-PATH-002 | warm_path | Moderate validation; cached compatibility; controlled dynamic behavior |
| ASCC-003-PATH-003 | cold_path | Configuration, registry loading, diagnostics, introspection, setup |
| ASCC-003-PATH-004 | test_path | Test-only surfaces and instrumentation |
| ASCC-003-PATH-005 | diagnostic_path | Expanded observability under explicit diagnostic rules |

### 18.3 Hot-Path Rule

```text
Hot-path contracts should prefer predeclared compatibility, stable carrier sets,
static or cached binding resolution, and minimal bridge-visible error categories.
```

### 18.4 Cold-Path Rule

```text
Cold-path contracts may permit richer validation, diagnostics, registry lookups,
or compatibility explanation, provided they do not redefine hot-path semantics.
```

---

## 19. C++ Representation Direction

### 19.1 Direction Statement

The future C++ representation should allow static-first expression of adapter and port obligations.

The likely representation may use:

1. templates,
2. traits,
3. CRTP,
4. type markers,
5. carrier-set types,
6. protocol traits,
7. compatibility traits,
8. optional runtime views.

This document does not freeze that representation.

### 19.2 Illustrative Pseudo-Code

```cpp
template <typename DerivedT, typename CarrierSetT>
struct TPluginAdapterContract {
    // content-side obligation surface
    // illustrative only
};

template <typename DerivedT, typename CarrierSetT>
struct TPortContract {
    // host-side obligation surface
    // illustrative only
};

template <typename AdapterT, typename PortT, typename ChannelT, typename ProtocolT>
struct TCompatibility {
    // compile-time or static-first compatibility description
    // illustrative only
};

template <typename AdapterT, typename PortT, typename SessionT>
struct TBridgeExchange {
    // bridge-visible orchestration context
    // illustrative only
};
```

### 19.3 Type Trait Direction

Possible future trait names may include:

```cpp
is_bridge_adapter<T>
is_bridge_port<T>
supports_carrier<T, Carrier>
supports_protocol<T, Protocol>
supports_channel<T, Channel>
is_hot_path_compatible<T>
```

These names are illustrative.

They do not freeze final type names.

### 19.4 C++ Non-Freeze Rule

```text
C++ pseudo-code in this document expresses architectural direction only.
It must not be treated as final class hierarchy, final namespace structure,
final template signature, final include graph, or final build target.
```

---

## 20. Contract Validation Matrix

### 20.1 TPort Validation Questions

| Record ID | Question | Expected Answer |
|---:|---|---|
| ASCC-003-VAL-PORT-001 | Does the port declare stable identity and kind? | Yes |
| ASCC-003-VAL-PORT-002 | Does the port declare compatible channels? | Yes |
| ASCC-003-VAL-PORT-003 | Does the port declare compatible carrier set? | Yes |
| ASCC-003-VAL-PORT-004 | Does the port expose only bridge-visible views? | Yes |
| ASCC-003-VAL-PORT-005 | Does the port hide host-private internals? | Yes |
| ASCC-003-VAL-PORT-006 | Does the port avoid claiming bridge ownership? | Yes |
| ASCC-003-VAL-PORT-007 | Does the port avoid claiming content-provider ownership? | Yes |
| ASCC-003-VAL-PORT-008 | Does the port return declared result categories? | Yes |
| ASCC-003-VAL-PORT-009 | Does the port return declared error categories? | Yes |
| ASCC-003-VAL-PORT-010 | Does the port preserve downstream non-ownership where relevant? | Yes |

### 20.2 TPluginAdapter Validation Questions

| Record ID | Question | Expected Answer |
|---:|---|---|
| ASCC-003-VAL-ADAPT-001 | Does the adapter declare stable identity and kind? | Yes |
| ASCC-003-VAL-ADAPT-002 | Does the adapter declare compatible channels? | Yes |
| ASCC-003-VAL-ADAPT-003 | Does the adapter declare compatible carrier set? | Yes |
| ASCC-003-VAL-ADAPT-004 | Does the adapter prepare only bridge-visible carriers? | Yes |
| ASCC-003-VAL-ADAPT-005 | Does the adapter hide content-private internals? | Yes |
| ASCC-003-VAL-ADAPT-006 | Does the adapter avoid mutating host internals? | Yes |
| ASCC-003-VAL-ADAPT-007 | Does the adapter avoid claiming port ownership? | Yes |
| ASCC-003-VAL-ADAPT-008 | Does the adapter interpret declared result categories? | Yes |
| ASCC-003-VAL-ADAPT-009 | Does the adapter interpret declared error categories? | Yes |
| ASCC-003-VAL-ADAPT-010 | Does the adapter preserve endpoint non-ownership? | Yes |

### 20.3 Binding Validation Questions

| Record ID | Question | Expected Answer |
|---:|---|---|
| ASCC-003-VAL-BIND-001 | Are adapter and port compatible under the channel? | Yes |
| ASCC-003-VAL-BIND-002 | Are adapter and port compatible under the protocol family? | Yes |
| ASCC-003-VAL-BIND-003 | Are carrier sets compatible? | Yes |
| ASCC-003-VAL-BIND-004 | Is multiplicity explicit? | Yes |
| ASCC-003-VAL-BIND-005 | Is direction explicit? | Yes |
| ASCC-003-VAL-BIND-006 | Are result and error models compatible? | Yes |
| ASCC-003-VAL-BIND-007 | Are private boundaries preserved? | Yes |
| ASCC-003-VAL-BIND-008 | Is any deferred compatibility review recorded? | Yes, when applicable |

---

## 21. Anti-Collapse Index

| Rule ID | Protected Term | Must Not Collapse Into | Protected Distinction | Severity |
|---:|---|---|---|---|
| ASCC-003-AC-001 | `TPort` | `TBridge` | Port exposes host obligations; bridge orchestrates | Critical |
| ASCC-003-AC-002 | `TPort` | `TPluginAdapter` | Port is host-side; adapter is content-side | Critical |
| ASCC-003-AC-003 | `TPort` | host provider internals | Port surface hides host implementation | Critical |
| ASCC-003-AC-004 | `TPort` | queue/container internals | Port may expose placement surface without leaking queue internals | Critical |
| ASCC-003-AC-005 | `TPluginAdapter` | `TBridge` | Adapter prepares/interprets; bridge orchestrates | Critical |
| ASCC-003-AC-006 | `TPluginAdapter` | `TPort` | Adapter is content-side; port is host-side | Critical |
| ASCC-003-AC-007 | `TPluginAdapter` | content provider internals | Adapter surface hides content implementation | Critical |
| ASCC-003-AC-008 | `TPluginAdapter` | validator / metadata injector / timestamp stabilizer by default | Adapter is a bridge surface, not a preparation component by default | High |
| ASCC-003-AC-009 | bridge-visible carrier | endpoint-private state | Carriers are protocol artifacts, not internal state | Critical |
| ASCC-003-AC-010 | compatibility check | runtime algorithm | Compatibility is contract validation, not final runtime implementation | Medium |
| ASCC-003-AC-011 | bridge result | downstream lifecycle proof | Result records communication outcome only | Critical |
| ASCC-003-AC-012 | bridge error | endpoint-private failure detail | Error category must not leak private implementation | High |
| ASCC-003-AC-013 | hot-path contract | generic dynamic plugin system | Hot-path contract may restrict dynamic behavior | High |
| ASCC-003-AC-014 | cold-path diagnostics | hot-path semantics | Diagnostics must not redefine hot-path contract | Medium |

---

## 22. Concrete Contract Examples

### 22.1 Log Level API to Write Side Placement

```text
Adapter:
  log_level_envelope_plugin_adapter

Port:
  write_side_placement_port

Channel:
  log_level_api_to_write_side_placement

Protocol:
  placement_protocol

Core carriers:
  placement_request
  placement_handle
  admission_result
  readiness_view
  bridge_result
```

Interpretation:

1. the adapter prepares a placement request from a prepared Log Level Envelope context,
2. the bridge routes the request through the selected channel/session/binding,
3. the port admits or rejects placement according to write-side host rules,
4. the port returns handle/result/readiness material,
5. the bridge returns a bridge result to the adapter or caller.

### 22.2 Read Side to Receiver Integration

```text
Adapter:
  read_side_projection_adapter

Port:
  in_process_receiver_port

Channel:
  read_side_to_receiver_projection

Protocol:
  receiver_delivery_protocol

Core carriers:
  placement_request
  admission_result
  readiness_view
  bridge_result
```

Interpretation:

1. read-side may act as content provider,
2. receiver exposes a port,
3. the bridge model remains unchanged,
4. endpoint-specific projection logic remains behind the adapter,
5. receiver internals remain behind the port.

### 22.3 Telemetry Export

```text
Adapter:
  telemetry_event_adapter

Port:
  opentelemetry_export_port

Channel:
  telemetry_export_channel

Protocol:
  export_protocol

Core carriers:
  placement_request
  admission_result
  load_signal
  bridge_result
```

Interpretation:

1. telemetry adapter provides bridge-visible export material,
2. OpenTelemetry port exposes export obligations,
3. bridge coordinates exchange,
4. telemetry SDK internals remain behind the port.

### 22.4 Thin C ABI Boundary

```text
Adapter:
  selected_cpp_surface_adapter

Port:
  thin_c_abi_receiver_port

Channel:
  cpp_to_c_abi_boundary

Protocol:
  abi_boundary_protocol

Core carriers:
  placement_request
  admission_result
  bridge_result
  correlation_token
```

Interpretation:

1. adapter maps selected C++ material into bridge-visible carriers,
2. ABI port maps bridge-visible material into ABI-safe receiving behavior,
3. bridge does not own ABI translation internals,
4. concrete ABI representation remains deferred.

---

## 23. Folder and File Derivation Implications

### 23.1 Candidate Folder Placement

The `TPort` and `TPluginAdapter` contract model suggests the following candidate folder refinement inside `communication_context/`:

```text
communication_context/
├── ports/
│   ├── docs/
│   ├── tests/
│   ├── contracts/
│   ├── views/
│   └── detail/
├── plugin_adapters/
│   ├── docs/
│   ├── tests/
│   ├── contracts/
│   ├── views/
│   └── detail/
├── compatibility/
│   ├── docs/
│   ├── tests/
│   ├── contracts/
│   └── detail/
└── errors/
    ├── docs/
    ├── tests/
    ├── carriers/
    └── detail/
```

### 23.2 Candidate File Families

This document suggests future candidate files only.

It does not freeze final inventory.

| Candidate Family | Example Candidate File | Meaning |
|---|---|---|
| Port contracts | `port_contract.hpp` | Port obligation surface |
| Adapter contracts | `plugin_adapter_contract.hpp` | Adapter obligation surface |
| Compatibility | `compatibility_traits.hpp` | Static-first compatibility description |
| Error categories | `bridge_error_category.hpp` | Bridge-visible error vocabulary |
| Result categories | `bridge_result_category.hpp` | Bridge-visible result vocabulary |
| Views | `port_readiness_view.hpp` | Bridge-visible port readiness view |
| Views | `adapter_capability_view.hpp` | Bridge-visible adapter capability view |
| Tests | `port_contract_test.cpp` | Contract validation tests |
| Tests | `plugin_adapter_contract_test.cpp` | Contract validation tests |
| Docs | `contract_model.md` | Local contract explanation |

### 23.3 Derivation Rule

```text
Future files must derive from declared contract obligations.

They must not invent new bridge semantics merely because a C++ helper file
would be convenient.
```

---

## 24. Implementation Readiness

### 24.1 Ready for Future Derivation

This document makes the following ready for future derivation:

1. port contract traits,
2. plugin adapter contract traits,
3. compatibility traits,
4. error category model,
5. result category model,
6. bridge-visible readiness views,
7. contract validation matrix,
8. port/adapter folder refinement,
9. carrier-protocol derivation in `ASCC-004`.

### 24.2 Not Yet Ready

The following remain deferred:

1. final C++ code,
2. final CRTP hierarchy,
3. final trait names,
4. final namespace structure,
5. final include graph,
6. final build targets,
7. final registry implementation,
8. final runtime bridge algorithm,
9. final hot-path memory model,
10. final adapter/port concrete implementations.

---

## 25. Summary

`ASCC-003` defines the contract model for `TPort` and `TPluginAdapter`.

The key conclusions are:

1. `TPort` is the host-side obligation surface.
2. `TPluginAdapter` is the content-side obligation surface.
3. `TBridge` composes both surfaces without owning endpoint internals.
4. Compatibility must be explicit.
5. Carrier mapping must be bridge-visible and type-governed.
6. Errors must be bridge-visible without leaking private implementation detail.
7. Results describe communication outcome, not downstream lifecycle proof.
8. Hot-path and cold-path contracts may differ without redefining core semantics.
9. C++ representation is static-first and template/CRTP-compatible but not frozen.
10. Future derivation should proceed into carrier and protocol modeling.

The next document should be:

```text
ASCC-004_Bridge_Carrier_Protocol_Model.md
```

That document should formalize the bridge carrier set, protocol families, sequence contracts, carrier/result/error schemas, and validation rules that connect `TBridge`, `TChannel`, `TSession`, `TPort`, and `TPluginAdapter`.
