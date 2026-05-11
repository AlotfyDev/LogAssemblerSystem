# CME-RSCP-W00 — ReadSide Circulation Profile Preliminary Model

## 1. Document Control

| Record ID | Field | Value |
|---:|---|---|
| CME-RSCP-W00-DOC-001 | Document Title | ReadSide Circulation Profile Preliminary Model |
| CME-RSCP-W00-DOC-002 | Component ID | `CME-COMP-021` |
| CME-RSCP-W00-DOC-003 | Component Name | `ReadSide_Circulation_Profile` |
| CME-RSCP-W00-DOC-004 | Domain | `circulation_mechanism` |
| CME-RSCP-W00-DOC-005 | Profile Position | post-bridge / read-side |
| CME-RSCP-W00-DOC-006 | Status | Preliminary Architecture Wave |
| CME-RSCP-W00-DOC-007 | Implementation Direction | C++17, header-only-first later; this wave is non-code planning |
| CME-RSCP-W00-DOC-008 | Primary Rule | Read-side circulation belongs to the circulation mechanism family but not to the pre-bridge profile |
| CME-RSCP-W00-DOC-009 | Non-Goal | This wave does not implement receiver delivery, persistence, retry algorithms, bridge runtime, or add-on behavior |

---

## 2. Purpose

### 2.1 Purpose Statement

This preliminary wave defines what can be safely fixed now for `ReadSide_Circulation_Profile`, before implementing any read-side runtime behavior.

It answers:

```text
What is the post-bridge/read-side circulation profile?
What can be decided now?
What depends on the other 20 components?
What depends on bridge/add-on/receiver contracts?
What must remain deferred?
```

### 2.2 Core Thesis

```text
ReadSide_Circulation_Profile is inside the circulation mechanism family,
but outside the pre-bridge profile.
```

It exists to absorb concerns that should not be forced into the pre-bridge engine:

1. receiver delay,
2. failed-dispatch handling,
3. read-side retry,
4. read-side backpressure,
5. delayed release,
6. receiver acknowledgement profile,
7. post-bridge capacity profile,
8. receiver-facing circulation cycles.

---

## 3. What Can Be Settled In This Preliminary Wave

### 3.1 Identity

```text
Component:
    ReadSide_Circulation_Profile

Alias:
    PostBridge_Circulation_Profile

Component ID:
    CME-COMP-021
```

### 3.2 Boundary

```text
Bridge-facing output from pre-bridge CME
→ bridge boundary
→ read-side circulation admission
→ receiver/addon-facing circulation
```

### 3.3 Ownership

The component owns:

1. read-side circulation profile definition,
2. receiver-side delay modeling,
3. failed-dispatch list concept,
4. receiver-facing retry profile,
5. delayed release profile,
6. receiver acknowledgement profile,
7. read-side backpressure profile,
8. post-bridge capacity profile,
9. read-side diagnostic reports,
10. dependency map toward bridge/addons.

### 3.4 Non-Ownership

The component does not own:

1. Log-Level API envelope production,
2. pre-bridge ingress,
3. pre-bridge dispatcher internals,
4. bridge orchestration internals,
5. final add-on implementation,
6. database persistence internals,
7. telemetry exporter internals,
8. receiver business logic,
9. raw payload parsing,
10. policy-system execution.

### 3.5 Candidate Subcomponents

```text
read_side_circulation_profile/
├── admission/
├── receiver_context/
├── failed_dispatch/
├── retry/
├── delayed_release/
├── backpressure/
├── receiver_acknowledgement/
├── post_bridge_capacity/
├── diagnostics/
├── boundary_contracts/
└── views/
```

These are preliminary subcomponent candidates, not final folder commitments.

---

## 4. What Cannot Be Settled Yet

### 4.1 Bridge Contract Dependency

Cannot fully settle:

1. exact bridge pull/push shape,
2. bridge acknowledgement model,
3. bridge-facing transfer semantics,
4. whether read-side receives copied/moved/borrowed envelope,
5. bridge failure classification.

Depends on:

```text
Communication_Binding
Dispatcher
Bridge-facing boundary contracts
```

### 4.2 Receiver / Add-on Dependency

Cannot fully settle:

1. receiver acknowledgement semantics,
2. receiver retry rules,
3. add-on-specific backpressure,
4. persistence completion,
5. telemetry/export completion,
6. file sink behavior,
7. database adapter behavior.

Depends on:

```text
addons/
receiver-side contracts
future read-side/addon architecture
```

### 4.3 Capacity Dependency

Cannot fully settle:

1. post-bridge capacity defaults,
2. receiver-side container count,
3. receiver-side slots per container,
4. failed-dispatch list capacity,
5. retry queue/list sizing.

Depends on:

```text
Capacity
Container
Container_Registry
Waiting List
Round_Manager
```

### 4.4 Release Dependency

Cannot fully settle:

1. delayed release trigger,
2. receiver-ack release,
3. bridge-observation release,
4. persistence-completion release.

Depends on:

```text
Release_Recycle
Dispatcher
Communication_Binding
Read-side receiver contract
```

---

## 5. Preliminary Architecture

### 5.1 Read-Side Direction

```text
bridge / post-bridge boundary → read-side profile → receiver/addon side
```

### 5.2 Difference From Pre-Bridge

| Dimension | Pre-Bridge Profile | Read-Side Profile |
|---|---|---|
| Producer | Log API plugin adapter | Bridge-facing boundary |
| Consumer | Bridge-facing adapter | receiver/addon |
| Backpressure | avoided by capacity profile | may be central |
| Retry | not default | likely profile-owned |
| Failed dispatch | deferred | explicit candidate |
| Release | exposure/round/profile | receiver/ack/profile |
| Capacity | extreme pre-sized | receiver-sensitive |
| Persistence | outside | addon-dependent boundary |
| Receiver delay | outside | in scope |

### 5.3 Reusable Mechanism Family

The read-side profile may reuse concepts from the pre-bridge engine:

1. containers,
2. slots,
3. registries,
4. waiting lists,
5. rounds,
6. references,
7. safe points,
8. release/recycle,
9. views/reports,
10. diagnostics.

But reuse does not imply identical profile behavior.

---

## 6. Gap Coverage In This Component

Currently mapped gaps include:

1. `read-side profile`,
2. `read-side backpressure`,
3. `read-side lifecycle`,
4. `receiver lifecycle`,
5. `read-side retry`,
6. `persistence`,
7. `persistence deletion`.

These should not return to pre-bridge CME as ordinary backpressure or retry behavior.

---

## 7. Preliminary Acceptance Criteria

This W00 wave is complete if it establishes:

1. identity,
2. boundary,
3. ownership/non-ownership,
4. candidate subcomponents,
5. dependency matrix,
6. initial gap mapping,
7. deferred decisions,
8. next wave proposal.

---

## 8. Recommended Next Waves

### 8.1 RSCP-W01 — ReadSide Profile Identity And Boundary Contracts

Focus:

```text
admission/
receiver_context/
boundary_contracts/
```

### 8.2 RSCP-W02 — Failed Dispatch And Retry Profile

Focus:

```text
failed_dispatch/
retry/
receiver_acknowledgement/
```

### 8.3 RSCP-W03 — Backpressure And Delayed Release Profile

Focus:

```text
backpressure/
delayed_release/
post_bridge_capacity/
```

### 8.4 RSCP-W04 — Diagnostics And Addon Boundary Integration

Focus:

```text
diagnostics/
views/
addon-facing reports
```
