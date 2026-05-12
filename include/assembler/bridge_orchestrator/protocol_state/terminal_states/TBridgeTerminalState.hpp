#pragma once

#include <string_view>

/**
 * @file TBridgeTerminalState.hpp
 * @brief Bridge-visible protocol terminal-state primitive.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative protocol-state definition
 * for its Communication Context concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical terminal-state vocabulary for bridge protocol lifecycle;
 * - terminal states independent from downstream persistence, telemetry, ABI,
 *   receiver business completion, or endpoint lifecycle;
 * - mapping surface between protocol-stage termination and bridge-result
 *   interpretation.
 *
 * @section ascc_current_wave Current W02 Implementation Scope
 * This W02 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable bridge-visible protocol
 * state categories, transition records, snapshots, and lifecycle values.
 *
 * - terminal-state enum;
 * - terminality helper;
 * - terminal-state string projection.
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
 * - proof of downstream persistence or receiver business completion.
 *
 * @section ascc_dependency_rule Dependency Rule
 * This protocol-state foundation header may depend on W01 primitive carriers
 * and bridge result/error foundations. It must not include endpoint-domain
 * headers such as log_level_api, write_side, read_side, persistence
 * implementations, telemetry SDKs, or thin C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBridgeTerminalState
    {
        none,
        success,
        rejected,
        failed,
        deferred,
        cancelled,
        expired,
        unsupported
    };

    [[nodiscard]] constexpr bool is_terminal_state(TBridgeTerminalState state) noexcept
    {
        return state != TBridgeTerminalState::none;
    }

    [[nodiscard]] constexpr std::string_view to_string(TBridgeTerminalState state) noexcept
    {
        switch (state)
        {
            case TBridgeTerminalState::none: return "none";
            case TBridgeTerminalState::success: return "success";
            case TBridgeTerminalState::rejected: return "rejected";
            case TBridgeTerminalState::failed: return "failed";
            case TBridgeTerminalState::deferred: return "deferred";
            case TBridgeTerminalState::cancelled: return "cancelled";
            case TBridgeTerminalState::expired: return "expired";
            case TBridgeTerminalState::unsupported: return "unsupported";
        }

        return "unknown";
    }
}