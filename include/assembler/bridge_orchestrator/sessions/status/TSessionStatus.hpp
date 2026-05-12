#pragma once

#include <string_view>

/**
 * @file TSessionStatus.hpp
 * @brief Bridge-visible session lifecycle status taxonomy.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to become part of the authoritative Session Model for
 * the Communication Context when ASCC matures. The final version should
 * preserve:
 *
 * - stable session lifecycle vocabulary for pending, open, active,
 *   closing, completed, rejected, failed, deferred, suspended, and expired
 *   states;
 * - clear distinction between session state and protocol-stage execution;
 * - textual conversion for diagnostics and future validation reports.
 *
 * @section ascc_current_wave Current W08 Implementation Scope
 * This W08 version intentionally implements only session identity, opening
 * request, lifecycle status, snapshot/view/result, and declaration-level
 * session state around a compatible binding. It may hold protocol state as
 * bridge-visible lifecycle metadata, but it does not execute protocol steps,
 * orchestrate bridges, invoke endpoints, allocate endpoint resources, or own
 * endpoint lifecycle.
 *
 * - enum class `TSessionStatus`;
 * - active/terminal/openable helpers;
 * - textual conversion helper.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - protocol execution or protocol stepping;
 * - bridge orchestration or bridge loop ownership;
 * - concrete adapter-port invocation;
 * - endpoint-domain validation internals;
 * - write-side slot/container/round internals;
 * - registry, database, persistence, or telemetry behavior;
 * - broker, queue, dispatcher, scheduler, or thread ownership;
 * - concrete Log Level API, Write Side, or Read Side bindings.
 * - full state machine execution or timeout scheduling.
 *
 * @section ascc_dependency_rule Dependency Rule
 * Session model headers may depend on W01 carriers/results/errors, W02
 * protocol-state foundations, W06 binding model, and W07 compatibility model.
 * They must not include endpoint-domain headers such as log_level_api,
 * write_side, read_side, persistence implementations, telemetry SDKs, or thin
 * C ABI implementation internals.
 */

namespace assembler::communication_context
{
    enum class TSessionStatus
    {
        unknown,
        pending_open,
        open,
        active,
        closing,
        completed,
        rejected,
        failed,
        deferred,
        suspended,
        expired
    };

    [[nodiscard]] constexpr bool is_terminal_session_status(
        TSessionStatus status) noexcept
    {
        return status == TSessionStatus::completed
            || status == TSessionStatus::rejected
            || status == TSessionStatus::failed
            || status == TSessionStatus::deferred
            || status == TSessionStatus::expired;
    }

    [[nodiscard]] constexpr bool is_open_session_status(
        TSessionStatus status) noexcept
    {
        return status == TSessionStatus::open
            || status == TSessionStatus::active
            || status == TSessionStatus::closing;
    }

    [[nodiscard]] constexpr bool can_close_session_status(
        TSessionStatus status) noexcept
    {
        return status == TSessionStatus::open
            || status == TSessionStatus::active
            || status == TSessionStatus::suspended;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TSessionStatus status) noexcept
    {
        switch (status)
        {
            case TSessionStatus::unknown: return "unknown";
            case TSessionStatus::pending_open: return "pending_open";
            case TSessionStatus::open: return "open";
            case TSessionStatus::active: return "active";
            case TSessionStatus::closing: return "closing";
            case TSessionStatus::completed: return "completed";
            case TSessionStatus::rejected: return "rejected";
            case TSessionStatus::failed: return "failed";
            case TSessionStatus::deferred: return "deferred";
            case TSessionStatus::suspended: return "suspended";
            case TSessionStatus::expired: return "expired";
        }

        return "unknown";
    }
}
