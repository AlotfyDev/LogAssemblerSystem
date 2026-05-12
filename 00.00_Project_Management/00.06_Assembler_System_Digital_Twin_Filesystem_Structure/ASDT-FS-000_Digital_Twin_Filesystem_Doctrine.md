
# ASDT-FS-000 — Digital Twin Filesystem Doctrine

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-000-DOC-001 | Document Title | Digital Twin Filesystem Doctrine |
| ASDT-FS-000-DOC-002 | File Name | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md` |
| ASDT-FS-000-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-000-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-000-DOC-005 | Project | Assembler System |
| ASDT-FS-000-DOC-006 | Primary Language | English |
| ASDT-FS-000-DOC-007 | Scope Level | Filesystem doctrine, folder taxonomy, folder ownership, folder-level documentation and testing |
| ASDT-FS-000-DOC-008 | Implementation Language Direction | C++17, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-000-DOC-009 | Status | Pre-Implementation Folder Doctrine |
| ASDT-FS-000-DOC-010 | File Inventory Status | Deferred |
| ASDT-FS-000-DOC-011 | Primary Rule | Folder taxonomy must be stabilized before file inventory |
| ASDT-FS-000-DOC-012 | Governing Principle | The filesystem is a logical digital twin of the system model, not a passive storage layout |

---

## 2. Purpose

### 2.1 Purpose Statement

This document defines the doctrine governing the filesystem structure of the Assembler System as a logical digital twin of the system’s architectural, domain, component, actor, carrier, state, port, adapter, and runtime coordination model.

The purpose of this document is not to enumerate final C++ files.

The purpose of this document is to establish how folders are derived, owned, ordered, scoped, documented, and tested before file-level inventories are produced.

### 2.2 Central Claim

```text
The filesystem is not merely a storage layout.

It is a logical mirror of the Assembler System’s architectural and design structure.
````

The filesystem must therefore express:

1. root DDD implementation domains,
2. domain-local internal roots,
3. component and actor departments,
4. shared semantic roots,
5. local carriers,
6. local state models,
7. hosted ports,
8. outbound adapters,
9. communication boundaries,
10. local documentation scopes,
11. local testing scopes,
12. dependency order,
13. ownership boundaries,
14. forbidden placements,
15. delayed file inventory derivation.

---

## 3. Folder-First Doctrine

### 3.1 Rule

```text
Folders are stabilized before files.
```

### 3.2 Meaning

The first stabilization target is the folder taxonomy.

This means that the project must first decide:

1. which root implementation domains exist,
2. which internal roots belong inside each domain,
3. which folders represent actors, components, carriers, ports, adapters, states, communications, or other meaningful semantic levels,
4. which folders may contain local `docs/`,
5. which folders may contain local `tests/`,
6. which folders are forbidden because they obscure semantic ownership,
7. which dependency direction governs the order of folders.

Only after these decisions are accepted should the project derive final file inventories.

### 3.3 File Inventory Deferral

|          Record ID | Decision                                             | Explanation                                                                                              |
| -----------------: | ---------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-FD-001 | Final header inventory is deferred                   | Specific `.hpp` files are not stabilized in this doctrine                                                |
| ASDT-FS-000-FD-002 | Previous file names are illustrative                 | Names such as `TValidator.hpp` or `TSlot.hpp` may be useful examples but are not frozen by this document |
| ASDT-FS-000-FD-003 | Folder meaning precedes file naming                  | File names must derive from accepted folder ownership and component boundaries                           |
| ASDT-FS-000-FD-004 | File inventory requires a later derivation document  | File-level derivation belongs to a later ASDT-FS document                                                |
| ASDT-FS-000-FD-005 | File names must not reshape architecture prematurely | Early file naming must not override folder-level semantics                                               |

---

## 4. Digital Twin Definition

### 4.1 Definition

In this documentation pack, **Digital Twin Filesystem** means:

```text
A filesystem structure whose folders intentionally mirror the logical structure,
ownership boundaries, dependency order, and behavioral architecture of the system.
```

The filesystem becomes a readable operational map of the system’s architecture.

### 4.2 Digital Twin Properties

