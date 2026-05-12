
# ASDT-FS-003 — Folder Dependency and Ownership Rules

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-003-DOC-001 | Document Title | Folder Dependency and Ownership Rules |
| ASDT-FS-003-DOC-002 | File Name | `ASDT-FS-003_Folder_Dependency_And_Ownership_Rules.md` |
| ASDT-FS-003-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-003-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-003-DOC-005 | Project | Assembler System |
| ASDT-FS-003-DOC-006 | Primary Language | English |
| ASDT-FS-003-DOC-007 | Scope Level | Folder dependency rules, folder ownership rules, dependency visibility, ownership boundaries, forbidden dependencies |
| ASDT-FS-003-DOC-008 | Implementation Language Direction | C++17, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-003-DOC-009 | Status | Pre-Implementation Folder Doctrine |
| ASDT-FS-003-DOC-010 | File Inventory Status | Deferred |
| ASDT-FS-003-DOC-011 | Depends On | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md`, `ASDT-FS-001_Root_DDD_Domain_Folders.md` |
| ASDT-FS-003-DOC-012 | Primary Rule | A folder owns the narrowest semantic scope that justifies its existence |
| ASDT-FS-003-DOC-013 | Dependency Rule | Dependency first, then what depends on it |
| ASDT-FS-003-DOC-014 | Ownership Rule | Ownership must not leak across domains, components, actors, ports, adapters, carriers, or runtime internals |
| ASDT-FS-003-DOC-015 | Governing Doctrine | The filesystem is a logical digital twin of the system model, not a passive storage layout |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the dependency and ownership rules that govern the Assembler System Digital Twin Filesystem.

It explains how folders may depend on each other, what each folder is allowed to own, what each folder must not own, how cross-domain references must be controlled, and how folder-level ownership prevents semantic collapse.

This document exists because the filesystem is intended to mirror the logical structure, ownership boundaries, dependency order, and behavioral architecture of the system, not merely store files. This principle was established in `ASDT-FS-000`, where the filesystem is defined as a logical digital twin and folder taxonomy must be stabilized before file inventory. :contentReference[oaicite:0]{index=0}

### 2.2 Position in the ASDT-FS Pack

`ASDT-FS-001` established the accepted root DDD implementation domains:

```text
ecosystem_governance/
log_level_api/
write_side/
````

It also established that these are semantic implementation domains, not documentation folders, technical buckets, or deployment packages by default. 

This document now defines the rules that govern dependency and ownership between those folders and their internal descendants.

### 2.3 What This Document Does

This document defines:

1. folder ownership rules,
2. folder dependency rules,
3. dependency direction rules,
4. allowed dependency forms,
5. forbidden dependency forms,
6. local ownership boundaries,
7. shared semantic root rules,
8. actor/component ownership rules,
9. carrier ownership rules,
10. port and adapter ownership rules,
11. state ownership rules,
12. communication boundary ownership rules,
13. docs/tests ownership rules,
14. root-domain dependency rules,
15. cross-domain dependency rules,
16. dependency validation questions,
17. ownership validation questions.

### 2.4 What This Document Does Not Do

This document does not define:

1. final `.hpp` files,
2. final C++ class definitions,
3. final include statements,
4. final namespace names,
5. final CMake targets,
6. final test files,
7. final documentation file inventory,
8. final runtime algorithms,
9. final bridge protocols,
10. final downstream registry schema,
11. final package implementation.

File inventory remains deferred.

---

## 3. Governing Principles

### 3.1 Folder-First Principle

```text
Folders are stabilized before files.
```

A dependency rule applies first to folders and semantic ownership.

Only after folder dependency and ownership rules are stable may file-level dependencies be derived.

### 3.2 Narrowest Ownership Principle

```text
A folder owns the narrowest semantic scope that justifies its existence.
```

A folder must not own concepts merely because it is convenient.

A folder must own only the concepts, docs, tests, carriers, state models, ports, adapters, and implementation details that belong to its semantic scope.

### 3.3 Dependency-First Ordering Principle

```text
Dependency first, then what depends on it.
```

Folder order should expose architectural dependency where practical.

A folder that provides a semantic foundation should appear before folders that depend on it.

### 3.4 Anti-Leakage Principle

```text
A folder must not leak its private internals into other folders.
```

Other folders may depend on approved public surfaces, carrier handles, ports, adapters, views, references, or documented abstractions.

They must not depend on private `detail/`, local state-machine internals, queue internals, slot internals, or component-local implementation mechanics.

### 3.5 No Generic Ownership Principle

```text
Generic folders are not ownership substitutes.
```

Folders such as:

```text
utils/
helpers/
common/
misc/
data/
contracts/
actors/
states/
```

are discouraged unless a strong semantic ownership case exists.

The preferred structure is actor/component-centered, with shared roots allowed only when genuinely shared.

---

## 4. Folder Ownership Model

### 4.1 Definition

Folder ownership means that a folder is the authoritative semantic location for a concept, component, actor, carrier, state model, port, adapter, documentation scope, or testing scope.

Ownership determines:

1. where a concept is defined,
2. where its local documentation belongs,
3. where its local tests belong,
4. which folder may evolve it,
5. which other folders may depend on it,
6. which dependencies are forbidden,
7. whether the concept can be shared,
8. whether the concept is internal or exposed.

### 4.2 Ownership Record Model

Every meaningful folder may be described by the following ownership model.

