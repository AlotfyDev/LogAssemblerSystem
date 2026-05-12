
# ASDT-FS-005 — Current Folder Structure Draft V1

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-005-DOC-001 | Document Title | Current Folder Structure Draft V1 |
| ASDT-FS-005-DOC-002 | File Name | `ASDT-FS-005_Current_Folder_Structure_Draft_V1.md` |
| ASDT-FS-005-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-005-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-005-DOC-005 | Project | Assembler System |
| ASDT-FS-005-DOC-006 | Primary Language | English |
| ASDT-FS-005-DOC-007 | Scope Level | Current folder structure draft, domain-internal folder structure, component-level placement, folder ownership draft |
| ASDT-FS-005-DOC-008 | Implementation Language Direction | C++17, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-005-DOC-009 | Status | Pre-Implementation Folder Structure Draft |
| ASDT-FS-005-DOC-010 | File Inventory Status | Deferred |
| ASDT-FS-005-DOC-011 | Depends On | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md`, `ASDT-FS-001_Root_DDD_Domain_Folders.md`, `ASDT-FS-003_Folder_Dependency_And_Ownership_Rules.md`, `ASDT-FS-004_Component_Subfolder_Rules.md` |
| ASDT-FS-005-DOC-012 | Primary Rule | This document drafts folders only; it does not freeze final files |
| ASDT-FS-005-DOC-013 | Governing Principle | Folder placement must reflect semantic ownership, dependency direction, boundary protection, and anti-collapse rules |
| ASDT-FS-005-DOC-014 | Excluded From This Document | Final `.hpp` inventory, final class names, namespace declarations, CMake targets, final include graph, final runtime algorithms |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the current draft filesystem structure for the Assembler System.

It transforms the previously established folder doctrine, root domain doctrine, ownership rules, dependency rules, and component subfolder rules into a concrete folder-tree draft.

It answers the question:

```text
Given the current architecture, what folder structure should represent the
Assembler System as a digital twin before final file inventory is derived?
````

### 2.2 Draft Status

This is a folder-structure draft.

It is not a final repository layout.

It is not a final package inventory.

It is not a final class inventory.

It is not a final file inventory.

The folder tree in this document is intended to stabilize:

1. root domain placement,
2. first-level domain folders,
3. component and actor folder ownership,
4. local documentation and testing placement,
5. local carrier placement,
6. state placement,
7. hosted port placement,
8. outbound adapter placement,
9. communication boundary placement,
10. forbidden or discouraged folder patterns.

### 2.3 Why This Document Comes Now

The previous documents established:

1. the filesystem is a logical digital twin, not passive storage,
2. folders are stabilized before files,
3. the root DDD domains are `ecosystem_governance/`, `log_level_api/`, and `write_side/`,
4. folders own narrow semantic scopes,
5. dependencies must follow dependency-first ordering,
6. component subfolders are optional and must be justified.

This document now applies those rules to the current folder draft.

---

## 3. Global Folder Structure Baseline

### 3.1 Current Top-Level Implementation Baseline

The current implementation baseline is:

```text id="asdt-fs-005-global-baseline"
include/
└── assembler/
    ├── ecosystem_governance/
    ├── log_level_api/
    └── write_side/
```

### 3.2 Repository Support Folders

The following support folders may exist outside `include/assembler/`, but they are not DDD implementation domains by default:

```text id="asdt-fs-005-support-folders"
docs/
tests/
examples/
cmake/
scripts/
tools/
```

These folders must not replace domain-local `docs/` and `tests/`.

They serve repository-level coordination, not component-local semantic ownership.

### 3.3 Root Domain Ordering

The root domain ordering remains:

```text id="asdt-fs-005-root-order"
ecosystem_governance/
log_level_api/
write_side/
```

This order reflects the current dependency orientation:

1. ecosystem governance supplies policy-facing types, registries, providers, and receiver-port definitions,
2. log-level API prepares content and assembles envelopes,
3. write-side coordinates runtime placement and dispatch.

---

## 4. Full Current Folder Tree Draft

### 4.1 Draft Tree

