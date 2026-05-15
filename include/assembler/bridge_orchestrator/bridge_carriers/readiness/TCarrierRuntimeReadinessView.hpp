#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/readiness/TCarrierReadinessReport.hpp"

/**
 * @file TCarrierRuntimeReadinessView.hpp
 * @brief Facade-safe readiness projection for the ASCC carrier runtime.
 *
 * This view projects bounded carrier-runtime readiness evidence into a
 * consumer-facing operational surface.
 *
 * The projection intentionally hides low-level runtime internals while still
 * exposing enough operational evidence for:
 *
 * - managerial facade readiness views
 * - protocol/session admission checks
 * - participant readiness projections
 * - diagnostics dashboards
 * - pipeline composition orchestration
 *
 * This component exists specifically to prevent direct leakage of internal
 * runtime evidence structures into facade and composition layers.
 *
 * Relationship to other components:
 *
 * - TCarrierReadinessReport:
 *      internal aggregate readiness evidence.
 *
 * - TCarrierFlowRuntime:
 *      runtime evidence producer.
 *
 * - facade_layer/managerial/TAsccCarrierReadinessView:
 *      higher managerial projection surface.
 *
 * - protocol/session readiness:
 *      aggregate operational admission consumers.
 */

namespace assembler::communication_context
{
    struct TCarrierRuntimeReadinessView final
    {
        TCarrierReadinessStatus status{
            TCarrierReadinessStatus::unknown};

        bool ready{false};
        bool degraded{false};
        bool blocked{false};
        bool failed{false};

        bool validation_ready{false};
        bool requirement_ready{false};
        bool flow_ready{false};

        std::size_t total_records{0};
        std::size_t rejected_records{0};

        std::string_view correlation{};
        std::string_view report_name{};
        std::string_view note{};

        [[nodiscard]] constexpr bool operational() const noexcept
        {
            return ready && !blocked && !failed;
        }

        [[nodiscard]] static constexpr TCarrierRuntimeReadinessView project(
            const TCarrierReadinessReport& report) noexcept
        {
            return {
                report.status,
                report.status == TCarrierReadinessStatus::ready,
                report.status == TCarrierReadinessStatus::degraded,
                report.status == TCarrierReadinessStatus::blocked,
                report.status == TCarrierReadinessStatus::failed,
                report.validation_ready,
                report.requirement_ready,
                report.flow_ready,
                report.flow.total_records,
                report.flow.rejected_records,
                report.flow.correlation.value,
                report.flow.report_name,
                report.note
            };
        }
    };
}
