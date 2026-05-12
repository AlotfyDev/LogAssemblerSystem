#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_core/results/TBridgeCoreResult.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/handles/TPlacementHandle.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"

/**
 * @file TFirstIntegrationSkeletonReport.hpp
 * @brief Result report for the first ASCC integration skeleton.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the first ASCC integration skeleton.
 * The final version should preserve:
 *
 * - unified diagnostic report spanning model skeleton and carrier flow;
 * - explicit booleans for each integration stage;
 * - preservation of bridge-visible results without endpoint-internal state.
 *
 * @section ascc_current_wave Current W15 Implementation Scope
 * This W15 version validates that W14A and W14B can be placed into the
 * existing W01-W10 Communication Context model as a coherent integration
 * skeleton. It intentionally remains a skeleton, not a production runtime.
 *
 * - model flags;
 * - flow flags;
 * - bridge/core result values;
 * - success and failure-note helpers.
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
    struct TFirstIntegrationSkeletonReport final
    {
        bool config_valid{false};
        bool adapter_view_valid{false};
        bool port_view_valid{false};
        bool channel_valid{false};
        bool surface_pair_valid{false};
        bool binding_compatible{false};
        bool session_open{false};
        bool protocol_ready{false};
        bool bridge_declared{false};
        bool bridge_model_completed{false};

        bool adapter_ready{false};
        bool placement_request_valid{false};
        bool port_ready{false};
        bool admission_accepted{false};
        bool placement_handle_valid{false};
        bool adapter_accepted_handle{false};
        bool load_signal_completed{false};
        bool port_received_load_signal{false};
        bool next_destination_acknowledged{false};

        TAdmissionResult admission{};
        TPlacementHandle placement_handle{TPlacementHandle::invalid()};
        TBridgeResult adapter_handle_result{};
        TBridgeResult load_signal_result{};
        TBridgeResult next_destination_result{};
        TBridgeCoreResult bridge_model_result{};
        std::string_view failure_note{};

        [[nodiscard]] constexpr bool model_succeeded() const noexcept
        {
            return config_valid
                && adapter_view_valid
                && port_view_valid
                && channel_valid
                && surface_pair_valid
                && binding_compatible
                && session_open
                && protocol_ready
                && bridge_declared
                && bridge_model_completed;
        }

        [[nodiscard]] constexpr bool flow_succeeded() const noexcept
        {
            return adapter_ready
                && placement_request_valid
                && port_ready
                && admission_accepted
                && placement_handle_valid
                && adapter_accepted_handle
                && load_signal_completed
                && port_received_load_signal
                && next_destination_acknowledged;
        }

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return model_succeeded() && flow_succeeded();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !succeeded();
        }

        constexpr void mark_failure(std::string_view note) noexcept
        {
            if (failure_note.empty())
            {
                failure_note = note;
            }
        }
    };
}