```text id="asdt-fs-005-current-tree"
include/
└── assembler/
    ├── ecosystem_governance/
    │   ├── docs/
    │   ├── tests/
    │   ├── policy_types/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   └── detail/
    │   ├── policy_registry/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── hosted_ports/
    │   │   ├── outbound_adapters/
    │   │   ├── views/
    │   │   └── detail/
    │   ├── provider_adapters/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── outbound_adapters/
    │   │   └── detail/
    │   └── receiver_ports/
    │       ├── docs/
    │       ├── tests/
    │       ├── log_level_api/
    │       │   ├── docs/
    │       │   ├── hosted_ports/
    │       │   └── carriers/
    │       └── write_side/
    │           ├── docs/
    │           ├── hosted_ports/
    │           └── carriers/
    │
    ├── log_level_api/
    │   ├── docs/
    │   ├── tests/
    │   ├── content/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── views/
    │   │   ├── handles/
    │   │   └── detail/
    │   ├── envelope/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── views/
    │   │   ├── handles/
    │   │   └── detail/
    │   ├── validator/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── state/
    │   │   ├── policies/
    │   │   ├── contracts/
    │   │   └── detail/
    │   ├── metadata_injector/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── state/
    │   │   ├── contracts/
    │   │   └── detail/
    │   ├── timestamp_stabilizer/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── state/
    │   │   ├── policies/
    │   │   ├── contracts/
    │   │   └── detail/
    │   ├── policy_assignment/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── hosted_ports/
    │   │   ├── outbound_adapters/
    │   │   ├── policies/
    │   │   ├── contracts/
    │   │   ├── views/
    │   │   └── detail/
    │   ├── envelope_assembler/
    │   │   ├── docs/
    │   │   ├── tests/
    │   │   ├── carriers/
    │   │   ├── state/
    │   │   ├── contracts/
    │   │   └── detail/
    │   └── write_side_bridge/
    │       ├── docs/
    │       ├── tests/
    │       ├── carriers/
    │       ├── hosted_ports/
    │       ├── outbound_adapters/
    │       ├── views/
    │       ├── handles/
    │       └── detail/
    │
    └── write_side/
        ├── docs/
        ├── tests/
        ├── ingress/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── hosted_ports/
        │   ├── views/
        │   ├── handles/
        │   └── detail/
        ├── policy_assignment/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── hosted_ports/
        │   ├── outbound_adapters/
        │   ├── policies/
        │   ├── contracts/
        │   ├── views/
        │   └── detail/
        ├── slot/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   │   ├── transitions/
        │   │   └── guards/
        │   ├── views/
        │   ├── handles/
        │   ├── contracts/
        │   └── detail/
        ├── slots_container/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   │   ├── transitions/
        │   │   └── guards/
        │   ├── views/
        │   ├── handles/
        │   ├── contracts/
        │   └── detail/
        ├── waiting_list/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   ├── views/
        │   ├── handles/
        │   └── detail/
        ├── slots_container_moderator/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   ├── views/
        │   ├── handles/
        │   ├── policies/
        │   └── detail/
        ├── slots_container_bundle_agent/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   ├── views/
        │   ├── handles/
        │   ├── policies/
        │   ├── contracts/
        │   └── detail/
        ├── round_manager/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   │   ├── transitions/
        │   │   └── guards/
        │   ├── views/
        │   ├── handles/
        │   ├── contracts/
        │   └── detail/
        ├── reference_precalculator/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── views/
        │   ├── handles/
        │   └── detail/
        ├── dispatcher/
        │   ├── docs/
        │   ├── tests/
        │   ├── carriers/
        │   ├── state/
        │   │   ├── transitions/
        │   │   └── guards/
        │   ├── hosted_ports/
        │   ├── outbound_adapters/
        │   ├── views/
        │   ├── handles/
        │   ├── policies/
        │   ├── contracts/
        │   └── detail/
        └── communications/
            ├── docs/
            ├── tests/
            ├── log_level_api_feeding/
            │   ├── docs/
            │   ├── tests/
            │   ├── carriers/
            │   ├── hosted_ports/
            │   ├── outbound_adapters/
            │   ├── views/
            │   ├── handles/
            │   └── detail/
            └── registry_delivery/
                ├── docs/
                ├── tests/
                ├── carriers/
                ├── hosted_ports/
                ├── outbound_adapters/
                ├── views/
                ├── handles/
                ├── contracts/
                └── detail/
```

### 4.2 Draft Interpretation Rule

```text id="asdt-fs-005-draft-interpretation-rule"
A folder shown in this draft is a proposed semantic location, not a commitment
to create files inside it immediately.
```

An empty folder should not be created unless the repository policy allows placeholder documentation such as `.gitkeep` or local `README.md`.

### 4.3 Optional Subfolder Rule

The presence of a subfolder in this draft means:

```text
This subfolder is currently allowed if its local meaning is justified.
```

It does not mean:

```text
This subfolder is mandatory for every implementation stage.
```

---

## 5. Domain-Level Ownership Summary

### 5.1 Root Domain Ownership Matrix

