
# GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| GL-CONT-008-DOC-001 | Pack Name | GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack |
| GL-CONT-008-DOC-002 | Parent Workstream | Glossary Workstream |
| GL-CONT-008-DOC-003 | Project | Assembler System |
| GL-CONT-008-DOC-004 | Document Type | Content Definition Pack |
| GL-CONT-008-DOC-005 | Status | Formal Draft V1 |
| GL-CONT-008-DOC-006 | Language | English |
| GL-CONT-008-DOC-007 | Depends On | GL-CONT-000, GL-CONT-001, GL-CONT-002, GL-CONT-003, GL-CONT-004, GL-CONT-005, GL-CONT-006, GL-CONT-007 |
| GL-CONT-008-DOC-008 | Scope | Policy terms, policy-object terms, policy-assignment terms, policy-consuming terms, metadata-preparation terms, timestamp-stabilization terms, governance terms |
| GL-CONT-008-DOC-009 | Excluded From This Pack | Final policy engine implementation, downstream policy lifecycle, database schema, query-time timestamp interpretation, final metadata serialization schema, final C++ class layout |
| GL-CONT-008-DOC-010 | Enables | GL-CONT-009, GL-CONT-010, policy-governance derivation, metadata/preparation contract derivation, timestamp contract derivation, compliance matrix derivation |

---

## 2. Pack Purpose

### 2.1 Purpose Statement

This pack defines the canonical glossary entries for policy, metadata, timestamp, and governance terminology in the Assembler System.

It answers the question:

```text
How does the Assembler System govern policy material, metadata preparation,
and timestamp stabilization without collapsing policy sources, policy objects,
policy assignment, policy-consuming components, metadata directives,
metadata injection, timestamp preparation, or downstream query interpretation?
````

The pack protects the architecture from confusing:

1. policy material with policy execution,
2. policy source with PolicyAssigner,
3. Policy Object with policy-consuming component,
4. Policy Assignment with Policy Object,
5. Metadata Injector with policy host,
6. Metadata Directive Source with Metadata Injector,
7. Timestamp Stabilizer with downstream query interpretation,
8. assembler-side preparation with downstream lifecycle ownership.

### 2.2 Pack Position

This pack follows:

1. `GL-CONT-000 — Glossary Governance & Entry Model Pack`,
2. `GL-CONT-001 — Core System Identity & Phase Terms Pack`,
3. `GL-CONT-002 — Boundary, Authority, and External Context Terms Pack`,
4. `GL-CONT-003 — Internal Actors and Delegated Entities Pack`,
5. `GL-CONT-004 — Governed Objects, Carriers, and Envelope Terms Pack`,
6. `GL-CONT-005 — Runtime, Queue, Slot, and Round Terms Pack`,
7. `GL-CONT-006 — Contracts, Templates, Type-Safety, and Contract Families Pack`,
8. `GL-CONT-007 — Responsibility, Obligation, Delegation, Enablement, and Capability Terms Pack`.

It precedes:

1. `GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack`,
2. `GL-CONT-010 — C++ Implementation Direction, Semantic Domains, and Future Derivation Terms Pack`.

### 2.3 Pack-Level Policy Rule

```text id="gl-cont-008-policy-rule"
Policy material governs behavior.
PolicyAssigner mediates policy assignment.
Policy-consuming components realize policy-governed mechanisms.
Policy Object itself is not the actor that executes behavior.
```

### 2.4 Pack-Level Metadata Rule

```text id="gl-cont-008-metadata-rule"
Metadata Injector is schema/directive-governed.
It must not be treated as a policy host unless a later formal contract
explicitly changes that status.
```

### 2.5 Pack-Level Timestamp Rule

```text id="gl-cont-008-timestamp-rule"
Timestamp Stabilizer performs assembler-side timestamp stabilization before
dispatch eligibility.
It must not be treated as downstream query-time timestamp interpretation,
storage lifecycle ownership, or registry-side timestamp authority.
```

### 2.6 Pack-Level Governance Rule

```text id="gl-cont-008-governance-rule"
Governance terms constrain meaning, eligibility, assignment, preparation,
and validation.
They must not be collapsed into runtime algorithms, implementation packages,
or downstream lifecycle ownership.
```

---

## 3. Term Inventory

|           Record ID | Term ID     | Canonical Term                    | Family      | Category                                                               | Ownership Scope                        | Entry Maturity    |
| ------------------: | ----------- | --------------------------------- | ----------- | ---------------------------------------------------------------------- | -------------------------------------- | ----------------- |
| GL-CONT-008-INV-001 | GL-POL-001  | Policy Governance                 | POL         | governance_model                                                       | governed                               | canonical_full    |
| GL-CONT-008-INV-002 | GL-POL-002  | Policy Material                   | POL / OBJ   | governed_object / policy_material                                      | external_supplied / assembler_governed | canonical_full    |
| GL-CONT-008-INV-003 | GL-POL-003  | Policy Object                     | POL / OBJ   | governed_object / policy_material                                      | external_supplied / assembler_governed | canonical_full    |
| GL-CONT-008-INV-004 | GL-POL-004  | Policy Assignment                 | POL / OBJ   | assignment_relation / governed_object                                  | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-005 | GL-POL-005  | PolicyAssigner                    | POL / ENT   | delegated_entity / policy_assignment_component                         | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-006 | GL-POL-006  | Policy Registry / Policy Source   | POL / EXT   | external_context / policy_source                                       | external / not_owned                   | canonical_full    |
| GL-CONT-008-INV-007 | GL-POL-007  | Policy-Consuming Component        | POL / ENT   | policy_consuming_component                                             | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-008 | GL-POL-008  | Policy-Governed Mechanism         | POL         | governed_mechanism                                                     | assembler_owned / governed             | canonical_full    |
| GL-CONT-008-INV-009 | GL-POL-009  | Policy Host                       | POL         | mechanism_host                                                         | governed                               | canonical_partial |
| GL-CONT-008-INV-010 | GL-POL-010  | Policy Source Non-Ownership       | POL / EXC   | authority_exclusion / anti_collapse_guard                              | not_owned                              | canonical_full    |
| GL-CONT-008-INV-011 | GL-META-001 | Metadata Preparation              | POL / OBJ   | preparation_concept                                                    | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-012 | GL-META-002 | Metadata Injector                 | ENT / POL   | supporting_entity / preparation_component                              | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-013 | GL-META-003 | Metadata Directive Source         | EXT / POL   | external_context / directive_source                                    | external / not_owned                   | canonical_full    |
| GL-CONT-008-INV-014 | GL-META-004 | Metadata Directive                | POL / OBJ   | governed_object / directive_material                                   | external_supplied / assembler_governed | canonical_full    |
| GL-CONT-008-INV-015 | GL-META-005 | Schema-Guided Metadata            | POL / OBJ   | metadata_artifact / governance_model                                   | governed                               | canonical_full    |
| GL-CONT-008-INV-016 | GL-META-006 | Directive-Driven Metadata         | POL / OBJ   | metadata_artifact / governance_model                                   | governed                               | canonical_full    |
| GL-CONT-008-INV-017 | GL-META-007 | Envelope Metadata Block           | OBJ / POL   | governed_object / metadata_artifact                                    | assembler_owned                        | canonical_partial |
| GL-CONT-008-INV-018 | GL-TIME-001 | Timestamp Stabilization           | POL / OBJ   | preparation_concept / timestamp_semantics                              | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-019 | GL-TIME-002 | Timestamp Stabilizer              | ENT / POL   | supporting_entity / preparation_component / policy_consuming_component | assembler_owned                        | canonical_full    |
| GL-CONT-008-INV-020 | GL-TIME-003 | Timestamp Semantics               | POL / OBJ   | governed_semantics                                                     | governed                               | canonical_full    |
| GL-CONT-008-INV-021 | GL-TIME-004 | Envelope Timestamp Block          | OBJ / POL   | governed_object / timestamp_artifact                                   | assembler_owned                        | canonical_partial |
| GL-CONT-008-INV-022 | GL-TIME-005 | Pre-Dispatch Timestamp Readiness  | POL / RUN   | readiness_state / preparation_concept                                  | assembler_owned                        | canonical_partial |
| GL-CONT-008-INV-023 | GL-GOV-001  | Governance Rule                   | GUARD / POL | doctrine / governance_rule                                             | governed                               | canonical_full    |
| GL-CONT-008-INV-024 | GL-GOV-002  | Governance Constraint             | GUARD / POL | constraint                                                             | governed                               | canonical_full    |
| GL-CONT-008-INV-025 | GL-GOV-003  | Eligibility Rule                  | GUARD / POL | validation_concept / governance_rule                                   | governed                               | canonical_partial |
| GL-CONT-008-INV-026 | GL-GOV-004  | Preparation Governance            | POL / CON   | governance_model / preparation_concept                                 | governed                               | canonical_full    |
| GL-CONT-008-INV-027 | GL-GOV-005  | Policy / Ecosystem Governance     | POL / CON   | governance_model / contract_family_context                             | governed                               | canonical_full    |
| GL-CONT-008-INV-028 | GL-GOV-006  | Metadata / Preparation Governance | POL / CON   | governance_model / contract_family_context                             | governed                               | canonical_full    |

---

## 4. Canonical Term Entries

---

### GL-POL-001 — Policy Governance

| Field           | Value             |
| --------------- | ----------------- |
| Term ID         | GL-POL-001        |
| Canonical Term  | Policy Governance |
| Family          | POL               |
| Category        | governance_model  |
| Ownership Scope | governed          |
| Entry Maturity  | canonical_full    |
| Evidence Status | direct / derived  |

#### Definition

Policy Governance is the assembler-side governance model that controls how policy material is received, represented, assigned, consumed, hosted, or excluded within the Assembler System.

It defines the rules that preserve the distinction between policy source, policy object, policy assignment, policy-consuming component, and policy-governed mechanism.

#### Architectural Role

Policy Governance protects policy semantics from category collapse.

It governs:

1. external policy-source relation,
2. policy material identity,
3. Policy Object handling,
4. Policy Assignment,
5. PolicyAssigner responsibility,
6. eligible policy-consuming components,
7. policy-governed mechanisms,
8. exclusion of non-policy-hosted components,
9. policy-source non-ownership,
10. downstream policy lifecycle exclusion.

Policy Governance does not make the Assembler own the policy source.

It does not make Policy Object an actor.

It does not make every preparation component a policy host.

#### Must Not Be Confused With

1. Policy engine implementation.
2. Policy source ownership.
3. Downstream policy lifecycle.
4. Metadata directive governance.
5. Metadata Injector behavior by default.
6. Runtime algorithm.
7. Final C++ policy package.

#### Valid Usage

* “Policy Governance preserves Policy Object and PolicyAssigner separation.”
* “Policy Governance determines eligible policy-consuming components.”
* “Policy Governance does not make Metadata Injector policy-hosted.”

#### Invalid Usage

* “Policy Governance means Assembler owns the policy registry.”
* “Policy Governance turns Policy Object into an executor.”
* “Policy Governance is the final policy engine.”
* “Policy Governance means all components consume policies.”

#### Related Terms

* GL-POL-002 — Policy Material
* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment
* GL-POL-005 — PolicyAssigner
* GL-POL-007 — Policy-Consuming Component
* GL-POL-008 — Policy-Governed Mechanism

#### Source Trace

| Source Type     | Source                                                                       |
| --------------- | ---------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Policy governance goals preserve policy-object and policy-host distinctions. |
| GL-CONT-003     | Defines PolicyAssigner and Policy-Consuming Component.                       |
| GL-CONT-004     | Defines Policy Object and Policy Assignment as governed objects.             |
| GL-CONT-006     | Defines Policy / Ecosystem Contract Family.                                  |

---

### GL-POL-002 — Policy Material

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-POL-002                             |
| Canonical Term  | Policy Material                        |
| Family          | POL / OBJ                              |
| Category        | governed_object / policy_material      |
| Ownership Scope | external_supplied / assembler_governed |
| Entry Maturity  | canonical_full                         |
| Evidence Status | derived                                |

#### Definition

Policy Material is governed material supplied by an external policy source or represented inside assembler-side policy governance.

It may be embodied as a `Policy Object`.

Policy Material governs behavior but does not execute behavior by itself.

#### Architectural Role

Policy Material is the abstract content of policy governance.

It can be received, referenced, assigned, carried, or interpreted under policy contracts.

It supports:

1. policy assignment,
2. policy-consuming behavior,
3. validation behavior where policy-governed,
4. timestamp behavior where policy-governed,
5. runtime behavior where policy-governed,
6. dispatch eligibility behavior where policy-governed.

Policy Material remains distinct from the component that consumes or executes policy-governed behavior.

#### Must Not Be Confused With

1. PolicyAssigner.
2. Policy Registry / Policy Source.
3. Policy-Consuming Component.
4. Policy Host.
5. Runtime executor.
6. Metadata Directive.
7. Metadata Injector.

#### Valid Usage

* “Policy Material may be supplied by a Policy Registry / Policy Source.”
* “Policy Material may be represented as Policy Object.”
* “Policy Material governs behavior but does not execute behavior.”

#### Invalid Usage

* “Policy Material is the PolicyAssigner.”
* “Policy Material is the policy source.”
* “Policy Material executes validation by itself.”
* “Policy Material is the same thing as metadata directive.”

#### Related Terms

* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment
* GL-POL-006 — Policy Registry / Policy Source
* GL-POL-007 — Policy-Consuming Component
* GL-META-004 — Metadata Directive

#### Source Trace

| Source Type     | Source                                                                                                                   |
| --------------- | ------------------------------------------------------------------------------------------------------------------------ |
| GL-CONT-004     | Policy Object is governed policy material supplied by a policy source or represented inside policy assignment semantics. |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs policy-source and policy-assignment interactions.                             |
| SYSTEM_GOALS.md | Policy Object must remain distinct from policy-consuming component.                                                      |

---

### GL-POL-003 — Policy Object

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-POL-003                             |
| Canonical Term  | Policy Object                          |
| Family          | POL / OBJ                              |
| Category        | governed_object / policy_material      |
| Ownership Scope | external_supplied / assembler_governed |
| Entry Maturity  | canonical_full                         |
| Evidence Status | direct / derived                       |

#### Definition

A Policy Object is governed policy material supplied by a policy source or represented inside assembler-side policy assignment semantics.

It governs behavior but does not execute behavior by itself.

#### Architectural Role

Policy Object is the concrete policy-material object recognized by the Assembler System.

It may be assigned to eligible policy-consuming components through `PolicyAssigner`.

The policy chain is:

```text id="gl-pol-003-policy-chain"
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

