# Policy Object Taxonomy V1

## 1. Scope
### 1.1
This document defines the semantic taxonomy of the **Policy Object** as used in this system.

### 1.2
This version is intentionally limited to **semantic closure only**.

### 1.3
This version does **not** attempt to formalize:
1. structural graph internals,
2. traversal semantics,
3. graph layering,
4. graph execution topology.

### 1.4
The present goal is to stabilize the minimum semantic meaning of a base policy object so that later policy families can be defined over a shared foundation.

---

## 2. Foundational Interpretation
### 2.1
A policy object in this system is primarily an **execution policy object**.

### 2.2
It is **not** primarily treated as:
1. a generic clause-satisfaction engine,
2. a flat configuration blob,
3. a single switch or enum mode,
4. a callback-only strategy object.

### 2.3
A policy object is understood as a **semantic governing object** with execution-oriented meaning.

### 2.4
A policy object is treated as **graph-founded in principle**, even when minimally realized.

### 2.5
The detailed graph structure is intentionally deferred to a separate document.

---

## 3. Core Semantic Definition
### 3.1
A policy object is an object that carries:
1. identity,
2. clauses,
3. safe replacement semantics,
4. lifecycle/state capability,
5. realization mechanism binding,
6. observation/audit capability.

### 3.2
A policy object is selected or assigned before execution.

### 3.3
In the normal execution path of an execution-policy family, the question is usually:
1. **how** the policy is realized,
not
2. **whether** the policy should be considered applicable.

### 3.4
Therefore, execution policies in this system are mostly **already chosen executable policies**, not runtime policy-candidate pools waiting for active clause truth evaluation.

---

## 4. Mandatory Semantic Elements
### 4.1 Policy Identity
#### 4.1.1
Every policy object shall possess identity semantics.

#### 4.1.2
Identity semantics should minimally support:
1. policy identity,
2. policy family recognition,
3. policy versioning,
4. policy scope awareness,
5. policy source/provenance awareness.

#### 4.1.3
Identity is required for:
1. traceability,
2. replacement discipline,
3. governance linkage,
4. auditability.

---

### 4.2 Policy Clauses
#### 4.2.1
Every policy object shall contain clauses structurally.

#### 4.2.2
A clause is a policy-local semantic unit such as:
1. execution directive,
2. execution constraint,
3. execution parameter,
4. execution preference,
5. fallback directive,
6. replacement-related directive.

#### 4.2.3
Clauses are mandatory structurally even when their runtime truth evaluation is not active.

#### 4.2.4
In execution-policy families, clauses are usually interpreted as **realization-bearing content** rather than as dynamically contested truth statements.

---

### 4.3 Safe Replacement Semantics
#### 4.3.1
Every policy object shall provide safe replacement semantics.

#### 4.3.2
A policy object is not assumed to be arbitrarily swappable at any runtime instant.

#### 4.3.3
Safe replacement semantics shall minimally allow:
1. replacement boundaries,
2. replacement eligibility conditions,
3. replacement discipline,
4. pending replacement awareness where applicable.

#### 4.3.4
Safe replacement semantics are treated as foundational, not auxiliary.

---

### 4.4 Lifecycle / State Slot
#### 4.4.1
Every policy object shall provide a lifecycle/state slot structurally.

#### 4.4.2
Lifecycle richness may vary across concrete policy families.

#### 4.4.3
The lifecycle/state slot exists to support:
1. activation,
2. suspension,
3. pending replacement,
4. retirement,
5. policy-state-sensitive governance.

#### 4.4.4
A concrete policy may realize this slot lightly, but the slot itself remains mandatory structurally.

---

### 4.5 Realization Mechanism Binding
#### 4.5.1
Every execution policy object shall be associated with a realization mechanism.

#### 4.5.2
The realization mechanism is responsible for enacting the policy on an external target object or through the external target object's execution surface.

#### 4.5.3
A policy object does **not** absorb, swallow, or own its target object.

#### 4.5.4
The correct semantic relation is:
1. the policy object carries execution-governing content,
2. the policy object is assigned a realization mechanism,
3. the realization mechanism acts on an external target object.

#### 4.5.5
Therefore, realization binding is mandatory in execution-policy families.

---

### 4.6 Observation / Audit Slot
#### 4.6.1
Every policy object shall provide observation/audit semantics structurally.

#### 4.6.2
Observation/audit support is:
1. mandatory structurally,
2. lightweight by default.

#### 4.6.3
This slot exists to support:
1. activation traceability,
2. replacement traceability,
3. evaluation traceability where applicable,
4. evidence production,
5. operational review.

