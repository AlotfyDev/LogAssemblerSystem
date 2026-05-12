
# ASDT-FS-001 — Root DDD Domain Folders

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-001-DOC-001 | Document Title | Root DDD Domain Folders |
| ASDT-FS-001-DOC-002 | File Name | `ASDT-FS-001_Root_DDD_Domain_Folders.md` |
| ASDT-FS-001-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-001-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-001-DOC-005 | Project | Assembler System |
| ASDT-FS-001-DOC-006 | Primary Language | English |
| ASDT-FS-001-DOC-007 | Scope Level | Root implementation domain folders |
| ASDT-FS-001-DOC-008 | Implementation Language Direction | C++17, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-001-DOC-009 | Status | Pre-Implementation Folder Doctrine |
| ASDT-FS-001-DOC-010 | File Inventory Status | Deferred |
| ASDT-FS-001-DOC-011 | Depends On | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md` |
| ASDT-FS-001-DOC-012 | Primary Rule | Root implementation folders are DDD implementation domains |
| ASDT-FS-001-DOC-013 | Governing Doctrine | Folder taxonomy must be stabilized before file inventory |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the root DDD implementation domain folders of the Assembler System.

It explains why the accepted root implementation domains are:

```text
ecosystem_governance/
log_level_api/
write_side/
````

This document does not define final C++ files.

This document does not define internal folders inside each root domain in full detail.

This document stabilizes the top-level implementation-domain layer only.

### 2.2 Position in the ASDT-FS Pack

This document follows `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md`.

The previous doctrine established that the filesystem is a logical digital twin of the system model, not a passive storage layout, and that folders must be stabilized before files. 

This document applies that doctrine to the first implementation layer: root DDD domain folders.

### 2.3 What This Document Does

This document defines:

1. the accepted root implementation domains,
2. the architectural meaning of each root domain,
3. the ownership boundary of each root domain,
4. the exclusions of each root domain,
5. the dependency relationship between root domains,
6. the difference between implementation domains and repository support folders,
7. the root-level anti-collapse rules,
8. the folder-first stabilization rules for this layer.

### 2.4 What This Document Does Not Do

This document does not define:

1. final `.hpp` files,
2. final C++ class names,
3. final namespace structure,
4. final build targets,
5. final CMake layout,
6. final package inventory,
7. final internal folder trees,
8. final tests,
9. final docs files,
10. final communications protocol,
11. final runtime algorithms,
12. downstream registry implementation.

Those belong to later ASDT-FS documents and later implementation derivation packs.

---

## 3. Root Domain Doctrine

### 3.1 Primary Rule

```text
Root implementation folders represent DDD implementation domains.
```

They are not arbitrary directories.

They are not documentation groups.

They are not generic technical folders.

They are not convenience buckets.

They are not deployment packages by default.

They are semantic implementation domains derived from the Assembler System architecture.

### 3.2 Root Domain Meaning

A root DDD implementation domain is a top-level implementation folder that owns a bounded semantic context inside the Assembler System.

It governs:

1. the vocabulary used inside the domain,
2. the responsibilities assigned to the domain,
3. the objects that belong to the domain,
4. the actors and components that may live inside the domain,
5. the allowed dependency direction,
6. the local `docs/` scope,
7. the local `tests/` scope,
8. the anti-collapse rules for the domain,
9. the future file inventory derivation for that domain.

### 3.3 Root Domain Non-Meaning

A root implementation domain is not:

1. a documentation category,
2. a build target by default,
3. a namespace by default,
4. a deployment unit by default,
5. a final package by default,
6. a Git repository module by default,
7. a test suite by default,
8. a feature folder,
9. a generic technical grouping,
10. a copy of the glossary taxonomy.

A root domain may later map to one or more namespaces, packages, libraries, or build targets, but those are later derivations.

---

## 4. Accepted Root Implementation Domains

### 4.1 Root Domain Baseline

The accepted root implementation-domain baseline is:

```text
include/
└── assembler/
    ├── ecosystem_governance/
    ├── log_level_api/
    └── write_side/
```

### 4.2 Root Domain Table