|          Record ID | Property                 | Meaning                                                                                                                                         |
| -----------------: | ------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-DT-001 | Mirroring                | Folders reflect system concepts rather than arbitrary storage convenience                                                                       |
| ASDT-FS-000-DT-002 | Ownership                | Each meaningful folder owns a bounded semantic scope                                                                                            |
| ASDT-FS-000-DT-003 | Locality                 | Documentation, tests, carriers, ports, adapters, and state models remain close to the folder that owns their meaning                            |
| ASDT-FS-000-DT-004 | Dependency Visibility    | Folder order reflects dependency order where practical                                                                                          |
| ASDT-FS-000-DT-005 | Anti-Collapse            | Folders prevent category collapse between domains, actors, carriers, registries, ports, adapters, contracts, states, and implementation details |
| ASDT-FS-000-DT-006 | Implementation Proximity | The structure is close enough to guide C++ implementation without becoming code-first                                                           |
| ASDT-FS-000-DT-007 | Explainability           | Each meaningful level can explain itself through local `docs/`                                                                                  |
| ASDT-FS-000-DT-008 | Testability              | Each meaningful level can verify itself through local `tests/`                                                                                  |
| ASDT-FS-000-DT-009 | Deferred Granularity     | File-level detail appears only after folder-level meaning is stable                                                                             |
| ASDT-FS-000-DT-010 | Architectural Continuity | Filesystem structure remains connected to system goals, glossary concepts, obligations, and dependency rules                                    |

---

## 5. Scope

### 5.1 In Scope

This doctrine governs:

|           Record ID | In-Scope Area               | Description                                                                                        |
| ------------------: | --------------------------- | -------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-SCP-001 | Root implementation domains | The top-level implementation folders under the Assembler namespace                                 |
| ASDT-FS-000-SCP-002 | Domain internal roots       | The first layer of meaningful folders inside each root domain                                      |
| ASDT-FS-000-SCP-003 | Component departments       | Actor/component folders that own an abstraction surface                                            |
| ASDT-FS-000-SCP-004 | Shared semantic roots       | Domain-level folders shared by multiple actors/components                                          |
| ASDT-FS-000-SCP-005 | Local docs model            | Rules for `docs/` at every meaningful folder level                                                 |
| ASDT-FS-000-SCP-006 | Local tests model           | Rules for `tests/` at every meaningful folder level                                                |
| ASDT-FS-000-SCP-007 | Local subfolder classes     | Folder classes such as `carriers/`, `hosted_ports/`, `outbound_adapters/`, `state/`, and `detail/` |
| ASDT-FS-000-SCP-008 | Contract realization model  | The rule that ports and adapters realize contracts materially                                      |
| ASDT-FS-000-SCP-009 | State model placement       | The rule for placing `state/` inside the owning folder                                             |
| ASDT-FS-000-SCP-010 | Communication placement     | The rule that bridges and communications are placed after internal structures are established      |

### 5.2 Out of Scope

This document does not define:

|           Record ID | Out-of-Scope Area                  | Reason                                                              |
| ------------------: | ---------------------------------- | ------------------------------------------------------------------- |
| ASDT-FS-000-OOS-001 | Final `.hpp` file inventory        | Deferred to later derivation                                        |
| ASDT-FS-000-OOS-002 | Final C++ class definitions        | Requires implementation design documents                            |
| ASDT-FS-000-OOS-003 | Final method signatures            | Requires component-level file and API derivation                    |
| ASDT-FS-000-OOS-004 | Build system structure             | CMake or build layout is downstream of implementation packaging     |
| ASDT-FS-000-OOS-005 | Repository-wide documentation tree | This document focuses on implementation-domain filesystem semantics |
| ASDT-FS-000-OOS-006 | Final tests implementation         | This document defines test placement, not test code                 |
| ASDT-FS-000-OOS-007 | Final bridge protocol details      | Communications are recognized but detailed later                    |
| ASDT-FS-000-OOS-008 | Downstream registry implementation | Registry internals remain outside Assembler ownership               |

---

## 6. Root DDD Implementation Domain Doctrine

### 6.1 Rule

```text
Root implementation folders represent DDD implementation domains.
```

They are not documentation folders.

They are not generic technical folders.

They are not convenience groupings.

### 6.2 Accepted Root Implementation Domains

The current accepted root DDD implementation domains are:

```text
ecosystem_governance/
log_level_api/
write_side/
```

|          Record ID | Root Domain             | Meaning                                                                                                                                                                                         |
| -----------------: | ----------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-RD-001 | `ecosystem_governance/` | Policy supply, policy type system, registries, provider adapters, and consumer-specific receiver ports from the Assembler System perspective                                                    |
| ASDT-FS-000-RD-002 | `log_level_api/`        | Content preparation, policy assignment, validation, timestamp stabilization, metadata injection, envelope assembly, API façade, and write-side bridge hosting                                   |
| ASDT-FS-000-RD-003 | `write_side/`           | Write-side runtime coordination, policy assignment, slots, slots containers, waiting lists, moderators, bundle agent, round managers, reference pre-calculation, dispatcher, and communications |

### 6.3 Non-Domain Repository Areas

The following are not root DDD implementation domains:

```text
docs/
governance/
tools/
cmake/
tests/
examples/
```

They may exist in the repository, but they are support areas, not root implementation domains.

|          Record ID | Folder        | Classification     | Reason                                                               |
| -----------------: | ------------- | ------------------ | -------------------------------------------------------------------- |
| ASDT-FS-000-ND-001 | `docs/`       | Repository support | Holds general project documentation                                  |
| ASDT-FS-000-ND-002 | `governance/` | Repository support | Holds glossary, schemas, mappings, and validation artifacts          |
| ASDT-FS-000-ND-003 | `tools/`      | Repository support | Holds generation, validation, linting, or audit tools                |
| ASDT-FS-000-ND-004 | `cmake/`      | Technical support  | Supports build configuration                                         |
| ASDT-FS-000-ND-005 | `tests/`      | Repository support | Holds integration, conformance, cross-domain, and system-level tests |
| ASDT-FS-000-ND-006 | `examples/`   | Repository support | Holds usage examples and integration demonstrations                  |

---

## 7. Domain Internal Root Doctrine

### 7.1 Rule

```text
Inside each root domain, the first folder layer must reflect that domain’s own semantic structure.
```

There is no universal internal folder taxonomy applied blindly to every domain.

### 7.2 Forbidden Generic First-Layer Pattern

A domain must not default to:

```text
domain/
├── data/
├── carriers/
├── actors/
├── contracts/
├── capabilities/
├── states/
└── utils/
```

This pattern is forbidden because it hides domain meaning behind generic technical categories.

### 7.3 Domain-Specific Internal Roots

Each domain uses its own internal roots.

#### 7.3.1 `ecosystem_governance/`

```text
ecosystem_governance/
├── policy_type_system/
├── policy_registries/
├── provider_adapters/
└── receiver_ports/
    ├── log_level_api/
    └── write_side/
```

#### 7.3.2 `log_level_api/`

```text
log_level_api/
├── policy_assignment/
├── content/
├── validator/
├── timestamp_stabilizer/
├── metadata_injector/
├── envelope/
├── envelope_assembler/
├── write_side_bridge/
└── api_facade/
```

#### 7.3.3 `write_side/`

