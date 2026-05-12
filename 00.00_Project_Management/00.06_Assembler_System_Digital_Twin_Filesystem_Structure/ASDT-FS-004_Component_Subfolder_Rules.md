
# ASDT-FS-004 — Component Subfolder Rules

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-004-DOC-001 | Document Title | Component Subfolder Rules |
| ASDT-FS-004-DOC-002 | File Name | `ASDT-FS-004_Component_Subfolder_Rules.md` |
| ASDT-FS-004-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-004-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-004-DOC-005 | Project | Assembler System |
| ASDT-FS-004-DOC-006 | Primary Language | English |
| ASDT-FS-004-DOC-007 | Scope Level | Component-level subfolder doctrine |
| ASDT-FS-004-DOC-008 | Implementation Language Direction | C++17, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-004-DOC-009 | Status | Pre-Implementation Folder Doctrine |
| ASDT-FS-004-DOC-010 | File Inventory Status | Deferred |
| ASDT-FS-004-DOC-011 | Depends On | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md`, `ASDT-FS-001_Root_DDD_Domain_Folders.md`, `ASDT-FS-003_Folder_Dependency_And_Ownership_Rules.md` |
| ASDT-FS-004-DOC-012 | Primary Rule | A component subfolder exists only when it represents a real local semantic responsibility |
| ASDT-FS-004-DOC-013 | Governing Principle | Component subfolders must preserve local ownership, local documentation, local testing, private internals, and public boundary surfaces |
| ASDT-FS-004-DOC-014 | Excluded From This Document | Final file inventory, final class names, final include graph, final CMake targets, final runtime algorithms |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the standard subfolder rules for actor, component, carrier-root, state-root, port-root, adapter-root, and communication-boundary folders inside the Assembler System Digital Twin Filesystem.

It answers the question:

```text
When a folder represents a real component or actor, which subfolders may exist
inside it, what does each subfolder mean, what does each subfolder own,
and what must each subfolder not own?
````

This document does not require every component to contain every possible subfolder.

Instead, it defines a controlled vocabulary of component subfolders and the rules governing when each one is valid.

### 2.2 Why This Document Exists

`ASDT-FS-003` established that actor and component folders own their local object model, and that local docs, tests, carriers, state, ports, adapters, and private details should live close to the owner when their meaning is local.

This document turns that principle into a reusable component-subfolder doctrine.

Without this document, future implementation folders may drift into generic patterns such as:

```text
models/
services/
helpers/
utils/
interfaces/
impl/
```

Those names may be technically familiar, but they are not precise enough for the Assembler System unless they are derived from a declared semantic owner.

### 2.3 What This Document Does

This document defines:

1. valid component subfolder classes,
2. when each subfolder class may appear,
3. what each subfolder class owns,
4. what each subfolder class must not own,
5. required parent-child ownership rules,
6. local `docs/` rules,
7. local `tests/` rules,
8. local `carriers/` rules,
9. local `state/` rules,
10. local `hosted_ports/` rules,
11. local `outbound_adapters/` rules,
12. local `detail/` rules,
13. local `policies/` rules where valid,
14. local `contracts/` rules where valid,
15. local `fixtures/` rules where valid,
16. communication-boundary subfolder rules,
17. forbidden component subfolder patterns,
18. validation questions for creating component subfolders.

### 2.4 What This Document Does Not Do

This document does not define:

1. final `.hpp` files,
2. final C++ class names,
3. final namespaces,
4. final include directives,
5. final test file names,
6. final CMake targets,
7. final runtime scheduling algorithms,
8. final downstream registry implementation,
9. final database schema,
10. final package inventory.

All file-level decisions remain deferred until folder semantics stabilize.

---

## 3. Component Subfolder Doctrine

### 3.1 Primary Rule

```text id="asdt-fs-004-primary-rule"
A component subfolder exists only when it represents a real local semantic responsibility.
```

A component must not receive a subfolder merely because a template says so.

For example, a component should not automatically contain:

```text
docs/
tests/
carriers/
state/
hosted_ports/
outbound_adapters/
detail/
```

unless each subfolder has a justified local meaning.

### 3.2 Optionality Rule

```text id="asdt-fs-004-optionality-rule"
All component subfolders are optional until justified by the component’s actual ownership.
```

A minimal component may have no subfolders.

A mature component may have several.

The presence of a subfolder must be explained by local ownership, local behavior, local boundary exposure, or local verification needs.

### 3.3 Parent Ownership Rule

```text id="asdt-fs-004-parent-ownership-rule"
A component subfolder inherits its semantic boundary from its immediate parent.
```

For example:

```text
write_side/dispatcher/state/
```

means:

```text
state owned by dispatcher
```

It does not mean:

```text
all write-side state
```

or:

```text
downstream registry lifecycle state
```

### 3.4 No Hidden Global Meaning Rule

```text id="asdt-fs-004-no-hidden-global-rule"
A local subfolder must not silently become a global system folder.
```

Examples:

1. `validator/detail/` is private to `validator/`.
2. `dispatcher/state/` is dispatcher-local.
3. `round_manager/carriers/` is round-manager-local.
4. `communications/registry_delivery/carriers/` is boundary-local.
5. `policy_assignment/hosted_ports/` is assignment-local.

---

## 4. Component Subfolder Inventory

### 4.1 Standard Subfolder Classes

