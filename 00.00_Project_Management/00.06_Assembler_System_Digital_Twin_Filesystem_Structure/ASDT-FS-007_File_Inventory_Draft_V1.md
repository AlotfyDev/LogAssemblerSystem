
# ASDT-FS-007 — File Inventory Draft V1

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| ASDT-FS-007-DOC-001 | Document Title | File Inventory Draft V1 |
| ASDT-FS-007-DOC-002 | File Name | `ASDT-FS-007_File_Inventory_Draft_V1.md` |
| ASDT-FS-007-DOC-003 | Formal Version | Formal Draft V1 |
| ASDT-FS-007-DOC-004 | Documentation Pack | Assembler System Digital Twin Filesystem Structure Pack |
| ASDT-FS-007-DOC-005 | Project | Assembler System |
| ASDT-FS-007-DOC-006 | Primary Language | English |
| ASDT-FS-007-DOC-007 | Scope Level | Candidate file inventory derived from accepted folder structure |
| ASDT-FS-007-DOC-008 | Implementation Direction | C++17, header-only-first where appropriate, templates, traits, CRTP-compatible abstraction layers |
| ASDT-FS-007-DOC-009 | Status | Candidate File Inventory Draft |
| ASDT-FS-007-DOC-010 | File Inventory Status | Candidate; not frozen |
| ASDT-FS-007-DOC-011 | Depends On | `ASDT-FS-000`, `ASDT-FS-001`, `ASDT-FS-003`, `ASDT-FS-004`, `ASDT-FS-005`, `ASDT-FS-006` |
| ASDT-FS-007-DOC-012 | Primary Rule | Every candidate file must derive from a declared folder owner |
| ASDT-FS-007-DOC-013 | Validation Target | `ASDT-FS-008_File_Inventory_Validation_Matrix.md` |
| ASDT-FS-007-DOC-014 | Cutover Target | `ASDT-FS-009_Implementation_Readiness_Cutover.md` |
| ASDT-FS-007-DOC-015 | Excluded From This Document | Final class declarations, final function signatures, final include graph, final namespace tree, final CMake targets, final implementation code |

---

## 2. Document Purpose

### 2.1 Purpose Statement

This document defines the first candidate file inventory for the Assembler System Digital Twin Filesystem.

It converts the current accepted folder draft into candidate files.

It answers the question:

```text
Given the current folder structure, which files are reasonable candidates
inside each folder, what does each file represent, who owns it, and what
must not depend on it?
````

### 2.2 Draft Boundary

This document does not freeze implementation.

A candidate file in this document means:

```text
This file is architecturally plausible under the current folder ownership model.
```

It does not mean:

```text
This file must be created immediately.
```

It also does not mean:

```text
The final C++ class, template, trait, namespace, include graph, or build target
is now frozen.
```

### 2.3 Inventory Method

This inventory is derived using the following chain:

```text
folder ownership
→ local semantic role
→ candidate file
→ file role
→ visibility
→ dependency permission
→ later validation
```

The reverse direction is forbidden.

---

## 3. Candidate File Record Model

Each candidate file is described using the following model.

|            Record ID | Field             | Meaning                                                                                             |
| -------------------: | ----------------- | --------------------------------------------------------------------------------------------------- |
| ASDT-FS-007-FIRM-001 | Candidate File ID | Stable ID for the candidate file                                                                    |
| ASDT-FS-007-FIRM-002 | Folder Owner      | Folder that owns the candidate file                                                                 |
| ASDT-FS-007-FIRM-003 | Candidate File    | Proposed file path or file name                                                                     |
| ASDT-FS-007-FIRM-004 | File Role         | component_surface, carrier, state, port, adapter, view, handle, contract, policy, detail, doc, test |
| ASDT-FS-007-FIRM-005 | Visibility        | public_surface, local_surface, private_detail, doc_only, test_only                                  |
| ASDT-FS-007-FIRM-006 | Derivation Source | Folder ownership, component responsibility, boundary role, runtime role, or policy role             |
| ASDT-FS-007-FIRM-007 | Notes             | Clarification, non-ownership warning, or deferred decision                                          |

---

## 4. Inventory Conventions

### 4.1 File Naming Convention

Candidate implementation headers use:

```text
lower_snake_case.hpp
```

Candidate documentation files use:

```text
README.md
ownership.md
dependency_notes.md
contract_notes.md
state_model.md
test_strategy.md
```

Candidate tests use:

```text
<artifact_name>_test.cpp
<artifact_name>_contract_test.cpp
<artifact_name>_state_test.cpp
```

### 4.2 Visibility Values

|           Record ID | Visibility     | Meaning                                             |
| ------------------: | -------------- | --------------------------------------------------- |
| ASDT-FS-007-VIS-001 | public_surface | May become an approved cross-folder include surface |
| ASDT-FS-007-VIS-002 | local_surface  | Intended for local folder or local domain use       |
| ASDT-FS-007-VIS-003 | private_detail | Must not be included from outside nearest owner     |
| ASDT-FS-007-VIS-004 | doc_only       | Documentation only                                  |
| ASDT-FS-007-VIS-005 | test_only      | Test-only artifact                                  |

### 4.3 Candidate Status Rule

All entries in this document have status:

```text
candidate
```

Freeze requires validation in `ASDT-FS-008`.

---

## 5. Global Repository-Level Candidate Files

These files are repository-support files.

They are not DDD implementation-domain files.

|    Candidate File ID | Folder Owner    | Candidate File                     | File Role | Visibility | Derivation Source                  | Notes                                               |
| -------------------: | --------------- | ---------------------------------- | --------- | ---------- | ---------------------------------- | --------------------------------------------------- |
| ASDT-FS-007-ROOT-001 | repository root | `README.md`                        | doc       | doc_only   | repository landing page            | Existing public project entry document              |
| ASDT-FS-007-ROOT-002 | repository root | `docs/architecture_index.md`       | doc       | doc_only   | documentation navigation           | Cross-links local docs; does not replace local docs |
| ASDT-FS-007-ROOT-003 | repository root | `docs/filesystem_index.md`         | doc       | doc_only   | ASDT-FS pack navigation            | Index only                                          |
| ASDT-FS-007-ROOT-004 | repository root | `docs/implementation_readiness.md` | doc       | doc_only   | future ASDT-FS-009 output          | Placeholder candidate only                          |
| ASDT-FS-007-ROOT-005 | repository root | `tests/README.md`                  | doc       | doc_only   | repository-level test coordination | Does not replace local tests                        |
| ASDT-FS-007-ROOT-006 | repository root | `examples/README.md`               | doc       | doc_only   | example coordination               | Examples remain deferred                            |

---

## 6. `ecosystem_governance/` Candidate Inventory

### 6.1 Domain-Level Files

|   Candidate File ID | Folder Owner                  | Candidate File                           | File Role | Visibility | Derivation Source | Notes                                                          |
| ------------------: | ----------------------------- | ---------------------------------------- | --------- | ---------- | ----------------- | -------------------------------------------------------------- |
| ASDT-FS-007-ECO-001 | `ecosystem_governance/`       | `README.md`                              | doc       | doc_only   | domain overview   | Explains ecosystem governance domain                           |
| ASDT-FS-007-ECO-002 | `ecosystem_governance/docs/`  | `domain_ownership.md`                    | doc       | doc_only   | domain ownership  | States policy-source non-ownership                             |
| ASDT-FS-007-ECO-003 | `ecosystem_governance/docs/`  | `dependency_notes.md`                    | doc       | doc_only   | domain dependency | Explains dependency toward consuming domains                   |
| ASDT-FS-007-ECO-004 | `ecosystem_governance/tests/` | `ecosystem_governance_boundary_test.cpp` | test      | test_only  | domain boundary   | Candidate test for non-ownership and receiver-port constraints |

### 6.2 `policy_types/`

|      Candidate File ID | Folder Owner             | Candidate File                         | File Role | Visibility     | Derivation Source           | Notes                                   |
| ---------------------: | ------------------------ | -------------------------------------- | --------- | -------------- | --------------------------- | --------------------------------------- |
| ASDT-FS-007-ECO-PT-001 | `policy_types/`          | `policy_type.hpp`                      | carrier   | public_surface | policy type system          | Candidate representation of policy type |
| ASDT-FS-007-ECO-PT-002 | `policy_types/`          | `policy_clause.hpp`                    | carrier   | public_surface | policy clause vocabulary    | Candidate; no policy execution          |
| ASDT-FS-007-ECO-PT-003 | `policy_types/`          | `policy_mechanism.hpp`                 | carrier   | public_surface | policy mechanism vocabulary | Candidate governed mechanism descriptor |
| ASDT-FS-007-ECO-PT-004 | `policy_types/`          | `policy_object_descriptor.hpp`         | carrier   | public_surface | policy object vocabulary    | Descriptor, not source ownership        |
| ASDT-FS-007-ECO-PT-005 | `policy_types/carriers/` | `policy_type_snapshot.hpp`             | carrier   | local_surface  | policy type carrier         | Candidate snapshot object               |
| ASDT-FS-007-ECO-PT-006 | `policy_types/detail/`   | `policy_type_normalization_detail.hpp` | detail    | private_detail | local implementation detail | Must not be externally included         |
| ASDT-FS-007-ECO-PT-007 | `policy_types/tests/`    | `policy_type_contract_test.cpp`        | test      | test_only      | type discipline             | Tests structural validity only          |

### 6.3 `policy_registry/`

|      Candidate File ID | Folder Owner                         | Candidate File                      | File Role         | Visibility     | Derivation Source       | Notes                                               |
| ---------------------: | ------------------------------------ | ----------------------------------- | ----------------- | -------------- | ----------------------- | --------------------------------------------------- |
| ASDT-FS-007-ECO-PR-001 | `policy_registry/`                   | `policy_registry.hpp`               | component_surface | local_surface  | registry abstraction    | Assembler-facing abstraction, not external registry |
| ASDT-FS-007-ECO-PR-002 | `policy_registry/hosted_ports/`      | `policy_registry_lookup_port.hpp`   | port              | public_surface | hosted lookup surface   | Candidate inbound lookup surface                    |
| ASDT-FS-007-ECO-PR-003 | `policy_registry/outbound_adapters/` | `policy_source_adapter.hpp`         | adapter           | public_surface | provider-facing adapter | Adapter does not own source                         |
| ASDT-FS-007-ECO-PR-004 | `policy_registry/views/`             | `policy_registry_view.hpp`          | view              | public_surface | safe projection         | Read-only projection                                |
| ASDT-FS-007-ECO-PR-005 | `policy_registry/detail/`            | `policy_registry_cache_detail.hpp`  | detail            | private_detail | private implementation  | Candidate only; no storage ownership                |
| ASDT-FS-007-ECO-PR-006 | `policy_registry/tests/`             | `policy_registry_boundary_test.cpp` | test              | test_only      | registry abstraction    | Ensures no external registry ownership              |

### 6.4 `provider_adapters/`

|      Candidate File ID | Folder Owner                           | Candidate File                           | File Role | Visibility     | Derivation Source         | Notes                        |
| ---------------------: | -------------------------------------- | ---------------------------------------- | --------- | -------------- | ------------------------- | ---------------------------- |
| ASDT-FS-007-ECO-PA-001 | `provider_adapters/`                   | `policy_provider_adapter.hpp`            | adapter   | public_surface | provider adapter folder   | Candidate provider surface   |
| ASDT-FS-007-ECO-PA-002 | `provider_adapters/carriers/`          | `policy_provider_payload.hpp`            | carrier   | local_surface  | provider payload          | Transfer material only       |
| ASDT-FS-007-ECO-PA-003 | `provider_adapters/outbound_adapters/` | `external_policy_source_adapter.hpp`     | adapter   | public_surface | external source relation  | Does not own external source |
| ASDT-FS-007-ECO-PA-004 | `provider_adapters/detail/`            | `policy_provider_translation_detail.hpp` | detail    | private_detail | local translation detail  | Private                      |
| ASDT-FS-007-ECO-PA-005 | `provider_adapters/tests/`             | `policy_provider_adapter_test.cpp`       | test      | test_only      | provider adapter behavior | Boundary-only test           |

### 6.5 `receiver_ports/log_level_api/`

|          Candidate File ID | Folder Owner                                 | Candidate File                        | File Role | Visibility     | Derivation Source           | Notes                                 |
| -------------------------: | -------------------------------------------- | ------------------------------------- | --------- | -------------- | --------------------------- | ------------------------------------- |
| ASDT-FS-007-ECO-RP-API-001 | `receiver_ports/log_level_api/hosted_ports/` | `log_level_api_policy_port.hpp`       | port      | public_surface | API policy receiver port    | Port definition for API domain        |
| ASDT-FS-007-ECO-RP-API-002 | `receiver_ports/log_level_api/carriers/`     | `log_level_api_policy_bundle_dto.hpp` | carrier   | public_surface | policy bundle DTO           | Candidate DTO for API policy material |
| ASDT-FS-007-ECO-RP-API-003 | `receiver_ports/log_level_api/docs/`         | `log_level_api_policy_receiver.md`    | doc       | doc_only       | receiver-port documentation | Explains consuming role               |

### 6.6 `receiver_ports/write_side/`

|         Candidate File ID | Folder Owner                              | Candidate File                     | File Role | Visibility     | Derivation Source               | Notes                          |
| ------------------------: | ----------------------------------------- | ---------------------------------- | --------- | -------------- | ------------------------------- | ------------------------------ |
| ASDT-FS-007-ECO-RP-WS-001 | `receiver_ports/write_side/hosted_ports/` | `write_side_policy_port.hpp`       | port      | public_surface | write-side policy receiver port | Port definition for write-side |
| ASDT-FS-007-ECO-RP-WS-002 | `receiver_ports/write_side/carriers/`     | `write_side_policy_bundle_dto.hpp` | carrier   | public_surface | write-side policy bundle        | Candidate DTO                  |
| ASDT-FS-007-ECO-RP-WS-003 | `receiver_ports/write_side/docs/`         | `write_side_policy_receiver.md`    | doc       | doc_only       | receiver-port documentation     | Explains consuming role        |

---

## 7. `log_level_api/` Candidate Inventory

### 7.1 Domain-Level Files

|   Candidate File ID | Folder Owner           | Candidate File                           | File Role | Visibility | Derivation Source    | Notes                                            |
| ------------------: | ---------------------- | ---------------------------------------- | --------- | ---------- | -------------------- | ------------------------------------------------ |
| ASDT-FS-007-API-001 | `log_level_api/`       | `README.md`                              | doc       | doc_only   | domain overview      | Explains preparation API domain                  |
| ASDT-FS-007-API-002 | `log_level_api/docs/`  | `domain_ownership.md`                    | doc       | doc_only   | API domain ownership | Content preparation and envelope production only |
| ASDT-FS-007-API-003 | `log_level_api/tests/` | `log_level_api_domain_boundary_test.cpp` | test      | test_only  | domain boundary      | Ensures no write-side internals are owned        |

### 7.2 `policy_assignment/`

|      Candidate File ID | Folder Owner                      | Candidate File                        | File Role         | Visibility     | Derivation Source               | Notes                                    |
| ---------------------: | --------------------------------- | ------------------------------------- | ----------------- | -------------- | ------------------------------- | ---------------------------------------- |
| ASDT-FS-007-API-PA-001 | `policy_assignment/`              | `log_level_api_policy_assigner.hpp`   | component_surface | local_surface  | API policy assignment component | First API-domain dependency              |
| ASDT-FS-007-API-PA-002 | `policy_assignment/carriers/`     | `policy_assignment.hpp`               | carrier           | local_surface  | local assignment object         | Assignment relation, not policy source   |
| ASDT-FS-007-API-PA-003 | `policy_assignment/carriers/`     | `policy_view.hpp`                     | view              | public_surface | safe policy projection          | Read-only projection                     |
| ASDT-FS-007-API-PA-004 | `policy_assignment/hosted_ports/` | `policy_port_host.hpp`                | port              | public_surface | hosted policy port              | Hosts injected ecosystem governance port |
| ASDT-FS-007-API-PA-005 | `policy_assignment/policies/`     | `api_policy_binding.hpp`              | policy            | local_surface  | API-side policy binding         | Local consumption only                   |
| ASDT-FS-007-API-PA-006 | `policy_assignment/detail/`       | `policy_assignment_detail.hpp`        | detail            | private_detail | local assignment mechanics      | Private                                  |
| ASDT-FS-007-API-PA-007 | `policy_assignment/tests/`        | `policy_assignment_contract_test.cpp` | test              | test_only      | assignment contract             | Ensures policy source non-ownership      |

### 7.3 `content/`

|        Candidate File ID | Folder Owner       | Candidate File               | File Role | Visibility     | Derivation Source            | Notes                  |
| -----------------------: | ------------------ | ---------------------------- | --------- | -------------- | ---------------------------- | ---------------------- |
| ASDT-FS-007-API-CONT-001 | `content/`         | `content.hpp`                | carrier   | public_surface | content carrier root         | Pre-envelope content   |
| ASDT-FS-007-API-CONT-002 | `content/views/`   | `content_view.hpp`           | view      | public_surface | read-only content projection | No mutation authority  |
| ASDT-FS-007-API-CONT-003 | `content/handles/` | `content_handle.hpp`         | handle    | public_surface | safe content reference       | Reference only         |
| ASDT-FS-007-API-CONT-004 | `content/detail/`  | `content_storage_detail.hpp` | detail    | private_detail | content internals            | Private                |
| ASDT-FS-007-API-CONT-005 | `content/tests/`   | `content_carrier_test.cpp`   | test      | test_only      | content carrier              | Verifies carrier shape |

### 7.4 `validator/`

|       Candidate File ID | Folder Owner           | Candidate File                   | File Role         | Visibility     | Derivation Source             | Notes                                 |
| ----------------------: | ---------------------- | -------------------------------- | ----------------- | -------------- | ----------------------------- | ------------------------------------- |
| ASDT-FS-007-API-VAL-001 | `validator/`           | `validator.hpp`                  | component_surface | local_surface  | validator component           | Abstract validation surface           |
| ASDT-FS-007-API-VAL-002 | `validator/`           | `plain_validator.hpp`            | component_surface | local_surface  | plain validation variant      | No policy binding                     |
| ASDT-FS-007-API-VAL-003 | `validator/`           | `policy_bound_validator.hpp`     | component_surface | local_surface  | policy-consuming variant      | Uses assigned policy                  |
| ASDT-FS-007-API-VAL-004 | `validator/carriers/`  | `validation_result.hpp`          | carrier           | public_surface | validation result             | Transfer result only                  |
| ASDT-FS-007-API-VAL-005 | `validator/carriers/`  | `validation_rule.hpp`            | carrier           | local_surface  | validation rule material      | Rule material, not full policy source |
| ASDT-FS-007-API-VAL-006 | `validator/state/`     | `validation_state.hpp`           | state             | local_surface  | local validation state        | Only if needed                        |
| ASDT-FS-007-API-VAL-007 | `validator/policies/`  | `validation_policy_binding.hpp`  | policy            | local_surface  | policy-consuming behavior     | Local policy consumption              |
| ASDT-FS-007-API-VAL-008 | `validator/contracts/` | `validation_contract.hpp`        | contract          | local_surface  | validation law representation | Contract representation only          |
| ASDT-FS-007-API-VAL-009 | `validator/detail/`    | `validation_pipeline_detail.hpp` | detail            | private_detail | internal validation pipeline  | Private                               |
| ASDT-FS-007-API-VAL-010 | `validator/tests/`     | `validator_contract_test.cpp`    | test              | test_only      | validation contract           | Tests policy/plain variants           |

### 7.5 `timestamp_stabilizer/`

|      Candidate File ID | Folder Owner                      | Candidate File                         | File Role         | Visibility     | Derivation Source           | Notes                                     |
| ---------------------: | --------------------------------- | -------------------------------------- | ----------------- | -------------- | --------------------------- | ----------------------------------------- |
| ASDT-FS-007-API-TS-001 | `timestamp_stabilizer/`           | `timestamp_stabilizer.hpp`             | component_surface | local_surface  | timestamp component         | Stabilization before dispatch eligibility |
| ASDT-FS-007-API-TS-002 | `timestamp_stabilizer/carriers/`  | `timestamp_input.hpp`                  | carrier           | local_surface  | timestamp input             | Preparation input                         |
| ASDT-FS-007-API-TS-003 | `timestamp_stabilizer/carriers/`  | `stabilized_timestamp.hpp`             | carrier           | public_surface | stabilized timestamp        | Prepared result                           |
| ASDT-FS-007-API-TS-004 | `timestamp_stabilizer/state/`     | `timestamp_stabilization_state.hpp`    | state             | local_surface  | local state                 | Not downstream query semantics            |
| ASDT-FS-007-API-TS-005 | `timestamp_stabilizer/policies/`  | `timestamp_policy_binding.hpp`         | policy            | local_surface  | optional policy consumption | Local only                                |
| ASDT-FS-007-API-TS-006 | `timestamp_stabilizer/contracts/` | `timestamp_stabilization_contract.hpp` | contract          | local_surface  | timestamp contract          | Representation only                       |
| ASDT-FS-007-API-TS-007 | `timestamp_stabilizer/detail/`    | `timestamp_normalization_detail.hpp`   | detail            | private_detail | private normalization       | Private                                   |
| ASDT-FS-007-API-TS-008 | `timestamp_stabilizer/tests/`     | `timestamp_stabilizer_test.cpp`        | test              | test_only      | timestamp behavior          | Ensures no query-time ownership           |

### 7.6 `metadata_injector/`

|        Candidate File ID | Folder Owner                   | Candidate File                        | File Role         | Visibility     | Derivation Source             | Notes                                  |
| -----------------------: | ------------------------------ | ------------------------------------- | ----------------- | -------------- | ----------------------------- | -------------------------------------- |
| ASDT-FS-007-API-META-001 | `metadata_injector/`           | `metadata_injector.hpp`               | component_surface | local_surface  | metadata injection component  | Schema/directive governed              |
| ASDT-FS-007-API-META-002 | `metadata_injector/carriers/`  | `metadata_directive_input.hpp`        | carrier           | local_surface  | directive input               | Not policy host                        |
| ASDT-FS-007-API-META-003 | `metadata_injector/carriers/`  | `prepared_metadata.hpp`               | carrier           | public_surface | prepared metadata result      | Used by envelope assembly              |
| ASDT-FS-007-API-META-004 | `metadata_injector/state/`     | `metadata_preparation_state.hpp`      | state             | local_surface  | local preparation state       | Candidate only                         |
| ASDT-FS-007-API-META-005 | `metadata_injector/contracts/` | `metadata_preparation_contract.hpp`   | contract          | local_surface  | metadata contract             | Not policy source                      |
| ASDT-FS-007-API-META-006 | `metadata_injector/detail/`    | `metadata_injection_detail.hpp`       | detail            | private_detail | private preparation mechanics | Private                                |
| ASDT-FS-007-API-META-007 | `metadata_injector/tests/`     | `metadata_injector_contract_test.cpp` | test              | test_only      | metadata behavior             | Verifies not policy-hosting by default |

### 7.7 `envelope/`

|       Candidate File ID | Folder Owner        | Candidate File                        | File Role | Visibility     | Derivation Source        | Notes                      |
| ----------------------: | ------------------- | ------------------------------------- | --------- | -------------- | ------------------------ | -------------------------- |
| ASDT-FS-007-API-ENV-001 | `envelope/`         | `log_level_envelope.hpp`              | carrier   | public_surface | envelope carrier root    | Central prepared carrier   |
| ASDT-FS-007-API-ENV-002 | `envelope/`         | `envelope_header.hpp`                 | carrier   | public_surface | envelope structure       | Header carrier             |
| ASDT-FS-007-API-ENV-003 | `envelope/`         | `envelope_body.hpp`                   | carrier   | public_surface | envelope structure       | Body carrier               |
| ASDT-FS-007-API-ENV-004 | `envelope/`         | `envelope_identity.hpp`               | carrier   | public_surface | envelope identity        | Identity artifact          |
| ASDT-FS-007-API-ENV-005 | `envelope/`         | `envelope_metadata_block.hpp`         | carrier   | public_surface | metadata block           | Prepared metadata block    |
| ASDT-FS-007-API-ENV-006 | `envelope/`         | `envelope_timestamp_block.hpp`        | carrier   | public_surface | timestamp block          | Stabilized timestamp block |
| ASDT-FS-007-API-ENV-007 | `envelope/views/`   | `log_level_envelope_view.hpp`         | view      | public_surface | safe projection          | Read-only                  |
| ASDT-FS-007-API-ENV-008 | `envelope/handles/` | `log_level_envelope_handle.hpp`       | handle    | public_surface | safe reference           | Reference only             |
| ASDT-FS-007-API-ENV-009 | `envelope/detail/`  | `envelope_layout_detail.hpp`          | detail    | private_detail | private layout mechanics | Not public API             |
| ASDT-FS-007-API-ENV-010 | `envelope/tests/`   | `log_level_envelope_carrier_test.cpp` | test      | test_only      | envelope carrier         | Ensures carrier, not actor |

### 7.8 `envelope_assembler/`

|      Candidate File ID | Folder Owner                    | Candidate File                              | File Role         | Visibility     | Derivation Source          | Notes                                          |
| ---------------------: | ------------------------------- | ------------------------------------------- | ----------------- | -------------- | -------------------------- | ---------------------------------------------- |
| ASDT-FS-007-API-EA-001 | `envelope_assembler/`           | `envelope_assembler.hpp`                    | component_surface | local_surface  | assembly component         | General assembler                              |
| ASDT-FS-007-API-EA-002 | `envelope_assembler/`           | `plain_envelope_assembler.hpp`              | component_surface | local_surface  | plain assembler variant    | No composed validator                          |
| ASDT-FS-007-API-EA-003 | `envelope_assembler/`           | `validator_composed_envelope_assembler.hpp` | component_surface | local_surface  | composed validator variant | Composes validator                             |
| ASDT-FS-007-API-EA-004 | `envelope_assembler/carriers/`  | `assembly_input.hpp`                        | carrier           | local_surface  | assembly input             | Input bundle                                   |
| ASDT-FS-007-API-EA-005 | `envelope_assembler/carriers/`  | `assembly_result.hpp`                       | carrier           | public_surface | assembly result            | Produces envelope                              |
| ASDT-FS-007-API-EA-006 | `envelope_assembler/carriers/`  | `preparation_bundle.hpp`                    | carrier           | local_surface  | prepared material          | Contains validation/metadata/timestamp results |
| ASDT-FS-007-API-EA-007 | `envelope_assembler/state/`     | `assembly_state.hpp`                        | state             | local_surface  | assembly state             | Candidate only                                 |
| ASDT-FS-007-API-EA-008 | `envelope_assembler/contracts/` | `envelope_assembly_contract.hpp`            | contract          | local_surface  | assembly contract          | Representation only                            |
| ASDT-FS-007-API-EA-009 | `envelope_assembler/detail/`    | `assembly_pipeline_detail.hpp`              | detail            | private_detail | private assembly pipeline  | Private                                        |
| ASDT-FS-007-API-EA-010 | `envelope_assembler/tests/`     | `envelope_assembler_contract_test.cpp`      | test              | test_only      | assembly behavior          | Tests variants                                 |

### 7.9 `write_side_bridge/`

|       Candidate File ID | Folder Owner                           | Candidate File                          | File Role         | Visibility     | Derivation Source         | Notes                                |
| ----------------------: | -------------------------------------- | --------------------------------------- | ----------------- | -------------- | ------------------------- | ------------------------------------ |
| ASDT-FS-007-API-WSB-001 | `write_side_bridge/`                   | `write_side_bridge.hpp`                 | component_surface | local_surface  | API/write-side bridge     | Bridge only                          |
| ASDT-FS-007-API-WSB-002 | `write_side_bridge/hosted_ports/`      | `envelope_placement_port_host.hpp`      | port              | public_surface | hosted placement surface  | Does not expose slot internals       |
| ASDT-FS-007-API-WSB-003 | `write_side_bridge/outbound_adapters/` | `envelope_load_signal_adapter.hpp`      | adapter           | public_surface | outbound signal adapter   | Load signal only                     |
| ASDT-FS-007-API-WSB-004 | `write_side_bridge/carriers/`          | `envelope_placement_request.hpp`        | carrier           | public_surface | placement request         | Bridge-safe request                  |
| ASDT-FS-007-API-WSB-005 | `write_side_bridge/carriers/`          | `envelope_placement_handle.hpp`         | handle            | public_surface | placement handle          | Reference only                       |
| ASDT-FS-007-API-WSB-006 | `write_side_bridge/carriers/`          | `envelope_load_signal.hpp`              | carrier           | public_surface | load signal               | Signal material                      |
| ASDT-FS-007-API-WSB-007 | `write_side_bridge/carriers/`          | `next_envelope_destination_request.hpp` | carrier           | public_surface | next destination request  | Does not own placement internals     |
| ASDT-FS-007-API-WSB-008 | `write_side_bridge/views/`             | `placement_readiness_view.hpp`          | view              | public_surface | safe readiness projection | No mutation                          |
| ASDT-FS-007-API-WSB-009 | `write_side_bridge/detail/`            | `bridge_translation_detail.hpp`         | detail            | private_detail | private translation       | Private                              |
| ASDT-FS-007-API-WSB-010 | `write_side_bridge/tests/`             | `write_side_bridge_boundary_test.cpp`   | test              | test_only      | bridge boundary           | Ensures no write-side internals leak |

---

## 8. `write_side/` Candidate Inventory

### 8.1 Domain-Level Files

|  Candidate File ID | Folder Owner        | Candidate File                        | File Role | Visibility | Derivation Source          | Notes                                              |
| -----------------: | ------------------- | ------------------------------------- | --------- | ---------- | -------------------------- | -------------------------------------------------- |
| ASDT-FS-007-WS-001 | `write_side/`       | `README.md`                           | doc       | doc_only   | write-side domain overview | Runtime placement and dispatch                     |
| ASDT-FS-007-WS-002 | `write_side/docs/`  | `domain_ownership.md`                 | doc       | doc_only   | write-side ownership       | Excludes envelope assembly and downstream registry |
| ASDT-FS-007-WS-003 | `write_side/docs/`  | `runtime_flow.md`                     | doc       | doc_only   | runtime coordination       | Explains placement, rounds, dispatch               |
| ASDT-FS-007-WS-004 | `write_side/tests/` | `write_side_domain_boundary_test.cpp` | test      | test_only  | domain boundary            | Ensures downstream non-ownership                   |

### 8.2 `policy_assignment/`

|     Candidate File ID | Folder Owner                      | Candidate File                            | File Role         | Visibility     | Derivation Source            | Notes                             |
| --------------------: | --------------------------------- | ----------------------------------------- | ----------------- | -------------- | ---------------------------- | --------------------------------- |
| ASDT-FS-007-WS-PA-001 | `policy_assignment/`              | `write_side_policy_assigner.hpp`          | component_surface | local_surface  | write-side policy assignment | First write-side dependency       |
| ASDT-FS-007-WS-PA-002 | `policy_assignment/carriers/`     | `write_side_policy_assignment.hpp`        | carrier           | local_surface  | local assignment             | Assignment relation               |
| ASDT-FS-007-WS-PA-003 | `policy_assignment/carriers/`     | `write_side_policy_view.hpp`              | view              | public_surface | safe policy projection       | Read-only                         |
| ASDT-FS-007-WS-PA-004 | `policy_assignment/hosted_ports/` | `write_side_policy_port_host.hpp`         | port              | public_surface | hosted policy port           | Injected ecosystem port           |
| ASDT-FS-007-WS-PA-005 | `policy_assignment/policies/`     | `runtime_policy_binding.hpp`              | policy            | local_surface  | runtime policy binding       | Local consumption only            |
| ASDT-FS-007-WS-PA-006 | `policy_assignment/detail/`       | `write_side_policy_assignment_detail.hpp` | detail            | private_detail | assignment mechanics         | Private                           |
| ASDT-FS-007-WS-PA-007 | `policy_assignment/tests/`        | `write_side_policy_assignment_test.cpp`   | test              | test_only      | assignment behavior          | Tests policy-source non-ownership |

### 8.3 `slot/`

|       Candidate File ID | Folder Owner              | Candidate File                  | File Role         | Visibility     | Derivation Source    | Notes                                     |
| ----------------------: | ------------------------- | ------------------------------- | ----------------- | -------------- | -------------------- | ----------------------------------------- |
| ASDT-FS-007-WS-SLOT-001 | `slot/`                   | `slot.hpp`                      | component_surface | public_surface | slot semantic root   | Slot structure                            |
| ASDT-FS-007-WS-SLOT-002 | `slot/carriers/`          | `slot_occupancy_record.hpp`     | carrier           | public_surface | occupancy carrier    | Records placement, not envelope lifecycle |
| ASDT-FS-007-WS-SLOT-003 | `slot/state/`             | `slot_lifecycle_state.hpp`      | state             | local_surface  | slot state           | Local lifecycle only                      |
| ASDT-FS-007-WS-SLOT-004 | `slot/state/transitions/` | `occupy_slot_transition.hpp`    | state             | local_surface  | occupancy transition | Local transition                          |
| ASDT-FS-007-WS-SLOT-005 | `slot/state/transitions/` | `release_slot_transition.hpp`   | state             | local_surface  | release transition   | Local transition                          |
| ASDT-FS-007-WS-SLOT-006 | `slot/state/guards/`      | `slot_available_guard.hpp`      | state             | local_surface  | slot guard           | Local guard                               |
| ASDT-FS-007-WS-SLOT-007 | `slot/views/`             | `slot_view.hpp`                 | view              | public_surface | safe slot projection | No mutation                               |
| ASDT-FS-007-WS-SLOT-008 | `slot/handles/`           | `slot_handle.hpp`               | handle            | public_surface | safe slot reference  | No ownership transfer                     |
| ASDT-FS-007-WS-SLOT-009 | `slot/contracts/`         | `slot_occupancy_contract.hpp`   | contract          | local_surface  | slot contract        | Representation only                       |
| ASDT-FS-007-WS-SLOT-010 | `slot/detail/`            | `slot_storage_detail.hpp`       | detail            | private_detail | private slot storage | Private                                   |
| ASDT-FS-007-WS-SLOT-011 | `slot/tests/`             | `slot_occupancy_state_test.cpp` | test              | test_only      | slot behavior        | Verifies occupancy semantics              |

### 8.4 `slots_container/`

|     Candidate File ID | Folder Owner                         | Candidate File                       | File Role         | Visibility     | Derivation Source       | Notes                        |
| --------------------: | ------------------------------------ | ------------------------------------ | ----------------- | -------------- | ----------------------- | ---------------------------- |
| ASDT-FS-007-WS-SC-001 | `slots_container/`                   | `slots_container.hpp`                | component_surface | public_surface | container semantic root | Queue = Container            |
| ASDT-FS-007-WS-SC-002 | `slots_container/carriers/`          | `slots_container_snapshot.hpp`       | carrier           | public_surface | container snapshot      | Read/transfer shape          |
| ASDT-FS-007-WS-SC-003 | `slots_container/state/`             | `slots_container_state.hpp`          | state             | local_surface  | container state         | Fullness/readiness           |
| ASDT-FS-007-WS-SC-004 | `slots_container/state/transitions/` | `place_envelope_transition.hpp`      | state             | local_surface  | placement transition    | Local transition             |
| ASDT-FS-007-WS-SC-005 | `slots_container/state/guards/`      | `slots_container_capacity_guard.hpp` | state             | local_surface  | capacity guard          | Local guard                  |
| ASDT-FS-007-WS-SC-006 | `slots_container/views/`             | `slots_container_view.hpp`           | view              | public_surface | container projection    | Safe readiness               |
| ASDT-FS-007-WS-SC-007 | `slots_container/handles/`           | `slots_container_handle.hpp`         | handle            | public_surface | container handle        | Reference only               |
| ASDT-FS-007-WS-SC-008 | `slots_container/contracts/`         | `slots_container_contract.hpp`       | contract          | local_surface  | container contract      | Not broker contract          |
| ASDT-FS-007-WS-SC-009 | `slots_container/detail/`            | `slots_container_storage_detail.hpp` | detail            | private_detail | internal storage        | Private                      |
| ASDT-FS-007-WS-SC-010 | `slots_container/tests/`             | `slots_container_contract_test.cpp`  | test              | test_only      | container behavior      | Enforces no broker semantics |

### 8.5 `waiting_list/`

|     Candidate File ID | Folder Owner             | Candidate File                     | File Role         | Visibility     | Derivation Source          | Notes                      |
| --------------------: | ------------------------ | ---------------------------------- | ----------------- | -------------- | -------------------------- | -------------------------- |
| ASDT-FS-007-WS-WL-001 | `waiting_list/`          | `waiting_list.hpp`                 | component_surface | public_surface | waiting-list semantic root | Identifier list            |
| ASDT-FS-007-WS-WL-002 | `waiting_list/carriers/` | `waiting_list_entry.hpp`           | carrier           | public_surface | list entry carrier         | Entry material             |
| ASDT-FS-007-WS-WL-003 | `waiting_list/carriers/` | `queue_container_identifier.hpp`   | handle            | public_surface | container identifier       | Carries identifier only    |
| ASDT-FS-007-WS-WL-004 | `waiting_list/state/`    | `waiting_list_state.hpp`           | state             | local_surface  | list readiness state       | Local only                 |
| ASDT-FS-007-WS-WL-005 | `waiting_list/views/`    | `waiting_list_view.hpp`            | view              | public_surface | safe projection            | Read-only                  |
| ASDT-FS-007-WS-WL-006 | `waiting_list/handles/`  | `waiting_list_handle.hpp`          | handle            | public_surface | reference                  | No ownership transfer      |
| ASDT-FS-007-WS-WL-007 | `waiting_list/detail/`   | `waiting_list_ordering_detail.hpp` | detail            | private_detail | ordering mechanics         | Private                    |
| ASDT-FS-007-WS-WL-008 | `waiting_list/tests/`    | `waiting_list_identifier_test.cpp` | test              | test_only      | identifier behavior        | Ensures not envelope store |

### 8.6 `slots_container_moderator/`

|      Candidate File ID | Folder Owner                          | Candidate File                          | File Role         | Visibility     | Derivation Source          | Notes                        |
| ---------------------: | ------------------------------------- | --------------------------------------- | ----------------- | -------------- | -------------------------- | ---------------------------- |
| ASDT-FS-007-WS-SCM-001 | `slots_container_moderator/`          | `slots_container_moderator.hpp`         | component_surface | local_surface  | single-container moderator | One moderator per container  |
| ASDT-FS-007-WS-SCM-002 | `slots_container_moderator/carriers/` | `container_preparation_report.hpp`      | carrier           | local_surface  | preparation report         | Report only                  |
| ASDT-FS-007-WS-SCM-003 | `slots_container_moderator/state/`    | `moderator_readiness_state.hpp`         | state             | local_surface  | moderator state            | Local readiness              |
| ASDT-FS-007-WS-SCM-004 | `slots_container_moderator/views/`    | `container_moderation_view.hpp`         | view              | public_surface | moderation projection      | Safe projection              |
| ASDT-FS-007-WS-SCM-005 | `slots_container_moderator/handles/`  | `moderator_handle.hpp`                  | handle            | public_surface | moderator reference        | Reference only               |
| ASDT-FS-007-WS-SCM-006 | `slots_container_moderator/policies/` | `moderation_policy_binding.hpp`         | policy            | local_surface  | local policy consumption   | Optional                     |
| ASDT-FS-007-WS-SCM-007 | `slots_container_moderator/detail/`   | `container_reinitialization_detail.hpp` | detail            | private_detail | reinitialization mechanics | Private                      |
| ASDT-FS-007-WS-SCM-008 | `slots_container_moderator/tests/`    | `slots_container_moderator_test.cpp`    | test              | test_only      | moderation behavior        | Tests single-container scope |

### 8.7 `slots_container_bundle_agent/`

|       Candidate File ID | Folder Owner                              | Candidate File                     | File Role         | Visibility     | Derivation Source           | Notes                                 |
| ----------------------: | ----------------------------------------- | ---------------------------------- | ----------------- | -------------- | --------------------------- | ------------------------------------- |
| ASDT-FS-007-WS-SCBA-001 | `slots_container_bundle_agent/`           | `slots_container_bundle_agent.hpp` | component_surface | local_surface  | bundle-level topology actor | Scaling/topology owner                |
| ASDT-FS-007-WS-SCBA-002 | `slots_container_bundle_agent/carriers/`  | `bundle_topology_snapshot.hpp`     | carrier           | local_surface  | bundle topology             | Snapshot only                         |
| ASDT-FS-007-WS-SCBA-003 | `slots_container_bundle_agent/carriers/`  | `container_scaling_plan.hpp`       | carrier           | local_surface  | scaling plan                | Horizontal/vertical scaling candidate |
| ASDT-FS-007-WS-SCBA-004 | `slots_container_bundle_agent/state/`     | `bundle_topology_state.hpp`        | state             | local_surface  | bundle state                | Local topology                        |
| ASDT-FS-007-WS-SCBA-005 | `slots_container_bundle_agent/views/`     | `bundle_capacity_view.hpp`         | view              | public_surface | safe bundle projection      | Read-only                             |
| ASDT-FS-007-WS-SCBA-006 | `slots_container_bundle_agent/handles/`   | `bundle_handle.hpp`                | handle            | public_surface | bundle reference            | Reference only                        |
| ASDT-FS-007-WS-SCBA-007 | `slots_container_bundle_agent/policies/`  | `scaling_policy_binding.hpp`       | policy            | local_surface  | scaling policy              | Optional                              |
| ASDT-FS-007-WS-SCBA-008 | `slots_container_bundle_agent/contracts/` | `bundle_scaling_contract.hpp`      | contract          | local_surface  | scaling contract            | Representation only                   |
| ASDT-FS-007-WS-SCBA-009 | `slots_container_bundle_agent/detail/`    | `bundle_scaling_detail.hpp`        | detail            | private_detail | scaling mechanics           | Private                               |
| ASDT-FS-007-WS-SCBA-010 | `slots_container_bundle_agent/tests/`     | `bundle_agent_scaling_test.cpp`    | test              | test_only      | bundle behavior             | Ensures not round manager             |

### 8.8 `round_manager/`

|     Candidate File ID | Folder Owner                       | Candidate File                    | File Role         | Visibility     | Derivation Source          | Notes                              |
| --------------------: | ---------------------------------- | --------------------------------- | ----------------- | -------------- | -------------------------- | ---------------------------------- |
| ASDT-FS-007-WS-RM-001 | `round_manager/`                   | `round_manager.hpp`               | component_surface | local_surface  | round coordination actor   | Coordinates rounds                 |
| ASDT-FS-007-WS-RM-002 | `round_manager/`                   | `writing_round_manager.hpp`       | component_surface | local_surface  | writing/feeding round      | Candidate split inside same folder |
| ASDT-FS-007-WS-RM-003 | `round_manager/`                   | `dispatching_round_manager.hpp`   | component_surface | local_surface  | dispatching/delivery round | Candidate split inside same folder |
| ASDT-FS-007-WS-RM-004 | `round_manager/carriers/`          | `round_membership_record.hpp`     | carrier           | local_surface  | round membership           | Membership carrier                 |
| ASDT-FS-007-WS-RM-005 | `round_manager/carriers/`          | `round_transition_report.hpp`     | carrier           | local_surface  | transition report          | Report only                        |
| ASDT-FS-007-WS-RM-006 | `round_manager/state/`             | `round_state.hpp`                 | state             | local_surface  | round state                | Local state                        |
| ASDT-FS-007-WS-RM-007 | `round_manager/state/transitions/` | `advance_round_transition.hpp`    | state             | local_surface  | round advancement          | Local transition                   |
| ASDT-FS-007-WS-RM-008 | `round_manager/state/guards/`      | `round_readiness_guard.hpp`       | state             | local_surface  | readiness guard            | Local guard                        |
| ASDT-FS-007-WS-RM-009 | `round_manager/views/`             | `round_membership_view.hpp`       | view              | public_surface | safe projection            | Read-only                          |
| ASDT-FS-007-WS-RM-010 | `round_manager/handles/`           | `round_handle.hpp`                | handle            | public_surface | round reference            | No ownership transfer              |
| ASDT-FS-007-WS-RM-011 | `round_manager/contracts/`         | `round_coordination_contract.hpp` | contract          | local_surface  | round contract             | Representation only                |
| ASDT-FS-007-WS-RM-012 | `round_manager/detail/`            | `round_rotation_detail.hpp`       | detail            | private_detail | rotation mechanics         | Private                            |
| ASDT-FS-007-WS-RM-013 | `round_manager/tests/`             | `round_manager_state_test.cpp`    | test              | test_only      | round behavior             | Tests writing/delivery transitions |

### 8.9 `reference_precalculator/`

|     Candidate File ID | Folder Owner                        | Candidate File                         | File Role         | Visibility     | Derivation Source               | Notes                                    |
| --------------------: | ----------------------------------- | -------------------------------------- | ----------------- | -------------- | ------------------------------- | ---------------------------------------- |
| ASDT-FS-007-WS-RP-001 | `reference_precalculator/`          | `reference_precalculator.hpp`          | component_surface | local_surface  | proactive reference calculation | Supports stable workflow                 |
| ASDT-FS-007-WS-RP-002 | `reference_precalculator/carriers/` | `precalculated_reference.hpp`          | carrier           | public_surface | calculated reference            | Reference material                       |
| ASDT-FS-007-WS-RP-003 | `reference_precalculator/carriers/` | `reference_precalculation_request.hpp` | carrier           | public_surface | request carrier                 | Request material                         |
| ASDT-FS-007-WS-RP-004 | `reference_precalculator/views/`    | `reference_precalculation_view.hpp`    | view              | public_surface | safe projection                 | No mutation                              |
| ASDT-FS-007-WS-RP-005 | `reference_precalculator/handles/`  | `precalculated_reference_handle.hpp`   | handle            | public_surface | reference handle                | Reference only                           |
| ASDT-FS-007-WS-RP-006 | `reference_precalculator/detail/`   | `reference_calculation_detail.hpp`     | detail            | private_detail | calculation mechanics           | Private                                  |
| ASDT-FS-007-WS-RP-007 | `reference_precalculator/tests/`    | `reference_precalculator_test.cpp`     | test              | test_only      | reference behavior              | Ensures not dispatcher or registry owner |

### 8.10 `dispatcher/`

|       Candidate File ID | Folder Owner                    | Candidate File                         | File Role         | Visibility     | Derivation Source               | Notes                            |
| ----------------------: | ------------------------------- | -------------------------------------- | ----------------- | -------------- | ------------------------------- | -------------------------------- |
| ASDT-FS-007-WS-DISP-001 | `dispatcher/`                   | `dispatcher.hpp`                       | component_surface | local_surface  | final outbound actor            | Dispatcher finality              |
| ASDT-FS-007-WS-DISP-002 | `dispatcher/carriers/`          | `dispatch_material.hpp`                | carrier           | public_surface | dispatch transfer material      | Transfer only                    |
| ASDT-FS-007-WS-DISP-003 | `dispatcher/carriers/`          | `dispatcher_feedback_report.hpp`       | carrier           | public_surface | feedback report                 | Report artifact                  |
| ASDT-FS-007-WS-DISP-004 | `dispatcher/state/`             | `dispatch_eligibility_state.hpp`       | state             | local_surface  | dispatch readiness              | Local state                      |
| ASDT-FS-007-WS-DISP-005 | `dispatcher/state/transitions/` | `mark_dispatch_ready_transition.hpp`   | state             | local_surface  | readiness transition            | Local transition                 |
| ASDT-FS-007-WS-DISP-006 | `dispatcher/state/guards/`      | `dispatch_eligibility_guard.hpp`       | state             | local_surface  | eligibility guard               | Local guard                      |
| ASDT-FS-007-WS-DISP-007 | `dispatcher/hosted_ports/`      | `dispatcher_admission_port.hpp`        | port              | public_surface | dispatcher inbound surface      | Candidate                        |
| ASDT-FS-007-WS-DISP-008 | `dispatcher/outbound_adapters/` | `registry_delivery_adapter.hpp`        | adapter           | public_surface | registry-facing adapter         | Does not own registry            |
| ASDT-FS-007-WS-DISP-009 | `dispatcher/views/`             | `dispatch_readiness_view.hpp`          | view              | public_surface | safe projection                 | Read-only                        |
| ASDT-FS-007-WS-DISP-010 | `dispatcher/handles/`           | `dispatch_handle.hpp`                  | handle            | public_surface | dispatch reference              | Reference only                   |
| ASDT-FS-007-WS-DISP-011 | `dispatcher/policies/`          | `dispatch_policy_binding.hpp`          | policy            | local_surface  | optional dispatch policy        | Local consumption                |
| ASDT-FS-007-WS-DISP-012 | `dispatcher/contracts/`         | `dispatcher_handoff_contract.hpp`      | contract          | local_surface  | handoff contract representation | Representation only              |
| ASDT-FS-007-WS-DISP-013 | `dispatcher/detail/`            | `dispatcher_pipeline_detail.hpp`       | detail            | private_detail | private dispatch pipeline       | Private                          |
| ASDT-FS-007-WS-DISP-014 | `dispatcher/tests/`             | `dispatcher_handoff_contract_test.cpp` | test              | test_only      | dispatcher/handoff behavior     | Ensures downstream non-ownership |

### 8.11 `communications/log_level_api_feeding/`

|           Candidate File ID | Folder Owner                                              | Candidate File                            | File Role | Visibility     | Derivation Source            | Notes                                |
| --------------------------: | --------------------------------------------------------- | ----------------------------------------- | --------- | -------------- | ---------------------------- | ------------------------------------ |
| ASDT-FS-007-WS-COMM-LAF-001 | `communications/log_level_api_feeding/`                   | `README.md`                               | doc       | doc_only       | feeding boundary overview    | Boundary documentation               |
| ASDT-FS-007-WS-COMM-LAF-002 | `communications/log_level_api_feeding/carriers/`          | `envelope_admission_request.hpp`          | carrier   | public_surface | feeding request              | Prepared envelope admission          |
| ASDT-FS-007-WS-COMM-LAF-003 | `communications/log_level_api_feeding/carriers/`          | `envelope_admission_result.hpp`           | carrier   | public_surface | feeding result               | Admission result                     |
| ASDT-FS-007-WS-COMM-LAF-004 | `communications/log_level_api_feeding/hosted_ports/`      | `envelope_admission_port.hpp`             | port      | public_surface | write-side receiving surface | Does not expose internals            |
| ASDT-FS-007-WS-COMM-LAF-005 | `communications/log_level_api_feeding/outbound_adapters/` | `placement_signal_adapter.hpp`            | adapter   | public_surface | internal translation         | Boundary adapter                     |
| ASDT-FS-007-WS-COMM-LAF-006 | `communications/log_level_api_feeding/views/`             | `feeding_readiness_view.hpp`              | view      | public_surface | safe readiness projection    | No mutation                          |
| ASDT-FS-007-WS-COMM-LAF-007 | `communications/log_level_api_feeding/handles/`           | `placement_handle.hpp`                    | handle    | public_surface | placement reference          | No ownership transfer                |
| ASDT-FS-007-WS-COMM-LAF-008 | `communications/log_level_api_feeding/detail/`            | `feeding_boundary_translation_detail.hpp` | detail    | private_detail | private translation          | Private                              |
| ASDT-FS-007-WS-COMM-LAF-009 | `communications/log_level_api_feeding/tests/`             | `log_level_api_feeding_boundary_test.cpp` | test      | test_only      | boundary test                | Ensures no write-side internals leak |

### 8.12 `communications/registry_delivery/`

|          Candidate File ID | Folder Owner                                          | Candidate File                             | File Role | Visibility     | Derivation Source                   | Notes                               |
| -------------------------: | ----------------------------------------------------- | ------------------------------------------ | --------- | -------------- | ----------------------------------- | ----------------------------------- |
| ASDT-FS-007-WS-COMM-RD-001 | `communications/registry_delivery/`                   | `README.md`                                | doc       | doc_only       | registry-delivery boundary overview | Boundary documentation              |
| ASDT-FS-007-WS-COMM-RD-002 | `communications/registry_delivery/carriers/`          | `handoff_material.hpp`                     | carrier   | public_surface | handoff material                    | Transfer material                   |
| ASDT-FS-007-WS-COMM-RD-003 | `communications/registry_delivery/carriers/`          | `handoff_evidence.hpp`                     | carrier   | public_surface | handoff evidence                    | Not persistence proof               |
| ASDT-FS-007-WS-COMM-RD-004 | `communications/registry_delivery/carriers/`          | `handoff_confirmation.hpp`                 | carrier   | public_surface | confirmation carrier                | Does not imply lifecycle ownership  |
| ASDT-FS-007-WS-COMM-RD-005 | `communications/registry_delivery/hosted_ports/`      | `registry_delivery_port.hpp`               | port      | public_surface | delivery boundary surface           | Port, not registry                  |
| ASDT-FS-007-WS-COMM-RD-006 | `communications/registry_delivery/outbound_adapters/` | `downstream_registry_adapter.hpp`          | adapter   | public_surface | downstream-facing adapter           | Does not own downstream             |
| ASDT-FS-007-WS-COMM-RD-007 | `communications/registry_delivery/views/`             | `handoff_readiness_view.hpp`               | view      | public_surface | safe handoff projection             | Read-only                           |
| ASDT-FS-007-WS-COMM-RD-008 | `communications/registry_delivery/handles/`           | `handoff_handle.hpp`                       | handle    | public_surface | handoff reference                   | Reference only                      |
| ASDT-FS-007-WS-COMM-RD-009 | `communications/registry_delivery/contracts/`         | `registry_delivery_contract.hpp`           | contract  | local_surface  | delivery contract representation    | Representation only                 |
| ASDT-FS-007-WS-COMM-RD-010 | `communications/registry_delivery/detail/`            | `registry_delivery_translation_detail.hpp` | detail    | private_detail | private translation                 | Private                             |
| ASDT-FS-007-WS-COMM-RD-011 | `communications/registry_delivery/tests/`             | `registry_delivery_boundary_test.cpp`      | test      | test_only      | boundary test                       | Ensures no registry internals owned |

---

## 9. Candidate Public Surface Matrix

|          Record ID | Candidate Public Surface                                     | Owner                                                | Allowed External Consumers                      | Forbidden Use                            |
| -----------------: | ------------------------------------------------------------ | ---------------------------------------------------- | ----------------------------------------------- | ---------------------------------------- |
| ASDT-FS-007-PS-001 | `policy_types/*.hpp`                                         | `ecosystem_governance/policy_types/`                 | `log_level_api`, `write_side` policy assignment | Policy source ownership                  |
| ASDT-FS-007-PS-002 | `receiver_ports/log_level_api/*`                             | `ecosystem_governance/receiver_ports/log_level_api/` | `log_level_api/policy_assignment/`              | API behavior execution                   |
| ASDT-FS-007-PS-003 | `receiver_ports/write_side/*`                                | `ecosystem_governance/receiver_ports/write_side/`    | `write_side/policy_assignment/`                 | Runtime execution                        |
| ASDT-FS-007-PS-004 | `content/content.hpp`                                        | `log_level_api/content/`                             | API preparation components                      | Treating raw content as envelope         |
| ASDT-FS-007-PS-005 | `envelope/log_level_envelope.hpp`                            | `log_level_api/envelope/`                            | API bridge, write-side admission                | Treating envelope as actor               |
| ASDT-FS-007-PS-006 | `envelope/views/*`                                           | `log_level_api/envelope/`                            | bridge, tests, diagnostics                      | Mutation authority                       |
| ASDT-FS-007-PS-007 | `write_side_bridge/carriers/*`                               | `log_level_api/write_side_bridge/`                   | write-side communication boundary               | Slot/container internals                 |
| ASDT-FS-007-PS-008 | `slot/views/*`                                               | `write_side/slot/`                                   | container/moderator/diagnostic consumers        | Direct slot mutation                     |
| ASDT-FS-007-PS-009 | `slots_container/views/*`                                    | `write_side/slots_container/`                        | moderator, round manager, bridge-safe surfaces  | Container internals leakage              |
| ASDT-FS-007-PS-010 | `waiting_list/carriers/queue_container_identifier.hpp`       | `write_side/waiting_list/`                           | round manager, reference precalculator          | Envelope storage                         |
| ASDT-FS-007-PS-011 | `reference_precalculator/carriers/*`                         | `write_side/reference_precalculator/`                | round manager, bridge surfaces                  | Registry identity ownership              |
| ASDT-FS-007-PS-012 | `dispatcher/outbound_adapters/registry_delivery_adapter.hpp` | `write_side/dispatcher/`                             | registry delivery boundary                      | Registry internals                       |
| ASDT-FS-007-PS-013 | `communications/registry_delivery/carriers/*`                | `write_side/communications/registry_delivery/`       | dispatcher, downstream adapter boundary         | Persistence proof or lifecycle ownership |

---

## 10. Candidate Private Surface Matrix

|            Record ID | Private Surface Pattern          | Owner                           | Forbidden External Dependents           |
| -------------------: | -------------------------------- | ------------------------------- | --------------------------------------- |
| ASDT-FS-007-PRIV-001 | `*/detail/*.hpp`                 | nearest semantic owner          | all external folders                    |
| ASDT-FS-007-PRIV-002 | `slot/state/*.hpp`               | `write_side/slot/`              | cross-domain consumers                  |
| ASDT-FS-007-PRIV-003 | `slots_container/state/*.hpp`    | `write_side/slots_container/`   | log-level API bridge                    |
| ASDT-FS-007-PRIV-004 | `round_manager/state/*.hpp`      | `write_side/round_manager/`     | log-level API bridge                    |
| ASDT-FS-007-PRIV-005 | `dispatcher/state/*.hpp`         | `write_side/dispatcher/`        | downstream registry                     |
| ASDT-FS-007-PRIV-006 | `policy_assignment/detail/*.hpp` | nearest policy assignment owner | policy source, external consumers       |
| ASDT-FS-007-PRIV-007 | `communications/*/detail/*.hpp`  | boundary folder                 | external domains and downstream systems |

---

## 11. Forbidden Candidate Files

The following candidate files are explicitly rejected.

|           Record ID | Rejected File                                            | Reason                                                      |
| ------------------: | -------------------------------------------------------- | ----------------------------------------------------------- |
| ASDT-FS-007-REJ-001 | `utils.hpp`                                              | Generic catch-all                                           |
| ASDT-FS-007-REJ-002 | `helpers.hpp`                                            | Hides local ownership                                       |
| ASDT-FS-007-REJ-003 | `common.hpp`                                             | Avoids declaring shared semantic owner                      |
| ASDT-FS-007-REJ-004 | `types.hpp`                                              | Too generic; use carrier/state/view/handle                  |
| ASDT-FS-007-REJ-005 | `models.hpp`                                             | Too generic; use carrier or state                           |
| ASDT-FS-007-REJ-006 | `interfaces.hpp`                                         | Use hosted ports, outbound adapters, or justified contracts |
| ASDT-FS-007-REJ-007 | `impl.hpp`                                               | Use `detail/<specific_name>.hpp`                            |
| ASDT-FS-007-REJ-008 | `message_broker.hpp`                                     | Violates Queue-as-Container doctrine                        |
| ASDT-FS-007-REJ-009 | `registry_storage_owner.hpp`                             | Violates downstream registry non-ownership                  |
| ASDT-FS-007-REJ-010 | `downstream_query_manager.hpp`                           | Violates downstream query exclusion                         |
| ASDT-FS-007-REJ-011 | `global_lifecycle_controller.hpp`                        | Violates bounded subsystem scope                            |
| ASDT-FS-007-REJ-012 | `envelope_assembler/detail` included by write-side files | Violates private detail boundary                            |
| ASDT-FS-007-REJ-013 | `slot/detail` included by log-level API files            | Violates write-side internal boundary                       |

---

## 12. Implementation Backlog Seeds

This file inventory suggests the following implementation backlog seeds.

These are not final tickets.

They are implementation-readiness candidates.

|          Record ID | Backlog Seed                                    | Source Candidate Files                                               | Implementation Meaning                       |
| -----------------: | ----------------------------------------------- | -------------------------------------------------------------------- | -------------------------------------------- |
| ASDT-FS-007-BL-001 | Establish policy type headers                   | `policy_types/*.hpp`                                                 | Define minimal policy vocabulary carriers    |
| ASDT-FS-007-BL-002 | Establish Log Level Envelope carrier            | `envelope/log_level_envelope.hpp` and envelope parts                 | Define central carrier structure             |
| ASDT-FS-007-BL-003 | Establish content carrier and view              | `content/content.hpp`, `content_view.hpp`                            | Define pre-envelope material                 |
| ASDT-FS-007-BL-004 | Establish validator variants                    | `validator.hpp`, `plain_validator.hpp`, `policy_bound_validator.hpp` | Define validation component surfaces         |
| ASDT-FS-007-BL-005 | Establish timestamp and metadata preparation    | timestamp and metadata candidate files                               | Define preparation components                |
| ASDT-FS-007-BL-006 | Establish envelope assembler variants           | assembler candidate files                                            | Define plain and validator-composed assembly |
| ASDT-FS-007-BL-007 | Establish write-side bridge carriers            | placement request, handle, signal                                    | Bridge API and write-side safely             |
| ASDT-FS-007-BL-008 | Establish slot and slots-container primitives   | slot/container candidate files                                       | Runtime placement primitives                 |
| ASDT-FS-007-BL-009 | Establish waiting-list identifier model         | waiting-list candidate files                                         | Queue-container identifier circulation       |
| ASDT-FS-007-BL-010 | Establish moderator and bundle agent skeletons  | moderator/bundle files                                               | Runtime preparation and scaling topology     |
| ASDT-FS-007-BL-011 | Establish round manager skeletons               | round manager files                                                  | Writing and delivery round coordination      |
| ASDT-FS-007-BL-012 | Establish reference precalculator               | reference candidate files                                            | Proactive reference calculation              |
| ASDT-FS-007-BL-013 | Establish dispatcher boundary                   | dispatcher files                                                     | Final outbound actor                         |
| ASDT-FS-007-BL-014 | Establish registry-delivery boundary            | registry delivery communication files                                | Handoff without registry ownership           |
| ASDT-FS-007-BL-015 | Establish local tests alongside first skeletons | all local `tests/` candidates                                        | Behavior-first verification                  |

---

## 13. Validation Handoff to ASDT-FS-008

`ASDT-FS-008_File_Inventory_Validation_Matrix.md` must validate this inventory against:

|          Record ID | Validation Area            | Required Check                                                        |
| -----------------: | -------------------------- | --------------------------------------------------------------------- |
| ASDT-FS-007-VH-001 | Ownership                  | Every file has a folder owner                                         |
| ASDT-FS-007-VH-002 | Role                       | Every file has a declared role                                        |
| ASDT-FS-007-VH-003 | Visibility                 | Every file has visibility                                             |
| ASDT-FS-007-VH-004 | Derivation                 | Every file derives from folder ownership                              |
| ASDT-FS-007-VH-005 | Detail Privacy             | No external dependency on `detail/`                                   |
| ASDT-FS-007-VH-006 | State Privacy              | No uncontrolled cross-boundary state dependency                       |
| ASDT-FS-007-VH-007 | Downstream Exclusion       | No registry/database/query ownership                                  |
| ASDT-FS-007-VH-008 | Queue Doctrine             | No message-broker semantics                                           |
| ASDT-FS-007-VH-009 | Actor/Object Separation    | Carriers do not become actors                                         |
| ASDT-FS-007-VH-010 | Port/Adapter Separation    | Ports and adapters remain distinct                                    |
| ASDT-FS-007-VH-011 | Generic File Rejection     | No `utils`, `helpers`, `common`, `types`, or `models` catch-all files |
| ASDT-FS-007-VH-012 | Implementation Prematurity | No final class/function signatures frozen here                        |

---

## 14. Freeze Status

This file inventory is not frozen.

It is ready for validation.

The next document must not add more candidate files unless validation reveals a missing architectural owner.

The next document is:

```text
ASDT-FS-008_File_Inventory_Validation_Matrix.md
```

After validation, the sequence must proceed to:

```text
ASDT-FS-009_Implementation_Readiness_Cutover.md
```

`ASDT-FS-009` must decide which candidate files become:

1. immediate implementation skeletons,
2. deferred implementation candidates,
3. rejected candidates,
4. documentation-only artifacts,
5. test-first artifacts,
6. C++ abstraction derivation inputs.

---

## 15. Summary

This document provides the first candidate file inventory for the Assembler System Digital Twin Filesystem.

The main conclusions are:

1. files derive from accepted folder ownership,
2. every candidate file has an owner, role, visibility, and derivation source,
3. public surfaces are limited to carriers, views, handles, ports, adapters, and justified contracts,
4. `detail/` remains private,
5. state remains local unless exposed through views or handles,
6. policy assignment does not own policy source lifecycle,
7. queue/container files must not become message broker files,
8. dispatcher and registry-delivery files must not own downstream registry internals,
9. final C++ class/function/include decisions remain deferred,
10. this inventory is ready for validation in `ASDT-FS-008`.