```text
write_side/
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

---

## 8. Contract Realization Doctrine

### 8.1 Rule

```text
A contract lives at the narrowest component scope that owns its meaning.
```

### 8.2 Rule

```text
Ports and adapters are contract-bearing components.
```

### 8.3 Rule

```text
Generic contracts folders are discouraged unless the contract is genuinely shared across multiple components.
```

### 8.4 Meaning

The architecture may define contracts as governing principles.
The filesystem should not automatically create `contracts/` folders as material representations of those principles.

The material implementation-facing realization of contracts normally appears as:

1. hosted ports,
2. receiver ports,
3. outbound adapters,
4. provider adapters,
5. traits,
6. component public surfaces,
7. DTO or carrier shapes where applicable,
8. local docs explaining the obligation,
9. local tests validating behavior.

### 8.5 Contract Type Names

This doctrine does not forbid C++ type names containing the word `Contract`.

For example, a later file inventory may include names such as:

```text
TPolicyTypeContract.hpp
TPolicyProviderAdapterContract.hpp
TWriteSidePolicyPortContract.hpp
```

However, this does not imply the existence of a generic `contracts/` folder.

### 8.6 Contract Placement Table

|          Record ID | Contract Meaning                            | Preferred Physical Realization                                    |
| -----------------: | ------------------------------------------- | ----------------------------------------------------------------- |
| ASDT-FS-000-CR-001 | Policy supply relation                      | `provider_adapters/` and `receiver_ports/`                        |
| ASDT-FS-000-CR-002 | Client-side injectable consumption          | `receiver_ports/<consumer>/` and consuming domain `hosted_ports/` |
| ASDT-FS-000-CR-003 | Outbound signaling                          | `outbound_adapters/`                                              |
| ASDT-FS-000-CR-004 | Hosted external port                        | `hosted_ports/`                                                   |
| ASDT-FS-000-CR-005 | Compile-time capability requirement         | `Traits` type, not a folder by default                            |
| ASDT-FS-000-CR-006 | Local obligation                            | Local `docs/` and `tests/` plus owning component code             |
| ASDT-FS-000-CR-007 | Shared protocol used by multiple components | Shared folder only if it cannot be owned more narrowly            |

---

## 9. Administrative Perspective Doctrine

### 9.1 Rule

```text
The administrative perspective is a domain-level interpretation of ecosystem_governance, not necessarily a separate implementation folder.
```

### 9.2 Meaning

From the Assembler System perspective, `ecosystem_governance/` represents the administrative and governance-facing policy supply layer.

However, this does not require a separate `administrative/` folder.

The implementation mirror of the administrative/consuming relation is:

```text
ecosystem_governance/
└── receiver_ports/
    ├── log_level_api/
    └── write_side/
```

### 9.3 Receiver Ports

```text
Consumer-specific receiver ports are the concrete implementation mirror of the administrative/consuming policy-feeding relation.
```

|          Record ID | Receiver Port Folder            | Meaning                                                               |
| -----------------: | ------------------------------- | --------------------------------------------------------------------- |
| ASDT-FS-000-AP-001 | `receiver_ports/log_level_api/` | Client-side injectable policy port and bundle DTO for `log_level_api` |
| ASDT-FS-000-AP-002 | `receiver_ports/write_side/`    | Client-side injectable policy port and bundle DTO for `write_side`    |

---

## 10. Component Department Doctrine

### 10.1 Rule

```text
A folder becomes a component or actor department when it owns a public abstraction surface or an implementation-facing semantic responsibility.
```

### 10.2 Component Department Examples

|          Record ID | Folder                                            | Department Type                            |
| -----------------: | ------------------------------------------------- | ------------------------------------------ |
| ASDT-FS-000-CD-001 | `log_level_api/validator/`                        | Component / actor department               |
| ASDT-FS-000-CD-002 | `log_level_api/envelope_assembler/`               | Composition component department           |
| ASDT-FS-000-CD-003 | `write_side/slots_container_moderator/`           | Actor department                           |
| ASDT-FS-000-CD-004 | `write_side/round_manager/`                       | Actor/component department                 |
| ASDT-FS-000-CD-005 | `write_side/reference_precalculator/`             | Component department                       |
| ASDT-FS-000-CD-006 | `write_side/dispatcher/`                          | Actor department                           |
| ASDT-FS-000-CD-007 | `ecosystem_governance/provider_adapters/`         | Adapter department                         |
| ASDT-FS-000-CD-008 | `ecosystem_governance/receiver_ports/write_side/` | Consumer-specific receiver port department |

### 10.3 Component Surface

Every non-trivial component department is expected to eventually own:

1. a public abstraction surface,
2. a traits or template discipline if needed,
3. local docs,
4. local tests,
5. local carriers if needed,
6. local ports or adapters if needed,
7. local state model if needed,
8. private detail if needed.

The final file names are deferred.

---

## 11. Meaningful Folder Doctrine

### 11.1 Rule

```text
Every meaningful folder may contain local docs/ and tests/.
```

### 11.2 Scope-Local Rule

```text
docs/ and tests/ are scope-local.
```

They document and verify the semantics of their containing folder.

### 11.3 Meaningful Folder Definition

A folder is meaningful when it represents one or more of the following:

1. root implementation domain,
2. domain internal root,
3. shared semantic root,
4. actor,
5. component,
6. carrier family,
7. hosted port area,
8. outbound adapter area,
9. state model,
10. communication boundary,
11. bridge,
12. policy assignment area,
13. runtime coordination area,
14. dispatcher or handoff area,
15. folder-level obligation or dependency boundary.

### 11.4 General Folder Pattern

```text
meaningful_folder/
├── docs/
├── tests/
└── level_specific_children/
```

### 11.5 Domain-Level Example

```text
write_side/
├── docs/
├── tests/
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
```

### 11.6 Component-Level Example

```text
write_side/
└── round_manager/
    ├── docs/
    ├── tests/
    ├── carriers/
    ├── state/
    └── detail/
