# DEFERRED DECISIONS — CME-ARCH-PACK-05

## 1. Push Profile Implementation

Pending:

```text
dispatcher-owned optional push
output-adapter-owned push
bridge-owned push only
```

## 2. Bridge Pull Observation

Pending:

```text
required for release
optional diagnostic
not modeled in first implementation
```

## 3. Failed Dispatch List

Pending:

```text
read-side only
pre-bridge disabled-by-default profile
shared template with distinct profile
```

## 4. Read-Side Package Location

Pending:

```text
same circulation_mechanism root with read_side profile
separate read_side/ domain
bridge/addon-owned profile
```

## 5. Release Trigger

Pending:

```text
on exposure
on bridge pull observation
on dispatch round completion
on read-side acknowledgement
```
