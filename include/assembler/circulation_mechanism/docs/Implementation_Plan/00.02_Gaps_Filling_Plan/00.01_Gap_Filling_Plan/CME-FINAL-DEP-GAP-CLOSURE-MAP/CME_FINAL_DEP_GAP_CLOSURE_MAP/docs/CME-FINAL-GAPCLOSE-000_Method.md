# CME-FINAL-GAPCLOSE-000 — Method

## 1. Purpose

This package maps final dependency-first phases and waves to the unique gap matrix.

Each wave must declare:

```text
direct_gap_ids
enabled_gap_ids
gap_closure_type
closure_evidence
```

## 2. Closure Types

| Type | Meaning |
|---|---|
| `direct_gap_closure` | Wave directly implements/models the missing capability |
| `dependency_enabler_closure` | Wave does not close a direct gap but enables later gap closure |
| `anti_collapse_guard_or_deferred_scope_registration` | Wave guards a forbidden collapse or records deferred scope |
| `compliance_gate_closure` | Wave proves readiness, compile safety, or negative compliance |

## 3. Phase 1 Clarification

`IDs` and `State` do not close direct functional gaps in the current unique gap matrix.

They close dependency foundations needed by later direct gap closures.