|          Record ID | Root Domain Folder      | Domain Name                 | Core Meaning                                                                                                                                                   | Ownership Scope                                              |
| -----------------: | ----------------------- | --------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------ |
| ASDT-FS-001-RD-001 | `ecosystem_governance/` | Ecosystem Governance Domain | Policy type system, policy registries, provider adapters, and consumer-specific receiver ports from the Assembler System perspective                           | Assembler-facing policy governance supply model              |
| ASDT-FS-001-RD-002 | `log_level_api/`        | Log Level API Domain        | Content preparation, validation, timestamp stabilization, metadata injection, envelope assembly, API façade, and write-side bridge hosting                     | Assembler-side preparation API and envelope production model |
| ASDT-FS-001-RD-003 | `write_side/`           | Write Side Domain           | Runtime placement, slots, slots containers, waiting lists, moderators, bundle agent, round managers, reference pre-calculation, dispatcher, and communications | Assembler-side write/runtime coordination and dispatch model |

### 4.3 Root Domain Count Rule

The current implementation-domain count is three.

```text
Root DDD implementation domains:
1. ecosystem_governance
2. log_level_api
3. write_side
```

A fourth root implementation domain must not be added casually.

A new root domain requires evidence that the candidate owns a separate semantic context that cannot be validly placed inside one of the accepted domains.

---

## 5. Root Domain Ordering

### 5.1 Ordering Rule

```text
Dependency first, then what depends on it.
```

The root domain order is not alphabetical.

The root domain order reflects system dependency and meaning.

### 5.2 Accepted Ordering

```text
ecosystem_governance/
→ log_level_api/
→ write_side/
```

### 5.3 Ordering Table

|           Record ID | Order | Domain                  | Reason                                                                                                                                               |
| ------------------: | ----: | ----------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-001-ORD-001 |     1 | `ecosystem_governance/` | Policy definitions, policy registries, provider adapters, and receiver-port definitions are upstream governance inputs for consuming domains         |
| ASDT-FS-001-ORD-002 |     2 | `log_level_api/`        | The API-side preparation model depends on governed policy inputs and produces prepared Log Level Envelopes                                           |
| ASDT-FS-001-ORD-003 |     3 | `write_side/`           | The write-side runtime model receives prepared envelopes, coordinates placement, manages rounds, and dispatches through final assembler-side handoff |

### 5.4 Ordering Clarification

This ordering is a semantic dependency order.

It does not imply that every type in `log_level_api/` directly includes every type in `ecosystem_governance/`.

It does not imply that every type in `write_side/` directly includes every type in `log_level_api/`.

It means that the architectural derivation sequence is:

```text
governed policy supply
→ governed content preparation and envelope assembly
→ write-side runtime coordination and dispatch
```

---

## 6. Repository Support Folders Are Not Root DDD Domains

### 6.1 Rule

```text
Repository support folders are not root DDD implementation domains.
```

### 6.2 Non-Domain Folder Table

|          Record ID | Folder        | Classification     | Reason                                                                            |
| -----------------: | ------------- | ------------------ | --------------------------------------------------------------------------------- |
| ASDT-FS-001-ND-001 | `docs/`       | Repository support | Holds project-wide documentation, not implementation-domain ownership             |
| ASDT-FS-001-ND-002 | `governance/` | Repository support | Holds glossary, schemas, indexes, validation artifacts, and governance references |
| ASDT-FS-001-ND-003 | `tests/`      | Repository support | Holds cross-domain, integration, conformance, and system-level tests              |
| ASDT-FS-001-ND-004 | `tools/`      | Repository support | Holds generators, validators, linters, scripts, and maintenance tools             |
| ASDT-FS-001-ND-005 | `cmake/`      | Build support      | Holds build-system support files                                                  |
| ASDT-FS-001-ND-006 | `examples/`   | Repository support | Holds usage examples and future integration demonstrations                        |
| ASDT-FS-001-ND-007 | `benchmarks/` | Repository support | Holds performance checks, not domain semantics                                    |
| ASDT-FS-001-ND-008 | `scripts/`    | Repository support | Holds automation scripts, not implementation-domain ownership                     |

### 6.3 Important Distinction

A repository may contain:

```text
docs/
tests/
tools/
```

at the repository level.

But every meaningful implementation folder may also contain local:

```text
docs/
tests/
```

The scope differs.

Repository-level `docs/` and `tests/` cover the whole project.

Domain-level `docs/` and `tests/` cover the owning domain.

Component-level `docs/` and `tests/` cover the owning component.

This follows the level-scoped documentation and testing model established in the digital twin doctrine. 

---

