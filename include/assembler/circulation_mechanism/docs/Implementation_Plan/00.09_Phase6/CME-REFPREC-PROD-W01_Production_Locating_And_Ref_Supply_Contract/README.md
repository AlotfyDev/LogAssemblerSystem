
# CME-REFPREC-PROD-W01 — Production Locating And Ref Supply Contract

## Delivered Capabilities

```text
reference handles and scopes
reference validity decisions
candidate model
waiting-list candidate consumption by array input
container registry resolution through try_get()
container state validation
slot selection through container view methods
ingress ref production
dispatch ref production
fixed-capacity ingress/dispatch ref pools
next-ref peek/pop
candidate rejection reporting
supply interruption reporting
negative compliance tests
```

## Expected Registry / Container Interface

```cpp
registry.try_get(TContainerRegistryIndex) -> const Container*
registry.generation() -> std::uint64_t
container.state() -> TContainerState
container.find_first_ingress_writable_slot() -> TSlotIndex
container.find_first_dispatch_ready_slot() -> TSlotIndex
```

## Explicit Non-Ownership

```text
No registry mutation
No container mutation
No slot mutation
No ingress placement
No dispatch exposure
No bridge behavior
No payload content inspection
```
