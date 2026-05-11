# DEFERRED DECISIONS — CME-ARCH-PACK-02

## 1. Round Manager Shape

Decision deferred:

```text
one generic RoundManager with round-kind profiles
vs
separate IngressRoundManager / DispatchRoundManager
```

## 2. Waiting List Type Shape

Decision deferred:

```text
TIngressWaitingList and TDispatchWaitingList as distinct types
vs
TWaitingList<RoundKind>
```

## 3. Dispatch Consumption Acknowledgement

Decision deferred:

```text
release on passive exposure
vs
release on bridge pull observation
vs
release on dispatch round closure
```

## 4. Push Dispatch

Decision deferred:

```text
optional push dispatch inside CME
vs
push modeled only as bridge/output adapter behavior
```

## 5. Time-Range Ordering Policy

Decision deferred:

```text
FIFO primary with time-range tie-break
vs
oldest time-range first
vs
time-range only for eviction
```
