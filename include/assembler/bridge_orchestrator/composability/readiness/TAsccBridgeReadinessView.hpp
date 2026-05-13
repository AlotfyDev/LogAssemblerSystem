#pragma once

#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccBridgeReadinessView.hpp
 * @brief Read-only readiness projection for ASCC bridge model availability.
 *
 * @section ascc_comp_w06 Purpose
 * This view describes whether bridge participation is required and whether the
 * bridge model/evidence is available. It does not step bridge core, run bridge
 * protocol, invoke endpoints, or own delivery.
 */

namespace assembler::communication_context
{
    struct TAsccBridgeReadinessView final
    {
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool bridge_required{false};
        bool bridge_model_available{false};
        bool bridge_budget_valid{false};
        bool bridge_diagnostics_available{false};
        std::string_view bridge_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && !bridge_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            if (!is_valid())
            {
                return false;
            }

            if (!bridge_required)
            {
                return status == TAsccReadinessStatus::ready
                    || status == TAsccReadinessStatus::out_of_scope;
            }

            return is_ready(status)
                && bridge_model_available
                && bridge_budget_valid
                && bridge_diagnostics_available;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || (bridge_required
                    && (!bridge_model_available
                        || !bridge_budget_valid
                        || !bridge_diagnostics_available));
        }

        [[nodiscard]] static constexpr TAsccBridgeReadinessView make(
            TAsccReadinessStatus readiness_status,
            bool is_bridge_required,
            bool has_bridge_model,
            bool has_valid_bridge_budget,
            bool has_bridge_diagnostics,
            std::string_view name = "bridge_readiness") noexcept
        {
            return TAsccBridgeReadinessView{
                readiness_status,
                is_bridge_required,
                has_bridge_model,
                has_valid_bridge_budget,
                has_bridge_diagnostics,
                name
            };
        }
    };
}
