
# GL-CONT-003 — Internal Actors and Delegated Entities Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-003-DOC-001 | Pack Name | GL-CONT-003 — Internal Actors and Delegated Entities Pack |
| GL-CONT-003-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-003-DOC-003 | Project | Assembler System |
| GL-CONT-003-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-003-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-003-DOC-006 | Language | English |
| GL-CONT-003-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002 |
| GL-CONT-003-DOC-008 | Scope | Internal actors, delegated entities, supporting entities, responsibility ownership vocabulary |
| GL-CONT-003-DOC-009 | Excluded From This Pack | Governed object definitions, runtime queue object definitions, full policy object model, contract family definitions, downstream registry authority terms |
| GL-CONT-003-DOC-010 | Enables | GL-CONT-004, GL-CONT-005, GL-CONT-006, GL-CONT-007, GL-CONT-008, GL-CONT-009 |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for internal actors and delegated entities inside the Assembler System.

It answers the question:

```text
Which internal assembler-side entities carry responsibilities,
which entities support responsibility execution,
which entities are primary responsibility owners,
and which named things must not be treated as actors?
````

The pack is designed to prevent vague subsystem-level assignment.

The Assembler Subsystem remains accountable, but responsibilities must be delegated to the narrowest mature architectural carrier.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`.

It precedes:

1. `GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack`,
2. `GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack`,
3. `GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack`,
4. `GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack`,
5. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`.

### 2.3 Pack-Level Actor Rule

```text id="gl-cont-003-actor-rule"
An internal actor is a responsibility-carrying assembler-side entity.
A port is an interaction surface.
A carrier object carries prepared content or governed state.
A supporting entity contributes to a responsibility without automatically becoming the primary owner.
```

---

## 3. Term Inventory

|           Record ID | Term ID    | Canonical Term                       | Family    | Category                                                               | Ownership Scope | Entry Maturity    |
| ------------------: | ---------- | ------------------------------------ | --------- | ---------------------------------------------------------------------- | --------------- | ----------------- |
| GL-CONT-003-INV-001 | GL-ENT-001 | Envelope Assembler                   | ENT       | internal_entity / supporting_entity / assembly_component               | assembler_owned | canonical_full    |
| GL-CONT-003-INV-002 | GL-ENT-002 | Dispatcher                           | ENT       | actor / delegated_entity                                               | assembler_owned | canonical_full    |
| GL-CONT-003-INV-003 | GL-ENT-003 | Validator                            | ENT       | supporting_entity / policy_consuming_component                         | assembler_owned | canonical_full    |
| GL-CONT-003-INV-004 | GL-ENT-004 | Metadata Injector                    | ENT       | supporting_entity / preparation_component                              | assembler_owned | canonical_full    |
| GL-CONT-003-INV-005 | GL-ENT-005 | Timestamp Stabilizer                 | ENT       | supporting_entity / preparation_component / policy_consuming_component | assembler_owned | canonical_full    |
| GL-CONT-003-INV-006 | GL-ENT-006 | PolicyAssigner                       | ENT / POL | delegated_entity / policy_assignment_component                         | assembler_owned | canonical_full    |
| GL-CONT-003-INV-007 | GL-ENT-007 | Queue Bundle Agent                   | ENT / RUN | actor / delegated_entity / runtime_coordinator                         | assembler_owned | canonical_full    |
| GL-CONT-003-INV-008 | GL-ENT-008 | Single Queue Moderator               | ENT / RUN | actor / delegated_entity / runtime_coordinator                         | assembler_owned | canonical_full    |
| GL-CONT-003-INV-009 | GL-ENT-009 | Writing / Feeding Round Manager      | ENT / RUN | actor / delegated_entity / round_manager                               | assembler_owned | canonical_full    |
| GL-CONT-003-INV-010 | GL-ENT-010 | Dispatching / Delivery Round Manager | ENT / RUN | actor / delegated_entity / round_manager                               | assembler_owned | canonical_full    |
| GL-CONT-003-INV-011 | GL-TRC-001 | Delegated Entity                     | TRC / ENT | delegated_entity                                                       | governed        | canonical_full    |
| GL-CONT-003-INV-012 | GL-TRC-002 | Supporting Entity                    | TRC / ENT | supporting_entity                                                      | governed        | canonical_full    |
| GL-CONT-003-INV-013 | GL-TRC-003 | Primary Responsibility Owner         | TRC / ENT | responsibility_owner                                                   | governed        | canonical_full    |
| GL-CONT-003-INV-014 | GL-ENT-011 | Policy-Consuming Component           | ENT / POL | policy_consuming_component                                             | assembler_owned | canonical_partial |
| GL-CONT-003-INV-015 | GL-ENT-012 | Runtime Coordination Actor           | ENT / RUN | actor / runtime_coordinator                                            | assembler_owned | canonical_partial |

---

## 4. Canonical Term Entries

---

### GL-ENT-001 — Envelope Assembler

| Field           | Value                                                    |
| --------------- | -------------------------------------------------------- |
| Term ID         | GL-ENT-001                                               |
| Canonical Term  | Envelope Assembler                                       |
| Family          | ENT                                                      |
| Category        | internal_entity / supporting_entity / assembly_component |
| Ownership Scope | assembler_owned                                          |
| Entry Maturity  | canonical_full                                           |
| Evidence Status | direct                                                   |

#### Definition

The Envelope Assembler is the assembler-side assembly component associated with the consuming entry path that produces the `Log Level Envelope`.

It composes or coordinates required preparation participants such as `Validator`, `Metadata Injector`, and `Timestamp Stabilizer` where required by the ingress contract.

#### Architectural Role

The Envelope Assembler is responsible for envelope realization.

It is positioned inside or injected through the consuming-side `Level API` path and produces the `Log Level Envelope` before the `Assembler Ingress Port` receives the envelope.

The corrected ingress rule is:

```text id="gl-ent-001-ingress-rule"
Level API
  contains / injects
    Envelope Assembler
      composes Validator, Metadata Injector, Timestamp Stabilizer
      produces Log Level Envelope

Assembler Ingress Port
  receives Log Level Envelope
