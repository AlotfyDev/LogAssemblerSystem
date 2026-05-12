
# GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-007-DOC-001 | Pack Name | GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack |
| GL-CONT-007-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-007-DOC-003 | Project | Assembler System |
| GL-CONT-007-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-007-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-007-DOC-006 | Language | English |
| GL-CONT-007-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002, GL-CONT-003, GL-CONT-004, GL-CONT-005, GL-CONT-006 |
| GL-CONT-007-DOC-008 | Scope | Responsibility vocabulary, obligation vocabulary, delegation vocabulary, enablement vocabulary, capability-candidate vocabulary, traceability vocabulary, gap-closure vocabulary |
| GL-CONT-007-DOC-009 | Excluded From This Pack | Final package derivation, final class derivation, final function derivation, final processing-unit derivation, final compliance matrix population |
| GL-CONT-007-DOC-010 | Enables | GL-CONT-008, GL-CONT-009, GL-CONT-010, Roadmap derivation, semantic domain derivation, package derivation, capability matrix derivation, compliance matrix derivation |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for responsibility, obligation, delegation, enablement, traceability, and capability-candidate terminology in the Assembler System.

It answers the question:

```text
How does the Assembler System move from external relation and contract
to responsibility, obligation, delegation, enablement, and future capability
without prematurely inventing classes, functions, packages, or processing units?
````

This pack protects the architecture from code-first derivation.

It also prevents broad assignment of responsibilities to the whole `Assembler Subsystem` when a narrower mature architectural carrier exists.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`,
4. `GL-CONT-003 — Internal Actors and Delegated Entities Pack`,
5. `GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack`,
6. `GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack`,
7. `GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack`.

It precedes:

1. `GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack`,
2. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`,
3. `GL-CONT-010 — C++ Implementation Direction, Semantic Domains, and Future Derivation Terms Pack`.

### 2.3 Pack-Level Derivation Rule

```text id="gl-cont-007-derivation-rule"
External Relation
→ Contract
→ Responsibility
→ Obligation
→ Delegation
→ Enablement
→ Capability Candidate
```

This order is mandatory.

A later implementation artifact must not be created by skipping this chain.

### 2.4 Pack-Level Anti-Premature-Implementation Rule

```text id="gl-cont-007-anti-premature-rule"
A responsibility is not a class.
An obligation is not a test by default.
A delegation is not a package by default.
An enablement is not final implementation.
A capability candidate is not automatically a class, function, package, or processing unit.
```

### 2.5 Pack-Level Narrow-Carrier Rule

```text id="gl-cont-007-narrow-carrier-rule"
Delegation must target the narrowest mature architectural carrier that can
validly carry the responsibility without violating boundary, contract,
object, runtime, or authority rules.
```

---

## 3. Term Inventory

|           Record ID | Term ID    | Canonical Term                      | Family      | Category                                 | Ownership Scope   | Entry Maturity    |
| ------------------: | ---------- | ----------------------------------- | ----------- | ---------------------------------------- | ----------------- | ----------------- |
| GL-CONT-007-INV-001 | GL-TRC-004 | External Relation                   | TRC / BND   | traceability_source / relation           | governed          | canonical_full    |
| GL-CONT-007-INV-002 | GL-TRC-005 | Responsibility                      | TRC         | responsibility                           | governed          | canonical_full    |
| GL-CONT-007-INV-003 | GL-TRC-006 | Obligation                          | TRC         | obligation                               | governed          | canonical_full    |
| GL-CONT-007-INV-004 | GL-TRC-007 | Delegation                          | TRC         | delegation_relation                      | governed          | canonical_full    |
| GL-CONT-007-INV-005 | GL-TRC-008 | Enablement                          | TRC         | enablement_family                        | governed / future | canonical_full    |
| GL-CONT-007-INV-006 | GL-TRC-009 | Capability Candidate                | TRC / DER   | future_derivation                        | governed / future | canonical_full    |
| GL-CONT-007-INV-007 | GL-TRC-010 | Traceability                        | TRC         | traceability_model                       | governed          | canonical_full    |
| GL-CONT-007-INV-008 | GL-TRC-011 | Gap Closure                         | TRC         | validation_concept / derivation_control  | governed          | canonical_full    |
| GL-CONT-007-INV-009 | GL-TRC-012 | Anti-Regression Rule                | TRC / GUARD | anti_collapse_guard / validation_concept | governed          | canonical_full    |
| GL-CONT-007-INV-010 | GL-TRC-013 | Narrow Mature Architectural Carrier | TRC / ENT   | delegation_target                        | governed          | canonical_full    |
| GL-CONT-007-INV-011 | GL-TRC-014 | Source Trace                        | TRC / DOC   | source_trace                             | governed          | canonical_full    |
| GL-CONT-007-INV-012 | GL-TRC-015 | Join Key                            | TRC / DOC   | identifier / traceability_model          | governed          | canonical_full    |
| GL-CONT-007-INV-013 | GL-TRC-016 | ID Namespace                        | TRC / DOC   | identifier_namespace                     | governed          | canonical_full    |
| GL-CONT-007-INV-014 | GL-TRC-017 | Responsibility Chain                | TRC         | derivation_chain                         | governed          | canonical_full    |
| GL-CONT-007-INV-015 | GL-TRC-018 | Responsibility Owner                | TRC / ENT   | responsibility_owner                     | governed          | canonical_full    |
| GL-CONT-007-INV-016 | GL-TRC-019 | Reviewable Guarantee                | TRC         | obligation / validation_concept          | governed          | canonical_full    |
| GL-CONT-007-INV-017 | GL-TRC-020 | Derivation Source                   | TRC / DOC   | traceability_source                      | governed          | canonical_full    |
| GL-CONT-007-INV-018 | GL-TRC-021 | Capability Surface                  | TRC / DER   | enablement_surface                       | governed / future | canonical_partial |
| GL-CONT-007-INV-019 | GL-TRC-022 | Capability Realization              | TRC / DER   | future_derivation                        | future            | canonical_partial |
| GL-CONT-007-INV-020 | GL-TRC-023 | Trace Chain Integrity               | TRC / GUARD | validation_concept / anti_collapse_guard | governed          | canonical_full    |

---

## 4. Canonical Term Entries

---

### GL-TRC-004 — External Relation

| Field           | Value                          |
| --------------- | ------------------------------ |
| Term ID         | GL-TRC-004                     |
| Canonical Term  | External Relation              |
| Family          | TRC / BND                      |
| Category        | traceability_source / relation |
| Ownership Scope | governed                       |
| Entry Maturity  | canonical_full                 |
| Evidence Status | direct / derived               |

#### Definition

An External Relation is a boundary-facing architectural relation between the Assembler System and an external, consuming-side, administrative, operational, policy-source, metadata-source, or downstream-facing context.

It is the starting point for the responsibility derivation chain.

#### Architectural Role

External Relation answers:

```text id="gl-trc-004-question"
Who or what interacts with the Assembler boundary,
and what governed relation does that interaction create?
```

An External Relation may involve:

1. `Level API`,
2. `Assemblers Administrator`,
3. `Policy Registry / Policy Source`,
4. `Metadata Directive Source`,
5. `Scaling / Operational Directive Source`,
6. `Log Level Records Registry`,
7. `Reading / Querying Subsystem`,
8. downstream preservation or query destinations.

An External Relation does not automatically define an internal actor.

It must first be interpreted through a Contract.

#### Must Not Be Confused With

1. Internal actor.
2. Boundary port itself.
3. C++ interface.
4. Package dependency.
5. Runtime event.
6. Downstream lifecycle ownership.
7. Capability candidate.

#### Valid Usage

* “External Relation identifies a boundary interaction.”
* “External Relation must be governed by a Contract before responsibility derivation.”
* “Policy Registry / Policy Source creates an external policy relation.”

#### Invalid Usage

* “External Relation is automatically a class.”
* “External Relation is the internal delegated entity.”
* “External Relation bypasses Contract definition.”
* “External Relation implies downstream ownership by the Assembler.”

#### Related Terms

* GL-CON-001 — Contract
* GL-TRC-005 — Responsibility
* GL-BND-002 — Boundary Surface
* GL-BND-003 — Contract Surface
* GL-EXT-001 — Level API
* GL-EXT-003 — Policy Registry / Policy Source

#### Source Trace

| Source Type        | Source                                                                             |
| ------------------ | ---------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines External Relation as the first item in the canonical responsibility chain. |
| GL-CONT-002        | Defines external context and boundary surfaces.                                    |
| GL-CONT-006        | Defines Contract as the architectural law governing relations.                     |

---

### GL-TRC-005 — Responsibility

| Field           | Value            |
| --------------- | ---------------- |
| Term ID         | GL-TRC-005       |
| Canonical Term  | Responsibility   |
| Family          | TRC              |
| Category        | responsibility   |
| Ownership Scope | governed         |
| Entry Maturity  | canonical_full   |
| Evidence Status | direct / derived |

#### Definition

A Responsibility is a canonical architectural duty or required outcome that the Assembler System, an internal actor, a port, a carrier object, a runtime structure, or a delegated entity must preserve or achieve under a governing Contract.

A Responsibility states what must be achieved.

It does not define the final implementation artifact.

#### Architectural Role

Responsibility is the bridge between Contract and Obligation.

It converts a governed relation into an explicit duty.

Examples of responsibility areas include:

1. envelope production,
2. envelope admission,
3. metadata preparation,
4. timestamp stabilization,
5. policy assignment,
6. queue/container runtime coordination,
7. dispatcher-mediated handoff,
8. authority closure,
9. source trace preservation,
10. anti-collapse enforcement.

A Responsibility must be traceable to a source such as an external relation, contract, doctrine, closure rule, or runtime model.

#### Must Not Be Confused With

1. Class.
2. Method.
3. Function.
4. Package.
5. Folder.
6. Final processing unit.
7. Runtime algorithm.
8. User story by default.

#### Valid Usage

* “Envelope Assembler has responsibility for envelope realization.”
* “Dispatcher has responsibility for final assembler-side handoff.”
* “Every major responsibility must be traceable.”

#### Invalid Usage

* “Responsibility is a C++ class.”
* “Responsibility is automatically a package.”
* “Responsibility can be invented without derivation source.”
* “Responsibility can skip obligations.”

#### Related Terms

* GL-CON-001 — Contract
* GL-TRC-006 — Obligation
* GL-TRC-007 — Delegation
* GL-TRC-010 — Traceability
* GL-TRC-017 — Responsibility Chain

#### Source Trace

| Source Type        | Source                                                                                                                                             |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-TRACE-001 requires every major assembler responsibility to be traceable to an external relation, contract, doctrine, closure, or runtime model. |
| SYSTEM_GOALS.md    | SG-TRACE-002 requires every responsibility to have at least one obligation or reviewable guarantee.                                                |
| ProjectOverview.md | Responsibility is the third step in the canonical chain after External Relation and Contract.                                                      |

---

### GL-TRC-006 — Obligation

| Field           | Value            |
| --------------- | ---------------- |
| Term ID         | GL-TRC-006       |
| Canonical Term  | Obligation       |
| Family          | TRC              |
| Category        | obligation       |
| Ownership Scope | governed         |
| Entry Maturity  | canonical_full   |
| Evidence Status | direct / derived |

#### Definition

An Obligation is a reviewable guarantee, constraint, preservation rule, or prevention rule attached to a Responsibility.

It states what must be guaranteed, constrained, preserved, rejected, or prevented while fulfilling the Responsibility.

#### Architectural Role

Obligation makes Responsibility reviewable.

It may define:

1. what must be preserved,
2. what must be rejected,
3. what must not collapse,
4. what must be traceable,
5. what must remain outside authority,
6. what must happen before handoff,
7. what must not happen after handoff.

Examples:

1. `Log Level Envelope` must not be replaced by raw content.
2. `Metadata Injector` must remain schema/directive-governed, not policy-hosted.
3. `Queue Container` must remain a container, not a message broker.
4. `Dispatcher` must remain the final assembler-side outbound actor.
5. `Post-Handoff Non-Ownership` must remain binding.

#### Must Not Be Confused With

1. Unit test by default.
2. Runtime assertion by default.
3. Legal obligation.
4. Implementation task.
5. Optional note.
6. Documentation preference.

#### Valid Usage

* “Every responsibility should have an obligation.”
* “Authority closure is an obligation attached to handoff responsibility.”
* “Anti-collapse rules can be obligations.”

#### Invalid Usage

* “Obligation exists only after code.”
* “Obligation is just a TODO.”
* “Obligation is optional guidance.”
* “Obligation can be ignored during package derivation.”

#### Related Terms

* GL-TRC-005 — Responsibility
* GL-TRC-019 — Reviewable Guarantee
* GL-CON-013 — Contract Compliance
* GL-CON-014 — Contract Violation
* GL-TRC-012 — Anti-Regression Rule

#### Source Trace

| Source Type        | Source                                                                                              |
| ------------------ | --------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-TRACE-002 requires every responsibility to have at least one obligation or reviewable guarantee. |
| ProjectOverview.md | Obligation follows Responsibility in the canonical derivation chain.                                |
| GL-CONT-006        | Contract Compliance and Contract Violation prepare future validation of obligations.                |

---

### GL-TRC-007 — Delegation

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-TRC-007          |
| Canonical Term  | Delegation          |
| Family          | TRC                 |
| Category        | delegation_relation |
| Ownership Scope | governed            |
| Entry Maturity  | canonical_full      |
| Evidence Status | direct / derived    |

#### Definition

Delegation is the governed assignment of a Responsibility to the narrowest mature architectural carrier capable of carrying that Responsibility without violating system boundaries, contracts, object categories, runtime rules, or authority exclusions.

#### Architectural Role

Delegation prevents vague responsibility assignment to the whole Assembler Subsystem.

It establishes which entity, port, carrier, runtime actor, or governed object carries a responsibility.

Delegation may target:

1. `Envelope Assembler`,
2. `Assembler Ingress Port`,
3. `PolicyAssigner`,
4. `Metadata Injector`,
5. `Timestamp Stabilizer`,
6. `Queue Bundle Agent`,
7. `Single Queue Moderator`,
8. `Writing / Feeding Round Manager`,
9. `Dispatching / Delivery Round Manager`,
10. `Dispatcher`,
11. `Log Level Envelope` as carrier object,
12. `Queue Container` as runtime state structure,
13. a future capability candidate after derivation.

Delegation does not automatically create code.

#### Must Not Be Confused With

1. Package creation.
2. Class ownership.
3. Runtime execution by default.
4. Broad subsystem accountability.
5. External relation.
6. Capability realization.
7. Downstream ownership transfer.

#### Valid Usage

* “Delegation targets the narrowest mature architectural carrier.”
* “Dispatcher is delegated final handoff responsibility.”
* “Assembler Subsystem remains accountable, but execution is delegated.”

#### Invalid Usage

* “Delegation means the whole subsystem directly performs the work.”
* “Delegation automatically creates a C++ class.”
* “Delegation to a port turns the port into an actor.”
* “Delegation can target a downstream subsystem as assembler-owned.”

#### Related Terms

* GL-TRC-013 — Narrow Mature Architectural Carrier
* GL-TRC-018 — Responsibility Owner
* GL-TRC-008 — Enablement
* GL-TRC-001 — Delegated Entity
* GL-TRC-002 — Supporting Entity
* GL-TRC-003 — Primary Responsibility Owner

#### Source Trace

| Source Type     | Source                                                                                            |
| --------------- | ------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-TRACE-003 requires delegation to target the narrowest mature architectural carrier.            |
| SYSTEM_GOALS.md | SG-TRACE-004 prevents supporting entities from being confused with primary responsibility owners. |
| GL-CONT-003     | Defines Delegated Entity, Supporting Entity, and Primary Responsibility Owner.                    |

---

### GL-TRC-008 — Enablement

| Field           | Value             |
| --------------- | ----------------- |
| Term ID         | GL-TRC-008        |
| Canonical Term  | Enablement        |
| Family          | TRC               |
| Category        | enablement_family |
| Ownership Scope | governed / future |
| Entry Maturity  | canonical_full    |
| Evidence Status | direct / derived  |

#### Definition

Enablement is the governed capability, surface, mechanism, condition, contract support, or readiness basis that allows a delegated architectural carrier to fulfill a Responsibility.

Enablement identifies what must exist or be available for a responsibility to be carried.

It is not final implementation.

#### Architectural Role

Enablement sits between Delegation and Capability Candidate.

It answers:

```text id="gl-trc-008-question"
What must be enabled for the delegated carrier to fulfill the responsibility?
```

Enablement may refer to:

1. a boundary surface,
2. a contract family,
3. a type-safety structure,
4. a runtime-state capability,
5. a traceability mechanism,
6. a policy assignment mechanism,
7. a queue/container readiness mechanism,
8. a handoff evidence mechanism,
9. a future C++ abstraction area.

#### Must Not Be Confused With

1. Final class.
2. Final function.
3. Final package.
4. Processing unit.
5. Runtime algorithm by default.
6. Implementation task.
7. Deployed feature.

#### Valid Usage

* “Enablement describes what allows responsibility execution.”
* “Queue Container Identifier handling may enable waiting-list coordination.”
* “Handoff Evidence enablement may support dispatcher auditability.”

#### Invalid Usage

* “Enablement is the final implementation.”
* “Enablement is automatically a package.”
* “Enablement creates a class directly.”
* “Enablement can ignore delegation target.”

#### Related Terms

* GL-TRC-007 — Delegation
* GL-TRC-009 — Capability Candidate
* GL-TRC-021 — Capability Surface
* GL-CON-015 — Contract-to-Capability Derivation
* GL-CPP-004 — Template Abstraction Layer

#### Source Trace

| Source Type        | Source                                                                                                |
| ------------------ | ----------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-TRACE-005 states Enablement shall not be treated as final implementation.                          |
| ProjectOverview.md | Enablement follows Delegation and precedes Capability Candidate in the canonical chain.               |
| GL-CONT-006        | Contract-to-Capability Derivation uses enablements before capability candidates and C++ abstractions. |

---

### GL-TRC-009 — Capability Candidate

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-TRC-009           |
| Canonical Term  | Capability Candidate |
| Family          | TRC / DER            |
| Category        | future_derivation    |
| Ownership Scope | governed / future    |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

A Capability Candidate is an implementation-facing possibility derived from a stable chain of External Relation, Contract, Responsibility, Obligation, Delegation, and Enablement.

It is a candidate for future implementation derivation.

It is not automatically a class, function, package, template, or processing unit.

#### Architectural Role

Capability Candidate is the last pre-implementation concept in the responsibility chain before future abstraction or implementation derivation.

It may later inform:

1. semantic domain derivation,
2. package derivation,
3. C++ template/CRTP abstraction,
4. processing-unit derivation,
5. tests,
6. compliance matrix rows,
7. examples,
8. reference pipelines.

Capability Candidate must remain traceable to its derivation chain.

#### Must Not Be Confused With

1. Final class.
2. Final function.
3. Final package.
4. Final processing unit.
5. C++ trait by default.
6. User story by default.
7. Implementation ticket by default.

#### Valid Usage

* “Capability Candidate may later derive into a C++ abstraction.”
* “Capability Candidates must preserve traceability.”
* “Capability Candidate follows enablement.”

#### Invalid Usage

* “Capability Candidate is automatically a class.”
* “Capability Candidate is automatically a package.”
* “Capability Candidate can be created from a folder name.”
* “Capability Candidate can skip Responsibility and Obligation.”

#### Related Terms

* GL-TRC-008 — Enablement
* GL-CON-015 — Contract-to-Capability Derivation
* GL-CPP-004 — Template Abstraction Layer
* GL-CPP-005 — CRTP Abstraction
* GL-DER-003 — Implementation Derivation

#### Source Trace

| Source Type        | Source                                                                                                                   |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------ |
| SYSTEM_GOALS.md    | SG-TRACE-006 states Capability Candidates shall not automatically become classes, functions, or packages.                |
| ProjectOverview.md | Capability Candidate is the final item in the canonical responsibility chain.                                            |
| GL-CONT-006        | Contract-to-Capability Derivation positions Capability Candidate before abstract C++ layer and concrete processing unit. |

---

### GL-TRC-010 — Traceability

| Field           | Value              |
| --------------- | ------------------ |
| Term ID         | GL-TRC-010         |
| Canonical Term  | Traceability       |
| Family          | TRC                |
| Category        | traceability_model |
| Ownership Scope | governed           |
| Entry Maturity  | canonical_full     |
| Evidence Status | direct / derived   |

#### Definition

Traceability is the governed ability to follow a term, responsibility, obligation, delegation, enablement, capability candidate, goal, contract, or future implementation artifact back to its canonical source and derivation chain.

#### Architectural Role

Traceability prevents arbitrary architecture.

It supports:

1. source trace,
2. goal trace,
3. contract trace,
4. responsibility trace,
5. obligation trace,
6. delegation trace,
7. enablement trace,
8. capability-candidate trace,
9. anti-collapse validation,
10. compliance matrix construction,
11. roadmap derivation,
12. test derivation.

Traceability is a system-level governance principle.

It is not merely a documentation convenience.

#### Must Not Be Confused With

1. Hyperlink only.
2. Comment in code only.
3. Git history only.
4. Audit log only.
5. Runtime tracing only.
6. Observability telemetry.

#### Valid Usage

* “Future tests should reference goal IDs and trace chains.”
* “Package derivation must preserve traceability.”
* “Traceability links glossary terms to source and derivation records.”

#### Invalid Usage

* “Traceability is only runtime tracing.”
* “Traceability is optional documentation.”
* “Traceability can be reconstructed from naming similarity.”
* “Traceability is only Git commit history.”

#### Related Terms

* GL-TRC-014 — Source Trace
* GL-TRC-015 — Join Key
* GL-TRC-016 — ID Namespace
* GL-TRC-017 — Responsibility Chain
* GL-TRC-023 — Trace Chain Integrity

#### Source Trace

| Source Type     | Source                                                                                                                     |
| --------------- | -------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-TRACE-007 states future goals, roadmap milestones, and tests should reference goal IDs and trace chains where possible. |
| GL-CONT-000     | Glossary governance requires source trace and later validation support.                                                    |
| GL-CONT-006     | Contract Compliance depends on traceability to contract families and goal IDs.                                             |

---

### GL-TRC-011 — Gap Closure

| Field           | Value                                   |
| --------------- | --------------------------------------- |
| Term ID         | GL-TRC-011                              |
| Canonical Term  | Gap Closure                             |
| Family          | TRC                                     |
| Category        | validation_concept / derivation_control |
| Ownership Scope | governed                                |
| Entry Maturity  | canonical_full                          |
| Evidence Status | derived                                 |

#### Definition

Gap Closure is the governed act of resolving a missing, incomplete, ambiguous, or under-specified part of a trace chain before allowing downstream derivation to proceed.

A gap may exist in source trace, contract definition, responsibility assignment, obligation definition, delegation target, enablement description, or capability-candidate justification.

#### Architectural Role

Gap Closure protects later derivation from false completeness.

It is required when:

1. a term is only a seed,
2. a responsibility lacks an obligation,
3. a delegation target is too broad,
4. an enablement is vague,
5. a capability candidate has no trace chain,
6. a contract family is missing,
7. an anti-collapse rule is absent,
8. source trace is unavailable or unstable.

Gap Closure may upgrade a term from `seed` to `canonical_partial`, or from `canonical_partial` to `canonical_full`.

#### Must Not Be Confused With

1. Adding implementation detail prematurely.
2. Filling a table with guesses.
3. Closing a GitHub issue by default.
4. Accepting a vague TODO.
5. Ignoring missing trace.
6. Creating a package to hide ambiguity.

#### Valid Usage

* “This capability candidate requires gap closure before package derivation.”
* “A seed term may need gap closure before implementation.”
* “Missing obligation is a traceability gap.”

#### Invalid Usage

* “Gap Closure means writing final code immediately.”
* “Gap Closure can skip source trace.”
* “Gap Closure means accepting the current ambiguity.”
* “Gap Closure is only project-management status.”

#### Related Terms

* GL-TRC-010 — Traceability
* GL-TRC-014 — Source Trace
* GL-TRC-023 — Trace Chain Integrity
* GL-CONT-000-MAT-* — Entry Maturity
* GL-CON-013 — Contract Compliance

#### Source Trace

| Source Type     | Source                                                                                                                            |
| --------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-000     | Low-detail seed policy preserves incomplete elements while marking maturity.                                                      |
| SYSTEM_GOALS.md | Traceability goals require responsibilities, obligations, delegation, enablement, and capability candidates to remain reviewable. |
| Roadmap Basis   | Compliance before expansion and dependency-first ordering require unresolved gaps to be closed before later derivation.           |

---

### GL-TRC-012 — Anti-Regression Rule

| Field           | Value                                    |
| --------------- | ---------------------------------------- |
| Term ID         | GL-TRC-012                               |
| Canonical Term  | Anti-Regression Rule                     |
| Family          | TRC / GUARD                              |
| Category        | anti_collapse_guard / validation_concept |
| Ownership Scope | governed                                 |
| Entry Maturity  | canonical_full                           |
| Evidence Status | derived                                  |

#### Definition

An Anti-Regression Rule is a governance rule that prevents later documents, packages, implementation artifacts, tests, or integrations from weakening or reversing a previously established architectural distinction, exclusion, responsibility chain, or anti-collapse rule.

#### Architectural Role

Anti-Regression Rule protects stabilized architecture.

It prevents regression such as:

1. turning `Queue Container` into a message broker,
2. turning `Log Level Envelope` into an actor,
3. turning `Registry / Delivery Port` into `Dispatcher`,
4. turning `Metadata Injector` into a policy host,
5. assigning downstream lifecycle ownership to Assembler,
6. treating `Capability Candidate` as final package,
7. deriving code before contract and responsibility are stable.

Anti-Regression Rule is especially important after glossary packs become source material for roadmap, package, and C++ derivation.

#### Must Not Be Confused With

1. Unit test only.
2. CI guard only.
3. Runtime assertion only.
4. Documentation preference.
5. Optional checklist.
6. Backward compatibility rule by default.

#### Valid Usage

* “Actor/port separation must be protected by anti-regression rules.”
* “Package derivation must not regress contract-family semantics.”
* “Queue-as-container doctrine requires anti-regression protection.”

#### Invalid Usage

* “Anti-Regression Rule matters only after implementation.”
* “Anti-Regression Rule is optional.”
* “Anti-Regression Rule can be overridden by package convenience.”
* “Anti-Regression Rule is only a test case.”

#### Related Terms

* GL-CON-014 — Contract Violation
* GL-CON-011 — Exclusion Contract Family
* GL-RUN-012 — Queue-as-Container Doctrine
* GL-TRC-023 — Trace Chain Integrity
* GL-CONT-000-GOV-* — Glossary Governance Requirements

#### Source Trace

| Source Type     | Source                                                                                             |
| --------------- | -------------------------------------------------------------------------------------------------- |
| GL-CONT-000     | Anti-collapse requirement states important terms must declare what they must not be confused with. |
| SYSTEM_GOALS.md | Negative goals and exclusion goals are enforceable constraints.                                    |
| GL-CONT-006     | Contract Violation may occur at architecture/design level, not only runtime.                       |

---

### GL-TRC-013 — Narrow Mature Architectural Carrier

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-TRC-013                          |
| Canonical Term  | Narrow Mature Architectural Carrier |
| Family          | TRC / ENT                           |
| Category        | delegation_target                   |
| Ownership Scope | governed                            |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

A Narrow Mature Architectural Carrier is the most specific stable architectural entity, port, actor, carrier object, runtime structure, contract surface, or governed object capable of carrying a Responsibility without category collapse or authority violation.

#### Architectural Role

This term governs delegation.

It prevents assigning every responsibility to the broad `Assembler Subsystem`.

A narrow mature carrier may be:

1. an internal actor,
2. a delegated entity,
3. a supporting entity,
4. a port,
5. a contract surface,
6. a carrier object,
7. a runtime state structure,
8. a contract family,
9. a future capability candidate after sufficient derivation.

Maturity means the carrier has enough definition to safely carry the responsibility.

Narrowness means the carrier is not broader than necessary.

#### Must Not Be Confused With

1. Whole subsystem by default.
2. Final C++ class.
3. Package owner.
4. Runtime thread.
5. Deployment service.
6. Downstream component.
7. Informal nickname.

#### Valid Usage

* “Delegation should target a Narrow Mature Architectural Carrier.”
* “Dispatcher is the narrow mature carrier for final outbound handoff.”
* “Queue Container is the narrow carrier for slot structure, not downstream lifecycle.”

#### Invalid Usage

* “The whole subsystem is always the carrier.”
* “Any named thing can be a carrier.”
* “A downstream registry can be selected as assembler-owned carrier.”
* “A seed term can carry implementation authority without maturity upgrade.”

#### Related Terms

* GL-TRC-007 — Delegation
* GL-TRC-018 — Responsibility Owner
* GL-TRC-001 — Delegated Entity
* GL-TRC-002 — Supporting Entity
* GL-ENT-* — Internal Actors
* GL-OBJ-* — Governed Objects
* GL-RUN-* — Runtime Structures

#### Source Trace

| Source Type     | Source                                                                                                        |
| --------------- | ------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-TRACE-003 requires delegation to target the narrowest mature architectural carrier.                        |
| GL-CONT-003     | Defines Delegated Entity, Supporting Entity, Primary Responsibility Owner, and actor/port/carrier separation. |
| GL-CONT-004     | Defines carrier objects and governed objects.                                                                 |
| GL-CONT-005     | Defines runtime structures that may carry runtime-state responsibilities.                                     |

---

### GL-TRC-014 — Source Trace

| Field           | Value            |
| --------------- | ---------------- |
| Term ID         | GL-TRC-014       |
| Canonical Term  | Source Trace     |
| Family          | TRC / DOC        |
| Category        | source_trace     |
| Ownership Scope | governed         |
| Entry Maturity  | canonical_full   |
| Evidence Status | direct / derived |

#### Definition

A Source Trace is a reference from a glossary term, responsibility, obligation, delegation, enablement, capability candidate, goal, or derivation artifact back to the source document, source group, record ID, decision, or canonical basis that supports it.

#### Architectural Role

Source Trace makes architecture auditable.

It allows later reviewers to ask:

1. where did this term come from?
2. which source supports this responsibility?
3. which goal requires this obligation?
4. which contract governs this derivation?
5. which prior pack established this rule?
6. which user decision stabilized this term?

Source Trace should prefer stable record IDs and canonical documents over informal text similarity.

#### Must Not Be Confused With

1. Free-text note only.
2. URL only.
3. Git blame only.
4. Runtime log trace.
5. Human memory.
6. Naming similarity.

#### Valid Usage

* “Each glossary entry should include a Source Trace where possible.”
* “Capability candidates should preserve source trace.”
* “A source trace may refer to a goal ID, document section, or prior pack.”

#### Invalid Usage

* “Source Trace can be inferred from similar names.”
* “Source Trace is optional for major responsibilities.”
* “Source Trace is runtime telemetry.”
* “Source Trace can be replaced by package name.”

#### Related Terms

* GL-TRC-010 — Traceability
* GL-TRC-015 — Join Key
* GL-TRC-016 — ID Namespace
* GL-TRC-020 — Derivation Source
* GL-CONT-000-SRC-* — Source Rules

#### Source Trace

| Source Type     | Source                                                                                                                                                                                                         |
| --------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-000     | Source Trace Requirement states each term should carry source group or source record where possible.                                                                                                           |
| GL-CONT-000     | Foundational Source Rules define prior documents, taxonomy, canonical responsibilities, delegation/enabling matrices, anti-collapse rules, ID grammar, user decisions, and future proposals as source classes. |
| SYSTEM_GOALS.md | Future roadmap milestones and tests should reference goal IDs and trace chains.                                                                                                                                |

---

### GL-TRC-015 — Join Key

| Field           | Value                           |
| --------------- | ------------------------------- |
| Term ID         | GL-TRC-015                      |
| Canonical Term  | Join Key                        |
| Family          | TRC / DOC                       |
| Category        | identifier / traceability_model |
| Ownership Scope | governed                        |
| Entry Maturity  | canonical_full                  |
| Evidence Status | direct / derived                |

#### Definition

A Join Key is a stable identifier used to connect glossary terms, source records, goals, responsibilities, obligations, delegations, enablements, capability candidates, validation records, and later representation artifacts without relying on text similarity.

#### Architectural Role

Join Key supports future CSV, JSON, database, and compliance representations.

It enables:

1. glossary-to-goal joins,
2. goal-to-obligation joins,
3. responsibility-to-delegation joins,
4. contract-to-capability joins,
5. source-to-term joins,
6. pack-to-pack joins,
7. validation-to-record joins,
8. PostgreSQL or JSON derivation readiness.

Join Keys must preserve row grain and namespace clarity.

#### Must Not Be Confused With

1. Human-readable label only.
2. Display title.
3. File path.
4. C++ symbol.
5. Database primary key by default.
6. Text search match.

#### Valid Usage

* “Term ID can act as a join key across glossary packs.”
* “Goal IDs can be joined to validation records.”
* “Join Keys prevent dependency on textual similarity.”

#### Invalid Usage

* “Join Key is the same as a paragraph title.”
* “Join Key can be inferred from approximate wording.”
* “Join Key must be a database key immediately.”
* “Join Key is a package path.”

#### Related Terms

* GL-TRC-016 — ID Namespace
* GL-TRC-014 — Source Trace
* GL-TRC-010 — Traceability
* GL-CONT-000-SRC-006 — ID Grammar and Join-Key Rules

#### Source Trace

| Source Type             | Source                                                                                                                |
| ----------------------- | --------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-000             | Source rules include ID Grammar and Join-Key Rules: namespaces, join keys, row grain, source trace, validation rules. |
| GL-CONT-000             | Representation readiness requires later CSV and JSON support without forcing early population.                        |
| System Governance Basis | Goal IDs and record IDs are intended as stable references for roadmap, tests, and compliance matrices.                |

---

### GL-TRC-016 — ID Namespace

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-TRC-016           |
| Canonical Term  | ID Namespace         |
| Family          | TRC / DOC            |
| Category        | identifier_namespace |
| Ownership Scope | governed             |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

An ID Namespace is a declared identifier scope that gives meaning to record IDs, term IDs, goal IDs, source IDs, contract IDs, responsibility IDs, and future representation IDs.

An ID must be interpreted within its namespace.

#### Architectural Role

ID Namespace prevents identifier collision and false joins.

Examples include:

1. `GL-SYS-*`,
2. `GL-BND-*`,
3. `GL-EXT-*`,
4. `GL-ENT-*`,
5. `GL-OBJ-*`,
6. `GL-RUN-*`,
7. `GL-CON-*`,
8. `GL-CPP-*`,
9. `GL-TRC-*`,
10. `GL-POL-*`,
11. `GL-EXC-*`,
12. `SG-*`,
13. `RM-*`.

ID Namespace allows later representation packs to convert content into structured records safely.

#### Must Not Be Confused With

1. Folder namespace by default.
2. C++ namespace by default.
3. Database schema by default.
4. File prefix only.
5. Visual grouping only.
6. Informal abbreviation.

#### Valid Usage

* “GL-TRC is the namespace for traceability terms.”
* “SG-ID is a goal namespace.”
* “ID Namespace must be declared before using IDs as join keys.”

#### Invalid Usage

* “Same number means same record across namespaces.”
* “Namespace can be ignored in joins.”
* “ID Namespace is automatically a C++ namespace.”
* “ID Namespace is only decorative.”

#### Related Terms

* GL-TRC-015 — Join Key
* GL-TRC-014 — Source Trace
* GL-TRC-010 — Traceability
* GL-CONT-000 — Glossary Governance
* GL-DOC-* — Documentation Governance Terms

#### Source Trace

| Source Type     | Source                                                                                   |
| --------------- | ---------------------------------------------------------------------------------------- |
| GL-CONT-000     | ID Grammar rules require IDs to be read according to declared namespace.                 |
| GL-CONT-000     | Term Families and Category Model provide structured namespace basis.                     |
| SYSTEM_GOALS.md | Goal IDs are stable references for future roadmap items, tests, and compliance matrices. |

---

### GL-TRC-017 — Responsibility Chain

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-TRC-017           |
| Canonical Term  | Responsibility Chain |
| Family          | TRC                  |
| Category        | derivation_chain     |
| Ownership Scope | governed             |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

The Responsibility Chain is the canonical derivation chain used by the Assembler System to move from external/boundary interaction to implementation-facing capability candidates.

The chain is:

```text id="gl-trc-017-chain"
External Relation
→ Contract
→ Responsibility
→ Obligation
→ Delegation
→ Enablement
→ Capability Candidate
```

#### Architectural Role

The Responsibility Chain is the system’s primary anti-arbitrary-implementation model.

It ensures that future artifacts derive from controlled architectural logic.

It governs:

1. roadmap milestones,
2. semantic domain derivation,
3. package derivation,
4. contract expansion,
5. capability candidate derivation,
6. C++ abstraction derivation,
7. processing-unit derivation,
8. compliance and test derivation.

#### Must Not Be Confused With

1. Runtime call chain.
2. Inheritance hierarchy.
3. Folder hierarchy.
4. Dependency graph by default.
5. User journey.
6. CI pipeline.

#### Valid Usage

* “Capability candidates must preserve the Responsibility Chain.”
* “Roadmap derivation should follow the Responsibility Chain.”
* “The chain prevents class-first architecture.”

#### Invalid Usage

* “Responsibility Chain is a runtime stack trace.”
* “Responsibility Chain is a package dependency list.”
* “Responsibility Chain can start from a class name.”
* “Responsibility Chain can skip Contract.”

#### Related Terms

* GL-TRC-004 — External Relation
* GL-CON-001 — Contract
* GL-TRC-005 — Responsibility
* GL-TRC-006 — Obligation
* GL-TRC-007 — Delegation
* GL-TRC-008 — Enablement
* GL-TRC-009 — Capability Candidate

#### Source Trace

| Source Type        | Source                                                                                                       |
| ------------------ | ------------------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines the canonical responsibility chain.                                                                  |
| SYSTEM_GOALS.md    | Preserves the same chain under Responsibility and Traceability Goals.                                        |
| GL-CONT-006        | Contract-to-Capability Derivation extends the chain toward abstract C++ layer and concrete processing units. |

---

### GL-TRC-018 — Responsibility Owner

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-TRC-018           |
| Canonical Term  | Responsibility Owner |
| Family          | TRC / ENT            |
| Category        | responsibility_owner |
| Ownership Scope | governed             |
| Entry Maturity  | canonical_full       |
| Evidence Status | derived              |

#### Definition

A Responsibility Owner is the architectural carrier assigned primary responsibility for achieving a Responsibility under the relevant Contract and Obligation.

A Responsibility Owner may be an actor, delegated entity, port, contract surface, carrier object, runtime structure, or future capability candidate, depending on the nature of the responsibility.

#### Architectural Role

Responsibility Owner clarifies who or what carries primary responsibility.

It prevents supporting entities from being mistaken for primary owners.

Examples:

1. `Envelope Assembler` may own envelope realization responsibility.
2. `Assembler Ingress Port` may own envelope admission responsibility.
3. `PolicyAssigner` may own policy assignment responsibility.
4. `Dispatcher` may own final outbound handoff responsibility.
5. `Queue Container` may own slot-structure responsibility.
6. `Log Level Envelope` may carry envelope-carrier responsibility as object, not actor.

#### Must Not Be Confused With

1. Supporting entity.
2. Whole subsystem by default.
3. Code owner.
4. GitHub assignee.
5. Package maintainer.
6. Runtime thread.
7. Human operator by default.

#### Valid Usage

* “Primary responsibility owner must be explicit.”
* “Supporting entities contribute without becoming owners by default.”
* “Responsibility Owner must satisfy narrow-carrier rule.”

#### Invalid Usage

* “Every supporting entity is a responsibility owner.”
* “Responsibility Owner means GitHub code owner.”
* “Responsibility Owner must always be an actor.”
* “Responsibility Owner can ignore contract obligations.”

#### Related Terms

* GL-TRC-003 — Primary Responsibility Owner
* GL-TRC-002 — Supporting Entity
* GL-TRC-007 — Delegation
* GL-TRC-013 — Narrow Mature Architectural Carrier
* GL-ENT-* — Internal Actors and Delegated Entities

#### Source Trace

| Source Type     | Source                                                                                            |
| --------------- | ------------------------------------------------------------------------------------------------- |
| GL-CONT-003     | Defines Primary Responsibility Owner and Supporting Entity distinctions.                          |
| SYSTEM_GOALS.md | SG-TRACE-004 states supporting entities shall not be confused with primary responsibility owners. |
| SYSTEM_GOALS.md | SG-TRACE-003 requires narrow mature carrier selection.                                            |

---

### GL-TRC-019 — Reviewable Guarantee

| Field           | Value                           |
| --------------- | ------------------------------- |
| Term ID         | GL-TRC-019                      |
| Canonical Term  | Reviewable Guarantee            |
| Family          | TRC                             |
| Category        | obligation / validation_concept |
| Ownership Scope | governed                        |
| Entry Maturity  | canonical_full                  |
| Evidence Status | derived                         |

#### Definition

A Reviewable Guarantee is an obligation statement that can be checked through documentation review, architecture review, compliance matrix review, test derivation, or future implementation verification.

It makes a Responsibility auditable.

#### Architectural Role

Reviewable Guarantee turns a responsibility into something that can be verified.

Examples:

1. raw content does not replace Log Level Envelope,
2. queue remains container, not broker,
3. dispatcher remains final outbound actor,
4. authority closes after valid handoff,
5. Metadata Injector is not policy-hosted,
6. capability candidates do not automatically become classes/packages.

A Reviewable Guarantee may later become a test, but it is not only a test.

#### Must Not Be Confused With

1. Unit test only.
2. Runtime assertion only.
3. CI check only.
4. Legal guarantee.
5. Performance SLA by default.
6. Informal comment.

#### Valid Usage

* “Every responsibility should have at least one Reviewable Guarantee.”
* “Anti-collapse statements are reviewable guarantees.”
* “Reviewable Guarantee can later feed compliance matrix rows.”

#### Invalid Usage

* “Reviewable Guarantee only exists in code.”
* “Reviewable Guarantee is optional.”
* “Reviewable Guarantee is the same as unit test.”
* “Reviewable Guarantee can be vague.”

#### Related Terms

* GL-TRC-006 — Obligation
* GL-TRC-005 — Responsibility
* GL-CON-013 — Contract Compliance
* GL-CON-014 — Contract Violation
* GL-TRC-012 — Anti-Regression Rule

#### Source Trace

| Source Type     | Source                                                                                              |
| --------------- | --------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-TRACE-002 requires every responsibility to have at least one obligation or reviewable guarantee. |
| SYSTEM_GOALS.md | Goals are reviewable and should guide compliance checks, tests, and future derivation.              |
| GL-CONT-006     | Contract Compliance is not limited to code tests and may begin as documentation review.             |

---

### GL-TRC-020 — Derivation Source

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-TRC-020          |
| Canonical Term  | Derivation Source   |
| Family          | TRC / DOC           |
| Category        | traceability_source |
| Ownership Scope | governed            |
| Entry Maturity  | canonical_full      |
| Evidence Status | derived             |

#### Definition

A Derivation Source is the authoritative basis from which a term, responsibility, obligation, delegation, enablement, capability candidate, contract, domain, package, abstraction, or validation record is derived.

#### Architectural Role

Derivation Source controls legitimacy.

Valid derivation sources may include:

1. foundational documents,
2. glossary packs,
3. system goals,
4. contract families,
5. boundary doctrine,
6. authority exclusions,
7. runtime doctrine,
8. object doctrine,
9. responsibility chain records,
10. explicit user decisions,
11. canonical source-data records.

A derivation source should be stable enough to support future artifacts.

#### Must Not Be Confused With

1. Inspiration.
2. Naming similarity.
3. Folder layout.
4. Existing code by default.
5. Personal preference.
6. Unreviewed assumption.

#### Valid Usage

* “The derivation source for this capability candidate is SG-TRACE-003 plus GL-CON-012.”
* “Semantic domains require derivation sources.”
* “A package should not be derived from folder convenience alone.”

#### Invalid Usage

* “Derivation Source is whatever name sounds right.”
* “Derivation Source can be a vague memory.”
* “Derivation Source is the implementation file.”
* “Derivation Source can ignore source trace.”

#### Related Terms

* GL-TRC-014 — Source Trace
* GL-TRC-010 — Traceability
* GL-TRC-015 — Join Key
* GL-DER-001 — Architecture-to-Implementation Derivation
* GL-CON-015 — Contract-to-Capability Derivation

#### Source Trace

| Source Type       | Source                                                                                                                                                                                                         |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-000       | Source Dependency Rule defines valid source classes.                                                                                                                                                           |
| VisionAndScope.md | Domain derivation must come from architectural taxonomy, entity separation, responsibilities, obligations, delegation, enablement, governed objects, boundary ports, doctrine rules, and authority exclusions. |
| Roadmap Basis     | Dependency-first and governance-before-derivation ordering require explicit derivation sources.                                                                                                                |

---

### GL-TRC-021 — Capability Surface

| Field           | Value              |
| --------------- | ------------------ |
| Term ID         | GL-TRC-021         |
| Canonical Term  | Capability Surface |
| Family          | TRC / DER          |
| Category        | enablement_surface |
| Ownership Scope | governed / future  |
| Entry Maturity  | canonical_partial  |
| Evidence Status | derived            |

#### Definition

A Capability Surface is a future-facing surface, abstraction area, contract-facing mechanism, or readiness point through which an Enablement may later become a Capability Candidate or implementation artifact.

It is a bridge term between enablement and future derivation.

#### Architectural Role

Capability Surface may describe where capability could appear without committing to a final class, package, or function.

Examples may include:

1. ingress admission surface,
2. envelope carrier surface,
3. metadata preparation surface,
4. timestamp stabilization surface,
5. policy assignment surface,
6. runtime-state surface,
7. handoff eligibility surface,
8. exclusion guard surface,
9. traceability/reporting surface.

Capability Surface must remain governed by source trace and contract families.

#### Must Not Be Confused With

1. Final API.
2. C++ interface by default.
3. Package.
4. Runtime endpoint.
5. Deployed service.
6. User-facing feature by default.

#### Valid Usage

* “Capability Surface identifies where an enablement could later be represented.”
* “Runtime State Contract Family may expose runtime-state capability surfaces.”
* “Capability Surface is not final implementation.”

#### Invalid Usage

* “Capability Surface is the final API.”
* “Capability Surface is automatically an interface.”
* “Capability Surface can be derived without contract.”
* “Capability Surface replaces capability candidate.”

#### Related Terms

* GL-TRC-008 — Enablement
* GL-TRC-009 — Capability Candidate
* GL-CON-004 — Contract Family
* GL-CON-015 — Contract-to-Capability Derivation
* GL-CPP-004 — Template Abstraction Layer

#### Source Trace

| Source Type     | Source                                                                                       |
| --------------- | -------------------------------------------------------------------------------------------- |
| GL-CONT-006     | Future abstraction candidates derive from contract families.                                 |
| SYSTEM_GOALS.md | Enablement must not be treated as final implementation.                                      |
| Roadmap Basis   | Capability Candidate Derivation prepares for abstractions without jumping to concrete units. |

---

### GL-TRC-022 — Capability Realization

| Field           | Value                  |
| --------------- | ---------------------- |
| Term ID         | GL-TRC-022             |
| Canonical Term  | Capability Realization |
| Family          | TRC / DER              |
| Category        | future_derivation      |
| Ownership Scope | future                 |
| Entry Maturity  | canonical_partial      |
| Evidence Status | derived                |

#### Definition

Capability Realization is the future act of turning a validated Capability Candidate into a concrete implementation artifact, such as an abstraction, processing unit, package component, test fixture, or example pipeline.

It is outside the immediate scope of this pack.

#### Architectural Role

Capability Realization marks the boundary between pre-implementation architecture and later implementation derivation.

It must occur only after:

1. source trace is clear,
2. contract is stable,
3. responsibility is explicit,
4. obligation is reviewable,
5. delegation target is valid,
6. enablement is described,
7. capability candidate is justified,
8. anti-collapse rules are preserved,
9. relevant contract family is known.

Capability Realization is future-facing and must be governed by roadmap phases.

#### Must Not Be Confused With

1. Capability Candidate.
2. Enablement.
3. Contract.
4. Immediate code creation.
5. Package-first design.
6. Folder taxonomy.

#### Valid Usage

* “Capability Realization comes after Capability Candidate validation.”
* “Processing-unit derivation is one form of future capability realization.”
* “Capability Realization must preserve trace chain integrity.”

#### Invalid Usage

* “Capability Realization can start from a class name.”
* “Capability Realization replaces responsibility mapping.”
* “Capability Realization is allowed before gap closure.”
* “Capability Realization can ignore anti-regression rules.”

#### Related Terms

* GL-TRC-009 — Capability Candidate
* GL-TRC-011 — Gap Closure
* GL-TRC-023 — Trace Chain Integrity
* GL-DER-003 — Implementation Derivation
* GL-CPP-004 — Template Abstraction Layer
* GL-CPP-005 — CRTP Abstraction

#### Source Trace

| Source Type     | Source                                                                                                                                                              |
| --------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-006     | Contract-to-Capability Derivation extends toward abstract C++ layer and concrete processing unit.                                                                   |
| Roadmap Basis   | Processing Unit Derivation comes after contracts, responsibility/obligation mapping, enablement, capability candidate derivation, and C++ abstraction architecture. |
| SYSTEM_GOALS.md | Capability candidates do not automatically become classes, functions, or packages.                                                                                  |

---

### GL-TRC-023 — Trace Chain Integrity

| Field           | Value                                    |
| --------------- | ---------------------------------------- |
| Term ID         | GL-TRC-023                               |
| Canonical Term  | Trace Chain Integrity                    |
| Family          | TRC / GUARD                              |
| Category        | validation_concept / anti_collapse_guard |
| Ownership Scope | governed                                 |
| Entry Maturity  | canonical_full                           |
| Evidence Status | derived                                  |

#### Definition

Trace Chain Integrity is the condition that a derivation chain remains complete, ordered, source-backed, and semantically valid from source relation through contract, responsibility, obligation, delegation, enablement, and capability candidate.

#### Architectural Role

Trace Chain Integrity prevents broken derivations.

A trace chain lacks integrity if:

1. it starts from a package name instead of a derivation source,
2. it skips Contract,
3. it creates Responsibility without source,
4. it defines Responsibility without Obligation,
5. it delegates to an invalid or too-broad carrier,
6. it treats Enablement as final implementation,
7. it treats Capability Candidate as final class/package,
8. it violates anti-collapse rules,
9. it lacks join keys or stable IDs,
10. it ignores authority exclusions.

Trace Chain Integrity is required before future derivation.

#### Must Not Be Confused With

1. Runtime trace completeness.
2. Log correlation.
3. Git history.
4. Documentation formatting.
5. Table completeness only.
6. Naming consistency only.

#### Valid Usage

* “This capability candidate passes trace chain integrity review.”
* “Missing obligation breaks trace chain integrity.”
* “Package derivation must require trace chain integrity.”

#### Invalid Usage

* “Trace Chain Integrity is only about formatting.”
* “Trace Chain Integrity can be inferred from similar names.”
* “Trace Chain Integrity allows skipped contracts.”
* “Trace Chain Integrity is runtime telemetry.”

#### Related Terms

* GL-TRC-010 — Traceability
* GL-TRC-017 — Responsibility Chain
* GL-TRC-011 — Gap Closure
* GL-TRC-012 — Anti-Regression Rule
* GL-TRC-015 — Join Key
* GL-TRC-016 — ID Namespace

#### Source Trace

| Source Type     | Source                                                                                                                                                                   |
| --------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| SYSTEM_GOALS.md | Responsibility and Traceability Goals require source-backed responsibilities, obligations, narrow delegation, non-final enablement, and non-final capability candidates. |
| GL-CONT-006     | Correct derivation rule prohibits deriving templates from naming preference, processing units from folders, or contracts from pre-written classes.                       |
| Roadmap Basis   | Dependency-first, governance-before-derivation, and compliance-before-expansion rules require chain integrity before expansion.                                          |

---

## 5. Responsibility Chain Governance Matrix

|           Record ID | Chain Step           | Governs                               | Must Be Present Before                       | Must Not Collapse Into       |
| ------------------: | -------------------- | ------------------------------------- | -------------------------------------------- | ---------------------------- |
| GL-CONT-007-RCG-001 | External Relation    | Boundary-facing interaction           | Contract                                     | Internal actor               |
| GL-CONT-007-RCG-002 | Contract             | Architectural law                     | Responsibility                               | C++ interface/class/template |
| GL-CONT-007-RCG-003 | Responsibility       | Required outcome                      | Obligation                                   | Class/function/package       |
| GL-CONT-007-RCG-004 | Obligation           | Reviewable guarantee or constraint    | Delegation                                   | Unit test only               |
| GL-CONT-007-RCG-005 | Delegation           | Assignment to valid carrier           | Enablement                                   | Package ownership            |
| GL-CONT-007-RCG-006 | Enablement           | Capability basis or support condition | Capability Candidate                         | Final implementation         |
| GL-CONT-007-RCG-007 | Capability Candidate | Implementation-facing possibility     | C++ abstraction / processing-unit derivation | Final class/function/package |

---

## 6. Responsibility-to-Carrier Examples

|            Record ID | Responsibility Area       | Likely Narrow Carrier  | Obligation Example                                             | Enablement Example                           |
| -------------------: | ------------------------- | ---------------------- | -------------------------------------------------------------- | -------------------------------------------- |
| GL-CONT-007-RCEX-001 | Envelope realization      | Envelope Assembler     | Must produce Log Level Envelope before ingress-port admission  | Ingress Contract Family                      |
| GL-CONT-007-RCEX-002 | Envelope admission        | Assembler Ingress Port | Must receive envelopes, not raw payloads                       | Slot and Queue Container admission semantics |
| GL-CONT-007-RCEX-003 | Metadata preparation      | Metadata Injector      | Must remain schema/directive-governed, not policy-hosted       | Metadata / Preparation Contract Family       |
| GL-CONT-007-RCEX-004 | Timestamp stabilization   | Timestamp Stabilizer   | Must stabilize timestamp semantics before dispatch eligibility | Timestamp preparation path                   |
| GL-CONT-007-RCEX-005 | Policy assignment         | PolicyAssigner         | Must not become policy source or policy object                 | Policy / Ecosystem Contract Family           |
| GL-CONT-007-RCEX-006 | Queue-bundle coordination | Queue Bundle Agent     | Must not become message broker                                 | Queue Bundle and Waiting List semantics      |
| GL-CONT-007-RCEX-007 | Single-queue moderation   | Single Queue Moderator | Must preserve occupancy/lifecycle distinction                  | Single Queue Container model                 |
| GL-CONT-007-RCEX-008 | Final handoff             | Dispatcher             | Must remain final assembler-side outbound actor                | Registry / Dispatcher Contract Family        |
| GL-CONT-007-RCEX-009 | Slot structure            | Queue Container        | Must own slot structure, not downstream lifecycle              | Runtime State Contract Family                |
| GL-CONT-007-RCEX-010 | Carrier semantics         | Log Level Envelope     | Must remain carrier object, not actor                          | Envelope Carrier Contract Family             |

---

## 7. Capability Candidate Derivation Matrix

|           Record ID | Capability Candidate Area          | Required Inputs                                                                                                                             | Not Yet Allowed               |
| ------------------: | ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------- |
| GL-CONT-007-CCD-001 | Ingress Admission Capability       | External Relation, Ingress Contract Family, envelope admission responsibility, slot admission obligation, Assembler Ingress Port delegation | Final ingress class           |
| GL-CONT-007-CCD-002 | Envelope Carrier Capability        | Envelope Carrier Contract Family, carrier-object responsibility, non-actor obligation, Log Level Envelope delegation                        | Final envelope implementation |
| GL-CONT-007-CCD-003 | Metadata Preparation Capability    | Metadata / Preparation Contract Family, metadata preparation responsibility, non-policy-host obligation, Metadata Injector delegation       | Final metadata module         |
| GL-CONT-007-CCD-004 | Timestamp Stabilization Capability | Metadata / Preparation Contract Family, timestamp stabilization responsibility, pre-dispatch obligation, Timestamp Stabilizer delegation    | Final timestamp class         |
| GL-CONT-007-CCD-005 | Policy Assignment Capability       | Policy / Ecosystem Contract Family, policy assignment responsibility, PolicyAssigner delegation, policy-object distinction obligation       | Final policy engine           |
| GL-CONT-007-CCD-006 | Queue Runtime Capability           | Runtime State Contract Family, queue/container responsibility, queue-as-container obligation, runtime actor delegation                      | Message broker package        |
| GL-CONT-007-CCD-007 | Handoff Eligibility Capability     | Registry / Dispatcher Contract Family, dispatch readiness responsibility, Dispatcher delegation, authority-closure obligation               | Downstream registry logic     |
| GL-CONT-007-CCD-008 | Exclusion Guard Capability         | Exclusion Contract Family, non-ownership responsibility, anti-regression obligation, boundary/authority delegation                          | Optional non-goal list        |

---

## 8. Anti-Collapse Index

|          Record ID | Term                                | Must Not Collapse Into       | Guard Meaning                                                            |
| -----------------: | ----------------------------------- | ---------------------------- | ------------------------------------------------------------------------ |
| GL-CONT-007-AC-001 | External Relation                   | Internal actor               | Boundary interaction does not create internal execution entity by itself |
| GL-CONT-007-AC-002 | Responsibility                      | Class/function/package       | Responsibility is architectural duty, not implementation artifact        |
| GL-CONT-007-AC-003 | Obligation                          | Unit test only               | Obligation is reviewable guarantee before test realization               |
| GL-CONT-007-AC-004 | Delegation                          | Package ownership            | Delegation assigns responsibility to valid architectural carrier         |
| GL-CONT-007-AC-005 | Enablement                          | Final implementation         | Enablement is support condition or capability basis                      |
| GL-CONT-007-AC-006 | Capability Candidate                | Final class/function/package | Candidate remains pre-implementation until realized later                |
| GL-CONT-007-AC-007 | Traceability                        | Runtime tracing              | Traceability is derivation/source governance                             |
| GL-CONT-007-AC-008 | Gap Closure                         | Guess filling                | Gap closure requires evidence or formal decision                         |
| GL-CONT-007-AC-009 | Anti-Regression Rule                | Optional test                | Anti-regression protects architecture across derivation                  |
| GL-CONT-007-AC-010 | Narrow Mature Architectural Carrier | Whole subsystem by default   | Carrier must be specific and mature enough                               |
| GL-CONT-007-AC-011 | Source Trace                        | Text similarity              | Source trace requires stable source basis                                |
| GL-CONT-007-AC-012 | Join Key                            | Display title                | Join key supports stable structured joins                                |
| GL-CONT-007-AC-013 | ID Namespace                        | C++ namespace by default     | ID namespace governs identifier interpretation                           |
| GL-CONT-007-AC-014 | Responsibility Chain                | Runtime call chain           | Chain is derivation model                                                |
| GL-CONT-007-AC-015 | Responsibility Owner                | Code owner                   | Owner is architectural carrier                                           |
| GL-CONT-007-AC-016 | Reviewable Guarantee                | CI check only                | Guarantee exists before implementation                                   |
| GL-CONT-007-AC-017 | Derivation Source                   | Naming preference            | Source must be authoritative                                             |
| GL-CONT-007-AC-018 | Capability Surface                  | Final API                    | Surface is future-facing enablement area                                 |
| GL-CONT-007-AC-019 | Capability Realization              | Capability Candidate         | Realization is later transformation                                      |
| GL-CONT-007-AC-020 | Trace Chain Integrity               | Formatting consistency       | Integrity requires ordered, source-backed derivation                     |

---

## 9. Responsibility Chain Integrity Checklist

|           Record ID | Check                                                    | Expected Result |
| ------------------: | -------------------------------------------------------- | --------------- |
| GL-CONT-007-TCI-001 | External Relation is identified                          | Pass            |
| GL-CONT-007-TCI-002 | Governing Contract is identified                         | Pass            |
| GL-CONT-007-TCI-003 | Responsibility is explicitly stated                      | Pass            |
| GL-CONT-007-TCI-004 | Responsibility is not treated as class/function/package  | Pass            |
| GL-CONT-007-TCI-005 | At least one Obligation or Reviewable Guarantee exists   | Pass            |
| GL-CONT-007-TCI-006 | Delegation target is explicit                            | Pass            |
| GL-CONT-007-TCI-007 | Delegation target is narrow and mature                   | Pass            |
| GL-CONT-007-TCI-008 | Supporting entities are not mistaken for primary owners  | Pass            |
| GL-CONT-007-TCI-009 | Enablement is described                                  | Pass            |
| GL-CONT-007-TCI-010 | Enablement is not final implementation                   | Pass            |
| GL-CONT-007-TCI-011 | Capability Candidate is derived, not invented            | Pass            |
| GL-CONT-007-TCI-012 | Capability Candidate is not final class/function/package | Pass            |
| GL-CONT-007-TCI-013 | Source Trace exists where possible                       | Pass            |
| GL-CONT-007-TCI-014 | Join Keys are stable where representation is expected    | Pass            |
| GL-CONT-007-TCI-015 | ID Namespace is declared                                 | Pass            |
| GL-CONT-007-TCI-016 | Anti-collapse rules are preserved                        | Pass            |
| GL-CONT-007-TCI-017 | Authority exclusions are not violated                    | Pass            |
| GL-CONT-007-TCI-018 | Gap Closure status is clear                              | Pass            |
| GL-CONT-007-TCI-019 | Anti-Regression Rule exists for stabilized distinctions  | Pass            |
| GL-CONT-007-TCI-020 | Future realization is deferred until roadmap phase       | Pass            |

---

## 10. Pack Dependency Map

|           Record ID | This Pack Concept       | Depends On                                                                                 | Enables                                               |
| ------------------: | ----------------------- | ------------------------------------------------------------------------------------------ | ----------------------------------------------------- |
| GL-CONT-007-DEP-001 | External Relation       | GL-CONT-002 boundary and external context terms                                            | Contract-driven responsibility derivation             |
| GL-CONT-007-DEP-002 | Responsibility          | GL-CONT-006 contract terms                                                                 | Obligation and delegation mapping                     |
| GL-CONT-007-DEP-003 | Obligation              | GL-CONT-006 contract compliance and violation terms                                        | Reviewable guarantees and compliance matrix           |
| GL-CONT-007-DEP-004 | Delegation              | GL-CONT-003 actors/delegated entities, GL-CONT-004 objects, GL-CONT-005 runtime structures | Enablement mapping                                    |
| GL-CONT-007-DEP-005 | Enablement              | Contract families and delegation targets                                                   | Capability Candidate derivation                       |
| GL-CONT-007-DEP-006 | Capability Candidate    | Full responsibility chain                                                                  | Future C++ abstraction and processing-unit derivation |
| GL-CONT-007-DEP-007 | Traceability            | GL-CONT-000 source trace and ID governance                                                 | CSV/JSON/population/validation readiness              |
| GL-CONT-007-DEP-008 | Gap Closure             | Entry maturity and traceability requirements                                               | Safe roadmap progression                              |
| GL-CONT-007-DEP-009 | Anti-Regression Rule    | Anti-collapse and exclusion rules                                                          | Compliance-before-expansion discipline                |
| GL-CONT-007-DEP-010 | Join Key / ID Namespace | GL-CONT-000 ID grammar and source rules                                                    | Structured representation packs                       |

---

## 11. Future Representation Readiness

This pack is designed to support later structured representations.

### 11.1 Candidate Future Tables or JSON Collections

|           Record ID | Representation Area     | Likely Row Grain                                       |
| ------------------: | ----------------------- | ------------------------------------------------------ |
| GL-CONT-007-REP-001 | `external_relations`    | One external relation record                           |
| GL-CONT-007-REP-002 | `responsibilities`      | One responsibility record                              |
| GL-CONT-007-REP-003 | `obligations`           | One obligation per responsibility or obligation family |
| GL-CONT-007-REP-004 | `delegations`           | One responsibility-to-carrier assignment               |
| GL-CONT-007-REP-005 | `enablements`           | One enablement record                                  |
| GL-CONT-007-REP-006 | `capability_candidates` | One candidate derived from a complete chain            |
| GL-CONT-007-REP-007 | `trace_chains`          | One full derivation chain                              |
| GL-CONT-007-REP-008 | `gap_closures`          | One gap or closure action                              |
| GL-CONT-007-REP-009 | `anti_regression_rules` | One anti-regression rule                               |
| GL-CONT-007-REP-010 | `join_key_registry`     | One stable join-key record                             |

### 11.2 Representation Constraint

```text id="gl-cont-007-representation-constraint"
Structured representation must preserve chain order, row grain,
ID namespace, join keys, source trace, and anti-collapse rules.
```

---

## 12. Validation Checklist

|           Record ID | Check                                                           | Expected Result |
| ------------------: | --------------------------------------------------------------- | --------------- |
| GL-CONT-007-VAL-001 | External Relation is defined as boundary-facing relation        | Pass            |
| GL-CONT-007-VAL-002 | Responsibility is defined as architectural duty, not code       | Pass            |
| GL-CONT-007-VAL-003 | Obligation is defined as reviewable guarantee/constraint        | Pass            |
| GL-CONT-007-VAL-004 | Delegation targets narrow mature carrier                        | Pass            |
| GL-CONT-007-VAL-005 | Enablement is not final implementation                          | Pass            |
| GL-CONT-007-VAL-006 | Capability Candidate is not final class/function/package        | Pass            |
| GL-CONT-007-VAL-007 | Traceability is not runtime tracing                             | Pass            |
| GL-CONT-007-VAL-008 | Gap Closure prevents false completeness                         | Pass            |
| GL-CONT-007-VAL-009 | Anti-Regression Rule protects stabilized distinctions           | Pass            |
| GL-CONT-007-VAL-010 | Narrow Mature Architectural Carrier is defined                  | Pass            |
| GL-CONT-007-VAL-011 | Source Trace is defined                                         | Pass            |
| GL-CONT-007-VAL-012 | Join Key is defined                                             | Pass            |
| GL-CONT-007-VAL-013 | ID Namespace is defined                                         | Pass            |
| GL-CONT-007-VAL-014 | Responsibility Chain is defined and ordered                     | Pass            |
| GL-CONT-007-VAL-015 | Responsibility Owner is not code owner by default               | Pass            |
| GL-CONT-007-VAL-016 | Reviewable Guarantee is not test-only                           | Pass            |
| GL-CONT-007-VAL-017 | Derivation Source is authoritative basis, not naming preference | Pass            |
| GL-CONT-007-VAL-018 | Capability Surface is future-facing, not final API              | Pass            |
| GL-CONT-007-VAL-019 | Capability Realization is deferred to later derivation          | Pass            |
| GL-CONT-007-VAL-020 | Trace Chain Integrity is defined                                | Pass            |
| GL-CONT-007-VAL-021 | Pack supports Roadmap derivation                                | Pass            |
| GL-CONT-007-VAL-022 | Pack supports package derivation without package-first design   | Pass            |
| GL-CONT-007-VAL-023 | Pack supports GL-CONT-008 and GL-CONT-009                       | Pass            |
| GL-CONT-007-VAL-024 | Anti-collapse index is included                                 | Pass            |

---

## 13. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                          | Status   |
| -------------------: | ------------------------------------------------------- | -------- |
| GL-CONT-007-EXIT-001 | External Relation is formally defined                   | Complete |
| GL-CONT-007-EXIT-002 | Responsibility is formally defined                      | Complete |
| GL-CONT-007-EXIT-003 | Obligation is formally defined                          | Complete |
| GL-CONT-007-EXIT-004 | Delegation is formally defined                          | Complete |
| GL-CONT-007-EXIT-005 | Enablement is formally defined                          | Complete |
| GL-CONT-007-EXIT-006 | Capability Candidate is formally defined                | Complete |
| GL-CONT-007-EXIT-007 | Traceability is formally defined                        | Complete |
| GL-CONT-007-EXIT-008 | Gap Closure is formally defined                         | Complete |
| GL-CONT-007-EXIT-009 | Anti-Regression Rule is formally defined                | Complete |
| GL-CONT-007-EXIT-010 | Narrow Mature Architectural Carrier is formally defined | Complete |
| GL-CONT-007-EXIT-011 | Source Trace is formally defined                        | Complete |
| GL-CONT-007-EXIT-012 | Join Key is formally defined                            | Complete |
| GL-CONT-007-EXIT-013 | ID Namespace is formally defined                        | Complete |
| GL-CONT-007-EXIT-014 | Responsibility Chain is formally preserved              | Complete |
| GL-CONT-007-EXIT-015 | Responsibility-to-carrier examples are included         | Complete |
| GL-CONT-007-EXIT-016 | Capability candidate derivation matrix is included      | Complete |
| GL-CONT-007-EXIT-017 | Anti-collapse index is included                         | Complete |
| GL-CONT-007-EXIT-018 | Trace chain integrity checklist is included             | Complete |
| GL-CONT-007-EXIT-019 | Future representation readiness is included             | Complete |
| GL-CONT-007-EXIT-020 | Pack is ready to support GL-CONT-008 and GL-CONT-009    | Complete |

---

## 14. Summary

`GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack` establishes the controlled vocabulary for architecture-to-implementation traceability.

The pack preserves the canonical derivation chain:

```text id="gl-cont-007-summary-chain"
External Relation
→ Contract
→ Responsibility
→ Obligation
→ Delegation
→ Enablement
→ Capability Candidate
```

It also stabilizes the following rules:

```text id="gl-cont-007-summary-rules"
Responsibility ≠ class/function/package
Obligation ≠ unit test only
Delegation ≠ package ownership
Enablement ≠ final implementation
Capability Candidate ≠ automatic class/function/package
Traceability ≠ runtime tracing
Join Key ≠ display title
ID Namespace ≠ C++ namespace by default
```

The pack prepares the Assembler System for:

1. policy/governance term expansion,
2. dispatcher and handoff term expansion,
3. roadmap derivation,
4. semantic domain derivation,
5. package derivation,
6. capability matrix derivation,
7. compliance matrix derivation,
8. C++ abstraction derivation.

The next glossary content pack is:

```text id="gl-cont-007-next"
GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack
```
