#pragma once

#include <string_view>

/**
 * @file TBridgeStatus.hpp
 * @brief Bridge Core lifecycle status taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Bridge Core for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable Bridge Core lifecycle vocabulary;
 * - clear distinction between bridge status, protocol status, session status,
 *   and endpoint lifecycle;
 * - textual conversion for diagnostics, snapshots, and future registries.
 *
 * @section ascc_current_wave Current W10 Implementation Scope
 * This W10 version intentionally implements only bridge identity, status,
 * configuration, step budget, orchestration result/view/snapshot, and an
 * endpoint-neutral Bridge Core that advances the W09 protocol model. It does
 * not invoke concrete endpoints, call ports or plugin adapters, own runtime
 * schedulers, allocate external resources, persist traces, or export telemetry.
 *
 * - enum class `TBridgeStatus`;
 * - runnable/terminal helpers;
 * - textual conversion helper.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, thread, or async ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings;
 * - dynamic plugin loading or runtime dependency injection.
 * - scheduler lifecycle, thread lifecycle, or endpoint lifecycle.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Bridge Core headers may depend on W01 carriers/results/errors, W02 protocol
 * state foundations, W08 session model through W09, and W09 bridge protocol
 * model. They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TBridgeStatus
    {
        unknown,
        declared,
        ready,
        running,
        paused,
        completed,
        rejected,
        failed,
        exhausted,
        cancelled
    };

    [[nodiscard]] constexpr bool is_terminal_bridge_status(
        TBridgeStatus status) noexcept
    {
        return status == TBridgeStatus::completed
            || status == TBridgeStatus::rejected
            || status == TBridgeStatus::failed
            || status == TBridgeStatus::exhausted
            || status == TBridgeStatus::cancelled;
    }

    [[nodiscard]] constexpr bool is_runnable_bridge_status(
        TBridgeStatus status) noexcept
    {
        return status == TBridgeStatus::ready
            || status == TBridgeStatus::running;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBridgeStatus status) noexcept
    {
        switch (status)
        {
            case TBridgeStatus::unknown: return "unknown";
            case TBridgeStatus::declared: return "declared";
            case TBridgeStatus::ready: return "ready";
            case TBridgeStatus::running: return "running";
            case TBridgeStatus::paused: return "paused";
            case TBridgeStatus::completed: return "completed";
            case TBridgeStatus::rejected: return "rejected";
            case TBridgeStatus::failed: return "failed";
            case TBridgeStatus::exhausted: return "exhausted";
            case TBridgeStatus::cancelled: return "cancelled";
        }

        return "unknown";
    }
}
