#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"

/**
 * @file TAsccParticipantReadinessView.hpp
 * @brief Read-only readiness projection for ASCC participants.
 *
 * @section ascc_comp_w06 Purpose
 * This view summarizes participant identity, role, and capability readiness
 * evidence produced by W03 without owning participant registries, endpoint
 * instances, adapters, ports, or carrier movement.
 */

namespace assembler::communication_context
{
    struct TAsccParticipantReadinessView final
    {
        TAsccReadinessStatus status{TAsccReadinessStatus::unknown};
        bool identity_valid{false};
        bool role_valid{false};
        bool required_capabilities_satisfied{false};
        bool carrier_capabilities_satisfied{false};
        std::size_t missing_required_capabilities{0u};
        std::string_view participant_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TAsccReadinessStatus::unknown
                && !participant_name.empty();
        }

        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid()
                && is_ready(status)
                && identity_valid
                && role_valid
                && required_capabilities_satisfied
                && carrier_capabilities_satisfied
                && missing_required_capabilities == 0u;
        }

        [[nodiscard]] constexpr bool blocked() const noexcept
        {
            return is_blocking_readiness_status(status)
                || !identity_valid
                || !role_valid
                || !required_capabilities_satisfied
                || !carrier_capabilities_satisfied
                || missing_required_capabilities > 0u;
        }

        [[nodiscard]] static constexpr TAsccParticipantReadinessView make(
            TAsccReadinessStatus readiness_status,
            bool has_valid_identity,
            bool has_valid_role,
            bool has_required_capabilities,
            bool has_carrier_capabilities,
            std::size_t missing_capabilities,
            std::string_view name = "participant_readiness") noexcept
        {
            return TAsccParticipantReadinessView{
                readiness_status,
                has_valid_identity,
                has_valid_role,
                has_required_capabilities,
                has_carrier_capabilities,
                missing_capabilities,
                name
            };
        }
    };
}
