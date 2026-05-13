#pragma once

#include <cstddef>
#include <string_view>

/**
 * @file TProtocolRequirementMatchResult.hpp
 * @brief Match result for ASCC protocol requirements.
 */

namespace assembler::communication_context
{
    enum class TProtocolRequirementMatchStatus
    {
        unknown,
        matched,
        missing_participant_role,
        missing_carrier_capability,
        wrong_carrier_direction,
        binding_requirement_failed,
        optional_missing,
        protocol_mismatch
    };

    [[nodiscard]] constexpr bool is_successful_protocol_requirement_match(
        TProtocolRequirementMatchStatus status) noexcept
    {
        return status == TProtocolRequirementMatchStatus::matched
            || status == TProtocolRequirementMatchStatus::optional_missing;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TProtocolRequirementMatchStatus status) noexcept
    {
        switch (status)
        {
            case TProtocolRequirementMatchStatus::unknown: return "unknown";
            case TProtocolRequirementMatchStatus::matched: return "matched";
            case TProtocolRequirementMatchStatus::missing_participant_role: return "missing_participant_role";
            case TProtocolRequirementMatchStatus::missing_carrier_capability: return "missing_carrier_capability";
            case TProtocolRequirementMatchStatus::wrong_carrier_direction: return "wrong_carrier_direction";
            case TProtocolRequirementMatchStatus::binding_requirement_failed: return "binding_requirement_failed";
            case TProtocolRequirementMatchStatus::optional_missing: return "optional_missing";
            case TProtocolRequirementMatchStatus::protocol_mismatch: return "protocol_mismatch";
        }

        return "unknown";
    }

    struct TProtocolRequirementMatchResult final
    {
        TProtocolRequirementMatchStatus status{TProtocolRequirementMatchStatus::unknown};
        std::size_t matched_required_count{0u};
        std::size_t missing_required_count{0u};
        std::size_t optional_missing_count{0u};
        std::size_t binding_failure_count{0u};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TProtocolRequirementMatchStatus::unknown;
        }

        [[nodiscard]] constexpr bool passed() const noexcept
        {
            return is_valid()
                && missing_required_count == 0u
                && binding_failure_count == 0u
                && is_successful_protocol_requirement_match(status);
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !passed();
        }

        [[nodiscard]] static constexpr TProtocolRequirementMatchResult matched(
            std::size_t required_count,
            std::string_view result_note = "protocol requirements matched") noexcept
        {
            return TProtocolRequirementMatchResult{
                TProtocolRequirementMatchStatus::matched,
                required_count,
                0u,
                0u,
                0u,
                result_note
            };
        }

        [[nodiscard]] static constexpr TProtocolRequirementMatchResult missing_carrier(
            std::size_t missing_count,
            std::string_view result_note = "required carrier capability missing") noexcept
        {
            return TProtocolRequirementMatchResult{
                TProtocolRequirementMatchStatus::missing_carrier_capability,
                0u,
                missing_count,
                0u,
                0u,
                result_note
            };
        }

        [[nodiscard]] static constexpr TProtocolRequirementMatchResult binding_failed(
            std::string_view result_note = "binding requirement failed") noexcept
        {
            return TProtocolRequirementMatchResult{
                TProtocolRequirementMatchStatus::binding_requirement_failed,
                0u,
                0u,
                0u,
                1u,
                result_note
            };
        }
    };
}