Policy Object remains an object.

It is not the PolicyAssigner.

It is not the policy source.

It is not the consuming component.

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

* GL-POL-002 — Policy Material
* GL-POL-004 — Policy Assignment
* GL-POL-005 — PolicyAssigner
* GL-POL-006 — Policy Registry / Policy Source
* GL-POL-007 — Policy-Consuming Component

#### Source Trace

| Source Type     | Source                                                                                      |
| --------------- | ------------------------------------------------------------------------------------------- |
| GL-CONT-004     | Defines Policy Object as a governed object and policy material.                             |
| GL-CONT-003     | PolicyAssigner mediates assignment to policy-consuming components.                          |
| SYSTEM_GOALS.md | Policy governance goals distinguish policy object from consuming component and policy host. |

---

### GL-POL-004 — Policy Assignment

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-POL-004                            |
| Canonical Term  | Policy Assignment                     |
| Family          | POL / OBJ                             |
| Category        | assignment_relation / governed_object |
| Ownership Scope | assembler_owned                       |
| Entry Maturity  | canonical_full                        |
| Evidence Status | direct / derived                      |

#### Definition

Policy Assignment is the governed association between a Policy Object and an eligible policy-consuming component or policy-governed mechanism.

#### Architectural Role

Policy Assignment expresses which Policy Object applies to which eligible behavior, component, or mechanism.

It is mediated by `PolicyAssigner`.

Policy Assignment is not the policy object itself.

It is not the policy source.

It is not the component consuming the policy.

It is the governed relation between policy material and eligible consumption.

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
* “Policy Assignment does not make the Policy Object an actor.”

#### Invalid Usage

* “Policy Assignment is the Policy Object.”
* “Policy Assignment is the policy source.”
* “Policy Assignment executes the policy.”
* “Policy Assignment means every component becomes policy-hosted.”

#### Related Terms

* GL-POL-003 — Policy Object
* GL-POL-005 — PolicyAssigner
* GL-POL-007 — Policy-Consuming Component
* GL-POL-008 — Policy-Governed Mechanism
* GL-POL-009 — Policy Host

#### Source Trace

| Source Type | Source                                                                                                       |
| ----------- | ------------------------------------------------------------------------------------------------------------ |
| GL-CONT-004 | Defines Policy Assignment as governed association between Policy Object and eligible component or mechanism. |
| GL-CONT-003 | PolicyAssigner is responsible for mediating policy assignment semantics.                                     |
| GL-CONT-006 | Policy / Ecosystem Contract Family governs policy assignment interactions.                                   |

---

### GL-POL-005 — PolicyAssigner

| Field           | Value                                          |
| --------------- | ---------------------------------------------- |
| Term ID         | GL-POL-005                                     |
| Canonical Term  | PolicyAssigner                                 |
| Family          | POL / ENT                                      |
| Category        | delegated_entity / policy_assignment_component |
| Ownership Scope | assembler_owned                                |
| Entry Maturity  | canonical_full                                 |
| Evidence Status | direct                                         |

#### Definition

PolicyAssigner is the assembler-side delegated entity responsible for mediating policy assignment semantics between Policy Objects and eligible policy-consuming components.

#### Architectural Role

PolicyAssigner preserves the distinction between:

1. policy source,
2. policy material,
3. Policy Object,
4. Policy Assignment,
5. policy-consuming component,
6. policy-governed mechanism,
7. policy host.

PolicyAssigner does not become the policy source.

It does not become the policy object.

It does not automatically execute every policy-governed mechanism.

It mediates assignment.

#### Must Not Be Confused With

1. Policy Registry / Policy Source.
2. Policy Object.
3. Policy-consuming component.
4. Policy Host.
5. Metadata Injector.
6. Validator.
7. Dispatcher.
8. Administrative / Ecosystem Port.

#### Valid Usage

* “PolicyAssigner mediates Policy Assignment.”
* “PolicyAssigner assigns Policy Objects to eligible policy-consuming components.”
* “PolicyAssigner is not the Policy Registry / Policy Source.”

#### Invalid Usage

* “PolicyAssigner is the policy source.”
* “PolicyAssigner is the Policy Object.”
* “PolicyAssigner executes every policy-governed mechanism.”
* “PolicyAssigner replaces Administrative / Ecosystem Port.”

#### Related Terms

* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment
* GL-POL-006 — Policy Registry / Policy Source
* GL-POL-007 — Policy-Consuming Component
* GL-POL-008 — Policy-Governed Mechanism

#### Source Trace

| Source Type     | Source                                                                                                       |
| --------------- | ------------------------------------------------------------------------------------------------------------ |
| GL-CONT-003     | Defines PolicyAssigner as assembler-side delegated entity for policy assignment.                             |
| GL-CONT-004     | Policy Object and Policy Assignment are governed objects, not actors.                                        |
| SYSTEM_GOALS.md | Policy governance goals preserve PolicyAssigner, Policy Object, and policy-consuming component distinctions. |

---

### GL-POL-006 — Policy Registry / Policy Source

| Field           | Value                            |
| --------------- | -------------------------------- |
| Term ID         | GL-POL-006                       |
| Canonical Term  | Policy Registry / Policy Source  |
| Family          | POL / EXT                        |
| Category        | external_context / policy_source |
| Ownership Scope | external / not_owned             |
| Entry Maturity  | canonical_full                   |
| Evidence Status | direct                           |

#### Definition

Policy Registry / Policy Source is the external policy source that supplies policy material or policy-governance input to the Assembler System.

It is not an internal assembler actor.

It is not owned by the Assembler System.

#### Architectural Role

Policy Registry / Policy Source defines the external origin of policy material.

It may supply or reference:

1. Policy Objects,
2. policy bundles,
3. policy directives,
4. policy-governance material,
5. eligibility constraints,
6. behavior-governing policy material.

The Assembler may receive, interpret, or assign policy material under its own boundary and contract rules.

The Assembler does not own the external policy source lifecycle.

#### Must Not Be Confused With

1. PolicyAssigner.
2. Policy Object.
3. Policy Assignment.
4. Policy-consuming component.
5. Administrative / Ecosystem Port.
6. Metadata Directive Source.
7. Downstream policy lifecycle.

#### Valid Usage

* “Policy Registry / Policy Source supplies policy material.”
* “PolicyAssigner is not the policy source.”
* “Policy source lifecycle is external to the Assembler.”

#### Invalid Usage

* “Policy Registry / Policy Source is an internal actor.”
* “Policy Registry / Policy Source is the PolicyAssigner.”
* “Assembler owns policy-source lifecycle.”
* “Policy source and metadata directive source are always the same thing.”

#### Related Terms

* GL-EXT-003 — Policy Registry / Policy Source
* GL-BND-007 — Administrative / Ecosystem Port
* GL-POL-002 — Policy Material
* GL-POL-003 — Policy Object
* GL-POL-010 — Policy Source Non-Ownership

#### Source Trace

| Source Type     | Source                                                                |
| --------------- | --------------------------------------------------------------------- |
| GL-CONT-002     | Defines Policy Registry / Policy Source as external context.          |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs policy-source interaction. |
| SYSTEM_GOALS.md | Boundary and policy goals preserve external/internal separation.      |

---

### GL-POL-007 — Policy-Consuming Component

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-POL-007                 |
| Canonical Term  | Policy-Consuming Component |
| Family          | POL / ENT                  |
| Category        | policy_consuming_component |
| Ownership Scope | assembler_owned            |
| Entry Maturity  | canonical_full             |
| Evidence Status | direct / derived           |

#### Definition

A Policy-Consuming Component is an assembler-side component or entity that is eligible to realize policy-governed behavior under an assigned Policy Object.

It consumes policy material as governance input but does not become the policy object or policy source.

#### Architectural Role

Policy-Consuming Component identifies eligible components that may behave according to assigned policy.

Examples may include:

1. Validator,
2. Timestamp Stabilizer,
3. policy-governed runtime participant,
4. policy-governed dispatch-readiness participant,
5. other eligible components defined by future contract families.

