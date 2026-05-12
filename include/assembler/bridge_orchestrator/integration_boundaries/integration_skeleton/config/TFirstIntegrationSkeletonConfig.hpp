#pragma once

#include <cstdint>
#include <string_view>

/**
 * @file TFirstIntegrationSkeletonConfig.hpp
 * @brief Configuration for the first ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - stable integration IDs for channel, binding, session, protocol, and bridge;
 * - payload descriptor defaults for the W14A adapter;
 * - bridge budget and naming defaults;
 * - no endpoint resource configuration.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - lightweight ID and label configuration;
 * - default factory;
 * - validity helper.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete endpoint-domain internals;
 * - Write Side slot/container/round implementation;
 * - Log Level API envelope assembly, validation, metadata, or timestamp internals;
 * - runtime scheduling, threading, async execution, persistence, telemetry, ABI, or database behavior;
 * - replacing W09 protocol model or W10 bridge model-step orchestration;
 * - hiding bridge-visible failure/report states.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W15 may depend on W01-W10, W14A, and W14B public include surfaces.
 * It must not include concrete endpoint-domain headers such as
 * `assembler/log_level_api/...` or `assembler/write_side/...` internals.
 */

namespace assembler::communication_context
{
    struct TFirstIntegrationSkeletonConfig final
    {
        std::uint64_t channel_id{1501u};
        std::uint64_t binding_id{1502u};
        std::uint64_t session_id{1503u};
        std::uint64_t protocol_id{1504u};
        std::uint64_t bridge_id{1505u};
        std::uint32_t max_bridge_model_steps{16u};
        std::string_view envelope_id{"w15-log-level-envelope"};
        std::uint64_t payload_size_hint{256u};
        std::string_view channel_name{"w15_log_level_api_to_write_side_channel"};
        std::string_view binding_name{"w15_log_level_api_to_write_side_binding"};
        std::string_view session_name{"w15_first_integration_session"};
        std::string_view protocol_name{"w15_envelope_placement_protocol"};
        std::string_view bridge_name{"w15_first_integration_bridge"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return channel_id != 0u
                && binding_id != 0u
                && session_id != 0u
                && protocol_id != 0u
                && bridge_id != 0u
                && max_bridge_model_steps > 0u
                && !envelope_id.empty()
                && !channel_name.empty()
                && !binding_name.empty()
                && !session_name.empty()
                && !protocol_name.empty()
                && !bridge_name.empty();
        }

        [[nodiscard]] static constexpr TFirstIntegrationSkeletonConfig defaults() noexcept
        {
            return TFirstIntegrationSkeletonConfig{};
        }
    };
}