## 7. Domain 1 — `ecosystem_governance/`

### 7.1 Domain Definition

`ecosystem_governance/` is the root DDD implementation domain that represents policy-governance supply, policy type definition, policy registry structure, provider adapter responsibility, and consumer-specific policy receiver-port definitions from the perspective of the Assembler System.

It is not the whole external ecosystem.

It is not a general administration application.

It is not a downstream policy database.

It is the assembler-facing implementation mirror of policy governance relations.

### 7.2 Domain Responsibility

The `ecosystem_governance/` domain owns the assembler-facing model for:

1. policy type system,
2. policy clauses,
3. policy mechanisms,
4. policy objects,
5. policy descriptors,
6. policy type registries,
7. provider adapters,
8. receiver-port definitions for consuming domains,
9. policy bundle DTO definitions for consuming domains,
10. governance supply boundaries.

### 7.3 Domain Non-Responsibility

The `ecosystem_governance/` domain does not own:

1. `log_level_api` internal policy assignment,
2. `write_side` internal policy assignment,
3. validator behavior,
4. timestamp stabilization behavior,
5. metadata injection behavior,
6. slots or containers,
7. waiting lists,
8. round managers,
9. dispatcher behavior,
10. downstream registry persistence,
11. downstream query lifecycle,
12. general administrative UI,
13. full external policy registry implementation unless explicitly derived later.

### 7.4 Administrative Perspective Rule

```text
The administrative perspective is a domain-level interpretation of ecosystem_governance,
not necessarily a separate implementation folder.
```

This means the administrative/ecosystem relation is expressed materially through policy provider adapters and consumer-specific receiver ports.

It does not require a root folder named:

```text
administrative/
```

### 7.5 Receiver-Port Rule

```text
Consumer-specific receiver ports are the concrete implementation mirror of the
administrative/consuming policy-feeding relation.
```

Therefore, the domain may contain receiver-port areas for:

```text
receiver_ports/log_level_api/
receiver_ports/write_side/
```

The exact internal folder taxonomy is defined in a later document.

### 7.6 Root-Level Shape

At this document’s level, the accepted root shape is only:

```text
ecosystem_governance/
```

The following domain-internal roots are recognized for later elaboration:

```text
ecosystem_governance/
├── policy_type_system/
├── policy_registries/
├── provider_adapters/
└── receiver_ports/
```

This document does not freeze files inside those folders.

### 7.7 Domain Anti-Collapse Rules

|             Record ID | Protected Meaning          | Must Not Collapse Into             | Reason                                                                                |
| --------------------: | -------------------------- | ---------------------------------- | ------------------------------------------------------------------------------------- |
| ASDT-FS-001-EG-AC-001 | `ecosystem_governance/`    | General external ecosystem         | The domain models assembler-facing governance, not the whole ecosystem                |
| ASDT-FS-001-EG-AC-002 | `ecosystem_governance/`    | `log_level_api/policy_assignment/` | Governance supplies policy material; local assignment belongs to the consuming domain |
| ASDT-FS-001-EG-AC-003 | `ecosystem_governance/`    | `write_side/policy_assignment/`    | Write-side policy interpretation is local to `write_side/`                            |
| ASDT-FS-001-EG-AC-004 | Provider adapters          | Receiver ports                     | Provider-side and consumer-side realizations must remain distinct                     |
| ASDT-FS-001-EG-AC-005 | Policy object              | Policy-consuming component         | Policy material is not the actor that applies behavior                                |
| ASDT-FS-001-EG-AC-006 | Administrative perspective | Separate root domain               | Administrative meaning does not automatically create a root folder                    |
| ASDT-FS-001-EG-AC-007 | Policy registry            | Downstream record registry         | Policy registries and Log Level Records Registry are different systems                |

### 7.8 Domain Documentation and Testing

The domain should support level-scoped local folders:

```text
ecosystem_governance/
├── docs/
├── tests/
└── ...
```

`ecosystem_governance/docs/` should explain the governance supply model, policy type ownership, provider adapter rules, receiver-port rules, and consumer-specific policy bundle boundaries.

`ecosystem_governance/tests/` should eventually verify domain-level conformance, forbidden dependency rules, policy bundle shape constraints, and receiver-port isolation.

---

## 8. Domain 2 — `log_level_api/`

### 8.1 Domain Definition