|                 Record ID | Ownership Field        | Meaning                                                                                                                 |
| ------------------------: | ---------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-003-OWN-MODEL-001 | Folder Path            | The canonical filesystem path                                                                                           |
| ASDT-FS-003-OWN-MODEL-002 | Folder Class           | Domain, component, actor, carrier root, state root, port root, adapter root, communications root, docs root, tests root |
| ASDT-FS-003-OWN-MODEL-003 | Owned Meaning          | The semantic meaning owned by the folder                                                                                |
| ASDT-FS-003-OWN-MODEL-004 | Ownership Scope        | Domain-level, component-level, actor-level, local, shared, cross-boundary                                               |
| ASDT-FS-003-OWN-MODEL-005 | Public Surface         | What other folders may use                                                                                              |
| ASDT-FS-003-OWN-MODEL-006 | Private Surface        | What other folders must not use                                                                                         |
| ASDT-FS-003-OWN-MODEL-007 | Allowed Dependencies   | What the folder may depend on                                                                                           |
| ASDT-FS-003-OWN-MODEL-008 | Forbidden Dependencies | What the folder must not depend on                                                                                      |
| ASDT-FS-003-OWN-MODEL-009 | Local Docs Scope       | What local `docs/` must explain                                                                                         |
| ASDT-FS-003-OWN-MODEL-010 | Local Tests Scope      | What local `tests/` must verify                                                                                         |

---

## 5. Folder Classes and Ownership Rules

### 5.1 Folder Class Table

|          Record ID | Folder Class            | Ownership Rule                                                                |
| -----------------: | ----------------------- | ----------------------------------------------------------------------------- |
| ASDT-FS-003-FC-001 | Root Domain Folder      | Owns a bounded semantic implementation domain                                 |
| ASDT-FS-003-FC-002 | Domain Internal Root    | Owns a first-layer semantic concern inside a domain                           |
| ASDT-FS-003-FC-003 | Actor Folder            | Owns a responsibility-carrying actor or actor-like component                  |
| ASDT-FS-003-FC-004 | Component Folder        | Owns a bounded component abstraction and its local internals                  |
| ASDT-FS-003-FC-005 | Carrier Folder          | Owns carrier structures used by a local component or shared context           |
| ASDT-FS-003-FC-006 | State Folder            | Owns behavioral state or state-machine semantics for the containing owner     |
| ASDT-FS-003-FC-007 | Hosted Port Folder      | Owns locally hosted injectable port surfaces consumed by the containing owner |
| ASDT-FS-003-FC-008 | Outbound Adapter Folder | Owns local outgoing adapter surfaces emitted by the containing owner          |
| ASDT-FS-003-FC-009 | Communications Folder   | Owns boundary communication abstractions between domains or external systems  |
| ASDT-FS-003-FC-010 | Detail Folder           | Owns private implementation internals                                         |
| ASDT-FS-003-FC-011 | Docs Folder             | Owns documentation for its immediate parent scope                             |
| ASDT-FS-003-FC-012 | Tests Folder            | Owns tests for its immediate parent scope                                     |

### 5.2 Folder Ownership Rule

```text
A folder may own only what its folder class and semantic scope justify.
```

For example:

1. `write_side/slot/` may own slot semantics.
2. `write_side/round_manager/` may own round-management semantics.
3. `write_side/round_manager/state/` may own round-manager state.
4. `write_side/communications/log_level_api_feeding/` may own boundary-facing communication with `log_level_api/`.
5. `log_level_api/envelope_assembler/` may own envelope-assembler composition logic.
6. `log_level_api/envelope/` may own envelope carrier structure.
7. `ecosystem_governance/receiver_ports/write_side/` may own write-side policy receiver-port definitions.

---

## 6. Root Domain Ownership Rules

### 6.1 Accepted Root Domains

The accepted root DDD implementation domains are:

```text
ecosystem_governance/
log_level_api/
write_side/
```

### 6.2 Root Ownership Table

|            Record ID | Root Domain             | Owns                                                                                                                                                                                    | Does Not Own                                                                                                                 |
| -------------------: | ----------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-003-ROOT-001 | `ecosystem_governance/` | Policy type system, policy registries, provider adapters, consumer-specific receiver-port definitions                                                                                   | Local API policy assignment, write-side runtime internals, dispatcher behavior, downstream registry lifecycle                |
| ASDT-FS-003-ROOT-002 | `log_level_api/`        | Content preparation, local API policy assignment, validation, timestamp stabilization, metadata injection, envelope structure, envelope assembly, API façade, write-side bridge hosting | Ecosystem policy registry internals, write-side slot/container internals, dispatcher finality, downstream registry internals |
| ASDT-FS-003-ROOT-003 | `write_side/`           | Local write-side policy assignment, slots, slots containers, waiting lists, moderators, bundle agent, round managers, reference pre-calculation, dispatcher, communications             | Raw content creation, envelope assembly internals, external policy registry internals, downstream registry lifecycle         |

### 6.3 Root Dependency Direction

```text
ecosystem_governance/
→ log_level_api/
→ write_side/
→ downstream external destination
```

This direction is architectural.

It does not mean uncontrolled include dependency.

It means that each later domain depends on abstractions, carriers, or ports that are semantically prepared by earlier domains.

### 6.4 Root Domain Ownership Constraint

```text
No root domain may absorb the core ownership of another root domain.
```

Examples:

1. `log_level_api/` must not own `write_side/slot/`.
2. `write_side/` must not own `log_level_api/envelope_assembler/`.
3. `ecosystem_governance/` must not own `log_level_api/policy_assignment/`.
4. `write_side/` must not own downstream registry internals.
5. `log_level_api/` must not own ecosystem policy registries.

---

## 7. Domain Internal Root Ownership Rules

### 7.1 Domain Internal Root Rule

```text
A domain internal root owns a first-layer semantic concern inside its parent domain.
```

It must not be a generic category unless that category is genuinely the semantic concern.

### 7.2 `ecosystem_governance/` Internal Ownership Preview

|              Record ID | Folder                | Owned Meaning                                                            | Ownership Boundary                                 |
| ---------------------: | --------------------- | ------------------------------------------------------------------------ | -------------------------------------------------- |
| ASDT-FS-003-EG-OWN-001 | `policy_type_system/` | Policy type vocabulary, policy clauses, mechanisms, objects, descriptors | Does not own local assignment inside consumers     |
| ASDT-FS-003-EG-OWN-002 | `policy_registries/`  | Governance-side registry abstractions and registry entries               | Does not own downstream Log Level Records Registry |
| ASDT-FS-003-EG-OWN-003 | `provider_adapters/`  | Provider-side adapters for policy supply                                 | Does not own receiver-side hosting behavior        |
| ASDT-FS-003-EG-OWN-004 | `receiver_ports/`     | Consumer-specific receiver-port definitions and policy bundle DTO shapes | Does not own consuming-domain assignment behavior  |

