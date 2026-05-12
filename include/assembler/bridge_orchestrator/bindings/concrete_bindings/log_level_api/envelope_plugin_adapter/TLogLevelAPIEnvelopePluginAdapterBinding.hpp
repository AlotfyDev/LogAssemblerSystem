#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapter.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/carriers/TLogLevelEnvelopeDescriptor.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/config/TLogLevelAPIEnvelopePluginAdapterConfig.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/factory/TLogLevelAPIEnvelopePluginAdapterFactory.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/policies/TLogLevelAPIEnvelopePluginAdapterReadinessPolicy.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/state/TLogLevelAPIEnvelopePluginAdapterState.hpp"
#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/views/TLogLevelAPIEnvelopePluginAdapterViewBuilder.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapterBinding.hpp
 * @brief Aggregate include for W14A Log Level API envelope plugin-adapter binding.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - single include surface for the W14A concrete content-side adapter;
 * - stable dependency point for later W14B/W14C concrete binding waves;
 * - explicit marker that W14A realizes only the plugin-adapter side.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - aggregate include;
 * - availability marker;
 * - no additional runtime behavior.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - Log Level API facade implementation;
 * - Envelope Assembler internals;
 * - content validation internals;
 * - metadata injection or timestamp stabilization internals;
 * - Write Side placement port implementation;
 * - Write Side slot/container/round internals;
 * - bridge orchestration beyond W10 model stepping;
 * - registry, database, persistence, telemetry, scheduler, thread, or ABI behavior;
 * - dynamic plugin loading or runtime dependency injection.
 * - concrete Write Side placement port or complete bridge execution.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W14A concrete adapter headers may depend on W01 primitive carriers, W03
 * participants, W05 `TPluginAdapter` obligations, and W10 aggregate bridge
 * surfaces for smoke-test compatibility. They must not include concrete
 * `assembler/log_level_api/...` or `assembler/write_side/...` endpoint-domain
 * internals until those domains are separately realized and explicitly bridged.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_W14A_LOG_LEVEL_API_ENVELOPE_PLUGIN_ADAPTER_AVAILABLE = true;
}