|          Record ID | Subfolder            | Folder Class                        | Core Meaning                                                                              |
| -----------------: | -------------------- | ----------------------------------- | ----------------------------------------------------------------------------------------- |
| ASDT-FS-004-SF-001 | `docs/`              | local_documentation_scope           | Documents the immediate parent scope                                                      |
| ASDT-FS-004-SF-002 | `tests/`             | local_test_scope                    | Verifies the immediate parent scope                                                       |
| ASDT-FS-004-SF-003 | `carriers/`          | local_carrier_scope                 | Owns local carried objects or DTO-like structures                                         |
| ASDT-FS-004-SF-004 | `state/`             | local_state_scope                   | Owns local behavioral state or state-machine semantics                                    |
| ASDT-FS-004-SF-005 | `hosted_ports/`      | local_inbound_contract_surface      | Owns ports hosted by the parent component                                                 |
| ASDT-FS-004-SF-006 | `outbound_adapters/` | local_outbound_contract_surface     | Owns adapters emitted by the parent component                                             |
| ASDT-FS-004-SF-007 | `detail/`            | local_private_implementation_scope  | Owns private implementation internals                                                     |
| ASDT-FS-004-SF-008 | `policies/`          | local_policy_material_scope         | Owns local policy-facing material only when policy consumption is local                   |
| ASDT-FS-004-SF-009 | `contracts/`         | local_contract_representation_scope | Owns local contract representations only when not better placed as ports/adapters         |
| ASDT-FS-004-SF-010 | `fixtures/`          | local_test_fixture_scope            | Owns test-only fixtures for local tests                                                   |
| ASDT-FS-004-SF-011 | `examples/`          | local_example_scope                 | Owns local usage examples for the parent scope                                            |
| ASDT-FS-004-SF-012 | `views/`             | local_view_scope                    | Owns read-only or projection-like surfaces when needed                                    |
| ASDT-FS-004-SF-013 | `handles/`           | local_handle_scope                  | Owns reference or handle abstractions when needed                                         |
| ASDT-FS-004-SF-014 | `validators/`        | nested_validation_scope             | Allowed only when validation is a subordinate local concern, not a domain-level component |
| ASDT-FS-004-SF-015 | `transitions/`       | local_transition_scope              | Allowed under `state/` when transition semantics are complex                              |

### 4.2 Standard Component Shape

The general logical shape is:

```text id="asdt-fs-004-general-shape"
component_or_actor/
├── docs/
├── tests/
├── carriers/
├── state/
├── hosted_ports/
├── outbound_adapters/
├── policies/
├── contracts/
├── views/
├── handles/
└── detail/
```

This is not a required physical template.

It is a controlled vocabulary of valid local subfolder meanings.

### 4.3 Minimal Component Shape

A component may be valid with only:

```text id="asdt-fs-004-minimal-shape"
component_or_actor/
```

if the component’s public surface and internals are not yet decomposed.

### 4.4 Mature Component Shape

A mature component may look like:

```text id="asdt-fs-004-mature-shape"
component_or_actor/
├── docs/
├── tests/
├── carriers/
├── state/
├── hosted_ports/
├── outbound_adapters/
└── detail/
```

Only justified subfolders should be created.

---

## 5. `docs/` Subfolder Rules

### 5.1 Definition

`docs/` is the local documentation scope for its immediate parent folder.

It explains the meaning, responsibility, boundaries, public surfaces, private surfaces, local flow, and local anti-collapse rules of the parent.

### 5.2 Ownership Rule

```text id="asdt-fs-004-docs-rule"
docs/ documents its immediate parent scope.
It does not create implementation ownership.
```

### 5.3 Valid Placement

|            Record ID | Parent Folder                                          | Valid Docs Meaning                                                   |
| -------------------: | ------------------------------------------------------ | -------------------------------------------------------------------- |
| ASDT-FS-004-DOCS-001 | `log_level_api/validator/docs/`                        | Documents validator behavior and local constraints                   |
| ASDT-FS-004-DOCS-002 | `log_level_api/envelope_assembler/docs/`               | Documents assembly behavior and preparation participant coordination |
| ASDT-FS-004-DOCS-003 | `write_side/slot/docs/`                                | Documents slot semantics and occupancy constraints                   |
| ASDT-FS-004-DOCS-004 | `write_side/dispatcher/docs/`                          | Documents dispatcher finality and handoff behavior                   |
| ASDT-FS-004-DOCS-005 | `write_side/communications/registry_delivery/docs/`    | Documents registry-facing delivery boundary                          |
| ASDT-FS-004-DOCS-006 | `ecosystem_governance/receiver_ports/write_side/docs/` | Documents write-side receiver-port definitions                       |

### 5.4 Docs Content Expectations

A local `docs/` folder should explain:

1. parent purpose,
2. parent ownership,
3. parent non-ownership,
4. parent public surface,
5. parent private surface,
6. allowed dependencies,
7. forbidden dependencies,
8. local carriers if any,
9. local state if any,
10. local ports/adapters if any,
11. local tests and verification scope,
12. anti-collapse rules.

### 5.5 Docs Anti-Collapse Rule

```text id="asdt-fs-004-docs-anti-collapse"
Documentation explains ownership.
Documentation does not own implementation meaning.
```

A concept is not owned by the folder where it is most thoroughly explained.

A concept is owned by the folder whose semantic scope justifies the concept.

---

## 6. `tests/` Subfolder Rules

### 6.1 Definition

`tests/` is the local verification scope for its immediate parent folder.

