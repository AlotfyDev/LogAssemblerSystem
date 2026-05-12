#pragma once

#include <string_view>

/**
 * @file TBridgeProtocolStatus.hpp
 * @brief Bridge protocol lifecycle status taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Protocol
 * Model for the Communication Context when ASCC matures. The final version
 * should preserve:
 *
 * - stable bridge protocol lifecycle vocabulary;
 * - clear distinction between protocol lifecycle, session lifecycle, and
 *   bridge orchestration lifecycle;
 * - textual conversion for diagnostics, views, and future registries.
 *
 * @section ascc_current_wave Current W09 Implementation Scope
 * This W09 version intentionally implements only protocol identity, status,
 * step/plan/frame/result/view/trace, and a bridge-visible protocol value that
 * advances declared protocol state over an already open Session. It does not
 * orchestrate bridges, invoke endpoints, call ports or plugin adapters,
 * allocate resources, run schedulers, or own endpoint lifecycle.
 *
 * - enum class `TBridgeProtocolStatus`;
 * - runnable/terminal helpers;
 * - textual conversion helper.
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
 * - scheduler lifecycle, thread lifecycle, or endpoint lifecycle.
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
    enum class TBridgeProtocolStatus
    {
        unknown,
        declared,
        ready,
        active,
        completed,
        rejected,
        failed,
        deferred,
        cancelled
    };

    [[nodiscard]] constexpr bool is_terminal_bridge_protocol_status(
        TBridgeProtocolStatus status) noexcept
    {
        return status == TBridgeProtocolStatus::completed
            || status == TBridgeProtocolStatus::rejected
            || status == TBridgeProtocolStatus::failed
            || status == TBridgeProtocolStatus::deferred
            || status == TBridgeProtocolStatus::cancelled;
    }

    [[nodiscard]] constexpr bool is_runnable_bridge_protocol_status(
        TBridgeProtocolStatus status) noexcept
    {
        return status == TBridgeProtocolStatus::ready
            || status == TBridgeProtocolStatus::active;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBridgeProtocolStatus status) noexcept
    {
        switch (status)
        {
            case TBridgeProtocolStatus::unknown: return "unknown";
            case TBridgeProtocolStatus::declared: return "declared";
            case TBridgeProtocolStatus::ready: return "ready";
            case TBridgeProtocolStatus::active: return "active";
            case TBridgeProtocolStatus::completed: return "completed";
            case TBridgeProtocolStatus::rejected: return "rejected";
            case TBridgeProtocolStatus::failed: return "failed";
            case TBridgeProtocolStatus::deferred: return "deferred";
            case TBridgeProtocolStatus::cancelled: return "cancelled";
        }

        return "unknown";
    }
}
