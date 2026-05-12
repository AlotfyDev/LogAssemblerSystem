
# GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-004-DOC-001 | Pack Name | GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack |
| GL-CONT-004-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-004-DOC-003 | Project | Assembler System |
| GL-CONT-004-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-004-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-004-DOC-006 | Language | English |
| GL-CONT-004-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002, GL-CONT-003 |
| GL-CONT-004-DOC-008 | Scope | Governed objects, carrier objects, envelope terminology, policy object terminology, handoff evidence objects, raw-content exclusions |
| GL-CONT-004-DOC-009 | Excluded From This Pack | Runtime queue/slot mechanics, full policy-governance mechanics, contract-family derivation, dispatcher/handoff process details, downstream registry schema |
| GL-CONT-004-DOC-010 | Enables | GL-CONT-005, GL-CONT-006, GL-CONT-008, GL-CONT-009, later object-model derivation, later envelope-carrier contract derivation |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for governed objects, carrier objects, envelope-related terms, and object-like artifacts in the Assembler System.

It answers the question:

```text
Which named things are carried, governed, emitted, assigned, transferred,
evidenced, or excluded as objects rather than treated as internal actors?
````

The pack protects the architecture from collapsing objects into actors, carriers into producers, policy material into policy executors, evidence into lifecycle ownership, or downstream records into assembler-owned objects.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`,
4. `GL-CONT-003 — Internal Actors and Delegated Entities Pack`.

It precedes:

1. `GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack`,
2. `GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack`,
3. `GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack`,
4. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`.

### 2.3 Pack-Level Object Rule

```text id="gl-cont-004-object-rule"
A governed object may be carried, validated, assigned, emitted, transferred,
or evidenced by an actor.
It must not be treated as the actor that performs those responsibilities.
```

### 2.4 Pack-Level Envelope Rule

```text id="gl-cont-004-envelope-rule"
The Log Level Envelope is the authoritative assembler-side runtime transport carrier.
It is not raw content, not the Envelope Assembler, not the Dispatcher,
and not a downstream registry record.
```

---

## 3. Term Inventory

|           Record ID | Term ID      | Canonical Term             | Family          | Category                                | Ownership Scope                        | Entry Maturity    |
| ------------------: | ------------ | -------------------------- | --------------- | --------------------------------------- | -------------------------------------- | ----------------- |
| GL-CONT-004-INV-001 | GL-OBJ-001   | Log Level Envelope         | OBJ             | carrier_object / governed_object        | assembler_owned / transferable         | canonical_full    |
| GL-CONT-004-INV-002 | GL-ALIAS-001 | Log Envelope               | ALIAS / OBJ     | alias                                   | governed                               | alias             |
| GL-CONT-004-INV-003 | GL-OBJ-002   | Governed Object            | OBJ             | governed_object                         | governed                               | canonical_full    |
| GL-CONT-004-INV-004 | GL-OBJ-003   | Carrier Object             | OBJ             | carrier_object                          | governed                               | canonical_full    |
| GL-CONT-004-INV-005 | GL-OBJ-004   | Policy Object              | OBJ / POL       | governed_object / policy_material       | external_supplied / assembler_governed | canonical_full    |
| GL-CONT-004-INV-006 | GL-OBJ-005   | Policy Assignment          | OBJ / POL       | governed_object / assignment_relation   | assembler_owned                        | canonical_full    |
| GL-CONT-004-INV-007 | GL-OBJ-006   | Delivery-Cycle Flag Set    | OBJ             | governed_object / state_artifact        | assembler_owned                        | canonical_partial |
| GL-CONT-004-INV-008 | GL-OBJ-007   | Dispatcher Feedback Report | OBJ             | governed_object / report_artifact       | assembler_owned / emitted              | canonical_partial |
| GL-CONT-004-INV-009 | GL-OBJ-008   | Handoff Evidence           | OBJ / EXC       | evidence_artifact                       | assembler_owned / downstream_facing    | canonical_full    |
| GL-CONT-004-INV-010 | GL-OBJ-009   | Runtime Transport Unit     | OBJ / RUN       | carrier_object / runtime_transport_unit | governed                               | canonical_full    |
| GL-CONT-004-INV-011 | GL-OBJ-010   | Downstream Registry Record | OBJ / EXT / EXC | downstream_record                       | downstream / not_owned                 | canonical_full    |
| GL-CONT-004-INV-012 | GL-OBJ-011   | Raw Payload / Raw Content  | OBJ / EXC       | raw_input_material                      | external / pre_envelope                | canonical_full    |
| GL-CONT-004-INV-013 | GL-OBJ-012   | Envelope Identity          | OBJ             | governed_object / identity_artifact     | assembler_owned                        | canonical_partial |
| GL-CONT-004-INV-014 | GL-OBJ-013   | Envelope Metadata Block    | OBJ             | governed_object / metadata_artifact     | assembler_owned                        | canonical_partial |
| GL-CONT-004-INV-015 | GL-OBJ-014   | Envelope Timestamp Block   | OBJ             | governed_object / timestamp_artifact    | assembler_owned                        | canonical_partial |
| GL-CONT-004-INV-016 | GL-OBJ-015   | Dispatch Eligibility State | OBJ             | governed_object / readiness_state       | assembler_owned                        | canonical_partial |

---

## 4. Canonical Term Entries

---

### GL-OBJ-001 — Log Level Envelope

| Field           | Value                            |
| --------------- | -------------------------------- |
| Term ID         | GL-OBJ-001                       |
| Canonical Term  | Log Level Envelope               |
| Family          | OBJ                              |
| Category        | carrier_object / governed_object |
| Ownership Scope | assembler_owned / transferable   |
| Entry Maturity  | canonical_full                   |
| Evidence Status | direct / user_decision / derived |

#### Definition

The Log Level Envelope is the authoritative assembler-side carrier object produced by the `Envelope Assembler` after governed content has passed through the required preparation path.

It is the central runtime transport unit for prepared content inside the Assembler System.

#### Architectural Role

The Log Level Envelope carries or binds assembler-prepared content and its associated governance material.

It may carry or bind:

1. accepted typed content,
2. envelope identity,
3. metadata preparation result,
4. stabilized timestamp semantics,
5. policy assignment,
6. queue/container admission relation,
7. dispatch eligibility state,
8. delivery-cycle state,
9. handoff trace material,
10. downstream-facing handoff material.

The Log Level Envelope is produced before the `Assembler Ingress Port` receives it.

It may later become eligible for dispatcher-mediated handoff.

#### Must Not Be Confused With

1. Envelope Assembler.
2. Raw Payload / Raw Content.
3. Assembler Ingress Port.
4. Dispatcher.
5. Queue Container.
6. Downstream Registry Record.
7. Policy Object.
8. Handoff Evidence by itself.

#### Valid Usage

* “Envelope Assembler produces the Log Level Envelope.”
* “Assembler Ingress Port receives Log Level Envelopes, not raw payloads.”
* “Log Level Envelope is the runtime transport carrier.”
* “Log Level Envelope remains a carrier object, not an actor.”

#### Invalid Usage

* “Log Level Envelope assembles itself.”
* “Log Level Envelope dispatches itself to the registry.”
* “Raw content can replace Log Level Envelope as runtime transport.”
* “Log Level Envelope is the downstream registry record.”
* “Log Level Envelope owns downstream lifecycle after handoff.”

#### Related Terms

* GL-ENT-001 — Envelope Assembler
* GL-BND-006 — Assembler Ingress Port
* GL-OBJ-002 — Governed Object
* GL-OBJ-003 — Carrier Object
* GL-OBJ-009 — Runtime Transport Unit
* GL-OBJ-010 — Downstream Registry Record
* GL-OBJ-011 — Raw Payload / Raw Content

#### Source Trace

| Source Type       | Source                                                                                       |
| ----------------- | -------------------------------------------------------------------------------------------- |
| VisionAndScope.md | Log Level Envelope is central to scope and must not be replaced by raw content.              |
| SYSTEM_GOALS.md   | SG-LLE-001 and SG-LLE-002 define it as runtime transport unit and carrier object, not actor. |
| GL-CONT-003       | Envelope Assembler produces Log Level Envelope.                                              |

---

### GL-ALIAS-001 — Log Envelope

| Field           | Value        |
| --------------- | ------------ |
| Term ID         | GL-ALIAS-001 |
| Canonical Term  | Log Envelope |
| Family          | ALIAS / OBJ  |
| Category        | alias        |
| Ownership Scope | governed     |
| Entry Maturity  | alias        |
| Evidence Status | legacy_alias |

#### Definition

Log Envelope is a legacy or source-data alias that refers to the same carrier concept as `Log Level Envelope` unless a later formal distinction is introduced.

#### Architectural Role

This alias preserves compatibility with earlier source language while preventing a hidden second envelope concept from emerging.

The formal glossary term remains:

```text id="gl-alias-001-canonical"
Log Level Envelope
```

#### Must Not Be Confused With

1. A separate envelope type by default.
2. Raw Payload / Raw Content.
3. Downstream Registry Record.
4. Envelope Assembler.
5. Handoff Evidence.

#### Valid Usage

* “Source material may say Log Envelope, but formal documentation should use Log Level Envelope.”
* “Log Envelope maps to Log Level Envelope unless otherwise specified.”

#### Invalid Usage

* “Log Envelope is a different object from Log Level Envelope.”
* “Log Envelope bypasses the Log Level Envelope rules.”
* “Log Envelope is less governed than Log Level Envelope.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-003 — Carrier Object
* GL-OBJ-009 — Runtime Transport Unit

#### Source Trace

| Source Type               | Source                                                                          |
| ------------------------- | ------------------------------------------------------------------------------- |
| ProjectOverview.md        | Notes that some source references may use Log Envelope as a legacy/source term. |
| Glossary Governance Basis | GL-CONT-000 requires aliases to point to canonical terms.                       |

---

### GL-OBJ-002 — Governed Object

| Field           | Value           |
| --------------- | --------------- |
| Term ID         | GL-OBJ-002      |
| Canonical Term  | Governed Object |
| Family          | OBJ             |
| Category        | governed_object |
| Ownership Scope | governed        |
| Entry Maturity  | canonical_full  |
| Evidence Status | derived         |

#### Definition

A Governed Object is an object whose meaning, validity, movement, assignment, emission, transfer, or interpretation is controlled by explicit assembler-side architectural rules.

#### Architectural Role

Governed Object is a category term.

It includes objects such as:

1. Log Level Envelope,
2. Policy Object,
3. Policy Assignment,
4. Delivery-Cycle Flag Set,
5. Dispatcher Feedback Report,
6. Handoff Evidence,
7. Envelope Metadata Block,
8. Dispatch Eligibility State.

A governed object may be acted upon by internal actors, but it is not itself the actor unless explicitly classified otherwise.

#### Must Not Be Confused With

1. Internal actor.
2. Boundary port.
3. Runtime coordinator.
4. Processing unit.
5. Downstream lifecycle owner.
6. Generic data blob.

#### Valid Usage

* “Log Level Envelope is a governed object.”
* “Policy Assignment is a governed assignment object or relation.”
* “Handoff Evidence is governed evidence, not downstream lifecycle ownership.”

#### Invalid Usage

* “Governed Object means executable component.”
* “Governed Object means actor.”
* “Governed Object automatically becomes a C++ class.”
* “Governed Object owns downstream lifecycle.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-003 — Carrier Object
* GL-TRC-001 — Delegated Entity
* GL-TRC-002 — Supporting Entity
* GL-ENT-012 — Runtime Coordination Actor

#### Source Trace

| Source Type        | Source                                                                                         |
| ------------------ | ---------------------------------------------------------------------------------------------- |
| GL-CONT-000        | Category model defines governed_object and distinguishes it from actor and carrier categories. |
| ProjectOverview.md | Architectural taxonomy separates governed objects from internal entities and runtime state.    |

---

### GL-OBJ-003 — Carrier Object

| Field           | Value          |
| --------------- | -------------- |
| Term ID         | GL-OBJ-003     |
| Canonical Term  | Carrier Object |
| Family          | OBJ            |
| Category        | carrier_object |
| Ownership Scope | governed       |
| Entry Maturity  | canonical_full |
| Evidence Status | derived        |

#### Definition

A Carrier Object is a governed object whose primary architectural role is to carry prepared content, state, assignment, evidence, or transfer material across an assembler-side path.

#### Architectural Role

Carrier Object distinguishes carried material from actors that perform work.

The primary carrier object in the Assembler System is the `Log Level Envelope`.

Carrier objects may move through ingress admission, queue/container coordination, dispatch readiness, and handoff preparation without becoming the actor that performs those transitions.

#### Must Not Be Confused With

1. Actor.
2. Producer.
3. Dispatcher.
4. Port.
5. Queue Container.
6. Downstream registry record by default.

#### Valid Usage

* “Log Level Envelope is a carrier object.”
* “A carrier object can be admitted, placed, dispatched, or handed off.”
* “Carrier object status does not imply actor behavior.”

#### Invalid Usage

* “Carrier Object performs dispatch.”
* “Carrier Object owns the queue.”
* “Carrier Object replaces the Dispatcher.”
* “Carrier Object is automatically a downstream record.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-002 — Governed Object
* GL-OBJ-009 — Runtime Transport Unit
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type     | Source                                                                                    |
| --------------- | ----------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-LLE-002 states Log Level Envelope remains a carrier object, not an actor.              |
| GL-CONT-000     | Category model defines carrier_object and prohibits treating Log Level Envelope as actor. |

---

### GL-OBJ-004 — Policy Object

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-OBJ-004                             |
| Canonical Term  | Policy Object                          |
| Family          | OBJ / POL                              |
| Category        | governed_object / policy_material      |
| Ownership Scope | external_supplied / assembler_governed |
| Entry Maturity  | canonical_full                         |
| Evidence Status | direct / derived                       |

#### Definition

A Policy Object is governed policy material supplied by a policy source or represented inside assembler-side policy assignment semantics.

It governs behavior but does not execute behavior by itself.

#### Architectural Role

Policy Object preserves the distinction between policy material and the components that consume or host policy-governed mechanisms.

The policy chain is:

```text id="gl-obj-004-policy-chain"
Policy Registry / Policy Source
  supplies:
    Policy Object