Metadata Injector is explicitly not a policy host by default.

A component may be policy-consuming only if a contract or governance rule makes it eligible.

#### Must Not Be Confused With

1. Policy Object.
2. PolicyAssigner.
3. Policy Registry / Policy Source.
4. Policy Host by default.
5. Metadata Injector by default.
6. Generic internal actor.
7. Downstream policy executor.

#### Valid Usage

* “Validator may be a policy-consuming component where validation is policy-governed.”
* “Timestamp Stabilizer may consume policy where timestamp behavior is policy-governed.”
* “Policy-consuming component remains distinct from Policy Object.”

#### Invalid Usage

* “Every component is policy-consuming by default.”
* “Policy-consuming component is the Policy Object.”
* “Policy-consuming component owns the policy source.”
* “Metadata Injector is policy-hosted by default.”

#### Related Terms

* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment
* GL-POL-005 — PolicyAssigner
* GL-POL-008 — Policy-Governed Mechanism
* GL-POL-009 — Policy Host
* GL-META-002 — Metadata Injector

#### Source Trace

| Source Type     | Source                                                                                                                        |
| --------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| GL-CONT-003     | Defines Policy-Consuming Component and identifies Validator and Timestamp Stabilizer eligibility.                             |
| SYSTEM_GOALS.md | Policy-consuming component table includes eligible participants and excludes Metadata Injector from policy-hosting semantics. |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs eligible policy-consuming components.                                              |

---

### GL-POL-008 — Policy-Governed Mechanism

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-POL-008                 |
| Canonical Term  | Policy-Governed Mechanism  |
| Family          | POL                        |
| Category        | governed_mechanism         |
| Ownership Scope | assembler_owned / governed |
| Entry Maturity  | canonical_full             |
| Evidence Status | derived                    |

#### Definition

A Policy-Governed Mechanism is a behavior, decision, readiness condition, validation path, or preparation path whose operation is constrained or shaped by an assigned Policy Object.

#### Architectural Role

Policy-Governed Mechanism is the behavior side of policy consumption.

It may govern:

1. validation behavior,
2. timestamp behavior,
3. dispatch eligibility behavior,
4. runtime readiness behavior,
5. policy-specific preparation path,
6. policy-bound contract interpretation.

The mechanism may be realized by a policy-consuming component.

The mechanism is not the policy object.

It is not the policy source.

It is not automatically a final runtime algorithm.

#### Must Not Be Confused With

1. Policy Object.
2. Policy Assignment.
3. PolicyAssigner.
4. Policy Registry / Policy Source.
5. Final implementation algorithm.
6. Metadata directive.
7. Downstream policy lifecycle.

#### Valid Usage

* “Validation may be a policy-governed mechanism.”
* “Policy-governed mechanism is realized by a policy-consuming component.”
* “A policy-governed mechanism must remain traceable to Policy Assignment.”

#### Invalid Usage

* “Policy-Governed Mechanism is the Policy Object.”
* “Policy-Governed Mechanism owns the policy source.”
* “Policy-Governed Mechanism is automatically a C++ class.”
* “Policy-Governed Mechanism replaces contract governance.”

#### Related Terms

* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment
* GL-POL-007 — Policy-Consuming Component
* GL-CON-006 — Policy / Ecosystem Contract Family
* GL-TRC-010 — Traceability

#### Source Trace

| Source Type     | Source                                                                                          |
| --------------- | ----------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Policy governance goals distinguish policy object, assignment, consumer, and mechanism hosting. |
| GL-CONT-003     | Policy-consuming components realize policy-governed mechanisms.                                 |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs policy-governed interactions.                        |

---

### GL-POL-009 — Policy Host

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-POL-009                 |
| Canonical Term  | Policy Host                |
| Family          | POL                        |
| Category        | mechanism_host             |
| Ownership Scope | governed                   |
| Entry Maturity  | canonical_partial          |
| Evidence Status | derived / needs_validation |

#### Definition

A Policy Host is a component or mechanism location that is explicitly allowed to host policy-governed behavior under a governing contract.

Policy Host is not a default status for every internal component.

#### Architectural Role

Policy Host marks where policy-governed mechanism execution may be hosted.

It is a stronger term than policy-consuming eligibility.

A component may consume policy for a specific behavior without being generalized into a broad policy host unless the contract says so.

Metadata Injector is explicitly not a policy host by default.

#### Must Not Be Confused With

1. Policy Object.
2. PolicyAssigner.
3. Policy Registry / Policy Source.
4. Policy-consuming component by default.
5. Metadata Injector.
6. Generic behavior executor.
7. Downstream policy engine.

#### Valid Usage

* “A Policy Host must be explicitly authorized by a contract.”
* “Policy Host status is not automatic.”
* “Metadata Injector is not policy-hosted by default.”

#### Invalid Usage

* “Every policy-consuming component is a Policy Host.”
* “Policy Host is the policy source.”
* “Policy Host is the Policy Object.”
* “Metadata Injector is automatically a Policy Host.”

#### Related Terms

* GL-POL-007 — Policy-Consuming Component
* GL-POL-008 — Policy-Governed Mechanism
* GL-POL-004 — Policy Assignment
* GL-META-002 — Metadata Injector
* GL-CON-006 — Policy / Ecosystem Contract Family

#### Source Trace

| Source Type     | Source                                                                           |
| --------------- | -------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Metadata Injector is excluded from policy-hosting semantics.                     |
| GL-CONT-003     | Metadata Injector is schema/directive-governed and explicitly not a policy host. |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs policy-hosting distinctions.          |

---

### GL-POL-010 — Policy Source Non-Ownership

| Field           | Value                                     |
| --------------- | ----------------------------------------- |
| Term ID         | GL-POL-010                                |
| Canonical Term  | Policy Source Non-Ownership               |
| Family          | POL / EXC                                 |
| Category        | authority_exclusion / anti_collapse_guard |
| Ownership Scope | not_owned                                 |
| Entry Maturity  | canonical_full                            |
| Evidence Status | derived                                   |

#### Definition

Policy Source Non-Ownership is the authority exclusion rule stating that the Assembler System may consume, reference, or assign policy material without owning the external policy source or its lifecycle.

#### Architectural Role

Policy Source Non-Ownership protects boundary discipline.

It prevents Assembler policy governance from expanding into:

1. policy registry implementation,
2. external policy lifecycle,
3. policy-source mutation,
4. policy-source storage,
5. downstream policy management,
6. global policy administration.

The Assembler owns policy assignment semantics inside its boundary.

It does not own the external policy source.

#### Must Not Be Confused With

1. Policy Governance.
2. Policy Assignment.
3. Policy Object handling.
4. PolicyAssigner responsibility.
5. Administrative / Ecosystem Port ownership.
6. Downstream policy lifecycle.

#### Valid Usage

* “Policy Source Non-Ownership prevents Assembler from becoming the policy registry.”
* “Assembler may assign Policy Objects without owning the source.”
* “Policy source lifecycle remains external.”

#### Invalid Usage

* “Policy assignment means policy source ownership.”
* “Assembler can mutate policy source records.”
* “Policy Source Non-Ownership prevents policy assignment entirely.”
* “Policy source is internal by default.”

#### Related Terms

* GL-POL-006 — Policy Registry / Policy Source
* GL-POL-005 — PolicyAssigner
* GL-POL-004 — Policy Assignment
* GL-BND-004 — Authority Boundary
* GL-EXC-001 — Post-Handoff Non-Ownership

#### Source Trace

| Source Type     | Source                                                                                    |
| --------------- | ----------------------------------------------------------------------------------------- |
| GL-CONT-002     | External context terms place Policy Registry / Policy Source outside assembler ownership. |
| SYSTEM_GOALS.md | Boundary and authority goals prevent expansion into external/downstream ownership.        |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs interaction without ownership transfer.        |

---

### GL-META-001 — Metadata Preparation

| Field           | Value                |
| --------------- | -------------------- |
| Term ID         | GL-META-001          |
| Canonical Term  | Metadata Preparation |
| Family          | POL / OBJ            |
| Category        | preparation_concept  |
| Ownership Scope | assembler_owned      |
| Entry Maturity  | canonical_full       |
| Evidence Status | direct / derived     |

#### Definition

Metadata Preparation is the assembler-side preparation activity that applies schema-guided or directive-driven metadata semantics to accepted content or envelope preparation paths.

#### Architectural Role

Metadata Preparation is part of write-side preparation.

It may contribute to the `Log Level Envelope` through an `Envelope Metadata Block` or equivalent governed metadata artifact.

It is governed by metadata directives, schema expectations, or preparation contracts.

Metadata Preparation is not policy assignment by default.

Metadata Preparation is not downstream registry metadata lifecycle.

#### Must Not Be Confused With

1. Policy assignment.
2. Policy hosting.
3. Metadata Directive Source.
4. Downstream registry metadata mutation.
5. Query-time metadata interpretation.
6. Storage schema ownership.
7. Generic annotation.

#### Valid Usage

* “Metadata Preparation is assembler-side preparation.”
* “Metadata Preparation may be schema-guided or directive-driven.”
* “Metadata Preparation can contribute to Envelope Metadata Block.”

#### Invalid Usage

* “Metadata Preparation is policy hosting.”
* “Metadata Preparation owns downstream metadata lifecycle.”
* “Metadata Preparation is query-time interpretation.”
* “Metadata Preparation bypasses envelope assembly.”

#### Related Terms

* GL-META-002 — Metadata Injector
* GL-META-003 — Metadata Directive Source
* GL-META-004 — Metadata Directive
* GL-META-005 — Schema-Guided Metadata
* GL-META-006 — Directive-Driven Metadata
* GL-META-007 — Envelope Metadata Block

#### Source Trace

| Source Type     | Source                                                                  |
| --------------- | ----------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Metadata and timestamp goals preserve preparation semantics.            |
| GL-CONT-003     | Metadata Injector applies metadata directives and is not policy-hosted. |
| GL-CONT-006     | Metadata / Preparation Contract Family governs metadata preparation.    |

---

### GL-META-002 — Metadata Injector

| Field           | Value                                     |
| --------------- | ----------------------------------------- |
| Term ID         | GL-META-002                               |
| Canonical Term  | Metadata Injector                         |
| Family          | ENT / POL                                 |
| Category        | supporting_entity / preparation_component |
| Ownership Scope | assembler_owned                           |
| Entry Maturity  | canonical_full                            |
| Evidence Status | direct                                    |

#### Definition

Metadata Injector is the assembler-side preparation component that applies schema-guided or directive-driven metadata preparation to accepted content or envelope preparation paths.

#### Architectural Role

Metadata Injector supports envelope preparation.

It may be composed by the Envelope Assembler where metadata preparation is required.

It is schema/directive-governed.

It is explicitly not a policy host by default.

Metadata Injector does not own the Metadata Directive Source.

It does not own downstream registry metadata lifecycle.

#### Must Not Be Confused With

1. Metadata Directive Source.
2. Metadata Directive.
3. PolicyAssigner.
4. Policy Object.
5. Policy Host.
6. Policy-consuming component by default.
7. Envelope Assembler itself.
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

* GL-META-001 — Metadata Preparation
* GL-META-003 — Metadata Directive Source
* GL-META-004 — Metadata Directive
* GL-META-007 — Envelope Metadata Block
* GL-POL-009 — Policy Host
* GL-ENT-001 — Envelope Assembler

