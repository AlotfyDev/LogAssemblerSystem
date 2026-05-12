#pragma once

#include <string_view>

#include "assembler/communication_context/protocol_state/stages/TBridgeStage.hpp"

/**
 * @file TBridgeTransition.hpp
 * @brief Bridge-visible protocol transition record.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative protocol-state definition
 * for its Communication Context concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical representation of movement from one bridge-visible protocol
 *   stage to another;
 * - future support for guarded transitions, transition diagnostics, and
 *   protocol-family-specific transition policy;
 * - clear distinction between protocol transition and endpoint internal state
 *   mutation.
 *
 * @section ascc_current_wave Current W02 Implementation Scope
 * This W02 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable bridge-visible protocol
 * state categories, transition records, snapshots, and lifecycle values.
 *
 * - from-stage and to-stage values;
 * - optional bridge-visible reason text;
 * - simple validity and terminal-transition helpers.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - bridge orchestration;
 * - endpoint validation internals;
 * - write-side slot/container/round internals;
 * - endpoint lifecycle state;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, or scheduler semantics;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This protocol-state foundation header may depend on W01 primitive carriers
 * and bridge result/error foundations. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    struct TBridgeTransition final
    {
        TBridgeStage from{TBridgeStage::idle};
        TBridgeStage to{TBridgeStage::idle};
        std::string_view reason{};

        [[nodiscard]] constexpr bool is_self_transition() const noexcept
        {
            return from == to;
        }

        [[nodiscard]] constexpr bool is_terminal_transition() const noexcept
        {
            return is_terminal_bridge_stage(to);
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !is_self_transition();
        }

        [[nodiscard]] static constexpr TBridgeTransition make(
            TBridgeStage from_stage,
            TBridgeStage to_stage,
            std::string_view why = {}) noexcept
        {
            return TBridgeTransition{from_stage, to_stage, why};
        }
    };
}