|           Record ID | Domain Folder           | Owns                                                                                                                                   | Does Not Own                                                                                      |
| ------------------: | ----------------------- | -------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| ASDT-FS-005-DOM-001 | `ecosystem_governance/` | Policy type system, policy-facing registries, provider adapters, receiver-port definitions                                             | Log envelope assembly, runtime queue placement, dispatcher handoff, downstream registry internals |
| ASDT-FS-005-DOM-002 | `log_level_api/`        | Content preparation, validation, metadata injection, timestamp stabilization, envelope assembly, write-side bridge                     | Runtime queue internals, dispatcher finality, downstream storage/query lifecycle                  |
| ASDT-FS-005-DOM-003 | `write_side/`           | Runtime placement, slots, containers, waiting lists, moderators, round managers, reference pre-calculation, dispatcher, communications | Envelope assembly internals, policy source ownership, downstream registry implementation          |

### 5.2 Domain Dependency Direction

```text id="asdt-fs-005-domain-dependency-direction"
ecosystem_governance/
→ log_level_api/
→ write_side/
```

This is a semantic dependency direction, not a final include graph.

### 5.3 Cross-Domain Dependency Rule

```text id="asdt-fs-005-cross-domain-rule"
Cross-domain dependency must use approved public surfaces, not private internals.
```

Examples:

1. `log_level_api/` may depend on approved policy types or receiver-port definitions from `ecosystem_governance/`.
2. `write_side/` may depend on approved envelope-facing or feeding surfaces.
3. `write_side/` must not depend on `log_level_api/envelope_assembler/detail/`.
4. `log_level_api/` must not depend on `write_side/slot/detail/`.
5. No domain may depend on downstream registry internals.

---

## 6. `ecosystem_governance/` Structure

### 6.1 Domain Meaning

`ecosystem_governance/` represents assembler-facing policy and ecosystem governance supply.

It owns policy-oriented type definitions, policy registry interaction abstractions, provider adapter surfaces, and receiver-port definitions for consuming domains.

### 6.2 Draft Folder Tree

```text id="asdt-fs-005-ecosystem-tree"
ecosystem_governance/
├── docs/
├── tests/
├── policy_types/
├── policy_registry/
├── provider_adapters/
└── receiver_ports/
    ├── log_level_api/
    └── write_side/
```

### 6.3 Folder Ownership Matrix

|           Record ID | Folder                        | Ownership Meaning                                                             |
| ------------------: | ----------------------------- | ----------------------------------------------------------------------------- |
| ASDT-FS-005-ECO-001 | `ecosystem_governance/docs/`  | Domain-level ecosystem governance documentation                               |
| ASDT-FS-005-ECO-002 | `ecosystem_governance/tests/` | Domain-level ecosystem governance tests                                       |
| ASDT-FS-005-ECO-003 | `policy_types/`               | Policy type vocabulary and policy-facing type structures                      |
| ASDT-FS-005-ECO-004 | `policy_registry/`            | Assembler-facing policy registry abstraction, not external registry ownership |
| ASDT-FS-005-ECO-005 | `provider_adapters/`          | Adapters toward external policy or ecosystem providers                        |
| ASDT-FS-005-ECO-006 | `receiver_ports/`             | Receiver-port definitions for internal consuming domains                      |

### 6.4 `policy_types/`

`policy_types/` owns the policy-oriented type system used by assembler-facing policy governance.

Allowed subfolders:

```text id="asdt-fs-005-policy-types-shape"
policy_types/
├── docs/
├── tests/
├── carriers/
└── detail/
```

It must not own:

1. policy assignment behavior,
2. local policy execution inside `log_level_api/`,
3. dispatcher policy decisions,
4. downstream policy source lifecycle.

### 6.5 `policy_registry/`

`policy_registry/` represents assembler-facing interaction with policy registry concepts.

Allowed subfolders:

```text id="asdt-fs-005-policy-registry-shape"
policy_registry/
├── docs/
├── tests/
├── hosted_ports/
├── outbound_adapters/
├── views/
└── detail/
```

It must not become:

1. the external Policy Registry,
2. a downstream policy database,
3. a policy execution engine,
4. a replacement for `PolicyAssigner`.

### 6.6 `provider_adapters/`

`provider_adapters/` owns adapters toward policy or ecosystem providers.

Allowed subfolders:

```text id="asdt-fs-005-provider-adapters-shape"
provider_adapters/
├── docs/
├── tests/
├── carriers/
├── outbound_adapters/
└── detail/
```

It must not own the provider itself.

### 6.7 `receiver_ports/`

`receiver_ports/` owns internal receiver-port definitions that support domain-facing policy or ecosystem interaction.

Draft shape:

```text id="asdt-fs-005-receiver-ports-shape"
receiver_ports/
├── docs/
├── tests/
├── log_level_api/
│   ├── docs/
│   ├── hosted_ports/
│   └── carriers/
└── write_side/
    ├── docs/
    ├── hosted_ports/
    └── carriers/
```