```

### 11.7 State-Level Example

```text
write_side/
└── round_manager/
    └── state/
        ├── docs/
        ├── tests/
        └── detail/
```

---

## 12. Local Documentation Doctrine

### 12.1 Rule

```text
Local docs/ explain the folder that owns them.
```

### 12.2 Repository-Level vs Local Docs

|          Record ID | Docs Location               | Scope                                                                      |
| -----------------: | --------------------------- | -------------------------------------------------------------------------- |
| ASDT-FS-000-LD-001 | Repository-level `docs/`    | System architecture, governance, project-wide doctrine                     |
| ASDT-FS-000-LD-002 | Domain-level `docs/`        | Domain purpose, boundaries, dependencies, exclusions                       |
| ASDT-FS-000-LD-003 | Component-level `docs/`     | Component obligations, behavior, ports/adapters, state model, dependencies |
| ASDT-FS-000-LD-004 | State-level `docs/`         | State definitions, transitions, transition guards, invalid states          |
| ASDT-FS-000-LD-005 | Communication-level `docs/` | Bridge semantics, port/adapter boundaries, leakage prevention              |

### 12.3 Local Docs Content

Local `docs/` may cover:

|           Record ID | Topic                     | Description                                                      |
| ------------------: | ------------------------- | ---------------------------------------------------------------- |
| ASDT-FS-000-LDC-001 | Local role                | What this folder represents                                      |
| ASDT-FS-000-LDC-002 | Obligations               | What the folder must guarantee                                   |
| ASDT-FS-000-LDC-003 | Contract-bearing surfaces | Ports, adapters, traits, DTO shapes, and public surfaces         |
| ASDT-FS-000-LDC-004 | Dependency rules          | What this folder may or must not depend on                       |
| ASDT-FS-000-LDC-005 | State model               | States, transitions, state machines, and snapshots               |
| ASDT-FS-000-LDC-006 | Local carriers            | Locally owned records, handles, reports, assignments, references |
| ASDT-FS-000-LDC-007 | Forbidden ownership       | What must not be placed in this folder                           |
| ASDT-FS-000-LDC-008 | Test rationale            | What local tests must validate                                   |
| ASDT-FS-000-LDC-009 | File rationale            | Later explanation for why specific files exist                   |

---

## 13. Local Testing Doctrine

### 13.1 Rule

```text
Local tests/ verify the folder that owns them.
```

### 13.2 Repository-Level vs Local Tests

|          Record ID | Tests Location               | Scope                                                                            |
| -----------------: | ---------------------------- | -------------------------------------------------------------------------------- |
| ASDT-FS-000-LT-001 | Repository-level `tests/`    | Cross-domain, integration, conformance, regression, and system behavior          |
| ASDT-FS-000-LT-002 | Domain-level `tests/`        | Domain dependency rules and domain-level behavior                                |
| ASDT-FS-000-LT-003 | Component-level `tests/`     | Component obligations, behavior, failure modes, dependency isolation             |
| ASDT-FS-000-LT-004 | State-level `tests/`         | State transitions, invalid transitions, state machine invariants                 |
| ASDT-FS-000-LT-005 | Communication-level `tests/` | Boundary isolation, adapter behavior, port-hosting behavior, no internal leakage |

### 13.3 Local Test Targets

Local tests may cover:

|           Record ID | Test Target                   | Description                                                 |
| ------------------: | ----------------------------- | ----------------------------------------------------------- |
| ASDT-FS-000-LTT-001 | Local behavior                | The expected behavior of the owning folder                  |
| ASDT-FS-000-LTT-002 | Obligations                   | Required guarantees                                         |
| ASDT-FS-000-LTT-003 | Dependency isolation          | Forbidden dependency checks                                 |
| ASDT-FS-000-LTT-004 | State transitions             | Valid and invalid transitions                               |
| ASDT-FS-000-LTT-005 | Port hosting                  | Correct injection and consumption of hosted ports           |
| ASDT-FS-000-LTT-006 | Adapter signaling             | Correct outbound adapter behavior                           |
| ASDT-FS-000-LTT-007 | Carrier invariants            | Correctness of local records, handles, reports, assignments |
| ASDT-FS-000-LTT-008 | Negative cases                | Misuse and anti-collapse cases                              |
| ASDT-FS-000-LTT-009 | Dependency-ordered behavior   | Behavior tested as soon as dependencies are stable          |
| ASDT-FS-000-LTT-010 | Round and workflow continuity | Especially relevant to `write_side/` runtime components     |

---

## 14. Allowed Local Subfolder Classes

### 14.1 General Rule

```text
Only justified local subfolders appear.
```

A component or semantic root should not blindly include every possible subfolder.

### 14.2 Allowed Subfolder Vocabulary

|          Record ID | Folder               | Meaning                                                                         | Appears When                                                               |
| -----------------: | -------------------- | ------------------------------------------------------------------------------- | -------------------------------------------------------------------------- |
| ASDT-FS-000-SF-001 | `docs/`              | Local documentation                                                             | Meaningful folder has explainable semantics                                |
| ASDT-FS-000-SF-002 | `tests/`             | Local tests                                                                     | Meaningful folder has verifiable behavior, obligations, or constraints     |
| ASDT-FS-000-SF-003 | `carriers/`          | Local carried objects, records, reports, handles, assignments, DTO-like objects | Folder owns local carried structures                                       |
| ASDT-FS-000-SF-004 | `hosted_ports/`      | Injectable ports authored elsewhere and hosted locally                          | Folder consumes a client-side or externally provided port                  |
| ASDT-FS-000-SF-005 | `outbound_adapters/` | Local adapters used to call, signal, or provide outward behavior                | Folder sends outward or realizes contract-out behavior                     |
| ASDT-FS-000-SF-006 | `state/`             | Local state model or state machine                                              | Folder owns first-class behavioral state                                   |
| ASDT-FS-000-SF-007 | `detail/`            | Private implementation internals                                                | Folder requires private mechanisms that must not be depended on externally |

### 14.3 Discouraged Generic Subfolders

|           Record ID | Folder                   | Reason                                                                                      |
| ------------------: | ------------------------ | ------------------------------------------------------------------------------------------- |
| ASDT-FS-000-DSF-001 | `contracts/`             | Contracts are principles; ports/adapters/traits are material realizations                   |
| ASDT-FS-000-DSF-002 | `utils/`                 | Encourages dumping-ground behavior                                                          |
| ASDT-FS-000-DSF-003 | `helpers/`               | Obscures ownership and meaning                                                              |
| ASDT-FS-000-DSF-004 | `common/`                | Weakens domain boundaries                                                                   |
| ASDT-FS-000-DSF-005 | `misc/`                  | No semantic ownership                                                                       |
| ASDT-FS-000-DSF-006 | `capabilities/`          | Capabilities become behavior/methods, not default folders                                   |
| ASDT-FS-000-DSF-007 | `actors/`                | Actor folders should be named by actor/component, not grouped generically                   |
| ASDT-FS-000-DSF-008 | `data/`                  | Too generic; use semantic roots or local carriers                                           |
| ASDT-FS-000-DSF-009 | `states/` at domain root | State belongs to owning component unless a domain-level state model is explicitly justified |

---

## 15. State Doctrine

### 15.1 Rule

```text
State is a valid first-class internal concept when it affects behavior and transitions.
```

### 15.2 Status vs State vs State Machine

|          Record ID | Term          | Meaning                                                                    |
| -----------------: | ------------- | -------------------------------------------------------------------------- |
| ASDT-FS-000-ST-001 | Status        | A descriptive value such as ready, full, occupied, or available            |
| ASDT-FS-000-ST-002 | State         | A behavioral condition that affects what the component may do next         |
| ASDT-FS-000-ST-003 | State Machine | A mechanism governing valid transitions between states                     |
| ASDT-FS-000-ST-004 | Snapshot      | A captured read-only state observation at a point in time                  |
| ASDT-FS-000-ST-005 | View          | Optional non-owning read-only projection; not a default glossary-root term |

### 15.3 Placement Rule

```text
state/ belongs inside the folder that owns the behavior.
```

Examples:

```text
write_side/slot/state/
write_side/slots_container/state/
write_side/round_manager/state/
write_side/dispatcher/state/
```

Do not create a root-level `states/` folder unless a genuine shared domain state model is explicitly justified.

---

## 16. Communications Doctrine

### 16.1 Rule

```text
Communications, bridges, ports, and adapters appear after internal runtime structures are established.
```

### 16.2 Reason

A communication boundary must expose stable abstractions, not internal mechanics.

For example, the bridge between `log_level_api` and `write_side` must not expose:

1. slot internals,
2. slots container internals,
3. bundle scaling internals,
4. waiting list internals,
5. moderator internals,
6. round manager internals.

It should expose only approved abstractions such as placement references, hosted ports, outbound adapters, or carrier handles.

### 16.3 Write-Side Communications

The current `write_side/communications/` structure is:

```text
write_side/
└── communications/
    ├── log_level_api_feeding/
    └── registry_delivery/