It contains tests that verify the behavior, contracts, state transitions, boundary surfaces, local carriers, and anti-collapse constraints of the parent.

### 6.2 Ownership Rule

```text id="asdt-fs-004-tests-rule"
tests/ verifies its immediate parent scope.
It does not grant ownership over foreign internals.
```

### 6.3 Valid Placement

|             Record ID | Parent Folder                                        | Valid Tests Meaning                             |
| --------------------: | ---------------------------------------------------- | ----------------------------------------------- |
| ASDT-FS-004-TESTS-001 | `log_level_api/validator/tests/`                     | Tests validation behavior                       |
| ASDT-FS-004-TESTS-002 | `log_level_api/envelope_assembler/tests/`            | Tests assembly coordination                     |
| ASDT-FS-004-TESTS-003 | `write_side/slot/tests/`                             | Tests slot semantics and occupancy invariants   |
| ASDT-FS-004-TESTS-004 | `write_side/slots_container/tests/`                  | Tests container placement behavior              |
| ASDT-FS-004-TESTS-005 | `write_side/round_manager/tests/`                    | Tests round membership and transition behavior  |
| ASDT-FS-004-TESTS-006 | `write_side/dispatcher/tests/`                       | Tests dispatch eligibility and handoff behavior |
| ASDT-FS-004-TESTS-007 | `write_side/communications/registry_delivery/tests/` | Tests registry-facing boundary isolation        |

### 6.4 Test Dependency Rule

Local tests may use:

1. parent public surface,
2. parent local fixtures,
3. mocks of approved external surfaces,
4. approved test carriers,
5. approved public handles,
6. approved public ports,
7. approved public adapters.

Local tests must not use:

1. another component’s `detail/`,
2. another component’s private state,
3. raw downstream internals,
4. private queue internals outside the tested parent,
5. private registry internals,
6. hidden friend-like implementation shortcuts.

### 6.5 Test Anti-Collapse Rule

```text id="asdt-fs-004-tests-anti-collapse"
A test may verify behavior across a boundary.
It must not erase the boundary.
```

Integration tests may coordinate multiple folders.

They still must respect public surfaces.

---

## 7. `fixtures/` Subfolder Rules

### 7.1 Definition

`fixtures/` contains local test-only objects used by the parent’s `tests/`.

### 7.2 Placement Rule

```text id="asdt-fs-004-fixtures-rule"
fixtures/ belongs under tests/ unless the fixtures are explicitly reusable across a wider test scope.
```

Preferred local shape:

```text id="asdt-fs-004-fixtures-shape"
component_or_actor/
└── tests/
    └── fixtures/
```

A top-level `fixtures/` folder is discouraged unless the fixture is shared by multiple test scopes and its ownership is explicitly documented.

### 7.3 Fixture Non-Production Rule

```text id="asdt-fs-004-fixture-non-production"
A fixture must not become production input by accident.
```

Fixtures must not define canonical system behavior.

They may simulate, mock, or sample behavior for test purposes only.

---

## 8. `carriers/` Subfolder Rules

### 8.1 Definition

`carriers/` owns local carried structures whose meaning belongs to the parent folder.

A carrier may represent:

1. input material,
2. output material,
3. request material,
4. response material,
5. report material,
6. evidence material,
7. handle material,
8. view material,
9. transfer material,
10. local DTO-like material.

### 8.2 Carrier Placement Rule

```text id="asdt-fs-004-carriers-rule"
carriers/ belongs to the narrowest parent folder that owns the meaning of what is carried.
```

### 8.3 Valid Carrier Placement

|           Record ID | Carrier Location                                            | Valid Meaning                                                |
| ------------------: | ----------------------------------------------------------- | ------------------------------------------------------------ |
| ASDT-FS-004-CAR-001 | `log_level_api/envelope/carriers/`                          | Only if envelope has local sub-carriers requiring separation |
| ASDT-FS-004-CAR-002 | `log_level_api/envelope_assembler/carriers/`                | Assembly-local input/result carriers                         |
| ASDT-FS-004-CAR-003 | `log_level_api/policy_assignment/carriers/`                 | API-domain policy assignment carriers                        |
| ASDT-FS-004-CAR-004 | `write_side/policy_assignment/carriers/`                    | Write-side policy assignment carriers                        |
| ASDT-FS-004-CAR-005 | `write_side/slot/carriers/`                                 | Slot-local carrier structures                                |
| ASDT-FS-004-CAR-006 | `write_side/slots_container/carriers/`                      | Container-local placement carriers                           |
| ASDT-FS-004-CAR-007 | `write_side/round_manager/carriers/`                        | Round movement or membership carriers                        |
| ASDT-FS-004-CAR-008 | `write_side/dispatcher/carriers/`                           | Dispatch and handoff carriers                                |
| ASDT-FS-004-CAR-009 | `write_side/communications/log_level_api_feeding/carriers/` | Feeding-boundary carriers                                    |
| ASDT-FS-004-CAR-010 | `write_side/communications/registry_delivery/carriers/`     | Registry-delivery boundary carriers                          |

### 8.4 Carrier Non-Ownership Rule

```text id="asdt-fs-004-carrier-non-ownership"
A carrier does not own the behavior that produces, validates, assigns, dispatches, or persists it.
```

Examples:

1. An assembly result carrier does not own assembly behavior.
2. A dispatch report carrier does not own dispatch behavior.
3. A handoff evidence carrier does not own downstream persistence.
4. A slot occupancy carrier does not own envelope lifecycle.
5. A policy assignment carrier does not own policy-source lifecycle.

