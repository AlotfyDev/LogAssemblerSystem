# GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-005-DOC-001 | Pack Name | GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack |
| GL-CONT-005-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-005-DOC-003 | Project | Assembler System |
| GL-CONT-005-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-005-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-005-DOC-006 | Language | English |
| GL-CONT-005-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002, GL-CONT-003, GL-CONT-004 |
| GL-CONT-005-DOC-008 | Scope | Runtime queue terms, queue-container terms, slot terms, occupancy terms, waiting-list terms, round coordination terms |
| GL-CONT-005-DOC-009 | Excluded From This Pack | Final runtime algorithms, scheduling implementation, lock-free data structures, storage persistence, downstream delivery semantics, final C++ class layout |
| GL-CONT-005-DOC-010 | Enables | GL-CONT-006, GL-CONT-007, GL-CONT-008, GL-CONT-009, runtime-state contract derivation, queue/container implementation design |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for runtime, queue, slot, waiting-list, and round-coordination terminology inside the Assembler System.

It answers the question:

```text
How does the Assembler System name and govern its runtime coordination structures
without turning queues into message brokers, slots into lifecycle owners,
waiting lists into envelope stores, or round managers into dispatchers?
````

The pack exists to preserve runtime vocabulary before deriving implementation contracts, C++ abstractions, processing units, or queue/container package structure.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`,
4. `GL-CONT-003 — Internal Actors and Delegated Entities Pack`,
5. `GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack`.

It precedes:

1. `GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack`,
2. `GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack`,
3. `GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack`,
4. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`.

### 2.3 Pack-Level Runtime Rule

```text id="gl-cont-005-runtime-rule"
Runtime coordination structures organize assembler-side movement, placement,
readiness, and moderation.
They must not become downstream lifecycle owners, storage engines,
message brokers, or dispatcher replacements.
```

### 2.4 Pack-Level Queue Rule

```text id="gl-cont-005-queue-rule"
Queue = Container.
Queue ≠ Message Broker.
Queue Container owns slot structure, not downstream lifecycle.
```

### 2.5 Pack-Level Slot Rule

```text id="gl-cont-005-slot-rule"
Slot occupancy records or represents placement of a prepared carrier.
Slot occupancy must not be treated as envelope lifecycle ownership.
```

### 2.6 Pack-Level Waiting-List Rule

```text id="gl-cont-005-waiting-list-rule"
Waiting Lists carry Queue Container Identifiers where applicable.
They must not become generic envelope stores or message-payload queues.
```

---

## 3. Term Inventory

|           Record ID | Term ID    | Canonical Term                      | Family      | Category                            | Ownership Scope | Entry Maturity    |
| ------------------: | ---------- | ----------------------------------- | ----------- | ----------------------------------- | --------------- | ----------------- |
| GL-CONT-005-INV-001 | GL-RUN-001 | Queue Container                     | RUN         | runtime_state / container_structure | assembler_owned | canonical_full    |
| GL-CONT-005-INV-002 | GL-RUN-002 | Queue Bundle                        | RUN         | runtime_state / container_grouping  | assembler_owned | canonical_full    |
| GL-CONT-005-INV-003 | GL-RUN-003 | Single Queue Container              | RUN         | runtime_state / container_structure | assembler_owned | canonical_full    |
| GL-CONT-005-INV-004 | GL-RUN-004 | Pending / Waiting Queue Container   | RUN         | runtime_state / queue_state_variant | assembler_owned | canonical_partial |
| GL-CONT-005-INV-005 | GL-RUN-005 | Slot                                | RUN         | runtime_state / placement_structure | assembler_owned | canonical_full    |
| GL-CONT-005-INV-006 | GL-RUN-006 | Envelope Slot Occupancy             | RUN / OBJ   | runtime_state / occupancy_relation  | assembler_owned | canonical_full    |
| GL-CONT-005-INV-007 | GL-RUN-007 | Slot Lifecycle State                | RUN         | runtime_state / slot_state          | assembler_owned | canonical_partial |
| GL-CONT-005-INV-008 | GL-RUN-008 | Waiting List                        | RUN         | runtime_state / identifier_list     | assembler_owned | canonical_full    |
| GL-CONT-005-INV-009 | GL-RUN-009 | Writing Round Manager Waiting List  | RUN         | runtime_state / identifier_list     | assembler_owned | canonical_full    |
| GL-CONT-005-INV-010 | GL-RUN-010 | Delivery Round Manager Waiting List | RUN         | runtime_state / identifier_list     | assembler_owned | canonical_full    |
| GL-CONT-005-INV-011 | GL-RUN-011 | Queue Container Identifier          | RUN / TRC   | runtime_locator / identifier        | assembler_owned | canonical_full    |
| GL-CONT-005-INV-012 | GL-RUN-012 | Queue-as-Container Doctrine         | RUN / GUARD | doctrine / anti_collapse_guard      | governed        | canonical_full    |
| GL-CONT-005-INV-013 | GL-RUN-013 | Queue Runtime Layer                 | RUN         | runtime_layer                       | assembler_owned | canonical_full    |
| GL-CONT-005-INV-014 | GL-RUN-014 | Runtime Coordination                | RUN         | runtime_coordination                | assembler_owned | canonical_full    |
| GL-CONT-005-INV-015 | GL-RUN-015 | Runtime Placement                   | RUN         | runtime_operation                   | assembler_owned | canonical_partial |
| GL-CONT-005-INV-016 | GL-RUN-016 | Runtime Readiness                   | RUN         | runtime_state / readiness_state     | assembler_owned | canonical_partial |
| GL-CONT-005-INV-017 | GL-RUN-017 | Queue Moderation                    | RUN         | runtime_coordination                | assembler_owned | canonical_partial |
| GL-CONT-005-INV-018 | GL-RUN-018 | Round Coordination                  | RUN         | runtime_coordination                | assembler_owned | canonical_full    |
| GL-CONT-005-INV-019 | GL-RUN-019 | Writing / Feeding Round             | RUN         | runtime_round                       | assembler_owned | canonical_full    |
| GL-CONT-005-INV-020 | GL-RUN-020 | Dispatching / Delivery Round        | RUN         | runtime_round                       | assembler_owned | canonical_full    |

---

## 4. Canonical Term Entries

---

### GL-RUN-001 — Queue Container

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-RUN-001                          |
| Canonical Term  | Queue Container                     |
| Family          | RUN                                 |
| Category        | runtime_state / container_structure |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

A Queue Container is the assembler-side runtime container that holds slot structure for prepared `Log Level Envelopes` after ingress admission.

It is the queue itself in the Assembler System runtime model.

#### Architectural Role

Queue Container provides bounded runtime placement and coordination.

It owns or defines:

1. slot structure,
2. admissible occupancy relation,
3. queue-local placement semantics,
4. queue-local moderation context,
5. queue-container identifier,
6. runtime readiness participation.

A Queue Container does not own downstream lifecycle.

It does not act as a message broker.

It does not replace the Dispatcher.

#### Must Not Be Confused With

1. Message broker.
2. Downstream storage queue.
3. Transport layer.
4. Queue Bundle Agent.
5. Single Queue Moderator.
6. Log Level Envelope.
7. Downstream Registry Record.
8. Runtime lifecycle owner.

#### Valid Usage

* “Assembler Ingress Port admits the Log Level Envelope into a Slot inside a Queue Container.”
* “Queue Container is the runtime container.”
* “Queue Container owns slot structure, not downstream lifecycle.”

#### Invalid Usage

* “Queue Container is a message broker.”
* “Queue Container owns downstream record lifecycle.”
* “Queue Container dispatches directly to registry.”
* “Queue Container is the Log Level Envelope.”

#### Related Terms

* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-011 — Queue Container Identifier
* GL-RUN-012 — Queue-as-Container Doctrine
* GL-ENT-008 — Single Queue Moderator
* GL-OBJ-001 — Log Level Envelope

#### Source Trace

| Source Type        | Source                                                                                                                            |
| ------------------ | --------------------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Corrected ingress flow states that Assembler Ingress Port admits Log Level Envelope into a Slot in a Queue Container.             |
| SYSTEM_GOALS.md    | SG-QUEUE-001 and SG-QUEUE-003 define Queue as container and Queue Container as owner of slot structure, not downstream lifecycle. |
| VisionAndScope.md  | Current vision includes Queue-as-Container as a core runtime doctrine.                                                            |

---

### GL-RUN-002 — Queue Bundle

| Field           | Value                              |
| --------------- | ---------------------------------- |
| Term ID         | GL-RUN-002                         |
| Canonical Term  | Queue Bundle                       |
| Family          | RUN                                |
| Category        | runtime_state / container_grouping |
| Ownership Scope | assembler_owned                    |
| Entry Maturity  | canonical_full                     |
| Evidence Status | direct / derived                   |

#### Definition

A Queue Bundle is a runtime grouping of multiple Queue Containers governed together for bundle-level coordination.

#### Architectural Role

Queue Bundle supports coordination above individual queue-container moderation.

It provides a grouping context for `Queue Bundle Agent`.

It does not erase the identity of individual Queue Containers.

It does not become a message broker.

It does not become a downstream lifecycle manager.

#### Must Not Be Confused With

1. Queue Bundle Agent.
2. Single Queue Container.
3. Message broker topic.
4. Downstream storage partition.
5. Dispatcher.
6. Waiting List.
7. Queue Container Identifier.

#### Valid Usage

* “Queue Bundle groups multiple Queue Containers.”
* “Queue Bundle Agent coordinates queue-bundle-level behavior.”
* “Queue Bundle does not replace individual Queue Containers.”

#### Invalid Usage

* “Queue Bundle is the Queue Bundle Agent.”
* “Queue Bundle is a broker topic.”
* “Queue Bundle owns downstream record lifecycle.”
* “Queue Bundle performs final handoff.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-003 — Single Queue Container
* GL-ENT-007 — Queue Bundle Agent
* GL-RUN-008 — Waiting List
* GL-RUN-014 — Runtime Coordination

#### Source Trace

| Source Type        | Source                                                                                                   |
| ------------------ | -------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Queue Bundle Agent orchestrates queue bundles and waiting-list discipline.                               |
| SYSTEM_GOALS.md    | SG-QUEUE-006 requires Queue Bundle Agent and Single Queue Moderator responsibilities to remain distinct. |
| GL-CONT-003        | Queue Bundle Agent is an actor; Queue Bundle is not the actor.                                           |

---

### GL-RUN-003 — Single Queue Container

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-RUN-003                          |
| Canonical Term  | Single Queue Container              |
| Family          | RUN                                 |
| Category        | runtime_state / container_structure |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

A Single Queue Container is one individual Queue Container treated as a distinct runtime container for single-queue moderation.

#### Architectural Role

Single Queue Container defines the scope of `Single Queue Moderator`.

It preserves the distinction between:

1. one queue container,
2. a queue bundle,
3. a queue moderator,
4. queue-bundle-level coordination.

A Single Queue Container is still a container, not a broker or actor.

#### Must Not Be Confused With

1. Single Queue Moderator.
2. Queue Bundle.
3. Queue Bundle Agent.
4. Slot.
5. Envelope Slot Occupancy.
6. Message broker.
7. Downstream registry.

#### Valid Usage

* “Single Queue Moderator moderates one Single Queue Container.”
* “Single Queue Container contains slots.”
* “Single Queue Container remains distinct from Queue Bundle.”

#### Invalid Usage

* “Single Queue Container is the Single Queue Moderator.”
* “Single Queue Container is the message broker.”
* “Single Queue Container owns envelope lifecycle.”
* “Single Queue Container performs downstream handoff.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-002 — Queue Bundle
* GL-ENT-008 — Single Queue Moderator
* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy

#### Source Trace

| Source Type        | Source                                                                          |
| ------------------ | ------------------------------------------------------------------------------- |
| ProjectOverview.md | Single Queue Moderator moderates one queue-container.                           |
| SYSTEM_GOALS.md    | SG-QUEUE-006 preserves distinction between queue bundle and single-queue roles. |
| GL-CONT-003        | Single Queue Moderator is actor; Queue Container is runtime structure.          |

---

### GL-RUN-004 — Pending / Waiting Queue Container

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-RUN-004                          |
| Canonical Term  | Pending / Waiting Queue Container   |
| Family          | RUN                                 |
| Category        | runtime_state / queue_state_variant |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_partial                   |
| Evidence Status | derived / seed_low_detail           |

#### Definition

A Pending / Waiting Queue Container is a Queue Container currently identified as waiting, pending, inactive, blocked, not selected, or not yet eligible for a specific runtime round or moderation action.

#### Architectural Role

This term preserves a runtime-state distinction without introducing a new ownership model.

A Pending / Waiting Queue Container remains a Queue Container.

Its waiting status does not convert it into:

1. a waiting list,
2. a message payload,
3. a storage record,
4. a downstream lifecycle object.

#### Must Not Be Confused With

1. Waiting List.
2. Queue Container Identifier.
3. Slot Lifecycle State.
4. Envelope Slot Occupancy.
5. Downstream delivery backlog.
6. Message broker queue.

#### Valid Usage

* “A Pending / Waiting Queue Container may be referenced by a Waiting List.”
* “Waiting status is a runtime coordination state.”
* “Pending / Waiting Queue Container remains a Queue Container.”

#### Invalid Usage

* “Pending / Waiting Queue Container is the Waiting List itself.”
* “Pending status means downstream lifecycle ownership.”
* “Waiting queue contains generic broker messages.”
* “Pending / Waiting Queue Container stores registry records.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-008 — Waiting List
* GL-RUN-011 — Queue Container Identifier
* GL-RUN-016 — Runtime Readiness

#### Source Trace

| Source Type             | Source                                                                                |
| ----------------------- | ------------------------------------------------------------------------------------- |
| Glossary Planning Basis | GL-CONT-005 planning identifies Pending / Waiting Queue Container as a runtime term.  |
| SYSTEM_GOALS.md         | SG-QUEUE-005 states waiting lists carry queue-container identifiers where applicable. |

---

### GL-RUN-005 — Slot

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-RUN-005                          |
| Canonical Term  | Slot                                |
| Family          | RUN                                 |
| Category        | runtime_state / placement_structure |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

A Slot is a bounded placement position inside a Queue Container into which a prepared `Log Level Envelope` may be admitted.

#### Architectural Role

Slot provides the placement unit inside Queue Container runtime structure.

It supports:

1. envelope admission,
2. occupancy relation,
3. slot lifecycle state,
4. moderation,
5. runtime readiness coordination.

A Slot is not the envelope.

A Slot is not lifecycle ownership over the envelope.

A Slot is not downstream storage.

#### Must Not Be Confused With

1. Log Level Envelope.
2. Envelope Slot Occupancy.
3. Queue Container.
4. Downstream Registry Record.
5. Storage cell.
6. Message broker partition.
7. Dispatcher.

#### Valid Usage

* “Assembler Ingress Port admits a Log Level Envelope into a suitable Slot.”
* “Slot belongs to a Queue Container.”
* “Slot can have lifecycle state.”

#### Invalid Usage

* “Slot owns the envelope lifecycle.”
* “Slot is the Log Level Envelope.”
* “Slot is the downstream registry record.”
* “Slot dispatches the envelope.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-007 — Slot Lifecycle State
* GL-OBJ-001 — Log Level Envelope
* GL-BND-006 — Assembler Ingress Port

#### Source Trace

| Source Type        | Source                                                                                           |
| ------------------ | ------------------------------------------------------------------------------------------------ |
| ProjectOverview.md | Corrected ingress flow places Log Level Envelope into a suitable Slot in target Queue Container. |
| VisionAndScope.md  | Corrected ingress scope identifies Queue Container Slot as target runtime admission position.    |
| SYSTEM_GOALS.md    | SG-ING-005 requires Assembler Ingress Port to admit envelopes into suitable slots.               |

---

### GL-RUN-006 — Envelope Slot Occupancy

| Field           | Value                              |
| --------------- | ---------------------------------- |
| Term ID         | GL-RUN-006                         |
| Canonical Term  | Envelope Slot Occupancy            |
| Family          | RUN / OBJ                          |
| Category        | runtime_state / occupancy_relation |
| Ownership Scope | assembler_owned                    |
| Entry Maturity  | canonical_full                     |
| Evidence Status | direct / derived                   |

#### Definition

Envelope Slot Occupancy is the runtime relation or state indicating that a `Log Level Envelope` occupies a specific Slot inside a Queue Container.

#### Architectural Role

Envelope Slot Occupancy records or represents placement.

It preserves the relation:

```text id="gl-run-006-occupancy-relation"
Log Level Envelope
  occupies:
    Slot
      inside:
        Queue Container
