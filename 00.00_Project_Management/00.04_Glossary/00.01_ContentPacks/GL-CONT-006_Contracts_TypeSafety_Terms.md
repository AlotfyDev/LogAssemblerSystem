
# GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-006-DOC-001 | Pack Name | GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack |
| GL-CONT-006-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-006-DOC-003 | Project | Assembler System |
| GL-CONT-006-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-006-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-006-DOC-006 | Language | English |
| GL-CONT-006-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002, GL-CONT-003, GL-CONT-004, GL-CONT-005 |
| GL-CONT-006-DOC-008 | Scope | Contract vocabulary, typed contract vocabulary, template/CRTP direction terms, compile-time discipline, canonical contract families |
| GL-CONT-006-DOC-009 | Excluded From This Pack | Final C++ interfaces, final class hierarchy, final traits implementation, final template code, final processing units, final package layout |
| GL-CONT-006-DOC-010 | Enables | GL-CONT-007, GL-CONT-008, GL-CONT-009, C++ abstraction derivation, template/CRTP architecture, processing-unit derivation, compliance matrix derivation |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for contracts, typed contracts, template contracts, type-safety terminology, and contract families in the Assembler System.

It answers the question:

```text
How does the Assembler System name and govern contracts before those contracts
are represented as C++ interfaces, traits, templates, CRTP bases, static checks,
or concrete processing units?
````

The pack protects the architecture from premature implementation.

It ensures that contracts remain architectural governance instruments before they become code artifacts.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`,
4. `GL-CONT-003 — Internal Actors and Delegated Entities Pack`,
5. `GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack`,
6. `GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack`.

It precedes:

1. `GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack`,
2. `GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack`,
3. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`,
4. `GL-CONT-010 — C++ Implementation Direction, Semantic Domains, and Future Derivation Terms Pack`.

### 2.3 Pack-Level Contract Rule

```text id="gl-cont-006-contract-rule"
Contract = architectural law before interface, class, trait, template,
concept-like construct, CRTP base, validation routine, or processing unit.
```

### 2.4 Pack-Level Type-Safety Rule

```text id="gl-cont-006-type-safety-rule"
Type safety must preserve architectural meaning.
It must not become a cosmetic C++ naming convention detached from contracts,
responsibilities, obligations, boundaries, carriers, or runtime states.
```

### 2.5 Pack-Level Template Rule

```text id="gl-cont-006-template-rule"
Templates and CRTP express reusable static abstraction patterns after contracts
are understood and before concrete processing units are derived.
```

---

## 3. Term Inventory

|           Record ID | Term ID    | Canonical Term                         | Family            | Category                                     | Ownership Scope                     | Entry Maturity    |
| ------------------: | ---------- | -------------------------------------- | ----------------- | -------------------------------------------- | ----------------------------------- | ----------------- |
| GL-CONT-006-INV-001 | GL-CON-001 | Contract                               | CON               | contract / doctrine                          | governed                            | canonical_full    |
| GL-CONT-006-INV-002 | GL-CON-002 | Typed Contract                         | CON / CPP         | contract / implementation_direction          | governed                            | canonical_full    |
| GL-CONT-006-INV-003 | GL-CON-003 | Template Contract                      | CON / CPP         | contract / implementation_direction          | future_derivation                   | canonical_full    |
| GL-CONT-006-INV-004 | GL-CON-004 | Contract Family                        | CON               | contract_family                              | governed                            | canonical_full    |
| GL-CONT-006-INV-005 | GL-CON-005 | Ingress Contract Family                | CON               | contract_family                              | assembler_owned                     | canonical_full    |
| GL-CONT-006-INV-006 | GL-CON-006 | Policy / Ecosystem Contract Family     | CON / POL         | contract_family                              | assembler_owned / external_facing   | canonical_full    |
| GL-CONT-006-INV-007 | GL-CON-007 | Metadata / Preparation Contract Family | CON               | contract_family                              | assembler_owned                     | canonical_full    |
| GL-CONT-006-INV-008 | GL-CON-008 | Operational / Scaling Contract Family  | CON / RUN         | contract_family                              | assembler_owned / external_facing   | canonical_full    |
| GL-CONT-006-INV-009 | GL-CON-009 | Registry / Dispatcher Contract Family  | CON / EXC         | contract_family                              | assembler_owned / downstream_facing | canonical_full    |
| GL-CONT-006-INV-010 | GL-CON-010 | Envelope Carrier Contract Family       | CON / OBJ         | contract_family                              | assembler_owned                     | canonical_full    |
| GL-CONT-006-INV-011 | GL-CON-011 | Exclusion Contract Family              | CON / EXC / GUARD | contract_family / anti_collapse_guard        | governed                            | canonical_full    |
| GL-CONT-006-INV-012 | GL-CON-012 | Runtime State Contract Family          | CON / RUN         | contract_family                              | assembler_owned                     | canonical_full    |
| GL-CONT-006-INV-013 | GL-CPP-001 | Contract Trait                         | CPP / CON         | implementation_direction                     | future_derivation                   | canonical_partial |
| GL-CONT-006-INV-014 | GL-CPP-002 | Type Marker                            | CPP / CON         | implementation_direction                     | future_derivation                   | canonical_partial |
| GL-CONT-006-INV-015 | GL-CPP-003 | Compile-Time Discipline                | CPP / CON         | implementation_direction / doctrine          | governed                            | canonical_full    |
| GL-CONT-006-INV-016 | GL-CPP-004 | Template Abstraction Layer             | CPP / CON         | implementation_direction / future_derivation | future_derivation                   | canonical_full    |
| GL-CONT-006-INV-017 | GL-CPP-005 | CRTP Abstraction                       | CPP / CON         | implementation_direction / future_derivation | future_derivation                   | canonical_full    |
| GL-CONT-006-INV-018 | GL-CON-013 | Contract Compliance                    | CON / TRC         | validation_concept                           | governed                            | canonical_partial |
| GL-CONT-006-INV-019 | GL-CON-014 | Contract Violation                     | CON / GUARD       | validation_concept / anti_collapse_guard     | governed                            | canonical_partial |
| GL-CONT-006-INV-020 | GL-CON-015 | Contract-to-Capability Derivation      | CON / DER / TRC   | future_derivation                            | governed / future                   | canonical_full    |

---

## 4. Canonical Term Entries

---

### GL-CON-001 — Contract

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-CON-001          |
| Canonical Term  | Contract            |
| Family          | CON                 |
| Category        | contract / doctrine |
| Ownership Scope | governed            |
| Entry Maturity  | canonical_full      |
| Evidence Status | direct / derived    |

#### Definition

A Contract is an architectural law that governs an interaction, responsibility, boundary surface, carrier behavior, runtime state, preparation path, handoff condition, or exclusion rule inside the Assembler System.

A Contract defines what must be true before implementation artifacts are derived.

#### Architectural Role

Contract is the central governance term for typed system behavior.

A Contract may govern:

1. ingress admission,
2. envelope assembly,
3. metadata preparation,
4. timestamp stabilization,
5. policy assignment,
6. runtime queue/container coordination,
7. dispatch readiness,
8. dispatcher-mediated handoff,
9. authority exclusion,
10. downstream non-ownership.

A Contract may later be represented by C++ interfaces, traits, templates, static checks, validation routines, or CRTP abstractions.

However, those are representations.

They are not the original meaning of the Contract.

#### Must Not Be Confused With

1. C++ interface by default.
2. Concrete class.
3. Template by default.
4. Runtime algorithm.
5. Validation function only.
6. API endpoint only.
7. Package boundary.
8. Processing unit.

#### Valid Usage

* “Contracts are architectural laws before implementation artifacts.”
* “Ingress Contract Family governs corrected ingress behavior.”
* “A Contract may later be represented by a template trait.”

#### Invalid Usage

* “A Contract is just a C++ interface.”
* “A Contract is automatically a class.”
* “A Contract is only a runtime validator.”
* “A Contract can be invented after a processing unit already exists.”

#### Related Terms

* GL-CON-002 — Typed Contract
* GL-CON-003 — Template Contract
* GL-CON-004 — Contract Family
* GL-CPP-001 — Contract Trait
* GL-CPP-003 — Compile-Time Discipline
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type        | Source                                                                                                                            |
| ------------------ | --------------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-TYPE-003 states that a contract shall be treated as an architectural law before interface, class, trait, or template artifact. |
| ProjectOverview.md | Defines contracts as typed laws governing interactions.                                                                           |
| Roadmap Basis      | Roadmap ordering doctrine places contracts before templates and abstractions before processing units.                             |

---

### GL-CON-002 — Typed Contract

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-CON-002                          |
| Canonical Term  | Typed Contract                      |
| Family          | CON / CPP                           |
| Category        | contract / implementation_direction |
| Ownership Scope | governed                            |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

A Typed Contract is a Contract whose architectural meaning is intended to be preserved through explicit type discipline.

In the Assembler System, Typed Contracts support C++17-oriented compile-time and structural correctness for assembler-facing interactions.

#### Architectural Role

Typed Contract binds architectural contract meaning to type-safe representation.

It may govern:

1. accepted content type,
2. envelope carrier type,
3. metadata block type,
4. timestamp block type,
5. policy assignment relation,
6. queue container identifier,
7. dispatch eligibility state,
8. handoff evidence shape.

A Typed Contract is still a Contract first.

It is not automatically a final C++ type.

#### Must Not Be Confused With

1. Type alias only.
2. C++ class only.
3. Template parameter only.
4. Serialization schema only.
5. Runtime check only.
6. Naming convention.

#### Valid Usage

* “Typed Contracts preserve assembler-facing interaction meaning.”
* “Envelope carrier behavior should be governed through typed contracts.”
* “Typed Contract may later be represented by traits or templates.”

#### Invalid Usage

* “Typed Contract means any struct with fields.”
* “Typed Contract is only a compile-time trick.”
* “Typed Contract can ignore architectural responsibilities.”
* “Typed Contract replaces source traceability.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-003 — Template Contract
* GL-CPP-001 — Contract Trait
* GL-CPP-002 — Type Marker
* GL-CPP-003 — Compile-Time Discipline

#### Source Trace

| Source Type       | Source                                                                                      |
| ----------------- | ------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | SG-TYPE-001 requires assembler-facing interactions to be expressed through typed contracts. |
| README Basis      | C++ identity includes strong type boundaries, compile-time discipline, templates, and CRTP. |
| VisionAndScope.md | Long-term implementation vision includes C++17, header-only-first, templates, and CRTP.     |

---

### GL-CON-003 — Template Contract

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-CON-003                          |
| Canonical Term  | Template Contract                   |
| Family          | CON / CPP                           |
| Category        | contract / implementation_direction |
| Ownership Scope | future_derivation                   |
| Entry Maturity  | canonical_full                      |
| Evidence Status | derived                             |

#### Definition

A Template Contract is a Contract intended for future representation through C++ template-based abstraction.

It captures reusable compile-time structure after architectural contract meaning is stable.

#### Architectural Role

Template Contract bridges architectural contracts and template/CRTP abstraction design.

It may support:

1. envelope specialization,
2. policy-bound behavior,
3. metadata preparation patterns,
4. timestamp stabilization patterns,
5. queue/container runtime state patterns,
6. dispatch eligibility patterns,
7. exclusion guard patterns.

Template Contract does not mean final template code has already been defined.

#### Must Not Be Confused With

1. Final C++ template implementation.
2. CRTP base by default.
3. Concrete processing unit.
4. Generic utility template.
5. Type alias.
6. Code-first interface.

#### Valid Usage

* “Template Contract prepares a contract for future C++ template representation.”
* “Template Contract follows architectural contract definition.”
* “Template Contracts may support reusable static abstraction patterns.”

#### Invalid Usage

* “Template Contract is already the final template file.”
* “Template Contract can be created without a contract family.”
* “Template Contract bypasses responsibility derivation.”
* “Template Contract automatically creates a processing unit.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-002 — Typed Contract
* GL-CPP-004 — Template Abstraction Layer
* GL-CPP-005 — CRTP Abstraction
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type       | Source                                                                                                                      |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | SG-TYPE-005 states Templates and CRTP should express reusable static abstraction patterns before concrete processing units. |
| Roadmap Basis     | Roadmap ordering doctrine places contracts before templates and abstractions before processing units.                       |
| VisionAndScope.md | Long-term implementation vision includes template-based abstraction layers and CRTP-based static polymorphism.              |

---

### GL-CON-004 — Contract Family

| Field           | Value            |
| --------------- | ---------------- |
| Term ID         | GL-CON-004       |
| Canonical Term  | Contract Family  |
| Family          | CON              |
| Category        | contract_family  |
| Ownership Scope | governed         |
| Entry Maturity  | canonical_full   |
| Evidence Status | direct / derived |

#### Definition

A Contract Family is a group of related Contracts governing a coherent architectural concern.

Contract Families organize contracts by semantic responsibility, not by filesystem folder or final package layout.

#### Architectural Role

Contract Family gives structure to contract governance.

The canonical Contract Families include:

1. Ingress Contract Family,
2. Policy / Ecosystem Contract Family,
3. Metadata / Preparation Contract Family,
4. Operational / Scaling Contract Family,
5. Registry / Dispatcher Contract Family,
6. Envelope Carrier Contract Family,
7. Exclusion Contract Family,
8. Runtime State Contract Family.

A Contract Family may later enable traits, templates, abstract layers, processing units, tests, and compliance checks.

#### Must Not Be Confused With

1. Package by default.
2. Namespace by default.
3. Folder by default.
4. C++ module by default.
5. Class hierarchy by default.
6. Runtime subsystem by default.

#### Valid Usage

* “Ingress Contract Family governs corrected ingress flow.”
* “Runtime State Contract Family governs queue/container state.”
* “Contract Families precede template traits.”

#### Invalid Usage

* “Contract Family means package directory.”
* “Contract Family automatically creates a class hierarchy.”
* “Contract Family is just a CMake target.”
* “Contract Family can ignore architectural taxonomy.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-005 — Ingress Contract Family
* GL-CON-006 — Policy / Ecosystem Contract Family
* GL-CON-012 — Runtime State Contract Family
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type        | Source                                                                                                                                                                                      |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Lists canonical contract/template families.                                                                                                                                                 |
| SYSTEM_GOALS.md    | SG-TYPE-002 requires contract families to govern ingress, policy/ecosystem, metadata/preparation, operational/scaling, registry/dispatcher, envelope carrier, exclusion, and runtime state. |
| GL-CONT-000        | Category model defines contract_family.                                                                                                                                                     |

---

### GL-CON-005 — Ingress Contract Family

| Field           | Value                   |
| --------------- | ----------------------- |
| Term ID         | GL-CON-005              |
| Canonical Term  | Ingress Contract Family |
| Family          | CON                     |
| Category        | contract_family         |
| Ownership Scope | assembler_owned         |
| Entry Maturity  | canonical_full          |
| Evidence Status | direct / derived        |

#### Definition

The Ingress Contract Family is the group of Contracts governing the corrected ingress path from consuming-side typed entry through envelope assembly and assembler ingress-port admission.

#### Architectural Role

Ingress Contract Family governs:

1. Level API as consuming-side typed entry façade,
2. Envelope Assembler production of Log Level Envelope,
3. composition of Validator, Metadata Injector, and Timestamp Stabilizer where required,
4. Assembler Ingress Port receiving Log Level Envelopes,
5. admission into a suitable Slot inside a target Queue Container.

The Ingress Contract Family prevents raw payloads from bypassing envelope assembly.

#### Must Not Be Confused With

1. Level API itself.
2. Envelope Assembler itself.
3. Assembler Ingress Port itself.
4. Raw payload submission path.
5. Queue Container itself.
6. Dispatcher handoff contract.

#### Valid Usage

* “Ingress Contract Family governs the corrected ingress flow.”
* “Assembler Ingress Port receives prepared envelopes under ingress contracts.”
* “Raw content must not replace Log Level Envelope in the ingress path.”

#### Invalid Usage

* “Ingress Contract Family means Assembler Ingress Port assembles envelopes.”
* “Ingress Contract Family allows raw payload runtime admission.”
* “Ingress Contract Family performs dispatch.”
* “Ingress Contract Family owns downstream lifecycle.”

#### Related Terms

* GL-EXT-001 — Level API
* GL-ENT-001 — Envelope Assembler
* GL-BND-006 — Assembler Ingress Port
* GL-OBJ-001 — Log Level Envelope
* GL-RUN-005 — Slot
* GL-RUN-001 — Queue Container

#### Source Trace

| Source Type        | Source                                                                                                                                        |
| ------------------ | --------------------------------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Corrected ingress flow defines Level API, Envelope Assembler, Log Level Envelope, Assembler Ingress Port, Slot, and Queue Container sequence. |
| SYSTEM_GOALS.md    | SG-ING-001 through SG-ING-005 define corrected ingress goals.                                                                                 |
| GL-CONT-002        | Assembler Ingress Port is a receiving contract port, not the envelope producer.                                                               |
| GL-CONT-003        | Envelope Assembler produces Log Level Envelope.                                                                                               |

---

### GL-CON-006 — Policy / Ecosystem Contract Family

| Field           | Value                              |
| --------------- | ---------------------------------- |
| Term ID         | GL-CON-006                         |
| Canonical Term  | Policy / Ecosystem Contract Family |
| Family          | CON / POL                          |
| Category        | contract_family                    |
| Ownership Scope | assembler_owned / external_facing  |
| Entry Maturity  | canonical_full                     |
| Evidence Status | direct / derived                   |

#### Definition

The Policy / Ecosystem Contract Family is the group of Contracts governing administrative, ecosystem, policy-source, and policy-assignment interactions that affect assembler-side behavior.

#### Architectural Role

This family governs:

1. Administrative / Ecosystem Port input,
2. Policy Registry / Policy Source interaction,
3. Policy Object receipt or reference,
4. PolicyAssigner assignment semantics,
5. eligible policy-consuming components,
6. policy-governed mechanisms,
7. exclusion of Metadata Injector from policy-hosting semantics.

It preserves the distinction between policy material, policy assignment, policy-consuming components, policy hosts, and policy-governed effects.

#### Must Not Be Confused With

1. Policy Object itself.
2. PolicyAssigner itself.
3. Policy Registry / Policy Source itself.
4. Metadata Directive Source.
5. Metadata Injector.
6. Consuming ingress.
7. Downstream policy lifecycle.

#### Valid Usage

* “Policy / Ecosystem Contract Family governs policy assignment semantics.”
* “Policy Object remains distinct from policy-consuming component.”
* “Metadata Injector is not policy-hosted under this family.”

#### Invalid Usage

* “Policy / Ecosystem Contract Family turns Metadata Injector into a policy host.”
* “Policy / Ecosystem Contract Family means PolicyAssigner is the policy source.”
* “Policy / Ecosystem Contract Family handles raw content ingress.”
* “Policy / Ecosystem Contract Family owns downstream policy lifecycle.”

#### Related Terms

* GL-BND-007 — Administrative / Ecosystem Port
* GL-EXT-003 — Policy Registry / Policy Source
* GL-OBJ-004 — Policy Object
* GL-OBJ-005 — Policy Assignment
* GL-ENT-006 — PolicyAssigner
* GL-ENT-011 — Policy-Consuming Component

#### Source Trace

| Source Type        | Source                                                                                                                          |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines PolicyAssigner and Policy Registry / Policy Source separation.                                                          |
| SYSTEM_GOALS.md    | Policy governance goals preserve Policy Object, PolicyAssigner, policy-consuming component, and Metadata Injector distinctions. |
| GL-CONT-003        | PolicyAssigner mediates assignment; Metadata Injector is not policy-hosted.                                                     |
| GL-CONT-004        | Policy Object and Policy Assignment are governed objects, not actors.                                                           |

---

### GL-CON-007 — Metadata / Preparation Contract Family

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-CON-007                             |
| Canonical Term  | Metadata / Preparation Contract Family |
| Family          | CON                                    |
| Category        | contract_family                        |
| Ownership Scope | assembler_owned                        |
| Entry Maturity  | canonical_full                         |
| Evidence Status | direct / derived                       |

#### Definition

The Metadata / Preparation Contract Family is the group of Contracts governing assembler-side preparation of accepted content or envelopes, including metadata preparation and timestamp stabilization.

#### Architectural Role

This family governs:

1. metadata directive use,
2. schema/directive-governed metadata preparation,
3. Metadata Injector role,
4. timestamp semantics,
5. Timestamp Stabilizer role,
6. preparation state before dispatch eligibility,
7. preservation of metadata/policy separation.

It ensures that preparation semantics remain assembler-side and do not become downstream query interpretation.

#### Must Not Be Confused With

1. Policy / Ecosystem Contract Family.
2. Policy hosting.
3. Downstream metadata lifecycle.
4. Downstream query timestamp interpretation.
5. Storage schema ownership.
6. Raw payload admission.

#### Valid Usage

* “Metadata / Preparation Contract Family governs Metadata Injector behavior.”
* “Timestamp stabilization belongs to preparation contracts.”
* “Metadata preparation is schema/directive-governed, not policy-hosted.”

#### Invalid Usage

* “Metadata / Preparation Contract Family makes Metadata Injector a policy host.”
* “Metadata / Preparation Contract Family owns downstream registry metadata lifecycle.”
* “Metadata / Preparation Contract Family executes read-side query interpretation.”
* “Metadata / Preparation Contract Family replaces ingress contracts.”

#### Related Terms

* GL-ENT-004 — Metadata Injector
* GL-ENT-005 — Timestamp Stabilizer
* GL-EXT-004 — Metadata Directive Source
* GL-OBJ-013 — Envelope Metadata Block
* GL-OBJ-014 — Envelope Timestamp Block

#### Source Trace

| Source Type     | Source                                                                                                                   |
| --------------- | ------------------------------------------------------------------------------------------------------------------------ |
| SYSTEM_GOALS.md | Metadata and timestamp goals distinguish metadata preparation from policy ownership and downstream query interpretation. |
| GL-CONT-003     | Metadata Injector is schema/directive-governed, not policy-hosted.                                                       |
| GL-CONT-004     | Envelope Metadata Block and Envelope Timestamp Block are governed object terms.                                          |

---

### GL-CON-008 — Operational / Scaling Contract Family

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-CON-008                            |
| Canonical Term  | Operational / Scaling Contract Family |
| Family          | CON / RUN                             |
| Category        | contract_family                       |
| Ownership Scope | assembler_owned / external_facing     |
| Entry Maturity  | canonical_full                        |
| Evidence Status | direct / derived                      |

#### Definition

The Operational / Scaling Contract Family is the group of Contracts governing operational directives, scaling directives, pause/drain/activate-like behavior, and runtime coordination controls that affect assembler-side queue/container behavior.

#### Architectural Role

This family governs how operational inputs may influence:

1. Queue Bundle Agent behavior,
2. Single Queue Moderator behavior,
3. Writing / Feeding Round Manager behavior,
4. Dispatching / Delivery Round Manager behavior,
5. Queue Container readiness,
6. waiting-list coordination,
7. runtime moderation.

It must preserve separation between external operational directive sources and internal runtime actors.

#### Must Not Be Confused With

1. Scaling / Operational Directive Source itself.
2. Queue Bundle Agent itself.
3. Queue Container itself.
4. Message broker control plane.
5. Downstream lifecycle management.
6. Registry delivery authority.

#### Valid Usage

* “Operational / Scaling Contract Family governs assembler-side runtime control input.”
* “Scaling directives may affect queue/container coordination.”
* “Operational contracts do not make queue actors downstream lifecycle owners.”

#### Invalid Usage

* “Operational / Scaling Contract Family is a message broker control plane.”
* “Operational / Scaling Contract Family owns downstream storage lifecycle.”
* “Operational / Scaling Contract Family is the Scaling / Operational Directive Source itself.”
* “Operational / Scaling Contract Family replaces Runtime State Contract Family.”

#### Related Terms

* GL-EXT-005 — Scaling / Operational Directive Source
* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-RUN-014 — Runtime Coordination

#### Source Trace

| Source Type        | Source                                                                                           |
| ------------------ | ------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines Scaling / Operational Directive Source as external and queue/runtime actors as internal. |
| SYSTEM_GOALS.md    | Queue runtime goals preserve queue-as-container coordination and runtime actor separation.       |
| GL-CONT-005        | Runtime terms define waiting lists, queue identifiers, queue moderation, and round coordination. |

---

### GL-CON-009 — Registry / Dispatcher Contract Family

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-CON-009                            |
| Canonical Term  | Registry / Dispatcher Contract Family |
| Family          | CON / EXC                             |
| Category        | contract_family                       |
| Ownership Scope | assembler_owned / downstream_facing   |
| Entry Maturity  | canonical_full                        |
| Evidence Status | direct / derived                      |

#### Definition

The Registry / Dispatcher Contract Family is the group of Contracts governing dispatcher-mediated handoff through the Registry / Delivery Port toward downstream preservation or query destinations.

#### Architectural Role

This family governs:

1. Dispatcher finality,
2. handoff eligibility,
3. Registry / Delivery Port usage,
4. downstream-facing transfer,
5. handoff evidence,
6. authority closure,
7. no downstream registry internal ownership.

It preserves the rule:

```text id="gl-con-009-dispatcher-rule"
Dispatcher = final assembler-side outbound actor.
Registry / Delivery Port = outbound contract surface.
Downstream Registry = not assembler-owned.
```

#### Must Not Be Confused With

1. Dispatcher itself.
2. Registry / Delivery Port itself.
3. downstream registry implementation.
4. storage engine.
5. query subsystem.
6. Runtime Round Manager.
7. Exclusion Contract Family by itself.

#### Valid Usage

* “Registry / Dispatcher Contract Family governs final outbound handoff.”
* “Dispatcher remains the final assembler-side actor.”
* “Registry / Delivery Port is the outbound contract surface.”

#### Invalid Usage

* “Registry / Dispatcher Contract Family owns downstream registry internals.”
* “Registry / Delivery Port replaces Dispatcher.”
* “Dispatching / Delivery Round Manager performs final handoff.”
* “Registry / Dispatcher Contract Family reopens assembler authority after handoff.”

#### Related Terms

* GL-ENT-002 — Dispatcher
* GL-BND-008 — Registry / Delivery Port
* GL-EXT-006 — Log Level Records Registry
* GL-OBJ-008 — Handoff Evidence
* GL-EXC-001 — Post-Handoff Non-Ownership
* GL-BND-004 — Authority Boundary

#### Source Trace

| Source Type     | Source                                                                           |
| --------------- | -------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Dispatcher and handoff goals preserve Dispatcher finality and authority closure. |
| GL-CONT-002     | Registry / Delivery Port is a port, not Dispatcher or registry implementation.   |
| GL-CONT-003     | Dispatcher is final assembler-side outbound actor.                               |
| GL-CONT-004     | Handoff Evidence supports auditability without downstream lifecycle ownership.   |

---

### GL-CON-010 — Envelope Carrier Contract Family

| Field           | Value                            |
| --------------- | -------------------------------- |
| Term ID         | GL-CON-010                       |
| Canonical Term  | Envelope Carrier Contract Family |
| Family          | CON / OBJ                        |
| Category        | contract_family                  |
| Ownership Scope | assembler_owned                  |
| Entry Maturity  | canonical_full                   |
| Evidence Status | direct / derived                 |

#### Definition

The Envelope Carrier Contract Family is the group of Contracts governing the Log Level Envelope as the authoritative assembler-side carrier object and runtime transport unit.

#### Architectural Role

This family governs:

1. envelope identity,
2. typed content binding,
3. metadata block binding,
4. timestamp block binding,
5. policy assignment relation,
6. queue/container admission relation,
7. dispatch eligibility state,
8. handoff trace material,
9. carrier/non-actor distinction.

It ensures that raw content cannot replace the Log Level Envelope as runtime transport.

#### Must Not Be Confused With

1. Log Level Envelope itself.
2. Envelope Assembler.
3. raw payload.
4. downstream registry record.
5. Dispatcher.
6. Queue Container.
7. storage schema.

#### Valid Usage

* “Envelope Carrier Contract Family governs envelope carrier semantics.”
* “Log Level Envelope remains carrier object, not actor.”
* “Envelope type specialization must preserve carrier doctrine.”

#### Invalid Usage

* “Envelope Carrier Contract Family allows raw payload handoff.”
* “Envelope Carrier Contract Family makes Log Level Envelope an actor.”
* “Envelope Carrier Contract Family is the Envelope Assembler.”
* “Envelope Carrier Contract Family defines downstream registry schema.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-003 — Carrier Object
* GL-OBJ-009 — Runtime Transport Unit
* GL-OBJ-012 — Envelope Identity
* GL-OBJ-013 — Envelope Metadata Block
* GL-OBJ-014 — Envelope Timestamp Block
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type       | Source                                                                                                                            |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | SG-LLE-001 and SG-LLE-002 require raw content not to replace Log Level Envelope and envelope to remain carrier object, not actor. |
| GL-CONT-004       | Log Level Envelope is authoritative carrier object and runtime transport unit.                                                    |
| VisionAndScope.md | Log Level Envelope is central to current vision and scope.                                                                        |

---

### GL-CON-011 — Exclusion Contract Family

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-CON-011                            |
| Canonical Term  | Exclusion Contract Family             |
| Family          | CON / EXC / GUARD                     |
| Category        | contract_family / anti_collapse_guard |
| Ownership Scope | governed                              |
| Entry Maturity  | canonical_full                        |
| Evidence Status | direct / derived                      |

#### Definition

The Exclusion Contract Family is the group of Contracts that define what the Assembler System must not own, perform, absorb, or collapse into.

#### Architectural Role

This family governs permanent non-ownership.

It prevents the Assembler System from becoming:

1. full logging system,
2. full messaging system,
3. message broker,
4. downstream registry,
5. database,
6. storage engine,
7. query engine,
8. network transport layer,
9. downstream lifecycle owner,
10. post-handoff mutation authority.

It also prevents category collapse, such as actor/port, carrier/actor, queue/broker, and handoff/lifecycle ownership collapse.

#### Must Not Be Confused With

1. Optional non-goal list.
2. Future backlog.
3. Implementation limitation.
4. Runtime error only.
5. Documentation preference.
6. Integration boundary.

#### Valid Usage

* “Exclusion Contract Family governs permanent non-ownership.”
* “Assembler authority closes after valid handoff.”
* “Queue must not become message broker.”

#### Invalid Usage

* “Exclusion Contract Family can be ignored in implementation.”
* “Exclusion Contract Family is only documentation.”
* “Exclusion Contract Family allows downstream mutation if convenient.”
* “Exclusion Contract Family is a future optional extension.”

#### Related Terms

* GL-EXC-001 — Post-Handoff Non-Ownership
* GL-BND-004 — Authority Boundary
* GL-BND-005 — Downstream Boundary
* GL-RUN-012 — Queue-as-Container Doctrine
* GL-CON-014 — Contract Violation

#### Source Trace

| Source Type       | Source                                                                                                                                    |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | Authority exclusion goals prohibit downstream registry, storage, query, mutation, replay, indexing, correction, and inspection ownership. |
| VisionAndScope.md | Permanent exclusions define what the Assembler must never own.                                                                            |
| GL-CONT-002       | Authority Boundary and Downstream Boundary define non-ownership after handoff.                                                            |
| GL-CONT-005       | Queue-as-Container Doctrine prevents queue/broker collapse.                                                                               |

---

### GL-CON-012 — Runtime State Contract Family

| Field           | Value                         |
| --------------- | ----------------------------- |
| Term ID         | GL-CON-012                    |
| Canonical Term  | Runtime State Contract Family |
| Family          | CON / RUN                     |
| Category        | contract_family               |
| Ownership Scope | assembler_owned               |
| Entry Maturity  | canonical_full                |
| Evidence Status | direct / derived              |

#### Definition

The Runtime State Contract Family is the group of Contracts governing assembler-side queue/container runtime state, slot placement, occupancy, waiting-list semantics, queue identifiers, runtime readiness, queue moderation, and round coordination.

#### Architectural Role

This family governs:

1. Queue Container,
2. Slot,
3. Envelope Slot Occupancy,
4. Slot Lifecycle State,
5. Waiting List,
6. Queue Container Identifier,
7. Queue Bundle,
8. Single Queue Container,
9. Runtime Readiness,
10. Queue Moderation,
11. Round Coordination.

It preserves the rule:

```text id="gl-con-012-runtime-rule"
Runtime state governs assembler-side placement and coordination.
It does not own downstream lifecycle.
```

#### Must Not Be Confused With

1. Message broker contract.
2. Storage persistence contract.
3. Downstream delivery contract.
4. Dispatcher finality contract.
5. Envelope lifecycle ownership.
6. Registry lifecycle schema.

#### Valid Usage

* “Runtime State Contract Family governs Slot and Envelope Slot Occupancy.”
* “Waiting Lists carry Queue Container Identifiers where applicable.”
* “Runtime state does not own downstream lifecycle.”

#### Invalid Usage

* “Runtime State Contract Family makes Queue Container a broker.”
* “Runtime State Contract Family stores downstream registry records.”
* “Runtime State Contract Family owns envelope lifecycle.”
* “Runtime State Contract Family replaces Registry / Dispatcher Contract Family.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-008 — Waiting List
* GL-RUN-011 — Queue Container Identifier
* GL-RUN-014 — Runtime Coordination

#### Source Trace

| Source Type       | Source                                                                                                                      |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-005       | Runtime vocabulary defines queue/container, slot, occupancy, waiting-list, and round terms.                                 |
| SYSTEM_GOALS.md   | Queue runtime goals require queue as container, waiting-list identifier semantics, and slot occupancy/lifecycle separation. |
| VisionAndScope.md | Queue-as-Container is part of current architectural vision.                                                                 |

---

### GL-CPP-001 — Contract Trait

| Field           | Value                    |
| --------------- | ------------------------ |
| Term ID         | GL-CPP-001               |
| Canonical Term  | Contract Trait           |
| Family          | CPP / CON                |
| Category        | implementation_direction |
| Ownership Scope | future_derivation        |
| Entry Maturity  | canonical_partial        |
| Evidence Status | derived                  |

#### Definition

A Contract Trait is a future C++ representation candidate that may encode aspects of a Contract or Contract Family as reusable compile-time metadata, constraints, or behavior-selection structure.

#### Architectural Role

Contract Trait is an implementation-direction term.

It may later support:

1. envelope specialization,
2. policy eligibility,
3. metadata capability declaration,
4. timestamp capability declaration,
5. queue container type constraints,
6. dispatch eligibility constraints,
7. exclusion guard mapping.

A Contract Trait is not the Contract itself.

It is a possible C++ representation of contract meaning.

#### Must Not Be Confused With

1. Contract itself.
2. Contract Family itself.
3. Final class hierarchy.
4. Runtime validator by default.
5. Processing unit.
6. Package boundary.

#### Valid Usage

* “Contract Trait may represent a contract at compile time.”
* “Contract Traits should derive from contract families.”
* “Traits must preserve architectural meaning.”

#### Invalid Usage

* “Contract Trait is the contract.”
* “Contract Trait can be invented without contract source.”
* “Contract Trait is automatically a processing unit.”
* “Contract Trait replaces responsibility traceability.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-002 — Typed Contract
* GL-CON-003 — Template Contract
* GL-CPP-002 — Type Marker
* GL-CPP-003 — Compile-Time Discipline

#### Source Trace

| Source Type       | Source                                                                                             |
| ----------------- | -------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | C++ abstraction layers should preserve contract meaning at compile time where appropriate.         |
| VisionAndScope.md | Long-term direction includes template-based abstraction layers and CRTP-based static polymorphism. |
| Roadmap Basis     | Contracts precede templates and template/CRTP abstraction precedes processing units.               |

---

### GL-CPP-002 — Type Marker

| Field           | Value                    |
| --------------- | ------------------------ |
| Term ID         | GL-CPP-002               |
| Canonical Term  | Type Marker              |
| Family          | CPP / CON                |
| Category        | implementation_direction |
| Ownership Scope | future_derivation        |
| Entry Maturity  | canonical_partial        |
| Evidence Status | derived                  |

#### Definition

A Type Marker is a future C++ representation candidate used to mark or distinguish architectural categories, contract participation, envelope types, policy eligibility, runtime state classes, or exclusion-guarded roles at compile time.

#### Architectural Role

Type Marker may support static distinction between:

1. carrier object and actor,
2. port and actor,
3. queue container and message broker,
4. envelope identity and queue container identifier,
5. policy object and policy-consuming component,
6. dispatcher and delivery port,
7. runtime readiness and dispatch eligibility.

Type Marker is a representation aid.

It must not create architectural meaning that does not exist in the glossary or contract model.

#### Must Not Be Confused With

1. Canonical term itself.
2. Runtime state.
3. Contract by itself.
4. Final class.
5. Serialization tag by default.
6. Database discriminator.

#### Valid Usage

* “Type Marker may preserve actor/carrier distinction.”
* “Type Marker may mark envelope carrier types.”
* “Type Markers must follow glossary categories.”

#### Invalid Usage

* “Type Marker invents new architecture.”
* “Type Marker replaces contract definition.”
* “Type Marker replaces source trace.”
* “Type Marker defines downstream registry schema.”

#### Related Terms

* GL-CPP-001 — Contract Trait
* GL-CON-002 — Typed Contract
* GL-CPP-003 — Compile-Time Discipline
* GL-OBJ-003 — Carrier Object
* GL-TRC-001 — Delegated Entity

#### Source Trace

| Source Type     | Source                                                                       |
| --------------- | ---------------------------------------------------------------------------- |
| GL-CONT-000     | Category integrity requires terms not silently change category.              |
| SYSTEM_GOALS.md | Type safety supports Log Level Envelope specialization and contract meaning. |
| GL-CONT-004     | Log Level Envelope is carrier object, not actor.                             |
| GL-CONT-005     | Queue Container Identifier is distinct from Envelope Identity.               |

---

### GL-CPP-003 — Compile-Time Discipline

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-CPP-003                          |
| Canonical Term  | Compile-Time Discipline             |
| Family          | CPP / CON                           |
| Category        | implementation_direction / doctrine |
| Ownership Scope | governed                            |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

Compile-Time Discipline is the C++ implementation direction requiring contract meaning, type categories, static distinctions, and reusable abstraction patterns to be preserved at compile time where appropriate.

#### Architectural Role

Compile-Time Discipline supports the Assembler System’s C++ write-side preparation kernel identity.

It may guide:

1. typed contract representation,
2. trait design,
3. type marker design,
4. template abstraction,
5. CRTP abstraction,
6. envelope specialization,
7. policy eligibility,
8. runtime state safety,
9. exclusion guard representation.

Compile-Time Discipline does not replace runtime validation where runtime validation is required.

#### Must Not Be Confused With

1. Eliminating all runtime checks.
2. C++ cleverness for its own sake.
3. Final implementation package.
4. Generic metaprogramming.
5. Premature optimization.
6. Build-system configuration.

#### Valid Usage

* “Compile-Time Discipline preserves contract meaning where appropriate.”
* “Compile-Time Discipline supports typed envelope specialization.”
* “Compile-Time Discipline must follow architectural contracts.”

#### Invalid Usage

* “Compile-Time Discipline means no runtime validation.”
* “Compile-Time Discipline is independent of contract families.”
* “Compile-Time Discipline means templates first, architecture later.”
* “Compile-Time Discipline can ignore boundary exclusions.”

#### Related Terms

* GL-CON-002 — Typed Contract
* GL-CON-003 — Template Contract
* GL-CPP-001 — Contract Trait
* GL-CPP-002 — Type Marker
* GL-CPP-004 — Template Abstraction Layer
* GL-CPP-005 — CRTP Abstraction

#### Source Trace

| Source Type       | Source                                                                                                                                  |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| README Basis      | C++ identity includes strong type boundaries, compile-time discipline, templates, and CRTP.                                             |
| SYSTEM_GOALS.md   | SG-TYPE-004 requires C++ abstraction layers to preserve contract meaning at compile time where appropriate.                             |
| VisionAndScope.md | Long-term implementation vision includes C++17, header-only-first, templates, CRTP, responsibility-derived processing units, and tests. |

---

### GL-CPP-004 — Template Abstraction Layer

| Field           | Value                                        |
| --------------- | -------------------------------------------- |
| Term ID         | GL-CPP-004                                   |
| Canonical Term  | Template Abstraction Layer                   |
| Family          | CPP / CON                                    |
| Category        | implementation_direction / future_derivation |
| Ownership Scope | future_derivation                            |
| Entry Maturity  | canonical_full                               |
| Evidence Status | direct / derived                             |

#### Definition

The Template Abstraction Layer is a future C++ abstraction layer that represents stable contract families and responsibility patterns through reusable template-based structures before concrete processing units are derived.

#### Architectural Role

Template Abstraction Layer sits between contract-family definition and concrete processing-unit derivation.

It may encode reusable patterns for:

1. envelope preparation,
2. policy-bound behavior,
3. metadata injection,
4. timestamp stabilization,
5. queue/container coordination,
6. runtime readiness,
7. dispatcher eligibility,
8. exclusion guards.

It is not a collection of final concrete units.

#### Must Not Be Confused With

1. Final implementation package.
2. Concrete processing unit layer.
3. Generic utilities folder.
4. Runtime algorithm layer.
5. Contract Family itself.
6. Filesystem structure by default.

#### Valid Usage

* “Template Abstraction Layer follows contract family expansion.”
* “Template abstractions precede concrete processing units.”
* “Template Abstraction Layer should preserve responsibility-derived structure.”

#### Invalid Usage

* “Template Abstraction Layer can be designed before contracts.”
* “Template Abstraction Layer is the final package layout.”
* “Template Abstraction Layer replaces semantic domain derivation.”
* “Template Abstraction Layer creates processing units directly.”

#### Related Terms

* GL-CON-003 — Template Contract
* GL-CPP-005 — CRTP Abstraction
* GL-CON-015 — Contract-to-Capability Derivation
* GL-DER-003 — Implementation Derivation
* GL-CPP-003 — Compile-Time Discipline

#### Source Trace

| Source Type       | Source                                                                                                                      |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | SG-TYPE-005 states Templates and CRTP should express reusable static abstraction patterns before concrete processing units. |
| Roadmap Basis     | Template/CRTP abstraction architecture occurs before processing unit derivation.                                            |
| VisionAndScope.md | Future derivation includes template/CRTP layers and concrete processing units.                                              |

---

### GL-CPP-005 — CRTP Abstraction

| Field           | Value                                        |
| --------------- | -------------------------------------------- |
| Term ID         | GL-CPP-005                                   |
| Canonical Term  | CRTP Abstraction                             |
| Family          | CPP / CON                                    |
| Category        | implementation_direction / future_derivation |
| Ownership Scope | future_derivation                            |
| Entry Maturity  | canonical_full                               |
| Evidence Status | direct / derived                             |

#### Definition

CRTP Abstraction is a future C++ static-polymorphism representation strategy in which derived types may bind to reusable base templates while preserving contract-derived behavior and type discipline.

#### Architectural Role

CRTP Abstraction may support reusable behavior without requiring runtime inheritance where static polymorphism better preserves contract meaning.

It may be used for:

1. envelope preparation abstractions,
2. validator-like contract participation,
3. metadata-preparation patterns,
4. timestamp-stabilization patterns,
5. queue moderation patterns,
6. dispatch eligibility patterns,
7. policy-consuming component patterns.

CRTP Abstraction is an implementation direction, not a contract by itself.

#### Must Not Be Confused With

1. Contract itself.
2. Runtime inheritance requirement.
3. Concrete processing unit.
4. Final class hierarchy.
5. Generic metaprogramming.
6. Architecture-free coding pattern.

#### Valid Usage

* “CRTP Abstraction may represent reusable static behavior.”
* “CRTP must follow contract and responsibility derivation.”
* “CRTP can support static polymorphism where appropriate.”

#### Invalid Usage

* “CRTP Abstraction is the architecture.”
* “CRTP Abstraction replaces contract families.”
* “CRTP Abstraction should be designed before glossary terms are stable.”
* “CRTP Abstraction automatically creates final processing units.”

#### Related Terms

* GL-CPP-004 — Template Abstraction Layer
* GL-CON-003 — Template Contract
* GL-CPP-003 — Compile-Time Discipline
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type       | Source                                                                                         |
| ----------------- | ---------------------------------------------------------------------------------------------- |
| README Basis      | Templates and CRTP are part of the architectural identity, not just implementation preference. |
| SYSTEM_GOALS.md   | SG-TYPE-005 places Templates and CRTP before concrete processing units.                        |
| VisionAndScope.md | Long-term implementation vision includes CRTP-based static polymorphism where appropriate.     |

---

### GL-CON-013 — Contract Compliance

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-CON-013          |
| Canonical Term  | Contract Compliance |
| Family          | CON / TRC           |
| Category        | validation_concept  |
| Ownership Scope | governed            |
| Entry Maturity  | canonical_partial   |
| Evidence Status | derived             |

#### Definition

Contract Compliance is the reviewable condition that an architectural element, future abstraction, processing unit, test, or implementation artifact satisfies the Contract or Contract Family governing it.

#### Architectural Role

Contract Compliance prepares future validation and compliance matrix work.

It may support review of:

1. boundary behavior,
2. envelope carrier behavior,
3. runtime state behavior,
4. policy assignment behavior,
5. metadata preparation behavior,
6. dispatcher handoff behavior,
7. exclusion rules,
8. C++ abstraction derivation.

Contract Compliance is not limited to code tests.

It may begin as documentation review.

#### Must Not Be Confused With

1. Unit test only.
2. Runtime assertion only.
3. Static assertion only.
4. CI status only.
5. Final compliance matrix by itself.
6. Legal compliance.

#### Valid Usage

* “Contract Compliance can be reviewed before code exists.”
* “Future tests should derive from contract compliance expectations.”
* “Compliance matrix should reference contract families and goal IDs.”

#### Invalid Usage

* “Contract Compliance exists only after implementation.”
* “Contract Compliance means passing unit tests only.”
* “Contract Compliance can ignore exclusion contracts.”
* “Contract Compliance replaces source traceability.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-004 — Contract Family
* GL-CON-014 — Contract Violation
* GL-TRC-* — Traceability
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type     | Source                                                                                 |
| --------------- | -------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Goals are reviewable and should guide compliance checks, tests, and future derivation. |
| Roadmap Basis   | Compliance and Test Matrix follows goals, obligations, and exclusions.                 |
| GL-CONT-000     | Glossary supports validation and coverage packs.                                       |

---

### GL-CON-014 — Contract Violation

| Field           | Value                                    |
| --------------- | ---------------------------------------- |
| Term ID         | GL-CON-014                               |
| Canonical Term  | Contract Violation                       |
| Family          | CON / GUARD                              |
| Category        | validation_concept / anti_collapse_guard |
| Ownership Scope | governed                                 |
| Entry Maturity  | canonical_partial                        |
| Evidence Status | derived                                  |

#### Definition

A Contract Violation is a breach of a Contract, Contract Family, exclusion rule, type-safety rule, boundary rule, runtime-state rule, or anti-collapse guard.

#### Architectural Role

Contract Violation identifies invalid architecture or implementation direction.

Examples include:

1. treating Queue Container as message broker,
2. treating Log Level Envelope as actor,
3. treating Registry / Delivery Port as Dispatcher,
4. allowing raw content to replace Log Level Envelope,
5. treating Metadata Injector as policy host,
6. assigning downstream registry lifecycle to Assembler,
7. deriving a processing unit before responsibility and contract are established.

#### Must Not Be Confused With

1. Runtime exception only.
2. Compile error only.
3. Test failure only.
4. Documentation typo.
5. Future improvement note.
6. User preference.

#### Valid Usage

* “Port/actor collapse is a Contract Violation.”
* “Queue-as-broker interpretation is a Contract Violation.”
* “Processing-unit derivation without responsibility trace is a Contract Violation.”

#### Invalid Usage

* “Contract Violation only matters in code.”
* “Contract Violation can be ignored during documentation.”
* “Contract Violation is just a naming issue.”
* “Contract Violation is optional if implementation is convenient.”

#### Related Terms

* GL-CON-013 — Contract Compliance
* GL-CON-011 — Exclusion Contract Family
* GL-RUN-012 — Queue-as-Container Doctrine
* GL-OBJ-001 — Log Level Envelope
* GL-BND-008 — Registry / Delivery Port

#### Source Trace

| Source Type     | Source                                                                                           |
| --------------- | ------------------------------------------------------------------------------------------------ |
| GL-CONT-000     | Anti-collapse requirement requires important terms to state what they must not be confused with. |
| SYSTEM_GOALS.md | Negative goals and exclusion goals are enforceable constraints.                                  |
| GL-CONT-005     | Runtime anti-collapse index identifies invalid queue/runtime collapses.                          |
| GL-CONT-004     | Envelope object rules prevent carrier/actor and carrier/raw-content collapse.                    |

---

### GL-CON-015 — Contract-to-Capability Derivation

| Field           | Value                             |
| --------------- | --------------------------------- |
| Term ID         | GL-CON-015                        |
| Canonical Term  | Contract-to-Capability Derivation |
| Family          | CON / DER / TRC                   |
| Category        | future_derivation                 |
| Ownership Scope | governed / future                 |
| Entry Maturity  | canonical_full                    |
| Evidence Status | derived                           |

#### Definition

Contract-to-Capability Derivation is the governed process of deriving enablements, capability candidates, template abstractions, and later concrete processing units from stable Contracts and Contract Families.

#### Architectural Role

This term preserves the official derivation order:

```text id="gl-con-015-chain"
External Relation
→ Contract
→ Responsibility
→ Obligation
→ Delegation
→ Enablement
→ Capability Candidate
→ Abstract C++ Layer
→ Concrete Processing Unit
```

It ensures that implementation artifacts are not invented before their governing contracts and responsibilities are known.

#### Must Not Be Confused With

1. Direct class creation.
2. Package-first design.
3. Utility-first coding.
4. Folder taxonomy.
5. Runtime algorithm design by default.
6. Processing-unit naming exercise.

#### Valid Usage

* “Contract-to-Capability Derivation must precede processing-unit derivation.”
* “Capability Candidates derive from contracts, responsibilities, obligations, delegation, and enablement.”
* “Template abstractions should follow contract-to-capability derivation.”

#### Invalid Usage

* “Contract-to-Capability Derivation starts from a C++ class.”
* “Contract-to-Capability Derivation starts from filesystem folders.”
* “Contract-to-Capability Derivation skips responsibility mapping.”
* “Contract-to-Capability Derivation creates final packages directly.”

#### Related Terms

* GL-CON-001 — Contract
* GL-CON-004 — Contract Family
* GL-CPP-004 — Template Abstraction Layer
* GL-CPP-005 — CRTP Abstraction
* GL-DER-001 — Architecture-to-Implementation Derivation
* GL-TRC-* — Responsibility / Obligation / Delegation / Enablement

#### Source Trace

| Source Type        | Source                                                                                                                                                                   |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines canonical chain: External Relation → Contract → Responsibility → Obligation → Delegation → Enablement → Capability Candidate.                                    |
| SYSTEM_GOALS.md    | Responsibility and traceability goals require derivation through trace chains and prohibit capability candidates from automatically becoming classes/functions/packages. |
| Roadmap Basis      | Dependency ordering places contract expansion and responsibility mapping before C++ abstractions and processing units.                                                   |

---

## 5. Contract Family Governance Matrix

|           Record ID | Contract Family                        | Governs                                                      | Primary Terms                                                                                      | Primary Anti-Collapse                    |
| ------------------: | -------------------------------------- | ------------------------------------------------------------ | -------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| GL-CONT-006-CFG-001 | Ingress Contract Family                | Corrected ingress and envelope admission                     | Level API, Envelope Assembler, Assembler Ingress Port, Log Level Envelope, Slot, Queue Container   | Ingress Port ≠ Envelope Assembler        |
| GL-CONT-006-CFG-002 | Policy / Ecosystem Contract Family     | Policy source, policy object, assignment, eligible consumers | Policy Registry / Policy Source, Policy Object, PolicyAssigner, Policy-Consuming Component         | Policy Object ≠ PolicyAssigner           |
| GL-CONT-006-CFG-003 | Metadata / Preparation Contract Family | Metadata preparation and timestamp stabilization             | Metadata Injector, Timestamp Stabilizer, Metadata Directive Source                                 | Metadata Injector ≠ Policy Host          |
| GL-CONT-006-CFG-004 | Operational / Scaling Contract Family  | Operational directives and runtime control                   | Scaling / Operational Directive Source, Queue Bundle Agent, Single Queue Moderator, Round Managers | Operational Source ≠ Runtime Actor       |
| GL-CONT-006-CFG-005 | Registry / Dispatcher Contract Family  | Final handoff and outbound contract surface                  | Dispatcher, Registry / Delivery Port, Handoff Evidence, Log Level Records Registry                 | Registry / Delivery Port ≠ Dispatcher    |
| GL-CONT-006-CFG-006 | Envelope Carrier Contract Family       | Envelope carrier semantics                                   | Log Level Envelope, Envelope Identity, Metadata Block, Timestamp Block, Dispatch Eligibility State | Envelope ≠ Actor                         |
| GL-CONT-006-CFG-007 | Exclusion Contract Family              | Permanent non-ownership and anti-collapse rules              | Authority Boundary, Downstream Boundary, Post-Handoff Non-Ownership                                | Handoff ≠ downstream lifecycle ownership |
| GL-CONT-006-CFG-008 | Runtime State Contract Family          | Queue/container/slot/waiting-list/round runtime state        | Queue Container, Slot, Envelope Slot Occupancy, Waiting List, Queue Container Identifier           | Queue ≠ Message Broker                   |

---

## 6. Contract-to-C++ Representation Matrix

|           Record ID | Architectural Concept   | Possible Future C++ Representation                                       | Representation Constraint                          |
| ------------------: | ----------------------- | ------------------------------------------------------------------------ | -------------------------------------------------- |
| GL-CONT-006-CPP-001 | Contract                | Interface, trait, template, validator, static rule                       | Representation must follow contract meaning        |
| GL-CONT-006-CPP-002 | Typed Contract          | Strong type, tagged type, constrained template, trait                    | Type must preserve architectural category          |
| GL-CONT-006-CPP-003 | Template Contract       | Template base, template policy, template adapter                         | Must not precede contract family definition        |
| GL-CONT-006-CPP-004 | Contract Family         | Namespace, trait family, abstraction group                               | Not automatically a package                        |
| GL-CONT-006-CPP-005 | Contract Trait          | Trait struct/class, static metadata, detection idiom                     | Trait is representation, not contract itself       |
| GL-CONT-006-CPP-006 | Type Marker             | Marker type, tag type, enum class, phantom type                          | Marker must not invent new semantics               |
| GL-CONT-006-CPP-007 | Compile-Time Discipline | static_assert, template constraints, SFINAE-like detection, CRTP binding | Does not eliminate required runtime validation     |
| GL-CONT-006-CPP-008 | CRTP Abstraction        | CRTP base template                                                       | Must follow responsibility and contract derivation |
| GL-CONT-006-CPP-009 | Contract Compliance     | static checks, tests, architecture review, documentation review          | Not limited to code tests                          |
| GL-CONT-006-CPP-010 | Contract Violation      | static failure, runtime rejection, review failure, compliance failure    | Violation may exist before code                    |

---

## 7. Contract Family Dependency Map

|           Record ID | Contract Family                        | Depends On                                                                                             | Enables                                                                |
| ------------------: | -------------------------------------- | ------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------- |
| GL-CONT-006-DEP-001 | Ingress Contract Family                | Boundary terms, internal actors, envelope terms, runtime placement terms                               | Ingress traits, envelope admission templates, ingress compliance tests |
| GL-CONT-006-DEP-002 | Policy / Ecosystem Contract Family     | External policy source, Policy Object, PolicyAssigner, policy-consuming components                     | Policy assignment traits, policy eligibility markers                   |
| GL-CONT-006-DEP-003 | Metadata / Preparation Contract Family | Metadata Directive Source, Metadata Injector, Timestamp Stabilizer, envelope metadata/timestamp blocks | Preparation abstractions, timestamp stabilization tests                |
| GL-CONT-006-DEP-004 | Operational / Scaling Contract Family  | Operational directive source, runtime actors, runtime state terms                                      | Runtime control abstractions, moderation capability candidates         |
| GL-CONT-006-DEP-005 | Registry / Dispatcher Contract Family  | Dispatcher, Registry / Delivery Port, downstream boundary, handoff evidence                            | Handoff eligibility abstractions, dispatcher compliance checks         |
| GL-CONT-006-DEP-006 | Envelope Carrier Contract Family       | Log Level Envelope, carrier object, governed object, raw-content exclusion                             | Envelope specialization, carrier traits, transport unit checks         |
| GL-CONT-006-DEP-007 | Exclusion Contract Family              | Boundary doctrine, authority exclusion, anti-collapse rules                                            | Compliance matrix, guard checks, non-ownership tests                   |
| GL-CONT-006-DEP-008 | Runtime State Contract Family          | Queue Container, Slot, Occupancy, Waiting List, Round Coordination                                     | Runtime state traits, queue/container implementation design            |

---

## 8. Contract Anti-Collapse Index

|          Record ID | Contract Area                          | Must Not Collapse Into             | Guard Meaning                                              |
| -----------------: | -------------------------------------- | ---------------------------------- | ---------------------------------------------------------- |
| GL-CONT-006-AC-001 | Contract                               | C++ interface only                 | Contract is architectural law first                        |
| GL-CONT-006-AC-002 | Typed Contract                         | Type alias only                    | Type must preserve architectural meaning                   |
| GL-CONT-006-AC-003 | Template Contract                      | Final template code                | Template Contract is pre-implementation derivation         |
| GL-CONT-006-AC-004 | Contract Family                        | Package/folder                     | Family is semantic governance group                        |
| GL-CONT-006-AC-005 | Ingress Contract Family                | Assembler Ingress Port             | Family governs flow; port is one participant               |
| GL-CONT-006-AC-006 | Policy / Ecosystem Contract Family     | PolicyAssigner                     | Family governs policy semantics; actor mediates assignment |
| GL-CONT-006-AC-007 | Metadata / Preparation Contract Family | Policy hosting                     | Metadata preparation is schema/directive-governed          |
| GL-CONT-006-AC-008 | Operational / Scaling Contract Family  | Broker control plane               | Operational directives do not create broker semantics      |
| GL-CONT-006-AC-009 | Registry / Dispatcher Contract Family  | Downstream registry implementation | Handoff contract does not own registry internals           |
| GL-CONT-006-AC-010 | Envelope Carrier Contract Family       | Envelope Assembler                 | Carrier contract governs envelope object, not producer     |
| GL-CONT-006-AC-011 | Exclusion Contract Family              | Optional notes                     | Exclusions are binding constraints                         |
| GL-CONT-006-AC-012 | Runtime State Contract Family          | Message broker contract            | Queue/container runtime is not broker semantics            |
| GL-CONT-006-AC-013 | Contract Trait                         | Contract itself                    | Trait is representation, not law                           |
| GL-CONT-006-AC-014 | Type Marker                            | Canonical term itself              | Marker represents category, not source meaning             |
| GL-CONT-006-AC-015 | Compile-Time Discipline                | No runtime checks                  | Compile-time discipline complements runtime validation     |
| GL-CONT-006-AC-016 | CRTP Abstraction                       | Architecture                       | CRTP is implementation strategy, not system meaning        |
| GL-CONT-006-AC-017 | Contract Compliance                    | Unit tests only                    | Compliance includes architecture and documentation review  |
| GL-CONT-006-AC-018 | Contract Violation                     | Runtime exception only             | Violation may occur at architectural/design level          |

---

## 9. Contract Derivation Flow

### 9.1 Architecture-to-Contract Flow

```text id="gl-cont-006-architecture-to-contract-flow"
Canonical Term
  enters:
    Term Family / Category Model