#### Source Trace

| Source Type     | Source                                                                                           |
| --------------- | ------------------------------------------------------------------------------------------------ |
| GL-CONT-003     | Metadata Injector applies metadata directives and is not a policy host.                          |
| SYSTEM_GOALS.md | SG-META and policy-governance goals distinguish Metadata Injector from policy-hosting semantics. |
| GL-CONT-006     | Metadata / Preparation Contract Family governs metadata preparation.                             |

---

### GL-META-003 — Metadata Directive Source

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-META-003                         |
| Canonical Term  | Metadata Directive Source           |
| Family          | EXT / POL                           |
| Category        | external_context / directive_source |
| Ownership Scope | external / not_owned                |
| Entry Maturity  | canonical_full                      |
| Evidence Status | direct                              |

#### Definition

Metadata Directive Source is the external source that supplies schema-guided or directive-driven metadata input to the Assembler System.

It is not the Metadata Injector.

It is not a policy source by default.

It is not owned by the Assembler System.

#### Architectural Role

Metadata Directive Source provides metadata directives or metadata-governance input.

The Assembler may receive or apply directives through its governed preparation path.

The source remains external.

Metadata Directive Source supports metadata preparation but does not become the internal component that applies metadata.

#### Must Not Be Confused With

1. Metadata Injector.
2. Metadata Directive.
3. Policy Registry / Policy Source by default.
4. PolicyAssigner.
5. Policy Object.
6. Downstream metadata registry.
7. Envelope Metadata Block.

#### Valid Usage

* “Metadata Directive Source supplies metadata directives.”
* “Metadata Injector applies directives; the source supplies them.”
* “Metadata Directive Source remains external.”

#### Invalid Usage

* “Metadata Directive Source is the Metadata Injector.”
* “Metadata Directive Source is always the Policy Registry / Policy Source.”
* “Metadata Directive Source is assembler-owned.”
* “Metadata Directive Source owns envelope metadata lifecycle inside Assembler.”

#### Related Terms

* GL-META-002 — Metadata Injector
* GL-META-004 — Metadata Directive
* GL-META-005 — Schema-Guided Metadata
* GL-META-006 — Directive-Driven Metadata
* GL-BND-007 — Administrative / Ecosystem Port

#### Source Trace

| Source Type     | Source                                                                                  |
| --------------- | --------------------------------------------------------------------------------------- |
| GL-CONT-002     | Defines Metadata Directive Source as external context.                                  |
| GL-CONT-003     | Metadata Injector is distinct from Metadata Directive Source.                           |
| SYSTEM_GOALS.md | Metadata goals distinguish metadata directive governance from policy-hosting semantics. |

---

### GL-META-004 — Metadata Directive

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-META-004                            |
| Canonical Term  | Metadata Directive                     |
| Family          | POL / OBJ                              |
| Category        | governed_object / directive_material   |
| Ownership Scope | external_supplied / assembler_governed |
| Entry Maturity  | canonical_full                         |
| Evidence Status | derived                                |

#### Definition

A Metadata Directive is governed directive material that instructs or constrains metadata preparation inside the Assembler System.

It may be supplied by a Metadata Directive Source and applied by Metadata Injector under metadata/preparation governance.

#### Architectural Role

Metadata Directive expresses how metadata should be prepared.

It may govern:

1. metadata fields,
2. metadata shape,
3. metadata eligibility,
4. metadata enrichment,
5. metadata normalization,
6. metadata preservation,
7. metadata block preparation.

A Metadata Directive is not the source.

It is not the injector.

It is not a Policy Object by default.

#### Must Not Be Confused With

1. Metadata Directive Source.
2. Metadata Injector.
3. Policy Object by default.
4. Policy Assignment.
5. Envelope Metadata Block.
6. Downstream metadata record.
7. Query metadata filter.

#### Valid Usage

* “Metadata Directive guides metadata preparation.”
* “Metadata Injector applies Metadata Directives.”
* “Metadata Directive may contribute to Envelope Metadata Block.”

#### Invalid Usage

* “Metadata Directive is the Metadata Injector.”
* “Metadata Directive is the external source.”
* “Metadata Directive is automatically Policy Object.”
* “Metadata Directive owns downstream metadata lifecycle.”

#### Related Terms

* GL-META-003 — Metadata Directive Source
* GL-META-002 — Metadata Injector
* GL-META-005 — Schema-Guided Metadata
* GL-META-006 — Directive-Driven Metadata
* GL-META-007 — Envelope Metadata Block

#### Source Trace

| Source Type     | Source                                                               |
| --------------- | -------------------------------------------------------------------- |
| GL-CONT-003     | Metadata Injector applies metadata directives.                       |
| GL-CONT-006     | Metadata / Preparation Contract Family governs metadata preparation. |
| SYSTEM_GOALS.md | Metadata goals preserve schema/directive governance.                 |

---

### GL-META-005 — Schema-Guided Metadata

| Field           | Value                                |
| --------------- | ------------------------------------ |
| Term ID         | GL-META-005                          |
| Canonical Term  | Schema-Guided Metadata               |
| Family          | POL / OBJ                            |
| Category        | metadata_artifact / governance_model |
| Ownership Scope | governed                             |
| Entry Maturity  | canonical_full                       |
| Evidence Status | derived                              |

#### Definition

Schema-Guided Metadata is metadata prepared according to a defined schema, structural expectation, or contract-shaped metadata model.

#### Architectural Role

Schema-Guided Metadata ensures that metadata preparation is not arbitrary.

It supports:

1. metadata shape discipline,
2. envelope metadata consistency,
3. contract-based metadata validation,
4. future typed metadata representation,
5. traceability of metadata semantics.

Schema-Guided Metadata is part of assembler-side preparation.

It does not imply database schema ownership.

It does not imply downstream registry schema ownership.

#### Must Not Be Confused With

1. Database schema.
2. Downstream registry schema.
3. Policy Object.
4. Metadata Directive Source.
5. Metadata Injector.
6. Query index schema.
7. Final serialization format by default.

#### Valid Usage

* “Metadata preparation may be schema-guided.”
* “Schema-Guided Metadata supports typed envelope metadata.”
* “Schema-Guided Metadata remains assembler-side preparation.”

#### Invalid Usage

* “Schema-Guided Metadata means Assembler owns database schema.”
* “Schema-Guided Metadata is the Metadata Injector.”
* “Schema-Guided Metadata is automatically a downstream registry field.”
* “Schema-Guided Metadata is policy hosting.”

#### Related Terms

* GL-META-001 — Metadata Preparation
* GL-META-002 — Metadata Injector
* GL-META-004 — Metadata Directive
* GL-META-007 — Envelope Metadata Block
* GL-CON-007 — Metadata / Preparation Contract Family

#### Source Trace

| Source Type     | Source                                                                         |
| --------------- | ------------------------------------------------------------------------------ |
| GL-CONT-003     | Metadata Injector is schema/directive-governed.                                |
| GL-CONT-006     | Metadata / Preparation Contract Family governs metadata/preparation contracts. |
| SYSTEM_GOALS.md | Metadata goals preserve metadata preparation semantics.                        |

---

### GL-META-006 — Directive-Driven Metadata

| Field           | Value                                |
| --------------- | ------------------------------------ |
| Term ID         | GL-META-006                          |
| Canonical Term  | Directive-Driven Metadata            |
| Family          | POL / OBJ                            |
| Category        | metadata_artifact / governance_model |
| Ownership Scope | governed                             |
| Entry Maturity  | canonical_full                       |
| Evidence Status | derived                              |

#### Definition

Directive-Driven Metadata is metadata prepared according to explicit metadata directives supplied through an approved source or governed boundary path.

#### Architectural Role

Directive-Driven Metadata preserves the distinction between:

1. directive material,
2. directive source,
3. metadata application component,
4. metadata result,
5. downstream metadata lifecycle.

It supports assembler-side metadata preparation without collapsing into policy governance or downstream metadata ownership.

#### Must Not Be Confused With

1. Metadata Directive Source.
2. Metadata Directive itself.
3. Metadata Injector.
4. Policy Object.
5. Policy Assignment.
6. Downstream registry metadata.
7. Query-time metadata interpretation.

#### Valid Usage

* “Metadata preparation may be directive-driven.”
* “Directive-Driven Metadata depends on approved metadata directives.”
* “Directive-Driven Metadata remains distinct from policy assignment.”

#### Invalid Usage

* “Directive-Driven Metadata is policy assignment.”
* “Directive-Driven Metadata owns downstream metadata records.”
* “Directive-Driven Metadata is the external directive source.”
* “Directive-Driven Metadata makes Metadata Injector policy-hosted.”

#### Related Terms

* GL-META-003 — Metadata Directive Source
* GL-META-004 — Metadata Directive
* GL-META-002 — Metadata Injector
* GL-META-007 — Envelope Metadata Block
* GL-META-005 — Schema-Guided Metadata

#### Source Trace

| Source Type     | Source                                                                          |
| --------------- | ------------------------------------------------------------------------------- |
| GL-CONT-003     | Metadata Injector applies metadata directives and is schema/directive-governed. |
| SYSTEM_GOALS.md | Metadata goals preserve directive-governed preparation.                         |
| GL-CONT-006     | Metadata / Preparation Contract Family governs directive-driven preparation.    |

---

### GL-META-007 — Envelope Metadata Block

| Field           | Value                               |
| --------------- | ----------------------------------- |
| Term ID         | GL-META-007                         |
| Canonical Term  | Envelope Metadata Block             |
| Family          | OBJ / POL                           |
| Category        | governed_object / metadata_artifact |
| Ownership Scope | assembler_owned                     |
| Entry Maturity  | canonical_partial                   |
| Evidence Status | derived / seed_low_detail           |

#### Definition

Envelope Metadata Block is the governed metadata artifact, block, or section associated with a prepared Log Level Envelope.

It represents the metadata result of assembler-side metadata preparation where such a block is required by contract.

#### Architectural Role

Envelope Metadata Block may carry:

1. schema-guided metadata,
2. directive-driven metadata,
3. metadata preparation result,
4. metadata trace material,
5. metadata eligibility state,
6. future typed metadata representation.

It is part of the envelope carrier’s governed material.

It is not the Metadata Injector.

It is not the Metadata Directive Source.

It is not downstream registry metadata lifecycle.

#### Must Not Be Confused With

1. Metadata Injector.
2. Metadata Directive Source.
3. Metadata Directive.
4. Policy Object.
5. Downstream Registry Record.
6. Query index metadata.
7. Database metadata schema.

#### Valid Usage

* “Envelope Metadata Block may carry prepared metadata.”
* “Metadata Injector may contribute to Envelope Metadata Block.”
* “Envelope Metadata Block is part of governed envelope material.”

#### Invalid Usage

* “Envelope Metadata Block is the Metadata Injector.”
* “Envelope Metadata Block owns downstream metadata lifecycle.”
* “Envelope Metadata Block is a policy host.”
* “Envelope Metadata Block is automatically a database schema.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-META-001 — Metadata Preparation
* GL-META-002 — Metadata Injector
* GL-META-005 — Schema-Guided Metadata
* GL-META-006 — Directive-Driven Metadata

#### Source Trace