```

#### Must Not Be Confused With

1. Log Level Envelope.
2. Assembler Ingress Port.
3. Level API.
4. Dispatcher.
5. Queue Container.
6. PolicyAssigner.
7. Raw payload intake.
8. Downstream registry record.

#### Valid Usage

* “Envelope Assembler produces the Log Level Envelope.”
* “Envelope Assembler may compose Validator, Metadata Injector, and Timestamp Stabilizer.”
* “Envelope Assembler is not the Assembler Ingress Port.”

#### Invalid Usage

* “Envelope Assembler is the Log Level Envelope.”
* “Envelope Assembler admits envelopes into Queue Container slots.”
* “Envelope Assembler dispatches envelopes to downstream registry.”
* “Envelope Assembler is a downstream lifecycle owner.”

#### Related Terms

* GL-EXT-001 — Level API
* GL-BND-006 — Assembler Ingress Port
* GL-ENT-003 — Validator
* GL-ENT-004 — Metadata Injector
* GL-ENT-005 — Timestamp Stabilizer
* GL-OBJ-001 — Log Level Envelope

#### Source Trace

| Source Type        | Source                                                                                                     |
| ------------------ | ---------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Envelope Assembler as composed inside or injected into Level API and producing Log Level Envelope. |
| VisionAndScope.md  | Corrected ingress scope assigns envelope production to Envelope Assembler.                                 |
| SYSTEM_GOALS.md    | SG-ING-002 requires Envelope Assembler to produce Log Level Envelope.                                      |

---

### GL-ENT-002 — Dispatcher

| Field           | Value                    |
| --------------- | ------------------------ |
| Term ID         | GL-ENT-002               |
| Canonical Term  | Dispatcher               |
| Family          | ENT                      |
| Category        | actor / delegated_entity |
| Ownership Scope | assembler_owned          |
| Entry Maturity  | canonical_full           |
| Evidence Status | direct                   |

#### Definition

The Dispatcher is the final assembler-side outbound actor responsible for mediating valid handoff toward downstream preservation or query destinations through the `Registry / Delivery Port`.

#### Architectural Role

The Dispatcher is the last assembler-side actor before authority closure.

It verifies or relies on handoff eligibility and performs dispatcher-mediated handoff.

After valid handoff, assembler authority closes and downstream lifecycle ownership does not return to the Assembler.

#### Must Not Be Confused With

1. Registry / Delivery Port.
2. Log Level Records Registry.
3. Downstream registry implementation.
4. Queue Bundle Agent.
5. Dispatching / Delivery Round Manager.
6. Log Level Envelope.
7. Handoff Evidence.
8. Downstream query subsystem.

#### Valid Usage

* “Dispatcher is the final assembler-side outbound actor.”
* “Dispatcher must not be bypassed.”
* “Dispatcher uses the Registry / Delivery Port as an outbound contract surface.”

#### Invalid Usage

* “Registry / Delivery Port replaces Dispatcher.”
* “Dispatcher owns downstream registry internals.”
* “Dispatcher is the downstream query subsystem.”
* “Log Level Envelope dispatches itself without Dispatcher.”

#### Related Terms

* GL-BND-008 — Registry / Delivery Port
* GL-BND-004 — Authority Boundary
* GL-BND-005 — Downstream Boundary
* GL-EXC-001 — Post-Handoff Non-Ownership
* GL-ENT-010 — Dispatching / Delivery Round Manager

#### Source Trace

| Source Type        | Source                                                                      |
| ------------------ | --------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Dispatcher as final assembler-side handoff actor.                   |
| SYSTEM_GOALS.md    | SG-DISP-001 states Dispatcher SHALL be final assembler-side outbound actor. |
| GL-CONT-002        | Registry / Delivery Port is a port, not the final actor.                    |

---

### GL-ENT-003 — Validator

| Field           | Value                                          |
| --------------- | ---------------------------------------------- |
| Term ID         | GL-ENT-003                                     |
| Canonical Term  | Validator                                      |
| Family          | ENT                                            |
| Category        | supporting_entity / policy_consuming_component |
| Ownership Scope | assembler_owned                                |
| Entry Maturity  | canonical_full                                 |
| Evidence Status | direct                                         |

#### Definition

The Validator is an assembler-side supporting entity that participates in validating ingress paths, contract expectations, or preparation eligibility where validation is required by the relevant contract family.

#### Architectural Role

The Validator supports envelope preparation and ingress discipline.

It may participate in the Envelope Assembler composition path.

It is also eligible as a policy-consuming component where validation behavior is policy-governed.

The Validator does not own the entire ingress path by itself.

#### Must Not Be Confused With

1. Envelope Assembler.
2. Assembler Ingress Port.
3. Log Level Envelope.
4. Policy Object.
5. PolicyAssigner.
6. Dispatcher.
7. Hot-path bypass rule.
8. Downstream validator.

#### Valid Usage

* “Validator participates in validation paths.”
* “Validator may be composed by Envelope Assembler where the contract requires validation.”
* “Validator can be a policy-consuming component.”

#### Invalid Usage

* “Validator produces the Log Level Envelope by itself.”
* “Validator is the Assembler Ingress Port.”
* “Validator owns downstream registry admission.”
* “Validator is always required in every hot path if validation has been externalized.”

#### Related Terms

* GL-ENT-001 — Envelope Assembler
* GL-ENT-006 — PolicyAssigner
* GL-ENT-011 — Policy-Consuming Component
* GL-CON-* — Ingress Contract Family
* GL-OBJ-* — Policy Object

#### Source Trace

| Source Type        | Source                                                                                         |
| ------------------ | ---------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Validator as participating in validating ingress paths and notes hot-path distinction. |
| SYSTEM_GOALS.md    | Policy-consuming component table includes Validator as eligible policy-consuming component.    |
| SYSTEM_GOALS.md    | SG-ING-003 includes Validator in Envelope Assembler composition where required.                |

---

### GL-ENT-004 — Metadata Injector

| Field           | Value                                     |
| --------------- | ----------------------------------------- |
| Term ID         | GL-ENT-004                                |
| Canonical Term  | Metadata Injector                         |
| Family          | ENT                                       |
| Category        | supporting_entity / preparation_component |
| Ownership Scope | assembler_owned                           |
| Entry Maturity  | canonical_full                            |
| Evidence Status | direct                                    |

#### Definition

The Metadata Injector is an assembler-side preparation component that applies schema-guided or directive-driven metadata preparation to accepted content or envelope preparation paths.

#### Architectural Role

The Metadata Injector supports metadata preparation.

It may be composed by the Envelope Assembler where metadata preparation is required.

It is schema/directive-governed.

It is explicitly not a policy host.

#### Must Not Be Confused With

1. Metadata Directive Source.
2. PolicyAssigner.
3. Policy Object.
4. Policy host.
5. Policy-consuming component by default.
6. Envelope Assembler.
7. Log Level Envelope.
8. Downstream registry metadata lifecycle.

#### Valid Usage

* “Metadata Injector applies metadata directives.”
* “Metadata Injector is schema/directive-governed.”
* “Metadata Injector is not policy-hosted.”

#### Invalid Usage

* “Metadata Injector is a policy host.”
* “Metadata Injector is the Metadata Directive Source.”
* “Metadata Injector owns policy assignment.”
* “Metadata Injector owns downstream registry metadata lifecycle.”

#### Related Terms

* GL-EXT-004 — Metadata Directive Source
* GL-ENT-001 — Envelope Assembler
* GL-ENT-006 — PolicyAssigner
* GL-ENT-011 — Policy-Consuming Component
* GL-POL-* — Policy Object
* GL-POL-* — Schema / Directive Governed

#### Source Trace

| Source Type        | Source                                                                                      |
| ------------------ | ------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Metadata Injector as applying metadata directives and not being a policy host.      |
| SYSTEM_GOALS.md    | SG-META-002 states Metadata Injector SHALL be schema/directive-governed, not policy-hosted. |
| SYSTEM_GOALS.md    | SG-POL-COMP-008 explicitly excludes Metadata Injector from policy-hosting semantics.        |

---

### GL-ENT-005 — Timestamp Stabilizer

| Field           | Value                                                                  |
| --------------- | ---------------------------------------------------------------------- |
| Term ID         | GL-ENT-005                                                             |
| Canonical Term  | Timestamp Stabilizer                                                   |
| Family          | ENT                                                                    |
| Category        | supporting_entity / preparation_component / policy_consuming_component |
| Ownership Scope | assembler_owned                                                        |
| Entry Maturity  | canonical_full                                                         |
| Evidence Status | direct                                                                 |

#### Definition

The Timestamp Stabilizer is an assembler-side preparation component that stabilizes timestamp semantics before dispatch eligibility.

#### Architectural Role

The Timestamp Stabilizer participates in accepted ingress and preparation paths.

It may be composed by the Envelope Assembler where timestamp stabilization is required.

It is eligible as a policy-consuming component when timestamp behavior is governed by policy.

It remains assembler-side preparation, not downstream query interpretation.

#### Must Not Be Confused With

1. Metadata Injector.
2. Metadata Directive Source.
3. Downstream query timestamp interpretation.
4. Dispatcher.
5. Log Level Envelope.
6. Policy Object.
7. Storage timestamp lifecycle.

#### Valid Usage

* “Timestamp Stabilizer stabilizes timestamp semantics before dispatch eligibility.”
* “Timestamp Stabilizer may participate in Envelope Assembler composition.”
* “Timestamp stabilization is part of assembler-side preparation.”

#### Invalid Usage

* “Timestamp Stabilizer executes downstream queries.”
* “Timestamp Stabilizer owns storage lifecycle timestamps.”
* “Timestamp Stabilizer is the Metadata Injector.”
* “Timestamp Stabilizer is a raw payload source.”

#### Related Terms

* GL-ENT-001 — Envelope Assembler
* GL-ENT-003 — Validator
* GL-ENT-004 — Metadata Injector
* GL-ENT-011 — Policy-Consuming Component
* GL-POL-* — Timestamp Semantics
* GL-POL-* — Timestamp Stabilization

#### Source Trace

| Source Type        | Source                                                                                     |
| ------------------ | ------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines Timestamp Stabilizer as stabilizing timestamp semantics in accepted ingress paths. |
| SYSTEM_GOALS.md    | SG-TIME-001 requires timestamp semantics to be stabilized before dispatch eligibility.     |
| SYSTEM_GOALS.md    | Policy-consuming component table includes Timestamp Stabilizer as eligible.                |

---

### GL-ENT-006 — PolicyAssigner

| Field           | Value                                          |
| --------------- | ---------------------------------------------- |
| Term ID         | GL-ENT-006                                     |
| Canonical Term  | PolicyAssigner                                 |
| Family          | ENT / POL                                      |
| Category        | delegated_entity / policy_assignment_component |
| Ownership Scope | assembler_owned                                |
| Entry Maturity  | canonical_full                                 |
| Evidence Status | direct                                         |

#### Definition

The PolicyAssigner is the assembler-side delegated entity responsible for mediating policy assignment semantics between Policy Objects and eligible policy-consuming components.

#### Architectural Role

PolicyAssigner preserves the distinction between:

1. policy object,
2. policy assignment,
3. policy-consuming component,
4. policy-hosted mechanism,
5. policy-governed behavior.

It does not become the policy source.

It does not execute every policy-governed mechanism by itself.

#### Must Not Be Confused With

1. Policy Registry / Policy Source.
2. Policy Object.
3. Policy-consuming component.
4. Metadata Injector.
5. Validator.
6. Dispatcher.
7. Administrative / Ecosystem Port.

#### Valid Usage

* “PolicyAssigner mediates policy assignment.”
* “PolicyAssigner assigns Policy Objects to eligible policy-consuming components.”
* “PolicyAssigner is not the Policy Registry / Policy Source.”

#### Invalid Usage

* “PolicyAssigner is the policy source.”
* “PolicyAssigner is the policy object.”
* “PolicyAssigner executes every policy-governed mechanism.”
* “PolicyAssigner makes Metadata Injector a policy host.”

#### Related Terms

* GL-EXT-003 — Policy Registry / Policy Source
* GL-ENT-011 — Policy-Consuming Component
* GL-ENT-003 — Validator
* GL-ENT-005 — Timestamp Stabilizer
* GL-ENT-002 — Dispatcher
* GL-POL-* — Policy Object
* GL-POL-* — Policy Assignment

#### Source Trace

| Source Type        | Source                                                                                           |
| ------------------ | ------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines PolicyAssigner as mediating assignment of Policy Objects to policy-consuming components. |
| SYSTEM_GOALS.md    | SG-POL-002 requires PolicyAssigner to mediate policy assignment semantics.                       |
| GL-CONT-002        | Policy Registry / Policy Source remains external and must not collapse into PolicyAssigner.      |

---

### GL-ENT-007 — Queue Bundle Agent

| Field           | Value                                          |
| --------------- | ---------------------------------------------- |
| Term ID         | GL-ENT-007                                     |
| Canonical Term  | Queue Bundle Agent                             |
| Family          | ENT / RUN                                      |
| Category        | actor / delegated_entity / runtime_coordinator |
| Ownership Scope | assembler_owned                                |
| Entry Maturity  | canonical_full                                 |
| Evidence Status | direct                                         |

#### Definition

The Queue Bundle Agent is an assembler-side runtime coordination actor responsible for queue-bundle-level coordination and waiting-list discipline.

#### Architectural Role

The Queue Bundle Agent works at bundle level, not single-queue level.

It coordinates queue bundles and preserves separation between bundle-level runtime coordination and single queue moderation.

It may be an eligible policy-consuming component where runtime behavior is policy-governed.

#### Must Not Be Confused With

1. Single Queue Moderator.
2. Queue Container.
3. Queue Bundle as object or grouping.
4. Message broker.
5. Scaling / Operational Directive Source.
6. Writing / Feeding Round Manager.
7. Dispatching / Delivery Round Manager.
8. Downstream registry.

#### Valid Usage

* “Queue Bundle Agent coordinates queue bundles.”
* “Queue Bundle Agent is distinct from Single Queue Moderator.”
* “Queue Bundle Agent may consume policy-governed runtime behavior.”

#### Invalid Usage

* “Queue Bundle Agent is a message broker.”
* “Queue Bundle Agent is a Queue Container.”
* “Queue Bundle Agent owns downstream record lifecycle.”
* “Queue Bundle Agent is the Scaling / Operational Directive Source.”

#### Related Terms

* GL-ENT-008 — Single Queue Moderator
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-EXT-005 — Scaling / Operational Directive Source
* GL-RUN-* — Queue Bundle
* GL-RUN-* — Queue Container

#### Source Trace

| Source Type        | Source                                                                                                   |
| ------------------ | -------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Queue Bundle Agent as orchestrating queue bundles and waiting-list discipline.                   |
| SYSTEM_GOALS.md    | SG-QUEUE-006 requires Queue Bundle Agent and Single Queue Moderator responsibilities to remain distinct. |
| SYSTEM_GOALS.md    | Policy-consuming component table includes Queue Bundle Agent as eligible.                                |

---

### GL-ENT-008 — Single Queue Moderator

| Field           | Value                                          |
| --------------- | ---------------------------------------------- |
| Term ID         | GL-ENT-008                                     |
| Canonical Term  | Single Queue Moderator                         |
| Family          | ENT / RUN                                      |
| Category        | actor / delegated_entity / runtime_coordinator |
| Ownership Scope | assembler_owned                                |
| Entry Maturity  | canonical_full                                 |
| Evidence Status | direct                                         |

#### Definition

The Single Queue Moderator is an assembler-side runtime coordination actor responsible for moderating a single Queue Container.

#### Architectural Role

The Single Queue Moderator preserves queue-container discipline, occupancy distinction, and lifecycle boundaries at the single-queue level.

It must not confuse slot occupancy with envelope lifecycle ownership.

It may be an eligible policy-consuming component where moderation behavior is policy-governed.

#### Must Not Be Confused With

1. Queue Bundle Agent.
2. Queue Container.
3. Slot.
4. Envelope Slot Occupancy.
5. Message broker.
6. Dispatcher.
7. Queue Container Identifier.
8. Downstream lifecycle manager.

#### Valid Usage

* “Single Queue Moderator moderates one Queue Container.”
* “Single Queue Moderator is distinct from Queue Bundle Agent.”
* “Single Queue Moderator must preserve slot occupancy boundaries.”

#### Invalid Usage

* “Single Queue Moderator is the Queue Container.”
* “Single Queue Moderator owns envelope lifecycle.”
* “Single Queue Moderator is a message broker.”
* “Single Queue Moderator performs downstream handoff.”

#### Related Terms

* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-RUN-* — Queue Container
* GL-RUN-* — Slot
* GL-RUN-* — Envelope Slot Occupancy

#### Source Trace

| Source Type        | Source                                                                                                            |
| ------------------ | ----------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Single Queue Moderator as moderating one queue-container and preserving occupancy/lifecycle distinctions. |
| SYSTEM_GOALS.md    | SG-QUEUE-006 requires distinct responsibilities for Queue Bundle Agent and Single Queue Moderator.                |
| SYSTEM_GOALS.md    | SG-QUEUE-004 states slot occupancy remains distinct from envelope lifecycle ownership.                            |

---

### GL-ENT-009 — Writing / Feeding Round Manager

| Field           | Value                                    |
| --------------- | ---------------------------------------- |
| Term ID         | GL-ENT-009                               |
| Canonical Term  | Writing / Feeding Round Manager          |
| Family          | ENT / RUN                                |
| Category        | actor / delegated_entity / round_manager |
| Ownership Scope | assembler_owned                          |
| Entry Maturity  | canonical_full                           |
| Evidence Status | direct                                   |

#### Definition

The Writing / Feeding Round Manager is an assembler-side round coordination actor responsible for writing/feed-domain round progression.

#### Architectural Role

The Writing / Feeding Round Manager participates in queue-container identifier handling, waiting-list discipline, and feed-domain coordination.

It is distinct from the Dispatching / Delivery Round Manager.

It coordinates write-side or feed-side progression; it does not perform final outbound handoff.

#### Must Not Be Confused With

1. Dispatching / Delivery Round Manager.
2. Dispatcher.
3. Queue Bundle Agent.
4. Single Queue Moderator.
5. Queue Container.
6. Waiting List itself.
7. Downstream delivery actor.

#### Valid Usage

* “Writing / Feeding Round Manager manages writing/feed-domain round progression.”
* “Writing / Feeding Round Manager interacts with queue-container identifiers.”
* “Writing / Feeding Round Manager is distinct from Dispatching / Delivery Round Manager.”

#### Invalid Usage

* “Writing / Feeding Round Manager is the Dispatcher.”
* “Writing / Feeding Round Manager performs final outbound registry handoff.”
* “Writing / Feeding Round Manager owns downstream lifecycle.”
* “Writing / Feeding Round Manager stores envelopes as generic message payloads.”

#### Related Terms

* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-RUN-* — Waiting List
* GL-RUN-* — Queue Container Identifier

#### Source Trace

| Source Type        | Source                                                                                                             |
| ------------------ | ------------------------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines Writing / Feeding Round Manager as managing writing/feed-domain round progression.                         |
| SYSTEM_GOALS.md    | SG-QUEUE-007 requires Writing / Feeding Round Manager and Dispatching / Delivery Round Manager to remain distinct. |
| SYSTEM_GOALS.md    | SG-QUEUE-005 states waiting lists carry queue-container identifiers where applicable.                              |

---

### GL-ENT-010 — Dispatching / Delivery Round Manager

| Field           | Value                                    |
| --------------- | ---------------------------------------- |
| Term ID         | GL-ENT-010                               |
| Canonical Term  | Dispatching / Delivery Round Manager     |
| Family          | ENT / RUN                                |
| Category        | actor / delegated_entity / round_manager |
| Ownership Scope | assembler_owned                          |
| Entry Maturity  | canonical_full                           |
| Evidence Status | direct                                   |

#### Definition

The Dispatching / Delivery Round Manager is an assembler-side round coordination actor responsible for dispatch/delivery-domain round progression before final dispatcher-mediated handoff.

#### Architectural Role

The Dispatching / Delivery Round Manager participates in moving prepared envelopes toward dispatch readiness.

It is not the final outbound actor.

The Dispatcher remains the final assembler-side outbound actor.

#### Must Not Be Confused With

1. Dispatcher.
2. Writing / Feeding Round Manager.
3. Registry / Delivery Port.
4. Log Level Records Registry.
5. Queue Container.
6. Handoff Evidence.
7. Downstream delivery subsystem.

#### Valid Usage

* “Dispatching / Delivery Round Manager manages dispatch/delivery-domain round progression.”
* “Dispatching / Delivery Round Manager prepares or coordinates toward dispatch readiness.”
* “Dispatcher remains the final outbound actor.”

#### Invalid Usage

* “Dispatching / Delivery Round Manager replaces Dispatcher.”
* “Dispatching / Delivery Round Manager owns downstream registry internals.”
* “Dispatching / Delivery Round Manager is the Registry / Delivery Port.”
* “Dispatching / Delivery Round Manager performs read-side query execution.”

#### Related Terms

* GL-ENT-002 — Dispatcher
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-BND-008 — Registry / Delivery Port
* GL-RUN-* — Dispatch Readiness
* GL-EXC-001 — Post-Handoff Non-Ownership

#### Source Trace

| Source Type        | Source                                                                                               |
| ------------------ | ---------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines Dispatching / Delivery Round Manager as managing dispatch/delivery-domain round progression. |
| SYSTEM_GOALS.md    | SG-QUEUE-007 preserves separation from Writing / Feeding Round Manager.                              |
| SYSTEM_GOALS.md    | SG-DISP-001 preserves Dispatcher finality.                                                           |

---

### GL-TRC-001 — Delegated Entity

| Field           | Value            |
| --------------- | ---------------- |
| Term ID         | GL-TRC-001       |
| Canonical Term  | Delegated Entity |
| Family          | TRC / ENT        |
| Category        | delegated_entity |
| Ownership Scope | governed         |
| Entry Maturity  | canonical_full   |
| Evidence Status | derived          |

#### Definition

A Delegated Entity is an architectural carrier selected to carry or perform a responsibility, obligation, or responsibility-supporting behavior inside the Assembler System.

#### Architectural Role

Delegated Entity is a traceability term.

It exists to prevent assigning all behavior vaguely to the Assembler Subsystem.

Delegation must target the narrowest mature architectural carrier.

A delegated entity may be an actor, preparation component, runtime coordinator, assignment component, or port, depending on the responsibility type.

#### Must Not Be Confused With

1. Whole Assembler Subsystem by default.
2. Final C++ class.
3. Implementation package.
4. Capability Candidate.
5. Supporting Entity by default.
6. Governed Object.
7. Carrier Object.

#### Valid Usage

* “Dispatcher is the delegated entity for final assembler-side handoff.”
* “PolicyAssigner is the delegated entity for policy assignment semantics.”
* “Delegation should target the narrowest mature architectural carrier.”

#### Invalid Usage

* “Every delegated entity is automatically a C++ class.”
* “Every delegated entity is an actor.”
* “Delegated entity means downstream registry ownership.”
* “Delegation can ignore source trace.”

#### Related Terms

* GL-TRC-002 — Supporting Entity
* GL-TRC-003 — Primary Responsibility Owner
* GL-ENT-002 — Dispatcher
* GL-ENT-006 — PolicyAssigner
* GL-DER-001 — Architecture-to-Implementation Derivation

#### Source Trace

| Source Type        | Source                                                                                                |
| ------------------ | ----------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Uses rule: Assembler Subsystem = accountable; Component / Port / Contract Object = delegated carrier. |
| SYSTEM_GOALS.md    | SG-TRACE-003 requires delegation to target the narrowest mature architectural carrier.                |
| GL-CONT-000        | Category model includes delegated_entity and source trace requirements.                               |

---

### GL-TRC-002 — Supporting Entity

| Field           | Value             |
| --------------- | ----------------- |
| Term ID         | GL-TRC-002        |
| Canonical Term  | Supporting Entity |
| Family          | TRC / ENT         |
| Category        | supporting_entity |
| Ownership Scope | governed          |
| Entry Maturity  | canonical_full    |
| Evidence Status | derived           |

#### Definition

A Supporting Entity is an assembler-side component that contributes to responsibility execution without necessarily being the primary responsibility owner.

#### Architectural Role

Supporting Entity preserves role precision.

It prevents components such as Validator, Metadata Injector, or Timestamp Stabilizer from being incorrectly treated as owners of the full ingress, envelope, policy, dispatch, or runtime lifecycle.

A supporting entity may participate in a composed path while remaining subordinate to the primary responsibility owner or delegated carrier for that path.

#### Must Not Be Confused With

1. Primary Responsibility Owner.
2. Whole subsystem accountability.
3. Policy source.
4. Carrier object.
5. Port.
6. Final implementation unit.
7. Downstream owner.

#### Valid Usage

* “Validator is a supporting entity in the envelope assembly path.”
* “Metadata Injector supports metadata preparation but is not a policy host.”
* “Timestamp Stabilizer supports timestamp stabilization before dispatch eligibility.”

#### Invalid Usage

* “A supporting entity owns the whole subsystem path.”
* “Metadata Injector owns policy execution.”
* “Validator owns downstream registry lifecycle.”
* “Supporting entity automatically becomes a package.”

#### Related Terms

* GL-TRC-001 — Delegated Entity
* GL-TRC-003 — Primary Responsibility Owner
* GL-ENT-003 — Validator
* GL-ENT-004 — Metadata Injector
* GL-ENT-005 — Timestamp Stabilizer

#### Source Trace

| Source Type        | Source                                                                                           |
| ------------------ | ------------------------------------------------------------------------------------------------ |
| SYSTEM_GOALS.md    | SG-TRACE-004 requires supporting entities not to be confused with primary responsibility owners. |
| ProjectOverview.md | Envelope Assembler composes Validator, Metadata Injector, Timestamp Stabilizer.                  |
| GL-CONT-000        | Category model includes supporting_entity.                                                       |

---

### GL-TRC-003 — Primary Responsibility Owner

| Field           | Value                        |
| --------------- | ---------------------------- |
| Term ID         | GL-TRC-003                   |
| Canonical Term  | Primary Responsibility Owner |
| Family          | TRC / ENT                    |
| Category        | responsibility_owner         |
| Ownership Scope | governed                     |
| Entry Maturity  | canonical_full               |
| Evidence Status | derived                      |

#### Definition

A Primary Responsibility Owner is the architectural entity that owns the central obligation for a responsibility after delegation has been resolved.

#### Architectural Role

Primary Responsibility Owner identifies the entity that should be reviewed when checking whether a responsibility has been satisfied.

It does not erase supporting entities.

It does not mean implementation class ownership.

It means architectural ownership of a responsibility or obligation at the current abstraction level.

#### Must Not Be Confused With

1. Supporting Entity.
2. Whole subsystem accountability.
3. C++ class owner.
4. Package owner.
5. Runtime object.
6. Carrier object.
7. External actor.

#### Valid Usage

* “Dispatcher is the primary responsibility owner for final outbound handoff.”
* “PolicyAssigner is the primary responsibility owner for policy assignment mediation.”
* “Envelope Assembler is the primary responsibility owner for envelope production.”

#### Invalid Usage

* “Every helper in a composed path is the primary responsibility owner.”
* “Primary Responsibility Owner must become a class name.”
* “Primary Responsibility Owner means downstream registry ownership.”
* “The Log Level Envelope is a primary responsibility owner.”

#### Related Terms

* GL-TRC-001 — Delegated Entity
* GL-TRC-002 — Supporting Entity
* GL-ENT-001 — Envelope Assembler
* GL-ENT-002 — Dispatcher
* GL-ENT-006 — PolicyAssigner

#### Source Trace

| Source Type        | Source                                                                                            |
| ------------------ | ------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-TRACE-004 preserves distinction between supporting entities and primary responsibility owners. |
| SYSTEM_GOALS.md    | SG-TRACE-003 requires narrow delegation to mature carriers.                                       |
| ProjectOverview.md | Internal overview distinguishes subsystem accountability from delegated execution.                |

---

### GL-ENT-011 — Policy-Consuming Component

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-ENT-011                 |
| Canonical Term  | Policy-Consuming Component |
| Family          | ENT / POL                  |
| Category        | policy_consuming_component |
| Ownership Scope | assembler_owned            |
| Entry Maturity  | canonical_partial          |
| Evidence Status | direct / derived           |

#### Definition

A Policy-Consuming Component is an assembler-side component eligible to host or realize policy-governed behavior after policy assignment.

#### Architectural Role

Policy-Consuming Component preserves the distinction between policy material and local behavior realization.

Policy Objects govern.

PolicyAssigner mediates assignment.

Policy-consuming components realize behavior under policy governance.

Eligible policy-consuming components may include:

1. Dispatcher,
2. Validator,
3. Timestamp Stabilizer,
4. Queue Bundle Agent,
5. Single Queue Moderator,
6. Writing / Feeding Round Manager,
7. Dispatching / Delivery Round Manager.

Metadata Injector is explicitly excluded from policy-hosting semantics unless a later formal correction changes the rule.

#### Must Not Be Confused With

1. Policy Object.
2. PolicyAssigner.
3. Policy Registry / Policy Source.
4. Metadata Injector.
5. Administrative / Ecosystem Port.
6. External policy source.
7. Downstream policy lifecycle.

#### Valid Usage

* “Dispatcher may be a policy-consuming component.”
* “Policy-consuming component realizes policy-governed behavior locally.”
* “Metadata Injector is excluded from policy-hosting semantics.”

#### Invalid Usage

* “Policy-consuming component is the policy source.”
* “Policy-consuming component is the Policy Object.”
* “Metadata Injector is policy-hosted by default.”
* “Policy-consuming component owns downstream policy lifecycle.”

#### Related Terms

* GL-ENT-006 — PolicyAssigner
* GL-ENT-002 — Dispatcher
* GL-ENT-003 — Validator
* GL-ENT-005 — Timestamp Stabilizer
* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager

#### Source Trace

| Source Type        | Source                                                                                            |
| ------------------ | ------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Defines policy-consuming components and excludes Metadata Injector from policy-hosting semantics. |
| SYSTEM_GOALS.md    | SG-POL-COMP table lists eligible components and explicitly excludes Metadata Injector.            |
| SYSTEM_GOALS.md    | SG-POL-003 requires policy-governed mechanisms to be hosted by eligible components.               |

---

### GL-ENT-012 — Runtime Coordination Actor

| Field           | Value                       |
| --------------- | --------------------------- |
| Term ID         | GL-ENT-012                  |
| Canonical Term  | Runtime Coordination Actor  |
| Family          | ENT / RUN                   |
| Category        | actor / runtime_coordinator |
| Ownership Scope | assembler_owned             |
| Entry Maturity  | canonical_partial           |
| Evidence Status | derived                     |

#### Definition

A Runtime Coordination Actor is an assembler-side actor responsible for coordinating runtime queue, round, waiting-list, or readiness behavior without becoming a message broker, storage engine, or downstream lifecycle owner.

#### Architectural Role

This term groups runtime-responsibility carriers such as:

1. Queue Bundle Agent,
2. Single Queue Moderator,
3. Writing / Feeding Round Manager,
4. Dispatching / Delivery Round Manager.

The term exists as a glossary classification, not as a required final class or package.

#### Must Not Be Confused With

1. Queue Container.
2. Queue Bundle.
3. Slot.
4. Envelope Slot Occupancy.
5. Message broker.
6. Storage engine.
7. Dispatcher by default.
8. Downstream lifecycle owner.

#### Valid Usage

* “Queue Bundle Agent is a runtime coordination actor.”
* “Single Queue Moderator is a runtime coordination actor.”
* “Runtime coordination actors do not turn Queue Containers into message brokers.”

#### Invalid Usage

* “Runtime Coordination Actor is a required base class.”
* “Runtime Coordination Actor owns downstream records.”
* “Runtime Coordination Actor is the queue object itself.”
* “Runtime Coordination Actor stores envelopes as generic message payloads.”

#### Related Terms

* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-RUN-* — Queue Container
* GL-RUN-* — Queue-as-Container Doctrine

#### Source Trace

| Source Type        | Source                                                                                           |
| ------------------ | ------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Runtime model defines queue-container coordination and round managers.                           |
| SYSTEM_GOALS.md    | Queue runtime goals preserve queue-as-container and separation among runtime coordination roles. |
| GL-CONT-000        | Category model permits actor and runtime_state distinctions.                                     |

---

## 5. Internal Entity Classification Matrix

|           Record ID | Term                                 | Internal Entity? |          Actor? | Supporting Entity? |       Primary Responsibility Owner? | Policy-Consuming Eligible? | Notes                               |
| ------------------: | ------------------------------------ | ---------------: | --------------: | -----------------: | ----------------------------------: | -------------------------: | ----------------------------------- |
| GL-CONT-003-ICM-001 | Envelope Assembler                   |              Yes |     Conditional |                Yes |        Yes, for envelope production |    Not primary policy host | Produces Log Level Envelope         |
| GL-CONT-003-ICM-002 | Dispatcher                           |              Yes |             Yes |                 No |           Yes, for outbound handoff |                        Yes | Final assembler-side outbound actor |
| GL-CONT-003-ICM-003 | Validator                            |              Yes |     Conditional |                Yes |                          Usually no |                        Yes | Supports validation paths           |
| GL-CONT-003-ICM-004 | Metadata Injector                    |              Yes | No / supporting |                Yes |                       No for policy |        Explicitly excluded | Schema/directive-governed           |
| GL-CONT-003-ICM-005 | Timestamp Stabilizer                 |              Yes |     Conditional |                Yes |     Yes for timestamp stabilization |                        Yes | Stabilizes timestamp semantics      |
| GL-CONT-003-ICM-006 | PolicyAssigner                       |              Yes |     Conditional |                 No |          Yes, for policy assignment |        Assignment mediator | Mediates policy assignment          |
| GL-CONT-003-ICM-007 | Queue Bundle Agent                   |              Yes |             Yes |                 No |        Yes, for bundle coordination |                        Yes | Bundle-level runtime actor          |
| GL-CONT-003-ICM-008 | Single Queue Moderator               |              Yes |             Yes |                 No |    Yes, for single-queue moderation |                        Yes | Single queue-container actor        |
| GL-CONT-003-ICM-009 | Writing / Feeding Round Manager      |              Yes |             Yes |                 No |     Yes, for feed-round progression |                        Yes | Write/feed round actor              |
| GL-CONT-003-ICM-010 | Dispatching / Delivery Round Manager |              Yes |             Yes |                 No | Yes, for delivery-round progression |                        Yes | Pre-dispatch/delivery round actor   |
| GL-CONT-003-ICM-011 | Delegated Entity                     |   Classification |     Conditional |        Conditional |                         Conditional |                Conditional | Governance classification           |
| GL-CONT-003-ICM-012 | Supporting Entity                    |   Classification |     Conditional |                Yes |                       No by default |                Conditional | Role classification                 |
| GL-CONT-003-ICM-013 | Primary Responsibility Owner         |   Classification |     Conditional |      No by default |                                 Yes |                Conditional | Responsibility review target        |
| GL-CONT-003-ICM-014 | Policy-Consuming Component           |   Classification |     Conditional |        Conditional |                         Conditional |                        Yes | Excludes Metadata Injector          |
| GL-CONT-003-ICM-015 | Runtime Coordination Actor           |   Classification |             Yes |      No by default |                         Conditional |                Conditional | Not a required implementation base  |

---

## 6. Responsibility Ownership Matrix

|           Record ID | Responsibility Area                 | Primary Responsibility Owner         | Supporting Entities                                            | Must Not Collapse Into                               |
| ------------------: | ----------------------------------- | ------------------------------------ | -------------------------------------------------------------- | ---------------------------------------------------- |
| GL-CONT-003-ROM-001 | Envelope production                 | Envelope Assembler                   | Validator, Metadata Injector, Timestamp Stabilizer             | Log Level Envelope, Assembler Ingress Port           |
| GL-CONT-003-ROM-002 | Envelope admission into queue slot  | Assembler Ingress Port               | Queue runtime components                                       | Envelope Assembler, Level API                        |
| GL-CONT-003-ROM-003 | Validation participation            | Validator                            | Envelope Assembler                                             | Policy Object, Ingress Port                          |
| GL-CONT-003-ROM-004 | Metadata preparation                | Metadata Injector                    | Envelope Assembler                                             | Policy host, Metadata Directive Source               |
| GL-CONT-003-ROM-005 | Timestamp stabilization             | Timestamp Stabilizer                 | Envelope Assembler                                             | Downstream query interpretation                      |
| GL-CONT-003-ROM-006 | Policy assignment mediation         | PolicyAssigner                       | Policy-consuming components                                    | Policy Source, Policy Object                         |
| GL-CONT-003-ROM-007 | Queue-bundle coordination           | Queue Bundle Agent                   | Round Managers                                                 | Single Queue Moderator, Message Broker               |
| GL-CONT-003-ROM-008 | Single queue moderation             | Single Queue Moderator               | Queue Bundle Agent                                             | Queue Container, Envelope lifecycle owner            |
| GL-CONT-003-ROM-009 | Writing/feed round progression      | Writing / Feeding Round Manager      | Queue Bundle Agent, Single Queue Moderator                     | Dispatching / Delivery Round Manager                 |
| GL-CONT-003-ROM-010 | Dispatch/delivery round progression | Dispatching / Delivery Round Manager | Queue Bundle Agent, Single Queue Moderator                     | Dispatcher                                           |
| GL-CONT-003-ROM-011 | Final outbound handoff              | Dispatcher                           | Dispatching / Delivery Round Manager, Registry / Delivery Port | Registry / Delivery Port, Log Level Records Registry |

---

## 7. Pack-Level Anti-Collapse Index

|          Record ID | Term                                 | Must Not Collapse Into               | Guard Meaning                                                     |
| -----------------: | ------------------------------------ | ------------------------------------ | ----------------------------------------------------------------- |
| GL-CONT-003-AC-001 | Envelope Assembler                   | Log Level Envelope                   | Producer is not carrier                                           |
| GL-CONT-003-AC-002 | Envelope Assembler                   | Assembler Ingress Port               | Producer is not receiving port                                    |
| GL-CONT-003-AC-003 | Dispatcher                           | Registry / Delivery Port             | Actor is not port                                                 |
| GL-CONT-003-AC-004 | Dispatcher                           | Log Level Records Registry           | Actor is not downstream registry                                  |
| GL-CONT-003-AC-005 | Validator                            | Envelope Assembler                   | Supporting validation is not full assembly ownership              |
| GL-CONT-003-AC-006 | Metadata Injector                    | Policy Host                          | Metadata injector is schema/directive-governed, not policy-hosted |
| GL-CONT-003-AC-007 | Metadata Injector                    | Metadata Directive Source            | Applier is not external source                                    |
| GL-CONT-003-AC-008 | Timestamp Stabilizer                 | Downstream Query Interpretation      | Stabilization is assembler-side preparation                       |
| GL-CONT-003-AC-009 | PolicyAssigner                       | Policy Object                        | Assigner is not policy material                                   |
| GL-CONT-003-AC-010 | PolicyAssigner                       | Policy Registry / Policy Source      | Assignment mediator is not external source                        |
| GL-CONT-003-AC-011 | Queue Bundle Agent                   | Single Queue Moderator               | Bundle-level actor is not single-queue actor                      |
| GL-CONT-003-AC-012 | Queue Bundle Agent                   | Message Broker                       | Queue coordination is not broker behavior                         |
| GL-CONT-003-AC-013 | Single Queue Moderator               | Queue Container                      | Moderator is not the queue object                                 |
| GL-CONT-003-AC-014 | Single Queue Moderator               | Envelope Lifecycle Owner             | Slot moderation is not lifecycle ownership                        |
| GL-CONT-003-AC-015 | Writing / Feeding Round Manager      | Dispatching / Delivery Round Manager | Feed round is distinct from delivery round                        |
| GL-CONT-003-AC-016 | Dispatching / Delivery Round Manager | Dispatcher                           | Delivery round coordination is not final handoff actor            |
| GL-CONT-003-AC-017 | Delegated Entity                     | Final C++ Class                      | Delegation is architectural, not immediate implementation         |
| GL-CONT-003-AC-018 | Supporting Entity                    | Primary Responsibility Owner         | Supporting role does not imply primary ownership                  |
| GL-CONT-003-AC-019 | Policy-Consuming Component           | Policy Object                        | Component realizes behavior; object governs                       |
| GL-CONT-003-AC-020 | Runtime Coordination Actor           | Queue Container                      | Actor coordinates runtime; queue is container                     |

---

## 8. Alias and Usage Notes

|             Record ID | Alias / Variant        | Canonical Term                                     | Status            | Usage Rule                                                |
| --------------------: | ---------------------- | -------------------------------------------------- | ----------------- | --------------------------------------------------------- |
| GL-CONT-003-ALIAS-001 | Envelope Builder       | Envelope Assembler                                 | discouraged_alias | Use Envelope Assembler in formal documentation            |
| GL-CONT-003-ALIAS-002 | Assembler              | Envelope Assembler / Assembler System              | ambiguous         | Avoid unless context is explicit                          |
| GL-CONT-003-ALIAS-003 | Dispatch Manager       | Dispatcher or Dispatching / Delivery Round Manager | ambiguous         | Must specify final actor vs round manager                 |
| GL-CONT-003-ALIAS-004 | Metadata Applier       | Metadata Injector                                  | shorthand         | Use Metadata Injector formally                            |
| GL-CONT-003-ALIAS-005 | Timestamp Normalizer   | Timestamp Stabilizer                               | possible_alias    | Use Timestamp Stabilizer formally                         |
| GL-CONT-003-ALIAS-006 | Policy Assigner        | PolicyAssigner                                     | spacing_variant   | Canonical spelling is PolicyAssigner                      |
| GL-CONT-003-ALIAS-007 | Queue Agent            | Queue Bundle Agent                                 | shorthand         | Use only after canonical term is introduced               |
| GL-CONT-003-ALIAS-008 | Queue Moderator        | Single Queue Moderator                             | shorthand         | Use full term when distinguishing from bundle-level agent |
| GL-CONT-003-ALIAS-009 | Write Round Manager    | Writing / Feeding Round Manager                    | shorthand         | Use canonical full term in formal tables                  |
| GL-CONT-003-ALIAS-010 | Delivery Round Manager | Dispatching / Delivery Round Manager               | shorthand         | Use canonical full term in formal tables                  |

---

## 9. Relationship Map

|           Record ID | Source Term                          | Relationship        | Target Term                  |
| ------------------: | ------------------------------------ | ------------------- | ---------------------------- |
| GL-CONT-003-REL-001 | Level API                            | contains_or_injects | Envelope Assembler           |
| GL-CONT-003-REL-002 | Envelope Assembler                   | composes            | Validator                    |
| GL-CONT-003-REL-003 | Envelope Assembler                   | composes            | Metadata Injector            |
| GL-CONT-003-REL-004 | Envelope Assembler                   | composes            | Timestamp Stabilizer         |
| GL-CONT-003-REL-005 | Envelope Assembler                   | produces            | Log Level Envelope           |
| GL-CONT-003-REL-006 | Assembler Ingress Port               | receives            | Log Level Envelope           |
| GL-CONT-003-REL-007 | PolicyAssigner                       | assigns             | Policy Object                |
| GL-CONT-003-REL-008 | PolicyAssigner                       | targets             | Policy-Consuming Component   |
| GL-CONT-003-REL-009 | Metadata Injector                    | governed_by         | Metadata Directive           |
| GL-CONT-003-REL-010 | Metadata Injector                    | must_not_be         | Policy Host                  |
| GL-CONT-003-REL-011 | Timestamp Stabilizer                 | stabilizes          | Timestamp Semantics          |
| GL-CONT-003-REL-012 | Queue Bundle Agent                   | coordinates         | Queue Bundle                 |
| GL-CONT-003-REL-013 | Single Queue Moderator               | moderates           | Queue Container              |
| GL-CONT-003-REL-014 | Writing / Feeding Round Manager      | manages             | Writing / Feeding Round      |
| GL-CONT-003-REL-015 | Dispatching / Delivery Round Manager | manages             | Dispatching / Delivery Round |
| GL-CONT-003-REL-016 | Dispatching / Delivery Round Manager | enables             | Dispatch Readiness           |
| GL-CONT-003-REL-017 | Dispatcher                           | performs            | Dispatcher-Mediated Handoff  |
| GL-CONT-003-REL-018 | Dispatcher                           | uses                | Registry / Delivery Port     |
| GL-CONT-003-REL-019 | Registry / Delivery Port             | must_not_replace    | Dispatcher                   |
| GL-CONT-003-REL-020 | Delegated Entity                     | carries             | Responsibility               |
| GL-CONT-003-REL-021 | Supporting Entity                    | supports            | Responsibility               |
| GL-CONT-003-REL-022 | Primary Responsibility Owner         | owns                | Responsibility Obligation    |
| GL-CONT-003-REL-023 | Runtime Coordination Actor           | coordinates         | Runtime State                |
| GL-CONT-003-REL-024 | Policy-Consuming Component           | realizes            | Policy-Governed Mechanism    |

---

## 10. Internal Actor Flow Reference

### 10.1 Preparation Actor Path

```text id="gl-cont-003-preparation-actor-path"
Level API
  contains / injects
    Envelope Assembler
      composes:
        Validator
        Metadata Injector
        Timestamp Stabilizer
      produces:
        Log Level Envelope