```

|           Record ID | Communication Area       | Meaning                                                                          |
| ------------------: | ------------------------ | -------------------------------------------------------------------------------- |
| ASDT-FS-000-COM-001 | `log_level_api_feeding/` | Boundary with `log_level_api` for feeding and placement interaction              |
| ASDT-FS-000-COM-002 | `registry_delivery/`     | Boundary with external Log Level / Message Records Registry for delivery/handoff |

### 16.4 Communication Rule

```text
Communication folders must expose ports, adapters, carriers, and local tests/docs.
They must not expose internal runtime ownership structures.
```

---

## 17. Dependency Ordering Doctrine

### 17.1 Rule

```text
Dependency first, then what depends on it.
```

### 17.2 Root Domain Dependency Direction

At the high level:

```text
ecosystem_governance
  → log_level_api
  → write_side
  → external registry/delivery destination
```

This does not mean every folder directly depends on the next.
It means that policy supply, preparation, write-side coordination, and downstream handoff must remain ordered and bounded.

### 17.3 Domain Internal Dependency Examples

#### 17.3.1 `log_level_api/`

```text
policy_assignment
→ content
→ validator
→ timestamp_stabilizer
→ metadata_injector
→ envelope
→ envelope_assembler
→ write_side_bridge
→ api_facade
```

#### 17.3.2 `write_side/`

```text
policy_assignment
→ slot
→ slots_container
→ waiting_list
→ slots_container_moderator
→ slots_container_bundle_agent
→ round_manager
→ reference_precalculator
→ dispatcher
→ communications
```

### 17.4 Runtime vs Type Dependency

Filesystem order may follow type and ownership dependency.

Runtime orchestration may begin elsewhere when provisioning requires it.

For example:

|           Record ID | Concern                   | Clarification                                                                                               |
| ------------------: | ------------------------- | ----------------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-DEP-001 | Bundle Agent provisioning | Runtime provisioning may begin with the bundle agent                                                        |
| ASDT-FS-000-DEP-002 | Filesystem order          | The bundle agent appears after slots container and moderator concepts because it depends on their existence |
| ASDT-FS-000-DEP-003 | Round Manager             | Manages waiting-list membership, not container creation                                                     |
| ASDT-FS-000-DEP-004 | Reference Pre-Calculator  | Depends on round and waiting-list information before communications expose placement references             |

---

## 18. Anti-Collapse Doctrine

### 18.1 Rule

```text
Folders must prevent semantic collapse.
```

### 18.2 Anti-Collapse Table

|          Record ID | Collapse Risk                                           | Prevention                                                                                                |
| -----------------: | ------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| ASDT-FS-000-AC-001 | Documentation folders treated as implementation domains | Root implementation domains are only `ecosystem_governance`, `log_level_api`, and `write_side`            |
| ASDT-FS-000-AC-002 | Contracts treated as generic folders                    | Ports/adapters/traits realize contracts physically                                                        |
| ASDT-FS-000-AC-003 | Administrative perspective treated as folder            | Administrative meaning is domain-level interpretation of `ecosystem_governance`                           |
| ASDT-FS-000-AC-004 | Policy bundle redefined in consuming domain             | Policy bundle DTOs are defined by `ecosystem_governance`; consuming domains host ports and assign locally |
| ASDT-FS-000-AC-005 | Assembler directly owns validator policy                | Validator may be policy-bound; assembler composes validator                                               |
| ASDT-FS-000-AC-006 | Write-side bridge exposes internals                     | Bridge exposes placement references, not internal slots/container mechanics                               |
| ASDT-FS-000-AC-007 | Bundle Agent confused with Round Manager                | Bundle Agent manages existence/scaling; Round Manager manages waiting-list membership                     |
| ASDT-FS-000-AC-008 | Moderator confused with Bundle Agent                    | Moderator prepares one assigned container; Bundle Agent manages bundle topology                           |
| ASDT-FS-000-AC-009 | Dispatcher confused with Registry                       | Dispatcher performs final assembler-side handoff; registry remains external                               |
| ASDT-FS-000-AC-010 | State treated as passive status                         | State folders appear only for first-class behavioral state models                                         |

---

## 19. Current Folder-Level Baseline

### 19.1 Root Implementation Baseline

```text
include/
└── assembler/
    ├── ecosystem_governance/
    ├── log_level_api/
    └── write_side/
