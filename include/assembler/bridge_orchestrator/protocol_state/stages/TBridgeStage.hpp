#pragma once

#include <string_view>

/**
 * @file TBridgeStage.hpp
 * @brief Bridge-visible protocol stage enumeration.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become the authoritative protocol-state definition
 * for its Communication Context concept when the full ASCC implementation
 * matures. The final version should preserve:
 *
 * - canonical stage vocabulary for bridge protocol execution;
 * - clear distinction between communication-state progress and endpoint-domain
 *   runtime state;
 * - stable stage names for protocols, sessions, diagnostics, snapshots, and
 *   bridge orchestration.
 *
 * @section ascc_current_wave Current W02 Implementation Scope
 * This W02 version intentionally implements only the dependency-foundation
 * subset needed by later phases. It provides stable bridge-visible protocol
 * state categories, transition records, snapshots, and lifecycle values.
 *
 * - stage enum covering idle, setup, readiness, request, admission, handle,
 *   signal, result, closure, and terminal transition points;
 * - constexpr terminal-stage helper;
 * - constexpr stage-name projection.
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
    enum class TBridgeStage
    {
        idle,
        session_opening,
        channel_resolution,
        binding_resolution,
        compatibility_check,
        adapter_readiness,
        request_preparation,
        port_readiness,
        admission_request,
        admission_result,
        handle_exchange,
        adapter_handle_acceptance,
        load_or_delivery_signal,
        next_destination,
        result_consolidation,
        session_closure,
        terminal_success,
        terminal_rejected,
        terminal_failed,
        terminal_deferred
    };

    [[nodiscard]] constexpr bool is_terminal_bridge_stage(TBridgeStage stage) noexcept
    {
        return stage == TBridgeStage::terminal_success
            || stage == TBridgeStage::terminal_rejected
            || stage == TBridgeStage::terminal_failed
            || stage == TBridgeStage::terminal_deferred;
    }

    [[nodiscard]] constexpr std::string_view to_string(TBridgeStage stage) noexcept
    {
        switch (stage)
        {
            case TBridgeStage::idle: return "idle";
            case TBridgeStage::session_opening: return "session_opening";
            case TBridgeStage::channel_resolution: return "channel_resolution";
            case TBridgeStage::binding_resolution: return "binding_resolution";
            case TBridgeStage::compatibility_check: return "compatibility_check";
            case TBridgeStage::adapter_readiness: return "adapter_readiness";
            case TBridgeStage::request_preparation: return "request_preparation";
            case TBridgeStage::port_readiness: return "port_readiness";
            case TBridgeStage::admission_request: return "admission_request";
            case TBridgeStage::admission_result: return "admission_result";
            case TBridgeStage::handle_exchange: return "handle_exchange";
            case TBridgeStage::adapter_handle_acceptance: return "adapter_handle_acceptance";
            case TBridgeStage::load_or_delivery_signal: return "load_or_delivery_signal";
            case TBridgeStage::next_destination: return "next_destination";
            case TBridgeStage::result_consolidation: return "result_consolidation";
            case TBridgeStage::session_closure: return "session_closure";
            case TBridgeStage::terminal_success: return "terminal_success";
            case TBridgeStage::terminal_rejected: return "terminal_rejected";
            case TBridgeStage::terminal_failed: return "terminal_failed";
            case TBridgeStage::terminal_deferred: return "terminal_deferred";
        }

        return "unknown";
    }
}