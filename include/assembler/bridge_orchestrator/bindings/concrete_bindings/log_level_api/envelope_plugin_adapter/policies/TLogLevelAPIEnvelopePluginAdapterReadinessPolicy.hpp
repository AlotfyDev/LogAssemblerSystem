#pragma once

#include "assembler/communication_context/bindings/concrete_bindings/log_level_api/envelope_plugin_adapter/carriers/TLogLevelEnvelopeDescriptor.hpp"

/**
 * @file TLogLevelAPIEnvelopePluginAdapterReadinessPolicy.hpp
 * @brief Readiness policy for the Log Level API envelope plugin adapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - endpoint-neutral readiness rules for adapting a prepared Log Level
 *   Envelope descriptor into Communication Context obligations;
 * - future extension point for adapter-side eligibility checks without
 *   importing full Log Level API validation internals;
 * - clear distinction between descriptor readiness and content validation.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - descriptor readiness check;
 * - readiness capacity hint projection;
 * - no envelope validation or policy-bound validator behavior.
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
 * - Log Level API validation policy.
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
    struct TLogLevelAPIEnvelopePluginAdapterReadinessPolicy final
    {
        [[nodiscard]] static constexpr bool descriptor_is_ready(
            const TLogLevelEnvelopeDescriptor& descriptor) noexcept
        {
            return descriptor.is_valid();
        }

        [[nodiscard]] static constexpr std::uint64_t readiness_capacity_hint(
            const TLogLevelEnvelopeDescriptor& descriptor) noexcept
        {
            return descriptor.is_valid() ? 1u : 0u;
        }
    };
}