### 7.3 `log_level_api/` Internal Ownership Preview

|                Record ID | Folder                  | Owned Meaning                                                       | Ownership Boundary                                          |
| -----------------------: | ----------------------- | ------------------------------------------------------------------- | ----------------------------------------------------------- |
| ASDT-FS-003-LAPI-OWN-001 | `policy_assignment/`    | Local API-domain policy assignment                                  | Does not own ecosystem policy source or registry            |
| ASDT-FS-003-LAPI-OWN-002 | `content/`              | Governed content representation                                     | Does not own raw external content lifecycle                 |
| ASDT-FS-003-LAPI-OWN-003 | `validator/`            | Validation behavior and optional policy-bound validation            | Does not own envelope assembly as a whole                   |
| ASDT-FS-003-LAPI-OWN-004 | `timestamp_stabilizer/` | Pre-dispatch timestamp stabilization                                | Does not own downstream query-time timestamp interpretation |
| ASDT-FS-003-LAPI-OWN-005 | `metadata_injector/`    | Metadata preparation and directive/schema-guided metadata injection | Does not become a policy host by default                    |
| ASDT-FS-003-LAPI-OWN-006 | `envelope/`             | Log Level Envelope carrier structure                                | Does not perform assembly behavior                          |
| ASDT-FS-003-LAPI-OWN-007 | `envelope_assembler/`   | Envelope assembly and composition of preparation participants       | Does not own write-side placement internals                 |
| ASDT-FS-003-LAPI-OWN-008 | `write_side_bridge/`    | Approved API-to-write-side bridge abstractions                      | Does not expose write-side internals                        |
| ASDT-FS-003-LAPI-OWN-009 | `api_facade/`           | Public API façade for preparation path                              | Does not become full application integration layer          |

### 7.4 `write_side/` Internal Ownership Preview

|              Record ID | Folder                          | Owned Meaning                                                                        | Ownership Boundary                               |
| ---------------------: | ------------------------------- | ------------------------------------------------------------------------------------ | ------------------------------------------------ |
| ASDT-FS-003-WS-OWN-001 | `policy_assignment/`            | Local write-side policy assignment                                                   | Does not own ecosystem policy source             |
| ASDT-FS-003-WS-OWN-002 | `slot/`                         | Slot semantics and local slot state                                                  | Does not own envelope lifecycle                  |
| ASDT-FS-003-WS-OWN-003 | `slots_container/`              | Slots container structure and container-local semantics                              | Does not become message broker                   |
| ASDT-FS-003-WS-OWN-004 | `waiting_list/`                 | Identifier-based waiting-list indexes                                                | Does not store full envelopes as a generic queue |
| ASDT-FS-003-WS-OWN-005 | `slots_container_moderator/`    | Preparation and reinitialization of one assigned container                           | Does not own bundle topology                     |
| ASDT-FS-003-WS-OWN-006 | `slots_container_bundle_agent/` | Container existence, horizontal scaling, vertical slot scaling, moderator assignment | Does not manage rounds                           |
| ASDT-FS-003-WS-OWN-007 | `round_manager/`                | Writing/feeding and delivery/dispatch round membership and movement                  | Does not create containers                       |
| ASDT-FS-003-WS-OWN-008 | `reference_precalculator/`      | Pre-computed placement references for stable feeding workflow                        | Does not expose internals directly to API        |
| ASDT-FS-003-WS-OWN-009 | `dispatcher/`                   | Final assembler-side outbound handoff actor                                          | Does not become downstream registry              |
| ASDT-FS-003-WS-OWN-010 | `communications/`               | Approved cross-boundary ports, adapters, carriers, and bridge abstractions           | Does not leak write-side runtime internals       |

---

## 8. Component and Actor Ownership Rules

### 8.1 Actor/Component-Centered Rule

```text
Actor and component folders own their local object model.
```

Local data, carriers, rules, state, ports, adapters, docs, tests, and details should live under the actor/component folder when their meaning is local to that actor or component.

### 8.2 Shared Root Exception

A concept may live at the domain root only when it is genuinely shared by multiple actors or components inside that domain.

For example:

```text
log_level_api/content/
log_level_api/envelope/
```

may be shared semantic roots because multiple preparation components may depend on content and envelope structures.

### 8.3 Local Ownership Pattern

A component folder may follow this logical pattern:

```text
component_or_actor/
├── docs/
├── tests/
├── carriers/
├── state/
├── hosted_ports/
├── outbound_adapters/
└── detail/
```

Only justified subfolders should appear.

A folder must not include all possible subfolders by default.

### 8.4 Component Ownership Table

|            Record ID | Component Folder Owns      | May Contain                                                | Must Not Contain                   |
| -------------------: | -------------------------- | ---------------------------------------------------------- | ---------------------------------- |
| ASDT-FS-003-COMP-001 | Public abstraction surface | Local docs/tests, carriers, state, ports, adapters, detail | Unrelated shared domain vocabulary |
| ASDT-FS-003-COMP-002 | Local behavioral rules     | Local tests and state if needed                            | Other actor’s private state        |
| ASDT-FS-003-COMP-003 | Local composition logic    | Local carrier handles and adapters                         | Downstream lifecycle ownership     |
| ASDT-FS-003-COMP-004 | Local obligations          | Local docs and tests                                       | Generic system-wide governance     |

---

## 9. Carrier Ownership Rules

### 9.1 Carrier Rule

```text
A carrier belongs to the narrowest folder that owns the meaning of what is carried.
```

### 9.2 Carrier Placement

