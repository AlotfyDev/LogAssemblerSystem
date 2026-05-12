# ASCC-COMP-W01B — Local Tree Delta Analysis

## 1. Purpose

This document records the delta between the previous GitHub-index-derived audit files and the newer local working-tree evidence supplied for the Bridge Orchestrator / Communication Context filesystem.

No code changes are made by this document.  It updates the audit evidence model only.

## 2. Evidence Rule

The W01 audit now treats filesystem evidence in this order:

```text
1. Local working-tree tree /f output when supplied by the maintainer
2. GitHub repository file fetch / search
3. Existing repository index markdown
4. SmokeTests_SystemView CSVs and diagrams
```

CSV files remain useful empirical documentation, but they are not absolute truth.

## 3. Main Delta Findings

### 3.1 W14A concrete LogAPI adapter files are confirmed present locally

The previous reconciliation matrix classified these as `reality_check_required` because the older GitHub-index tree omitted root files under the W14A folder.

Local tree confirms the following files exist:

```text
bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapter.hpp
bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapterBinding.hpp
bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/policies/TLogLevelAPIEnvelopePluginAdapterReadinessPolicy.hpp
```

Audit correction:

```text
W14A root adapter and binding are no longer missing/reality-check-only.
They are local-tree-confirmed path-backed headers.
```

### 3.2 W14B concrete write-side placement port root file is confirmed present locally

The previous matrix classified `TWriteSideEnvelopePlacementPort.hpp` as `reality_check_required` because the older index omitted it.

Local tree confirms:

```text
bindings/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPort.hpp
bindings/concrete_bindings/write_side/envelope_placement_port/TWriteSideEnvelopePlacementPortBinding.hpp
```

Audit correction:

```text
W14B placement port root implementation is local-tree-confirmed path-backed.
```

### 3.3 Registry delivery plugin adapter subtree is richer than the older index indicated

Local tree confirms the registry-delivery binding surface includes:

```text
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/TWriteSideRegistryDeliveryPluginAdapter.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/TWriteSideRegistryDeliveryPluginAdapterBinding.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/carriers/TWriteSideRegistryDeliveryMaterialDescriptor.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/config/TWriteSideRegistryDeliveryPluginAdapterConfig.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/factory/TWriteSideRegistryDeliveryPluginAdapterFactory.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/policies/TWriteSideRegistryDeliveryReadinessPolicy.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/state/TWriteSideRegistryDeliveryPluginAdapterState.hpp
bindings/concrete_bindings/write_side/registry_delivery_plugin_adapter/views/TWriteSideRegistryDeliveryPluginAdapterViewBuilder.hpp
```

Audit implication:

```text
Registry delivery is not just a single placeholder adapter file.
It has a concrete binding/support subtree and must be included in later ASCC-INT or composability audits.
```

### 3.4 Temporary comparison file exists locally

Local tree shows:

```text
bindings/concrete_bindings/write_side/envelope_placement_port/factory/Temp_Version_To_Compare.hpp
```

Audit classification:

```text
local_temp_or_review_artifact
```

No cleanup action is taken in W01B.  It should be considered in W01C remediation decisions only after confirming whether it is intentional or stale.

### 3.5 Tests layout differs from the older GitHub-index tree

Local tree shows compiled executables under:

```text
tests/smoke_tests_resulted_executables/
```

while the older index had executable entries mixed under `tests/smoke-tests/`.

Audit correction:

```text
Local test layout is cleaner and should be treated as the current layout evidence.
```

### 3.6 Docs tree is richer than the first repo-index view

Local folders evidence confirms:

```text
docs/holistic_docs/{architecture,evolution,flows,layers,patterns,plan,principles,qa,references,relationships}
docs/SmokeTests_SystemView/w01_smoke_test ... w15_smoke_test
```

Audit implication:

```text
Docs inventory must include both holistic docs and SmokeTests_SystemView.
W01 audit should not reduce docs evidence to only the component CSVs.
```

## 4. Reconciliation Matrix Corrections Required

| Matrix Row | Previous Classification | Corrected Classification |
|---|---|---|
| ASCC-COMP-W01B-057 | `reality_check_required` | `local_tree_confirmed_path_backed` |
| ASCC-COMP-W01B-058 | `reality_check_required` | `local_tree_confirmed_path_backed` |
| ASCC-COMP-W01B-060 | `reality_check_required` | `local_tree_confirmed_path_backed` |

Additional rows should be added for:

```text
TWriteSideRegistryDeliveryPluginAdapterBinding
TWriteSideRegistryDeliveryMaterialDescriptor
TWriteSideRegistryDeliveryPluginAdapterConfig
TWriteSideRegistryDeliveryPluginAdapterFactory
TWriteSideRegistryDeliveryReadinessPolicy
TWriteSideRegistryDeliveryPluginAdapterState
TWriteSideRegistryDeliveryPluginAdapterViewBuilder
Temp_Version_To_Compare.hpp
```

## 5. Updated W01B Rule

Before applying any more code cleanup, W01B must reconcile three sources:

```text
1. current local tree evidence
2. GitHub fetch/search reality
3. SmokeTests_SystemView CSV claims
```

Only after that can W01C decide safe cleanup actions.

## 6. No-Code-Change Status

This delta analysis performs no header modifications.

The next safe action is to update the W01A/W01B CSV audit artifacts to incorporate local-tree-confirmed entries and mark the older index omissions as stale/incomplete evidence.
