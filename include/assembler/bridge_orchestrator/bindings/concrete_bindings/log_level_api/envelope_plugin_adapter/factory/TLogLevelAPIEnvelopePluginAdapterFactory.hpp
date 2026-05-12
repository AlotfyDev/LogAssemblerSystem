#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/TLogLevelAPIEnvelopePluginAdapter.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapterFactory.hpp
 * @brief Factory helpers for Log Level API envelope plugin adapter construction.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - stable construction helpers for the W14A concrete adapter;
 * - future extension point for creation from real Log Level API envelope
 *   objects once that endpoint domain is realized;
 * - no ownership of endpoint factories or DI containers.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - creation from descriptor;
 * - creation from minimal envelope fields;
 * - no dynamic allocation.
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
 * - Log Level API object factory or runtime plugin loader.
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
    struct TLogLevelAPIEnvelopePluginAdapterFactory final
    {
        [[nodiscard]] static constexpr TLogLevelAPIEnvelopePluginAdapter from_descriptor(
            TLogLevelEnvelopeDescriptor descriptor,
            TLogLevelAPIEnvelopePluginAdapterConfig config =
                TLogLevelAPIEnvelopePluginAdapterConfig::defaults()) noexcept
        {
            return TLogLevelAPIEnvelopePluginAdapter(descriptor, config);
        }

        [[nodiscard]] static constexpr TLogLevelAPIEnvelopePluginAdapter from_fields(
            TCorrelationToken token,
            std::string_view envelope_id,
            std::uint64_t payload_size_hint = 0u,
            TLogLevelAPIEnvelopePluginAdapterConfig config =
                TLogLevelAPIEnvelopePluginAdapterConfig::defaults()) noexcept
        {
            return TLogLevelAPIEnvelopePluginAdapter(
                TLogLevelEnvelopeDescriptor::make(
                    token,
                    envelope_id,
                    payload_size_hint,
                    true,
                    config.requested_destination_family),
                config);
        }
    };
}