|           Record ID | Carrier Type                         | Preferred Placement                                   |
| ------------------: | ------------------------------------ | ----------------------------------------------------- |
| ASDT-FS-003-CAR-001 | Shared envelope carrier              | `log_level_api/envelope/`                             |
| ASDT-FS-003-CAR-002 | Assembly input/result carrier        | `log_level_api/envelope_assembler/carriers/` if local |
| ASDT-FS-003-CAR-003 | API policy assignment carrier        | `log_level_api/policy_assignment/carriers/`           |
| ASDT-FS-003-CAR-004 | Write-side policy assignment carrier | `write_side/policy_assignment/carriers/`              |
| ASDT-FS-003-CAR-005 | Slot-local carrier                   | `write_side/slot/carriers/` if local                  |
| ASDT-FS-003-CAR-006 | Container-local carrier              | `write_side/slots_container/carriers/` if local       |
| ASDT-FS-003-CAR-007 | Round-manager carrier                | `write_side/round_manager/carriers/`                  |
| ASDT-FS-003-CAR-008 | Dispatcher report carrier            | `write_side/dispatcher/carriers/`                     |
| ASDT-FS-003-CAR-009 | Bridge carrier                       | Relevant `communications/` or bridge folder           |
| ASDT-FS-003-CAR-010 | Policy bundle DTO                    | `ecosystem_governance/receiver_ports/<consumer>/`     |

### 9.3 Carrier Anti-Collapse Rule

```text
A carrier is not the actor that produces, validates, assigns, dispatches, or stores it.
```

Examples:

1. `Log Level Envelope` is not `Envelope Assembler`.
2. `Policy Object` is not `PolicyAssigner`.
3. `Handoff Evidence` is not `Dispatcher`.
4. `Slot Occupancy` is not envelope lifecycle ownership.
5. `Dispatcher Feedback Report` is not downstream registry state.

---

## 10. Port and Adapter Ownership Rules

### 10.1 Contract Realization Rule

```text
Ports and adapters are contract-bearing components.
```

A generic `contracts/` folder is discouraged unless a contract is genuinely shared across multiple components and cannot be placed more narrowly.

### 10.2 Port Ownership Rule

```text
A port is owned by the folder that defines or hosts the interaction surface.
```

There are two common cases:

1. provider domain defines receiver-port shapes for consumers,
2. consuming domain hosts the injectable port locally.

### 10.3 Adapter Ownership Rule

```text
An adapter is owned by the folder that emits, provides, or translates an external-facing interaction.
```

### 10.4 Port and Adapter Placement Table

|          Record ID | Interaction                                   | Preferred Ownership                                  |
| -----------------: | --------------------------------------------- | ---------------------------------------------------- |
| ASDT-FS-003-PA-001 | Policy provider adapter                       | `ecosystem_governance/provider_adapters/`            |
| ASDT-FS-003-PA-002 | Log Level API policy receiver-port definition | `ecosystem_governance/receiver_ports/log_level_api/` |
| ASDT-FS-003-PA-003 | Write-side policy receiver-port definition    | `ecosystem_governance/receiver_ports/write_side/`    |
| ASDT-FS-003-PA-004 | Log Level API hosted policy port              | `log_level_api/policy_assignment/hosted_ports/`      |
| ASDT-FS-003-PA-005 | Write-side hosted policy port                 | `write_side/policy_assignment/hosted_ports/`         |
| ASDT-FS-003-PA-006 | API-to-write-side placement host              | `log_level_api/write_side_bridge/hosted_ports/`      |
| ASDT-FS-003-PA-007 | API-to-write-side outbound signal             | `log_level_api/write_side_bridge/outbound_adapters/` |
| ASDT-FS-003-PA-008 | Write-side feeding boundary                   | `write_side/communications/log_level_api_feeding/`   |
| ASDT-FS-003-PA-009 | Registry delivery boundary                    | `write_side/communications/registry_delivery/`       |

### 10.5 Port/Adapter Anti-Collapse Rule

```text
A port or adapter may carry a contract, but it is not the contract as an abstract architectural law.
```

The contract is the governing law.

The port or adapter is the implementation-facing realization surface.

---

## 11. State Ownership Rules

### 11.1 State Placement Rule

```text
state/ belongs inside the folder that owns the behavior.
```

A domain-level `states/` folder is discouraged unless a true shared domain state model is formally justified.

### 11.2 State Ownership Table

|          Record ID | State Owner        | Preferred State Placement                                | Reason                                                            |
| -----------------: | ------------------ | -------------------------------------------------------- | ----------------------------------------------------------------- |
| ASDT-FS-003-ST-001 | Slot               | `write_side/slot/state/`                                 | Slot lifecycle and occupancy state belong to slot semantics       |
| ASDT-FS-003-ST-002 | Slots Container    | `write_side/slots_container/state/`                      | Container readiness and fullness belong to container semantics    |
| ASDT-FS-003-ST-003 | Moderator          | `write_side/slots_container_moderator/state/`            | Moderator preparation/reinitialization state belongs to moderator |
| ASDT-FS-003-ST-004 | Bundle Agent       | `write_side/slots_container_bundle_agent/state/`         | Scaling/topology state belongs to bundle agent                    |
| ASDT-FS-003-ST-005 | Round Manager      | `write_side/round_manager/state/`                        | Round membership and transition state belong to round manager     |
| ASDT-FS-003-ST-006 | Dispatcher         | `write_side/dispatcher/state/`                           | Dispatch eligibility and handoff state belong to dispatcher       |
| ASDT-FS-003-ST-007 | Validator          | `log_level_api/validator/state/` only if needed          | Validation state belongs locally if behavior requires it          |
| ASDT-FS-003-ST-008 | Envelope Assembler | `log_level_api/envelope_assembler/state/` only if needed | Assembly state belongs locally if behavior requires it            |

### 11.3 State Anti-Collapse Rule

```text
State is not merely status text.
State owns behavioral consequences and transition constraints.
```

A status flag may be a carrier field.

A state model affects what a component may validly do next.

A state machine governs transitions.

---

## 12. Detail Folder Ownership Rules

### 12.1 Detail Rule

```text
detail/ is private to its nearest owning folder.
```

### 12.2 Dependency Rule