`log_level_api/` is the root DDD implementation domain that represents the assembler-side content preparation API, policy assignment interpretation, content handling, validation, timestamp stabilization, metadata injection, envelope construction, API façade, and controlled bridge toward the write side.

It is the domain in which incoming governed content becomes a prepared `Log Level Envelope`.

### 8.2 Domain Responsibility

The `log_level_api/` domain owns the assembler-facing model for:

1. local policy assignment for the API domain,
2. governed content representation,
3. validation path,
4. optional policy-bound validation,
5. timestamp stabilization,
6. metadata injection,
7. envelope structure,
8. envelope assembly,
9. API façade,
10. hosted bridge surfaces toward the write side,
11. outbound signaling to the write side where justified,
12. preparation-before-admission semantics.

### 8.3 Domain Non-Responsibility

The `log_level_api/` domain does not own:

1. ecosystem-wide policy type registries,
2. policy provider adapters,
3. write-side slots,
4. write-side slots containers,
5. waiting-list indexes,
6. round managers,
7. reference pre-calculation internals,
8. dispatcher authority,
9. downstream registry implementation,
10. downstream record lifecycle,
11. message brokering,
12. storage persistence,
13. query behavior.

### 8.4 Corrected Ingress Flow Rule

The corrected preparation flow is:

```text
Log Level API
  contains / injects
    Envelope Assembler
      composes Validator, Metadata Injector, Timestamp Stabilizer
      produces Log Level Envelope

Assembler Ingress Port
  receives Log Level Envelope
  admits it into suitable Slot in target Queue Container
```

This means `log_level_api/` is responsible for envelope preparation before write-side admission.

It does not mean the API owns write-side placement internals.

### 8.5 Policy Assignment Rule

The first internal concern inside `log_level_api/` is local policy assignment.

The consuming domain receives policy material through governance-provided receiver-port definitions, then locally interprets that material as API-specific assignments.

Therefore:

```text
ecosystem_governance defines the policy bundle DTO and receiver-port contract shape.
log_level_api hosts the port and assigns policy locally.
```

### 8.6 Assembler and Validator Rule

The envelope assembler does not directly own policy semantics.

The validator may be plain or policy-bound.

The assembler may compose a validator.

Therefore:

```text
Validator may be policy-bound.
Envelope Assembler may be validator-composed.
Envelope Assembler does not become the policy owner.
```

### 8.7 Write-Side Bridge Rule

`log_level_api/` may contain a write-side bridge area.

That bridge must not expose write-side internals.

It may host placement-related ports or outbound adapters, but the detailed communication model is deferred.

The bridge exists only to prevent direct coupling between the envelope preparation domain and write-side internal runtime structures.

### 8.8 Root-Level Shape

At this document’s level, the accepted root shape is only:

```text
log_level_api/
```

The following domain-internal roots are recognized for later elaboration:

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

This document does not freeze files inside those folders.

### 8.9 Domain Anti-Collapse Rules

|               Record ID | Protected Meaning     | Must Not Collapse Into             | Reason                                                                        |
| ----------------------: | --------------------- | ---------------------------------- | ----------------------------------------------------------------------------- |
| ASDT-FS-001-LAPI-AC-001 | `log_level_api/`      | Full external Level API platform   | This domain models assembler-side preparation API concerns                    |
| ASDT-FS-001-LAPI-AC-002 | Envelope Assembler    | Log Level Envelope                 | The assembler produces the envelope; the envelope is a carrier                |
| ASDT-FS-001-LAPI-AC-003 | Validator             | Envelope Assembler                 | Validator may be composed by assembler but remains distinct                   |
| ASDT-FS-001-LAPI-AC-004 | Metadata Injector     | Policy host                        | Metadata injection is schema/directive-governed unless later changed formally |
| ASDT-FS-001-LAPI-AC-005 | Timestamp Stabilizer  | Downstream query timestamp logic   | Timestamp stabilization is pre-dispatch preparation                           |
| ASDT-FS-001-LAPI-AC-006 | API policy assignment | Ecosystem policy registry          | Local assignment is not source registry ownership                             |
| ASDT-FS-001-LAPI-AC-007 | Write-side bridge     | Write-side internals               | Bridge must expose approved references, not runtime internals                 |
| ASDT-FS-001-LAPI-AC-008 | API façade            | Full application integration layer | API façade remains within assembler preparation scope                         |

