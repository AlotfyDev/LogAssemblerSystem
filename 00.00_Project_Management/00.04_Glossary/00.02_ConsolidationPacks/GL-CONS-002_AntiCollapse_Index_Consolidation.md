
# GL-CONS-002 — Anti-Collapse Index Consolidation

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONS-002-DOC-001 | Document Title | GL-CONS-002_AntiCollapse_Index_Consolidation.md |
| GL-CONS-002-DOC-002 | Formal Version | Formal Draft V1 |
| GL-CONS-002-DOC-003 | Project | Assembler System |
| GL-CONS-002-DOC-004 | Parent Workstream | Glossary Workstream |
| GL-CONS-002-DOC-005 | Document Type | Consolidated Index / Validation Control Pack |
| GL-CONS-002-DOC-006 | Language | English |
| GL-CONS-002-DOC-007 | Status | Formal Draft V1 |
| GL-CONS-002-DOC-008 | Consolidates | Anti-collapse rules from GL-CONT-000 through GL-CONT-010 |
| GL-CONS-002-DOC-009 | Scope | Category-collapse prevention, boundary-collapse prevention, ownership-collapse prevention, implementation-prematurity prevention, future validation readiness |
| GL-CONS-002-DOC-010 | Excluded From This Pack | Full glossary entry population, master Glossary.md assembly, CSV/JSON schema finalization, database schema derivation, implementation package derivation |
| GL-CONS-002-DOC-011 | Enables | Anti-collapse validation matrix, glossary QA checks, documentation review, schema constraints, future DB-backed glossary governance |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack consolidates the anti-collapse rules distributed across the Assembler System glossary content packs.

It answers the question:

```text
Which conceptual, architectural, ownership, runtime, contract, policy,
handoff, and implementation-direction collapses must be explicitly prevented
across the Assembler System documentation and future derivation path?
````

This pack is not a master glossary.

It is an index of guard rules.

Each rule identifies a prohibited conceptual merge, its protected distinction, the source pack family that established it, and the validation use of the rule.

### 2.2 Why This Pack Exists

The Assembler System vocabulary contains terms that are close enough to be confused but architecturally distinct.

Examples include:

```text
Envelope Assembler ≠ Log Level Envelope
Dispatcher ≠ Registry / Delivery Port
Queue Container ≠ Message Broker
Contract ≠ C++ interface
Responsibility ≠ class
Semantic Domain ≠ technical folder
```

Without a consolidated anti-collapse index, later documents, schemas, databases, packages, and C++ derivation packs could accidentally merge distinct categories.

This pack prevents that failure.

### 2.3 Core Function

|            Record ID | Function             | Description                                                                                                |
| -------------------: | -------------------- | ---------------------------------------------------------------------------------------------------------- |
| GL-CONS-002-FUNC-001 | Guard Index          | Lists anti-collapse rules as standalone records                                                            |
| GL-CONS-002-FUNC-002 | Validation Reference | Provides rules for future glossary coverage and consistency checks                                         |
| GL-CONS-002-FUNC-003 | Derivation Guard     | Prevents invalid package, class, schema, or database derivation                                            |
| GL-CONS-002-FUNC-004 | Ownership Guard      | Prevents assembler authority from absorbing downstream responsibility                                      |
| GL-CONS-002-FUNC-005 | Category Guard       | Preserves distinctions between actor, object, port, contract, runtime state, evidence, and future artifact |
| GL-CONS-002-FUNC-006 | Database Readiness   | Prepares anti-collapse rules for later relational or JSON-backed storage                                   |

---

## 3. Consolidation Principle

### 3.1 Primary Principle

```text id="gl-cons-002-primary-principle"
Every anti-collapse rule protects one architectural distinction that must remain
valid across documentation, glossary entries, validation artifacts, and future
implementation derivation.
```

### 3.2 Index Rule

```text id="gl-cons-002-index-rule"
An anti-collapse rule is not explanatory prose only.
It is a validation-grade constraint that may later become a database row,
schema assertion, review checklist item, test derivation source, or compliance rule.
```

### 3.3 No-Term-Merge Rule

```text id="gl-cons-002-no-term-merge-rule"
If two terms have different architectural categories, ownership scopes,
authority positions, runtime roles, or derivation maturity levels, they must not
be merged merely because their names are similar or their runtime path is adjacent.
```

---

## 4. Anti-Collapse Rule Record Model

Each anti-collapse rule in this pack should be interpretable as a future database row.

| Field                  | Meaning                                                              |
| ---------------------- | -------------------------------------------------------------------- |
| Rule ID                | Stable identifier for the anti-collapse rule                         |
| Protected Term         | The term whose meaning is being protected                            |
| Must Not Collapse Into | The term, category, system, or artifact it must not be confused with |
| Protected Distinction  | The architectural distinction being preserved                        |
| Source Pack            | Main GL-CONT pack where the rule is established                      |
| Severity               | Critical / High / Medium                                             |
| Validation Use         | How future reviews or validators should use the rule                 |
| Derivation Impact      | What future derivation would break if the rule is violated           |

---

## 5. Severity Model

|           Record ID | Severity | Meaning                                                                             |
| ------------------: | -------- | ----------------------------------------------------------------------------------- |
| GL-CONS-002-SEV-001 | Critical | Violation changes system ownership, boundary, or core identity                      |
| GL-CONS-002-SEV-002 | High     | Violation corrupts actor/object/contract/runtime semantics                          |
| GL-CONS-002-SEV-003 | Medium   | Violation creates terminology drift or premature derivation risk                    |
| GL-CONS-002-SEV-004 | Low      | Violation creates editorial ambiguity but does not immediately corrupt architecture |

---

## 6. Rule Families

|           Record ID | Rule Family                                    | Description                                                                                              |
| ------------------: | ---------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| GL-CONS-002-FAM-001 | Identity Collapse Rules                        | Prevent the Assembler System from becoming adjacent systems                                              |
| GL-CONS-002-FAM-002 | Boundary and Authority Collapse Rules          | Prevent ports, boundaries, and downstream systems from merging                                           |
| GL-CONS-002-FAM-003 | Actor / Entity Collapse Rules                  | Prevent internal actors from merging with ports, objects, or the whole subsystem                         |
| GL-CONS-002-FAM-004 | Object / Carrier Collapse Rules                | Prevent governed objects and carriers from becoming actors or raw material                               |
| GL-CONS-002-FAM-005 | Runtime Collapse Rules                         | Prevent queue/container/slot/round vocabulary from becoming broker or lifecycle ownership                |
| GL-CONS-002-FAM-006 | Contract and Type-Safety Collapse Rules        | Prevent contracts from being reduced to code artifacts                                                   |
| GL-CONS-002-FAM-007 | Responsibility and Derivation Collapse Rules   | Prevent responsibilities, obligations, and capabilities from becoming implementation artifacts too early |
| GL-CONS-002-FAM-008 | Policy / Metadata / Timestamp Collapse Rules   | Prevent governance terms from merging with policy execution or downstream query semantics                |
| GL-CONS-002-FAM-009 | Dispatcher / Handoff / Registry Collapse Rules | Prevent handoff from becoming downstream lifecycle ownership                                             |
| GL-CONS-002-FAM-010 | C++ / Semantic Domain / Package Collapse Rules | Prevent future implementation direction from becoming final code structure prematurely                   |

---

# 7. Consolidated Anti-Collapse Index

## 7.1 Identity Collapse Rules

|      Rule ID | Protected Term                             | Must Not Collapse Into         | Protected Distinction                                                | Source Pack                             | Severity | Validation Use                          |
| -----------: | ------------------------------------------ | ------------------------------ | -------------------------------------------------------------------- | --------------------------------------- | -------- | --------------------------------------- |
| GL-AC-ID-001 | Assembler System                           | Full logging system            | Assembler owns preparation/dispatch only, not full logging lifecycle | GL-CONT-001                             | Critical | Check all system-scope claims           |
| GL-AC-ID-002 | Assembler System                           | Full messaging system          | Runtime queues are containers, not broker infrastructure             | GL-CONT-001 / GL-CONT-005               | Critical | Check runtime and roadmap language      |
| GL-AC-ID-003 | Assembler System                           | Downstream registry            | Registry internals remain downstream and not assembler-owned         | GL-CONT-001 / GL-CONT-002 / GL-CONT-009 | Critical | Check ownership and handoff claims      |
| GL-AC-ID-004 | Assembler System                           | Database or storage engine     | Storage lifecycle is excluded after handoff                          | GL-CONT-001 / GL-CONT-009               | Critical | Check storage/database derivation       |
| GL-AC-ID-005 | Assembler System                           | Query engine                   | Reading/querying subsystem is external and not owned                 | GL-CONT-001 / GL-CONT-002               | Critical | Check query-related scope               |
| GL-AC-ID-006 | Assembler System                           | Network transport layer        | Transport mechanism is not system identity                           | GL-CONT-001                             | High     | Check integration and delivery language |
| GL-AC-ID-007 | C++ Write-Side Preparation Kernel          | Generic C++ utility library    | Kernel identity is architectural, write-side, and preparation-bound  | GL-CONT-001 / GL-CONT-010               | High     | Check C++ package proposals             |
| GL-AC-ID-008 | Pre-Implementation Architecture Phase      | Implementation-ready codebase  | Current phase defines architecture before code                       | GL-CONT-001                             | High     | Check roadmap and milestone claims      |
| GL-AC-ID-009 | Documentation-First Architecture Formation | Documentation-only project     | Documentation is a derivation control layer, not an end state        | GL-CONT-001 / GL-CONT-010               | Medium   | Check implementation planning language  |
| GL-AC-ID-010 | Preparation and Dispatch Authority         | Downstream lifecycle authority | Authority ends at valid dispatcher-mediated handoff                  | GL-CONT-001 / GL-CONT-009               | Critical | Check authority closure                 |

---

## 7.2 Boundary and Authority Collapse Rules

|       Rule ID | Protected Term                  | Must Not Collapse Into           | Protected Distinction                                                    | Source Pack               | Severity | Validation Use                        |
| ------------: | ------------------------------- | -------------------------------- | ------------------------------------------------------------------------ | ------------------------- | -------- | ------------------------------------- |
| GL-AC-BND-001 | Assembler Boundary              | Entire logging platform boundary | Assembler boundary is narrower than full platform boundary               | GL-CONT-002               | Critical | Review system boundary sections       |
| GL-AC-BND-002 | Assembler Boundary              | Downstream registry boundary     | Registry internals are outside assembler authority                       | GL-CONT-002 / GL-CONT-009 | Critical | Review handoff and registry language  |
| GL-AC-BND-003 | Assembler Boundary              | Query subsystem boundary         | Query behavior is external                                               | GL-CONT-002               | Critical | Review read/query scope               |
| GL-AC-BND-004 | Boundary Surface                | Internal actor                   | Boundary surfaces mediate interaction; actors carry responsibilities     | GL-CONT-002 / GL-CONT-003 | High     | Check term categories                 |
| GL-AC-BND-005 | Boundary Surface                | Processing unit                  | Boundary surface is not automatically an implementation unit             | GL-CONT-002 / GL-CONT-010 | High     | Check C++ derivation packs            |
| GL-AC-BND-006 | Contract Surface                | C++ interface by default         | Contract surface is architectural before implementation                  | GL-CONT-002 / GL-CONT-006 | High     | Check interface proposals             |
| GL-AC-BND-007 | Authority Boundary              | Deployment boundary              | Authority is semantic/ownership boundary, not merely deployment topology | GL-CONT-002               | High     | Check infrastructure diagrams         |
| GL-AC-BND-008 | Downstream Boundary             | Assembler-owned boundary         | Downstream remains external/not owned after handoff                      | GL-CONT-002 / GL-CONT-009 | Critical | Check downstream lifecycle references |
| GL-AC-BND-009 | Assembler Ingress Port          | Envelope Assembler               | Ingress receives prepared envelope; assembler produces it earlier        | GL-CONT-002 / GL-CONT-003 | Critical | Check ingress flow                    |
| GL-AC-BND-010 | Assembler Ingress Port          | Raw payload intake               | Ingress port receives Log Level Envelope, not raw payload                | GL-CONT-002 / GL-CONT-004 | Critical | Check ingestion model                 |
| GL-AC-BND-011 | Administrative / Ecosystem Port | Consuming ingress                | Admin/control input remains separate from content entry                  | GL-CONT-002               | High     | Check boundary surface use            |
| GL-AC-BND-012 | Registry / Delivery Port        | Dispatcher                       | Port is contract surface; Dispatcher is final outbound actor             | GL-CONT-002 / GL-CONT-009 | Critical | Check handoff architecture            |
| GL-AC-BND-013 | Registry / Delivery Port        | Log Level Records Registry       | Delivery port is assembler-facing surface; registry is downstream system | GL-CONT-002 / GL-CONT-009 | Critical | Check registry-facing language        |
| GL-AC-BND-014 | Level API                       | Internal assembler actor         | Level API is consuming-side façade/context                               | GL-CONT-002 / GL-CONT-003 | High     | Check external/internal taxonomy      |
| GL-AC-BND-015 | Policy Registry / Policy Source | PolicyAssigner                   | Source supplies policy material; PolicyAssigner mediates assignment      | GL-CONT-002 / GL-CONT-008 | High     | Check policy diagrams                 |
| GL-AC-BND-016 | Metadata Directive Source       | Metadata Injector                | Source supplies directives; injector performs assembler-side preparation | GL-CONT-002 / GL-CONT-008 | High     | Check metadata governance             |
| GL-AC-BND-017 | Log Level Records Registry      | Assembler component              | Registry is downstream and not internal                                  | GL-CONT-002 / GL-CONT-009 | Critical | Check component inventory             |
| GL-AC-BND-018 | Reading / Querying Subsystem    | Assembler subsystem              | Read/query behavior remains outside assembler scope                      | GL-CONT-002               | Critical | Check query-related roadmap items     |
| GL-AC-BND-019 | Post-Handoff Non-Ownership      | Optional note                    | It is an authority rule, not editorial guidance                          | GL-CONT-002 / GL-CONT-009 | Critical | Check validation and compliance       |

---

## 7.3 Actor and Entity Collapse Rules

|       Rule ID | Protected Term                       | Must Not Collapse Into                      | Protected Distinction                                                            | Source Pack                             | Severity | Validation Use                         |
| ------------: | ------------------------------------ | ------------------------------------------- | -------------------------------------------------------------------------------- | --------------------------------------- | -------- | -------------------------------------- |
| GL-AC-ENT-001 | Internal Actor                       | Port                                        | Actor carries responsibility; port is interaction surface                        | GL-CONT-003                             | High     | Check entity classification            |
| GL-AC-ENT-002 | Internal Actor                       | Carrier Object                              | Actor performs/coordinates; carrier object is carried/governed                   | GL-CONT-003 / GL-CONT-004               | High     | Check actor/object mapping             |
| GL-AC-ENT-003 | Supporting Entity                    | Primary Responsibility Owner by default     | Support does not imply primary ownership                                         | GL-CONT-003                             | High     | Check responsibility assignments       |
| GL-AC-ENT-004 | Delegated Entity                     | Whole subsystem                             | Delegation targets narrow mature carrier, not broad subsystem by default         | GL-CONT-003 / GL-CONT-007               | High     | Check delegation tables                |
| GL-AC-ENT-005 | Envelope Assembler                   | Log Level Envelope                          | Producer is not produced carrier                                                 | GL-CONT-003 / GL-CONT-004               | Critical | Check ingress and object model         |
| GL-AC-ENT-006 | Envelope Assembler                   | Assembler Ingress Port                      | Assembly precedes ingress-port receipt                                           | GL-CONT-003                             | Critical | Check corrected ingress flow           |
| GL-AC-ENT-007 | Envelope Assembler                   | Level API                                   | Level API may contain/inject assembler, but is not identical to it               | GL-CONT-003 / GL-CONT-002               | High     | Check consuming façade diagrams        |
| GL-AC-ENT-008 | Envelope Assembler                   | Dispatcher                                  | Assembly and outbound handoff are distinct responsibilities                      | GL-CONT-003 / GL-CONT-009               | High     | Check pipeline sequence                |
| GL-AC-ENT-009 | Envelope Assembler                   | Queue Container                             | Producer does not own runtime container placement                                | GL-CONT-003 / GL-CONT-005               | High     | Check runtime derivation               |
| GL-AC-ENT-010 | Dispatcher                           | Registry / Delivery Port                    | Dispatcher is actor; port is contract surface                                    | GL-CONT-003 / GL-CONT-009               | Critical | Check handoff path                     |
| GL-AC-ENT-011 | Dispatcher                           | Log Level Records Registry                  | Dispatcher mediates handoff; registry is downstream                              | GL-CONT-003 / GL-CONT-009               | Critical | Check registry ownership               |
| GL-AC-ENT-012 | Dispatcher                           | Queue Bundle Agent                          | Runtime coordination and final handoff are separate actors                       | GL-CONT-003 / GL-CONT-005 / GL-CONT-009 | High     | Check runtime/handoff responsibilities |
| GL-AC-ENT-013 | Dispatcher                           | Dispatching / Delivery Round Manager        | Round manager coordinates rounds; Dispatcher is final outbound actor             | GL-CONT-003 / GL-CONT-009               | High     | Check delivery round language          |
| GL-AC-ENT-014 | Validator                            | Envelope Assembler                          | Validator supports validation; assembler realizes envelope                       | GL-CONT-003                             | High     | Check composition language             |
| GL-AC-ENT-015 | Validator                            | Policy Object                               | Validator may consume policy; policy object is governed material                 | GL-CONT-003 / GL-CONT-008               | High     | Check policy validation references     |
| GL-AC-ENT-016 | Metadata Injector                    | Policy Host by default                      | Metadata injection is schema/directive-governed unless later contract changes it | GL-CONT-003 / GL-CONT-008               | High     | Check metadata-policy relation         |
| GL-AC-ENT-017 | Metadata Injector                    | Metadata Directive Source                   | Internal preparation component differs from external directive source            | GL-CONT-003 / GL-CONT-008               | High     | Check metadata source diagrams         |
| GL-AC-ENT-018 | Timestamp Stabilizer                 | Downstream query-time timestamp interpreter | Stabilization is assembler-side pre-dispatch preparation                         | GL-CONT-003 / GL-CONT-008               | High     | Check timestamp semantics              |
| GL-AC-ENT-019 | PolicyAssigner                       | Policy Object                               | Assignment actor/relation differs from policy material object                    | GL-CONT-003 / GL-CONT-008               | High     | Check policy chain                     |
| GL-AC-ENT-020 | PolicyAssigner                       | Policy Registry / Policy Source             | Internal assignment component differs from external source                       | GL-CONT-003 / GL-CONT-008               | High     | Check policy-source ownership          |
| GL-AC-ENT-021 | Queue Bundle Agent                   | Queue Bundle                                | Actor coordinating bundle differs from runtime grouping object                   | GL-CONT-003 / GL-CONT-005               | High     | Check runtime entity taxonomy          |
| GL-AC-ENT-022 | Single Queue Moderator               | Single Queue Container                      | Moderator is actor; container is runtime structure                               | GL-CONT-003 / GL-CONT-005               | High     | Check queue moderation                 |
| GL-AC-ENT-023 | Writing / Feeding Round Manager      | Waiting List                                | Manager coordinates; waiting list carries identifiers                            | GL-CONT-003 / GL-CONT-005               | Medium   | Check round model                      |
| GL-AC-ENT-024 | Dispatching / Delivery Round Manager | Dispatcher                                  | Round manager is not final outbound actor                                        | GL-CONT-003 / GL-CONT-009               | High     | Check delivery process                 |
| GL-AC-ENT-025 | Policy-Consuming Component           | Policy Object                               | Consuming component realizes policy-governed behavior; object does not execute   | GL-CONT-003 / GL-CONT-008               | High     | Check policy governance                |
| GL-AC-ENT-026 | Runtime Coordination Actor           | Runtime container                           | Actor coordinates runtime structures; container stores/organizes placement       | GL-CONT-003 / GL-CONT-005               | High     | Check runtime model                    |

---

## 7.4 Object and Carrier Collapse Rules

|       Rule ID | Protected Term             | Must Not Collapse Into                 | Protected Distinction                                                            | Source Pack               | Severity | Validation Use                 |
| ------------: | -------------------------- | -------------------------------------- | -------------------------------------------------------------------------------- | ------------------------- | -------- | ------------------------------ |
| GL-AC-OBJ-001 | Governed Object            | Actor                                  | Object may be carried/validated/assigned; it does not perform responsibilities   | GL-CONT-004               | High     | Check object model             |
| GL-AC-OBJ-002 | Carrier Object             | Producer component                     | Carrier holds material; producer creates or prepares it                          | GL-CONT-004               | High     | Check envelope model           |
| GL-AC-OBJ-003 | Log Level Envelope         | Envelope Assembler                     | Envelope is produced carrier; assembler is producing entity                      | GL-CONT-004 / GL-CONT-003 | Critical | Check ingress path             |
| GL-AC-OBJ-004 | Log Level Envelope         | Raw Payload / Raw Content              | Envelope is prepared authoritative carrier; raw content is pre-envelope material | GL-CONT-004               | Critical | Check payload language         |
| GL-AC-OBJ-005 | Log Level Envelope         | Assembler Ingress Port                 | Envelope is received by port; port is boundary surface                           | GL-CONT-004 / GL-CONT-002 | Critical | Check ingress definitions      |
| GL-AC-OBJ-006 | Log Level Envelope         | Dispatcher                             | Envelope is carried toward handoff; Dispatcher performs final handoff            | GL-CONT-004 / GL-CONT-009 | Critical | Check handoff descriptions     |
| GL-AC-OBJ-007 | Log Level Envelope         | Queue Container                        | Envelope occupies slot; queue container owns slot structure                      | GL-CONT-004 / GL-CONT-005 | High     | Check runtime placement        |
| GL-AC-OBJ-008 | Log Level Envelope         | Downstream Registry Record             | Envelope is assembler-side carrier; registry record is downstream artifact       | GL-CONT-004 / GL-CONT-009 | Critical | Check registry persistence     |
| GL-AC-OBJ-009 | Log Level Envelope         | Handoff Evidence                       | Evidence supports traceability; envelope is runtime carrier                      | GL-CONT-004 / GL-CONT-009 | High     | Check handoff artifacts        |
| GL-AC-OBJ-010 | Log Envelope               | Separate canonical envelope by default | Alias maps to Log Level Envelope unless later distinction is formalized          | GL-CONT-004               | Medium   | Check alias handling           |
| GL-AC-OBJ-011 | Policy Object              | PolicyAssigner                         | Policy material is not assignment actor                                          | GL-CONT-004 / GL-CONT-008 | High     | Check policy object use        |
| GL-AC-OBJ-012 | Policy Object              | Policy-Consuming Component             | Object governs behavior; component realizes behavior                             | GL-CONT-004 / GL-CONT-008 | High     | Check policy host language     |
| GL-AC-OBJ-013 | Policy Assignment          | Policy Object                          | Assignment relation differs from assigned material                               | GL-CONT-004 / GL-CONT-008 | High     | Check policy model             |
| GL-AC-OBJ-014 | Delivery-Cycle Flag Set    | Dispatcher Feedback Report             | State flags differ from report artifact                                          | GL-CONT-004               | Medium   | Check delivery-cycle artifacts |
| GL-AC-OBJ-015 | Dispatcher Feedback Report | Handoff Evidence                       | Feedback/report artifact is not necessarily handoff evidence                     | GL-CONT-004 / GL-CONT-009 | Medium   | Check reporting model          |
| GL-AC-OBJ-016 | Handoff Evidence           | Proof of downstream persistence        | Evidence supports assembler-side traceability, not downstream lifecycle proof    | GL-CONT-004 / GL-CONT-009 | Critical | Check handoff claims           |
| GL-AC-OBJ-017 | Runtime Transport Unit     | Message broker message                 | Runtime transport carrier is not broker infrastructure                           | GL-CONT-004 / GL-CONT-005 | High     | Check runtime terminology      |
| GL-AC-OBJ-018 | Downstream Registry Record | Assembler-owned object                 | Registry record belongs downstream after handoff                                 | GL-CONT-004 / GL-CONT-009 | Critical | Check persistence ownership    |
| GL-AC-OBJ-019 | Raw Payload / Raw Content  | Runtime transport unit                 | Raw material must not replace prepared envelope                                  | GL-CONT-004               | Critical | Check ingestion claims         |
| GL-AC-OBJ-020 | Dispatch Eligibility State | Valid downstream acceptance            | Eligibility is assembler-side readiness, not downstream acceptance               | GL-CONT-004 / GL-CONT-009 | High     | Check dispatch readiness       |

---

## 7.5 Runtime Collapse Rules

|       Rule ID | Protected Term                      | Must Not Collapse Into          | Protected Distinction                                                 | Source Pack               | Severity | Validation Use                 |
| ------------: | ----------------------------------- | ------------------------------- | --------------------------------------------------------------------- | ------------------------- | -------- | ------------------------------ |
| GL-AC-RUN-001 | Queue Container                     | Message broker                  | Queue is container, not broker                                        | GL-CONT-005               | Critical | Check runtime architecture     |
| GL-AC-RUN-002 | Queue Container                     | Downstream storage queue        | Assembler queue does not own downstream storage lifecycle             | GL-CONT-005 / GL-CONT-009 | Critical | Check persistence language     |
| GL-AC-RUN-003 | Queue Container                     | Transport layer                 | Queue container organizes runtime placement, not network transport    | GL-CONT-005               | High     | Check integration diagrams     |
| GL-AC-RUN-004 | Queue Container                     | Queue Bundle Agent              | Container structure differs from coordinating actor                   | GL-CONT-005 / GL-CONT-003 | High     | Check actor/container model    |
| GL-AC-RUN-005 | Queue Container                     | Dispatcher                      | Runtime container does not perform final outbound handoff             | GL-CONT-005 / GL-CONT-009 | Critical | Check handoff bypass risk      |
| GL-AC-RUN-006 | Queue Container                     | Log Level Envelope              | Container holds slot structure; envelope is carrier object            | GL-CONT-005 / GL-CONT-004 | High     | Check queue contents           |
| GL-AC-RUN-007 | Queue Container                     | Runtime lifecycle owner         | Queue owns slot structure, not envelope or downstream lifecycle       | GL-CONT-005               | High     | Check lifecycle ownership      |
| GL-AC-RUN-008 | Queue Bundle                        | Queue Bundle Agent              | Bundle is grouping; agent is actor                                    | GL-CONT-005 / GL-CONT-003 | High     | Check bundle coordination      |
| GL-AC-RUN-009 | Queue Bundle                        | Message broker topic            | Bundle grouping is not broker topic semantics                         | GL-CONT-005               | High     | Check broker analogies         |
| GL-AC-RUN-010 | Single Queue Container              | Single Queue Moderator          | Container differs from actor moderating it                            | GL-CONT-005 / GL-CONT-003 | High     | Check moderation language      |
| GL-AC-RUN-011 | Pending / Waiting Queue Container   | Waiting List                    | Queue state variant differs from identifier list                      | GL-CONT-005               | Medium   | Check waiting model            |
| GL-AC-RUN-012 | Slot                                | Envelope                        | Slot is placement structure; envelope is carrier                      | GL-CONT-005 / GL-CONT-004 | High     | Check runtime placement        |
| GL-AC-RUN-013 | Envelope Slot Occupancy             | Envelope lifecycle ownership    | Occupancy records placement; it does not own lifecycle                | GL-CONT-005               | Critical | Check runtime state model      |
| GL-AC-RUN-014 | Slot Lifecycle State                | Envelope lifecycle              | Slot state differs from envelope lifecycle                            | GL-CONT-005               | High     | Check lifecycle diagrams       |
| GL-AC-RUN-015 | Waiting List                        | Envelope store                  | Waiting list carries identifiers, not generic envelope storage        | GL-CONT-005               | High     | Check queue waiting structures |
| GL-AC-RUN-016 | Writing Round Manager Waiting List  | Payload queue                   | Waiting list is not raw payload queue                                 | GL-CONT-005               | High     | Check writing-round model      |
| GL-AC-RUN-017 | Delivery Round Manager Waiting List | Dispatcher                      | Waiting list supports coordination; Dispatcher performs final handoff | GL-CONT-005 / GL-CONT-009 | High     | Check delivery process         |
| GL-AC-RUN-018 | Queue Container Identifier          | Queue Container itself          | Identifier locates/references container, not the container object     | GL-CONT-005               | Medium   | Check schema modeling          |
| GL-AC-RUN-019 | Queue-as-Container Doctrine         | Implementation detail only      | Doctrine is an architectural guard, not just code structure           | GL-CONT-005               | High     | Check runtime design           |
| GL-AC-RUN-020 | Runtime Coordination                | Downstream lifecycle management | Runtime coordination stays assembler-side                             | GL-CONT-005 / GL-CONT-009 | Critical | Check runtime scope            |
| GL-AC-RUN-021 | Round Coordination                  | Dispatcher finality             | Round coordination must not replace final dispatcher-mediated handoff | GL-CONT-005 / GL-CONT-009 | High     | Check delivery rounds          |
| GL-AC-RUN-022 | Writing / Feeding Round             | Dispatching / Delivery Round    | Write-side feeding and delivery coordination are distinct rounds      | GL-CONT-005               | Medium   | Check round taxonomy           |

---

## 7.6 Contract and Type-Safety Collapse Rules

|       Rule ID | Protected Term                         | Must Not Collapse Into                   | Protected Distinction                                                 | Source Pack               | Severity | Validation Use               |
| ------------: | -------------------------------------- | ---------------------------------------- | --------------------------------------------------------------------- | ------------------------- | -------- | ---------------------------- |
| GL-AC-CON-001 | Contract                               | C++ interface by default                 | Contract is architectural law before implementation                   | GL-CONT-006               | Critical | Check interface derivation   |
| GL-AC-CON-002 | Contract                               | Concrete class                           | Contract does not imply class existence                               | GL-CONT-006               | Critical | Check class proposals        |
| GL-AC-CON-003 | Contract                               | Template by default                      | Template may represent contract later, but does not define it         | GL-CONT-006               | High     | Check template design        |
| GL-AC-CON-004 | Contract                               | Runtime algorithm                        | Contract governs behavior; algorithm implements later                 | GL-CONT-006               | High     | Check runtime specs          |
| GL-AC-CON-005 | Contract                               | Validation function only                 | Contract is broader than validation function                          | GL-CONT-006               | High     | Check validation design      |
| GL-AC-CON-006 | Contract                               | API endpoint only                        | Endpoint may be surface; contract is governance law                   | GL-CONT-006 / GL-CONT-002 | High     | Check boundary APIs          |
| GL-AC-CON-007 | Contract                               | Package boundary                         | Contract may influence package, but is not package itself             | GL-CONT-006 / GL-CONT-010 | High     | Check package derivation     |
| GL-AC-CON-008 | Typed Contract                         | Type alias only                          | Typed contract preserves architectural meaning, not just naming       | GL-CONT-006               | High     | Check type model             |
| GL-AC-CON-009 | Typed Contract                         | Serialization schema only                | Schema may represent data; typed contract governs interaction meaning | GL-CONT-006               | High     | Check JSON/CSV derivation    |
| GL-AC-CON-010 | Template Contract                      | Final C++ template implementation        | Template contract is future representation candidate, not final code  | GL-CONT-006 / GL-CONT-010 | High     | Check C++ abstractions       |
| GL-AC-CON-011 | Contract Family                        | Implementation package                   | Family groups governance concerns, not filesystem units               | GL-CONT-006               | High     | Check package naming         |
| GL-AC-CON-012 | Ingress Contract Family                | Raw intake path                          | Ingress contract governs prepared/corrected ingress, not raw bypass   | GL-CONT-006 / GL-CONT-004 | Critical | Check ingress implementation |
| GL-AC-CON-013 | Policy / Ecosystem Contract Family     | Policy engine implementation             | Contract family is governance layer, not final engine                 | GL-CONT-006 / GL-CONT-008 | High     | Check policy packages        |
| GL-AC-CON-014 | Metadata / Preparation Contract Family | Metadata storage schema only             | Preparation contract governs assembler-side preparation semantics     | GL-CONT-006 / GL-CONT-008 | High     | Check metadata schema        |
| GL-AC-CON-015 | Registry / Dispatcher Contract Family  | Downstream registry schema               | Registry-facing contract does not own registry internals              | GL-CONT-006 / GL-CONT-009 | Critical | Check database derivation    |
| GL-AC-CON-016 | Exclusion Contract Family              | Optional documentation appendix          | Exclusion contracts are binding authority rules                       | GL-CONT-006 / GL-CONT-009 | Critical | Check scope compliance       |
| GL-AC-CON-017 | Runtime State Contract Family          | Queue implementation only                | Runtime-state contracts govern semantics before implementation        | GL-CONT-006 / GL-CONT-005 | High     | Check runtime code design    |
| GL-AC-CON-018 | Compile-Time Discipline                | Cosmetic C++ naming convention           | Type-safety must preserve architectural meaning                       | GL-CONT-006 / GL-CONT-010 | High     | Check C++ style guides       |
| GL-AC-CON-019 | Template Abstraction Layer             | Concrete processing units                | Abstractions precede concrete units                                   | GL-CONT-006 / GL-CONT-010 | High     | Check roadmap order          |
| GL-AC-CON-020 | CRTP Abstraction                       | Runtime inheritance hierarchy by default | CRTP is static abstraction direction, not runtime OOP by default      | GL-CONT-006 / GL-CONT-010 | Medium   | Check C++ architecture       |
| GL-AC-CON-021 | Contract Compliance                    | Test suite by itself                     | Compliance may inform tests but is not only tests                     | GL-CONT-006 / GL-CONT-010 | Medium   | Check validation planning    |
| GL-AC-CON-022 | Contract Violation                     | Runtime exception only                   | Violation may be architectural, documentation, schema, or code-level  | GL-CONT-006               | Medium   | Check validation model       |

---

## 7.7 Responsibility and Derivation Collapse Rules

|       Rule ID | Protected Term       | Must Not Collapse Into        | Protected Distinction                                                      | Source Pack               | Severity | Validation Use                 |
| ------------: | -------------------- | ----------------------------- | -------------------------------------------------------------------------- | ------------------------- | -------- | ------------------------------ |
| GL-AC-TRC-001 | External Relation    | Internal actor                | Relation identifies boundary interaction, not executing entity             | GL-CONT-007 / GL-CONT-002 | High     | Check relation mapping         |
| GL-AC-TRC-002 | External Relation    | C++ interface                 | Relation must pass through contract before representation                  | GL-CONT-007 / GL-CONT-006 | High     | Check interface derivation     |
| GL-AC-TRC-003 | External Relation    | Capability Candidate          | Relation does not skip contract/responsibility chain                       | GL-CONT-007               | High     | Check derivation chain         |
| GL-AC-TRC-004 | Responsibility       | Class                         | Responsibility is duty/outcome, not class                                  | GL-CONT-007               | Critical | Check class derivation         |
| GL-AC-TRC-005 | Responsibility       | Method or function            | Responsibility may derive functions later but is not one by default        | GL-CONT-007               | Critical | Check function mapping         |
| GL-AC-TRC-006 | Responsibility       | Package                       | Package cannot be invented directly from responsibility                    | GL-CONT-007 / GL-CONT-010 | High     | Check package derivation       |
| GL-AC-TRC-007 | Responsibility       | Runtime algorithm             | Responsibility states required outcome, not final algorithm                | GL-CONT-007               | High     | Check algorithm specs          |
| GL-AC-TRC-008 | Obligation           | Unit test by default          | Obligation is reviewable guarantee; tests may derive later                 | GL-CONT-007               | High     | Check test derivation          |
| GL-AC-TRC-009 | Obligation           | Optional note                 | Obligation is binding reviewable constraint                                | GL-CONT-007               | High     | Check document review          |
| GL-AC-TRC-010 | Delegation           | Package by default            | Delegation assigns responsibility carrier, not package structure           | GL-CONT-007               | High     | Check package mapping          |
| GL-AC-TRC-011 | Delegation           | Whole subsystem by default    | Delegation should target narrow mature carrier where available             | GL-CONT-007 / GL-CONT-003 | High     | Check responsibility ownership |
| GL-AC-TRC-012 | Enablement           | Final implementation          | Enablement prepares capability surface, not final code                     | GL-CONT-007               | High     | Check roadmap stage            |
| GL-AC-TRC-013 | Capability Candidate | Class                         | Candidate may inform class derivation later, not automatically             | GL-CONT-007 / GL-CONT-010 | Critical | Check C++ derivation           |
| GL-AC-TRC-014 | Capability Candidate | Function                      | Candidate is not function-level artifact by default                        | GL-CONT-007               | High     | Check function proposals       |
| GL-AC-TRC-015 | Capability Candidate | Package                       | Candidate is not package by default                                        | GL-CONT-007 / GL-CONT-010 | High     | Check package derivation       |
| GL-AC-TRC-016 | Capability Candidate | Processing Unit               | Processing units are later derivation artifacts                            | GL-CONT-007 / GL-CONT-010 | High     | Check roadmap ordering         |
| GL-AC-TRC-017 | Traceability         | Documentation decoration      | Traceability is governance requirement                                     | GL-CONT-007 / GL-CONT-000 | High     | Check source trace             |
| GL-AC-TRC-018 | Gap Closure          | Feature addition              | Gap closure resolves derivation/coverage gaps, not arbitrary expansion     | GL-CONT-007               | Medium   | Check validation backlog       |
| GL-AC-TRC-019 | Join Key             | Textual similarity            | Joins depend on canonical keys, not names that look similar                | GL-CONT-007 / GL-CONT-000 | High     | Check schema/database design   |
| GL-AC-TRC-020 | ID Namespace         | Global natural-language label | IDs must be interpreted within declared namespace                          | GL-CONT-007 / GL-CONT-000 | High     | Check data modeling            |
| GL-AC-TRC-021 | Responsibility Chain | Optional derivation style     | Chain order is mandatory for implementation derivation                     | GL-CONT-007               | Critical | Check roadmap and C++ packs    |
| GL-AC-TRC-022 | Reviewable Guarantee | Test-only artifact            | Reviewable guarantee may drive review, docs, schema, tests, and compliance | GL-CONT-007               | Medium   | Check QA model                 |

---

## 7.8 Policy, Metadata, Timestamp, and Governance Collapse Rules

|        Rule ID | Protected Term                   | Must Not Collapse Into               | Protected Distinction                                                    | Source Pack               | Severity | Validation Use                     |
| -------------: | -------------------------------- | ------------------------------------ | ------------------------------------------------------------------------ | ------------------------- | -------- | ---------------------------------- |
|  GL-AC-POL-001 | Policy Governance                | Policy engine implementation         | Governance model is not final engine                                     | GL-CONT-008               | High     | Check policy package design        |
|  GL-AC-POL-002 | Policy Governance                | Policy source ownership              | Assembler may govern use, not own external source                        | GL-CONT-008 / GL-CONT-002 | Critical | Check ownership model              |
|  GL-AC-POL-003 | Policy Material                  | PolicyAssigner                       | Material governs behavior; assigner mediates assignment                  | GL-CONT-008               | High     | Check policy chain                 |
|  GL-AC-POL-004 | Policy Material                  | Policy Registry / Policy Source      | Material is supplied by source but not identical to source               | GL-CONT-008 / GL-CONT-002 | High     | Check source/object model          |
|  GL-AC-POL-005 | Policy Material                  | Policy-Consuming Component           | Material is not consuming executor                                       | GL-CONT-008               | High     | Check behavior descriptions        |
|  GL-AC-POL-006 | Policy Object                    | PolicyAssigner                       | Policy object is governed material, not assignment component             | GL-CONT-008 / GL-CONT-004 | High     | Check term use                     |
|  GL-AC-POL-007 | Policy Object                    | Policy-Consuming Component           | Object does not execute policy-governed behavior by itself               | GL-CONT-008               | High     | Check component responsibilities   |
|  GL-AC-POL-008 | Policy Assignment                | Policy Object                        | Assignment relation differs from assigned object                         | GL-CONT-008 / GL-CONT-004 | High     | Check policy model                 |
|  GL-AC-POL-009 | PolicyAssigner                   | Policy Registry / Policy Source      | Internal assignment component differs from external source               | GL-CONT-008 / GL-CONT-002 | High     | Check policy diagrams              |
|  GL-AC-POL-010 | Policy-Consuming Component       | Policy Object                        | Consuming component realizes governed behavior; object is material       | GL-CONT-008               | High     | Check component taxonomy           |
|  GL-AC-POL-011 | Policy-Governed Mechanism        | Policy Object                        | Mechanism behavior is governed by policy; object is not mechanism itself | GL-CONT-008               | Medium   | Check policy semantics             |
|  GL-AC-POL-012 | Policy Host                      | Every preparation component          | Hosting must be explicitly contracted, not assumed                       | GL-CONT-008               | High     | Check host assignments             |
|  GL-AC-POL-013 | Policy Source Non-Ownership      | Weak documentation note              | It is an authority exclusion                                             | GL-CONT-008 / GL-CONT-009 | Critical | Check policy ownership             |
| GL-AC-META-001 | Metadata Preparation             | Policy hosting                       | Metadata preparation is schema/directive-governed by default             | GL-CONT-008               | High     | Check metadata-policy relation     |
| GL-AC-META-002 | Metadata Injector                | Policy Host by default               | Injector is not policy host unless later contract explicitly changes it  | GL-CONT-008 / GL-CONT-003 | High     | Check component roles              |
| GL-AC-META-003 | Metadata Injector                | Metadata Directive Source            | Internal component differs from external directive source                | GL-CONT-008 / GL-CONT-002 | High     | Check source/component distinction |
| GL-AC-META-004 | Metadata Directive               | Policy Object                        | Directive material differs from policy material                          | GL-CONT-008               | High     | Check governance material          |
| GL-AC-META-005 | Schema-Guided Metadata           | Policy-governed behavior by default  | Schema guidance differs from policy execution                            | GL-CONT-008               | Medium   | Check metadata schema              |
| GL-AC-META-006 | Envelope Metadata Block          | Metadata Injector                    | Metadata artifact differs from producing/preparing component             | GL-CONT-008 / GL-CONT-004 | High     | Check envelope object model        |
| GL-AC-TIME-001 | Timestamp Stabilization          | Downstream query-time interpretation | Stabilization is assembler-side pre-dispatch preparation                 | GL-CONT-008               | High     | Check query semantics              |
| GL-AC-TIME-002 | Timestamp Stabilizer             | Registry-side timestamp authority    | Stabilizer does not own downstream timestamp lifecycle                   | GL-CONT-008 / GL-CONT-009 | High     | Check registry claims              |
| GL-AC-TIME-003 | Timestamp Semantics              | Raw timestamp field only             | Semantics include governed interpretation, not just a field              | GL-CONT-008               | Medium   | Check schema derivation            |
| GL-AC-TIME-004 | Envelope Timestamp Block         | Timestamp Stabilizer                 | Artifact differs from preparing component                                | GL-CONT-008 / GL-CONT-004 | High     | Check object/component mapping     |
| GL-AC-TIME-005 | Pre-Dispatch Timestamp Readiness | Downstream acceptance                | Readiness is assembler-side eligibility, not downstream validation       | GL-CONT-008 / GL-CONT-009 | High     | Check dispatch criteria            |
|  GL-AC-GOV-001 | Governance Rule                  | Runtime algorithm                    | Governance constrains; algorithm implements later                        | GL-CONT-008 / GL-CONT-006 | High     | Check implementation derivation    |
|  GL-AC-GOV-002 | Governance Constraint            | Optional advice                      | Constraint is binding within architecture                                | GL-CONT-008               | High     | Check validation matrices          |
|  GL-AC-GOV-003 | Eligibility Rule                 | Downstream acceptance                | Eligibility is assembler-side readiness condition                        | GL-CONT-008 / GL-CONT-009 | High     | Check handoff conditions           |

---

## 7.9 Dispatcher, Handoff, Registry, and Authority Exclusion Collapse Rules

|        Rule ID | Protected Term                 | Must Not Collapse Into               | Protected Distinction                                                     | Source Pack               | Severity | Validation Use                  |
| -------------: | ------------------------------ | ------------------------------------ | ------------------------------------------------------------------------- | ------------------------- | -------- | ------------------------------- |
| GL-AC-DISP-001 | Dispatcher                     | Registry / Delivery Port             | Actor differs from outbound contract surface                              | GL-CONT-009               | Critical | Check handoff path              |
| GL-AC-DISP-002 | Dispatcher                     | Log Level Records Registry           | Dispatcher is assembler-owned actor; registry is downstream               | GL-CONT-009               | Critical | Check component boundaries      |
| GL-AC-DISP-003 | Dispatcher                     | Downstream registry implementation   | Dispatcher does not own registry internals                                | GL-CONT-009               | Critical | Check registry design           |
| GL-AC-DISP-004 | Dispatcher                     | Queue Bundle Agent                   | Runtime coordination actor differs from final handoff actor               | GL-CONT-009 / GL-CONT-003 | High     | Check actor roles               |
| GL-AC-DISP-005 | Dispatcher                     | Dispatching / Delivery Round Manager | Round manager coordinates; Dispatcher hands off                           | GL-CONT-009 / GL-CONT-005 | High     | Check delivery round            |
| GL-AC-DISP-006 | Dispatcher                     | Log Level Envelope                   | Actor differs from carried object                                         | GL-CONT-009 / GL-CONT-004 | Critical | Check object/actor distinction  |
| GL-AC-DISP-007 | Dispatcher                     | Handoff Evidence                     | Actor differs from evidence artifact                                      | GL-CONT-009 / GL-CONT-004 | High     | Check evidence model            |
| GL-AC-DISP-008 | Dispatcher Finality            | Optional optimization rule           | Finality is binding; fast paths must not bypass it                        | GL-CONT-009               | Critical | Check implementation shortcuts  |
| GL-AC-DISP-009 | Dispatcher Finality            | Downstream ownership                 | Finality does not extend ownership after handoff                          | GL-CONT-009               | Critical | Check lifecycle claims          |
| GL-AC-DISP-010 | Dispatcher-Mediated Handoff    | Queue placement                      | Handoff is outbound authority edge, not runtime placement                 | GL-CONT-009 / GL-CONT-005 | Critical | Check flow stages               |
| GL-AC-DISP-011 | Dispatcher-Mediated Handoff    | Registry persistence                 | Handoff does not prove persistence                                        | GL-CONT-009               | Critical | Check persistence claims        |
| GL-AC-DISP-012 | Dispatch Eligibility           | Downstream acceptance                | Eligibility is assembler-side readiness                                   | GL-CONT-009               | High     | Check delivery criteria         |
| GL-AC-DISP-013 | Dispatch Eligibility State     | Handoff Evidence                     | Readiness state differs from trace/evidence artifact                      | GL-CONT-009 / GL-CONT-004 | Medium   | Check dispatch artifacts        |
|  GL-AC-HND-001 | Handoff                        | Downstream lifecycle ownership       | Handoff transfers across boundary; ownership does not return to assembler | GL-CONT-009               | Critical | Check ownership scope           |
|  GL-AC-HND-002 | Valid Handoff                  | Storage lifecycle                    | Valid handoff closes assembler authority; storage is downstream           | GL-CONT-009               | Critical | Check storage language          |
|  GL-AC-HND-003 | Handoff Evidence               | Proof of downstream persistence      | Evidence is assembler-side traceability, not persistence proof            | GL-CONT-009 / GL-CONT-004 | Critical | Check evidence claims           |
|  GL-AC-HND-004 | Handoff Material               | Downstream Registry Record           | Transfer material is not necessarily registry record                      | GL-CONT-009 / GL-CONT-004 | High     | Check handoff schema            |
|  GL-AC-HND-005 | Handoff Trace                  | Downstream lifecycle log             | Trace supports handoff review, not downstream lifecycle authority         | GL-CONT-009               | High     | Check traceability model        |
|  GL-AC-HND-006 | Handoff Boundary               | Database boundary                    | Handoff boundary is authority edge, not database schema boundary          | GL-CONT-009               | High     | Check DB derivation             |
|  GL-AC-HND-007 | Handoff Confirmation           | Full downstream ownership proof      | Confirmation is acknowledgement artifact, not broad lifecycle proof       | GL-CONT-009               | High     | Check downstream integration    |
|  GL-AC-REG-001 | Registry / Delivery Port       | Dispatcher                           | Port cannot replace actor                                                 | GL-CONT-009 / GL-CONT-002 | Critical | Check handoff architecture      |
|  GL-AC-REG-002 | Registry / Delivery Port       | Registry internals                   | Delivery surface is not registry implementation                           | GL-CONT-009               | Critical | Check registry design           |
|  GL-AC-REG-003 | Log Level Records Registry     | Assembler-owned storage              | Registry is downstream and not owned                                      | GL-CONT-009 / GL-CONT-002 | Critical | Check ownership diagrams        |
|  GL-AC-REG-004 | Registry-Facing Delivery       | Database schema ownership            | Delivery relation does not imply DB schema authority                      | GL-CONT-009               | Critical | Check PostgreSQL derivation     |
|  GL-AC-REG-005 | Downstream Registry Record     | Log Level Envelope                   | Registry record differs from assembler-side envelope                      | GL-CONT-009 / GL-CONT-004 | Critical | Check record modeling           |
|  GL-AC-REG-006 | Registry Internals             | Assembler implementation package     | Registry internals are not assembler packages                             | GL-CONT-009 / GL-CONT-010 | Critical | Check package layout            |
|  GL-AC-REG-007 | Registry Admission             | Assembler handoff                    | Admission is downstream action; handoff is assembler boundary action      | GL-CONT-009               | High     | Check boundary semantics        |
|  GL-AC-REG-008 | Registry Persistence           | Handoff Evidence                     | Persistence is downstream; evidence is assembler trace                    | GL-CONT-009               | Critical | Check persistence claims        |
|  GL-AC-EXC-001 | Post-Handoff Non-Ownership     | Optional note                        | Non-ownership is binding authority exclusion                              | GL-CONT-009 / GL-CONT-002 | Critical | Check all downstream references |
|  GL-AC-EXC-002 | Authority Closure              | Temporary state                      | Authority closure is structural boundary rule                             | GL-CONT-009               | Critical | Check lifecycle diagrams        |
|  GL-AC-EXC-003 | Downstream Lifecycle Exclusion | Deferred assembler work              | Exclusion means not owned, not postponed                                  | GL-CONT-009               | Critical | Check roadmap backlog           |
|  GL-AC-EXC-004 | Storage Lifecycle Exclusion    | Future storage module                | Storage lifecycle remains downstream                                      | GL-CONT-009               | Critical | Check implementation scope      |
|  GL-AC-EXC-005 | Query Lifecycle Exclusion      | Future query module                  | Query lifecycle remains outside assembler                                 | GL-CONT-009 / GL-CONT-002 | Critical | Check read-side proposals       |
|  GL-AC-EXC-006 | Replay Exclusion               | Dispatcher responsibility            | Replay is downstream/non-owned                                            | GL-CONT-009               | Critical | Check recovery features         |
|  GL-AC-EXC-007 | Mutation Exclusion             | Post-handoff assembler correction    | Mutation after handoff is excluded                                        | GL-CONT-009               | Critical | Check correction features       |
|  GL-AC-EXC-008 | Indexing Exclusion             | Assembler responsibility             | Indexing is downstream/non-owned                                          | GL-CONT-009               | Critical | Check search/index language     |
|  GL-AC-EXC-009 | Correction Exclusion           | Assembler lifecycle authority        | Correction post-handoff is excluded                                       | GL-CONT-009               | Critical | Check lifecycle model           |
|  GL-AC-EXC-010 | Inspection Exclusion           | Query subsystem authority            | Inspection is downstream/read-side unless separately scoped               | GL-CONT-009               | High     | Check observability language    |
|  GL-AC-EXC-011 | Record Lifecycle Exclusion     | Envelope lifecycle                   | Downstream record lifecycle differs from assembler envelope movement      | GL-CONT-009               | Critical | Check record semantics          |
|  GL-AC-EXC-012 | Downstream Authority           | Assembler authority                  | Downstream owns downstream lifecycle after handoff                        | GL-CONT-009               | Critical | Check authority maps            |

---

## 7.10 C++ Direction, Semantic Domain, and Package Collapse Rules

|       Rule ID | Protected Term                       | Must Not Collapse Into          | Protected Distinction                                                               | Source Pack               | Severity | Validation Use                   |
| ------------: | ------------------------------------ | ------------------------------- | ----------------------------------------------------------------------------------- | ------------------------- | -------- | -------------------------------- |
| GL-AC-CPP-001 | C++17 Implementation Direction       | Final codebase already existing | Direction is future derivation, not current implementation                          | GL-CONT-010               | High     | Check implementation claims      |
| GL-AC-CPP-002 | C++17 Implementation Direction       | License to invent classes first | C++ derivation must follow contracts/responsibilities                               | GL-CONT-010 / GL-CONT-007 | Critical | Check C++ class proposals        |
| GL-AC-CPP-003 | Header-Only First                    | Header-only forever             | Header-first is posture, not permanent restriction                                  | GL-CONT-010               | Medium   | Check C++ build plan             |
| GL-AC-CPP-004 | Header-Only First                    | No build system                 | Header-first does not eliminate CMake candidate                                     | GL-CONT-010               | Medium   | Check build docs                 |
| GL-AC-CPP-005 | Header-Only Kernel                   | Full codebase                   | Kernel candidate is not complete system implementation                              | GL-CONT-010               | High     | Check repository planning        |
| GL-AC-CPP-006 | CMake Candidate                      | Architecture source             | Build tooling must not define architecture                                          | GL-CONT-010               | High     | Check build-first planning       |
| GL-AC-CPP-007 | Modern C++ Type Discipline           | Naming convention               | Type discipline preserves contract meaning                                          | GL-CONT-010 / GL-CONT-006 | High     | Check coding standards           |
| GL-AC-CPP-008 | Static Abstraction                   | Concrete processing unit        | Abstraction precedes concrete realization                                           | GL-CONT-010 / GL-CONT-006 | High     | Check processing-unit derivation |
| GL-AC-CPP-009 | Static Polymorphism                  | Dispatcher                      | Static polymorphism is C++ representation strategy, not runtime handoff actor       | GL-CONT-010 / GL-CONT-009 | Medium   | Check C++ diagrams               |
| GL-AC-CPP-010 | Concept-Like Pattern                 | C++20 concept requirement       | Pattern is C++17-oriented concept-like discipline, not necessarily language feature | GL-CONT-010               | Medium   | Check language-version claims    |
| GL-AC-CPP-011 | Trait-Based Representation           | Contract itself                 | Trait may represent contract later; it does not define original contract            | GL-CONT-010 / GL-CONT-006 | High     | Check contract traits            |
| GL-AC-CPP-012 | Compile-Time Contract Representation | Runtime validation replacement  | Compile-time representation does not remove architectural validation needs          | GL-CONT-010 / GL-CONT-006 | Medium   | Check validation plan            |
| GL-AC-DOM-001 | Semantic Domain                      | Technical folder                | Domain derives from meaning, not folder convenience                                 | GL-CONT-010               | Critical | Check package derivation         |
| GL-AC-DOM-002 | Semantic Domain                      | Package by default              | Domain informs package; it is not automatically package                             | GL-CONT-010               | High     | Check domain/package map         |
| GL-AC-DOM-003 | Semantic Domain Boundary             | Filesystem boundary             | Domain boundary is semantic/authority/dependency boundary                           | GL-CONT-010               | High     | Check repo layout                |
| GL-AC-DOM-004 | Domain Dependency Direction          | Include order only              | Dependency direction is architectural, not just compilation order                   | GL-CONT-010               | High     | Check package dependencies       |
| GL-AC-DOM-005 | Technical Folder                     | Semantic Domain                 | Technical folder is implementation container, not meaning source                    | GL-CONT-010               | Critical | Check filesystem design          |
| GL-AC-DOM-006 | Technical Folder Fallacy             | Acceptable package derivation   | Folder-based domain derivation is explicitly guarded against                        | GL-CONT-010               | Critical | Check roadmap gates              |
| GL-AC-DER-001 | Future Derivation                    | Current implementation          | Future derivation is not present code                                               | GL-CONT-010               | High     | Check status labels              |
| GL-AC-DER-002 | Derivation Gate                      | Optional milestone              | Gate controls valid progression                                                     | GL-CONT-010               | High     | Check roadmap phase exits        |
| GL-AC-DER-003 | Architecture Freeze                  | Implementation freeze           | Architecture freeze precedes implementation freeze                                  | GL-CONT-010 / GL-CONT-001 | High     | Check milestone definitions      |
| GL-AC-DER-004 | C++ Abstraction Derivation           | Concrete class writing          | Abstraction derives before concrete units                                           | GL-CONT-010 / GL-CONT-006 | High     | Check implementation order       |
| GL-AC-DER-005 | Abstract C++ Layer                   | Final package layout            | Abstract layer may inform package, but is not package                               | GL-CONT-010               | High     | Check C++ layer model            |
| GL-AC-DER-006 | Processing Unit Candidate            | Concrete Processing Unit        | Candidate differs from finalized implementation unit                                | GL-CONT-010               | High     | Check roadmap artifacts          |
| GL-AC-DER-007 | Concrete Processing Unit             | Feature idea                    | Processing unit must be derived from responsibility chain                           | GL-CONT-010 / GL-CONT-007 | Critical | Check unit derivation            |
| GL-AC-DER-008 | Package Candidate                    | Final package                   | Candidate is not frozen package                                                     | GL-CONT-010               | High     | Check package docs               |
| GL-AC-DER-009 | Filesystem Representation            | Architecture                    | Filesystem represents architecture; it does not define it                           | GL-CONT-010               | Critical | Check repo layout                |
| GL-AC-DER-010 | Repository Layout                    | Semantic model                  | Layout follows semantic model, not vice versa                                       | GL-CONT-010               | High     | Check repository design          |
| GL-AC-DER-011 | Implementation Artifact              | Source of meaning               | Implementation artifacts must preserve glossary/contract meaning                    | GL-CONT-010 / GL-CONT-000 | High     | Check code review                |
| GL-AC-DER-012 | Compliance Matrix                    | Test suite by itself            | Compliance matrix may drive tests but is broader than test suite                    | GL-CONT-010               | Medium   | Check QA artifacts               |
| GL-AC-DER-013 | Test Derivation                      | Obligation itself               | Tests derive from obligations; they do not replace obligations                      | GL-CONT-010 / GL-CONT-007 | Medium   | Check test plans                 |
| GL-AC-DER-014 | Example Derivation                   | Normative implementation        | Examples illustrate; they do not define architecture                                | GL-CONT-010               | Medium   | Check examples                   |
| GL-AC-DER-015 | Implementation Freeze                | Architecture Freeze             | Implementation freeze comes after architecture-derived artifacts stabilize          | GL-CONT-010               | High     | Check release gates              |

---

# 8. High-Priority Critical Rule Subset

The following subset should be treated as always-on validation gates.

|        Rule ID | Critical Rule                                                                       |
| -------------: | ----------------------------------------------------------------------------------- |
|   GL-AC-ID-001 | Assembler System must not become the full logging system                            |
|   GL-AC-ID-002 | Assembler System must not become the full messaging system                          |
|   GL-AC-ID-003 | Assembler System must not become the downstream registry                            |
|  GL-AC-BND-012 | Registry / Delivery Port must not replace Dispatcher                                |
|  GL-AC-BND-019 | Post-Handoff Non-Ownership is not optional                                          |
|  GL-AC-ENT-005 | Envelope Assembler must not collapse into Log Level Envelope                        |
|  GL-AC-ENT-010 | Dispatcher must not collapse into Registry / Delivery Port                          |
|  GL-AC-OBJ-004 | Log Level Envelope must not collapse into raw payload                               |
|  GL-AC-OBJ-008 | Log Level Envelope must not collapse into downstream registry record                |
|  GL-AC-RUN-001 | Queue Container must not collapse into message broker                               |
|  GL-AC-RUN-013 | Envelope Slot Occupancy must not collapse into envelope lifecycle ownership         |
|  GL-AC-CON-001 | Contract must not collapse into C++ interface by default                            |
|  GL-AC-TRC-004 | Responsibility must not collapse into class                                         |
|  GL-AC-TRC-013 | Capability Candidate must not collapse into class                                   |
|  GL-AC-POL-006 | Policy Object must not collapse into PolicyAssigner                                 |
| GL-AC-META-002 | Metadata Injector must not become Policy Host by default                            |
| GL-AC-TIME-001 | Timestamp Stabilization must not collapse into downstream query-time interpretation |
| GL-AC-DISP-010 | Dispatcher-Mediated Handoff must not collapse into queue placement                  |
|  GL-AC-HND-001 | Handoff must not create downstream lifecycle ownership                              |
|  GL-AC-HND-003 | Handoff Evidence must not prove downstream persistence                              |
|  GL-AC-REG-004 | Registry-Facing Delivery must not imply database schema ownership                   |
|  GL-AC-EXC-003 | Downstream Lifecycle Exclusion must not be treated as deferred assembler work       |
|  GL-AC-DOM-001 | Semantic Domain must not collapse into technical folder                             |
|  GL-AC-DER-009 | Filesystem Representation must not define architecture                              |

---

# 9. Validation Application Model

## 9.1 Documentation Review

During documentation review, each new document should be checked against this index.

|           Record ID | Review Target              | Required Check                                                     |
| ------------------: | -------------------------- | ------------------------------------------------------------------ |
| GL-CONS-002-REV-001 | README / Overview          | No identity or boundary collapse                                   |
| GL-CONS-002-REV-002 | Vision / Scope             | No downstream ownership leakage                                    |
| GL-CONS-002-REV-003 | System Goals               | Goals preserve anti-collapse rules                                 |
| GL-CONS-002-REV-004 | Roadmap                    | Roadmap phases do not skip derivation gates                        |
| GL-CONS-002-REV-005 | Glossary Entries           | Each major term preserves “must not be confused with” rules        |
| GL-CONS-002-REV-006 | C++ Derivation Packs       | Classes/packages do not precede contract/responsibility derivation |
| GL-CONS-002-REV-007 | Database / Schema Packs    | Database records do not merge distinct term categories             |
| GL-CONS-002-REV-008 | Runtime Design Packs       | Queues remain containers, not brokers                              |
| GL-CONS-002-REV-009 | Dispatcher / Handoff Packs | Handoff does not imply downstream lifecycle ownership              |

## 9.2 Future Validator Rules

A future validator may use the following checks.

|           Record ID | Validator Rule                   | Description                                                                     |
| ------------------: | -------------------------------- | ------------------------------------------------------------------------------- |
| GL-CONS-002-VAL-001 | Category Pair Check              | Detect invalid pairings such as actor/object or port/actor collapse             |
| GL-CONS-002-VAL-002 | Ownership Scope Check            | Detect assembler-owned labels applied to downstream records                     |
| GL-CONS-002-VAL-003 | Authority Closure Check          | Detect post-handoff assembler ownership claims                                  |
| GL-CONS-002-VAL-004 | Implementation Prematurity Check | Detect classes/packages/functions derived without responsibility chain          |
| GL-CONS-002-VAL-005 | Runtime Doctrine Check           | Detect broker/storage language attached to queue containers                     |
| GL-CONS-002-VAL-006 | Policy Governance Check          | Detect policy object/executor/source collapse                                   |
| GL-CONS-002-VAL-007 | Metadata Governance Check        | Detect Metadata Injector being treated as policy host by default                |
| GL-CONS-002-VAL-008 | Timestamp Scope Check            | Detect timestamp stabilization being treated as downstream query interpretation |
| GL-CONS-002-VAL-009 | Domain Derivation Check          | Detect semantic domains created from folder names only                          |
| GL-CONS-002-VAL-010 | Alias Integrity Check            | Detect aliases becoming hidden separate canonical terms                         |

---

# 10. Future Database Readiness

## 10.1 Suggested Table Grain

If this index is later represented in a database, the row grain should be:

```text id="gl-cons-002-db-grain"
One anti-collapse rule per row.
```

## 10.2 Suggested Relational Columns

| Column                   | Meaning                                                                                         |
| ------------------------ | ----------------------------------------------------------------------------------------------- |
| `rule_id`                | Stable anti-collapse rule identifier                                                            |
| `protected_term_id`      | Optional canonical term ID                                                                      |
| `protected_term`         | Human-readable protected term                                                                   |
| `must_not_collapse_into` | Prohibited target term/category/artifact                                                        |
| `protected_distinction`  | Explanation of preserved distinction                                                            |
| `rule_family`            | Identity, boundary, actor, object, runtime, contract, traceability, policy, handoff, derivation |
| `source_pack`            | GL-CONT source pack                                                                             |
| `severity`               | Critical / High / Medium / Low                                                                  |
| `validation_use`         | How validators should apply the rule                                                            |
| `derivation_impact`      | What breaks if rule is violated                                                                 |
| `status`                 | active / deprecated / superseded                                                                |
| `notes`                  | Optional consolidation notes                                                                    |

## 10.3 Suggested JSON Shape

```json id="gl-cons-002-json-shape"
{
  "rule_id": "GL-AC-OBJ-004",
  "protected_term": "Log Level Envelope",
  "must_not_collapse_into": "Raw Payload / Raw Content",
  "protected_distinction": "Envelope is prepared authoritative carrier; raw content is pre-envelope material.",
  "rule_family": "object_carrier_collapse",
  "source_pack": "GL-CONT-004",
  "severity": "critical",
  "validation_use": "Check ingestion and runtime transport language.",
  "status": "active"
}
```

---

# 11. Exit Criteria

|            Record ID | Exit Criterion                                                             | Status   |
| -------------------: | -------------------------------------------------------------------------- | -------- |
| GL-CONS-002-EXIT-001 | Identity anti-collapse rules are consolidated                              | Complete |
| GL-CONS-002-EXIT-002 | Boundary and authority anti-collapse rules are consolidated                | Complete |
| GL-CONS-002-EXIT-003 | Actor/entity anti-collapse rules are consolidated                          | Complete |
| GL-CONS-002-EXIT-004 | Object/carrier anti-collapse rules are consolidated                        | Complete |
| GL-CONS-002-EXIT-005 | Runtime anti-collapse rules are consolidated                               | Complete |
| GL-CONS-002-EXIT-006 | Contract/type-safety anti-collapse rules are consolidated                  | Complete |
| GL-CONS-002-EXIT-007 | Responsibility/derivation anti-collapse rules are consolidated             | Complete |
| GL-CONS-002-EXIT-008 | Policy/metadata/timestamp anti-collapse rules are consolidated             | Complete |
| GL-CONS-002-EXIT-009 | Dispatcher/handoff/registry/exclusion anti-collapse rules are consolidated | Complete |
| GL-CONS-002-EXIT-010 | C++/semantic-domain/package anti-collapse rules are consolidated           | Complete |
| GL-CONS-002-EXIT-011 | High-priority critical subset is identified                                | Complete |
| GL-CONS-002-EXIT-012 | Future validation and database readiness model is defined                  | Complete |

---

# 12. Summary

`GL-CONS-002_AntiCollapse_Index_Consolidation.md` establishes the anti-collapse rule index for the Assembler System glossary workstream.

It does not merge the glossary entries.

It preserves the governing distinctions that future documentation, schemas, databases, packages, C++ abstractions, and validation systems must respect.

The core protected doctrine is:

```text id="gl-cons-002-summary-doctrine"
System identity must not expand into adjacent systems.
Boundary surfaces must not become actors.
Ports must not replace responsibility carriers.
Actors must not become carrier objects.
Carrier objects must not become producers or downstream records.
Queues must remain containers, not brokers.
Contracts must remain architectural laws before code.
Responsibilities must not become classes, packages, or functions directly.
Policy objects must not become policy executors.
Metadata preparation must not become policy hosting by default.
Timestamp stabilization must not become downstream query interpretation.
Dispatcher must remain the final assembler-side outbound actor.
Handoff must not create downstream lifecycle ownership.
Evidence must not prove downstream persistence.
C++ direction must not become final code prematurely.
Semantic domains must not be derived from technical folders.
Filesystem representation must not define architecture.
```

Recommended next artifact:

```text id="gl-cons-002-next"
GL-CONS-003_SourceTrace_Index_Consolidation.md
```

```
```