### 8.5 Carrier Sharing Rule

A carrier may be shared only if:

1. multiple local components require it,
2. the carrier’s meaning is genuinely shared,
3. the shared owner is narrower than the whole domain where possible,
4. the carrier does not expose private fields from one component to another,
5. the carrier does not create hidden coupling.

---

## 9. `state/` Subfolder Rules

### 9.1 Definition

`state/` owns local behavioral state, readiness state, lifecycle state, transition rules, or state-machine semantics belonging to the parent component.

### 9.2 Placement Rule

```text id="asdt-fs-004-state-rule"
state/ belongs inside the folder that owns the behavior whose state is being modeled.
```

### 9.3 Valid State Placement

|             Record ID | State Location                                   | Valid Meaning                                      |
| --------------------: | ------------------------------------------------ | -------------------------------------------------- |
| ASDT-FS-004-STATE-001 | `write_side/slot/state/`                         | Slot lifecycle and occupancy state                 |
| ASDT-FS-004-STATE-002 | `write_side/slots_container/state/`              | Container readiness, fullness, and placement state |
| ASDT-FS-004-STATE-003 | `write_side/slots_container_moderator/state/`    | Moderator preparation and reinitialization state   |
| ASDT-FS-004-STATE-004 | `write_side/slots_container_bundle_agent/state/` | Bundle topology and scaling state                  |
| ASDT-FS-004-STATE-005 | `write_side/round_manager/state/`                | Round membership and movement state                |
| ASDT-FS-004-STATE-006 | `write_side/dispatcher/state/`                   | Dispatch eligibility and handoff state             |
| ASDT-FS-004-STATE-007 | `log_level_api/validator/state/`                 | Validation state if behavior requires it           |
| ASDT-FS-004-STATE-008 | `log_level_api/envelope_assembler/state/`        | Assembly state if behavior requires it             |

### 9.4 State Substructure

A complex `state/` folder may contain:

```text id="asdt-fs-004-state-shape"
state/
├── transitions/
├── guards/
├── snapshots/
└── docs/
```

Only justified subfolders should appear.

### 9.5 State Anti-Collapse Rule

```text id="asdt-fs-004-state-anti-collapse"
State is not a cosmetic status field.
State carries behavioral consequences and transition constraints.
```

A status flag may live in a carrier.

A state model governs what can happen next.

---

## 10. `transitions/` Subfolder Rules

### 10.1 Definition

`transitions/` contains local transition semantics for state models when those semantics are too complex to remain directly under `state/`.

### 10.2 Placement Rule

```text id="asdt-fs-004-transitions-rule"
transitions/ is valid only under state/ or another explicitly state-owning folder.
```

Preferred shape:

```text id="asdt-fs-004-transitions-shape"
component_or_actor/
└── state/
    └── transitions/
```

### 10.3 Valid Uses

`transitions/` may exist for:

1. slot occupancy transitions,
2. container readiness transitions,
3. moderator reinitialization transitions,
4. round membership transitions,
5. dispatch eligibility transitions,
6. handoff failure/retry transitions if in scope.

### 10.4 Invalid Uses

`transitions/` must not be used as:

1. a generic algorithm folder,
2. a replacement for state ownership,
3. a location for unrelated workflow utilities,
4. a cross-domain orchestration folder,
5. a downstream lifecycle model.

---

## 11. `hosted_ports/` Subfolder Rules

### 11.1 Definition

`hosted_ports/` owns inbound or locally hosted interaction surfaces that the parent component exposes for other components or domains to call through approved contracts.

### 11.2 Placement Rule

```text id="asdt-fs-004-hosted-ports-rule"
hosted_ports/ belongs to the component that hosts the interaction surface.
```

### 11.3 Valid Placement

|          Record ID | Hosted Port Location                                            | Valid Meaning                                                        |
| -----------------: | --------------------------------------------------------------- | -------------------------------------------------------------------- |
| ASDT-FS-004-HP-001 | `log_level_api/policy_assignment/hosted_ports/`                 | Hosted policy assignment port for API-domain policy material         |
| ASDT-FS-004-HP-002 | `write_side/policy_assignment/hosted_ports/`                    | Hosted policy assignment port for write-side policy material         |
| ASDT-FS-004-HP-003 | `log_level_api/write_side_bridge/hosted_ports/`                 | Hosted bridge surface for write-side placement/reference interaction |
| ASDT-FS-004-HP-004 | `write_side/communications/log_level_api_feeding/hosted_ports/` | Write-side feeding boundary receiving surface                        |
| ASDT-FS-004-HP-005 | `write_side/communications/registry_delivery/hosted_ports/`     | Registry-delivery boundary surface if locally hosted                 |

### 11.4 Hosted Port Non-Meaning

A hosted port is not:

1. the full component,
2. the actor performing the behavior,
3. the carrier being transferred,
4. the downstream system,
5. the contract as abstract law,
6. the private implementation of the parent.

### 11.5 Hosted Port Anti-Collapse Rule

```text id="asdt-fs-004-hosted-port-anti-collapse"
A hosted port exposes an approved interaction surface.
It must not expose private internals.
```

---

## 12. `outbound_adapters/` Subfolder Rules

### 12.1 Definition

`outbound_adapters/` owns local outgoing adapter surfaces used by the parent component to emit, translate, or hand off interaction toward another boundary or component.

### 12.2 Placement Rule

