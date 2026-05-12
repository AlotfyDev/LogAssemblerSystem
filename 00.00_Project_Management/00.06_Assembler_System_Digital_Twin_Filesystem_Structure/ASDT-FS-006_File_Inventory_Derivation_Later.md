
# ASDT-FS-006 — File Inventory Derivation Rules

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-006-DOC-001 | Document Title | File Inventory Derivation Rules |
| ASDT-FS-006-DOC-002 | File Name | `ASDT-FS-006_File_Inventory_Derivation_Rules.md` |
| ASDT-FS-006-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-006-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-006-DOC-005 | Project | Assembler System |
| ASDT-FS-006-DOC-006 | Primary Language | English |
| ASDT-FS-006-DOC-007 | Scope Level | File inventory derivation rules, file naming doctrine, folder-to-file derivation, header inventory readiness |
| ASDT-FS-006-DOC-008 | Implementation Language Direction | C++17, header-only-first, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-006-DOC-009 | Status | Pre-Implementation File Inventory Doctrine |
| ASDT-FS-006-DOC-010 | File Inventory Status | Derivation rules defined; final inventory still pending |
| ASDT-FS-006-DOC-011 | Depends On | `ASDT-FS-000_Digital_Twin_Filesystem_Doctrine.md`, `ASDT-FS-001_Root_DDD_Domain_Folders.md`, `ASDT-FS-003_Folder_Dependency_And_Ownership_Rules.md`, `ASDT-FS-004_Component_Subfolder_Rules.md`, `ASDT-FS-005_Current_Folder_Structure_Draft_V1.md` |
| ASDT-FS-006-DOC-012 | Primary Rule | Files must derive from accepted folder ownership; files must not reshape folder ownership |
| ASDT-FS-006-DOC-013 | Governing Principle | A file is a local implementation or documentation artifact inside a declared semantic owner |
| ASDT-FS-006-DOC-014 | Excluded From This Document | Final `.hpp` list, final class declarations, final function signatures, final namespace declarations, CMake target definitions, final include graph |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines how file inventories must be derived from the accepted Assembler System Digital Twin Filesystem structure.

It answers the question:

```text
After folder ownership is stabilized, how should future files be derived,
named, placed, grouped, and validated without allowing file names, class names,
or implementation convenience to reshape the architecture?
````

This document does not freeze the final `.hpp` inventory.

It defines the rules that a later file inventory pack must follow.

### 2.2 Why This Document Exists

The previous filesystem documents intentionally deferred file-level decisions.

That deferral protected the architecture from code-first design.

However, once folder ownership begins to stabilize, the project needs a controlled method for deriving files from folders.

Without this document, file creation may drift into:

1. generic technical names,
2. premature class names,
3. duplicate ownership,
4. hidden cross-domain dependencies,
5. public exposure of private implementation,
6. ungoverned template abstractions,
7. arbitrary header placement,
8. incorrect mapping between components and files.

This document prevents those failures.

### 2.3 What This Document Does

This document defines:

1. file derivation principles,
2. file inventory grain,
3. file naming rules,
4. header-only-first rules,
5. folder-to-file derivation rules,
6. public/private file placement rules,
7. `detail/` file rules,
8. `carriers/` file rules,
9. `state/` file rules,
10. `hosted_ports/` file rules,
11. `outbound_adapters/` file rules,
12. `views/` file rules,
13. `handles/` file rules,
14. `contracts/` file rules,
15. `policies/` file rules,
16. docs and tests file derivation rules,
17. forbidden file patterns,
18. file inventory validation questions.

### 2.4 What This Document Does Not Do

This document does not define:

1. final `.hpp` files,
2. final class names,
3. final template signatures,
4. final namespace tree,
5. final include graph,
6. final CMake targets,
7. final test file names,
8. final benchmark files,
9. final examples,
10. final runtime algorithms.

Those belong to later implementation derivation documents.

---

## 3. File Derivation Doctrine

### 3.1 Primary Rule

```text id="asdt-fs-006-primary-rule"
Files must derive from accepted folder ownership.
Files must not reshape folder ownership.
```

A file is not a new architectural owner.

A file is an artifact placed under a semantic owner.

### 3.2 File Derivation Order

The accepted derivation order is:

```text id="asdt-fs-006-derivation-order"
System meaning
→ semantic domain
→ component or actor folder
→ local subfolder
→ file role
→ file name
→ C++ declaration
→ include relationship
```

The inverse order is forbidden.

### 3.3 Forbidden Derivation Order

The following order is invalid:

```text id="asdt-fs-006-forbidden-order"
class name
→ file name
→ folder
→ package
→ domain meaning
```

This would make implementation convenience the source of architecture.

### 3.4 File Inventory Meaning

A file inventory is a controlled list of files that may exist inside a folder because the folder already owns the meaning those files express.

A file inventory must answer:

1. Which folder owns this file?
2. What semantic role does the file perform?
3. Is the file public, private, local, test-only, documentation-only, or generated?
4. Which contract, carrier, state model, port, adapter, view, handle, policy, or detail does it represent?
5. What must not depend on it?
6. What may include it?
7. What later class, trait, template, or function may derive from it?

---

## 4. File Inventory Record Model

### 4.1 Required Record Fields

Each future file inventory row should use the following model.

|            Record ID | Field                   | Meaning                                                                                                               |
| -------------------: | ----------------------- | --------------------------------------------------------------------------------------------------------------------- |
| ASDT-FS-006-FIRM-001 | File Inventory ID       | Stable record ID for the proposed file                                                                                |
| ASDT-FS-006-FIRM-002 | Folder Path             | Canonical folder path that owns the file                                                                              |
| ASDT-FS-006-FIRM-003 | File Name               | Proposed file name                                                                                                    |
| ASDT-FS-006-FIRM-004 | File Extension          | `.hpp`, `.ipp`, `.md`, `.json`, `.csv`, `.cpp`, `.test.hpp`, or other approved extension                              |
| ASDT-FS-006-FIRM-005 | File Role               | carrier, state, transition, guard, port, adapter, view, handle, contract, policy, detail, doc, test, fixture, example |
| ASDT-FS-006-FIRM-006 | Visibility              | public_surface, local_surface, private_detail, test_only, doc_only, generated                                         |
| ASDT-FS-006-FIRM-007 | Ownership Statement     | What semantic meaning the file expresses                                                                              |
| ASDT-FS-006-FIRM-008 | Derivation Source       | Folder, component, contract, responsibility, glossary term, or architecture rule that justifies the file              |
| ASDT-FS-006-FIRM-009 | Allowed Dependents      | Which folders or files may depend on this file                                                                        |
| ASDT-FS-006-FIRM-010 | Forbidden Dependents    | Which folders or categories must not depend on this file                                                              |
| ASDT-FS-006-FIRM-011 | Public Include Status   | include_allowed / local_only / private_only / test_only / not_applicable                                              |
| ASDT-FS-006-FIRM-012 | Implementation Maturity | candidate / draft / accepted / frozen / deprecated                                                                    |
| ASDT-FS-006-FIRM-013 | Notes                   | Clarifications, unresolved questions, or validation concerns                                                          |

### 4.2 Minimal File Inventory Row

A minimal file inventory row must include at least:

1. folder path,
2. file name,
3. file role,
4. visibility,
5. ownership statement,
6. derivation source.

### 4.3 No-Orphan File Rule

```text id="asdt-fs-006-no-orphan-file-rule"
No file may exist in the inventory without a declared folder owner and derivation source.
```

A file that cannot name its semantic owner is not ready for inclusion.

---

## 5. Approved File Classes

### 5.1 File Class Table

|          Record ID | File Class                     | Typical Extension                                                  | Meaning                                                                     |
| -----------------: | ------------------------------ | ------------------------------------------------------------------ | --------------------------------------------------------------------------- |
| ASDT-FS-006-FC-001 | Public Header                  | `.hpp`                                                             | Public or approved local C++ declaration surface                            |
| ASDT-FS-006-FC-002 | Private Detail Header          | `.hpp`                                                             | Private implementation detail under `detail/`                               |
| ASDT-FS-006-FC-003 | Template Implementation Header | `.ipp` or `.hpp`                                                   | Inline template implementation where separate representation is justified   |
| ASDT-FS-006-FC-004 | Documentation File             | `.md`                                                              | Local documentation attached to folder ownership                            |
| ASDT-FS-006-FC-005 | Test File                      | `.test.hpp`, `.test.cpp`, or project-approved pattern              | Local verification artifact                                                 |
| ASDT-FS-006-FC-006 | Fixture File                   | `.json`, `.csv`, `.txt`, `.md`, or project-approved fixture format | Test or example input/output material                                       |
| ASDT-FS-006-FC-007 | Example File                   | `.hpp`, `.cpp`, `.md`, or project-approved pattern                 | Demonstration of approved usage                                             |
| ASDT-FS-006-FC-008 | Generated File                 | project-approved generated extension                               | Derived artifact, never canonical meaning source                            |
| ASDT-FS-006-FC-009 | Configuration Candidate        | `.json`, `.yaml`, `.toml`, or project-approved format              | Configuration or policy fixture candidate, not runtime authority by default |
| ASDT-FS-006-FC-010 | Index File                     | `README.md`, `index.md`, or approved equivalent                    | Human navigation aid for a folder                                           |

### 5.2 Header-Only-First Rule

```text id="asdt-fs-006-header-only-first-rule"
The default implementation posture is header-only-first where appropriate,
but header-only placement must not force unrelated responsibilities into one file.
```

Header-only-first does not mean:

1. one giant header,
2. no folder-local separation,
3. no private detail files,
4. no test fixtures,
5. no future `.cpp` option where justified,
6. no implementation boundary discipline.

### 5.3 File Extension Discipline

A file extension does not define architectural meaning.

For example:

1. `.hpp` does not automatically mean public.
2. `.ipp` does not automatically mean private.
3. `.md` does not automatically mean repository-level documentation.
4. `.json` does not automatically mean schema authority.
5. `.cpp` does not automatically mean implementation ownership.

Meaning is determined by folder ownership and file role.

---

## 6. File Naming Doctrine

### 6.1 Primary Naming Rule

```text id="asdt-fs-006-file-naming-rule"
A file name should identify the narrow semantic artifact it represents.
```

A file name must not hide ownership ambiguity.

### 6.2 Naming Style

The current recommended naming style is:

```text
lower_snake_case.hpp
```

Examples:

```text
log_level_envelope.hpp
dispatch_eligibility_state.hpp
queue_container_identifier.hpp
handoff_evidence.hpp
```

This style is recommended for file names only.

It does not decide final C++ type names.

### 6.3 C++ Type Name Separation

```text id="asdt-fs-006-type-name-separation-rule"
A file name may suggest a C++ type, but it does not freeze the final C++ type name.
```

For example:

```text
log_level_envelope.hpp
```

may later contain:

```text
LogLevelEnvelope
```

or an approved template/trait representation.

The file name does not freeze class design.

### 6.4 Forbidden Naming Patterns

The following file names are discouraged unless explicitly justified:

```text id="asdt-fs-006-forbidden-file-names"
utils.hpp
helpers.hpp
common.hpp
misc.hpp
types.hpp
models.hpp
interfaces.hpp
impl.hpp
base.hpp
manager.hpp
service.hpp
data.hpp
```

They usually hide unresolved ownership.

### 6.5 Replacement Guidance

| Discouraged Name | Preferred Direction                                                    |
| ---------------- | ---------------------------------------------------------------------- |
| `utils.hpp`      | Named local `detail/` helper, view, handle, or specific algorithm file |
| `helpers.hpp`    | Specific semantic helper under local `detail/`                         |
| `common.hpp`     | Shared semantic owner with declared scope                              |
| `types.hpp`      | Specific carrier, state, view, handle, or contract file                |
| `models.hpp`     | `carriers/`, `state/`, `views/`, or domain-specific artifact           |
| `interfaces.hpp` | `hosted_ports/`, `outbound_adapters/`, or `contracts/`                 |
| `impl.hpp`       | `detail/<specific_name>.hpp`                                           |
| `manager.hpp`    | Specific actor or coordinator file                                     |
| `service.hpp`    | Specific component name                                                |
| `data.hpp`       | carrier, state, fixture, policy, or view file                          |

---

## 7. Folder-to-File Derivation Rules

### 7.1 Domain-Level Files

Root domain folders may contain only domain-level navigation or domain-level governance files by default.

Allowed candidates:

```text
README.md
domain_overview.md
domain_ownership.md
domain_dependency_notes.md
```

Root domain folders should not directly contain broad implementation headers unless the domain owns a real public façade.

### 7.2 Component-Level Files

A component folder may contain files only when the component owns a real semantic responsibility.

Allowed file roles include:

1. component façade,
2. local type bridge,
3. ownership README,
4. local documentation,
5. local tests,
6. local subfolder artifacts.

A component folder should not become a dumping ground for all local files.

### 7.3 Subfolder-Level Files

A subfolder derives files according to its declared role.

Examples:

```text
carriers/           → carrier object headers
state/              → state model headers
state/transitions/  → transition rule headers
state/guards/       → guard condition headers
hosted_ports/       → inbound contract surface headers
outbound_adapters/  → outbound adapter surface headers
views/              → read-only or projection surface headers
handles/            → safe reference or token headers
contracts/          → contract representation candidates
policies/           → local policy material or policy-binding candidates
detail/             → private implementation details
docs/               → local documentation
tests/              → local verification artifacts
fixtures/           → local test/example material
```

### 7.4 Parent-Child Meaning Rule

```text id="asdt-fs-006-parent-child-file-rule"
A file inside a subfolder inherits its semantic boundary from the subfolder
and its nearest component owner.
```

For example:

```text
write_side/dispatcher/state/dispatch_eligibility_state.hpp
```

means:

```text
dispatcher-owned dispatch eligibility state
```

It does not mean:

```text
all write-side state
```

or:

```text
downstream registry delivery state
```

---

## 8. Public and Private Surface Rules

### 8.1 Public Surface Candidate Files

Files may be public surface candidates only when placed under one of the approved surface folders:

1. `hosted_ports/`,
2. `outbound_adapters/`,
3. `carriers/`,
4. `views/`,
5. `handles/`,
6. justified `contracts/`.

### 8.2 Private Detail Files

Files under `detail/` are private by default.

```text id="asdt-fs-006-detail-private-rule"
No external folder may depend on another folder’s `detail/` files.
```

The only allowed dependents of a `detail/` file are:

1. files in the same `detail/` folder,
2. files in the nearest owning component,
3. local tests for that component, where explicitly allowed.

### 8.3 State Privacy Rule

State files are local by default unless explicitly exposed through approved views or handles.

A file under:

```text
state/
state/transitions/
state/guards/
```

must not be included directly across domain boundaries.

### 8.4 View and Handle Exposure Rule

If another component needs to inspect or reference local state, the owning component should expose:

1. a `views/` file for read-only projection,
2. a `handles/` file for safe reference,
3. a `hosted_ports/` file for controlled interaction.

It must not expose private `state/` or `detail/` files directly.

---

## 9. Role-Specific File Rules

### 9.1 `carriers/` Files

A `carriers/` file represents a carried object, transfer material, prepared artifact, or local message-like object within the owning component boundary.

It may define:

1. carrier identity,
2. payload shape,
3. move-only or immutable carrier semantics,
4. validation hooks,
5. handoff material shape,
6. local transfer object shape.

It must not define:

1. actor behavior,
2. dispatcher behavior,
3. storage lifecycle,
4. downstream registry internals,
5. broad runtime algorithm ownership.

### 9.2 `state/` Files

A `state/` file represents local state owned by the component.

It may define:

1. state enum candidates,
2. state snapshot candidates,
3. readiness states,
4. lifecycle states internal to the component,
5. state transition input/output types.

It must not define:

1. global system lifecycle,
2. downstream record lifecycle,
3. unrelated component state,
4. broad storage/query state.

### 9.3 `state/transitions/` Files

A transition file represents a local transition rule.

It may define:

1. transition preconditions,
2. transition result types,
3. transition validation candidates,
4. transition trace records.

It must not define unrelated runtime scheduling.

### 9.4 `state/guards/` Files

A guard file represents a local guard condition.

It may define:

1. guard predicates,
2. eligibility checks,
3. readiness checks,
4. local validation checks.

It must not become a global validation engine unless a later contract derives that role.

### 9.5 `hosted_ports/` Files

A hosted port file represents an inbound surface owned by the component.

It may define:

1. input contract surface,
2. request carrier shape,
3. accepted caller expectations,
4. local admission semantics.

It must not define:

1. external actor ownership,
2. caller implementation,
3. downstream registry internals,
4. private state mutation outside the owner.

### 9.6 `outbound_adapters/` Files

An outbound adapter file represents an outward-facing interaction surface from the owner toward another boundary or system.

It may define:

1. adapter contract candidate,
2. outbound material shape,
3. outbound transformation candidate,
4. handoff adapter surface.

It must not define the external system itself.

### 9.7 `views/` Files

A view file represents read-only or projection-oriented access to owned state, carriers, or readiness.

It may define:

1. read-only projection,
2. status view,
3. diagnostic view,
4. eligibility view.

It must not provide mutation authority.

### 9.8 `handles/` Files

A handle file represents a safe reference, token, ID, or locator.

It may define:

1. identifier wrapper,
2. safe reference token,
3. queue/container locator,
4. slot handle,
5. envelope handle,
6. dispatch handle.

It must not become lifecycle ownership.

### 9.9 `contracts/` Files

A contract file represents an implementation-facing contract candidate.

It may define:

1. trait candidate,
2. static contract candidate,
3. concept-like pattern candidate,
4. validation surface candidate,
5. CRTP-compatible base candidate.

It must not pretend that a C++ interface is the original contract meaning.

The contract meaning remains architectural first.

### 9.10 `policies/` Files

A policy file represents local policy material, policy binding, or policy-consumption rules where justified.

It may define:

1. local policy binding candidate,
2. policy-consumption rules,
3. policy assignment material,
4. policy fixture for tests.

It must not own external policy source lifecycle.

### 9.11 `detail/` Files

A detail file represents private implementation support.

It may define:

1. local helper implementation,
2. private algorithm fragment,
3. private storage shape,
4. private template helper,
5. local implementation adapter.

It must not be included by other components.

It must not become the hidden public API.

---

## 10. Documentation File Rules

### 10.1 Local Documentation Rule

```text id="asdt-fs-006-local-doc-rule"
Documentation files must live as close as possible to the semantic owner they explain.
```

For example:

```text
write_side/dispatcher/docs/handoff_boundary.md
```

is preferred over a generic repository-level document if the meaning is dispatcher-local.

### 10.2 Allowed Local Documentation Files

Allowed documentation file candidates include:

```text
README.md
ownership.md
dependency_notes.md
anti_collapse_notes.md
contract_notes.md
state_model.md
port_surface.md
adapter_surface.md
test_strategy.md
```

### 10.3 Repository-Level Documentation Rule

Repository-level `docs/` may summarize or cross-reference local documentation.

It must not replace local docs owned by components.

---

## 11. Test File Rules

### 11.1 Local Test Rule

```text id="asdt-fs-006-local-test-rule"
Tests should live close to the folder whose behavior, contract, carrier, state,
or boundary they verify.
```

### 11.2 Test Ownership

A test file must declare the artifact it verifies.

A test file may verify:

1. carrier validity,
2. state transition correctness,
3. guard behavior,
4. contract conformance,
5. port admission behavior,
6. adapter output shape,
7. dispatcher eligibility,
8. anti-collapse constraints,
9. boundary non-ownership rules.

### 11.3 Fixture Rule

Fixtures belong under the nearest relevant `tests/fixtures/` folder where possible.

A fixture must not become canonical runtime data.

### 11.4 Test Naming Recommendation

Recommended test naming style:

```text
<artifact_name>_test.cpp
<artifact_name>_contract_test.cpp
<artifact_name>_state_test.cpp
<artifact_name>_guard_test.cpp
<artifact_name>_adapter_test.cpp
```

This is a recommendation, not a final test framework decision.

---

## 12. Candidate File Derivation Examples

### 12.1 `log_level_api/envelope/`

Candidate files:

```text
log_level_api/envelope/
├── README.md
├── docs/
│   └── envelope_carrier_semantics.md
├── tests/
│   └── log_level_envelope_contract_test.cpp
├── views/
│   └── log_level_envelope_view.hpp
├── handles/
│   └── log_level_envelope_handle.hpp
└── detail/
    └── envelope_storage_detail.hpp
