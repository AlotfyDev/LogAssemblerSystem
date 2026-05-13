#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccProtocolReadinessView.hpp
 * @brief Read-only readiness projection for ASCC protocol requirements.
 *
 * @section ascc_comp_w06 Purpose
 * This view summarizes W05 protocol requirement readiness. It does not execute
 * protocol steps, move carriers, open sessions, or invoke bridge runtime.
 */

namespace assembler::communication_context
{
    struct TAsccProtocolReadinessView final
    {
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool protocol_kind_valid{false};
        bool participant_requirements_satisfied{false};
        bool carrier_requirements_satisfied{false};
        bool binding_requirements_satisfied{false};
        std::size_t missing_required_items{0u};
        std::string_view protocol_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && !protocol_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && is_ready(status)
                && protocol_kind_valid
                && participant_requirements_satisfied
                && carrier_requirements_satisfied
                && binding_requirements_satisfied
                && missing_required_items == 0u;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || !protocol_kind_valid
                || !participant_requirements_satisfied
                || !carrier_requirements_satisfied
                || !binding_requirements_satisfied
                || missing_required_items > 0u;
        }

        [[nodiscard]] static constexpr TAsccProtocolReadinessView make(
            TAsccReadinessStatus readiness_status,
            bool has_valid_protocol_kind,
            bool has_participant_requirements,
            bool has_carrier_requirements,
            bool has_binding_requirements,
            std::size_t missing_items,
            std::string_view name = "protocol_readiness") noexcept
        {
            return TAsccProtocolReadinessView{
                readiness_status,
                has_valid_protocol_kind,
                has_participant_requirements,
                has_carrier_requirements,
                has_binding_requirements,
                missing_items,
                name
            };
        }
    };
}
