#pragma once

#include <string_view>

/**
 * @file TBoundaryHandoffStatus.hpp
 * @brief Status taxonomy for abstract boundary handoff attempts.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - small status vocabulary for abstract handoff attempts;
 * - distinction between accepted, rejected, deferred, completed, failed, and
 *   unsupported;
 * - conversion helpers for diagnostics and later reports.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - enum class `TBoundaryHandoffStatus`;
 * - terminal/failure helper;
 * - textual conversion.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This file must not implement or expose:
 *
 * - concrete persistence, telemetry, ABI, read-side, or external receiver
 *   integration;
 * - endpoint-domain internals;
 * - adapter/port call wiring for concrete endpoints;
 * - storage, database, file IO, network IO, telemetry export, or logging sinks;
 * - runtime scheduling, service location, dependency injection, broker, queue,
 *   worker, thread, async, or event-loop behavior;
 * - bridge execution replacement;
 * - ownership over downstream lifecycle or endpoint resources.
 *
 * @section ascc_dependency_rule Dependency Rule
 * W13 may depend on W01-W12 public Communication Context surfaces.
 * It must remain future-facing and abstract. Concrete implementations belong
 * to later dedicated binding waves.
 */

namespace assembler::communication_context
{
    enum class TBoundaryHandoffStatus
    {
        unknown,
        accepted,
        rejected,
        deferred,
        completed,
        failed,
        unsupported
    };

    [[nodiscard]] constexpr bool is_terminal_boundary_handoff_status(
        TBoundaryHandoffStatus status) noexcept
    {
        return status == TBoundaryHandoffStatus::rejected
            || status == TBoundaryHandoffStatus::completed
            || status == TBoundaryHandoffStatus::failed
            || status == TBoundaryHandoffStatus::unsupported;
    }

    [[nodiscard]] constexpr bool is_failed_boundary_handoff_status(
        TBoundaryHandoffStatus status) noexcept
    {
        return status == TBoundaryHandoffStatus::rejected
            || status == TBoundaryHandoffStatus::failed
            || status == TBoundaryHandoffStatus::unsupported;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TBoundaryHandoffStatus status) noexcept
    {
        switch (status)
        {
            case TBoundaryHandoffStatus::unknown: return "unknown";
            case TBoundaryHandoffStatus::accepted: return "accepted";
            case TBoundaryHandoffStatus::rejected: return "rejected";
            case TBoundaryHandoffStatus::deferred: return "deferred";
            case TBoundaryHandoffStatus::completed: return "completed";
            case TBoundaryHandoffStatus::failed: return "failed";
            case TBoundaryHandoffStatus::unsupported: return "unsupported";
        }

        return "unknown";
    }
}