A receiver port is an interaction surface.

It is not the component that executes the received behavior.

---

## 7. `log_level_api/` Structure

### 7.1 Domain Meaning

`log_level_api/` represents assembler-side preparation API and envelope production.

It owns content-facing preparation, validation, metadata injection, timestamp stabilization, policy assignment at the API preparation level, envelope assembly, and bridge interaction toward write-side runtime placement.

### 7.2 Draft Folder Tree

```text id="asdt-fs-005-log-level-api-tree"
log_level_api/
├── docs/
├── tests/
├── content/
├── envelope/
├── validator/
├── metadata_injector/
├── timestamp_stabilizer/
├── policy_assignment/
├── envelope_assembler/
└── write_side_bridge/
```

### 7.3 Folder Ownership Matrix

|           Record ID | Folder                  | Ownership Meaning                                                     |
| ------------------: | ----------------------- | --------------------------------------------------------------------- |
| ASDT-FS-005-API-001 | `content/`              | Content-facing material before or during preparation                  |
| ASDT-FS-005-API-002 | `envelope/`             | Log Level Envelope carrier model and envelope-local surfaces          |
| ASDT-FS-005-API-003 | `validator/`            | Validation behavior for preparation input and envelope readiness      |
| ASDT-FS-005-API-004 | `metadata_injector/`    | Metadata preparation and schema/directive-governed metadata injection |
| ASDT-FS-005-API-005 | `timestamp_stabilizer/` | Timestamp stabilization before dispatch eligibility                   |
| ASDT-FS-005-API-006 | `policy_assignment/`    | API-side policy assignment mediation                                  |
| ASDT-FS-005-API-007 | `envelope_assembler/`   | Composition of prepared material into Log Level Envelope              |
| ASDT-FS-005-API-008 | `write_side_bridge/`    | Approved bridge surface toward write-side placement/admission         |

### 7.4 `content/`

`content/` owns content-facing representations before or during preparation.

Allowed subfolders:

```text id="asdt-fs-005-content-shape"
content/
├── docs/
├── tests/
├── views/
├── handles/
└── detail/
```

It must not replace `envelope/`.

Raw content must not be treated as a prepared Log Level Envelope.

### 7.5 `envelope/`

`envelope/` owns the Log Level Envelope carrier model.

Allowed subfolders:

```text id="asdt-fs-005-envelope-shape"
envelope/
├── docs/
├── tests/
├── views/
├── handles/
└── detail/
```

`envelope/` must not own:

1. envelope assembly behavior,
2. runtime placement,
3. dispatcher handoff,
4. downstream registry records.

The `Envelope Assembler` produces the envelope.

The envelope itself is a carrier object.

### 7.6 `validator/`

`validator/` owns validation behavior.

Allowed subfolders:

```text id="asdt-fs-005-validator-shape"
validator/
├── docs/
├── tests/
├── carriers/
├── state/
├── policies/
├── contracts/
└── detail/
```

`validator/` may consume policy-governed constraints.

It must not own the external policy source.

### 7.7 `metadata_injector/`

`metadata_injector/` owns metadata preparation behavior.

Allowed subfolders:

```text id="asdt-fs-005-metadata-injector-shape"
metadata_injector/
├── docs/
├── tests/
├── carriers/
├── state/
├── contracts/
└── detail/
```

`policies/` is not included by default.

It may only be added if a later formal contract explicitly changes metadata injection into a local policy-hosting concern.

### 7.8 `timestamp_stabilizer/`

`timestamp_stabilizer/` owns timestamp stabilization behavior.

Allowed subfolders:

```text id="asdt-fs-005-timestamp-stabilizer-shape"
timestamp_stabilizer/
├── docs/
├── tests/
├── carriers/
├── state/
├── policies/
├── contracts/
└── detail/
```

It must not become downstream query-time timestamp interpretation.

### 7.9 `policy_assignment/`

`policy_assignment/` owns API-side policy assignment mediation.

Allowed subfolders:

```text id="asdt-fs-005-api-policy-assignment-shape"
policy_assignment/
├── docs/
├── tests/
├── carriers/
├── hosted_ports/
├── outbound_adapters/
├── policies/
├── contracts/
├── views/
└── detail/
```

It must not own policy source lifecycle.

### 7.10 `envelope_assembler/`

`envelope_assembler/` owns the assembly behavior that produces the Log Level Envelope.

Allowed subfolders:

```text id="asdt-fs-005-envelope-assembler-shape"
envelope_assembler/
├── docs/
├── tests/
├── carriers/
├── state/
├── contracts/
└── detail/
```