### 8.10 Domain Documentation and Testing

The domain should support level-scoped local folders:

```text
log_level_api/
├── docs/
├── tests/
└── ...
```

`log_level_api/docs/` should explain API-domain preparation responsibility, policy assignment locality, validator composition, envelope assembly, metadata/timestamp preparation, bridge restrictions, and forbidden ownership.

`log_level_api/tests/` should eventually verify domain-level preparation behavior, forbidden dependency rules, envelope production requirements, and bridge isolation.

---

## 9. Domain 3 — `write_side/`

### 9.1 Domain Definition

`write_side/` is the root DDD implementation domain that represents assembler-side write/runtime coordination after envelope preparation.

It owns the runtime model for slots, slots containers, waiting lists, moderators, bundle agent, round managers, reference pre-calculation, dispatcher, and communications.

It is the domain where prepared envelopes are coordinated for placement, writing rounds, delivery rounds, dispatch readiness, and final assembler-side handoff.

### 9.2 Domain Responsibility

The `write_side/` domain owns the assembler-facing model for:

1. local write-side policy assignment,
2. slots,
3. slots containers,
4. waiting-list indexes,
5. slots container moderators,
6. slots container bundle agent,
7. writing/feeding round management,
8. delivery/dispatching round management,
9. reference pre-calculation,
10. dispatcher,
11. log-level-api feeding communications,
12. registry delivery communications,
13. write-side runtime state models,
14. final assembler-side dispatch boundary.

### 9.3 Domain Non-Responsibility

The `write_side/` domain does not own:

1. raw content creation,
2. envelope assembly before preparation,
3. external policy registry internals,
4. log-level API façade,
5. validator behavior,
6. metadata injection behavior,
7. timestamp stabilization behavior,
8. downstream registry internals,
9. downstream persistence,
10. downstream query lifecycle,
11. downstream indexing,
12. downstream replay,
13. downstream mutation,
14. full messaging broker behavior.

### 9.4 Queue-as-Container Rule

The write-side runtime model follows:

```text
Queue = Container.
Queue ≠ Message Broker.
```

This means `write_side/` owns queue-container coordination.

It does not become a message broker.

### 9.5 Bundle Agent Rule

The slots container bundle agent is responsible for:

1. horizontal scaling of containers,
2. vertical scaling of slots per container,
3. existence of slots containers,
4. assigning one moderator per slots container,
5. maintaining bundle topology.

It is not the round manager.

It is not the dispatcher.

### 9.6 Moderator Rule

Each slots container has one assigned moderator.

The moderator is responsible for:

1. preparing the assigned container,
2. preparing the assigned slots,
3. qualifying the container for rounds,
4. reporting full/readiness signals,
5. reinitializing the container after delivery round exit.

The moderator does not own the whole bundle.

The moderator does not own waiting-list indexes.

### 9.7 Round Manager Rule

The round manager is responsible for waiting-list membership and movement across writing/feeding and delivery/dispatching rounds.

It records identifiers of containers and moderators into the appropriate waiting-list indexes.

It does not create containers.

It does not scale containers.

It does not prepare slots.

### 9.8 Reference Pre-Calculator Rule

The reference pre-calculator is a first-class write-side component.

It prepares current and next placement references proactively so the feeding workflow can remain stable and continuous.

It must not expose write-side internals to `log_level_api/`.

It may depend on round-manager and waiting-list information, but it does not replace the round manager.

### 9.9 Dispatcher Rule

Dispatcher is the final assembler-side outbound actor.

It performs dispatcher-mediated handoff through the registry/delivery-facing boundary.

It does not become the downstream registry.

It does not own post-handoff lifecycle.

### 9.10 Communications Rule

`write_side/communications/` comes after internal runtime structures.

Communications must expose approved abstractions, ports, adapters, and carriers.

Communications must not expose:

1. slot internals,
2. slots container internals,
3. bundle scaling internals,
4. waiting-list internals,
5. moderator internals,
6. round-manager internals,
7. dispatcher internals beyond approved handoff surface.

### 9.11 Root-Level Shape

At this document’s level, the accepted root shape is only:

```text
write_side/
```

The following domain-internal roots are recognized for later elaboration:

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

This document does not freeze files inside those folders.

### 9.12 Domain Anti-Collapse Rules