```

Notes:

1. `log_level_envelope_view.hpp` may expose read-only projection.
2. `log_level_envelope_handle.hpp` may expose safe reference semantics.
3. `envelope_storage_detail.hpp` remains private.
4. Envelope assembly behavior belongs under `envelope_assembler/`, not here.

### 12.2 `log_level_api/envelope_assembler/`

Candidate files:

```text
log_level_api/envelope_assembler/
├── README.md
├── docs/
│   └── assembly_sequence.md
├── tests/
│   └── envelope_assembler_contract_test.cpp
├── carriers/
│   └── assembly_result.hpp
├── state/
│   └── assembly_state.hpp
├── contracts/
│   └── envelope_assembly_contract.hpp
└── detail/
    └── assembly_pipeline_detail.hpp
```

Notes:

1. This folder owns assembly behavior.
2. It may produce `Log Level Envelope`.
3. It must not be confused with the envelope carrier itself.

### 12.3 `write_side/slot/`

Candidate files:

```text
write_side/slot/
├── README.md
├── docs/
│   └── slot_occupancy_model.md
├── tests/
│   └── slot_occupancy_state_test.cpp
├── carriers/
│   └── slot_occupancy_record.hpp
├── state/
│   ├── slot_lifecycle_state.hpp
│   ├── transitions/
│   │   └── occupy_slot_transition.hpp
│   └── guards/
│       └── slot_available_guard.hpp
├── views/
│   └── slot_view.hpp
├── handles/
│   └── slot_handle.hpp
├── contracts/
│   └── slot_occupancy_contract.hpp
└── detail/
    └── slot_storage_detail.hpp
