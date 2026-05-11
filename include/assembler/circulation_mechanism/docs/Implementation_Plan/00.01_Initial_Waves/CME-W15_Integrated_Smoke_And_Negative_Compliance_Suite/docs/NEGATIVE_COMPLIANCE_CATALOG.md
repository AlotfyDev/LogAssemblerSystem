# Negative Compliance Catalog — CME-W15

## 1. Purpose

This catalog lists anti-collapse checks that the implementation must preserve.

Some checks are expressed as compileable assertions. Other checks remain documented
as future compile-fail or policy tests once stronger type machinery is introduced.

---

## 2. Core Negative Assertions

### NEG-CME-001 — Container Is Not Broker

**Protected meaning:** `TContainer` is a data-structure container.

**Must not collapse into:**

```text
message broker
queue broker
topic router
downstream registry
receiver lifecycle owner
```

**Current enforcement:** documentation + smoke construction of `TContainer` without broker API.

---

### NEG-CME-002 — Waiting List Is Not Envelope Store

**Protected meaning:** `TIngressWaitingList` and `TDispatchWaitingList` carry `TWaitingListEntry`, which contains a `TContainerRegistryIndex`.

**Must not collapse into:**

```text
payload queue
envelope store
message buffer
consumer group backlog
```

**Current enforcement:** compileable test pushes only index/state entries.

---

### NEG-CME-003 — Reference Is Not Raw Pointer

**Protected meaning:** access refs are scoped artifacts.

**Must not collapse into:**

```text
raw pointer
external mutable handle
bridge protocol handle
receiver handle
```

**Current enforcement:** reference structs require id/kind/direction/scope/validity.

---

### NEG-CME-004 — Ingress Ref Is Not Dispatch Ref

**Protected meaning:** ingress refs are direction-specific.

**Must not collapse into:**

```text
generic untyped ref
dispatch ref
bridge ref
```

**Current enforcement:** compileable direction mismatch policy check.

---

### NEG-CME-005 — Dispatcher Is Not Bridge

**Protected meaning:** `TDispatcher` exposes, bridge consumes.

**Must not collapse into:**

```text
Bridge Orchestrator
bridge protocol session
receiver delivery
copy/move executor
```

**Current enforcement:** dispatcher/report structures do not expose bridge protocol execution.

---

### NEG-CME-006 — Report Is Not Downstream Proof

**Protected meaning:** reports are evidence inside their declared scope.

**Must not collapse into:**

```text
persistence proof
receiver acknowledgement
bridge success guarantee
delivery certificate
```

**Current enforcement:** documentation and report fields restricted to local evidence.

---

### NEG-CME-007 — View Is Not Mutable Handle

**Protected meaning:** views are read-only projections.

**Must not collapse into:**

```text
mutable reference
state owner
transition executor
container mutation surface
```

**Current enforcement:** view structs only carry value projections.

---

### NEG-CME-008 — Safe Point Is Not Automatic Operation

**Protected meaning:** safe point permits operation; it does not execute it.

**Must not collapse into:**

```text
reset algorithm
scaling algorithm
eviction algorithm
registry rebuild
```

**Current enforcement:** safe point policy returns boolean only.

---

### NEG-CME-009 — Eviction Profile Is Not Retry Engine

**Protected meaning:** eviction profiles select/describe possible handling under capacity conditions.

**Must not collapse into:**

```text
read-side retry
receiver delay handling
bridge recovery
persistence deletion
```

**Current enforcement:** eviction wave only carries candidates/profiles/reports.

---

### NEG-CME-010 — Binding Descriptor Is Not Runtime Adapter

**Protected meaning:** communication binding descriptors describe readiness/compatibility.

**Must not collapse into:**

```text
adapter invocation
Log API runtime
Bridge runtime
payload movement
```

**Current enforcement:** compatibility policy is descriptive and blocks mutable internal exposure.