It may coordinate:

1. validation result,
2. metadata preparation result,
3. timestamp stabilization result,
4. policy assignment result,
5. envelope carrier construction.

It must not become:

1. the envelope itself,
2. the write-side runtime,
3. the dispatcher,
4. the downstream registry.

### 7.11 `write_side_bridge/`

`write_side_bridge/` owns the approved bridge from API preparation to write-side admission or placement interaction.

Allowed subfolders:

```text id="asdt-fs-005-write-side-bridge-shape"
write_side_bridge/
├── docs/
├── tests/
├── carriers/
├── hosted_ports/
├── outbound_adapters/
├── views/
├── handles/
└── detail/
```

It must not expose write-side private internals.

---

## 8. `write_side/` Structure

### 8.1 Domain Meaning

`write_side/` owns assembler-side runtime placement, queue/container coordination, waiting lists, moderation, round coordination, reference pre-calculation, dispatcher behavior, and communication boundaries.

It is not a message broker.

It is not a downstream registry.

It is not a storage engine.

### 8.2 Draft Folder Tree

```text id="asdt-fs-005-write-side-tree"
write_side/
├── docs/
├── tests/
├── ingress/
├── policy_assignment/
├── slot/
├── slots_container/
├── waiting_list/
├── slots_container_moderator/
├── slots_container_bundle_agent/
├── round_manager/
├── reference_precalculator/
├── dispatcher/
└── communications/
    ├── log_level_api_feeding/
    └── registry_delivery/
```

### 8.3 Folder Ownership Matrix

|          Record ID | Folder                          | Ownership Meaning                                                 |
| -----------------: | ------------------------------- | ----------------------------------------------------------------- |
| ASDT-FS-005-WS-001 | `ingress/`                      | Write-side admission surface for prepared envelopes               |
| ASDT-FS-005-WS-002 | `policy_assignment/`            | Write-side policy assignment or policy-governed runtime mediation |
| ASDT-FS-005-WS-003 | `slot/`                         | Slot semantics, occupancy, and slot-local state                   |
| ASDT-FS-005-WS-004 | `slots_container/`              | Queue-container structure and placement ownership                 |
| ASDT-FS-005-WS-005 | `waiting_list/`                 | Waiting-list structures carrying queue/container identifiers      |
| ASDT-FS-005-WS-006 | `slots_container_moderator/`    | Single-container moderation and reinitialization behavior         |
| ASDT-FS-005-WS-007 | `slots_container_bundle_agent/` | Queue bundle topology and bundle-level coordination               |
| ASDT-FS-005-WS-008 | `round_manager/`                | Writing/feeding and dispatching/delivery round coordination       |
| ASDT-FS-005-WS-009 | `reference_precalculator/`      | Reference pre-calculation before dispatch or placement use        |
| ASDT-FS-005-WS-010 | `dispatcher/`                   | Final assembler-side outbound actor                               |
| ASDT-FS-005-WS-011 | `communications/`               | Boundary-specific communication folders                           |

### 8.4 `ingress/`

`ingress/` owns write-side admission of prepared Log Level Envelopes into runtime placement surfaces.

Allowed subfolders:

```text id="asdt-fs-005-ingress-shape"
ingress/
├── docs/
├── tests/
├── carriers/
├── hosted_ports/
├── views/
├── handles/
└── detail/
```

It must not perform envelope assembly.

It receives already prepared envelope material through approved surfaces.

### 8.5 `slot/`

`slot/` owns slot semantics.

Allowed subfolders:

```text id="asdt-fs-005-slot-shape"
slot/
├── docs/
├── tests/
├── carriers/
├── state/
│   ├── transitions/
│   └── guards/
├── views/
├── handles/
├── contracts/
└── detail/
```

It must not own queue-container topology.

It must not own envelope lifecycle beyond slot occupancy semantics.

### 8.6 `slots_container/`

`slots_container/` owns queue-container structure.

Allowed subfolders:

```text id="asdt-fs-005-slots-container-shape"
slots_container/
├── docs/
├── tests/
├── carriers/
├── state/
│   ├── transitions/
│   └── guards/
├── views/
├── handles/
├── contracts/
└── detail/
```

It must not become a message broker.

It owns container structure and placement behavior, not downstream lifecycle.

### 8.7 `waiting_list/`

`waiting_list/` owns waiting-list structures.

Allowed subfolders:

```text id="asdt-fs-005-waiting-list-shape"
waiting_list/
├── docs/
├── tests/
├── carriers/
├── state/
├── views/
├── handles/
└── detail/
```

Waiting lists may carry queue-container identifiers.

They must not become generic envelope stores.

