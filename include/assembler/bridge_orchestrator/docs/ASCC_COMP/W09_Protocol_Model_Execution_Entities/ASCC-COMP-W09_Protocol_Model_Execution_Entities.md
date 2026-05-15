# ASCC-COMP-W09 — Protocol Model Execution Entities

## 1. Purpose

This package adds the missing protocol execution-support layer above the existing protocol model.

The existing `TBridgeProtocol` already contains header-only model execution:

```text
declare
activate
advance_model_step
reject
fail
view
frame
trace
```

But `TBridgeProtocolStep` and `TBridgeProtocolPlan` are still endpoint-neutral step declarations. They do not bind a step to:

```text
participant requirements
carrier requirements
binding requirements
obligation surfaces
endpoint invocation descriptors
step evidence requirements
```

## 2. Core Rule

```text
TBridgeProtocol remains the protocol model runtime.
TBridgeProtocolStep remains a stage-transition descriptor.
Protocol execution support must bind steps to requirements and obligations
without turning TBridgeProtocolStep into a callback or endpoint closure.
```

## 3. Included Entities

```text
protocols/bindings/TProtocolStepRequirementBinding.hpp
protocols/bindings/TProtocolStepObligationBinding.hpp
protocols/invocation/TProtocolStepInvocationDescriptor.hpp
protocols/policies/TProtocolStepExecutionPolicy.hpp
protocols/evidence/TProtocolStepEvidenceRequirement.hpp
protocols/reports/TProtocolPlanReadinessReport.hpp
protocols/matching/TProtocolRequirementMatcher.hpp

facade_layer/administrative/TAsccProtocolCatalogView.hpp
facade_layer/managerial/TAsccProtocolReadinessView.hpp
facade_layer/managerial/TAsccProtocolAdmissionPolicy.hpp
facade_layer/managerial/TProtocolRequirementFacadeAdapter.hpp
```

## 4. Closure

The package operationalizes the missing middle layer:

```text
TBridgeProtocolStep
    -> protocol requirements
    -> participant/binding/carrier obligations
    -> invocation descriptor
    -> execution policy
    -> readiness/evidence reports
```
