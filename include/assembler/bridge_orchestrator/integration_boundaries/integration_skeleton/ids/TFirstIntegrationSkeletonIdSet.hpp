#pragma once

#include "assembler/communication_context/bindings/ids/TBindingId.hpp"
#include "assembler/communication_context/bridge_core/ids/TBridgeId.hpp"
#include "assembler/communication_context/protocols/ids/TBridgeProtocolId.hpp"
#include "assembler/communication_context/sessions/ids/TSessionId.hpp"
#include "assembler/communication_context/integration_boundaries/integration_skeleton/config/TFirstIntegrationSkeletonConfig.hpp"

/**
 * @file TFirstIntegrationSkeletonIdSet.hpp
 * @brief Typed ID set for the first ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - explicit typed IDs derived from W15 config;
 * - bridge-visible identity continuity across binding/session/protocol/bridge;
 * - no global registry or ID allocator behavior.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - typed ID conversion helpers;
 * - channel id exposure;
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
    struct TFirstIntegrationSkeletonIdSet final
    {
        std::uint64_t channel_id{0u};
        TBindingId binding_id{TBindingId::invalid()};
        TSessionId session_id{TSessionId::invalid()};
        TBridgeProtocolId protocol_id{TBridgeProtocolId::invalid()};
        TBridgeId bridge_id{TBridgeId::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return channel_id != 0u
                && binding_id.is_valid()
                && session_id.is_valid()
                && protocol_id.is_valid()
                && bridge_id.is_valid();
        }

        [[nodiscard]] static constexpr TFirstIntegrationSkeletonIdSet from_config(
            const TFirstIntegrationSkeletonConfig& config) noexcept
        {
            return TFirstIntegrationSkeletonIdSet{
                config.channel_id,
                TBindingId::from_value(config.binding_id),
                TSessionId::from_value(config.session_id),
                TBridgeProtocolId::from_value(config.protocol_id),
                TBridgeId::from_value(config.bridge_id)
            };
        }
    };
}