### 8.8 `slots_container_moderator/`

`slots_container_moderator/` owns moderation for a single queue container.

Allowed subfolders:

```text id="asdt-fs-005-moderator-shape"
slots_container_moderator/
├── docs/
├── tests/
├── carriers/
├── state/
├── views/
├── handles/
├── policies/
└── detail/
```

It must not own the full queue bundle.

### 8.9 `slots_container_bundle_agent/`

`slots_container_bundle_agent/` owns bundle-level container coordination.

Allowed subfolders:

```text id="asdt-fs-005-bundle-agent-shape"
slots_container_bundle_agent/
├── docs/
├── tests/
├── carriers/
├── state/
├── views/
├── handles/
├── policies/
├── contracts/
└── detail/
```

It must not become a storage lifecycle owner.

### 8.10 `round_manager/`

`round_manager/` owns round coordination.

Allowed subfolders:

```text id="asdt-fs-005-round-manager-shape"
round_manager/
├── docs/
├── tests/
├── carriers/
├── state/
│   ├── transitions/
│   └── guards/
├── views/
├── handles/
├── contracts/
└── detail/
```

This folder may later distinguish:

1. writing / feeding round,
2. dispatching / delivery round.

However, those should not become separate root folders unless their semantic ownership diverges enough to justify separate folders.

### 8.11 `reference_precalculator/`

`reference_precalculator/` owns pre-calculation of references used by write-side coordination or dispatch.

Allowed subfolders:

```text id="asdt-fs-005-reference-precalculator-shape"
reference_precalculator/
├── docs/
├── tests/
├── carriers/
├── views/
├── handles/
└── detail/
```

It must not own dispatcher behavior or downstream record identity.

### 8.12 `dispatcher/`

`dispatcher/` owns final assembler-side outbound dispatch behavior.

Allowed subfolders:

```text id="asdt-fs-005-dispatcher-shape"
dispatcher/
├── docs/
├── tests/
├── carriers/
├── state/
│   ├── transitions/
│   └── guards/
├── hosted_ports/
├── outbound_adapters/
├── views/
├── handles/
├── policies/
├── contracts/
└── detail/
```

`dispatcher/` must preserve:

1. dispatcher finality,
2. handoff boundary discipline,
3. post-handoff non-ownership,
4. registry non-ownership,
5. downstream lifecycle exclusion.

### 8.13 `communications/`

`communications/` owns boundary-specific communication folders.

Draft shape:

```text id="asdt-fs-005-communications-shape"
communications/
├── docs/
├── tests/
├── log_level_api_feeding/
└── registry_delivery/
```

`communications/` is not a generic transport layer.

Each child boundary must have a specific semantic purpose.

---

## 9. Communication Boundary Folders

### 9.1 `log_level_api_feeding/`

`log_level_api_feeding/` owns the boundary between prepared API-side envelope production and write-side admission/placement.

Draft shape:

```text id="asdt-fs-005-log-level-api-feeding-shape"
log_level_api_feeding/
├── docs/
├── tests/
├── carriers/
├── hosted_ports/
├── outbound_adapters/
├── views/
├── handles/
└── detail/
```

It may own:

1. feeding-boundary carriers,
2. write-side receiving surface,
3. placement request/result abstractions,
4. readiness views,
5. safe handles.

It must not own:

1. envelope assembler internals,
2. slot private internals,
3. slots-container private internals,
4. round-manager private state,
5. dispatcher handoff behavior.

### 9.2 `registry_delivery/`

`registry_delivery/` owns the registry-facing delivery boundary.

Draft shape:

```text id="asdt-fs-005-registry-delivery-shape"
registry_delivery/
├── docs/
├── tests/
├── carriers/
├── hosted_ports/
├── outbound_adapters/
├── views/
├── handles/
├── contracts/
└── detail/
```

It may own:

1. handoff material carriers,
2. handoff evidence carriers,
3. delivery acknowledgement carriers,
4. registry-facing adapter surfaces,
5. handoff-readiness views,
6. delivery handles.

It must not own:

1. downstream registry schema,
2. downstream storage lifecycle,
3. downstream query lifecycle,
4. downstream replay logic,
5. downstream indexing logic,
6. downstream mutation logic.

---

## 10. Folder Dependency Draft

### 10.1 Domain Dependency Order

```text id="asdt-fs-005-domain-order"
ecosystem_governance
→ log_level_api
→ write_side
```

### 10.2 Log Level API Internal Dependency Draft

```text id="asdt-fs-005-api-internal-order"
content
→ validator
→ metadata_injector
→ timestamp_stabilizer
→ policy_assignment
→ envelope
→ envelope_assembler
→ write_side_bridge
```