| Source Type | Source                                                                       |
| ----------- | ---------------------------------------------------------------------------- |
| GL-CONT-004 | Identifies Envelope Metadata Block as a governed object / metadata artifact. |
| GL-CONT-003 | Metadata Injector supports metadata preparation in envelope assembly paths.  |
| GL-CONT-006 | Metadata / Preparation Contract Family may govern metadata block behavior.   |

---

### GL-TIME-001 — Timestamp Stabilization

| Field           | Value                                     |
| --------------- | ----------------------------------------- |
| Term ID         | GL-TIME-001                               |
| Canonical Term  | Timestamp Stabilization                   |
| Family          | POL / OBJ                                 |
| Category        | preparation_concept / timestamp_semantics |
| Ownership Scope | assembler_owned                           |
| Entry Maturity  | canonical_full                            |
| Evidence Status | direct / derived                          |

#### Definition

Timestamp Stabilization is the assembler-side preparation activity of stabilizing timestamp semantics before dispatch eligibility.

It ensures that timestamp meaning is prepared before the envelope may become eligible for dispatcher-mediated handoff.

#### Architectural Role

Timestamp Stabilization is part of write-side preparation.

It may contribute to:

1. Envelope Timestamp Block,
2. dispatch eligibility state,
3. preparation readiness,
4. policy-governed timestamp behavior,
5. timestamp traceability,
6. future typed timestamp contracts.

Timestamp Stabilization is not downstream query timestamp interpretation.

It is not storage lifecycle timestamp management.

It is not downstream registry timestamp ownership.

#### Must Not Be Confused With

1. Metadata Injection.
2. Downstream query timestamp interpretation.
3. Storage timestamp lifecycle.
4. Registry timestamp mutation.
5. Generic wall-clock capture.
6. Dispatch itself.
7. Handoff evidence by itself.

#### Valid Usage

* “Timestamp Stabilization occurs before dispatch eligibility.”
* “Timestamp Stabilization is assembler-side preparation.”
* “Timestamp Stabilization may be policy-governed where contracts allow.”

#### Invalid Usage

* “Timestamp Stabilization executes downstream queries.”
* “Timestamp Stabilization owns storage timestamp lifecycle.”
* “Timestamp Stabilization is the Dispatcher.”
* “Timestamp Stabilization occurs after downstream registry handoff.”

#### Related Terms

* GL-TIME-002 — Timestamp Stabilizer
* GL-TIME-003 — Timestamp Semantics
* GL-TIME-004 — Envelope Timestamp Block
* GL-TIME-005 — Pre-Dispatch Timestamp Readiness
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type     | Source                                                                                    |
| --------------- | ----------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Timestamp goals require timestamp semantics to be stabilized before dispatch eligibility. |
| GL-CONT-003     | Timestamp Stabilizer stabilizes timestamp semantics before dispatch eligibility.          |
| GL-CONT-006     | Metadata / Preparation Contract Family governs timestamp stabilization as preparation.    |

---

### GL-TIME-002 — Timestamp Stabilizer

| Field           | Value                                                                  |
| --------------- | ---------------------------------------------------------------------- |
| Term ID         | GL-TIME-002                                                            |
| Canonical Term  | Timestamp Stabilizer                                                   |
| Family          | ENT / POL                                                              |
| Category        | supporting_entity / preparation_component / policy_consuming_component |
| Ownership Scope | assembler_owned                                                        |
| Entry Maturity  | canonical_full                                                         |
| Evidence Status | direct                                                                 |

#### Definition

Timestamp Stabilizer is the assembler-side preparation component that stabilizes timestamp semantics before dispatch eligibility.

It may be eligible as a policy-consuming component when timestamp behavior is policy-governed.

#### Architectural Role

Timestamp Stabilizer participates in accepted ingress and envelope preparation paths.

It may be composed by the Envelope Assembler where timestamp stabilization is required.

It may consume policy where policy-governed timestamp behavior is explicitly assigned.

It remains a preparation component.

It is not downstream query interpretation.

It is not storage timestamp lifecycle owner.

#### Must Not Be Confused With

1. Metadata Injector.
2. Metadata Directive Source.
3. Downstream query timestamp interpretation.
4. Dispatcher.
5. Log Level Envelope.
6. Policy Object.
7. Storage timestamp lifecycle.
8. Registry timestamp ownership.

#### Valid Usage

* “Timestamp Stabilizer stabilizes timestamp semantics before dispatch eligibility.”
* “Timestamp Stabilizer may participate in Envelope Assembler composition.”
* “Timestamp Stabilizer may be policy-consuming where timestamp behavior is policy-governed.”

#### Invalid Usage

* “Timestamp Stabilizer executes downstream queries.”
* “Timestamp Stabilizer owns storage lifecycle timestamps.”
* “Timestamp Stabilizer is the Metadata Injector.”
* “Timestamp Stabilizer is a raw payload source.”

#### Related Terms

* GL-TIME-001 — Timestamp Stabilization
* GL-TIME-003 — Timestamp Semantics
* GL-TIME-004 — Envelope Timestamp Block
* GL-POL-007 — Policy-Consuming Component
* GL-ENT-001 — Envelope Assembler

#### Source Trace

| Source Type     | Source                                                                                         |
| --------------- | ---------------------------------------------------------------------------------------------- |
| GL-CONT-003     | Defines Timestamp Stabilizer as preparation component and policy-consuming eligible component. |
| SYSTEM_GOALS.md | Timestamp semantics must be stabilized before dispatch eligibility.                            |
| GL-CONT-006     | Metadata / Preparation Contract Family governs timestamp preparation.                          |

---

### GL-TIME-003 — Timestamp Semantics

| Field           | Value               |
| --------------- | ------------------- |
| Term ID         | GL-TIME-003         |
| Canonical Term  | Timestamp Semantics |
| Family          | POL / OBJ           |
| Category        | governed_semantics  |
| Ownership Scope | governed            |
| Entry Maturity  | canonical_full      |
| Evidence Status | derived             |

#### Definition

Timestamp Semantics is the governed meaning of timestamp-related information inside assembler-side preparation.

It defines what timestamp information means before dispatch eligibility.

#### Architectural Role

Timestamp Semantics provides meaning to timestamp preparation.

It may govern:

1. event time meaning,
2. ingestion time meaning,
3. preparation time meaning,
4. stabilization status,
5. timestamp provenance,
6. timestamp eligibility,
7. timestamp block interpretation inside the envelope.

Timestamp Semantics is prepared before handoff.

It does not define downstream query interpretation after handoff.

#### Must Not Be Confused With

1. Raw wall-clock value.
2. Downstream query timestamp interpretation.
3. Storage timestamp lifecycle.
4. Registry timestamp mutation.
5. Metadata preparation by default.
6. Dispatch time by default.
7. Handoff evidence by itself.

#### Valid Usage

* “Timestamp Semantics must be stabilized before dispatch eligibility.”
* “Timestamp Semantics may be carried in Envelope Timestamp Block.”
* “Timestamp Semantics belongs to assembler-side preparation.”

#### Invalid Usage

* “Timestamp Semantics means downstream query semantics.”
* “Timestamp Semantics is only a raw timestamp value.”
* “Timestamp Semantics is owned by downstream registry after handoff.”
* “Timestamp Semantics replaces dispatch eligibility.”

#### Related Terms

* GL-TIME-001 — Timestamp Stabilization
* GL-TIME-002 — Timestamp Stabilizer
* GL-TIME-004 — Envelope Timestamp Block
* GL-TIME-005 — Pre-Dispatch Timestamp Readiness
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type     | Source                                                                             |
| --------------- | ---------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Timestamp semantics must be stabilized before dispatch eligibility.                |
| GL-CONT-003     | Timestamp Stabilizer stabilizes timestamp semantics in accepted preparation paths. |
| GL-CONT-004     | Envelope Timestamp Block is a governed timestamp artifact.                         |

---

### GL-TIME-004 — Envelope Timestamp Block

| Field           | Value                                |
| --------------- | ------------------------------------ |
| Term ID         | GL-TIME-004                          |
| Canonical Term  | Envelope Timestamp Block             |
| Family          | OBJ / POL                            |
| Category        | governed_object / timestamp_artifact |
| Ownership Scope | assembler_owned                      |
| Entry Maturity  | canonical_partial                    |
| Evidence Status | derived / seed_low_detail            |

#### Definition

Envelope Timestamp Block is the governed timestamp artifact, block, or section associated with a prepared Log Level Envelope.

It represents timestamp semantics prepared by assembler-side timestamp stabilization where such a block is required by contract.

#### Architectural Role

Envelope Timestamp Block may carry:

1. stabilized timestamp semantics,
2. timestamp provenance,
3. timestamp readiness state,
4. timestamp preparation result,
5. policy-governed timestamp indicators,
6. future typed timestamp representation.

It is part of the envelope’s governed material.

It is not the Timestamp Stabilizer.

It is not downstream query interpretation.

It is not registry-side timestamp lifecycle ownership.

#### Must Not Be Confused With

1. Timestamp Stabilizer.
2. Timestamp Stabilization.
3. Downstream query timestamp interpretation.
4. Storage timestamp lifecycle.
5. Downstream Registry Record.
6. Handoff Evidence by default.
7. Dispatch time by default.

#### Valid Usage

* “Envelope Timestamp Block may carry stabilized timestamp semantics.”
* “Timestamp Stabilizer may contribute to Envelope Timestamp Block.”
* “Envelope Timestamp Block is a governed timestamp artifact.”

#### Invalid Usage

* “Envelope Timestamp Block stabilizes itself.”
* “Envelope Timestamp Block executes query-time timestamp logic.”
* “Envelope Timestamp Block owns storage timestamp lifecycle.”
* “Envelope Timestamp Block replaces Dispatcher handoff evidence.”

#### Related Terms

* GL-OBJ-001 — Log Level Envelope
* GL-TIME-001 — Timestamp Stabilization
* GL-TIME-002 — Timestamp Stabilizer
* GL-TIME-003 — Timestamp Semantics
* GL-TIME-005 — Pre-Dispatch Timestamp Readiness

#### Source Trace

| Source Type     | Source                                                                        |
| --------------- | ----------------------------------------------------------------------------- |
| GL-CONT-004     | Identifies Envelope Timestamp Block as a governed timestamp artifact.         |
| GL-CONT-003     | Timestamp Stabilizer participates in preparation before dispatch eligibility. |
| SYSTEM_GOALS.md | Timestamp goals preserve pre-dispatch timestamp stabilization.                |

---

### GL-TIME-005 — Pre-Dispatch Timestamp Readiness

| Field           | Value                                 |
| --------------- | ------------------------------------- |
| Term ID         | GL-TIME-005                           |
| Canonical Term  | Pre-Dispatch Timestamp Readiness      |
| Family          | POL / RUN                             |
| Category        | readiness_state / preparation_concept |
| Ownership Scope | assembler_owned                       |
| Entry Maturity  | canonical_partial                     |
| Evidence Status | derived                               |

#### Definition

Pre-Dispatch Timestamp Readiness is the assembler-side readiness condition indicating that timestamp semantics have been sufficiently stabilized for the envelope to participate in dispatch eligibility evaluation.

#### Architectural Role

Pre-Dispatch Timestamp Readiness bridges timestamp preparation and dispatch eligibility.

It may contribute to:

1. Dispatch Eligibility State,
2. readiness checks,
3. policy-governed timestamp constraints,
4. handoff eligibility,
5. future compliance matrix validation.

It is not final dispatch.

It is not handoff evidence by itself.

It is not downstream timestamp interpretation.

#### Must Not Be Confused With

1. Dispatcher action.
2. Handoff Evidence.
3. Downstream query timestamp readiness.
4. Registry admission.
5. Storage lifecycle timestamp.
6. Queue slot occupancy.
7. Delivery confirmation.

#### Valid Usage

* “Pre-Dispatch Timestamp Readiness supports dispatch eligibility.”
* “Timestamp semantics must be stabilized before pre-dispatch readiness passes.”
* “Pre-Dispatch Timestamp Readiness is assembler-side.”

#### Invalid Usage

* “Pre-Dispatch Timestamp Readiness is final handoff.”
* “Pre-Dispatch Timestamp Readiness proves downstream registry persistence.”
* “Pre-Dispatch Timestamp Readiness is query readiness.”
* “Pre-Dispatch Timestamp Readiness owns timestamp lifecycle after handoff.”

#### Related Terms

* GL-TIME-001 — Timestamp Stabilization
* GL-TIME-003 — Timestamp Semantics
* GL-OBJ-015 — Dispatch Eligibility State
* GL-ENT-002 — Dispatcher
* GL-OBJ-008 — Handoff Evidence

#### Source Trace

| Source Type     | Source                                                                                          |
| --------------- | ----------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Timestamp semantics must be stabilized before dispatch eligibility.                             |
| GL-CONT-004     | Dispatch Eligibility State is a governed readiness artifact.                                    |
| GL-CONT-006     | Registry / Dispatcher and Metadata / Preparation contract families govern readiness boundaries. |

---

### GL-GOV-001 — Governance Rule

| Field           | Value                      |
| --------------- | -------------------------- |
| Term ID         | GL-GOV-001                 |
| Canonical Term  | Governance Rule            |
| Family          | GUARD / POL                |
| Category        | doctrine / governance_rule |
| Ownership Scope | governed                   |
| Entry Maturity  | canonical_full             |
| Evidence Status | derived                    |

#### Definition

A Governance Rule is a canonical rule that constrains meaning, behavior, assignment, eligibility, preparation, validation, or authority inside the Assembler System.

#### Architectural Role

Governance Rule is a general term for rules that protect architectural meaning.

It may govern:

1. boundary behavior,
2. policy assignment,
3. metadata preparation,
4. timestamp stabilization,
5. responsibility delegation,
6. contract compliance,
7. runtime eligibility,
8. authority exclusion,
9. anti-collapse protection,
10. future derivation.

A Governance Rule may later become a validation check or compliance row.

It is not a runtime algorithm by default.

#### Must Not Be Confused With

1. Runtime algorithm.
2. C++ function.
3. Test case only.
4. Database constraint by default.
5. Policy Object by default.
6. Implementation package.
7. User preference.

#### Valid Usage

* “Policy Object separation is protected by a Governance Rule.”
* “Metadata Injector non-policy-hosting is a Governance Rule.”
* “Governance Rules may feed compliance matrices.”

#### Invalid Usage

* “Governance Rule is only code.”
* “Governance Rule is optional.”
* “Governance Rule is the same as Policy Object.”
* “Governance Rule can be ignored during implementation derivation.”

#### Related Terms

* GL-GOV-002 — Governance Constraint
* GL-GOV-003 — Eligibility Rule
* GL-TRC-012 — Anti-Regression Rule
* GL-CON-013 — Contract Compliance
* GL-CON-014 — Contract Violation

#### Source Trace

| Source Type     | Source                                                                   |
| --------------- | ------------------------------------------------------------------------ |
| GL-CONT-000     | Glossary governance requires anti-collapse and category integrity rules. |
| GL-CONT-007     | Anti-Regression Rule protects stabilized distinctions.                   |
| SYSTEM_GOALS.md | Negative goals and exclusion goals are enforceable constraints.          |

---

### GL-GOV-002 — Governance Constraint

| Field           | Value                 |
| --------------- | --------------------- |
| Term ID         | GL-GOV-002            |
| Canonical Term  | Governance Constraint |
| Family          | GUARD / POL           |
| Category        | constraint            |
| Ownership Scope | governed              |
| Entry Maturity  | canonical_full        |
| Evidence Status | derived               |

#### Definition

A Governance Constraint is a restriction or prohibition that prevents invalid system expansion, category collapse, invalid assignment, invalid eligibility, or authority leakage.

#### Architectural Role

Governance Constraint states what must not happen.

Examples include:

1. Policy Object must not become PolicyAssigner.
2. PolicyAssigner must not become Policy Source.
3. Metadata Injector must not become Policy Host by default.
4. Timestamp Stabilizer must not become downstream query interpreter.
5. Metadata Directive Source must not become Metadata Injector.
6. Policy Source must remain external.
7. Timestamp lifecycle after handoff must not return to Assembler ownership.

Governance Constraint may later become a validation rule.

#### Must Not Be Confused With

1. Optional note.
2. Implementation detail.
3. Runtime assertion only.
4. Unit test only.
5. Documentation style preference.
6. Performance constraint by default.

#### Valid Usage

* “Metadata Injector non-policy-hosting is a Governance Constraint.”
* “Policy source non-ownership is a Governance Constraint.”
* “Governance Constraints protect authority boundaries.”

#### Invalid Usage

* “Governance Constraint is optional.”
* “Governance Constraint exists only after code.”
* “Governance Constraint is only a test.”
* “Governance Constraint can be overridden by package convenience.”

#### Related Terms

* GL-GOV-001 — Governance Rule
* GL-GOV-003 — Eligibility Rule
* GL-TRC-012 — Anti-Regression Rule
* GL-CON-014 — Contract Violation
* GL-EXC-001 — Post-Handoff Non-Ownership

#### Source Trace

| Source Type     | Source                                                                                             |
| --------------- | -------------------------------------------------------------------------------------------------- |
| SYSTEM_GOALS.md | Negative goals and exclusions are enforceable architecture constraints.                            |
| GL-CONT-000     | Anti-collapse requirements require important terms to declare what they must not be confused with. |
| GL-CONT-007     | Anti-Regression Rule protects stabilized distinctions.                                             |

---

### GL-GOV-003 — Eligibility Rule

| Field           | Value                                |
| --------------- | ------------------------------------ |
| Term ID         | GL-GOV-003                           |
| Canonical Term  | Eligibility Rule                     |
| Family          | GUARD / POL                          |
| Category        | validation_concept / governance_rule |
| Ownership Scope | governed                             |
| Entry Maturity  | canonical_partial                    |
| Evidence Status | derived                              |

#### Definition

An Eligibility Rule is a governance rule that determines whether an object, component, envelope, mechanism, assignment, or state is eligible for a specific assembler-side action or relation.

#### Architectural Role

Eligibility Rules may govern:

1. policy assignment eligibility,
2. policy-consuming eligibility,
3. metadata preparation eligibility,
4. timestamp readiness eligibility,
5. dispatch eligibility,
6. queue admission eligibility,
7. handoff eligibility.

Eligibility Rule is a reviewable governance concept before becoming a runtime check.

It must be traceable to a contract, responsibility, obligation, or governance source.

#### Must Not Be Confused With

1. Runtime `if` statement only.
2. Final validation function.
3. Unit test only.
4. Arbitrary condition.
5. Policy Object by default.
6. Dispatcher action by default.

#### Valid Usage

* “Policy-consuming eligibility should be governed by Eligibility Rules.”
* “Pre-Dispatch Timestamp Readiness may be controlled by an Eligibility Rule.”
* “Eligibility Rules may later become validation checks.”

#### Invalid Usage

* “Eligibility Rule is arbitrary runtime logic.”
* “Eligibility Rule requires final code now.”
* “Eligibility Rule bypasses contract traceability.”
* “Eligibility Rule is the Policy Object itself.”

#### Related Terms

* GL-GOV-001 — Governance Rule
* GL-GOV-002 — Governance Constraint
* GL-POL-007 — Policy-Consuming Component
* GL-TIME-005 — Pre-Dispatch Timestamp Readiness
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type     | Source                                                                |
| --------------- | --------------------------------------------------------------------- |
| GL-CONT-007     | Responsibilities require obligations and reviewable guarantees.       |
| GL-CONT-006     | Contract families govern eligibility before implementation artifacts. |
| SYSTEM_GOALS.md | Goals define reviewable verification expectations.                    |

---

### GL-GOV-004 — Preparation Governance

| Field           | Value                                  |
| --------------- | -------------------------------------- |
| Term ID         | GL-GOV-004                             |
| Canonical Term  | Preparation Governance                 |
| Family          | POL / CON                              |
| Category        | governance_model / preparation_concept |
| Ownership Scope | governed                               |
| Entry Maturity  | canonical_full                         |
| Evidence Status | derived                                |

#### Definition

Preparation Governance is the governance model controlling how assembler-side preparation activities are constrained, ordered, made eligible, and validated before dispatch.

#### Architectural Role

Preparation Governance applies to:

1. envelope assembly,
2. validation,
3. metadata preparation,
4. timestamp stabilization,
5. policy assignment where relevant,
6. dispatch eligibility preparation,
7. envelope carrier readiness.

It ensures that prepared content becomes dispatch-ready only through governed preparation.

Preparation Governance is not downstream preservation.

It is not final runtime algorithm.

It is not downstream query interpretation.

#### Must Not Be Confused With

1. Downstream storage governance.
2. Query governance.
3. Registry lifecycle management.
4. Runtime scheduling algorithm.
5. Final C++ package.
6. Policy source ownership.

#### Valid Usage

* “Preparation Governance controls metadata and timestamp preparation.”
* “Preparation Governance occurs before dispatch eligibility.”
* “Preparation Governance feeds future compliance checks.”

#### Invalid Usage

* “Preparation Governance owns downstream records.”
* “Preparation Governance is query behavior.”
* “Preparation Governance is only runtime code.”
* “Preparation Governance replaces Dispatcher.”

#### Related Terms

* GL-META-001 — Metadata Preparation
* GL-TIME-001 — Timestamp Stabilization
* GL-POL-004 — Policy Assignment
* GL-CON-007 — Metadata / Preparation Contract Family
* GL-OBJ-015 — Dispatch Eligibility State

#### Source Trace

| Source Type     | Source                                                               |
| --------------- | -------------------------------------------------------------------- |
| GL-CONT-006     | Metadata / Preparation Contract Family governs preparation behavior. |
| SYSTEM_GOALS.md | Metadata and timestamp goals preserve preparation semantics.         |
| GL-CONT-004     | Log Level Envelope carries prepared governance material.             |

---

### GL-GOV-005 — Policy / Ecosystem Governance

| Field           | Value                                      |
| --------------- | ------------------------------------------ |
| Term ID         | GL-GOV-005                                 |
| Canonical Term  | Policy / Ecosystem Governance              |
| Family          | POL / CON                                  |
| Category        | governance_model / contract_family_context |
| Ownership Scope | governed                                   |
| Entry Maturity  | canonical_full                             |
| Evidence Status | derived                                    |

#### Definition

Policy / Ecosystem Governance is the governance model controlling administrative, ecosystem, policy-source, policy-object, and policy-assignment interactions that affect assembler-side behavior.

#### Architectural Role

