#pragma once

#include "assembler/communication_context/bridge_core/TBridge.hpp"
#include "assembler/communication_context/bridge_core/budget/TBridgeStepBudget.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeConfig.hpp"
#include "assembler/communication_context/bridge_core/config/TBridgeRunMode.hpp"
#include "assembler/communication_context/bridge_core/frames/TBridgeCoreFrame.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"
#include "assembler/communication_context/bridge_core/policies/TBridgeCorePolicy.hpp"
#include "assembler/communication_context/bridge_core/reports/TBridgeCoreStepReport.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/snapshots/TBridgeCoreSnapshot.hpp"
#include "assembler/communication_context/bridge_core/status/TBridgeStatus.hpp"
#include "assembler/communication_context/bridge_core/traces/TBridgeCoreTrace.hpp"
#include "assembler/communication_context/bridge_core/views/TBridgeCoreView.hpp"

/**
 * @file TBridgeCore.hpp
 * @brief Aggregate include for W10 Bridge Core.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - single aggregate include for the W10 Bridge Core surface;
 * - stable entry point for downstream waves, tests, and examples;
 * - future compatibility surface for public include documentation.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - includes the Bridge Core identity, config, budget, status, issue,
 *   frame, snapshot, view, result, trace, report, policy, and TBridge value.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - implementation translation-unit ownership.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_W10_BRIDGE_CORE_AVAILABLE = true;
}