```text id="asdt-fs-004-outbound-adapters-rule"
outbound_adapters/ belongs to the component that emits or translates the outgoing interaction.
```

### 12.3 Valid Placement

|          Record ID | Outbound Adapter Location                                            | Valid Meaning                           |
| -----------------: | -------------------------------------------------------------------- | --------------------------------------- |
| ASDT-FS-004-OA-001 | `ecosystem_governance/provider_adapters/`                            | Policy-provider adapter surfaces        |
| ASDT-FS-004-OA-002 | `log_level_api/write_side_bridge/outbound_adapters/`                 | API-to-write-side bridge adapters       |
| ASDT-FS-004-OA-003 | `write_side/dispatcher/outbound_adapters/`                           | Dispatcher outbound handoff adapters    |
| ASDT-FS-004-OA-004 | `write_side/communications/registry_delivery/outbound_adapters/`     | Registry-delivery adapter surfaces      |
| ASDT-FS-004-OA-005 | `write_side/communications/log_level_api_feeding/outbound_adapters/` | Boundary translation adapters if needed |

### 12.4 Adapter Non-Ownership Rule

```text id="asdt-fs-004-adapter-non-ownership"
An outbound adapter does not own the destination system.
```

Examples:

1. A registry-delivery adapter does not own registry internals.
2. A policy-provider adapter does not own consuming-domain assignment.
3. A write-side bridge adapter does not own slot internals.
4. A dispatcher adapter does not own downstream persistence.

---

## 13. `detail/` Subfolder Rules

### 13.1 Definition

`detail/` owns private implementation internals for its nearest parent folder.

### 13.2 Placement Rule

```text id="asdt-fs-004-detail-rule"
detail/ is private to its nearest semantic owner.
```

### 13.3 Valid Placement

|              Record ID | Detail Location                                       | Meaning                                |
| ---------------------: | ----------------------------------------------------- | -------------------------------------- |
| ASDT-FS-004-DETAIL-001 | `log_level_api/validator/detail/`                     | Validator-private internals            |
| ASDT-FS-004-DETAIL-002 | `log_level_api/envelope_assembler/detail/`            | Assembly-private internals             |
| ASDT-FS-004-DETAIL-003 | `write_side/slot/detail/`                             | Slot-private internals                 |
| ASDT-FS-004-DETAIL-004 | `write_side/slots_container/detail/`                  | Container-private internals            |
| ASDT-FS-004-DETAIL-005 | `write_side/round_manager/detail/`                    | Round-manager-private internals        |
| ASDT-FS-004-DETAIL-006 | `write_side/dispatcher/detail/`                       | Dispatcher-private internals           |
| ASDT-FS-004-DETAIL-007 | `write_side/communications/registry_delivery/detail/` | Boundary-private translation internals |

### 13.4 Forbidden Dependency Rule

```text id="asdt-fs-004-detail-forbidden-dep"
No external folder may depend on another folder’s detail/.
```

A dependency on `detail/` means one of the following is probably true:

1. the needed concept should be promoted to a public surface,
2. the needed concept should be a carrier,
3. the needed concept should be a hosted port,
4. the needed concept should be an outbound adapter,
5. the needed concept should be a shared semantic root,
6. the dependency is invalid.

### 13.5 Detail Anti-Collapse Rule

```text id="asdt-fs-004-detail-anti-collapse"
detail/ protects implementation freedom.
It must not become a hidden public API.
```

---

## 14. `policies/` Subfolder Rules

### 14.1 Definition

`policies/` may own local policy-facing material only when policy consumption or policy-governed behavior is local to the parent component.

### 14.2 Placement Rule

```text id="asdt-fs-004-policies-rule"
policies/ is valid only when the parent component locally consumes, applies,
or adapts policy-governed behavior.
```

### 14.3 Valid Placement

|           Record ID | Policies Location                                   | Valid Meaning                                                              |
| ------------------: | --------------------------------------------------- | -------------------------------------------------------------------------- |
| ASDT-FS-004-POL-001 | `log_level_api/validator/policies/`                 | Validator-local policy-bound validation rules if formalized                |
| ASDT-FS-004-POL-002 | `log_level_api/timestamp_stabilizer/policies/`      | Timestamp policy consumption if formalized                                 |
| ASDT-FS-004-POL-003 | `log_level_api/metadata_injector/policies/`         | Only if later formal contract allows policy hosting; otherwise discouraged |
| ASDT-FS-004-POL-004 | `write_side/policy_assignment/policies/`            | Write-side local policy assignment material                                |
| ASDT-FS-004-POL-005 | `write_side/dispatcher/policies/`                   | Dispatch policy constraints if formalized                                  |
| ASDT-FS-004-POL-006 | `write_side/slots_container_bundle_agent/policies/` | Scaling policy constraints if formalized                                   |

### 14.4 Policy Non-Ownership Rule

```text id="asdt-fs-004-policy-non-ownership"
A local policies/ folder does not own the external Policy Registry or Policy Source.
```

Policy source ownership remains external or ecosystem-governance-facing.

Local policy folders may own local interpretation or local consumption only when formally justified.

### 14.5 Policy Anti-Collapse Rule

```text id="asdt-fs-004-policy-anti-collapse"
Policy material is not policy execution.
Policy assignment is not policy source ownership.
```

---

## 15. `contracts/` Subfolder Rules

### 15.1 Definition

`contracts/` may own local contract representations only when the parent folder owns a local contract surface that is not better represented as a port, adapter, carrier, or state rule.