Architectural Relation
  defines:
    Contract Need

Contract
  governs:
    Responsibility and Obligation

Contract Family
  groups:
    Related Contracts

Contract-to-Capability Derivation
  enables:
    Enablement and Capability Candidate

Template / CRTP Abstraction
  represents:
    Stable contract-derived patterns

Concrete Processing Unit
  may be derived only after:
    Responsibility + Obligation + Delegation + Contract are stable
```

### 9.2 Correct Derivation Rule

```text id="gl-cont-006-correct-derivation-rule"
Do not derive templates from naming preference.
Do not derive processing units from folders.
Do not derive contracts from pre-written classes.
Derive contracts from architectural relations, boundaries, carriers,
runtime states, responsibilities, obligations, and exclusions.
```

### 9.3 Invalid Derivation Pattern

```text id="gl-cont-006-invalid-derivation-pattern"
Class Name
→ Interface
→ Package
→ Contract

This direction is invalid for the Assembler System.
```

### 9.4 Valid Derivation Pattern

```text id="gl-cont-006-valid-derivation-pattern"
External Relation / Boundary / Carrier / Runtime State
→ Contract
→ Responsibility
→ Obligation
→ Delegation
→ Enablement
→ Capability Candidate
→ Template / CRTP Abstraction
→ Concrete Processing Unit
```

---

## 10. Contract Family to Prior Packs Map

|               Record ID | Contract Family                        | Required Prior Glossary Packs                      |
| ----------------------: | -------------------------------------- | -------------------------------------------------- |
| GL-CONT-006-PACKMAP-001 | Ingress Contract Family                | GL-CONT-002, GL-CONT-003, GL-CONT-004, GL-CONT-005 |
| GL-CONT-006-PACKMAP-002 | Policy / Ecosystem Contract Family     | GL-CONT-002, GL-CONT-003, GL-CONT-004              |
| GL-CONT-006-PACKMAP-003 | Metadata / Preparation Contract Family | GL-CONT-003, GL-CONT-004                           |
| GL-CONT-006-PACKMAP-004 | Operational / Scaling Contract Family  | GL-CONT-002, GL-CONT-003, GL-CONT-005              |
| GL-CONT-006-PACKMAP-005 | Registry / Dispatcher Contract Family  | GL-CONT-002, GL-CONT-003, GL-CONT-004              |
| GL-CONT-006-PACKMAP-006 | Envelope Carrier Contract Family       | GL-CONT-003, GL-CONT-004, GL-CONT-005              |
| GL-CONT-006-PACKMAP-007 | Exclusion Contract Family              | GL-CONT-001, GL-CONT-002, GL-CONT-004, GL-CONT-005 |
| GL-CONT-006-PACKMAP-008 | Runtime State Contract Family          | GL-CONT-003, GL-CONT-004, GL-CONT-005              |

---

## 11. Future C++ Abstraction Readiness

This pack does not define final C++ implementation artifacts.

It prepares the vocabulary needed to derive them later.

### 11.1 Future Abstraction Candidates

|           Record ID | Future Abstraction Area        | Derivation Basis                       |
| ------------------: | ------------------------------ | -------------------------------------- |
| GL-CONT-006-ABS-001 | Ingress Template Abstractions  | Ingress Contract Family                |
| GL-CONT-006-ABS-002 | Envelope Carrier Traits        | Envelope Carrier Contract Family       |
| GL-CONT-006-ABS-003 | Metadata Preparation Traits    | Metadata / Preparation Contract Family |
| GL-CONT-006-ABS-004 | Timestamp Stabilization Traits | Metadata / Preparation Contract Family |
| GL-CONT-006-ABS-005 | Policy Eligibility Traits      | Policy / Ecosystem Contract Family     |
| GL-CONT-006-ABS-006 | Runtime State Traits           | Runtime State Contract Family          |
| GL-CONT-006-ABS-007 | Queue Container Type Markers   | Runtime State Contract Family          |
| GL-CONT-006-ABS-008 | Dispatcher Eligibility Traits  | Registry / Dispatcher Contract Family  |
| GL-CONT-006-ABS-009 | Exclusion Guard Types          | Exclusion Contract Family              |
| GL-CONT-006-ABS-010 | CRTP Processing Bases          | Contract-to-Capability Derivation      |

### 11.2 Readiness Constraint

```text id="gl-cont-006-abstraction-readiness"
A C++ abstraction is ready only when its governing Contract Family,
responsibilities, obligations, delegation target, and anti-collapse rules
are explicit.
```

---

## 12. Validation Checklist

|           Record ID | Check                                                                                   | Expected Result |
| ------------------: | --------------------------------------------------------------------------------------- | --------------- |
| GL-CONT-006-VAL-001 | Contract is defined as architectural law                                                | Pass            |
| GL-CONT-006-VAL-002 | Contract is not reduced to C++ interface                                                | Pass            |
| GL-CONT-006-VAL-003 | Typed Contract preserves type discipline without becoming code-first                    | Pass            |
| GL-CONT-006-VAL-004 | Template Contract is future representation, not final code                              | Pass            |
| GL-CONT-006-VAL-005 | Contract Family is semantic group, not package/folder                                   | Pass            |
| GL-CONT-006-VAL-006 | All canonical contract families are listed                                              | Pass            |
| GL-CONT-006-VAL-007 | Ingress Contract Family preserves corrected ingress flow                                | Pass            |
| GL-CONT-006-VAL-008 | Policy / Ecosystem Contract Family preserves policy-object distinction                  | Pass            |
| GL-CONT-006-VAL-009 | Metadata / Preparation Contract Family preserves Metadata Injector non-policy-host rule | Pass            |
| GL-CONT-006-VAL-010 | Operational / Scaling Contract Family remains separate from broker semantics            | Pass            |
| GL-CONT-006-VAL-011 | Registry / Dispatcher Contract Family preserves Dispatcher finality                     | Pass            |
| GL-CONT-006-VAL-012 | Envelope Carrier Contract Family preserves carrier/non-actor distinction                | Pass            |
| GL-CONT-006-VAL-013 | Exclusion Contract Family is binding, not optional                                      | Pass            |
| GL-CONT-006-VAL-014 | Runtime State Contract Family preserves Queue = Container                               | Pass            |
| GL-CONT-006-VAL-015 | Contract Trait is representation, not contract itself                                   | Pass            |
| GL-CONT-006-VAL-016 | Type Marker does not invent semantics                                                   | Pass            |
| GL-CONT-006-VAL-017 | Compile-Time Discipline does not eliminate runtime validation                           | Pass            |
| GL-CONT-006-VAL-018 | Template/CRTP abstractions precede concrete processing units                            | Pass            |
| GL-CONT-006-VAL-019 | Contract-to-Capability derivation preserves trace chain                                 | Pass            |
| GL-CONT-006-VAL-020 | Pack is ready to support GL-CONT-007                                                    | Pass            |

---

## 13. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                                                    | Status   |
| -------------------: | --------------------------------------------------------------------------------- | -------- |
| GL-CONT-006-EXIT-001 | Contract is formally defined                                                      | Complete |
| GL-CONT-006-EXIT-002 | Typed Contract is formally defined                                                | Complete |
| GL-CONT-006-EXIT-003 | Template Contract is formally defined                                             | Complete |
| GL-CONT-006-EXIT-004 | Contract Family is formally defined                                               | Complete |
| GL-CONT-006-EXIT-005 | Eight canonical contract families are defined                                     | Complete |
| GL-CONT-006-EXIT-006 | Contract-to-C++ representation boundary is clarified                              | Complete |
| GL-CONT-006-EXIT-007 | Contract Trait and Type Marker are marked as future C++ representation candidates | Complete |
| GL-CONT-006-EXIT-008 | Compile-Time Discipline is defined without eliminating runtime validation         | Complete |
| GL-CONT-006-EXIT-009 | Template Abstraction Layer is positioned before concrete processing units         | Complete |
| GL-CONT-006-EXIT-010 | CRTP Abstraction is positioned as future static-polymorphism strategy             | Complete |
| GL-CONT-006-EXIT-011 | Contract Compliance and Contract Violation are defined for future validation      | Complete |
| GL-CONT-006-EXIT-012 | Contract-to-Capability Derivation preserves the official derivation chain         | Complete |
| GL-CONT-006-EXIT-013 | Anti-collapse index is included                                                   | Complete |
| GL-CONT-006-EXIT-014 | Pack is ready to enable responsibility/obligation terminology                     | Complete |

---

## 14. Summary

`GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack` establishes the canonical vocabulary for contract governance and C++ abstraction readiness.

The pack stabilizes the following model:

```text id="gl-cont-006-summary-model"
Contract
= architectural law
≠ interface/class/template by default

Typed Contract
= contract with type-discipline intent
≠ type alias only

Template Contract
= contract prepared for future template representation
≠ final template code

Contract Family
= semantic governance group
≠ package/folder/namespace by default

Contract Trait
= future C++ representation candidate
≠ contract itself

Type Marker
= future compile-time category marker
≠ source of new architectural meaning

Compile-Time Discipline
= preserve contract meaning statically where appropriate
≠ eliminate all runtime checks

Template / CRTP Abstraction
= reusable static abstraction after contracts are stable
≠ concrete processing unit

Contract-to-Capability Derivation
= governed path from contract to enablement and capability candidate
≠ code-first implementation
```

The canonical contract families are:

```text id="gl-cont-006-contract-families"
Ingress Contract Family
Policy / Ecosystem Contract Family
Metadata / Preparation Contract Family
Operational / Scaling Contract Family
Registry / Dispatcher Contract Family
Envelope Carrier Contract Family
Exclusion Contract Family
Runtime State Contract Family
```

This pack enables the next glossary content pack:

```text id="gl-cont-006-next"
GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack
```
