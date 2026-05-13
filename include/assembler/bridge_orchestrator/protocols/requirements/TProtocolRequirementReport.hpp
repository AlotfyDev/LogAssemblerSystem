#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/protocols/requirements/TProtocolRequirementMatchResult.hpp"

/**
 * @file TProtocolRequirementReport.hpp
 * @brief Summary report for ASCC protocol requirement matching.
 */

namespace assembler::communication_context
{
    struct TProtocolRequirementReport final
    {
        std::string_view report_name{};
        std::size_t participant_requirements{0u};
        std::size_t carrier_requirements{0u};
        std::size_t binding_requirements{0u};
        std::size_t matched_required_count{0u};
        std::size_t missing_required_count{0u};
        std::size_t optional_missing_count{0u};
        std::size_t binding_failure_count{0u};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !report_name.empty()
                && (participant_requirements + carrier_requirements + binding_requirements) > 0u;
        }

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return is_valid()
                && missing_required_count == 0u
                && binding_failure_count == 0u;
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !passed();
        }

        template <typename RequirementSet>
        [[nodiscard]] static constexpr TProtocolRequirementReport from_set_and_match(
            RequirementSet const& set,
            TProtocolRequirementMatchResult const& match,
            std::string_view name = "protocol_requirement_report",
            std::string_view report_note = {}) noexcept
        {
            return TProtocolRequirementReport{
                name,
                set.participant_count,
                set.carrier_count,
                set.binding_count,
                match.matched_required_count,
                match.missing_required_count,
                match.optional_missing_count,
                match.binding_failure_count,
                report_note
            };
        }
    };
}