### 15.2 Placement Rule

```text id="asdt-fs-004-contracts-rule"
contracts/ is allowed only when the contract representation is local,
explicit, and not better placed as hosted_ports/, outbound_adapters/,
carriers/, or state/.
```

### 15.3 Preferred Alternatives

Before creating `contracts/`, consider whether the contract belongs in:

|               Record ID | Alternative Folder         | Use When                                         |
| ----------------------: | -------------------------- | ------------------------------------------------ |
| ASDT-FS-004-CON-ALT-001 | `hosted_ports/`            | The contract is an inbound interaction surface   |
| ASDT-FS-004-CON-ALT-002 | `outbound_adapters/`       | The contract is an outbound interaction surface  |
| ASDT-FS-004-CON-ALT-003 | `carriers/`                | The contract constrains transferred material     |
| ASDT-FS-004-CON-ALT-004 | `state/`                   | The contract constrains transitions or readiness |
| ASDT-FS-004-CON-ALT-005 | domain-level contract pack | The contract applies across multiple components  |

### 15.4 Contract Anti-Collapse Rule

```text id="asdt-fs-004-contracts-anti-collapse"
A contracts/ folder may represent contract artifacts.
It must not replace architectural contract law.
```

The architecture owns the law.

The folder may later host implementation-facing representations.

---

## 16. `views/` Subfolder Rules

### 16.1 Definition

`views/` owns local read-only projections or restricted surfaces that expose a safe subset of parent-owned information.

### 16.2 Placement Rule

```text id="asdt-fs-004-views-rule"
views/ is valid when a component must expose read-only information without exposing internals.
```

### 16.3 Valid Uses

`views/` may be appropriate for:

1. container readiness views,
2. slot occupancy views,
3. round membership views,
4. dispatch eligibility views,
5. bridge-safe placement views,
6. policy assignment views,
7. handoff evidence views.

### 16.4 View Anti-Collapse Rule

```text id="asdt-fs-004-view-anti-collapse"
A view exposes a safe projection.
It does not grant mutation authority or internal ownership.
```

---

## 17. `handles/` Subfolder Rules

### 17.1 Definition

`handles/` owns local reference, locator, or identity-like abstractions that allow another component to refer to something without owning its internals.

### 17.2 Placement Rule

```text id="asdt-fs-004-handles-rule"
handles/ is valid when a component must expose reference semantics without exposing internal structure.
```

### 17.3 Valid Uses

`handles/` may be appropriate for:

1. queue container identifiers,
2. slot references,
3. placement handles,
4. round membership handles,
5. handoff handles,
6. dispatch eligibility references,
7. bridge-safe references.

### 17.4 Handle Anti-Collapse Rule

```text id="asdt-fs-004-handle-anti-collapse"
A handle permits reference.
It does not transfer ownership.
```

A handle to a slot does not make the caller a slot owner.

A handle to a queue container does not make the caller a container owner.

A handoff handle does not make the assembler a downstream lifecycle owner.

---

## 18. Communication Boundary Subfolder Rules

### 18.1 Communication Boundary Shape

A communication boundary folder may use the following local shape:

```text id="asdt-fs-004-comm-shape"
communications/
└── boundary_name/
    ├── docs/
    ├── tests/
    ├── carriers/
    ├── hosted_ports/
    ├── outbound_adapters/
    ├── views/
    ├── handles/
    └── detail/
```

Only justified subfolders should appear.

### 18.2 `log_level_api_feeding/` Subfolder Rules

`write_side/communications/log_level_api_feeding/` may contain:

|           Record ID | Subfolder            | Valid Meaning                                                    |
| ------------------: | -------------------- | ---------------------------------------------------------------- |
| ASDT-FS-004-LAF-001 | `docs/`              | Feeding-boundary documentation                                   |
| ASDT-FS-004-LAF-002 | `tests/`             | Boundary isolation and feeding behavior tests                    |
| ASDT-FS-004-LAF-003 | `carriers/`          | Placement request/result carriers                                |
| ASDT-FS-004-LAF-004 | `hosted_ports/`      | Write-side feeding receiving surface                             |
| ASDT-FS-004-LAF-005 | `outbound_adapters/` | Optional outbound translation toward internal write-side surface |
| ASDT-FS-004-LAF-006 | `views/`             | Safe write-side readiness projections                            |
| ASDT-FS-004-LAF-007 | `handles/`           | Placement or container handles                                   |
| ASDT-FS-004-LAF-008 | `detail/`            | Boundary-private translation internals                           |

It must not contain:

1. slot private internals,
2. slots-container private internals,
3. bundle-agent scaling internals,
4. round-manager private state,
5. envelope assembler internals.

### 18.3 `registry_delivery/` Subfolder Rules

`write_side/communications/registry_delivery/` may contain:

|          Record ID | Subfolder            | Valid Meaning                                        |
| -----------------: | -------------------- | ---------------------------------------------------- |
| ASDT-FS-004-RD-001 | `docs/`              | Registry-facing boundary documentation               |
| ASDT-FS-004-RD-002 | `tests/`             | Registry-delivery boundary tests                     |
| ASDT-FS-004-RD-003 | `carriers/`          | Handoff material, evidence, acknowledgement carriers |
| ASDT-FS-004-RD-004 | `hosted_ports/`      | Locally hosted delivery boundary surface if required |
| ASDT-FS-004-RD-005 | `outbound_adapters/` | Dispatcher-to-registry delivery adapters             |
| ASDT-FS-004-RD-006 | `views/`             | Handoff-readiness or delivery status projections     |
| ASDT-FS-004-RD-007 | `handles/`           | Handoff handles or delivery references               |
| ASDT-FS-004-RD-008 | `detail/`            | Boundary-private translation internals               |