|             Record ID | Protected Meaning               | Must Not Collapse Into        | Reason                                                                                    |
| --------------------: | ------------------------------- | ----------------------------- | ----------------------------------------------------------------------------------------- |
| ASDT-FS-001-WS-AC-001 | `write_side/`                   | Full messaging system         | Write-side queues are containers, not broker infrastructure                               |
| ASDT-FS-001-WS-AC-002 | Slot                            | Envelope lifecycle owner      | Slot placement does not imply lifecycle ownership                                         |
| ASDT-FS-001-WS-AC-003 | Slots Container                 | Message broker queue          | Queue container is runtime structure, not broker                                          |
| ASDT-FS-001-WS-AC-004 | Waiting List                    | Envelope store                | Waiting lists index identifiers, not full envelope stores                                 |
| ASDT-FS-001-WS-AC-005 | Bundle Agent                    | Round Manager                 | Bundle agent manages existence and scaling; round manager manages waiting-list membership |
| ASDT-FS-001-WS-AC-006 | Moderator                       | Bundle Agent                  | Moderator prepares one assigned container; bundle agent manages container topology        |
| ASDT-FS-001-WS-AC-007 | Round Manager                   | Dispatcher                    | Round manager manages rounds; dispatcher performs final outbound handoff                  |
| ASDT-FS-001-WS-AC-008 | Reference Pre-Calculator        | Bridge                        | Pre-calculator computes references; bridge exposes approved abstraction                   |
| ASDT-FS-001-WS-AC-009 | Dispatcher                      | Registry                      | Dispatcher hands off; registry is downstream                                              |
| ASDT-FS-001-WS-AC-010 | Registry Delivery Communication | Downstream registry internals | Communication boundary does not imply registry ownership                                  |

### 9.13 Domain Documentation and Testing

The domain should support level-scoped local folders:

```text
write_side/
├── docs/
├── tests/
└── ...
```

`write_side/docs/` should explain runtime coordination, queue-as-container doctrine, slot/container ownership, waiting-list behavior, bundle-agent scaling, moderator assignment, round management, reference pre-calculation, dispatcher finality, and communications boundaries.

`write_side/tests/` should eventually verify domain-level dependency rules, runtime coordination flows, invalid ownership claims, round movement, reference continuity, and dispatcher boundary closure.

---

## 10. Cross-Domain Dependency Model

### 10.1 High-Level Flow

```text
ecosystem_governance/
  supplies governed policy definitions, provider adapters, and receiver-port definitions
        ↓
log_level_api/
  receives/hosts policy ports, prepares content, produces Log Level Envelopes
        ↓
write_side/
  receives prepared envelopes, coordinates runtime placement, dispatches outward
```

### 10.2 Cross-Domain Dependency Table

|          Record ID | From Domain      | To Domain               | Allowed Relationship                                                                                                 | Constraint                              |
| -----------------: | ---------------- | ----------------------- | -------------------------------------------------------------------------------------------------------------------- | --------------------------------------- |
| ASDT-FS-001-XD-001 | `log_level_api/` | `ecosystem_governance/` | Hosts governance-provided policy receiver-port surfaces and consumes policy bundle definitions                       | Must not own ecosystem registries       |
| ASDT-FS-001-XD-002 | `write_side/`    | `ecosystem_governance/` | Hosts governance-provided write-side policy receiver-port surfaces and consumes write-side policy bundle definitions | Must not own ecosystem registries       |
| ASDT-FS-001-XD-003 | `write_side/`    | `log_level_api/`        | Receives prepared envelope-facing communication through approved feeding boundary                                    | Must not depend on API internals        |
| ASDT-FS-001-XD-004 | `log_level_api/` | `write_side/`           | Hosts or composes approved write-side placement/reference abstractions                                               | Must not depend on write-side internals |
| ASDT-FS-001-XD-005 | `write_side/`    | Downstream registry     | Performs registry delivery through dispatcher-mediated handoff                                                       | Must not own downstream lifecycle       |

### 10.3 Forbidden Cross-Domain Dependencies

