#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityMatchResult.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityView.hpp"

/**
 * @file TParticipantCapabilityReport.hpp
 * @brief Summary report for participant capability matching.
 */

namespace assembler::communication_context
{
    struct TParticipantCapabilityReport final
    {
        TParticipantCapabilityView view{};
        std::size_t matched_required_count{0u};
        std::size_t missing_required_count{0u};
        std::size_t optional_missing_count{0u};
        std::string_view report_name{"participant_capability_report"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return view.is_valid() && !report_name.empty();
        }

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return is_valid() && missing_required_count == 0u;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !passed();
        }

        constexpr void observe(TParticipantCapabilityMatchResult result) noexcept
        {
            if (!result.is_valid())
            {
                return;
            }

            if (result.matched())
            {
                ++matched_required_count;
                return;
            }

            if (result.status == TParticipantCapabilityMatchStatus::optional_missing)
            {
                ++optional_missing_count;
                return;
            }

            ++missing_required_count;
        }

        [[nodiscard]] static constexpr TParticipantCapabilityReport make(
            TParticipantCapabilityView capability_view,
            std::string_view name = "participant_capability_report") noexcept
        {
            return TParticipantCapabilityReport{
                capability_view,
                0u,
                0u,
                0u,
                name
            };
        }
    };
}