This is a semantic order.

It does not require final include dependencies to follow this exact sequence.

### 10.3 Write Side Internal Dependency Draft

```text id="asdt-fs-005-write-side-internal-order"
ingress
→ policy_assignment
→ slot
→ slots_container
→ waiting_list
→ slots_container_moderator
→ slots_container_bundle_agent
→ round_manager
→ reference_precalculator
→ dispatcher
→ communications/registry_delivery
```

### 10.4 Boundary Dependency Draft

```text id="asdt-fs-005-boundary-order"
log_level_api/write_side_bridge
→ write_side/communications/log_level_api_feeding
→ write_side/ingress
→ write_side/runtime placement folders
→ write_side/dispatcher
→ write_side/communications/registry_delivery
```

### 10.5 Forbidden Dependency Examples

|            Record ID | Forbidden Dependency                                                           | Reason                                         |
| -------------------: | ------------------------------------------------------------------------------ | ---------------------------------------------- |
| ASDT-FS-005-FDEP-001 | `write_side/slot/` depends on `log_level_api/envelope_assembler/detail/`       | Violates private implementation boundary       |
| ASDT-FS-005-FDEP-002 | `log_level_api/metadata_injector/` owns external policy source                 | Violates policy-source non-ownership           |
| ASDT-FS-005-FDEP-003 | `write_side/communications/registry_delivery/` owns downstream registry schema | Violates downstream non-ownership              |
| ASDT-FS-005-FDEP-004 | `write_side/slots_container/` behaves as message broker                        | Violates queue-as-container doctrine           |
| ASDT-FS-005-FDEP-005 | `ecosystem_governance/policy_registry/` becomes policy execution engine        | Collapses registry abstraction into execution  |
| ASDT-FS-005-FDEP-006 | `dispatcher/` depends on registry internals                                    | Violates dispatcher/registry boundary          |
| ASDT-FS-005-FDEP-007 | Any folder depends on another folder’s `detail/`                               | Violates local private implementation boundary |

---

## 11. Public Surface Draft

### 11.1 Public Surface Candidate Folders

The following subfolders may expose approved public surfaces:

1. `hosted_ports/`,
2. `outbound_adapters/`,
3. `carriers/`,
4. `views/`,
5. `handles/`,
6. local `contracts/` where justified.

### 11.2 Private Surface Folders

The following folders are private or local-only by default:

1. `detail/`,
2. `tests/`,
3. `tests/fixtures/`,
4. internal `state/`,
5. internal `state/transitions/`,
6. internal `state/guards/`.

### 11.3 Public Surface Rule

```text id="asdt-fs-005-public-surface-rule"
Cross-folder interaction must use approved public surfaces.
```

A public surface must be explicitly justified.

A private folder must not become public through convenience includes.

---

## 12. Deferred File Inventory

### 12.1 Deferred Decisions

This document intentionally defers:

1. `.hpp` file names,
2. `.cpp` file names if any,
3. namespace declarations,
4. class names,
5. trait names,
6. CRTP base names,
7. final CMake target names,
8. exact include graph,
9. test file names,
10. example file names.

### 12.2 File Derivation Rule

```text id="asdt-fs-005-file-derivation-rule"
Files must derive from accepted folder ownership, not reshape folder ownership.
```

### 12.3 Future File Inventory Pack

A later document should define:

```text id="asdt-fs-005-next-file-inventory"
ASDT-FS-006_File_Inventory_Derivation_Rules.md
```

or equivalent.

That future document should derive file inventories from:

1. folder ownership,
2. component responsibilities,
3. contract representations,
4. carriers,
5. states,
6. ports,
7. adapters,
8. tests,
9. local docs.

---

## 13. Forbidden Folder Patterns

### 13.1 Forbidden or Discouraged Generic Folders

The following folders remain discouraged unless explicitly justified:

```text id="asdt-fs-005-forbidden-generic-folders"
utils/
helpers/
common/
misc/
data/
models/
services/
interfaces/
impl/
types/
```

### 13.2 Replacement Guidance

| Discouraged Folder | Preferred Alternatives                                                      |
| ------------------ | --------------------------------------------------------------------------- |
| `utils/`           | `detail/`, `handles/`, `views/`, or a real component folder                 |
| `helpers/`         | `detail/` or a named local component                                        |
| `common/`          | a shared semantic owner with explicit scope                                 |
| `models/`          | `carriers/`, `state/`, `views/`, or domain-specific root                    |
| `interfaces/`      | `hosted_ports/`, `outbound_adapters/`, or justified `contracts/`            |
| `impl/`            | `detail/`                                                                   |
| `data/`            | `carriers/`, `state/`, `fixtures/`, `policies/`, or `views/`                |
| `services/`        | actor/component names such as `dispatcher/`, `validator/`, `round_manager/` |

