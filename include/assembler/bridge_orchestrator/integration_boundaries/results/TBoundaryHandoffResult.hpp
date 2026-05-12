#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/integration_boundaries/carriers/TBoundaryHandoffHandle.hpp"
#include "assembler/communication_context/integration_boundaries/statuses/TBoundaryHandoffStatus.hpp"

/**
 * @file TBoundaryHandoffResult.hpp
 * @brief Result carrier for abstract boundary handoff attempts.
 *
 * @section ascc_final_intent Final Intended File Shape
 * This file is expected to remain part of the future-facing integration
 * boundary abstraction layer for the Communication Context. The final version
 * should preserve:
 *
 * - unified handoff result carrying status, optional handle, bridge result,
 *   and note;
 * - no downstream lifecycle guarantee;
 * - clear distinction between accepted handoff and completed handoff.
 *
 * @section ascc_current_wave Current W13 Implementation Scope
 * This W13 version intentionally implements lightweight, header-only,
 * endpoint-neutral abstract boundary values and CRTP surfaces over existing
 * W01-W12 public ASCC foundations.
 *
 * - result value type;
 * - success/failure helpers;
 * - static factories for accepted, completed, rejected, deferred, failed, and
 *   unsupported outcomes.
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
    struct TBoundaryHandoffResult final
    {
        TBoundaryHandoffStatus status{TBoundaryHandoffStatus::unknown};
        TBoundaryHandoffHandle handle{TBoundaryHandoffHandle::invalid()};
        TBridgeResult bridge_result{TBridgeResult::success()};
        std::string_view note{};

        [[nodiscard]] constexpr bool accepted() const noexcept
        {
            return status == TBoundaryHandoffStatus::accepted
                && handle.is_valid()
                && bridge_result.succeeded();
        }

        [[nodiscard]] constexpr bool completed() const noexcept
        {
            return status == TBoundaryHandoffStatus::completed
                && bridge_result.succeeded();
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return is_failed_boundary_handoff_status(status)
                || bridge_result.failed();
        }

        [[nodiscard]] constexpr bool deferred() const noexcept
        {
            return status == TBoundaryHandoffStatus::deferred
                || bridge_result.deferred();
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult accepted(
            TBoundaryHandoffHandle accepted_handle,
            std::string_view text = "boundary handoff accepted") noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::accepted,
                accepted_handle,
                TBridgeResult::success(accepted_handle.correlation),
                text
            };
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult completed(
            TBoundaryHandoffHandle completed_handle,
            std::string_view text = "boundary handoff completed") noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::completed,
                completed_handle,
                TBridgeResult::success(completed_handle.correlation),
                text
            };
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult rejected(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::rejected,
                TBoundaryHandoffHandle::invalid(),
                TBridgeResult::reject(reason, token),
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult deferred(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::deferred,
                TBoundaryHandoffHandle::invalid(),
                TBridgeResult::defer(reason, token),
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult failed(
            TBridgeError reason,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::failed,
                TBoundaryHandoffHandle::invalid(),
                TBridgeResult::fail(reason, token),
                reason.message
            };
        }

        [[nodiscard]] static constexpr TBoundaryHandoffResult unsupported(
            std::string_view text,
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TBoundaryHandoffResult{
                TBoundaryHandoffStatus::unsupported,
                TBoundaryHandoffHandle::invalid(),
                TBridgeResult::reject(
                    TBridgeError::make(TBridgeErrorCode::incompatible_carrier, text),
                    token),
                text
            };
        }
    };
}