Policy / Ecosystem Governance maps to the `Policy / Ecosystem Contract Family`.

It governs:

1. Administrative / Ecosystem Port interactions,
2. Policy Registry / Policy Source relation,
3. Policy Object receipt or reference,
4. Policy Assignment,
5. PolicyAssigner responsibility,
6. policy-consuming component eligibility,
7. policy-hosting restrictions,
8. policy source non-ownership.

It prevents policy interactions from collapsing into consuming ingress or downstream lifecycle ownership.

#### Must Not Be Confused With

1. Consuming ingress.
2. Metadata directive governance by default.
3. Policy source ownership.
4. Downstream policy lifecycle.
5. Final policy engine.
6. Generic administration.

#### Valid Usage

* “Policy / Ecosystem Governance protects Policy Object and PolicyAssigner distinctions.”
* “Administrative / Ecosystem Port belongs to policy/ecosystem governance.”
* “Policy source non-ownership remains binding.”

#### Invalid Usage

* “Policy / Ecosystem Governance means raw content ingress.”
* “Policy / Ecosystem Governance owns the policy source.”
* “Policy / Ecosystem Governance is final policy engine implementation.”
* “Policy / Ecosystem Governance makes Metadata Injector policy-hosted.”

#### Related Terms

* GL-CON-006 — Policy / Ecosystem Contract Family
* GL-BND-007 — Administrative / Ecosystem Port
* GL-POL-006 — Policy Registry / Policy Source
* GL-POL-003 — Policy Object
* GL-POL-004 — Policy Assignment

#### Source Trace

| Source Type     | Source                                                                                                            |
| --------------- | ----------------------------------------------------------------------------------------------------------------- |
| GL-CONT-006     | Policy / Ecosystem Contract Family governs administrative, ecosystem, policy-source, and assignment interactions. |
| GL-CONT-002     | Administrative / Ecosystem Port is distinct from consuming ingress.                                               |
| SYSTEM_GOALS.md | Policy governance goals preserve policy-object and policy-host distinctions.                                      |

---

### GL-GOV-006 — Metadata / Preparation Governance

| Field           | Value                                      |
| --------------- | ------------------------------------------ |
| Term ID         | GL-GOV-006                                 |
| Canonical Term  | Metadata / Preparation Governance          |
| Family          | POL / CON                                  |
| Category        | governance_model / contract_family_context |
| Ownership Scope | governed                                   |
| Entry Maturity  | canonical_full                             |
| Evidence Status | derived                                    |

#### Definition

Metadata / Preparation Governance is the governance model controlling metadata preparation, timestamp stabilization, and related preparation semantics inside the Assembler System.

#### Architectural Role

Metadata / Preparation Governance maps to the `Metadata / Preparation Contract Family`.

It governs:

1. Metadata Injector behavior,
2. metadata directives,
3. schema-guided metadata,
4. directive-driven metadata,
5. Envelope Metadata Block preparation,
6. Timestamp Stabilizer behavior,
7. timestamp semantics,
8. Envelope Timestamp Block preparation,
9. pre-dispatch timestamp readiness.

It preserves the boundary between preparation and downstream query or storage lifecycle.

#### Must Not Be Confused With

1. Policy / Ecosystem Governance.
2. Policy source ownership.
3. Downstream registry metadata lifecycle.
4. Query-time timestamp interpretation.
5. Storage timestamp lifecycle.
6. Final serialization schema.
7. Final implementation package.

#### Valid Usage

* “Metadata / Preparation Governance controls Metadata Injector and Timestamp Stabilizer semantics.”
* “Timestamp stabilization remains pre-dispatch preparation.”
* “Metadata / Preparation Governance does not own downstream metadata lifecycle.”

#### Invalid Usage

* “Metadata / Preparation Governance is downstream registry schema.”
* “Metadata / Preparation Governance is query timestamp logic.”
* “Metadata / Preparation Governance makes Metadata Injector policy-hosted.”
* “Metadata / Preparation Governance replaces policy assignment.”

#### Related Terms

* GL-CON-007 — Metadata / Preparation Contract Family
* GL-META-002 — Metadata Injector
* GL-TIME-002 — Timestamp Stabilizer
* GL-META-007 — Envelope Metadata Block
* GL-TIME-004 — Envelope Timestamp Block

#### Source Trace

| Source Type     | Source                                                                              |
| --------------- | ----------------------------------------------------------------------------------- |
| GL-CONT-006     | Metadata / Preparation Contract Family governs metadata and preparation contracts.  |
| GL-CONT-003     | Metadata Injector and Timestamp Stabilizer are preparation components.              |
| SYSTEM_GOALS.md | Metadata and timestamp goals preserve preparation semantics and non-collapse rules. |

---

## 5. Policy Governance Chain

|           Record ID | Chain Step | Canonical Term                  | Meaning                                                           |
| ------------------: | ---------- | ------------------------------- | ----------------------------------------------------------------- |
| GL-CONT-008-PGC-001 | Source     | Policy Registry / Policy Source | External source of policy material                                |
| GL-CONT-008-PGC-002 | Material   | Policy Material                 | Governed policy material supplied or referenced                   |
| GL-CONT-008-PGC-003 | Object     | Policy Object                   | Governed object representing policy material                      |
| GL-CONT-008-PGC-004 | Mediator   | PolicyAssigner                  | Delegated entity mediating assignment                             |
| GL-CONT-008-PGC-005 | Relation   | Policy Assignment               | Association between Policy Object and eligible consumer/mechanism |
| GL-CONT-008-PGC-006 | Consumer   | Policy-Consuming Component      | Component eligible to realize policy-governed behavior            |
| GL-CONT-008-PGC-007 | Behavior   | Policy-Governed Mechanism       | Mechanism shaped by assigned policy                               |
| GL-CONT-008-PGC-008 | Guard      | Policy Source Non-Ownership     | Policy source remains outside assembler ownership                 |

---

## 6. Metadata Preparation Chain

|           Record ID | Chain Step | Canonical Term                                     | Meaning                                                |
| ------------------: | ---------- | -------------------------------------------------- | ------------------------------------------------------ |
| GL-CONT-008-MPC-001 | Source     | Metadata Directive Source                          | External source of metadata directives                 |
| GL-CONT-008-MPC-002 | Directive  | Metadata Directive                                 | Governed directive material for metadata preparation   |
| GL-CONT-008-MPC-003 | Governance | Schema-Guided Metadata / Directive-Driven Metadata | Preparation rule basis                                 |
| GL-CONT-008-MPC-004 | Component  | Metadata Injector                                  | Assembler-side component applying metadata preparation |
| GL-CONT-008-MPC-005 | Result     | Envelope Metadata Block                            | Governed metadata artifact inside envelope             |
| GL-CONT-008-MPC-006 | Guard      | Non-Policy-Hosting Metadata Rule                   | Metadata Injector is not policy-hosted by default      |

---

## 7. Timestamp Preparation Chain

|           Record ID | Chain Step | Canonical Term                   | Meaning                                                      |
| ------------------: | ---------- | -------------------------------- | ------------------------------------------------------------ |
| GL-CONT-008-TPC-001 | Semantics  | Timestamp Semantics              | Governed meaning of timestamp information                    |
| GL-CONT-008-TPC-002 | Component  | Timestamp Stabilizer             | Preparation component stabilizing timestamp semantics        |
| GL-CONT-008-TPC-003 | Activity   | Timestamp Stabilization          | Assembler-side preparation activity                          |
| GL-CONT-008-TPC-004 | Result     | Envelope Timestamp Block         | Governed timestamp artifact inside envelope                  |
| GL-CONT-008-TPC-005 | Readiness  | Pre-Dispatch Timestamp Readiness | Readiness condition before dispatch eligibility              |
| GL-CONT-008-TPC-006 | Guard      | Query-Time Exclusion             | Timestamp preparation is not downstream query interpretation |

---

## 8. Responsibility-to-Governance Mapping

|           Record ID | Responsibility Area            | Narrow Carrier                   | Obligation                                               | Governance Family                 |
| ------------------: | ------------------------------ | -------------------------------- | -------------------------------------------------------- | --------------------------------- |
| GL-CONT-008-RGM-001 | Policy material separation     | Policy Object                    | Must not become PolicyAssigner or source                 | Policy Governance                 |
| GL-CONT-008-RGM-002 | Policy assignment              | PolicyAssigner                   | Must mediate assignment without becoming policy source   | Policy / Ecosystem Governance     |
| GL-CONT-008-RGM-003 | Policy consumption             | Policy-Consuming Component       | Must remain distinct from Policy Object                  | Policy Governance                 |
| GL-CONT-008-RGM-004 | Metadata directive application | Metadata Injector                | Must remain schema/directive-governed, not policy-hosted | Metadata / Preparation Governance |
| GL-CONT-008-RGM-005 | Metadata source separation     | Metadata Directive Source        | Must remain external, not Metadata Injector              | Metadata / Preparation Governance |
| GL-CONT-008-RGM-006 | Timestamp stabilization        | Timestamp Stabilizer             | Must stabilize semantics before dispatch eligibility     | Metadata / Preparation Governance |
| GL-CONT-008-RGM-007 | Timestamp readiness            | Pre-Dispatch Timestamp Readiness | Must not become final handoff or query readiness         | Preparation Governance            |
| GL-CONT-008-RGM-008 | Governance validation          | Governance Rule                  | Must remain reviewable before code                       | Governance Constraint Model       |

---

## 9. Anti-Collapse Index

|          Record ID | Term                             | Must Not Collapse Into           | Guard Meaning                                        |
| -----------------: | -------------------------------- | -------------------------------- | ---------------------------------------------------- |
| GL-CONT-008-AC-001 | Policy Governance                | Policy engine implementation     | Governance precedes implementation                   |
| GL-CONT-008-AC-002 | Policy Material                  | Policy executor                  | Material governs behavior but does not execute       |
| GL-CONT-008-AC-003 | Policy Object                    | PolicyAssigner                   | Object is assigned; assigner mediates                |
| GL-CONT-008-AC-004 | Policy Assignment                | Policy Object                    | Assignment is relation, not material                 |
| GL-CONT-008-AC-005 | PolicyAssigner                   | Policy Registry / Policy Source  | Assigner is internal; source is external             |
| GL-CONT-008-AC-006 | Policy Registry / Policy Source  | Internal actor                   | Source remains external                              |
| GL-CONT-008-AC-007 | Policy-Consuming Component       | Policy Object                    | Component realizes governed behavior; object governs |
| GL-CONT-008-AC-008 | Policy-Governed Mechanism        | Policy Object                    | Mechanism is behavior, not material                  |
| GL-CONT-008-AC-009 | Policy Host                      | Every policy-consuming component | Hosting must be explicit                             |
| GL-CONT-008-AC-010 | Metadata Preparation             | Policy assignment                | Metadata preparation is schema/directive-governed    |
| GL-CONT-008-AC-011 | Metadata Injector                | Policy Host                      | Metadata Injector is not policy-hosted by default    |
| GL-CONT-008-AC-012 | Metadata Directive Source        | Metadata Injector                | Source supplies; injector applies                    |
| GL-CONT-008-AC-013 | Metadata Directive               | Policy Object by default         | Metadata directive is metadata governance material   |
| GL-CONT-008-AC-014 | Schema-Guided Metadata           | Database schema                  | It is assembler-side metadata discipline             |
| GL-CONT-008-AC-015 | Directive-Driven Metadata        | Policy assignment                | Directive-driven metadata is metadata preparation    |
| GL-CONT-008-AC-016 | Envelope Metadata Block          | Metadata Injector                | Block is artifact; injector is component             |
| GL-CONT-008-AC-017 | Timestamp Stabilization          | Query-time interpretation        | Stabilization is pre-dispatch preparation            |
| GL-CONT-008-AC-018 | Timestamp Stabilizer             | Downstream query subsystem       | Stabilizer is assembler-side preparation component   |
| GL-CONT-008-AC-019 | Timestamp Semantics              | Raw timestamp value only         | Semantics means governed timestamp meaning           |
| GL-CONT-008-AC-020 | Envelope Timestamp Block         | Timestamp Stabilizer             | Block is artifact; stabilizer is component           |
| GL-CONT-008-AC-021 | Pre-Dispatch Timestamp Readiness | Final handoff                    | Readiness supports eligibility; it is not handoff    |
| GL-CONT-008-AC-022 | Governance Rule                  | Runtime algorithm only           | Governance precedes runtime implementation           |
| GL-CONT-008-AC-023 | Governance Constraint            | Optional note                    | Constraint is enforceable architecture rule          |
| GL-CONT-008-AC-024 | Eligibility Rule                 | Arbitrary condition              | Eligibility must be contract/trace governed          |