No folder outside the nearest owner may depend on `detail/`.

For example:

```text
log_level_api/validator/detail/
```

may be used by:

```text
log_level_api/validator/
```

but must not be used by:

```text
log_level_api/envelope_assembler/
write_side/
ecosystem_governance/
```

unless a later explicit exception is approved.

### 12.3 Detail Anti-Leakage Rule

```text
If another folder needs something from detail/, the concept is probably misplaced.
```

The correct solution may be:

1. promote a stable public surface,
2. create a local carrier,
3. define a hosted port,
4. define an outbound adapter,
5. create a shared semantic root,
6. move the concept to the actual owner.

---

## 13. Documentation Ownership Rules

### 13.1 Docs Rule

```text
docs/ documents its immediate parent scope.
```

### 13.2 Docs Ownership Table

|            Record ID | Docs Folder                  | Owns Documentation For                                                           |
| -------------------: | ---------------------------- | -------------------------------------------------------------------------------- |
| ASDT-FS-003-DOCS-001 | Repository-level `docs/`     | Whole project and cross-domain architecture                                      |
| ASDT-FS-003-DOCS-002 | `ecosystem_governance/docs/` | Ecosystem governance domain                                                      |
| ASDT-FS-003-DOCS-003 | `log_level_api/docs/`        | Log Level API domain                                                             |
| ASDT-FS-003-DOCS-004 | `write_side/docs/`           | Write Side domain                                                                |
| ASDT-FS-003-DOCS-005 | Component-level `docs/`      | Immediate component, actor, carrier root, port root, adapter root, or state root |
| ASDT-FS-003-DOCS-006 | `communications/*/docs/`     | Immediate communication boundary                                                 |

### 13.3 Docs Anti-Collapse Rule

```text
Documentation location does not create implementation ownership.
```

A documentation folder may explain a concept.

It does not necessarily own the implementation concept.

Implementation ownership follows semantic folder rules.

---

## 14. Testing Ownership Rules

### 14.1 Tests Rule

```text
tests/ verifies its immediate parent scope.
```

### 14.2 Tests Ownership Table

|             Record ID | Tests Folder                  | Owns Tests For                                                           |
| --------------------: | ----------------------------- | ------------------------------------------------------------------------ |
| ASDT-FS-003-TESTS-001 | Repository-level `tests/`     | Cross-domain, integration, conformance, and system-level behavior        |
| ASDT-FS-003-TESTS-002 | Domain-level `tests/`         | Domain-level dependency and ownership constraints                        |
| ASDT-FS-003-TESTS-003 | Component-level `tests/`      | Component obligations, local behavior, local state, local ports/adapters |
| ASDT-FS-003-TESTS-004 | State-level `tests/`          | State transitions, invalid transitions, state-machine invariants         |
| ASDT-FS-003-TESTS-005 | Communications-level `tests/` | Boundary isolation, adapter behavior, port behavior, leakage prevention  |

### 14.3 Tests Anti-Collapse Rule

```text
A local test verifies local behavior; it does not grant ownership over foreign internals.
```

A test may simulate or mock another domain’s public surface.

It must not depend on private internals from another folder.

---

## 15. Cross-Domain Dependency Rules

### 15.1 Cross-Domain Public Surface Rule

```text
Cross-domain dependency must use approved public surfaces.
```

Allowed public surfaces may include:

1. stable carrier types,
2. receiver-port definitions,
3. hosted ports,
4. outbound adapters,
5. bridge carriers,
6. documented views,
7. reference handles,
8. policy bundle DTOs,
9. façade surfaces,
10. communication boundary surfaces.

### 15.2 Cross-Domain Forbidden Surface Rule

Cross-domain dependency must not use:

1. `detail/`,
2. local state internals,
3. local test helpers,
4. local docs as implementation authority,
5. private carrier fields,
6. private queue internals,
7. private slot internals,
8. moderator internals,
9. bundle scaling internals,
10. dispatcher internals beyond approved handoff surfaces.

### 15.3 Cross-Domain Matrix

|          Record ID | From Folder                                        | May Depend On                                                             | Must Not Depend On                  |
| -----------------: | -------------------------------------------------- | ------------------------------------------------------------------------- | ----------------------------------- |
| ASDT-FS-003-XD-001 | `log_level_api/`                                   | Governance-provided policy bundle DTOs and hosted policy ports            | Ecosystem registry internals        |
| ASDT-FS-003-XD-002 | `write_side/`                                      | Governance-provided write-side policy bundle DTOs and hosted policy ports | Ecosystem registry internals        |
| ASDT-FS-003-XD-003 | `log_level_api/write_side_bridge/`                 | Approved placement/reference abstractions                                 | Write-side slot/container internals |
| ASDT-FS-003-XD-004 | `write_side/communications/log_level_api_feeding/` | Approved envelope-facing feeding abstractions                             | Envelope assembler internals        |
| ASDT-FS-003-XD-005 | `write_side/communications/registry_delivery/`     | Registry/delivery boundary contract surfaces                              | Downstream registry internals       |
| ASDT-FS-003-XD-006 | `write_side/dispatcher/`                           | Approved delivery surfaces and local dispatch state                       | Downstream persistence lifecycle    |
| ASDT-FS-003-XD-007 | `ecosystem_governance/receiver_ports/`             | Consumer-specific policy receiving requirements                           | Consumer implementation internals   |

---

## 16. Intra-Domain Dependency Rules

### 16.1 Intra-Domain Rule

```text
Within a domain, dependency should follow local semantic order.
```

A later component may depend on earlier foundational concepts.

An earlier component should not depend on later orchestration or runtime consumers unless a formally approved inversion abstraction exists.

### 16.2 `log_level_api/` Dependency Order

The preferred dependency order is:

```text
policy_assignment/
→ content/
→ validator/
→ timestamp_stabilizer/
→ metadata_injector/
→ envelope/
→ envelope_assembler/
→ write_side_bridge/
→ api_facade/
```

### 16.3 `log_level_api/` Dependency Rules