---

## 5. Dormant but Structurally Present Elements
### 5.1 Applicability Slot
#### 5.1.1
Applicability semantics remain structurally present in the general policy model.

#### 5.1.2
However, in execution-policy families, applicability is usually:
1. pre-resolved upstream,
2. trivially satisfied,
3. or operationally dormant.

#### 5.1.3
Therefore, applicability remains part of the semantic base, but it is not treated as an active center of gravity in the present execution-policy interpretation.

---

### 5.2 Clause Truth Evaluation
#### 5.2.1
Clause truth evaluation is not the main execution concern of execution-policy families in this system.

#### 5.2.2
A concrete execution policy is normally assumed to have been chosen under already-valid conditions.

#### 5.2.3
As a result, clause truth checking may remain:
1. structurally representable,
2. semantically acknowledged,
3. but practically dormant during normal realization.

---

## 6. Clarified Non-Conflations
### 6.1 Policy Object vs Clause
#### 6.1.1
A clause is not a full policy object.

#### 6.1.2
A policy object is a higher-order semantic container that organizes clauses together with replacement, lifecycle, realization, and observation semantics.

---

### 6.2 Policy Object vs Realization Mechanism
#### 6.2.1
A realization mechanism is not the same thing as the policy object.

#### 6.2.2
The policy object governs execution semantically.

#### 6.2.3
The realization mechanism enacts the policy.

#### 6.2.4
The mechanism may be represented as:
1. a mechanism object,
2. an assigned executor path,
3. an injected callable family,
4. a bound method-level realization surface.

---

### 6.3 Policy Object vs Target Object
#### 6.3.1
The target object is not owned by the policy object.

#### 6.3.2
The policy object does not absorb the target object.

#### 6.3.3
The realization mechanism operates on or through the external target object.

#### 6.3.4
Typical target objects may include:
1. dispatcher,
2. moderator,
3. queue bundle agent,
4. other execution-bearing subsystem components.

---

### 6.4 Policy Object vs Flat Configuration Blob
#### 6.4.1
A policy object may be externally represented by configuration payloads, but semantically it is not reduced to a flat configuration blob.

#### 6.4.2
A policy object carries execution-governing meaning and replacement discipline beyond static field storage.

---

## 7. Semantic Consequences for Concrete Policy Families
### 7.1
Concrete policy families should differ primarily in:
1. clause content,
2. clause richness,
3. lifecycle richness,
4. safe replacement detail,
5. realization mechanism family,
6. observation/audit detail.

### 7.2
Concrete policy families should **not** need to reinvent the semantic base every time.

### 7.3
This taxonomy therefore provides a shared semantic skeleton for:
1. dispatch policy objects,
2. slot lifecycle policy objects,
3. level container policy objects,
4. resolver pipeline policy objects,
5. preview-related policy objects,
6. other future execution-policy families.

---

## 8. Graph-Founded Principle
### 8.1
Policy objects in this system are treated as **graph-founded in principle**.

### 8.2
This principle is acknowledged here only at the semantic level.

### 8.3
This document does not yet formalize:
1. graph node taxonomy,
2. graph edge taxonomy,
3. structural graph layering,
4. traversal graph behavior,
5. activation/traversal execution semantics.

### 8.4
Those structural and traversal concerns are explicitly deferred to a later dedicated document.

---

## 9. Minimum Semantic Closure Achieved by This Version
### 9.1
This version closes the following questions semantically:
1. what a policy object is,
2. what elements are mandatory in the semantic base,
3. what remains structurally present but dormant in execution-policy families,
4. what must not be conflated with the policy object,
5. how realization binding should be understood,
6. why policy objects are not reducible to flat configuration blobs.

### 9.2
This version intentionally does **not** close:
1. graph structure internals,
2. graph traversal semantics,
3. concrete policy class design,
4. policy storage catalogs,
5. policy serialization formats,
6. per-family concrete implementation details.

---

## 10. Final Definition
### 10.1
A **Policy Object** in this system is a graph-founded, execution-oriented semantic governing object that carries identity, clauses, safe replacement semantics, lifecycle capability, realization-mechanism binding, and lightweight-by-default observation/audit capability.

### 10.2
In execution-policy families, applicability and clause-truth evaluation remain structurally present but are typically pre-resolved upstream and therefore operationally dormant during normal realization.

### 10.3
A policy object does not own its target object.  
Instead, it is assigned a realization mechanism, and that mechanism enacts the policy on an external execution-bearing target object.
