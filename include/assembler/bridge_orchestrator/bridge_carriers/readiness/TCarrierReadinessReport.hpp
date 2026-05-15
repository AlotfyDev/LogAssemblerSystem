#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowReport.hpp"
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"
#include "assembler/communication_context/bridge_core/errors/TBridgeError.hpp"

/**
 * @file TCarrierReadinessReport.hpp
 * @brief Aggregate readiness evidence for the ASCC bridge carrier runtime.
 *
 * This report aggregates carrier-runtime evidence into one canonical readiness
 * projection consumable by:
 *
 * - facade layer readiness views
 * - protocol readiness gates
 * - session admission/runtime checks
 * - participant operational readiness
 * - diagnostics/reporting systems
 * - higher pipeline composition layers
 *
 * The report intentionally does NOT expose transport/runtime internals.
 * Instead, it exposes bounded semantic evidence describing whether the
 * carrier runtime is operationally ready.
 *
 * Readiness here means:
 * - validation semantics passed
 * - requirement satisfaction succeeded
 * - runtime flow evidence remained healthy
 * - no blocking rejection state exists
 */

namespace assembler::communication_context
{
    enum class TCarrierReadinessStatus
    {
        unknown,
        ready,
        degraded,
        blocked,
        failed
    };

    [[nodiscard]] constexpr std::string_view to_string(
        TCarrierReadinessStatus status) noexcept
    {
        switch (status)
        {
            case TCarrierReadinessStatus::unknown:
                return "unknown";

            case TCarrierReadinessStatus::ready:
                return "ready";

            case TCarrierReadinessStatus::degraded:
                return "degraded";

            case TCarrierReadinessStatus::blocked:
                return "blocked";

            case TCarrierReadinessStatus::failed:
                return "failed";
        }

        return "unknown";
    }

    struct TCarrierReadinessReport final
    {
        TCarrierValidationReport validation{};
        TCarrierRequirementSatisfactionReport requirement{};
        TCarrierFlowReport flow{};

        TCarrierReadinessStatus status{
            TCarrierReadinessStatus::unknown};

        bool validation_ready{false};
        bool requirement_ready{false};
        bool flow_ready{false};
        bool blocked{false};

        TBridgeError error{};

        std::string_view note{};

        [[nodiscard]] constexpr bool is_ready() const noexcept
        {
            return status == TCarrierReadinessStatus::ready
                && validation_ready
                && requirement_ready
                && flow_ready
                && !blocked;
        }

        [[nodiscard]] static constexpr TCarrierReadinessReport ready_report(
            TCarrierValidationReport validation_report,
            TCarrierRequirementSatisfactionReport requirement_report,
            TCarrierFlowReport flow_report,
            std::string_view note = "carrier runtime ready") noexcept
        {
            return {
                validation_report,
                requirement_report,
                flow_report,
                TCarrierReadinessStatus::ready,
                true,
                true,
                true,
                false,
                {},
                note
            };
        }

        [[nodiscard]] static constexpr TCarrierReadinessReport degraded_report(
            TCarrierValidationReport validation_report,
            TCarrierRequirementSatisfactionReport requirement_report,
            TCarrierFlowReport flow_report,
            std::string_view note = "carrier runtime degraded") noexcept
        {
            return {
                validation_report,
                requirement_report,
                flow_report,
                TCarrierReadinessStatus::degraded,
                validation_report.result.passed(),
                requirement_report.satisfied(),
                !flow_report.blocked(),
                flow_report.blocked(),
                {},
                note
            };
        }

        [[nodiscard]] static constexpr TCarrierReadinessReport blocked_report(
            TCarrierValidationReport validation_report,
            TCarrierRequirementSatisfactionReport requirement_report,
            TCarrierFlowReport flow_report,
            TBridgeError runtime_error,
            std::string_view note = "carrier runtime blocked") noexcept
        {
            return {
                validation_report,
                requirement_report,
                flow_report,
                TCarrierReadinessStatus::blocked,
                validation_report.result.passed(),
                requirement_report.satisfied(),
                false,
                true,
                runtime_error,
                note
            };
        }

        [[nodiscard]] static constexpr TCarrierReadinessReport failed_report(
            TCarrierValidationReport validation_report,
            TCarrierRequirementSatisfactionReport requirement_report,
            TCarrierFlowReport flow_report,
            TBridgeError runtime_error,
            std::string_view note = "carrier runtime failed") noexcept
        {
            return {
                validation_report,
                requirement_report,
                flow_report,
                TCarrierReadinessStatus::failed,
                false,
                false,
                false,
                true,
                runtime_error,
                note
            };
        }
    };
}