### 13.3 Generic Folder Rule

```text id="asdt-fs-005-generic-folder-rule"
A generic folder must not hide an unresolved ownership decision.
```

---

## 14. Current Draft Validation Questions

Before accepting this folder draft, reviewers should answer:

|           Record ID | Question                                                           | Required Direction |
| ------------------: | ------------------------------------------------------------------ | ------------------ |
| ASDT-FS-005-VAL-001 | Does every root folder represent a semantic implementation domain? | Yes                |
| ASDT-FS-005-VAL-002 | Does every first-level domain child have a clear owner?            | Yes                |
| ASDT-FS-005-VAL-003 | Are any folders generic ownership substitutes?                     | No                 |
| ASDT-FS-005-VAL-004 | Does any folder imply downstream registry ownership?               | No                 |
| ASDT-FS-005-VAL-005 | Does any folder expose another component’s `detail/`?              | No                 |
| ASDT-FS-005-VAL-006 | Are docs and tests local to their parent scope?                    | Yes                |
| ASDT-FS-005-VAL-007 | Are carriers placed under the narrowest valid owner?               | Yes                |
| ASDT-FS-005-VAL-008 | Are state folders placed under behavior owners?                    | Yes                |
| ASDT-FS-005-VAL-009 | Are ports and adapters distinguished?                              | Yes                |
| ASDT-FS-005-VAL-010 | Does `registry_delivery/` avoid downstream lifecycle ownership?    | Yes                |
| ASDT-FS-005-VAL-011 | Does `log_level_api_feeding/` avoid exposing write-side internals? | Yes                |
| ASDT-FS-005-VAL-012 | Is file inventory still deferred?                                  | Yes                |

---

## 15. Freeze Readiness

### 15.1 Freeze Status

This draft is not frozen.

It may be used as the baseline for review.

### 15.2 Freeze Preconditions

The folder structure may be frozen only when:

1. all root domains are accepted,
2. all first-level domain folders have ownership records,
3. all optional subfolders are justified,
4. no forbidden generic folders remain,
5. `detail/` privacy is enforced,
6. cross-domain public surfaces are declared,
7. downstream non-ownership is preserved,
8. communication boundary folders are accepted,
9. docs and tests placement is local and consistent,
10. file inventory remains deferred until the next derivation step.

### 15.3 Freeze Artifacts

A folder-structure freeze should produce:

|              Record ID | Artifact                          | Purpose                                          |
| ---------------------: | --------------------------------- | ------------------------------------------------ |
| ASDT-FS-005-FREEZE-001 | Root Domain Matrix                | Confirms root domains and their ownership        |
| ASDT-FS-005-FREEZE-002 | Domain Child Folder Matrix        | Confirms first-level domain children             |
| ASDT-FS-005-FREEZE-003 | Component Subfolder Matrix        | Confirms allowed subfolders per component        |
| ASDT-FS-005-FREEZE-004 | Public Surface Matrix             | Confirms approved cross-folder surfaces          |
| ASDT-FS-005-FREEZE-005 | Private Surface Matrix            | Confirms protected `detail/` and state internals |
| ASDT-FS-005-FREEZE-006 | Dependency Direction Matrix       | Confirms allowed semantic dependency direction   |
| ASDT-FS-005-FREEZE-007 | Forbidden Folder Rejection Matrix | Records rejected generic or invalid folders      |
| ASDT-FS-005-FREEZE-008 | Deferred File Inventory Notice    | Confirms that file derivation remains later work |

---

## 16. Summary

This document defines the current folder structure draft for the Assembler System Digital Twin Filesystem.

The core conclusions are:

1. the current root implementation domains remain `ecosystem_governance/`, `log_level_api/`, and `write_side/`,
2. folder structure reflects semantic ownership, not storage convenience,
3. domain-local `docs/` and `tests/` remain close to the owner,
4. `ecosystem_governance/` owns policy-facing supply and receiver-port definitions,
5. `log_level_api/` owns content preparation and envelope assembly,
6. `write_side/` owns runtime placement and dispatcher-mediated handoff,
7. communication boundaries are explicit under `write_side/communications/`,
8. `detail/` remains private to its nearest semantic owner,
9. generic folders remain discouraged,
10. downstream registry internals remain excluded,
11. final file inventory remains deferred.

The next strongest document is:

```text id="asdt-fs-005-next-doc"
ASDT-FS-006_File_Inventory_Derivation_Rules.md
```

This next document should define how files are derived from the frozen folder structure without letting file names, class names, or implementation convenience reshape the architecture.

```
```