|                Record ID | Folder                  | May Depend On                                                  | Must Not Depend On                         |
| -----------------------: | ----------------------- | -------------------------------------------------------------- | ------------------------------------------ |
| ASDT-FS-003-LAPI-DEP-001 | `policy_assignment/`    | Governance-provided policy bundle DTOs and hosted port shapes  | Validator internals, assembler internals   |
| ASDT-FS-003-LAPI-DEP-002 | `content/`              | Minimal shared type requirements                               | Validator, envelope assembler, write-side  |
| ASDT-FS-003-LAPI-DEP-003 | `validator/`            | Content and local policy assignment if policy-bound            | Envelope assembler internals               |
| ASDT-FS-003-LAPI-DEP-004 | `timestamp_stabilizer/` | Content or timestamp input carriers as needed                  | Downstream query internals                 |
| ASDT-FS-003-LAPI-DEP-005 | `metadata_injector/`    | Content, metadata directives, local preparation carriers       | Policy hosting semantics unless formalized |
| ASDT-FS-003-LAPI-DEP-006 | `envelope/`             | Prepared content, metadata block, timestamp block as structure | Assembly behavior                          |
| ASDT-FS-003-LAPI-DEP-007 | `envelope_assembler/`   | Validator, timestamp stabilizer, metadata injector, envelope   | Write-side slot/container internals        |
| ASDT-FS-003-LAPI-DEP-008 | `write_side_bridge/`    | Approved write-side placement/reference abstractions           | Write-side private internals               |
| ASDT-FS-003-LAPI-DEP-009 | `api_facade/`           | Envelope assembler and approved bridge surface                 | Downstream registry internals              |

### 16.4 `write_side/` Dependency Order

The preferred dependency order is:

```text
policy_assignment/
→ slot/
→ slots_container/
→ waiting_list/
→ slots_container_moderator/
→ slots_container_bundle_agent/
→ round_manager/
→ reference_precalculator/
→ dispatcher/
→ communications/
```

### 16.5 `write_side/` Dependency Rules

|              Record ID | Folder                          | May Depend On                                                     | Must Not Depend On                      |
| ---------------------: | ------------------------------- | ----------------------------------------------------------------- | --------------------------------------- |
| ASDT-FS-003-WS-DEP-001 | `policy_assignment/`            | Governance-provided write-side policy bundle DTOs                 | Slot/container internals by default     |
| ASDT-FS-003-WS-DEP-002 | `slot/`                         | Local slot carriers/state                                         | Container, moderator, round manager     |
| ASDT-FS-003-WS-DEP-003 | `slots_container/`              | Slot                                                              | Bundle agent, round manager, dispatcher |
| ASDT-FS-003-WS-DEP-004 | `waiting_list/`                 | Container identifiers and index carriers                          | Full envelopes as storage payloads      |
| ASDT-FS-003-WS-DEP-005 | `slots_container_moderator/`    | Slots container and slot readiness surfaces                       | Bundle topology ownership               |
| ASDT-FS-003-WS-DEP-006 | `slots_container_bundle_agent/` | Slots containers and moderator assignment surfaces                | Round state ownership                   |
| ASDT-FS-003-WS-DEP-007 | `round_manager/`                | Waiting lists, container identifiers, moderator readiness signals | Container creation/scaling ownership    |
| ASDT-FS-003-WS-DEP-008 | `reference_precalculator/`      | Round manager and waiting-list abstractions                       | Direct API internals                    |
| ASDT-FS-003-WS-DEP-009 | `dispatcher/`                   | Delivery round readiness, dispatch eligibility, delivery carriers | Downstream registry internals           |
| ASDT-FS-003-WS-DEP-010 | `communications/`               | Approved surfaces from internal owners                            | Private internals of internal owners    |

---

## 17. Communication Boundary Ownership Rules

### 17.1 Communication Boundary Rule

```text
communications/ exposes approved boundary abstractions, not internals.
```

### 17.2 Write-Side Communication Areas

```text
write_side/
└── communications/
    ├── log_level_api_feeding/
    └── registry_delivery/
```

### 17.3 `log_level_api_feeding/` Ownership

`write_side/communications/log_level_api_feeding/` owns the write-side communication boundary for receiving prepared envelope placement interactions from `log_level_api/`.

It may own:

1. feeding port surfaces,
2. placement request carriers,
3. placement handle carriers,
4. reference-ready views,
5. adapter surfaces,
6. boundary tests,
7. boundary docs.

It must not expose:

1. raw slot internals,
2. raw slots container internals,
3. waiting-list internals,
4. bundle-agent scaling internals,
5. moderator internals,
6. round-manager private state.

### 17.4 `registry_delivery/` Ownership

`write_side/communications/registry_delivery/` owns the registry-facing delivery boundary.

It may own:

1. registry delivery port surfaces,
2. dispatch handoff adapters,
3. handoff material carriers,
4. handoff evidence carriers,
5. downstream acknowledgement carriers,
6. boundary tests,
7. boundary docs.

It must not own:

1. downstream registry implementation,
2. downstream database schema,
3. downstream persistence lifecycle,
4. downstream query behavior,
5. downstream mutation lifecycle,
6. downstream indexing lifecycle.

---

## 18. Dependency Inversion and Bridge Rules

### 18.1 Inversion Rule

```text
Dependency inversion is allowed only through explicit bridge, port, adapter, handle, or view abstractions.
```

### 18.2 Bridge Rule

A bridge exists to prevent direct coupling.

A bridge must not become a secret dependency tunnel.

### 18.3 Valid Bridge Uses

|              Record ID | Bridge Use                                                          | Validity |
| ---------------------: | ------------------------------------------------------------------- | -------- |
| ASDT-FS-003-BRIDGE-001 | API requests a placement destination from write-side abstraction    | Valid    |
| ASDT-FS-003-BRIDGE-002 | Write-side signals that a slot/container has completed loading      | Valid    |
| ASDT-FS-003-BRIDGE-003 | API receives a placement handle instead of slot internals           | Valid    |
| ASDT-FS-003-BRIDGE-004 | Write-side prepares next reference through reference pre-calculator | Valid    |
| ASDT-FS-003-BRIDGE-005 | Registry delivery passes through dispatcher-mediated boundary       | Valid    |

