# ASCC-COMP-W09 — Protocol To Bridge Core Execution Relationship

## 1. Relationship

```text
TBridge
    -> TBridgeProtocol
        -> TBridgeProtocolPlan
            -> TBridgeProtocolStep
```

`TBridge` owns bridge-level orchestration and budget.

`TBridgeProtocol` owns protocol-level model advancement.

This package adds the missing middle layer between protocol steps and future invocation:

```text
TProtocolStepRequirementBinding
TProtocolStepObligationBinding
TProtocolStepInvocationDescriptor
TProtocolStepExecutionPolicy
```

## 2. Anti-Collapse Rule

`TBridgeProtocolStep` must remain a stage transition descriptor.

It must not become:

```text
callback
endpoint closure
adapter call object
port invocation object
```

## 3. Execution Flow

```text
TBridgeStepExecutor
    -> TBridge::step_model_report()
    -> TBridgeProtocol::advance_model_step()
    -> TProtocolStepExecutionPolicy checks whether invocation is allowed
    -> TProtocolStepInvocationDescriptor describes optional invocation
```

Actual adapter/port invocation remains an explicit later boundary.
