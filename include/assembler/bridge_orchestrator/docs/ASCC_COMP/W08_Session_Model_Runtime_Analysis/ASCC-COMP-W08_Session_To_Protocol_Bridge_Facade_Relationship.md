# ASCC-COMP-W08 — Session To Protocol, Bridge, And Facade Relationship

## Session To Protocol

A protocol is declared over an already open session.

```text
TSessionOpenRequest
    -> TSession::open()
    -> TSessionProtocolBootstrapPolicy
    -> TBridgeProtocol::declare(open_session, plan)
```

## Session To Bridge Core

Bridge Core consumes a ready protocol. It should not bypass session readiness.

```text
TSession
    -> TBridgeProtocol
        -> TBridge
```

## Session To Facade

Pipeline Composer and facade consumers should not mutate sessions directly.
They should consume facade projections and policies.
