#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"

/**
 * @file TBridgeProtocolStep.hpp
 * @brief Declared bridge protocol step.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable declaration of one bridge-visible protocol step;
 * - future support for guards, endpoint-neutral obligations, evidence
 *   requirements, and trace labels;
 * - no endpoint invocation or bridge orchestration.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - order, from-stage, to-stage, name, and optional/terminal flags;
 * - validity and terminal helpers;
 * - static factory helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - runtime endpoint call closure or executable callback.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Protocol Model headers may depend on W01 carriers/results/errors,
 * W02 protocol-state foundations, W06 binding model through sessions, W07
 * compatibility through sessions, and W08 session model. They must not include
 * endpoint-domain headers such as log_level_api, write_side, read_side,
 * persistence implementations, telemetry SDKs, or thin C ABI implementation
 * internals.
 */

namespace assembler::communication_context
{
    struct TBridgeProtocolStep final
    {
        std::uint32_t order{0u};
        TBridgeStage from{TBridgeStage::idle};
        TBridgeStage to{TBridgeStage::idle};
        std::string_view step_name{};
        bool optional{false};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return order > 0u
                && from != to
                && !is_terminal_bridge_stage(from);
        }

        [[nodiscard]] constexpr bool is_terminal_step() const noexcept
        {
            return is_terminal_bridge_stage(to);
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return !optional;
        }

        [[nodiscard]] static constexpr TBridgeProtocolStep make(
            std::uint32_t step_order,
            TBridgeStage from_stage,
            TBridgeStage to_stage,
            std::string_view name = {},
            bool is_optional = false) noexcept
        {
            return TBridgeProtocolStep{
                step_order,
                from_stage,
                to_stage,
                name,
                is_optional
            };
        }
    };
}