```

### 10.2 Policy Assignment Path

```text id="gl-cont-003-policy-path"
Policy Registry / Policy Source
  supplies:
    Policy Object

PolicyAssigner
  mediates:
    Policy Assignment

Eligible Policy-Consuming Components
  realize:
    Policy-Governed Mechanisms
```

### 10.3 Runtime Coordination Actor Path

```text id="gl-cont-003-runtime-path"
Queue Bundle Agent
  coordinates queue-bundle discipline

Single Queue Moderator
  moderates single Queue Container discipline

Writing / Feeding Round Manager
  manages writing/feed-domain round progression

Dispatching / Delivery Round Manager
  manages dispatch/delivery-domain round progression

Dispatcher
  performs final assembler-side outbound handoff
```

---

## 11. Source Trace Summary

|           Record ID | Source Area        | Supported Terms                                                                                     |
| ------------------: | ------------------ | --------------------------------------------------------------------------------------------------- |
| GL-CONT-003-SRC-001 | README.md          | Dispatcher, Log Level Envelope centrality, queue-as-container, C++ derivation posture               |
| GL-CONT-003-SRC-002 | ProjectOverview.md | Internal actors, delegated entities, corrected ingress, policy-consuming components, runtime actors |
| GL-CONT-003-SRC-003 | VisionAndScope.md  | Ownership scope, corrected ingress scope, future derivation rules, authority closure                |
| GL-CONT-003-SRC-004 | SYSTEM_GOALS.md    | Traceability goals, policy goals, queue runtime goals, dispatcher goals                             |
| GL-CONT-003-SRC-005 | GL-CONT-000        | Entry schema, category model, maturity model, anti-collapse model                                   |
| GL-CONT-003-SRC-006 | GL-CONT-002        | Boundary surfaces, external context, port/actor separation, downstream non-ownership                |

---

## 12. Validation Checklist

|           Record ID | Check                                                                                    | Expected Result |
| ------------------: | ---------------------------------------------------------------------------------------- | --------------- |
| GL-CONT-003-VAL-001 | Every internal actor term has a Term ID                                                  | Pass            |
| GL-CONT-003-VAL-002 | Every term has family and category                                                       | Pass            |
| GL-CONT-003-VAL-003 | Every term declares ownership scope                                                      | Pass            |
| GL-CONT-003-VAL-004 | Envelope Assembler is not confused with Log Level Envelope                               | Pass            |
| GL-CONT-003-VAL-005 | Envelope Assembler is not confused with Assembler Ingress Port                           | Pass            |
| GL-CONT-003-VAL-006 | Dispatcher remains final assembler-side outbound actor                                   | Pass            |
| GL-CONT-003-VAL-007 | Registry / Delivery Port does not replace Dispatcher                                     | Pass            |
| GL-CONT-003-VAL-008 | Metadata Injector is not policy-hosted                                                   | Pass            |
| GL-CONT-003-VAL-009 | PolicyAssigner is not Policy Object or Policy Source                                     | Pass            |
| GL-CONT-003-VAL-010 | Queue Bundle Agent and Single Queue Moderator remain distinct                            | Pass            |
| GL-CONT-003-VAL-011 | Writing / Feeding Round Manager and Dispatching / Delivery Round Manager remain distinct | Pass            |
| GL-CONT-003-VAL-012 | Supporting Entity and Primary Responsibility Owner remain distinct                       | Pass            |
| GL-CONT-003-VAL-013 | Delegated Entity is not treated as final implementation artifact                         | Pass            |
| GL-CONT-003-VAL-014 | Runtime Coordination Actor is not treated as Queue Container                             | Pass            |
| GL-CONT-003-VAL-015 | Policy-consuming eligibility excludes Metadata Injector                                  | Pass            |

---

## 13. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                                                         | Status   |
| -------------------: | -------------------------------------------------------------------------------------- | -------- |
| GL-CONT-003-EXIT-001 | Core internal actors are defined                                                       | Complete |
| GL-CONT-003-EXIT-002 | Delegated entity vocabulary is defined                                                 | Complete |
| GL-CONT-003-EXIT-003 | Supporting entity vocabulary is defined                                                | Complete |
| GL-CONT-003-EXIT-004 | Primary responsibility owner vocabulary is defined                                     | Complete |
| GL-CONT-003-EXIT-005 | Envelope Assembler is distinguished from Log Level Envelope and Assembler Ingress Port | Complete |
| GL-CONT-003-EXIT-006 | Dispatcher is distinguished from Registry / Delivery Port                              | Complete |
| GL-CONT-003-EXIT-007 | Metadata Injector is excluded from policy-hosting semantics                            | Complete |
| GL-CONT-003-EXIT-008 | Runtime coordination actors are classified without becoming queue objects              | Complete |
| GL-CONT-003-EXIT-009 | Relationship map supports later responsibility and runtime packs                       | Complete |
| GL-CONT-003-EXIT-010 | Pack is ready to support GL-CONT-004 and GL-CONT-005                                   | Complete |

---

## 14. Summary

`GL-CONT-003 — Internal Actors and Delegated Entities Pack` establishes the canonical vocabulary for internal responsibility carriers in the Assembler System.

The pack stabilizes the following internal actor model:

```text id="gl-cont-003-summary-model"
Envelope Assembler
= produces Log Level Envelope

Validator
= supports validation paths

Metadata Injector
= applies metadata directives; not policy-hosted

Timestamp Stabilizer
= stabilizes timestamp semantics before dispatch eligibility

PolicyAssigner
= mediates policy assignment semantics

Queue Bundle Agent
= coordinates queue-bundle runtime discipline

Single Queue Moderator
= moderates one Queue Container

Writing / Feeding Round Manager
= manages writing/feed-domain round progression

Dispatching / Delivery Round Manager
= manages dispatch/delivery-domain round progression

Dispatcher
= final assembler-side outbound actor

Delegated Entity
= narrow mature architectural responsibility carrier

Supporting Entity
= contributes without automatically owning the primary responsibility

Primary Responsibility Owner
= review target for a delegated responsibility
```

This pack enables the next glossary content pack:

```text id="gl-cont-003-next"
GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack
```