PolicyAssigner
  mediates:
    Policy Assignment

Policy-Consuming Component
  realizes:
    Policy-Governed Mechanism
```

#### Must Not Be Confused With

1. PolicyAssigner.
2. Policy Registry / Policy Source.
3. Policy-Consuming Component.
4. Policy Host.
5. Metadata Injector.
6. Validator.
7. Dispatcher.
8. Log Level Envelope.

#### Valid Usage

* “Policy Object governs behavior.”
* “PolicyAssigner assigns Policy Objects.”
* “Policy-consuming components realize policy-governed mechanisms.”

#### Invalid Usage

* “Policy Object executes behavior.”
* “Policy Object is the PolicyAssigner.”
* “Policy Object is the policy source.”
* “Policy Object makes Metadata Injector policy-hosted.”

#### Related Terms

* GL-EXT-003 — Policy Registry / Policy Source
* GL-ENT-006 — PolicyAssigner
* GL-ENT-011 — Policy-Consuming Component
* GL-OBJ-005 — Policy Assignment

#### Source Trace

| Source Type        | Source                                                                               |
| ------------------ | ------------------------------------------------------------------------------------ |
| ProjectOverview.md | Defines policy objects as assigned by PolicyAssigner to policy-consuming components. |
| SYSTEM_GOALS.md    | SG-POL-001 states Policy Object remains distinct from policy-consuming component.    |

---

### GL-OBJ-005 — Policy Assignment

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-OBJ-005                            |
| Canonical Term  | Policy Assignment                     |
| Family          | OBJ / POL                             |
| Category        | governed_object / assignment_relation |
| Ownership Scope | assembler_owned                       |
| Entry Maturity  | canonical_full                        |
| Evidence Status | direct / derived                      |

#### Definition

Policy Assignment is the governed association between a Policy Object and an eligible policy-consuming component or policy-governed mechanism.

#### Architectural Role

Policy Assignment is mediated by `PolicyAssigner`.

It records or expresses which policy material applies to which eligible component or behavior.

It is not the same thing as the policy object itself, the policy source, or the component consuming the policy.

#### Must Not Be Confused With

1. Policy Object.
2. PolicyAssigner.
3. Policy Registry / Policy Source.
4. Policy-consuming component.
5. Policy execution.
6. Metadata preparation.
7. Downstream policy lifecycle.

#### Valid Usage

* “PolicyAssigner mediates Policy Assignment.”
* “Policy Assignment links policy material to eligible components.”
* “Policy Assignment does not make the policy object an actor.”

#### Invalid Usage

* “Policy Assignment is the Policy Object.”
* “Policy Assignment is the policy source.”
* “Policy Assignment executes the mechanism.”
* “Policy Assignment owns downstream registry policy.”

#### Related Terms

* GL-OBJ-004 — Policy Object
* GL-ENT-006 — PolicyAssigner
* GL-ENT-011 — Policy-Consuming Component
* GL-POL-* — Policy-Governed Mechanism

#### Source Trace

| Source Type        | Source                                                                               |
| ------------------ | ------------------------------------------------------------------------------------ |
| ProjectOverview.md | PolicyAssigner mediates assignment of Policy Objects to policy-consuming components. |
| SYSTEM_GOALS.md    | SG-POL-002 requires PolicyAssigner to mediate policy assignment semantics.           |

---

### GL-OBJ-006 — Delivery-Cycle Flag Set

| Field           | Value                            |
| --------------- | -------------------------------- |
| Term ID         | GL-OBJ-006                       |
| Canonical Term  | Delivery-Cycle Flag Set          |
| Family          | OBJ                              |
| Category        | governed_object / state_artifact |
| Ownership Scope | assembler_owned                  |
| Entry Maturity  | canonical_partial                |
| Evidence Status | direct / seed_low_detail         |

#### Definition

Delivery-Cycle Flag Set is a governed state artifact representing delivery-cycle-related flags associated with dispatch or delivery progression.

#### Architectural Role

Delivery-Cycle Flag Set may support dispatch/delivery readiness, round coordination, or delivery-state inspection within assembler-owned preparation and dispatch boundaries.

It is not a feedback report.

It is not a downstream registry record.

It does not own lifecycle after handoff.

#### Must Not Be Confused With

1. Dispatcher Feedback Report.
2. Handoff Evidence.
3. Downstream Registry Record.
4. Dispatching / Delivery Round Manager.
5. Dispatcher.
6. Queue Container state by default.

#### Valid Usage

* “Delivery-Cycle Flag Set is a governed delivery-state artifact.”
* “Delivery-Cycle Flag Set may participate in readiness interpretation.”
* “Delivery-Cycle Flag Set is distinct from Dispatcher Feedback Report.”

#### Invalid Usage

* “Delivery-Cycle Flag Set is the Dispatcher.”
* “Delivery-Cycle Flag Set is a feedback report.”
* “Delivery-Cycle Flag Set owns downstream delivery lifecycle.”
* “Delivery-Cycle Flag Set is a registry record.”

#### Related Terms

* GL-OBJ-007 — Dispatcher Feedback Report
* GL-OBJ-015 — Dispatch Eligibility State
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type             | Source                                                                                            |
| ----------------------- | ------------------------------------------------------------------------------------------------- |
| GL-CONT-000             | Anti-collapse guard examples distinguish Delivery-Cycle Flag Set from Dispatcher Feedback Report. |
| Glossary Planning Basis | GL-CONT-004 planning identifies Delivery-Cycle Flag Set as a governed object term.                |

---

### GL-OBJ-007 — Dispatcher Feedback Report

| Field           | Value                             |
| --------------- | --------------------------------- |
| Term ID         | GL-OBJ-007                        |
| Canonical Term  | Dispatcher Feedback Report        |
| Family          | OBJ                               |
| Category        | governed_object / report_artifact |
| Ownership Scope | assembler_owned / emitted         |
| Entry Maturity  | canonical_partial                 |
| Evidence Status | direct / seed_low_detail          |

#### Definition

Dispatcher Feedback Report is a governed report artifact emitted or associated with dispatcher-side feedback about handoff, readiness, delivery outcome, or dispatch interpretation within assembler-side boundaries.

#### Architectural Role

Dispatcher Feedback Report may record or communicate dispatcher-related feedback.

It is not the Dispatcher.

It is not a Delivery-Cycle Flag Set.

It is not downstream registry lifecycle ownership.

It must not be used to re-open assembler authority after valid handoff.

#### Must Not Be Confused With

1. Dispatcher.
2. Delivery-Cycle Flag Set.
3. Handoff Evidence.
4. Downstream Registry Record.
5. Dispatching / Delivery Round Manager.
6. Registry / Delivery Port.

#### Valid Usage

* “Dispatcher Feedback Report is a report artifact.”
* “Dispatcher Feedback Report may describe dispatch-side feedback.”
* “Dispatcher Feedback Report is distinct from Delivery-Cycle Flag Set.”

#### Invalid Usage

* “Dispatcher Feedback Report performs dispatch.”
* “Dispatcher Feedback Report owns downstream lifecycle.”
* “Dispatcher Feedback Report is the delivery-cycle flag set.”
* “Dispatcher Feedback Report replaces Handoff Evidence.”

#### Related Terms

* GL-ENT-002 — Dispatcher
* GL-OBJ-006 — Delivery-Cycle Flag Set
* GL-OBJ-008 — Handoff Evidence
* GL-BND-008 — Registry / Delivery Port

#### Source Trace

| Source Type             | Source                                                                                            |
| ----------------------- | ------------------------------------------------------------------------------------------------- |
| GL-CONT-000             | Anti-collapse guard examples distinguish Delivery-Cycle Flag Set from Dispatcher Feedback Report. |
| Glossary Planning Basis | GL-CONT-004 planning identifies Dispatcher Feedback Report as a governed object term.             |

---

### GL-OBJ-008 — Handoff Evidence

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-OBJ-008                          |
| Canonical Term  | Handoff Evidence                    |
| Family          | OBJ / EXC                           |
| Category        | evidence_artifact                   |
| Ownership Scope | assembler_owned / downstream_facing |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

Handoff Evidence is trace material preserved by the Assembler System to show that a prepared carrier or handoff material reached a valid dispatcher-mediated handoff boundary.

#### Architectural Role

Handoff Evidence supports auditability, reviewability, and compliance without transferring downstream lifecycle authority back to the Assembler.

It may identify:

1. envelope identity,
2. handoff eligibility condition,
3. dispatcher-mediated transfer,
4. target boundary surface,
5. handoff timestamp or stabilized time reference,
6. authority-closure marker,
7. downstream-facing receipt material if available.

#### Must Not Be Confused With

1. Downstream Registry Record.
2. Downstream lifecycle ownership.
3. Dispatcher Feedback Report by default.
4. Policy Assignment.
5. Log Level Envelope itself.
6. Registry internals.

#### Valid Usage

* “Handoff Evidence may be preserved for audit.”
* “Handoff Evidence does not imply downstream lifecycle ownership.”
* “Handoff Evidence supports proof of assembler authority closure.”

#### Invalid Usage

* “Handoff Evidence lets Assembler mutate downstream records.”
* “Handoff Evidence is the registry record.”
* “Handoff Evidence reopens assembler authority after valid handoff.”
* “Handoff Evidence is the Dispatcher.”

#### Related Terms

* GL-ENT-002 — Dispatcher
* GL-BND-008 — Registry / Delivery Port
* GL-BND-004 — Authority Boundary
* GL-EXC-001 — Post-Handoff Non-Ownership
* GL-OBJ-010 — Downstream Registry Record

#### Source Trace

| Source Type     | Source                                                                                           |
| --------------- | ------------------------------------------------------------------------------------------------ |
| SYSTEM_GOALS.md | SG-DISP-007 permits preserving handoff evidence without claiming downstream lifecycle ownership. |
| GL-CONT-002     | Authority boundary and post-handoff non-ownership are established.                               |

---

### GL-OBJ-009 — Runtime Transport Unit

| Field           | Value                                   |
| --------------- | --------------------------------------- |
| Term ID         | GL-OBJ-009                              |
| Canonical Term  | Runtime Transport Unit                  |
| Family          | OBJ / RUN                               |
| Category        | carrier_object / runtime_transport_unit |
| Ownership Scope | governed                                |
| Entry Maturity  | canonical_full                          |
| Evidence Status | derived                                 |

#### Definition

Runtime Transport Unit is the governed unit that moves through assembler-side runtime coordination after preparation.

Within the Assembler System, the canonical runtime transport unit is the `Log Level Envelope`.

#### Architectural Role

This term prevents raw content or arbitrary payloads from becoming the runtime unit.

The runtime path must move prepared, governed carriers rather than informal payloads.

#### Must Not Be Confused With

1. Raw Payload / Raw Content.
2. Queue Container.
3. Slot.
4. Waiting List item by default.
5. Downstream Registry Record.
6. Message broker message.

#### Valid Usage

* “Log Level Envelope is the runtime transport unit.”
* “Raw content must not replace the runtime transport unit.”
* “Runtime transport unit remains governed by envelope carrier rules.”

#### Invalid Usage

* “Runtime Transport Unit is raw payload.”
* “Runtime Transport Unit is the Queue Container.”
* “Runtime Transport Unit is a broker message.”
* “Runtime Transport Unit is automatically the downstream registry record.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-003 — Carrier Object
* GL-OBJ-011 — Raw Payload / Raw Content
* GL-RUN-* — Queue Container
* GL-RUN-* — Slot

#### Source Trace

| Source Type       | Source                                                                                  |
| ----------------- | --------------------------------------------------------------------------------------- |
| VisionAndScope.md | Raw content must not replace Log Level Envelope as runtime transport.                   |
| SYSTEM_GOALS.md   | SG-LLE-001 prohibits raw content from replacing the envelope as runtime transport unit. |

---

### GL-OBJ-010 — Downstream Registry Record

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-OBJ-010                 |
| Canonical Term  | Downstream Registry Record |
| Family          | OBJ / EXT / EXC            |
| Category        | downstream_record          |
| Ownership Scope | downstream / not_owned     |
| Entry Maturity  | canonical_full             |
| Evidence Status | derived                    |

#### Definition

A Downstream Registry Record is a record owned by a downstream registry or preservation system after valid dispatcher-mediated handoff.

It is outside assembler ownership.

#### Architectural Role

This term protects the Assembler System from claiming downstream registry internals, downstream persistence lifecycle, query lifecycle, indexing, replay, mutation, correction, or inspection authority.

A Log Level Envelope may be handed off toward downstream preservation, but it must not be treated as assembler-owned downstream lifecycle after handoff.

#### Must Not Be Confused With

1. Log Level Envelope.
2. Handoff Evidence.
3. Dispatcher Feedback Report.
4. Queue Container state.
5. Assembler-owned object.
6. Registry / Delivery Port.

#### Valid Usage

* “Downstream Registry Record is not assembler-owned.”
* “Assembler may hand off prepared envelope material toward downstream records.”
* “Registry internals remain downstream.”

#### Invalid Usage

* “Assembler owns Downstream Registry Record lifecycle.”
* “Log Level Envelope is automatically the downstream registry record.”
* “Handoff Evidence is the downstream registry record.”
* “Registry / Delivery Port owns registry internals.”

#### Related Terms

* GL-EXT-006 — Log Level Records Registry
* GL-BND-005 — Downstream Boundary
* GL-BND-008 — Registry / Delivery Port
* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-008 — Handoff Evidence

#### Source Trace

| Source Type       | Source                                                                                                 |
| ----------------- | ------------------------------------------------------------------------------------------------------ |
| VisionAndScope.md | Permanent exclusions define downstream registry internals and lifecycle as outside assembler scope.    |
| SYSTEM_GOALS.md   | Authority exclusion goals prohibit assembler ownership of registry internals and downstream lifecycle. |
| GL-CONT-002       | Downstream Boundary and Log Level Records Registry are downstream/not-owned.                           |

---

### GL-OBJ-011 — Raw Payload / Raw Content

| Field           | Value                     |
| --------------- | ------------------------- |
| Term ID         | GL-OBJ-011                |
| Canonical Term  | Raw Payload / Raw Content |
| Family          | OBJ / EXC                 |
| Category        | raw_input_material        |
| Ownership Scope | external / pre_envelope   |
| Entry Maturity  | canonical_full            |
| Evidence Status | derived                   |

#### Definition

Raw Payload or Raw Content is incoming material before it has been transformed into a governed `Log Level Envelope`.

#### Architectural Role

This term exists primarily as an exclusion guard.

Raw content may be a pre-envelope input concept, but it must not become the assembler-side runtime transport unit and must not bypass envelope assembly.

#### Must Not Be Confused With

1. Log Level Envelope.
2. Runtime Transport Unit.
3. Downstream Registry Record.
4. Handoff Evidence.
5. Accepted dispatch-ready envelope.
6. Queue-contained envelope.

#### Valid Usage

* “Raw content must be prepared into Log Level Envelope before runtime transport.”
* “Raw Payload is pre-envelope material.”
* “Raw content must not bypass envelope assembly.”

#### Invalid Usage

* “Raw Payload is admitted directly into runtime queue slots.”
* “Raw content replaces Log Level Envelope.”
* “Raw content is dispatch-ready by default.”
* “Raw content is the downstream registry record.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-009 — Runtime Transport Unit
* GL-ENT-001 — Envelope Assembler
* GL-BND-006 — Assembler Ingress Port

#### Source Trace

| Source Type     | Source                                                                                        |
| --------------- | --------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-ING-004 requires Assembler Ingress Port to receive envelopes, not raw payloads.            |
| SYSTEM_GOALS.md | SG-LLE-001 prohibits raw content from replacing Log Level Envelope as runtime transport unit. |
| GL-CONT-003     | Envelope Assembler produces envelope before Assembler Ingress Port receives it.               |

---

### GL-OBJ-012 — Envelope Identity

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-OBJ-012                          |
| Canonical Term  | Envelope Identity                   |
| Family          | OBJ                                 |
| Category        | governed_object / identity_artifact |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_partial                   |
| Evidence Status | derived                             |

#### Definition

Envelope Identity is the governed identity artifact or identity semantics associated with a Log Level Envelope.

#### Architectural Role

Envelope Identity supports traceability across preparation, queue/container admission, dispatch readiness, and handoff evidence.

It should not be confused with downstream registry identity unless a later formal mapping explicitly defines that relationship.

#### Must Not Be Confused With

1. Downstream Registry Record identity by default.
2. Queue Container Identifier.
3. Handoff Evidence.
4. Policy Assignment.
5. Raw Payload identity.

#### Valid Usage

* “Envelope Identity supports traceability.”
* “Envelope Identity may appear in handoff evidence.”
* “Envelope Identity is distinct from Queue Container Identifier.”

#### Invalid Usage

* “Envelope Identity is automatically downstream registry primary key.”
* “Envelope Identity is the Queue Container Identifier.”
* “Envelope Identity owns lifecycle after handoff.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-OBJ-008 — Handoff Evidence
* GL-RUN-* — Queue Container Identifier
* GL-OBJ-010 — Downstream Registry Record

#### Source Trace

| Source Type        | Source                                                                             |
| ------------------ | ---------------------------------------------------------------------------------- |
| ProjectOverview.md | Log Level Envelope may carry or bind envelope identity and handoff trace material. |
| VisionAndScope.md  | Envelope scope includes typed carrier and dispatch-ready carrier semantics.        |

---

### GL-OBJ-013 — Envelope Metadata Block

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-OBJ-013                          |
| Canonical Term  | Envelope Metadata Block             |
| Family          | OBJ                                 |
| Category        | governed_object / metadata_artifact |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_partial                   |
| Evidence Status | derived                             |

#### Definition

Envelope Metadata Block is the metadata artifact carried by or bound to a Log Level Envelope after assembler-side metadata preparation.

#### Architectural Role

Envelope Metadata Block captures the result of metadata preparation without turning the Metadata Injector into a policy host and without claiming downstream metadata lifecycle ownership.

#### Must Not Be Confused With

1. Metadata Injector.
2. Metadata Directive Source.
3. Policy Object.
4. Policy Assignment.
5. Downstream registry metadata lifecycle.
6. Raw content metadata by default.

#### Valid Usage

* “Envelope Metadata Block is carried by the Log Level Envelope.”
* “Metadata Injector prepares or applies metadata that may appear in the envelope metadata block.”
* “Envelope Metadata Block is schema/directive-governed, not policy-hosted by default.”

#### Invalid Usage

* “Envelope Metadata Block is the Metadata Injector.”
* “Envelope Metadata Block owns policy assignment.”
* “Envelope Metadata Block owns downstream registry metadata lifecycle.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-ENT-004 — Metadata Injector
* GL-EXT-004 — Metadata Directive Source
* GL-OBJ-004 — Policy Object

#### Source Trace

| Source Type        | Source                                                                |
| ------------------ | --------------------------------------------------------------------- |
| ProjectOverview.md | Log Level Envelope may carry or bind metadata.                        |
| SYSTEM_GOALS.md    | Metadata Injector is schema/directive-governed and not policy-hosted. |

---

### GL-OBJ-014 — Envelope Timestamp Block

| Field           | Value                                |
| --------------- | ------------------------------------ |
| Term ID         | GL-OBJ-014                           |
| Canonical Term  | Envelope Timestamp Block             |
| Family          | OBJ                                  |
| Category        | governed_object / timestamp_artifact |
| Ownership Scope | assembler_owned                      |
| Entry Maturity  | canonical_partial                    |
| Evidence Status | derived                              |

#### Definition

Envelope Timestamp Block is the timestamp artifact carried by or bound to a Log Level Envelope after timestamp semantics have been stabilized.

#### Architectural Role

Envelope Timestamp Block preserves stabilized timestamp semantics before dispatch eligibility.

It belongs to assembler-side preparation and does not become downstream query interpretation.

#### Must Not Be Confused With

1. Timestamp Stabilizer.
2. Downstream query timestamp interpretation.
3. Storage timestamp lifecycle.
4. Handoff Evidence by default.
5. Raw payload timestamp.

#### Valid Usage

* “Envelope Timestamp Block carries stabilized timestamp semantics.”
* “Timestamp Stabilizer prepares timestamp semantics before dispatch eligibility.”
* “Envelope Timestamp Block is not downstream query interpretation.”

#### Invalid Usage

* “Envelope Timestamp Block performs timestamp stabilization.”
* “Envelope Timestamp Block owns query lifecycle.”
* “Envelope Timestamp Block owns downstream storage timestamps.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-ENT-005 — Timestamp Stabilizer
* GL-OBJ-015 — Dispatch Eligibility State
* GL-OBJ-008 — Handoff Evidence

#### Source Trace

| Source Type     | Source                                                                                         |
| --------------- | ---------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-TIME-001 requires timestamp semantics to be stabilized before dispatch eligibility.         |
| SYSTEM_GOALS.md | SG-TIME-002 keeps timestamp stabilization assembler-side, not downstream query interpretation. |

---

### GL-OBJ-015 — Dispatch Eligibility State

| Field           | Value                             |
| --------------- | --------------------------------- |
| Term ID         | GL-OBJ-015                        |
| Canonical Term  | Dispatch Eligibility State        |
| Family          | OBJ                               |
| Category        | governed_object / readiness_state |
| Ownership Scope | assembler_owned                   |
| Entry Maturity  | canonical_partial                 |
| Evidence Status | derived                           |

#### Definition

Dispatch Eligibility State is the governed readiness state indicating whether a prepared carrier is eligible for dispatcher-mediated handoff.

#### Architectural Role

Dispatch Eligibility State supports the transition from preparation and runtime coordination to final outbound handoff.

It may be determined or consumed by dispatcher-side or delivery-round behavior, but it is not itself the Dispatcher.

#### Must Not Be Confused With

1. Dispatcher.
2. Dispatching / Delivery Round Manager.
3. Handoff Evidence.
4. Downstream Registry Record.
5. Delivery-Cycle Flag Set by default.
6. Queue Container state by default.

#### Valid Usage

* “Dispatcher verifies or relies on Dispatch Eligibility State.”
* “Dispatch Eligibility State is a governed readiness state.”
* “Prepared envelopes must satisfy handoff eligibility before outbound transfer.”

#### Invalid Usage

* “Dispatch Eligibility State performs dispatch.”
* “Dispatch Eligibility State owns downstream lifecycle.”
* “Dispatch Eligibility State is the downstream registry record.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-ENT-002 — Dispatcher
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-OBJ-006 — Delivery-Cycle Flag Set
* GL-OBJ-008 — Handoff Evidence

#### Source Trace

| Source Type       | Source                                                                                             |
| ----------------- | -------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md   | SG-DISP-003 requires Dispatcher to verify or rely on handoff eligibility before outbound transfer. |
| VisionAndScope.md | Log Level Envelope scope includes dispatch-ready carrier semantics.                                |

---

## 5. Governed Object Classification Matrix

|            Record ID | Term                       |   Governed Object? |           Carrier? | Actor? |      Downstream-Owned? | Notes                                         |
| -------------------: | -------------------------- | -----------------: | -----------------: | -----: | ---------------------: | --------------------------------------------- |
| GL-CONT-004-GOCM-001 | Log Level Envelope         |                Yes |                Yes |     No |      No before handoff | Central runtime transport carrier             |
| GL-CONT-004-GOCM-002 | Log Envelope               |              Alias |              Alias |     No |                     No | Legacy/source alias for Log Level Envelope    |
| GL-CONT-004-GOCM-003 | Governed Object            |           Category |        Conditional |     No |            Conditional | Classification term                           |
| GL-CONT-004-GOCM-004 | Carrier Object             |           Category |                Yes |     No |            Conditional | Object that carries governed material         |
| GL-CONT-004-GOCM-005 | Policy Object              |                Yes |    Policy material |     No | Source may be external | Governs behavior, does not execute            |
| GL-CONT-004-GOCM-006 | Policy Assignment          |                Yes |  Relation/artifact |     No |                     No | Mediated by PolicyAssigner                    |
| GL-CONT-004-GOCM-007 | Delivery-Cycle Flag Set    |                Yes |     State artifact |     No |                     No | Distinct from feedback report                 |
| GL-CONT-004-GOCM-008 | Dispatcher Feedback Report |                Yes |    Report artifact |     No |                     No | Distinct from flag set                        |
| GL-CONT-004-GOCM-009 | Handoff Evidence           |                Yes |  Evidence artifact |     No |                     No | Does not imply downstream lifecycle ownership |
| GL-CONT-004-GOCM-010 | Runtime Transport Unit     |           Category |                Yes |     No |                     No | Canonically Log Level Envelope                |
| GL-CONT-004-GOCM-011 | Downstream Registry Record |     Yes downstream |  No assembler-side |     No |                    Yes | Not assembler-owned                           |
| GL-CONT-004-GOCM-012 | Raw Payload / Raw Content  | Pre-governed input |                 No |     No |  External/pre-envelope | Must not replace envelope                     |
| GL-CONT-004-GOCM-013 | Envelope Identity          |                Yes |  Identity artifact |     No |          No by default | Distinct from downstream registry identity    |
| GL-CONT-004-GOCM-014 | Envelope Metadata Block    |                Yes |  Metadata artifact |     No |                     No | Result of metadata preparation                |
| GL-CONT-004-GOCM-015 | Envelope Timestamp Block   |                Yes | Timestamp artifact |     No |                     No | Result of timestamp stabilization             |
| GL-CONT-004-GOCM-016 | Dispatch Eligibility State |                Yes |    Readiness state |     No |                     No | Consumed by Dispatcher or delivery path       |

---

## 6. Envelope Composition Reference

### 6.1 Envelope-Bound Material

A Log Level Envelope may carry or bind the following governed material:

|           Record ID | Envelope Material          | Term ID    | Role                                            |
| ------------------: | -------------------------- | ---------- | ----------------------------------------------- |
| GL-CONT-004-ENV-001 | Envelope Identity          | GL-OBJ-012 | Stable envelope traceability                    |
| GL-CONT-004-ENV-002 | Envelope Metadata Block    | GL-OBJ-013 | Metadata preparation result                     |
| GL-CONT-004-ENV-003 | Envelope Timestamp Block   | GL-OBJ-014 | Stabilized timestamp semantics                  |
| GL-CONT-004-ENV-004 | Policy Assignment          | GL-OBJ-005 | Policy association result                       |
| GL-CONT-004-ENV-005 | Dispatch Eligibility State | GL-OBJ-015 | Readiness for outbound handoff                  |
| GL-CONT-004-ENV-006 | Delivery-Cycle Flag Set    | GL-OBJ-006 | Delivery-cycle state artifact, where applicable |
| GL-CONT-004-ENV-007 | Handoff Evidence Reference | GL-OBJ-008 | Trace material after or around handoff          |

### 6.2 Envelope Non-Contents by Default

The following must not be assumed to be inside the envelope unless a later formal contract defines it:

|               Record ID | Non-Content                     | Reason                                     |
| ----------------------: | ------------------------------- | ------------------------------------------ |
| GL-CONT-004-NONCONT-001 | Downstream Registry Record      | Downstream-owned after handoff             |
| GL-CONT-004-NONCONT-002 | Dispatcher                      | Actor, not envelope content                |
| GL-CONT-004-NONCONT-003 | Envelope Assembler              | Producer, not produced carrier content     |
| GL-CONT-004-NONCONT-004 | Queue Container                 | Runtime container, not envelope content    |
| GL-CONT-004-NONCONT-005 | Policy Registry / Policy Source | External source, not envelope content      |
| GL-CONT-004-NONCONT-006 | Raw Payload as runtime unit     | Must be transformed into governed envelope |

---

## 7. Object Relationship Map

|           Record ID | Source Term                     | Relationship          | Target Term                |
| ------------------: | ------------------------------- | --------------------- | -------------------------- |
| GL-CONT-004-REL-001 | Envelope Assembler              | produces              | Log Level Envelope         |
| GL-CONT-004-REL-002 | Log Envelope                    | alias_of              | Log Level Envelope         |
| GL-CONT-004-REL-003 | Log Level Envelope              | is_a                  | Carrier Object             |
| GL-CONT-004-REL-004 | Log Level Envelope              | is_a                  | Governed Object            |
| GL-CONT-004-REL-005 | Log Level Envelope              | serves_as             | Runtime Transport Unit     |
| GL-CONT-004-REL-006 | Raw Payload / Raw Content       | must_be_prepared_into | Log Level Envelope         |
| GL-CONT-004-REL-007 | Assembler Ingress Port          | receives              | Log Level Envelope         |
| GL-CONT-004-REL-008 | Policy Registry / Policy Source | supplies              | Policy Object              |
| GL-CONT-004-REL-009 | PolicyAssigner                  | mediates              | Policy Assignment          |
| GL-CONT-004-REL-010 | Policy Assignment               | associates            | Policy Object              |
| GL-CONT-004-REL-011 | Policy Assignment               | targets               | Policy-Consuming Component |
| GL-CONT-004-REL-012 | Metadata Injector               | prepares              | Envelope Metadata Block    |
| GL-CONT-004-REL-013 | Timestamp Stabilizer            | prepares              | Envelope Timestamp Block   |
| GL-CONT-004-REL-014 | Dispatcher                      | relies_on_or_verifies | Dispatch Eligibility State |
| GL-CONT-004-REL-015 | Dispatcher                      | may_emit_or_reference | Dispatcher Feedback Report |
| GL-CONT-004-REL-016 | Dispatcher                      | produces_or_preserves | Handoff Evidence           |
| GL-CONT-004-REL-017 | Handoff Evidence                | must_not_be           | Downstream Registry Record |
| GL-CONT-004-REL-018 | Log Level Envelope              | must_not_be           | Downstream Registry Record |
| GL-CONT-004-REL-019 | Delivery-Cycle Flag Set         | must_not_be           | Dispatcher Feedback Report |
| GL-CONT-004-REL-020 | Downstream Registry Record      | owned_by              | Log Level Records Registry |

---

## 8. Pack-Level Anti-Collapse Index

|          Record ID | Term                       | Must Not Collapse Into       | Guard Meaning                                        |
| -----------------: | -------------------------- | ---------------------------- | ---------------------------------------------------- |
| GL-CONT-004-AC-001 | Log Level Envelope         | Envelope Assembler           | Carrier is not producer                              |
| GL-CONT-004-AC-002 | Log Level Envelope         | Raw Payload / Raw Content    | Prepared carrier is not raw input                    |
| GL-CONT-004-AC-003 | Log Level Envelope         | Dispatcher                   | Carrier is not final actor                           |
| GL-CONT-004-AC-004 | Log Level Envelope         | Downstream Registry Record   | Assembler carrier is not downstream lifecycle record |
| GL-CONT-004-AC-005 | Log Level Envelope         | Queue Container              | Carrier is not runtime container                     |
| GL-CONT-004-AC-006 | Log Envelope               | Independent canonical object | Alias must not fork meaning                          |
| GL-CONT-004-AC-007 | Governed Object            | Actor                        | Object governance is not behavior ownership          |
| GL-CONT-004-AC-008 | Carrier Object             | Actor                        | Carrying material is not performing work             |
| GL-CONT-004-AC-009 | Policy Object              | PolicyAssigner               | Policy material is not assignment mediator           |
| GL-CONT-004-AC-010 | Policy Object              | Policy-Consuming Component   | Governance material is not host component            |
| GL-CONT-004-AC-011 | Policy Assignment          | Policy Object                | Assignment relation is not policy material itself    |
| GL-CONT-004-AC-012 | Delivery-Cycle Flag Set    | Dispatcher Feedback Report   | State flags are not report artifact                  |
| GL-CONT-004-AC-013 | Dispatcher Feedback Report | Dispatcher                   | Report is not actor                                  |
| GL-CONT-004-AC-014 | Handoff Evidence           | Downstream Registry Record   | Evidence is not lifecycle record                     |
| GL-CONT-004-AC-015 | Handoff Evidence           | Downstream ownership         | Evidence does not reopen authority                   |
| GL-CONT-004-AC-016 | Runtime Transport Unit     | Raw Payload / Raw Content    | Runtime transport must be governed envelope          |
| GL-CONT-004-AC-017 | Downstream Registry Record | Assembler-owned object       | Registry record is downstream-owned                  |
| GL-CONT-004-AC-018 | Envelope Metadata Block    | Metadata Injector            | Metadata artifact is not component                   |
| GL-CONT-004-AC-019 | Envelope Timestamp Block   | Timestamp Stabilizer         | Timestamp artifact is not component                  |
| GL-CONT-004-AC-020 | Dispatch Eligibility State | Dispatcher                   | Readiness state is not actor                         |

---

## 9. Alias and Usage Notes

|             Record ID | Alias / Variant   | Canonical Term             | Status              | Usage Rule                                             |
| --------------------: | ----------------- | -------------------------- | ------------------- | ------------------------------------------------------ |
| GL-CONT-004-ALIAS-001 | Log Envelope      | Log Level Envelope         | legacy_alias        | Use Log Level Envelope in formal documentation         |
| GL-CONT-004-ALIAS-002 | Envelope          | Log Level Envelope         | ambiguous_shorthand | Only use after canonical term is introduced in context |
| GL-CONT-004-ALIAS-003 | LLE               | Log Level Envelope         | abbreviation        | Allowed in dense tables after definition               |
| GL-CONT-004-ALIAS-004 | Raw Payload       | Raw Payload / Raw Content  | variant             | Use combined canonical term in glossary entries        |
| GL-CONT-004-ALIAS-005 | Raw Content       | Raw Payload / Raw Content  | variant             | Use combined canonical term in glossary entries        |
| GL-CONT-004-ALIAS-006 | Handoff Trace     | Handoff Evidence           | possible_alias      | Use Handoff Evidence in formal usage                   |
| GL-CONT-004-ALIAS-007 | Dispatch Feedback | Dispatcher Feedback Report | shorthand           | Use full canonical term in tables                      |
| GL-CONT-004-ALIAS-008 | Registry Record   | Downstream Registry Record | ambiguous           | Must clarify downstream/non-owned status               |
| GL-CONT-004-ALIAS-009 | Policy Bundle     | Policy Object / Policy Set | needs_review        | Do not use as canonical until policy pack defines it   |
| GL-CONT-004-ALIAS-010 | Envelope Metadata | Envelope Metadata Block    | shorthand           | Use full term for object-model derivation              |

---

## 10. Object Flow Reference

### 10.1 Pre-Envelope to Envelope Flow

```text id="gl-cont-004-pre-envelope-flow"
Raw Payload / Raw Content
  enters consuming-side preparation context