It must not contain:

1. downstream registry schema,
2. downstream storage lifecycle,
3. downstream query lifecycle,
4. downstream replay logic,
5. downstream indexing logic,
6. downstream mutation logic.

---

## 19. Component-Type-Specific Subfolder Profiles

### 19.1 Preparation Component Profile

Applies to:

1. `validator/`,
2. `timestamp_stabilizer/`,
3. `metadata_injector/`,
4. `envelope_assembler/`.

Allowed local subfolders:

```text id="asdt-fs-004-prep-profile"
docs/
tests/
carriers/
state/
policies/
contracts/
detail/
```

Not every preparation component should contain all of these.

### 19.2 Carrier Root Profile

Applies to:

1. `content/`,
2. `envelope/`,
3. shared carrier roots.

Allowed local subfolders:

```text id="asdt-fs-004-carrier-profile"
docs/
tests/
views/
handles/
detail/
```

`carriers/` under a carrier root should be used carefully, because the parent is already a carrier-oriented folder.

### 19.3 Runtime Component Profile

Applies to:

1. `slot/`,
2. `slots_container/`,
3. `waiting_list/`,
4. `slots_container_moderator/`,
5. `slots_container_bundle_agent/`,
6. `round_manager/`,
7. `reference_precalculator/`.

Allowed local subfolders:

```text id="asdt-fs-004-runtime-profile"
docs/
tests/
carriers/
state/
views/
handles/
policies/
contracts/
detail/
```

### 19.4 Dispatcher Profile

Applies to:

```text
write_side/dispatcher/
```

Allowed local subfolders:

```text id="asdt-fs-004-dispatcher-profile"
docs/
tests/
carriers/
state/
hosted_ports/
outbound_adapters/
views/
handles/
policies/
contracts/
detail/
```

Dispatcher subfolders must preserve dispatcher finality and must not absorb downstream registry internals.

### 19.5 Policy Assignment Component Profile

Applies to:

1. `log_level_api/policy_assignment/`,
2. `write_side/policy_assignment/`.

Allowed local subfolders:

```text id="asdt-fs-004-policy-assignment-profile"
docs/
tests/
carriers/
hosted_ports/
outbound_adapters/
policies/
contracts/
views/
detail/
```

Policy assignment must not become policy source ownership.

### 19.6 Communication Boundary Profile

Applies to folders under:

```text
write_side/communications/
```

Allowed local subfolders:

```text id="asdt-fs-004-communication-profile"
docs/
tests/
carriers/
hosted_ports/
outbound_adapters/
views/
handles/
contracts/
detail/
```

Communication boundaries expose approved abstractions, not internal runtime mechanics.

---

## 20. Forbidden Component Subfolders

### 20.1 Forbidden Generic Subfolders

The following generic folders are discouraged inside components unless explicitly justified:

|              Record ID | Folder        | Reason                                                                                  |
| ---------------------: | ------------- | --------------------------------------------------------------------------------------- |
| ASDT-FS-004-FORBID-001 | `utils/`      | Hides ownership and encourages unrelated helper accumulation                            |
| ASDT-FS-004-FORBID-002 | `helpers/`    | Usually duplicates `detail/` without privacy discipline                                 |
| ASDT-FS-004-FORBID-003 | `common/`     | Obscures the real shared semantic owner                                                 |
| ASDT-FS-004-FORBID-004 | `misc/`       | No clear semantic boundary                                                              |
| ASDT-FS-004-FORBID-005 | `impl/`       | Less precise than `detail/` and may leak as public implementation                       |
| ASDT-FS-004-FORBID-006 | `models/`     | Too generic; prefer `carriers/`, `state/`, `views/`, or domain-specific roots           |
| ASDT-FS-004-FORBID-007 | `services/`   | Too generic; prefer actor/component names                                               |
| ASDT-FS-004-FORBID-008 | `interfaces/` | Too generic; prefer `hosted_ports/`, `outbound_adapters/`, or `contracts/` if justified |
| ASDT-FS-004-FORBID-009 | `types/`      | Too generic unless scoped under a precise semantic root                                 |
| ASDT-FS-004-FORBID-010 | `data/`       | Does not distinguish carrier, state, fixture, policy, or view meaning                   |

### 20.2 Forbidden Subfolder Meaning

A subfolder must not be created to:

1. hide unresolved architecture,
2. group unrelated files,
3. avoid choosing an owner,
4. bypass dependency direction,
5. expose private internals,
6. duplicate a domain root,
7. encode downstream ownership,
8. create a generic utility dependency,
9. replace contract derivation,
10. replace component responsibility.

---

## 21. Public and Private Surface Rules

### 21.1 Public Surface Subfolders

The following subfolders may contribute to public or boundary-facing surfaces:

1. `hosted_ports/`,
2. `outbound_adapters/`,
3. `carriers/`,
4. `views/`,
5. `handles/`,
6. local `contracts/` where justified.

### 21.2 Private Surface Subfolders

The following subfolders are private or test-local:

1. `detail/`,
2. `tests/`,
3. `tests/fixtures/`,
4. internal `state/` unless explicitly exposed through views or handles,
5. local `policies/` unless explicitly exposed through policy assignment surfaces.