---

## 10. Contract Family Alignment Matrix

|           Record ID | Contract Family                        | Terms Governed                                                                                             | Notes                                                  |
| ------------------: | -------------------------------------- | ---------------------------------------------------------------------------------------------------------- | ------------------------------------------------------ |
| GL-CONT-008-CFA-001 | Policy / Ecosystem Contract Family     | Policy Object, Policy Assignment, PolicyAssigner, Policy-Consuming Component, Policy Source Non-Ownership  | Governs policy-source and assignment interactions      |
| GL-CONT-008-CFA-002 | Metadata / Preparation Contract Family | Metadata Injector, Metadata Directive, Metadata Preparation, Timestamp Stabilizer, Timestamp Stabilization | Governs metadata and timestamp preparation             |
| GL-CONT-008-CFA-003 | Ingress Contract Family                | Metadata Injector, Timestamp Stabilizer, Envelope Metadata Block, Envelope Timestamp Block                 | Governs composition where required by ingress contract |
| GL-CONT-008-CFA-004 | Envelope Carrier Contract Family       | Envelope Metadata Block, Envelope Timestamp Block, Policy Assignment                                       | Governs envelope-carried governance material           |
| GL-CONT-008-CFA-005 | Registry / Dispatcher Contract Family  | Pre-Dispatch Timestamp Readiness, Dispatch Eligibility State                                               | Governs readiness before handoff                       |
| GL-CONT-008-CFA-006 | Exclusion Contract Family              | Policy Source Non-Ownership, downstream metadata/timestamp non-ownership                                   | Prevents authority leakage                             |

---

## 11. Future Representation Readiness

This pack is designed to support later structured representations.

### 11.1 Candidate Future Tables or JSON Collections

|           Record ID | Representation Area          | Likely Row Grain                                |
| ------------------: | ---------------------------- | ----------------------------------------------- |
| GL-CONT-008-REP-001 | `policy_terms`               | One policy glossary term                        |
| GL-CONT-008-REP-002 | `policy_objects`             | One policy object or policy-material record     |
| GL-CONT-008-REP-003 | `policy_assignments`         | One policy-object-to-consumer assignment        |
| GL-CONT-008-REP-004 | `policy_consumers`           | One eligible policy-consuming component         |
| GL-CONT-008-REP-005 | `policy_governed_mechanisms` | One governed behavior/mechanism                 |
| GL-CONT-008-REP-006 | `metadata_directives`        | One metadata directive record                   |
| GL-CONT-008-REP-007 | `metadata_preparation_rules` | One metadata governance/preparation rule        |
| GL-CONT-008-REP-008 | `timestamp_semantics`        | One timestamp semantics record                  |
| GL-CONT-008-REP-009 | `timestamp_readiness_rules`  | One readiness or eligibility rule               |
| GL-CONT-008-REP-010 | `governance_constraints`     | One governance constraint or anti-collapse rule |

### 11.2 Representation Constraint

```text id="gl-cont-008-representation-constraint"
Structured representation must preserve source/actor/object distinctions,
policy source non-ownership, metadata non-policy-hosting, timestamp
pre-dispatch scope, contract-family alignment, and anti-collapse guards.
```

---

## 12. Validation Checklist

|           Record ID | Check                                                            | Expected Result |
| ------------------: | ---------------------------------------------------------------- | --------------- |
| GL-CONT-008-VAL-001 | Policy Governance is defined                                     | Pass            |
| GL-CONT-008-VAL-002 | Policy Material is distinct from policy execution                | Pass            |
| GL-CONT-008-VAL-003 | Policy Object is distinct from PolicyAssigner                    | Pass            |
| GL-CONT-008-VAL-004 | Policy Assignment is distinct from Policy Object                 | Pass            |
| GL-CONT-008-VAL-005 | PolicyAssigner is distinct from Policy Registry / Policy Source  | Pass            |
| GL-CONT-008-VAL-006 | Policy Registry / Policy Source is external                      | Pass            |
| GL-CONT-008-VAL-007 | Policy-Consuming Component is distinct from Policy Object        | Pass            |
| GL-CONT-008-VAL-008 | Policy-Governed Mechanism is defined                             | Pass            |
| GL-CONT-008-VAL-009 | Policy Host is not default status for all components             | Pass            |
| GL-CONT-008-VAL-010 | Policy Source Non-Ownership is defined                           | Pass            |
| GL-CONT-008-VAL-011 | Metadata Preparation is defined                                  | Pass            |
| GL-CONT-008-VAL-012 | Metadata Injector is not policy-hosted by default                | Pass            |
| GL-CONT-008-VAL-013 | Metadata Directive Source is external                            | Pass            |
| GL-CONT-008-VAL-014 | Metadata Directive is distinct from source and injector          | Pass            |
| GL-CONT-008-VAL-015 | Schema-Guided Metadata is not database schema ownership          | Pass            |
| GL-CONT-008-VAL-016 | Directive-Driven Metadata is not policy assignment               | Pass            |
| GL-CONT-008-VAL-017 | Envelope Metadata Block is artifact, not component               | Pass            |
| GL-CONT-008-VAL-018 | Timestamp Stabilization is pre-dispatch preparation              | Pass            |
| GL-CONT-008-VAL-019 | Timestamp Stabilizer is not downstream query subsystem           | Pass            |
| GL-CONT-008-VAL-020 | Timestamp Semantics is governed meaning, not raw value only      | Pass            |
| GL-CONT-008-VAL-021 | Envelope Timestamp Block is artifact, not component              | Pass            |
| GL-CONT-008-VAL-022 | Pre-Dispatch Timestamp Readiness is not final handoff            | Pass            |
| GL-CONT-008-VAL-023 | Governance Rule is not runtime algorithm only                    | Pass            |
| GL-CONT-008-VAL-024 | Governance Constraint is enforceable, not optional note          | Pass            |
| GL-CONT-008-VAL-025 | Eligibility Rule remains trace/contract-governed                 | Pass            |
| GL-CONT-008-VAL-026 | Pack supports GL-CONT-009                                        | Pass            |
| GL-CONT-008-VAL-027 | Pack supports future policy/metadata/timestamp compliance matrix | Pass            |

---

## 13. Pack Exit Criteria

This pack is complete when the following are true:

|            Record ID | Exit Criterion                                                             | Status   |
| -------------------: | -------------------------------------------------------------------------- | -------- |
| GL-CONT-008-EXIT-001 | Policy Governance is formally defined                                      | Complete |
| GL-CONT-008-EXIT-002 | Policy Object and Policy Assignment distinctions are preserved             | Complete |
| GL-CONT-008-EXIT-003 | PolicyAssigner and Policy Source distinction is preserved                  | Complete |
| GL-CONT-008-EXIT-004 | Policy-consuming component model is defined                                | Complete |
| GL-CONT-008-EXIT-005 | Policy-hosting default exclusion is defined                                | Complete |
| GL-CONT-008-EXIT-006 | Metadata Preparation is formally defined                                   | Complete |
| GL-CONT-008-EXIT-007 | Metadata Injector non-policy-hosting rule is preserved                     | Complete |
| GL-CONT-008-EXIT-008 | Metadata Directive Source and Metadata Directive are distinguished         | Complete |
| GL-CONT-008-EXIT-009 | Envelope Metadata Block is defined as governed artifact                    | Complete |
| GL-CONT-008-EXIT-010 | Timestamp Stabilization is formally defined                                | Complete |
| GL-CONT-008-EXIT-011 | Timestamp Stabilizer is distinguished from downstream query interpretation | Complete |
| GL-CONT-008-EXIT-012 | Timestamp Semantics and Envelope Timestamp Block are defined               | Complete |
| GL-CONT-008-EXIT-013 | Pre-Dispatch Timestamp Readiness is defined                                | Complete |
| GL-CONT-008-EXIT-014 | Governance Rule, Governance Constraint, and Eligibility Rule are defined   | Complete |
| GL-CONT-008-EXIT-015 | Policy governance chain is included                                        | Complete |
| GL-CONT-008-EXIT-016 | Metadata preparation chain is included                                     | Complete |
| GL-CONT-008-EXIT-017 | Timestamp preparation chain is included                                    | Complete |
| GL-CONT-008-EXIT-018 | Anti-collapse index is included                                            | Complete |
| GL-CONT-008-EXIT-019 | Contract family alignment matrix is included                               | Complete |
| GL-CONT-008-EXIT-020 | Pack is ready to support GL-CONT-009                                       | Complete |

---

## 14. Summary

`GL-CONT-008 — Policy, Metadata, Timestamp, and Governance Terms Pack` establishes the controlled vocabulary for policy governance, metadata preparation, timestamp stabilization, and governance constraints inside the Assembler System.

The pack preserves the following core rules:

```text id="gl-cont-008-summary-rules"
Policy Object ≠ PolicyAssigner
PolicyAssigner ≠ Policy Registry / Policy Source
Policy Assignment ≠ Policy Object
Policy-Consuming Component ≠ Policy Object
Metadata Injector ≠ Policy Host by default
Metadata Directive Source ≠ Metadata Injector
Metadata Directive ≠ Policy Object by default
Timestamp Stabilization ≠ downstream query interpretation
Timestamp Stabilizer ≠ downstream query subsystem
Envelope Metadata Block ≠ Metadata Injector
Envelope Timestamp Block ≠ Timestamp Stabilizer
Pre-Dispatch Timestamp Readiness ≠ final handoff
Governance Rule ≠ runtime algorithm only
```

It prepares the Assembler System for:

1. dispatcher and handoff terminology,
2. dispatch eligibility governance,
3. registry-facing handoff constraints,
4. authority exclusion expansion,
5. compliance matrix derivation,
6. future metadata/timestamp typed-contract derivation,
7. future C++ policy/preparation abstraction derivation.

The next glossary content pack is:

```text id="gl-cont-008-next"
GL-CONT-009 — Dispatcher, Handoff, Registry, and Authority Exclusion Terms Pack
```