Envelope Assembler
  composes required preparation participants
  produces:
    Log Level Envelope

Log Level Envelope
  becomes:
    Runtime Transport Unit
```

### 10.2 Envelope Governance Flow

```text id="gl-cont-004-envelope-governance-flow"
Log Level Envelope
  carries / binds:
    Envelope Identity
    Envelope Metadata Block
    Envelope Timestamp Block
    Policy Assignment
    Dispatch Eligibility State
```

### 10.3 Handoff Evidence Flow

```text id="gl-cont-004-handoff-evidence-flow"
Dispatcher
  verifies or relies on:
    Dispatch Eligibility State

Dispatcher
  performs:
    Dispatcher-Mediated Handoff

Assembler may preserve:
  Handoff Evidence

Handoff Evidence
  must not become:
    Downstream Registry Record
    Downstream lifecycle ownership
```

---

## 11. Source Trace Summary

|           Record ID | Source Area        | Supported Terms                                                                                         |
| ------------------: | ------------------ | ------------------------------------------------------------------------------------------------------- |
| GL-CONT-004-SRC-001 | README.md          | Log Level Envelope centrality, carrier object distinction, downstream registry non-ownership            |
| GL-CONT-004-SRC-002 | ProjectOverview.md | Log Level Envelope, Log Envelope alias, carrier role, envelope-bound material                           |
| GL-CONT-004-SRC-003 | VisionAndScope.md  | Envelope centrality, runtime transport unit, raw-content exclusion, non-actor status                    |
| GL-CONT-004-SRC-004 | SYSTEM_GOALS.md    | SG-LLE goals, dispatcher evidence goal, policy object distinction, authority exclusion                  |
| GL-CONT-004-SRC-005 | GL-CONT-000        | Entry schema, category model, governed_object and carrier_object categories, anti-collapse model        |
| GL-CONT-004-SRC-006 | GL-CONT-002        | Downstream boundary, downstream registry record non-ownership, post-handoff non-ownership               |
| GL-CONT-004-SRC-007 | GL-CONT-003        | Envelope Assembler produces Log Level Envelope; Dispatcher is actor; PolicyAssigner mediates assignment |

---

## 12. Validation Checklist

|           Record ID | Check                                                               | Expected Result |
| ------------------: | ------------------------------------------------------------------- | --------------- |
| GL-CONT-004-VAL-001 | Every object term has a Term ID                                     | Pass            |
| GL-CONT-004-VAL-002 | Every object term has family and category                           | Pass            |
| GL-CONT-004-VAL-003 | Every object term declares ownership scope                          | Pass            |
| GL-CONT-004-VAL-004 | Log Level Envelope is classified as carrier object                  | Pass            |
| GL-CONT-004-VAL-005 | Log Level Envelope is not classified as actor                       | Pass            |
| GL-CONT-004-VAL-006 | Log Envelope is treated as alias, not separate canonical object     | Pass            |
| GL-CONT-004-VAL-007 | Raw Payload / Raw Content cannot replace runtime transport unit     | Pass            |
| GL-CONT-004-VAL-008 | Policy Object is distinct from PolicyAssigner                       | Pass            |
| GL-CONT-004-VAL-009 | Policy Assignment is distinct from Policy Object                    | Pass            |
| GL-CONT-004-VAL-010 | Delivery-Cycle Flag Set is distinct from Dispatcher Feedback Report | Pass            |
| GL-CONT-004-VAL-011 | Handoff Evidence does not imply downstream lifecycle ownership      | Pass            |
| GL-CONT-004-VAL-012 | Downstream Registry Record is downstream/not-owned                  | Pass            |
| GL-CONT-004-VAL-013 | Envelope Metadata Block is distinct from Metadata Injector          | Pass            |
| GL-CONT-004-VAL-014 | Envelope Timestamp Block is distinct from Timestamp Stabilizer      | Pass            |
| GL-CONT-004-VAL-015 | Dispatch Eligibility State is distinct from Dispatcher              | Pass            |

---

## 13. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                                       | Status   |
| -------------------: | -------------------------------------------------------------------- | -------- |
| GL-CONT-004-EXIT-001 | Core governed object terms are defined                               | Complete |
| GL-CONT-004-EXIT-002 | Carrier object vocabulary is defined                                 | Complete |
| GL-CONT-004-EXIT-003 | Log Level Envelope is formally defined as central carrier            | Complete |
| GL-CONT-004-EXIT-004 | Log Envelope alias is mapped to Log Level Envelope                   | Complete |
| GL-CONT-004-EXIT-005 | Policy Object and Policy Assignment are separated                    | Complete |
| GL-CONT-004-EXIT-006 | Delivery-Cycle Flag Set and Dispatcher Feedback Report are separated | Complete |
| GL-CONT-004-EXIT-007 | Handoff Evidence is defined without downstream ownership leakage     | Complete |
| GL-CONT-004-EXIT-008 | Downstream Registry Record is explicitly downstream/not-owned        | Complete |
| GL-CONT-004-EXIT-009 | Raw Payload / Raw Content is excluded from runtime transport status  | Complete |
| GL-CONT-004-EXIT-010 | Pack is ready to support GL-CONT-005 runtime queue and slot terms    | Complete |

---

## 14. Summary

`GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack` establishes the canonical vocabulary for assembler-side governed objects and carriers.

The pack stabilizes the following object model:

```text id="gl-cont-004-summary-model"
Log Level Envelope
= authoritative assembler-side carrier object
= runtime transport unit
≠ actor
≠ raw content
≠ downstream registry record

Log Envelope
= legacy/source alias for Log Level Envelope

Governed Object
= object controlled by architecture rules

Carrier Object
= governed object that carries prepared content or state

Policy Object
= governance material
≠ PolicyAssigner
≠ policy-consuming component

Policy Assignment
= mediated association between policy material and eligible target

Delivery-Cycle Flag Set
= delivery-state artifact
≠ Dispatcher Feedback Report

Dispatcher Feedback Report
= report artifact
≠ Dispatcher

Handoff Evidence
= trace/evidence artifact
≠ downstream lifecycle ownership

Downstream Registry Record
= downstream-owned record
≠ assembler-owned envelope

Raw Payload / Raw Content
= pre-envelope material
≠ runtime transport unit
```

This pack enables the next glossary content pack:

```text id="gl-cont-004-next"
GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack
```