```

Notes:

1. Slot files own slot semantics.
2. They do not own queue-container topology.
3. They do not own envelope lifecycle beyond occupancy semantics.

### 12.4 `write_side/slots_container/`

Candidate files:

```text
write_side/slots_container/
├── README.md
├── docs/
│   └── queue_container_structure.md
├── tests/
│   └── queue_container_contract_test.cpp
├── carriers/
│   └── queue_container_snapshot.hpp
├── state/
│   ├── queue_container_state.hpp
│   ├── transitions/
│   │   └── place_envelope_transition.hpp
│   └── guards/
│       └── queue_container_capacity_guard.hpp
├── views/
│   └── queue_container_view.hpp
├── handles/
│   └── queue_container_identifier.hpp
├── contracts/
│   └── queue_container_contract.hpp
└── detail/
    └── queue_container_storage_detail.hpp
```

Notes:

1. Queue container files must preserve Queue = Container.
2. They must not implement message broker semantics.
3. They own container structure, not downstream lifecycle.

### 12.5 `write_side/dispatcher/`

Candidate files:

```text
write_side/dispatcher/
├── README.md
├── docs/
│   ├── dispatcher_finality.md
│   └── handoff_boundary.md
├── tests/
│   └── dispatcher_handoff_contract_test.cpp
├── carriers/
│   └── dispatch_material.hpp
├── state/
│   ├── dispatch_eligibility_state.hpp
│   ├── transitions/
│   │   └── mark_dispatch_ready_transition.hpp
│   └── guards/
│       └── dispatch_eligibility_guard.hpp
├── hosted_ports/
│   └── dispatcher_admission_port.hpp
├── outbound_adapters/
│   └── registry_delivery_adapter.hpp
├── views/
│   └── dispatch_readiness_view.hpp
├── handles/
│   └── dispatch_handle.hpp
├── policies/
│   └── dispatch_policy_binding.hpp
├── contracts/
│   └── dispatcher_handoff_contract.hpp
└── detail/
    └── dispatcher_pipeline_detail.hpp