```

Envelope Slot Occupancy is not envelope lifecycle ownership.

It is not downstream lifecycle ownership.

It is not a downstream registry record.

#### Must Not Be Confused With

1. Envelope lifecycle ownership.
2. Downstream Registry Record.
3. Slot itself.
4. Log Level Envelope itself.
5. Queue Container ownership.
6. Handoff Evidence.

#### Valid Usage

* “Envelope Slot Occupancy records the envelope-slot placement relation.”
* “Slot occupancy is distinct from envelope lifecycle ownership.”
* “Single Queue Moderator must preserve occupancy/lifecycle distinction.”

#### Invalid Usage

* “Envelope Slot Occupancy owns the envelope lifecycle.”
* “Envelope Slot Occupancy is the downstream registry record.”
* “Envelope Slot Occupancy means the envelope has been delivered.”
* “Envelope Slot Occupancy replaces handoff evidence.”

#### Related Terms

* GL-RUN-005 — Slot
* GL-RUN-001 — Queue Container
* GL-OBJ-001 — Log Level Envelope
* GL-ENT-008 — Single Queue Moderator
* GL-OBJ-008 — Handoff Evidence

#### Source Trace

| Source Type     | Source                                                                                 |
| --------------- | -------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-QUEUE-004 states slot occupancy remains distinct from envelope lifecycle ownership. |
| GL-CONT-003     | Single Queue Moderator must preserve slot occupancy and lifecycle distinction.         |
| GL-CONT-004     | Log Level Envelope is carrier object and must not own downstream lifecycle.            |

---

### GL-RUN-007 — Slot Lifecycle State

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-RUN-007                 |
| Canonical Term  | Slot Lifecycle State       |
| Family          | RUN                        |
| Category        | runtime_state / slot_state |
| Ownership Scope | assembler_owned            |
| Entry Maturity  | canonical_partial          |
| Evidence Status | derived / seed_low_detail  |

#### Definition

Slot Lifecycle State is the assembler-side runtime state of a Slot within a Queue Container.

It may describe whether the Slot is available, occupied, reserved, blocked, released, or otherwise eligible for runtime coordination.

#### Architectural Role

Slot Lifecycle State governs slot availability and placement behavior.

It does not govern downstream lifecycle of the Log Level Envelope.

It belongs to queue/container runtime coordination.

#### Must Not Be Confused With

1. Envelope lifecycle.
2. Downstream registry lifecycle.
3. Dispatch eligibility state by default.
4. Delivery-cycle flag set by default.
5. Handoff Evidence.
6. Queue Container Identifier.

#### Valid Usage

* “Slot Lifecycle State can indicate whether a Slot is available.”
* “Slot Lifecycle State belongs to queue runtime semantics.”
* “Slot state does not equal envelope lifecycle state.”

#### Invalid Usage

* “Slot Lifecycle State owns envelope lifecycle.”
* “Slot Lifecycle State is downstream delivery state.”
* “Slot Lifecycle State is a registry persistence state.”
* “Slot Lifecycle State replaces dispatch eligibility.”

#### Related Terms

* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-016 — Runtime Readiness
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type             | Source                                                                                                                     |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Glossary Planning Basis | GL-CONT-005 planning identifies Slot Lifecycle State as a runtime term.                                                    |
| SYSTEM_GOALS.md         | SG-QUEUE-003 and SG-QUEUE-004 distinguish slot/occupancy model from downstream lifecycle and envelope lifecycle ownership. |

---

### GL-RUN-008 — Waiting List

| Field           | Value                           |
| --------------- | ------------------------------- |
| Term ID         | GL-RUN-008                      |
| Canonical Term  | Waiting List                    |
| Family          | RUN                             |
| Category        | runtime_state / identifier_list |
| Ownership Scope | assembler_owned                 |
| Entry Maturity  | canonical_full                  |
| Evidence Status | direct / derived                |

#### Definition

A Waiting List is an assembler-side runtime list used to preserve or order Queue Container Identifiers awaiting a runtime coordination action.

#### Architectural Role

Waiting List is an identifier-oriented coordination structure.

It may support:

1. writing/feed-domain progression,
2. dispatch/delivery-domain progression,
3. queue selection,
4. queue activation,
5. runtime readiness evaluation.

A Waiting List should carry Queue Container Identifiers where applicable.

It is not an envelope store.

It is not a message queue.

It is not a broker.

#### Must Not Be Confused With

1. Queue Container.
2. Queue Container Identifier.
3. Log Level Envelope store.
4. Message broker queue.
5. Downstream delivery backlog.
6. Registry lifecycle list.

#### Valid Usage

* “Waiting List stores Queue Container Identifiers where applicable.”
* “Round managers may use waiting lists for runtime coordination.”
* “Waiting List is not generic message payload ownership.”

#### Invalid Usage

* “Waiting List stores raw payloads.”
* “Waiting List owns envelopes.”
* “Waiting List is the Queue Container.”
* “Waiting List is a downstream delivery backlog.”

#### Related Terms

* GL-RUN-009 — Writing Round Manager Waiting List
* GL-RUN-010 — Delivery Round Manager Waiting List
* GL-RUN-011 — Queue Container Identifier
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager

#### Source Trace

| Source Type        | Source                                                                                                                       |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-QUEUE-005 states waiting lists carry queue-container identifiers where applicable, not generic message payload ownership. |
| ProjectOverview.md | Queue Bundle Agent orchestrates queue bundles and waiting-list discipline.                                                   |
| GL-CONT-003        | Round managers interact with queue-container identifiers and waiting-list state.                                             |

---

### GL-RUN-009 — Writing Round Manager Waiting List

| Field           | Value                              |
| --------------- | ---------------------------------- |
| Term ID         | GL-RUN-009                         |
| Canonical Term  | Writing Round Manager Waiting List |
| Family          | RUN                                |
| Category        | runtime_state / identifier_list    |
| Ownership Scope | assembler_owned                    |
| Entry Maturity  | canonical_full                     |
| Evidence Status | direct / derived                   |

#### Definition

Writing Round Manager Waiting List is the waiting-list structure associated with writing/feed-domain round progression.

It carries Queue Container Identifiers where applicable for queues awaiting writing or feeding coordination.

#### Architectural Role

This waiting list supports `Writing / Feeding Round Manager`.

It is a coordination aid, not a payload store.

It preserves the writing/feed-domain side of round coordination.

It must remain distinct from delivery-round waiting-list semantics.

#### Must Not Be Confused With

1. Delivery Round Manager Waiting List.
2. Writing / Feeding Round Manager actor.
3. Queue Container itself.
4. Envelope store.
5. Raw payload list.
6. Message broker backlog.

#### Valid Usage

* “Writing Round Manager Waiting List supports feed-domain round progression.”
* “It should carry Queue Container Identifiers where applicable.”
* “It is distinct from the Delivery Round Manager Waiting List.”

#### Invalid Usage

* “Writing Round Manager Waiting List stores envelopes as messages.”
* “Writing Round Manager Waiting List performs delivery handoff.”
* “Writing Round Manager Waiting List is the round manager actor.”
* “Writing Round Manager Waiting List replaces Queue Container.”

#### Related Terms

* GL-ENT-009 — Writing / Feeding Round Manager
* GL-RUN-008 — Waiting List
* GL-RUN-010 — Delivery Round Manager Waiting List
* GL-RUN-011 — Queue Container Identifier
* GL-RUN-019 — Writing / Feeding Round

#### Source Trace

| Source Type        | Source                                                                                                                        |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Writing / Feeding Round Manager manages writing/feed-domain round progression and interacts with queue-container identifiers. |
| SYSTEM_GOALS.md    | SG-QUEUE-005 and SG-QUEUE-007 govern waiting-list locator semantics and round-manager separation.                             |
| GL-CONT-003        | Writing / Feeding Round Manager is a runtime actor, not the waiting list itself.                                              |

---

### GL-RUN-010 — Delivery Round Manager Waiting List

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-RUN-010                          |
| Canonical Term  | Delivery Round Manager Waiting List |
| Family          | RUN                                 |
| Category        | runtime_state / identifier_list     |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct / derived                    |

#### Definition

Delivery Round Manager Waiting List is the waiting-list structure associated with dispatch/delivery-domain round progression.

It carries Queue Container Identifiers where applicable for queues awaiting delivery-side coordination or dispatch-readiness progression.

#### Architectural Role

This waiting list supports `Dispatching / Delivery Round Manager`.

It contributes to dispatch/delivery-domain coordination before final Dispatcher handoff.

It does not perform final handoff.

It does not replace Dispatcher.

It does not own downstream lifecycle.

#### Must Not Be Confused With

1. Writing Round Manager Waiting List.
2. Dispatching / Delivery Round Manager actor.
3. Dispatcher.
4. Registry / Delivery Port.
5. Handoff Evidence.
6. Downstream delivery backlog.

#### Valid Usage

* “Delivery Round Manager Waiting List supports delivery-domain progression.”
* “It references Queue Container Identifiers where applicable.”
* “Dispatcher remains the final outbound actor.”

#### Invalid Usage

* “Delivery Round Manager Waiting List performs final handoff.”
* “Delivery Round Manager Waiting List owns downstream delivery lifecycle.”
* “Delivery Round Manager Waiting List replaces Dispatcher.”
* “Delivery Round Manager Waiting List stores downstream records.”

#### Related Terms

* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-002 — Dispatcher
* GL-RUN-008 — Waiting List
* GL-RUN-009 — Writing Round Manager Waiting List
* GL-RUN-011 — Queue Container Identifier
* GL-RUN-020 — Dispatching / Delivery Round

#### Source Trace

| Source Type        | Source                                                                                                              |
| ------------------ | ------------------------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Dispatching / Delivery Round Manager manages dispatch/delivery-domain round progression.                            |
| SYSTEM_GOALS.md    | SG-QUEUE-007 preserves separation between Writing / Feeding Round Manager and Dispatching / Delivery Round Manager. |
| GL-CONT-003        | Dispatching / Delivery Round Manager is not the final outbound actor; Dispatcher remains final.                     |

---

### GL-RUN-011 — Queue Container Identifier

| Field           | Value                        |
| --------------- | ---------------------------- |
| Term ID         | GL-RUN-011                   |
| Canonical Term  | Queue Container Identifier   |
| Family          | RUN / TRC                    |
| Category        | runtime_locator / identifier |
| Ownership Scope | assembler_owned              |
| Entry Maturity  | canonical_full               |
| Evidence Status | direct / derived             |

#### Definition

Queue Container Identifier is the canonical runtime locator or identifier used to reference a Queue Container in runtime coordination structures such as waiting lists, round managers, or moderation flows.

#### Architectural Role

Queue Container Identifier preserves locator semantics.

It allows waiting lists and round managers to coordinate queue containers without becoming stores of envelopes, raw payloads, or downstream records.

It is not the Queue Container itself.

It is not an envelope identity.

It is not downstream registry identity by default.

#### Must Not Be Confused With

1. Queue Container itself.
2. Envelope Identity.
3. Downstream Registry Record identity.
4. Slot.
5. Envelope Slot Occupancy.
6. Handoff Evidence.

#### Valid Usage

* “Waiting Lists carry Queue Container Identifiers where applicable.”
* “Queue Container Identifier locates a Queue Container.”
* “Queue Container Identifier is distinct from Envelope Identity.”

#### Invalid Usage

* “Queue Container Identifier is the Log Level Envelope ID.”
* “Queue Container Identifier is a downstream registry primary key.”
* “Queue Container Identifier owns the queue lifecycle.”
* “Queue Container Identifier stores payload content.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-008 — Waiting List
* GL-OBJ-012 — Envelope Identity
* GL-RUN-009 — Writing Round Manager Waiting List
* GL-RUN-010 — Delivery Round Manager Waiting List

#### Source Trace

| Source Type     | Source                                                                                |
| --------------- | ------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-QUEUE-005 states waiting lists carry queue-container identifiers where applicable. |
| GL-CONT-004     | Envelope Identity is distinct from Queue Container Identifier.                        |
| GL-CONT-003     | Round managers interact with queue-container identifiers and waiting-list state.      |

---

### GL-RUN-012 — Queue-as-Container Doctrine

| Field           | Value                            |
| --------------- | -------------------------------- |
| Term ID         | GL-RUN-012                       |
| Canonical Term  | Queue-as-Container Doctrine      |
| Family          | RUN / GUARD                      |
| Category        | doctrine / anti_collapse_guard   |
| Ownership Scope | governed                         |
| Entry Maturity  | canonical_full                   |
| Evidence Status | direct / user_decision / derived |

#### Definition

Queue-as-Container Doctrine is the governing architectural rule that a queue in the Assembler System must be modeled as a container, not as a message broker, transport layer, storage engine, or downstream lifecycle manager.

#### Architectural Role

This doctrine governs all queue/runtime terms.

It prevents category collapse between:

1. Queue Container and message broker,
2. queue slot and storage record,
3. waiting list and envelope store,
4. runtime coordination and downstream lifecycle,
5. queue moderation and dispatch finality.

#### Must Not Be Confused With

1. Broker architecture.
2. Messaging platform doctrine.
3. Storage persistence doctrine.
4. Downstream registry doctrine.
5. Transport protocol design.
6. Final implementation algorithm.

#### Valid Usage

* “Queue-as-Container Doctrine governs runtime queue design.”
* “Queue = Container.”
* “Queue must not become a message broker.”

#### Invalid Usage

* “Queue-as-Container Doctrine means broker semantics.”
* “Queue-as-Container Doctrine grants downstream lifecycle ownership.”
* “Queue-as-Container Doctrine defines final C++ lock strategy.”
* “Queue-as-Container Doctrine replaces Dispatcher finality.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-008 — Waiting List
* GL-RUN-013 — Queue Runtime Layer

#### Source Trace

| Source Type             | Source                                                                                                      |
| ----------------------- | ----------------------------------------------------------------------------------------------------------- |
| VisionAndScope.md       | Current vision includes Queue-as-Container and explicitly prevents generic messaging-system interpretation. |
| SYSTEM_GOALS.md         | SG-QUEUE-001 and SG-QUEUE-002 require queue as container and prohibit message broker interpretation.        |
| Glossary Planning Basis | GL-CONT-005 planning defines Queue = Container and Queue ≠ Message Broker as governing rules.               |

---

### GL-RUN-013 — Queue Runtime Layer

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-RUN-013          |
| Canonical Term  | Queue Runtime Layer |
| Family          | RUN                 |
| Category        | runtime_layer       |
| Ownership Scope | assembler_owned     |
| Entry Maturity  | canonical_full      |
| Evidence Status | direct / derived    |

#### Definition

Queue Runtime Layer is the assembler-side runtime layer responsible for queue/container coordination, slot placement, occupancy, waiting-list discipline, moderation, and round coordination.

#### Architectural Role

Queue Runtime Layer sits between envelope admission and dispatcher-side handoff progression.

It coordinates runtime state without becoming:

1. message broker,
2. transport layer,
3. downstream storage,
4. downstream registry,
5. final dispatcher,
6. query lifecycle owner.

#### Must Not Be Confused With

1. Dispatch Layer.
2. Downstream Boundary Layer.
3. Storage layer.
4. Message broker layer.
5. Network transport layer.
6. Final C++ package by default.

#### Valid Usage

* “Queue Runtime Layer coordinates Queue Containers, Slots, and Waiting Lists.”
* “Queue Runtime Layer preserves queue-as-container semantics.”
* “Queue Runtime Layer precedes final dispatcher-mediated handoff.”

#### Invalid Usage

* “Queue Runtime Layer owns downstream registry lifecycle.”
* “Queue Runtime Layer is the messaging system.”
* “Queue Runtime Layer replaces Dispatcher.”
* “Queue Runtime Layer is automatically a final package name.”

#### Related Terms

* GL-RUN-001 — Queue Container
* GL-RUN-012 — Queue-as-Container Doctrine
* GL-RUN-014 — Runtime Coordination
* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator

#### Source Trace

| Source Type        | Source                                                                                              |
| ------------------ | --------------------------------------------------------------------------------------------------- |
| README Basis       | Recommended architectural layers include Runtime Queue Container Layer.                             |
| ProjectOverview.md | Runtime coordination model includes Queue Bundle Agent, Single Queue Moderator, and round managers. |
| SYSTEM_GOALS.md    | Queue runtime goals preserve queue-as-container runtime coordination.                               |

---

### GL-RUN-014 — Runtime Coordination

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-RUN-014           |
| Canonical Term  | Runtime Coordination |
| Family          | RUN                  |
| Category        | runtime_coordination |
| Ownership Scope | assembler_owned      |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

Runtime Coordination is assembler-side coordination of queue containers, slots, occupancy, waiting lists, moderators, agents, round managers, and readiness progression before final dispatcher-mediated handoff.

#### Architectural Role

Runtime Coordination organizes the movement and readiness of prepared carriers inside the Assembler boundary.

It coordinates but does not own downstream lifecycle.

It may be carried by actors such as:

1. Queue Bundle Agent,
2. Single Queue Moderator,
3. Writing / Feeding Round Manager,
4. Dispatching / Delivery Round Manager.

Runtime Coordination does not replace Dispatcher finality.

#### Must Not Be Confused With

1. Downstream lifecycle management.
2. Message brokering.
3. Storage persistence.
4. Dispatcher handoff itself.
5. Query lifecycle.
6. Transport-layer delivery.

#### Valid Usage

* “Runtime Coordination happens after envelope admission.”
* “Runtime Coordination involves queue-container and round-manager discipline.”
* “Runtime Coordination does not own downstream records.”

#### Invalid Usage

* “Runtime Coordination is downstream delivery ownership.”
* “Runtime Coordination is a message broker.”
* “Runtime Coordination bypasses Dispatcher.”
* “Runtime Coordination performs query interpretation.”

#### Related Terms

* GL-RUN-013 — Queue Runtime Layer
* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type        | Source                                                                                               |
| ------------------ | ---------------------------------------------------------------------------------------------------- |
| ProjectOverview.md | System position includes Queue-as-Container Runtime Coordination before Dispatcher-Mediated Handoff. |
| VisionAndScope.md  | Owned architectural concerns include Queue-as-Container Coordination.                                |
| SYSTEM_GOALS.md    | Queue runtime goals define runtime coordination boundaries.                                          |

---

### GL-RUN-015 — Runtime Placement

| Field           | Value             |
| --------------- | ----------------- |
| Term ID         | GL-RUN-015        |
| Canonical Term  | Runtime Placement |
| Family          | RUN               |
| Category        | runtime_operation |
| Ownership Scope | assembler_owned   |
| Entry Maturity  | canonical_partial |
| Evidence Status | derived           |

#### Definition

Runtime Placement is the assembler-side act or state transition by which a prepared Log Level Envelope is placed into a suitable Slot inside a Queue Container.

#### Architectural Role

Runtime Placement occurs after envelope assembly and before later runtime readiness or delivery progression.

It is associated with Assembler Ingress Port admission and Queue Container slot structure.

Runtime Placement is not downstream delivery.

It is not persistence.

It is not final handoff.

#### Must Not Be Confused With

1. Envelope assembly.
2. Downstream registry admission.
3. Dispatcher-mediated handoff.
4. Envelope lifecycle ownership.
5. Storage persistence.
6. Message brokering.

#### Valid Usage

* “Runtime Placement admits a prepared envelope into a Slot.”
* “Runtime Placement occurs inside Queue Container semantics.”
* “Runtime Placement is not downstream delivery.”

#### Invalid Usage

* “Runtime Placement means the envelope has been delivered.”
* “Runtime Placement owns downstream lifecycle.”
* “Runtime Placement stores the record in the registry.”
* “Runtime Placement replaces Dispatcher.”

#### Related Terms

* GL-BND-006 — Assembler Ingress Port
* GL-RUN-005 — Slot
* GL-RUN-006 — Envelope Slot Occupancy
* GL-RUN-001 — Queue Container
* GL-OBJ-001 — Log Level Envelope

#### Source Trace

| Source Type        | Source                                                                                 |
| ------------------ | -------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md    | SG-ING-005 requires envelope admission into suitable slots in target Queue Containers. |
| ProjectOverview.md | Corrected ingress flow defines the envelope admission path.                            |

---

### GL-RUN-016 — Runtime Readiness

| Field           | Value                           |
| --------------- | ------------------------------- |
| Term ID         | GL-RUN-016                      |
| Canonical Term  | Runtime Readiness               |
| Family          | RUN                             |
| Category        | runtime_state / readiness_state |
| Ownership Scope | assembler_owned                 |
| Entry Maturity  | canonical_partial               |
| Evidence Status | derived                         |

#### Definition

Runtime Readiness is the assembler-side runtime condition indicating whether a queue, slot, envelope placement, or coordination path is ready for a next runtime action.

#### Architectural Role

Runtime Readiness contributes to progression toward dispatch eligibility but is not identical to final handoff eligibility unless a later contract explicitly defines that mapping.

It may be evaluated by moderators, queue agents, or round managers.

It does not replace Dispatcher verification or reliance on handoff eligibility.

#### Must Not Be Confused With

1. Dispatch Eligibility State by default.
2. Handoff Evidence.
3. Downstream registry admission.
4. Storage readiness.
5. Query readiness.
6. Lifecycle transfer.

#### Valid Usage

* “Runtime Readiness may contribute to dispatch progression.”
* “Runtime Readiness belongs to assembler-side runtime coordination.”
* “Runtime Readiness is not automatically downstream handoff eligibility.”

#### Invalid Usage

* “Runtime Readiness is the same as downstream delivery success.”
* “Runtime Readiness bypasses Dispatcher.”
* “Runtime Readiness owns downstream lifecycle.”
* “Runtime Readiness is query execution readiness.”

#### Related Terms

* GL-OBJ-015 — Dispatch Eligibility State
* GL-RUN-014 — Runtime Coordination
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type     | Source                                                                                             |
| --------------- | -------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | SG-DISP-003 requires Dispatcher to verify or rely on handoff eligibility before outbound transfer. |
| GL-CONT-004     | Dispatch Eligibility State is a governed readiness state distinct from Dispatcher.                 |
| GL-CONT-003     | Delivery Round Manager prepares or coordinates toward dispatch readiness.                          |

---

### GL-RUN-017 — Queue Moderation

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-RUN-017           |
| Canonical Term  | Queue Moderation     |
| Family          | RUN                  |
| Category        | runtime_coordination |
| Ownership Scope | assembler_owned      |
| Entry Maturity  | canonical_partial    |
| Evidence Status | derived              |

#### Definition

Queue Moderation is the runtime coordination activity that manages or supervises one or more Queue Containers according to assembler-side queue/container rules.

#### Architectural Role

Queue Moderation may occur at:

1. bundle level through Queue Bundle Agent,
2. single-queue level through Single Queue Moderator.

Queue Moderation preserves queue-container discipline, occupancy distinction, readiness progression, and waiting-list rules.

It does not dispatch directly to downstream destinations.

#### Must Not Be Confused With

1. Queue Container itself.
2. Queue Bundle itself.
3. Dispatcher.
4. Message broker behavior.
5. Downstream lifecycle management.
6. Storage scheduling.

#### Valid Usage

* “Single Queue Moderator performs queue moderation for one Queue Container.”
* “Queue Bundle Agent coordinates bundle-level queue moderation.”
* “Queue Moderation preserves slot occupancy boundaries.”

#### Invalid Usage

* “Queue Moderation is the Queue Container.”
* “Queue Moderation performs downstream registry handoff.”
* “Queue Moderation is message brokering.”
* “Queue Moderation owns envelope lifecycle.”

#### Related Terms

* GL-ENT-007 — Queue Bundle Agent
* GL-ENT-008 — Single Queue Moderator
* GL-RUN-001 — Queue Container
* GL-RUN-002 — Queue Bundle
* GL-RUN-006 — Envelope Slot Occupancy

#### Source Trace

| Source Type     | Source                                                                                                     |
| --------------- | ---------------------------------------------------------------------------------------------------------- |
| GL-CONT-003     | Queue Bundle Agent and Single Queue Moderator are runtime coordination actors.                             |
| SYSTEM_GOALS.md | SG-QUEUE-006 preserves distinction between Queue Bundle Agent and Single Queue Moderator responsibilities. |

---

### GL-RUN-018 — Round Coordination

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-RUN-018           |
| Canonical Term  | Round Coordination   |
| Family          | RUN                  |
| Category        | runtime_coordination |
| Ownership Scope | assembler_owned      |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

Round Coordination is assembler-side coordination of runtime progression through writing/feed-domain rounds or dispatch/delivery-domain rounds.

#### Architectural Role

Round Coordination preserves separation between:

1. writing/feed-domain progression,
2. dispatch/delivery-domain progression,
3. final dispatcher-mediated handoff.

Round Coordination is carried by round managers.

It is not the same as the final Dispatcher actor.

It does not own downstream lifecycle.

#### Must Not Be Confused With

1. Dispatcher.
2. Handoff.
3. Registry delivery.
4. Queue Container itself.
5. Waiting List itself.
6. Message broker scheduling.

#### Valid Usage

* “Round Coordination is performed by round managers.”
* “Writing / Feeding Round and Dispatching / Delivery Round are distinct.”
* “Round Coordination may move envelopes toward dispatch readiness.”

#### Invalid Usage

* “Round Coordination replaces Dispatcher.”
* “Round Coordination owns downstream records.”
* “Round Coordination is message broker scheduling.”
* “Round Coordination means final handoff is complete.”

#### Related Terms

* GL-RUN-019 — Writing / Feeding Round
* GL-RUN-020 — Dispatching / Delivery Round
* GL-ENT-009 — Writing / Feeding Round Manager
* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type        | Source                                                                                    |
| ------------------ | ----------------------------------------------------------------------------------------- |
| ProjectOverview.md | Round managers manage writing/feed-domain and dispatch/delivery-domain round progression. |
| SYSTEM_GOALS.md    | SG-QUEUE-007 requires the two round-manager roles to remain distinct.                     |
| GL-CONT-003        | Round managers are internal runtime coordination actors.                                  |

---

### GL-RUN-019 — Writing / Feeding Round

| Field           | Value                   |
| --------------- | ----------------------- |
| Term ID         | GL-RUN-019              |
| Canonical Term  | Writing / Feeding Round |
| Family          | RUN                     |
| Category        | runtime_round           |
| Ownership Scope | assembler_owned         |
| Entry Maturity  | canonical_full          |
| Evidence Status | direct / derived        |

#### Definition

Writing / Feeding Round is a runtime round domain concerned with writing-side or feed-side progression of Queue Containers or related runtime coordination state.

#### Architectural Role

Writing / Feeding Round belongs to the earlier runtime progression side.

It may involve waiting-list discipline, queue-container identifiers, and readiness movement before delivery-side progression.

It is not final dispatch.

It is not downstream delivery.

#### Must Not Be Confused With

1. Dispatching / Delivery Round.
2. Dispatcher.
3. Final handoff.
4. Downstream registry admission.
5. Queue Container itself.
6. Writing Round Manager Waiting List.

#### Valid Usage

* “Writing / Feeding Round is coordinated by Writing / Feeding Round Manager.”
* “Writing / Feeding Round is distinct from Dispatching / Delivery Round.”
* “Writing / Feeding Round may use queue-container identifiers.”

#### Invalid Usage

* “Writing / Feeding Round performs final outbound handoff.”
* “Writing / Feeding Round owns downstream delivery lifecycle.”
* “Writing / Feeding Round is the Dispatcher.”
* “Writing / Feeding Round is a message broker delivery cycle.”

#### Related Terms

* GL-ENT-009 — Writing / Feeding Round Manager
* GL-RUN-009 — Writing Round Manager Waiting List
* GL-RUN-020 — Dispatching / Delivery Round
* GL-RUN-011 — Queue Container Identifier

#### Source Trace

| Source Type        | Source                                                                              |
| ------------------ | ----------------------------------------------------------------------------------- |
| ProjectOverview.md | Writing / Feeding Round Manager manages writing/feed-domain round progression.      |
| SYSTEM_GOALS.md    | SG-QUEUE-007 distinguishes writing/feeding and dispatching/delivery round managers. |

---

### GL-RUN-020 — Dispatching / Delivery Round

| Field           | Value                        |
| --------------- | ---------------------------- |
| Term ID         | GL-RUN-020                   |
| Canonical Term  | Dispatching / Delivery Round |
| Family          | RUN                          |
| Category        | runtime_round                |
| Ownership Scope | assembler_owned              |
| Entry Maturity  | canonical_full               |
| Evidence Status | direct / derived             |

#### Definition

Dispatching / Delivery Round is a runtime round domain concerned with dispatch-side or delivery-side progression before final dispatcher-mediated handoff.

#### Architectural Role

Dispatching / Delivery Round may coordinate prepared envelopes or queue-container readiness toward dispatch eligibility.

It belongs to runtime progression before final outbound authority closure.

It is not the Dispatcher.

It is not the Registry / Delivery Port.

It is not downstream lifecycle ownership.

#### Must Not Be Confused With

1. Dispatcher.
2. Registry / Delivery Port.
3. Downstream registry delivery.
4. Writing / Feeding Round.
5. Delivery Round Manager Waiting List.
6. Handoff Evidence.

#### Valid Usage

* “Dispatching / Delivery Round is coordinated by Dispatching / Delivery Round Manager.”
* “Dispatching / Delivery Round may move runtime state toward dispatch readiness.”
* “Dispatcher remains the final outbound actor.”

#### Invalid Usage

* “Dispatching / Delivery Round performs final handoff by itself.”
* “Dispatching / Delivery Round owns downstream registry lifecycle.”
* “Dispatching / Delivery Round is the Registry / Delivery Port.”
* “Dispatching / Delivery Round is the downstream delivery subsystem.”

#### Related Terms

* GL-ENT-010 — Dispatching / Delivery Round Manager
* GL-RUN-010 — Delivery Round Manager Waiting List
* GL-RUN-019 — Writing / Feeding Round
* GL-OBJ-015 — Dispatch Eligibility State
* GL-ENT-002 — Dispatcher

#### Source Trace

| Source Type        | Source                                                                                        |
| ------------------ | --------------------------------------------------------------------------------------------- |
| ProjectOverview.md | Dispatching / Delivery Round Manager manages dispatch/delivery-domain round progression.      |
| SYSTEM_GOALS.md    | SG-QUEUE-007 preserves round-domain separation and SG-DISP-001 preserves Dispatcher finality. |
| GL-CONT-003        | Dispatching / Delivery Round Manager is not the final outbound actor.                         |

---

## 5. Runtime Classification Matrix

|           Record ID | Term                                | Runtime Structure? | Actor? |                   Stores Envelopes? |   Stores Identifiers? | Owns Downstream Lifecycle? | Notes                                          |
| ------------------: | ----------------------------------- | -----------------: | -----: | ----------------------------------: | --------------------: | -------------------------: | ---------------------------------------------- |
| GL-CONT-005-RCM-001 | Queue Container                     |                Yes |     No | Contains slots that may be occupied |        Has identifier |                         No | Queue = container                              |
| GL-CONT-005-RCM-002 | Queue Bundle                        |                Yes |     No |        Indirectly groups containers | May group identifiers |                         No | Grouping, not actor                            |
| GL-CONT-005-RCM-003 | Single Queue Container              |                Yes |     No |                      Contains slots |        Has identifier |                         No | Moderated by Single Queue Moderator            |
| GL-CONT-005-RCM-004 | Pending / Waiting Queue Container   |                Yes |     No |             Same as Queue Container |     May be referenced |                         No | Runtime state variant                          |
| GL-CONT-005-RCM-005 | Slot                                |                Yes |     No |                  Placement position |                    No |                         No | Belongs to Queue Container                     |
| GL-CONT-005-RCM-006 | Envelope Slot Occupancy             |                Yes |     No |       Represents placement relation |                    No |                         No | Not lifecycle ownership                        |
| GL-CONT-005-RCM-007 | Slot Lifecycle State                |                Yes |     No |                                  No |                    No |                         No | Slot state, not envelope lifecycle             |
| GL-CONT-005-RCM-008 | Waiting List                        |                Yes |     No |                      No by doctrine |                   Yes |                         No | Identifier-oriented list                       |
| GL-CONT-005-RCM-009 | Writing Round Manager Waiting List  |                Yes |     No |                      No by doctrine |                   Yes |                         No | Feed-domain coordination                       |
| GL-CONT-005-RCM-010 | Delivery Round Manager Waiting List |                Yes |     No |                      No by doctrine |                   Yes |                         No | Delivery-domain coordination before Dispatcher |
| GL-CONT-005-RCM-011 | Queue Container Identifier          |            Locator |     No |                                  No |      It is identifier |                         No | Distinct from Envelope Identity                |
| GL-CONT-005-RCM-012 | Queue-as-Container Doctrine         |           Doctrine |     No |                                  No |                    No |                         No | Governing anti-collapse rule                   |
| GL-CONT-005-RCM-013 | Queue Runtime Layer                 |              Layer |     No | Conditional by contained structures |           Conditional |                         No | Coordination layer                             |
| GL-CONT-005-RCM-014 | Runtime Coordination                |           Activity |     No |                        No by itself |           Conditional |                         No | Carried by actors                              |
| GL-CONT-005-RCM-015 | Runtime Placement                   |          Operation |     No |            Places prepared envelope |                    No |                         No | Not final handoff                              |
| GL-CONT-005-RCM-016 | Runtime Readiness                   |              State |     No |                                  No |                    No |                         No | May contribute to dispatch eligibility         |
| GL-CONT-005-RCM-017 | Queue Moderation                    |           Activity |     No |                        No by itself |           Conditional |                         No | Performed by moderators/agents                 |
| GL-CONT-005-RCM-018 | Round Coordination                  |           Activity |     No |                        No by itself |           Conditional |                         No | Performed by round managers                    |
| GL-CONT-005-RCM-019 | Writing / Feeding Round             |      Runtime round |     No |                        No by itself |           Conditional |                         No | Feed-domain round                              |
| GL-CONT-005-RCM-020 | Dispatching / Delivery Round        |      Runtime round |     No |                        No by itself |           Conditional |                         No | Pre-dispatch delivery-domain round             |

---

## 6. Runtime Relationship Map

|           Record ID | Source Term                          | Relationship          | Target Term                  |
| ------------------: | ------------------------------------ | --------------------- | ---------------------------- |
| GL-CONT-005-REL-001 | Queue Container                      | contains              | Slot                         |
| GL-CONT-005-REL-002 | Slot                                 | may_have              | Slot Lifecycle State         |
| GL-CONT-005-REL-003 | Log Level Envelope                   | may_occupy            | Slot                         |
| GL-CONT-005-REL-004 | Envelope Slot Occupancy              | relates               | Log Level Envelope           |
| GL-CONT-005-REL-005 | Envelope Slot Occupancy              | relates               | Slot                         |
| GL-CONT-005-REL-006 | Slot                                 | belongs_to            | Queue Container              |
| GL-CONT-005-REL-007 | Queue Container                      | identified_by         | Queue Container Identifier   |
| GL-CONT-005-REL-008 | Waiting List                         | carries               | Queue Container Identifier   |
| GL-CONT-005-REL-009 | Writing Round Manager Waiting List   | specializes           | Waiting List                 |
| GL-CONT-005-REL-010 | Delivery Round Manager Waiting List  | specializes           | Waiting List                 |
| GL-CONT-005-REL-011 | Queue Bundle                         | groups                | Queue Container              |
| GL-CONT-005-REL-012 | Queue Bundle Agent                   | coordinates           | Queue Bundle                 |
| GL-CONT-005-REL-013 | Single Queue Moderator               | moderates             | Single Queue Container       |
| GL-CONT-005-REL-014 | Writing / Feeding Round Manager      | coordinates           | Writing / Feeding Round      |
| GL-CONT-005-REL-015 | Dispatching / Delivery Round Manager | coordinates           | Dispatching / Delivery Round |
| GL-CONT-005-REL-016 | Dispatching / Delivery Round         | may_progress_toward   | Dispatch Eligibility State   |
| GL-CONT-005-REL-017 | Dispatcher                           | verifies_or_relies_on | Dispatch Eligibility State   |
| GL-CONT-005-REL-018 | Dispatcher                           | performs              | Dispatcher-Mediated Handoff  |
| GL-CONT-005-REL-019 | Runtime Placement                    | creates_or_updates    | Envelope Slot Occupancy      |
| GL-CONT-005-REL-020 | Queue-as-Container Doctrine          | governs               | Queue Runtime Layer          |

---

## 7. Runtime Flow Reference

### 7.1 Admission and Placement Flow

```text id="gl-cont-005-admission-flow"
Assembler Ingress Port
  receives:
    Log Level Envelope