```

### 19.2 `ecosystem_governance/` Baseline

```text
ecosystem_governance/
├── docs/
├── tests/
├── policy_type_system/
├── policy_registries/
├── provider_adapters/
└── receiver_ports/
    ├── docs/
    ├── tests/
    ├── log_level_api/
    └── write_side/
```

### 19.3 `log_level_api/` Baseline

```text
log_level_api/
├── docs/
├── tests/
├── policy_assignment/
├── content/
├── validator/
├── timestamp_stabilizer/
├── metadata_injector/
├── envelope/
├── envelope_assembler/
├── write_side_bridge/
└── api_facade/
```

### 19.4 `write_side/` Baseline

```text
write_side/
├── docs/
├── tests/
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
    ├── docs/
    ├── tests/
    ├── log_level_api_feeding/
    └── registry_delivery/
```

---

## 20. Later Documents in This Pack

### 20.1 Planned Sequence

|            Record ID | Document                                               | Purpose                                                       |
| -------------------: | ------------------------------------------------------ | ------------------------------------------------------------- |
| ASDT-FS-000-NEXT-001 | `ASDT-FS-001_Root_DDD_Domain_Folders.md`               | Defines root implementation domain folders                    |
| ASDT-FS-000-NEXT-002 | `ASDT-FS-002_Domain_Internal_Folder_Taxonomy.md`       | Defines first-layer internal roots inside each domain         |
| ASDT-FS-000-NEXT-003 | `ASDT-FS-003_Folder_Dependency_And_Ownership_Rules.md` | Defines ownership, dependency order, and forbidden placement  |
| ASDT-FS-000-NEXT-004 | `ASDT-FS-004_Component_Subfolder_Rules.md`             | Defines docs/tests/carriers/ports/adapters/state/detail rules |
| ASDT-FS-000-NEXT-005 | `ASDT-FS-005_Current_Folder_Structure_Draft_V1.md`     | Presents the current folder-only draft                        |
| ASDT-FS-000-NEXT-006 | `ASDT-FS-006_File_Inventory_Derivation_Later.md`       | Defines how final files will later be derived from folders    |

---

## 21. Summary

This document establishes the folder-first doctrine for the Assembler System Digital Twin Filesystem Structure Pack.

The governing conclusions are:

1. the filesystem is a logical digital twin of the system model,
2. root implementation folders follow DDD domains,
3. documentation and governance support folders are not implementation domains,
4. folder taxonomy must be stabilized before file inventory,
5. contracts are governing principles, not default folders,
6. ports and adapters are contract-bearing realizations,
7. local `docs/` and `tests/` may exist at every meaningful folder level,
8. `state/` is valid when state is a first-class behavioral concept,
9. communications are placed after internal runtime structures are established,
10. dependency order governs folder order where practical,
11. anti-collapse rules govern naming and placement,
12. final C++ file inventory is deferred.

The next document shall define the root DDD implementation domain folders in detail.

```
```