### 21.3 Surface Rule

```text id="asdt-fs-004-surface-rule"
Only approved public surfaces may be used across component boundaries.
```

Private subfolders must not become implicit dependency points.

---

## 22. Allowed Component Subfolder Dependency Direction

### 22.1 General Direction

Within a component, the preferred dependency direction is:

```text id="asdt-fs-004-internal-dep-direction"
carriers/
→ state/
→ hosted_ports/
→ outbound_adapters/
→ views/
→ handles/
→ detail/
→ parent public surface
```

This direction is not a mandatory include order.

It is a semantic dependency guide.

### 22.2 Documentation and Tests

`docs/` and `tests/` are special:

1. `docs/` may reference all parent-local concepts for explanation.
2. `tests/` may exercise parent-local public and test-approved internal surfaces.
3. neither `docs/` nor `tests/` define production ownership.

### 22.3 Detail Dependency

`detail/` may depend on parent-local concepts.

Parent public surfaces may use `detail/` internally.

External folders must not depend on `detail/`.

---

## 23. Component Subfolder Validation Questions

Before creating a subfolder inside a component, answer:

|           Record ID | Question                                                         | Required Answer   |
| ------------------: | ---------------------------------------------------------------- | ----------------- |
| ASDT-FS-004-VAL-001 | What exact local meaning does this subfolder own?                | Must be explicit  |
| ASDT-FS-004-VAL-002 | Why does this meaning belong under this parent?                  | Must be justified |
| ASDT-FS-004-VAL-003 | Is the subfolder one of the allowed subfolder classes?           | Must be yes       |
| ASDT-FS-004-VAL-004 | Is the subfolder being created from a template rather than need? | Must be no        |
| ASDT-FS-004-VAL-005 | Does the subfolder duplicate another owner’s meaning?            | Must be no        |
| ASDT-FS-004-VAL-006 | Does the subfolder expose private internals?                     | Must be no        |
| ASDT-FS-004-VAL-007 | Does the subfolder imply downstream ownership?                   | Must be no        |
| ASDT-FS-004-VAL-008 | Is `detail/` being accessed from outside?                        | Must be no        |
| ASDT-FS-004-VAL-009 | Is a port/adapter/carrier/view/handle more precise?              | Must be assessed  |
| ASDT-FS-004-VAL-010 | Does the subfolder need local docs or tests?                     | Must be assessed  |

---

## 24. Component Subfolder Freeze Rules

### 24.1 Freeze Preconditions

A component subfolder structure may be frozen only when:

1. the parent component’s ownership is declared,
2. the parent component’s non-ownership is declared,
3. all subfolders have justified meanings,
4. no generic subfolder is present without justification,
5. `detail/` is private,
6. cross-component dependencies use public surfaces,
7. local docs scope is clear,
8. local tests scope is clear,
9. carrier placement is narrow,
10. state placement follows behavior ownership,
11. ports and adapters are distinguished,
12. communication boundaries expose abstractions only.

### 24.2 Freeze Artifacts

The freeze should produce:

|              Record ID | Artifact                    | Purpose                                          |
| ---------------------: | --------------------------- | ------------------------------------------------ |
| ASDT-FS-004-FREEZE-001 | Component Subfolder Matrix  | Lists each component and its approved subfolders |
| ASDT-FS-004-FREEZE-002 | Subfolder Ownership Matrix  | Lists owned meaning per subfolder                |
| ASDT-FS-004-FREEZE-003 | Public Surface Matrix       | Lists approved cross-component surfaces          |
| ASDT-FS-004-FREEZE-004 | Private Surface Matrix      | Lists protected internals                        |
| ASDT-FS-004-FREEZE-005 | Local Docs Matrix           | Lists documentation scopes                       |
| ASDT-FS-004-FREEZE-006 | Local Tests Matrix          | Lists testing scopes                             |
| ASDT-FS-004-FREEZE-007 | Forbidden Subfolder Matrix  | Lists rejected generic or invalid subfolders     |
| ASDT-FS-004-FREEZE-008 | Subfolder Dependency Matrix | Lists allowed subfolder-level dependencies       |

---

## 25. Summary

This document defines the component subfolder rules for the Assembler System Digital Twin Filesystem.

The governing conclusions are:

1. component subfolders are optional, not template-mandated,
2. every subfolder must own a local semantic responsibility,
3. `docs/` documents the immediate parent scope,
4. `tests/` verifies the immediate parent scope,
5. `fixtures/` are test-only and must not become production material,
6. `carriers/` owns local carried structures,
7. `state/` owns local behavioral state and transitions,
8. `hosted_ports/` owns inbound/local interaction surfaces,
9. `outbound_adapters/` owns outgoing interaction surfaces,
10. `detail/` is private to the nearest owner,
11. `policies/` is valid only for local policy consumption or interpretation,
12. `contracts/` is valid only when a local contract representation is justified,
13. `views/` exposes safe read-only projections,
14. `handles/` exposes reference semantics without ownership transfer,
15. communication boundaries expose approved abstractions, not internals,
16. generic folders such as `utils/`, `helpers/`, `common/`, and `misc/` are discouraged,
17. final file inventory remains deferred.

The next document should define the domain-specific internal folder structures for:

```text
ecosystem_governance/
log_level_api/
write_side/
```

including their accepted first-level folders, subfolder profiles, dependency order, and forbidden placements.

```
```