Assembler Ingress Port
  admits envelope into:
    suitable Slot

Slot
  belongs to:
    Queue Container

Runtime Placement
  creates or updates:
    Envelope Slot Occupancy
```

### 7.2 Queue Coordination Flow

```text id="gl-cont-005-queue-coordination-flow"
Queue Bundle
  groups:
    Queue Containers

Queue Bundle Agent
  coordinates:
    Queue Bundle

Single Queue Moderator
  moderates:
    Single Queue Container

Waiting List
  carries:
    Queue Container Identifiers
```

### 7.3 Round Coordination Flow

```text id="gl-cont-005-round-flow"
Writing / Feeding Round Manager
  coordinates:
    Writing / Feeding Round
  may use:
    Writing Round Manager Waiting List

Dispatching / Delivery Round Manager
  coordinates:
    Dispatching / Delivery Round
  may use:
    Delivery Round Manager Waiting List

Dispatching / Delivery Round
  may progress runtime state toward:
    Dispatch Eligibility State

Dispatcher
  remains:
    final assembler-side outbound actor
```

---

## 8. Runtime Anti-Collapse Index

|          Record ID | Term                                 | Must Not Collapse Into                | Guard Meaning                                          |
| -----------------: | ------------------------------------ | ------------------------------------- | ------------------------------------------------------ |
| GL-CONT-005-AC-001 | Queue Container                      | Message broker                        | Queue is container, not broker                         |
| GL-CONT-005-AC-002 | Queue Container                      | Downstream lifecycle owner            | Runtime container does not own downstream lifecycle    |
| GL-CONT-005-AC-003 | Queue Container                      | Queue Bundle Agent                    | Container is not actor                                 |
| GL-CONT-005-AC-004 | Queue Container                      | Single Queue Moderator                | Container is not moderator                             |
| GL-CONT-005-AC-005 | Queue Bundle                         | Queue Bundle Agent                    | Grouping is not actor                                  |
| GL-CONT-005-AC-006 | Single Queue Container               | Single Queue Moderator                | Container is not moderator                             |
| GL-CONT-005-AC-007 | Slot                                 | Log Level Envelope                    | Placement structure is not carrier                     |
| GL-CONT-005-AC-008 | Slot                                 | Downstream Registry Record            | Runtime placement is not downstream persistence        |
| GL-CONT-005-AC-009 | Envelope Slot Occupancy              | Envelope lifecycle ownership          | Occupancy is not lifecycle ownership                   |
| GL-CONT-005-AC-010 | Envelope Slot Occupancy              | Handoff Evidence                      | Placement is not handoff proof                         |
| GL-CONT-005-AC-011 | Slot Lifecycle State                 | Envelope lifecycle state              | Slot state is not envelope lifecycle                   |
| GL-CONT-005-AC-012 | Waiting List                         | Envelope store                        | Waiting list carries identifiers where applicable      |
| GL-CONT-005-AC-013 | Waiting List                         | Message queue                         | Waiting list is not broker payload queue               |
| GL-CONT-005-AC-014 | Queue Container Identifier           | Envelope Identity                     | Queue locator is not envelope identity                 |
| GL-CONT-005-AC-015 | Queue Container Identifier           | Downstream Registry Record ID         | Runtime locator is not downstream primary key          |
| GL-CONT-005-AC-016 | Writing Round Manager Waiting List   | Delivery Round Manager Waiting List   | Feed-domain list is distinct from delivery-domain list |
| GL-CONT-005-AC-017 | Dispatching / Delivery Round         | Dispatcher                            | Runtime round is not final outbound actor              |
| GL-CONT-005-AC-018 | Dispatching / Delivery Round Manager | Dispatcher                            | Round manager is not final actor                       |
| GL-CONT-005-AC-019 | Queue Runtime Layer                  | Dispatch Layer                        | Runtime coordination is not final handoff              |
| GL-CONT-005-AC-020 | Runtime Readiness                    | Dispatch Eligibility State by default | Readiness mapping requires contract definition         |
| GL-CONT-005-AC-021 | Queue Moderation                     | Message brokering                     | Moderation is assembler-side container discipline      |
| GL-CONT-005-AC-022 | Round Coordination                   | Downstream delivery ownership         | Round coordination remains assembler-side              |

---

## 9. Waiting-List Semantics

### 9.1 Waiting-List Content Rule

Waiting Lists should carry `Queue Container Identifiers` where applicable.

They should not be modeled as primary stores of:

1. raw payloads,
2. Log Level Envelopes,
3. downstream records,
4. broker messages,
5. registry lifecycle records.

### 9.2 Waiting-List Role Table

|          Record ID | Waiting List                        | Supported Actor                      | Preferred Content          | Forbidden Collapse                      |
| -----------------: | ----------------------------------- | ------------------------------------ | -------------------------- | --------------------------------------- |
| GL-CONT-005-WL-001 | Waiting List                        | Generic runtime coordination actor   | Queue Container Identifier | Message payload queue                   |
| GL-CONT-005-WL-002 | Writing Round Manager Waiting List  | Writing / Feeding Round Manager      | Queue Container Identifier | Delivery backlog                        |
| GL-CONT-005-WL-003 | Delivery Round Manager Waiting List | Dispatching / Delivery Round Manager | Queue Container Identifier | Dispatcher or downstream delivery queue |

### 9.3 Waiting-List Interpretation Rule

```text id="gl-cont-005-waiting-list-interpretation"
A Waiting List identifies runtime containers awaiting coordination.
It does not, by default, own or contain the envelopes themselves.
```

---

## 10. Slot and Occupancy Semantics

### 10.1 Slot Relationship

A Slot is a placement structure.

Envelope Slot Occupancy is the relation between a Slot and a Log Level Envelope.

The two should not be collapsed.

```text id="gl-cont-005-slot-occupancy"
Queue Container
  contains:
    Slot

