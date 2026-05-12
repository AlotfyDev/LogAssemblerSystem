#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TLogLevelAPIEnvelopePluginAdapterConfig.hpp
 * @brief Configuration for the Log Level API envelope plugin adapter.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the concrete Log Level API envelope
 * plugin-adapter binding surface when ASCC matures. The final version should
 * preserve:
 *
 * - stable adapter identity, participant identity, domain labels, and
 *   destination defaults;
 * - future extension point for endpoint-neutral adapter policy without
 *   including Log Level API or Write Side internals;
 * - no runtime dependency injection or dynamic plugin loading.
 *
 * @section ascc_current_wave Current W14A Implementation Scope
 * This W14A version implements the content-side concrete adapter surface only.
 * It adapts a bridge-visible Log Level Envelope descriptor into W05
 * `TPluginAdapter` obligations and remains compatible with W01-W10
 * Communication Context foundations. It does not implement the Log Level API
 * facade, the Envelope Assembler, the Write Side host port, the Write Side
 * placement internals, or endpoint runtime execution.
 *
 * - adapter id;
 * - participant id and display labels;
 * - default domain/family/destination strings;
 * - validity helper and default factory.
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
 * - endpoint runtime configuration or DI container configuration.
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
    struct TLogLevelAPIEnvelopePluginAdapterConfig final
    {
        std::uint64_t adapter_id{1401u};
        std::uint64_t participant_id{14001u};
        std::string_view participant_domain{"log_level_api"};
        std::string_view participant_family{"envelope_plugin_adapter"};
        std::string_view display_name{"LogLevelAPI Envelope PluginAdapter"};
        std::string_view requested_destination_family{"write_side"};
        std::uint32_t adapter_version{1u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return adapter_id != 0u
                && participant_id != 0u
                && !participant_domain.empty()
                && !participant_family.empty()
                && !requested_destination_family.empty()
                && adapter_version > 0u;
        }

        [[nodiscard]] static constexpr TLogLevelAPIEnvelopePluginAdapterConfig defaults() noexcept
        {
            return TLogLevelAPIEnvelopePluginAdapterConfig{};
        }
    };
}
