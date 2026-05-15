#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/readiness/TCarrierRuntimeReadinessView.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"

/**
 * @file TAsccCarrierReadinessView.hpp
 * @brief Managerial facade projection for carrier runtime readiness.
 *
 * This facade component exposes a managerial-safe readiness surface for the
 * bridge_carriers operational subsystem.
 *
 * The component intentionally consumes:
 *
 * - TCarrierRuntimeReadinessView
 *
 * instead of consuming low-level runtime evidence directly.
 *
 * This prevents facade-layer leakage of:
 *
 * - validation internals
 * - requirement runtime structures
 * - flow runtime evidence
 * - low-level readiness aggregation details
 *
 * Architectural role:
 *
 * bridge_carriers/ produces bounded runtime readiness evidence.
 * facade_layer/ projects managerial-safe operational readiness views.
 *
 * This separation is critical because facade consumers should operate against
 * stable readiness projections rather than internal runtime topology.
 *
 * Consumed by:
 *
 * - managerial dashboards
 * - administrative readiness views
 * - participant orchestration surfaces
 * - protocol/session admission layers
 * - pipeline composition governance
 */

namespace assembler::communication_context
{
    struct TAsccCarrierReadinessView final
    {
        TAsccComponentReadinessStatus status{
            TAsccComponentReadinessStatus::unknown};

        TCarrierRuntimeReadinessView runtime_view{};

        std::string_view readiness_note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status
                != TAsccComponentReadinessStatus::unknown;
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && status
                    == TAsccComponentReadinessStatus::ready
                && runtime_view.operational();
        }

        [[nodiscard]] static constexpr TAsccCarrierReadinessView
        from_runtime_view(
            TCarrierRuntimeReadinessView runtime,
            std::string_view note = {}) noexcept
        {
            TAsccComponentReadinessStatus projected_status =
                TAsccComponentReadinessStatus::unknown;

            if (runtime.failed || runtime.blocked)
            {
                projected_status =
                    TAsccComponentReadinessStatus::blocked;
            }
            else if (runtime.ready)
            {
                projected_status =
                    TAsccComponentReadinessStatus::ready;
            }
            else if (runtime.degraded)
            {
                projected_status =
                    TAsccComponentReadinessStatus::degraded;
            }

            return {
                projected_status,
                runtime,
                note
            };
        }
    };
}