Log Level Envelope
  may occupy:
    Slot

Envelope Slot Occupancy
  represents:
    envelope-slot relation
```

### 10.2 Lifecycle Guard

```text id="gl-cont-005-lifecycle-guard"
Slot occupancy does not grant ownership over the envelope lifecycle.
Slot state does not grant ownership over downstream record lifecycle.
```

### 10.3 Slot/Occlusion Matrix

|            Record ID | Runtime Concept         | Owns Slot? | Owns Envelope? | Owns Downstream Record? | Notes                                |
| -------------------: | ----------------------- | ---------: | -------------: | ----------------------: | ------------------------------------ |
| GL-CONT-005-SLOT-001 | Queue Container         |        Yes |             No |                      No | Owns slot structure                  |
| GL-CONT-005-SLOT-002 | Slot                    |         No |             No |                      No | Placement position                   |
| GL-CONT-005-SLOT-003 | Envelope Slot Occupancy |         No |             No |                      No | Placement relation                   |
| GL-CONT-005-SLOT-004 | Single Queue Moderator  |         No |             No |                      No | Moderates queue-container discipline |
| GL-CONT-005-SLOT-005 | Dispatcher              |         No |             No |                      No | Mediates handoff, not slot ownership |

---

## 11. Runtime Actor-to-Structure Map

|             Record ID | Actor                                | Acts On / Coordinates                                             | Must Not Be Confused With |
| --------------------: | ------------------------------------ | ----------------------------------------------------------------- | ------------------------- |
| GL-CONT-005-ACTOR-001 | Queue Bundle Agent                   | Queue Bundle, Waiting Lists, Queue Container Identifiers          | Queue Bundle itself       |
| GL-CONT-005-ACTOR-002 | Single Queue Moderator               | Single Queue Container, Slot, Occupancy, Slot Lifecycle State     | Queue Container itself    |
| GL-CONT-005-ACTOR-003 | Writing / Feeding Round Manager      | Writing / Feeding Round, Writing Round Manager Waiting List       | Dispatcher                |
| GL-CONT-005-ACTOR-004 | Dispatching / Delivery Round Manager | Dispatching / Delivery Round, Delivery Round Manager Waiting List | Dispatcher                |
| GL-CONT-005-ACTOR-005 | Dispatcher                           | Dispatch Eligibility State, Handoff, Registry / Delivery Port     | Round manager             |

---

## 12. Contract Readiness Notes

This pack prepares the runtime vocabulary for later contract-family derivation.

The following future contract areas are enabled but not yet defined here:

|                Record ID | Future Contract Area          | Runtime Basis                                                         |
| -----------------------: | ----------------------------- | --------------------------------------------------------------------- |
| GL-CONT-005-CONREADY-001 | Runtime State Contract Family | Queue Container, Slot, Occupancy, Waiting List                        |
| GL-CONT-005-CONREADY-002 | Queue Admission Contract      | Assembler Ingress Port, Slot, Queue Container                         |
| GL-CONT-005-CONREADY-003 | Queue Moderation Contract     | Queue Bundle Agent, Single Queue Moderator                            |
| GL-CONT-005-CONREADY-004 | Round Coordination Contract   | Writing / Feeding Round Manager, Dispatching / Delivery Round Manager |
| GL-CONT-005-CONREADY-005 | Dispatch Readiness Contract   | Runtime Readiness, Dispatch Eligibility State                         |
| GL-CONT-005-CONREADY-006 | Occupancy Integrity Contract  | Envelope Slot Occupancy, Slot Lifecycle State                         |
| GL-CONT-005-CONREADY-007 | Waiting-List Locator Contract | Waiting List, Queue Container Identifier                              |

---

## 13. Source Trace Summary

|           Record ID | Source Area        | Supported Terms                                                                          |
| ------------------: | ------------------ | ---------------------------------------------------------------------------------------- |
| GL-CONT-005-SRC-001 | README.md          | Runtime Queue Container Layer, Queue as Container, Dispatcher separation                 |
| GL-CONT-005-SRC-002 | ProjectOverview.md | Queue Container, Slot, Queue Bundle Agent, Single Queue Moderator, Round Managers        |
| GL-CONT-005-SRC-003 | VisionAndScope.md  | Queue-as-Container scope, corrected ingress target slot, runtime coordination ownership  |
| GL-CONT-005-SRC-004 | SYSTEM_GOALS.md    | SG-QUEUE goals, slot occupancy distinction, waiting-list identifier rule                 |
| GL-CONT-005-SRC-005 | GL-CONT-000        | Term family/category model, runtime_state category, anti-collapse requirements           |
| GL-CONT-005-SRC-006 | GL-CONT-003        | Runtime actors and delegated entities                                                    |
| GL-CONT-005-SRC-007 | GL-CONT-004        | Log Level Envelope as carrier, Dispatch Eligibility State, Envelope Identity distinction |

---

## 14. Validation Checklist

|           Record ID | Check                                                                 | Expected Result |
| ------------------: | --------------------------------------------------------------------- | --------------- |
| GL-CONT-005-VAL-001 | Queue Container is classified as runtime container                    | Pass            |
| GL-CONT-005-VAL-002 | Queue Container is not classified as actor                            | Pass            |
| GL-CONT-005-VAL-003 | Queue Container is not treated as message broker                      | Pass            |
| GL-CONT-005-VAL-004 | Queue Bundle is distinct from Queue Bundle Agent                      | Pass            |
| GL-CONT-005-VAL-005 | Single Queue Container is distinct from Single Queue Moderator        | Pass            |
| GL-CONT-005-VAL-006 | Slot is distinct from Log Level Envelope                              | Pass            |
| GL-CONT-005-VAL-007 | Envelope Slot Occupancy is distinct from envelope lifecycle ownership | Pass            |
| GL-CONT-005-VAL-008 | Slot Lifecycle State is distinct from downstream lifecycle            | Pass            |
| GL-CONT-005-VAL-009 | Waiting List stores Queue Container Identifiers where applicable      | Pass            |
| GL-CONT-005-VAL-010 | Waiting List is not a generic envelope store                          | Pass            |
| GL-CONT-005-VAL-011 | Queue Container Identifier is distinct from Envelope Identity         | Pass            |
| GL-CONT-005-VAL-012 | Writing and delivery waiting lists remain distinct                    | Pass            |
| GL-CONT-005-VAL-013 | Writing / Feeding Round is distinct from Dispatching / Delivery Round | Pass            |
| GL-CONT-005-VAL-014 | Dispatching / Delivery Round Manager is distinct from Dispatcher      | Pass            |
| GL-CONT-005-VAL-015 | Runtime Coordination does not own downstream lifecycle                | Pass            |
| GL-CONT-005-VAL-016 | Queue Runtime Layer does not replace Dispatch Layer                   | Pass            |

---

## 15. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                                     | Status   |
| -------------------: | ------------------------------------------------------------------ | -------- |
| GL-CONT-005-EXIT-001 | Core runtime queue terms are defined                               | Complete |
| GL-CONT-005-EXIT-002 | Queue Container is formally defined as runtime container           | Complete |
| GL-CONT-005-EXIT-003 | Queue-as-Container Doctrine is formally stated                     | Complete |
| GL-CONT-005-EXIT-004 | Queue ≠ Message Broker is enforced                                 | Complete |
| GL-CONT-005-EXIT-005 | Slot and Envelope Slot Occupancy are separated                     | Complete |
| GL-CONT-005-EXIT-006 | Slot occupancy ≠ Envelope Lifecycle Ownership is enforced          | Complete |
| GL-CONT-005-EXIT-007 | Waiting List locator semantics are defined                         | Complete |
| GL-CONT-005-EXIT-008 | Writing and delivery waiting lists are separated                   | Complete |
| GL-CONT-005-EXIT-009 | Queue Container Identifier is distinguished from Envelope Identity | Complete |
| GL-CONT-005-EXIT-010 | Runtime actors are mapped to runtime structures                    | Complete |
| GL-CONT-005-EXIT-011 | Round Coordination is separated from Dispatcher finality           | Complete |
| GL-CONT-005-EXIT-012 | Pack is ready to support contract-family derivation                | Complete |

---

## 16. Summary

`GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack` establishes the canonical vocabulary for assembler-side runtime coordination.

The pack stabilizes the following runtime model:

```text id="gl-cont-005-summary-model"
Queue Container
= runtime container
≠ message broker
≠ downstream lifecycle owner

Queue Bundle
= grouping of Queue Containers
≠ Queue Bundle Agent

Single Queue Container
= one Queue Container
≠ Single Queue Moderator

Slot
= placement structure inside Queue Container
≠ Log Level Envelope
≠ downstream record

Envelope Slot Occupancy
= envelope-slot relation
≠ envelope lifecycle ownership

Waiting List
= identifier-oriented runtime coordination list
should carry Queue Container Identifiers where applicable
≠ envelope store
≠ message payload queue

Queue Container Identifier
= runtime locator for Queue Container
≠ Envelope Identity
≠ downstream registry ID

Writing / Feeding Round
≠ Dispatching / Delivery Round

Dispatching / Delivery Round Manager
≠ Dispatcher

Runtime Coordination
= assembler-side queue/container/round coordination
≠ downstream delivery lifecycle
```

This pack enables the next glossary content pack:

```text id="gl-cont-005-next"
GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack
```