### 18.4 Invalid Bridge Uses

|                  Record ID | Invalid Bridge Use                               | Reason                                          |
| -------------------------: | ------------------------------------------------ | ----------------------------------------------- |
| ASDT-FS-003-BRIDGE-BAD-001 | API directly mutates slot internals              | Violates write-side ownership                   |
| ASDT-FS-003-BRIDGE-BAD-002 | API reads waiting-list private index structure   | Leaks round internals                           |
| ASDT-FS-003-BRIDGE-BAD-003 | Write-side constructs envelope internals         | Violates log-level-api ownership                |
| ASDT-FS-003-BRIDGE-BAD-004 | Dispatcher writes directly to registry internals | Violates downstream boundary                    |
| ASDT-FS-003-BRIDGE-BAD-005 | Communications folder owns all runtime logic     | Collapses boundary surface into internal system |

---

## 19. Ownership Transfer Rules

### 19.1 Ownership Transfer Principle

```text
Runtime movement is not ownership transfer unless explicitly defined.
```

An envelope moving from preparation into placement does not mean every downstream folder owns the envelope’s full semantic structure.

### 19.2 Envelope Ownership Across Flow

|            Record ID | Stage                         | Folder Ownership                                                                        | Clarification                                      |
| -------------------: | ----------------------------- | --------------------------------------------------------------------------------------- | -------------------------------------------------- |
| ASDT-FS-003-FLOW-001 | Content preparation           | `log_level_api/content/`                                                                | Owns content representation                        |
| ASDT-FS-003-FLOW-002 | Validation                    | `log_level_api/validator/`                                                              | Owns validation behavior                           |
| ASDT-FS-003-FLOW-003 | Timestamp stabilization       | `log_level_api/timestamp_stabilizer/`                                                   | Owns timestamp preparation                         |
| ASDT-FS-003-FLOW-004 | Metadata injection            | `log_level_api/metadata_injector/`                                                      | Owns metadata preparation                          |
| ASDT-FS-003-FLOW-005 | Envelope structure            | `log_level_api/envelope/`                                                               | Owns envelope carrier structure                    |
| ASDT-FS-003-FLOW-006 | Envelope assembly             | `log_level_api/envelope_assembler/`                                                     | Owns assembly behavior                             |
| ASDT-FS-003-FLOW-007 | Placement coordination        | `write_side/communications/log_level_api_feeding/` and approved write-side abstractions | Owns placement interaction, not envelope internals |
| ASDT-FS-003-FLOW-008 | Slot occupancy                | `write_side/slot/` and `write_side/slots_container/`                                    | Owns occupancy relation, not envelope lifecycle    |
| ASDT-FS-003-FLOW-009 | Dispatch                      | `write_side/dispatcher/`                                                                | Owns handoff behavior                              |
| ASDT-FS-003-FLOW-010 | Post-handoff record lifecycle | Downstream registry                                                                     | Not assembler-owned                                |

---

## 20. Forbidden Ownership Claims

### 20.1 Forbidden Claims Table

|            Record ID | Forbidden Claim                                      | Violation                                                    |
| -------------------: | ---------------------------------------------------- | ------------------------------------------------------------ |
| ASDT-FS-003-FOWN-001 | `log_level_api/` owns write-side slots               | Violates write-side runtime ownership                        |
| ASDT-FS-003-FOWN-002 | `write_side/` owns envelope assembly                 | Violates API preparation ownership                           |
| ASDT-FS-003-FOWN-003 | `ecosystem_governance/` owns local policy assignment | Violates consuming-domain local interpretation               |
| ASDT-FS-003-FOWN-004 | `dispatcher/` owns downstream records                | Violates authority closure                                   |
| ASDT-FS-003-FOWN-005 | `communications/` owns internal runtime logic        | Collapses boundary with implementation internals             |
| ASDT-FS-003-FOWN-006 | `waiting_list/` owns envelopes                       | Waiting list indexes identifiers, not full payload lifecycle |
| ASDT-FS-003-FOWN-007 | `slot/` owns envelope lifecycle                      | Slot owns placement/occupancy semantics only                 |
| ASDT-FS-003-FOWN-008 | `provider_adapters/` owns hosted receiver behavior   | Provider adapter and receiver port must remain distinct      |
| ASDT-FS-003-FOWN-009 | `docs/` owns implementation meaning                  | Docs explain; semantic folders own                           |
| ASDT-FS-003-FOWN-010 | `tests/` owns implementation behavior                | Tests verify; semantic folders own                           |

---

## 21. Forbidden Dependency Patterns

### 21.1 Forbidden Dependency Table

|            Record ID | Forbidden Dependency                                                | Reason                                   |
| -------------------: | ------------------------------------------------------------------- | ---------------------------------------- |
| ASDT-FS-003-FDEP-001 | Any folder depends on another folder’s `detail/`                    | Violates private implementation boundary |
| ASDT-FS-003-FDEP-002 | Earlier foundational folder depends on later orchestration folder   | Inverts dependency direction             |
| ASDT-FS-003-FDEP-003 | `log_level_api/` depends on `write_side/slot/` internals            | Leaks placement internals                |
| ASDT-FS-003-FDEP-004 | `write_side/` depends on `log_level_api/envelope_assembler/detail/` | Leaks assembly internals                 |
| ASDT-FS-003-FDEP-005 | `ecosystem_governance/` depends on consumer implementation          | Inverts provider/consumer relation       |
| ASDT-FS-003-FDEP-006 | `dispatcher/` depends on downstream registry internals              | Violates downstream non-ownership        |
| ASDT-FS-003-FDEP-007 | `api_facade/` bypasses envelope assembler                           | Violates preparation path                |
| ASDT-FS-003-FDEP-008 | `communications/` bypasses dispatcher for final handoff             | Violates dispatcher finality             |
| ASDT-FS-003-FDEP-009 | Any domain treats raw content as dispatch-ready                     | Violates envelope centrality             |
| ASDT-FS-003-FDEP-010 | Generic utility folder becomes hidden shared dependency             | Obscures semantic ownership              |

