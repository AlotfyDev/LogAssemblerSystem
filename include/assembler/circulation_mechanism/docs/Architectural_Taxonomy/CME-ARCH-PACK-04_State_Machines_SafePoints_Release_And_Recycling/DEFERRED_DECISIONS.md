# DEFERRED DECISIONS — CME-ARCH-PACK-04

## 1. State Representation

Pending:

```text
enum class only
state descriptor structs
state + issue record
state + generation token
```

## 2. Transition Guards

Pending:

```text
local guard headers
policy traits
compile-time constraints
runtime diagnostic checks
```

## 3. Safe Point Location

Pending:

```text
shared safe_points/ root
or component-local safe_point files under each owner
```

## 4. Release Trigger For Dispatch

Pending:

```text
release on passive exposure
release on bridge pull observation
release on dispatch round completion
release deferred to read-side profile
```

## 5. Recycle Timing

Pending:

```text
immediate moderator reset
queued reset
next-cycle reset
batch reset at round boundary
```