|           Record ID | Forbidden Dependency                                            | Reason                                                                             |
| ------------------: | --------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| ASDT-FS-001-FXD-001 | `ecosystem_governance/` depending on `log_level_api/` internals | Governance definitions must not depend on consumer implementation                  |
| ASDT-FS-001-FXD-002 | `ecosystem_governance/` depending on `write_side/` internals    | Governance definitions must not depend on runtime implementation                   |
| ASDT-FS-001-FXD-003 | `log_level_api/` depending on write-side slot internals         | API domain must not know placement internals                                       |
| ASDT-FS-001-FXD-004 | `write_side/` depending on envelope assembler internals         | Write-side receives prepared envelope-facing abstractions, not assembler internals |
| ASDT-FS-001-FXD-005 | Any domain depending on downstream registry internals           | Registry internals are outside assembler ownership                                 |
| ASDT-FS-001-FXD-006 | Any domain bypassing Dispatcher for final handoff               | Dispatcher is the final assembler-side outbound actor                              |
| ASDT-FS-001-FXD-007 | Any domain treating raw content as dispatch-ready               | Prepared Log Level Envelope is required before downstream handoff                  |

---

## 11. Root-Level Local Docs and Tests

### 11.1 Rule

```text
Every root DDD implementation domain may own local docs/ and tests/.
```

### 11.2 Domain-Level Docs

Domain-level `docs/` explain the domain itself.

They should cover:

1. domain purpose,
2. domain boundaries,
3. owned concepts,
4. excluded concepts,
5. cross-domain relations,
6. local anti-collapse rules,
7. dependency constraints,
8. domain-level obligations,
9. future file inventory rationale,
10. local testing rationale.

### 11.3 Domain-Level Tests

Domain-level `tests/` verify domain-level behavior and conformance.

They may eventually include:

1. dependency conformance tests,
2. forbidden include checks,
3. domain-boundary tests,
4. contract-bearing surface tests,
5. anti-collapse validation tests,
6. local integration tests,
7. domain-specific behavior tests,
8. local state-model tests where relevant.

### 11.4 Root Domain Docs/Tests Baseline

```text
include/
└── assembler/
    ├── ecosystem_governance/
    │   ├── docs/
    │   └── tests/
    │
    ├── log_level_api/
    │   ├── docs/
    │   └── tests/
    │
    └── write_side/
        ├── docs/
        └── tests/
```

This document recognizes these folders as valid at the root domain level.

It does not define their final file contents.

---

## 12. Root Namespace and Include Path Considerations

### 12.1 Namespace Deferral Rule

This document does not freeze final C++ namespace spelling.

However, the folder baseline suggests a future namespace shape such as:

```cpp
assembler::ecosystem_governance
assembler::log_level_api
assembler::write_side
```

This remains a future derivation, not a final decision.

### 12.2 Include Path Deferral Rule

This document does not freeze final include conventions.

Potential include paths may later follow:

```cpp
#include <assembler/ecosystem_governance/...>
#include <assembler/log_level_api/...>
#include <assembler/write_side/...>
```

But final header inventory and include structure remain deferred.

### 12.3 Build Target Deferral Rule

Root domains may later map to:

1. one header-only target,
2. multiple interface library targets,
3. domain-specific interface targets,
4. implementation targets if non-header-only material appears.

This document does not decide that mapping.

---

## 13. Folder-First Constraints at Root Level

### 13.1 No File Inventory Constraint

No root domain file inventory is frozen by this document.

The following are not yet final:

1. `TPolicyClause.hpp`,
2. `TLogLevelEnvelope.hpp`,
3. `TSlot.hpp`,
4. `TDispatcher.hpp`,
5. any `Traits` file,
6. any `Contract` file,
7. any `StateMachine` file,
8. any `DTO` file.

Such names may be useful examples from prior discussion, but root folder meaning must stabilize first.

### 13.2 No Technical Folder First Constraint

The implementation root must not begin as:

```text
include/
└── assembler/
    ├── templates/
    ├── interfaces/
    ├── impl/
    ├── data/
    ├── utils/
    └── tests/
```

This would derive architecture from technical storage categories rather than semantic domains.

### 13.3 No Documentation-as-Domain Constraint

The implementation root must not treat:

```text
docs/
governance/
glossary/
schemas/
roadmap/
```

as implementation domains.

These may be critical project support areas, but they are not root DDD implementation folders.

---

## 14. Root Domain Validation Questions

Before accepting any future change to the root domain set, the following questions must be answered.