```

Notes:

1. Dispatcher files must preserve dispatcher finality.
2. Registry delivery adapter must not own downstream registry internals.
3. Handoff evidence is not proof of downstream persistence.

### 12.6 `write_side/communications/registry_delivery/`

Candidate files:

```text
write_side/communications/registry_delivery/
├── README.md
├── docs/
│   └── registry_delivery_boundary.md
├── tests/
│   └── registry_delivery_boundary_test.cpp
├── carriers/
│   ├── handoff_material.hpp
│   └── handoff_evidence.hpp
├── hosted_ports/
│   └── registry_delivery_port.hpp
├── outbound_adapters/
│   └── downstream_registry_adapter.hpp
├── views/
│   └── handoff_readiness_view.hpp
├── handles/
│   └── handoff_handle.hpp
├── contracts/
│   └── registry_delivery_contract.hpp
└── detail/
    └── registry_delivery_detail.hpp
```

Notes:

1. This folder owns registry-facing delivery boundary files.
2. It does not own registry implementation.
3. It does not own storage, query, replay, mutation, or indexing lifecycle.

---

## 13. Include Dependency Rules

### 13.1 Include Direction Rule

```text id="asdt-fs-006-include-direction-rule"
Include dependencies must follow approved semantic dependency direction.
```

A file may include:

1. files from its own folder,
2. approved public surface files from dependency folders,
3. approved carrier, view, handle, port, adapter, or contract files,
4. local `detail/` only from within the same owner.

A file must not include:

1. another component’s `detail/`,
2. downstream registry internals,
3. unrelated state internals,
4. test files,
5. fixtures as production dependencies,
6. generated files as canonical sources.

### 13.2 Public Include Rule

Public headers must not expose private detail types in their public declarations.

### 13.3 Detail Include Rule

Private detail files may include public files from their owner and dependencies.

Public files must not depend on private detail files unless the detail is implementation-only and not visible in the public surface.

### 13.4 Test Include Rule

Tests may include private detail files only when the test is local to the owning component and the project explicitly allows white-box verification.

---

## 14. File Inventory Validation Questions

Before adding a file to a future inventory, reviewers should answer:

|           Record ID | Question                                                           | Required Direction |
| ------------------: | ------------------------------------------------------------------ | ------------------ |
| ASDT-FS-006-VAL-001 | Does the file have a declared folder owner?                        | Yes                |
| ASDT-FS-006-VAL-002 | Does the file derive from accepted folder ownership?               | Yes                |
| ASDT-FS-006-VAL-003 | Is the file role explicit?                                         | Yes                |
| ASDT-FS-006-VAL-004 | Is the file visibility explicit?                                   | Yes                |
| ASDT-FS-006-VAL-005 | Does the file avoid generic naming?                                | Yes                |
| ASDT-FS-006-VAL-006 | Does the file avoid creating a new architectural owner?            | Yes                |
| ASDT-FS-006-VAL-007 | Does the file avoid exposing another folder’s `detail/`?           | Yes                |
| ASDT-FS-006-VAL-008 | Does the file preserve downstream non-ownership?                   | Yes                |
| ASDT-FS-006-VAL-009 | Does the file preserve queue-as-container where relevant?          | Yes                |
| ASDT-FS-006-VAL-010 | Does the file preserve actor/object distinction where relevant?    | Yes                |
| ASDT-FS-006-VAL-011 | Does the file avoid freezing class design prematurely?             | Yes                |
| ASDT-FS-006-VAL-012 | Does the file avoid becoming a generic `utils` or `common` bucket? | Yes                |
| ASDT-FS-006-VAL-013 | Does the file have allowed include dependents?                     | Yes                |
| ASDT-FS-006-VAL-014 | Does the file have forbidden dependents where needed?              | Yes                |
| ASDT-FS-006-VAL-015 | Does the file preserve local docs/tests ownership?                 | Yes                |

---

## 15. Forbidden File Patterns

### 15.1 Generic Catch-All Files

The following patterns are forbidden unless explicitly justified:

```text
utils.hpp
common.hpp
helpers.hpp
misc.hpp
types.hpp
models.hpp
data.hpp
interfaces.hpp
impl.hpp
all.hpp
everything.hpp
global.hpp
```

### 15.2 Cross-Domain Shortcut Files

The following are invalid by default:

```text
write_side/log_level_api_internals.hpp
dispatcher/registry_internals.hpp
slot/envelope_assembler_detail.hpp
ecosystem_governance/write_side_runtime.hpp
```

They suggest illegal dependency shortcuts.

### 15.3 Hidden Authority Files

A file name must not imply authority the folder does not own.

Invalid examples:

```text
registry_storage_owner.hpp
downstream_query_manager.hpp
global_lifecycle_controller.hpp
message_broker.hpp
logging_system_manager.hpp
```

These violate assembler scope.

### 15.4 Premature Implementation Files

The following are discouraged before contracts and responsibility chains justify them:

```text
processor.hpp
manager.hpp
service.hpp
engine.hpp
runtime.hpp
controller.hpp
factory.hpp
```

They may become valid later only with a precise semantic owner and derivation source.

---

## 16. File Inventory Freeze Readiness

### 16.1 Freeze Status

This document does not freeze the file inventory.

It defines the freeze requirements.

### 16.2 Freeze Preconditions

A file inventory may be frozen only when:

1. the folder structure is accepted,
2. every proposed file has a folder owner,
3. every proposed file has a role,
4. every proposed file has a visibility classification,
5. public/private include rules are defined,
6. local docs and tests are placed near owners,
7. no generic catch-all files remain,
8. no downstream authority leakage appears,
9. no file bypasses folder ownership,
10. no class name or implementation convenience reshapes the architecture.

### 16.3 Freeze Artifacts

A future file inventory freeze should produce:

|              Record ID | Freeze Artifact                | Purpose                                                           |
| ---------------------: | ------------------------------ | ----------------------------------------------------------------- |
| ASDT-FS-006-FREEZE-001 | File Inventory Matrix          | Complete list of accepted files                                   |
| ASDT-FS-006-FREEZE-002 | File Ownership Matrix          | File-to-folder ownership mapping                                  |
| ASDT-FS-006-FREEZE-003 | File Role Matrix               | File-to-role classification                                       |
| ASDT-FS-006-FREEZE-004 | Visibility Matrix              | Public/local/private/test/doc classification                      |
| ASDT-FS-006-FREEZE-005 | Include Permission Matrix      | Allowed include relationships                                     |
| ASDT-FS-006-FREEZE-006 | Forbidden Include Matrix       | Forbidden include relationships                                   |
| ASDT-FS-006-FREEZE-007 | Test Mapping Matrix            | Test-to-artifact mapping                                          |
| ASDT-FS-006-FREEZE-008 | Documentation Mapping Matrix   | Doc-to-folder and doc-to-file mapping                             |
| ASDT-FS-006-FREEZE-009 | Generic File Rejection Matrix  | Rejected catch-all or ambiguous files                             |
| ASDT-FS-006-FREEZE-010 | Deferred Implementation Notice | Confirms class/function/template details remain later derivations |

---

## 17. Recommended Next Document

The next strongest document is:

```text id="asdt-fs-006-next-doc"
ASDT-FS-007_File_Inventory_Draft_V1.md
```

That document should apply these rules to produce the first candidate file inventory.

It should not yet define final C++ classes or functions.

It should list candidate files per folder using the file inventory record model.

---

## 18. Summary

This document defines the rules for deriving file inventories from the Assembler System Digital Twin Filesystem.

The core conclusions are:

1. files derive from folder ownership,
2. file names do not define architecture,
3. file names do not freeze C++ class names,
4. header-only-first is a posture, not a license for giant headers,
5. `detail/` remains private,
6. public surfaces must be explicit,
7. carriers, state, ports, adapters, views, handles, contracts, policies, docs, and tests each have distinct file roles,
8. generic catch-all files are discouraged,
9. downstream authority must not appear in file inventory,
10. final file inventory remains a later controlled draft.

The next document should be the first concrete file list:

```text
ASDT-FS-007_File_Inventory_Draft_V1.md
```

```
```