---

## 22. Dependency Validation Questions

Before adding a dependency between folders, answer the following.

|            Record ID | Validation Question                                           | Required Answer                          |
| -------------------: | ------------------------------------------------------------- | ---------------------------------------- |
| ASDT-FS-003-DVAL-001 | Which folder owns the depended-on concept?                    | A single narrow owner must be identified |
| ASDT-FS-003-DVAL-002 | Is the dependency using a public surface?                     | Must be yes                              |
| ASDT-FS-003-DVAL-003 | Does the dependency access `detail/`?                         | Must be no                               |
| ASDT-FS-003-DVAL-004 | Does the dependency invert semantic order?                    | Must be no unless formal bridge exists   |
| ASDT-FS-003-DVAL-005 | Does the dependency leak runtime internals?                   | Must be no                               |
| ASDT-FS-003-DVAL-006 | Does the dependency bypass dispatcher finality?               | Must be no                               |
| ASDT-FS-003-DVAL-007 | Does the dependency imply downstream ownership?               | Must be no                               |
| ASDT-FS-003-DVAL-008 | Does the dependency duplicate a shared concept?               | Must be no                               |
| ASDT-FS-003-DVAL-009 | Is a bridge, port, adapter, handle, or view more appropriate? | Must be assessed                         |
| ASDT-FS-003-DVAL-010 | Is the dependency test-only or production-facing?             | Must be declared                         |

---

## 23. Ownership Validation Questions

Before creating or modifying a folder, answer the following.

|            Record ID | Validation Question                                                                                                                        | Required Answer                    |
| -------------------: | ------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------- |
| ASDT-FS-003-OVAL-001 | What semantic meaning does this folder own?                                                                                                | Must be explicit                   |
| ASDT-FS-003-OVAL-002 | Why can this meaning not live under a narrower existing folder?                                                                            | Must be justified                  |
| ASDT-FS-003-OVAL-003 | Is the folder a domain, component, actor, carrier root, state root, port root, adapter root, communication root, docs root, or tests root? | Must be classified                 |
| ASDT-FS-003-OVAL-004 | What does the folder explicitly not own?                                                                                                   | Must be documented                 |
| ASDT-FS-003-OVAL-005 | What public surface may other folders use?                                                                                                 | Must be documented                 |
| ASDT-FS-003-OVAL-006 | What private surface must other folders not use?                                                                                           | Must be documented                 |
| ASDT-FS-003-OVAL-007 | Does the folder create a circular dependency?                                                                                              | Must be no                         |
| ASDT-FS-003-OVAL-008 | Does the folder duplicate glossary taxonomy mechanically?                                                                                  | Must be no                         |
| ASDT-FS-003-OVAL-009 | Does the folder represent implementation semantics, not just documentation?                                                                | Must be yes unless it is `docs/`   |
| ASDT-FS-003-OVAL-010 | Does the folder have local docs/tests scope if meaningful?                                                                                 | Must be yes or explicitly deferred |

---

## 24. Dependency and Ownership Freeze Rules

### 24.1 Freeze Preconditions

A folder dependency/ownership freeze may be declared only after:

1. root domains are accepted,
2. domain internal roots are accepted,
3. each meaningful folder has an ownership statement,
4. each meaningful folder has explicit non-ownership statements,
5. cross-domain dependencies are mapped,
6. forbidden dependencies are listed,
7. `detail/` leakage is prevented,
8. communication boundaries are defined,
9. local docs/tests rules are accepted,
10. anti-collapse rules are reviewed.

### 24.2 Freeze Output

The freeze output should include:

|              Record ID | Freeze Artifact             | Purpose                                          |
| ---------------------: | --------------------------- | ------------------------------------------------ |
| ASDT-FS-003-FREEZE-001 | Folder Ownership Matrix     | Lists each folder and what it owns               |
| ASDT-FS-003-FREEZE-002 | Folder Dependency Matrix    | Lists allowed dependencies                       |
| ASDT-FS-003-FREEZE-003 | Forbidden Dependency Matrix | Lists prohibited dependencies                    |
| ASDT-FS-003-FREEZE-004 | Public Surface Matrix       | Lists approved cross-folder surfaces             |
| ASDT-FS-003-FREEZE-005 | Private Surface Matrix      | Lists protected internals                        |
| ASDT-FS-003-FREEZE-006 | Docs/Tests Scope Matrix     | Lists local documentation and testing scopes     |
| ASDT-FS-003-FREEZE-007 | Anti-Collapse Matrix        | Lists protected distinctions                     |
| ASDT-FS-003-FREEZE-008 | Change-Control Matrix       | Defines how folder dependencies may change later |

---

## 25. Summary

This document defines the folder dependency and ownership rules for the Assembler System Digital Twin Filesystem.

The governing conclusions are:

1. every meaningful folder must own a narrow semantic scope,
2. dependency direction follows “dependency first, then what depends on it,”
3. root domains must not absorb each other’s ownership,
4. domain-internal roots must own first-layer semantic concerns,
5. actor/component folders own local object models,
6. shared roots are allowed only when genuinely shared,
7. carriers belong to the narrowest owner of their carried meaning,
8. ports and adapters are contract-bearing realization surfaces,
9. `state/` belongs to the behavior owner,
10. `detail/` is private to its nearest owner,
11. `docs/` documents the immediate parent scope,
12. `tests/` verifies the immediate parent scope,
13. communications expose approved abstractions, not internals,
14. cross-domain dependencies must use approved public surfaces,
15. downstream registry internals remain outside assembler ownership,
16. file inventory remains deferred.

The next document should define the component subfolder rules in detail, including `docs/`, `tests/`, `carriers/`, `state/`, `hosted_ports/`, `outbound_adapters/`, and `detail/` placement rules.

```
```