|           Record ID | Validation Question                                                                           | Required Answer Type           |
| ------------------: | --------------------------------------------------------------------------------------------- | ------------------------------ |
| ASDT-FS-001-VAL-001 | Does the proposed folder own a semantic context, or is it merely technical?                   | Semantic context required      |
| ASDT-FS-001-VAL-002 | Does the proposed folder own responsibilities that cannot fit inside an existing root domain? | Evidence required              |
| ASDT-FS-001-VAL-003 | Does the proposed folder preserve dependency order?                                           | Must not invert dependencies   |
| ASDT-FS-001-VAL-004 | Does the proposed folder avoid turning documentation into implementation?                     | Must pass                      |
| ASDT-FS-001-VAL-005 | Does the proposed folder avoid duplicating glossary taxonomy as folder taxonomy?              | Must pass                      |
| ASDT-FS-001-VAL-006 | Does the proposed folder avoid bypassing dispatcher finality?                                 | Must pass                      |
| ASDT-FS-001-VAL-007 | Does the proposed folder avoid downstream registry ownership?                                 | Must pass                      |
| ASDT-FS-001-VAL-008 | Does the proposed folder have clear local docs/tests scope?                                   | Required for meaningful folder |
| ASDT-FS-001-VAL-009 | Does the proposed folder introduce a circular dependency?                                     | Must not                       |
| ASDT-FS-001-VAL-010 | Does the proposed folder preserve folder-first doctrine?                                      | Must pass                      |

---

## 15. Root Domain Change Control

### 15.1 Change Rule

```text
Changing the root DDD implementation domain set requires architectural review.
```

### 15.2 Change Types

|           Record ID | Change Type                      | Review Requirement                                                                   |
| ------------------: | -------------------------------- | ------------------------------------------------------------------------------------ |
| ASDT-FS-001-CHG-001 | Add root domain                  | Requires proof of independent semantic ownership                                     |
| ASDT-FS-001-CHG-002 | Remove root domain               | Requires proof that responsibilities are safely reassigned                           |
| ASDT-FS-001-CHG-003 | Rename root domain               | Requires glossary and reference impact review                                        |
| ASDT-FS-001-CHG-004 | Split root domain                | Requires dependency and ownership review                                             |
| ASDT-FS-001-CHG-005 | Merge root domains               | Requires anti-collapse review                                                        |
| ASDT-FS-001-CHG-006 | Move root responsibility         | Requires source trace and responsibility-chain review                                |
| ASDT-FS-001-CHG-007 | Promote support folder to domain | Requires proof it is not merely documentation, tooling, build, or validation support |

### 15.3 Root Domain Freeze Point

A root-domain freeze point may be declared only after:

1. root domain names are accepted,
2. root domain meanings are accepted,
3. root domain exclusions are accepted,
4. root dependency direction is accepted,
5. domain-level docs/tests rule is accepted,
6. internal domain root taxonomy is drafted,
7. anti-collapse rules are reviewed,
8. cross-domain dependency rules are reviewed.

---

## 16. Accepted Baseline Summary

### 16.1 Folder Baseline

```text
include/
└── assembler/
    ├── ecosystem_governance/
    │   ├── docs/
    │   └── tests/
    │
    ├── log_level_api/
    │   ├── docs/
    │   └── tests/
    │
    └── write_side/
        ├── docs/
        └── tests/
```

### 16.2 Domain-Internal Roots Preview

The next layer is recognized but not fully defined in this document.

```text
ecosystem_governance/
├── policy_type_system/
├── policy_registries/
├── provider_adapters/
└── receiver_ports/
```

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

These are elaborated in the next ASDT-FS documents.

---

## 17. Summary

This document establishes the root DDD implementation domain folder layer for the Assembler System Digital Twin Filesystem Structure Pack.

The accepted root implementation domains are:

```text
ecosystem_governance/
log_level_api/
write_side/
```

The governing conclusions are:

1. root implementation folders are DDD implementation domains,
2. root domains are semantic implementation contexts, not generic folders,
3. repository support folders are not root DDD domains,
4. `ecosystem_governance/` owns assembler-facing policy governance supply structure,
5. `log_level_api/` owns preparation, envelope assembly, and API-facing preparation structure,
6. `write_side/` owns runtime coordination, placement, rounds, dispatcher, and communications structure,
7. root domain ordering follows dependency and meaning,
8. domain-level `docs/` and `tests/` are valid and scope-local,
9. file inventory remains deferred,
10. internal root taxonomy is handled in later ASDT-FS documents.

The next document shall define the domain-internal folder taxonomy for the accepted root domains.

```
```
