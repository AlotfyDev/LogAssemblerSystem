#pragma once

#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityRequirement.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapability.hpp"

/**
 * @file TParticipantCapabilityMatchResult.hpp
 * @brief Match result between a required participant carrier capability and an available one.
 */

namespace assembler::communication_context
{
    enum class TParticipantCapabilityMatchStatus
    {
        unknown,
        matched,
        missing_required_capability,
        wrong_role,
        wrong_capability,
        wrong_carrier,
        wrong_direction,
        protocol_mismatch,
        optional_missing
    };

    [[nodiscard]] constexpr bool is_successful_participant_capability_match(
        TParticipantCapabilityMatchStatus status) noexcept
    {
        return status == TParticipantCapabilityMatchStatus::matched
            || status == TParticipantCapabilityMatchStatus::optional_missing;
    }

    [[nodiscard]] constexpr std::string_view to_string(
        TParticipantCapabilityMatchStatus status) noexcept
    {
        switch (status)
        {
            case TParticipantCapabilityMatchStatus::unknown: return "unknown";
            case TParticipantCapabilityMatchStatus::matched: return "matched";
            case TParticipantCapabilityMatchStatus::missing_required_capability: return "missing_required_capability";
            case TParticipantCapabilityMatchStatus::wrong_role: return "wrong_role";
            case TParticipantCapabilityMatchStatus::wrong_capability: return "wrong_capability";
            case TParticipantCapabilityMatchStatus::wrong_carrier: return "wrong_carrier";
            case TParticipantCapabilityMatchStatus::wrong_direction: return "wrong_direction";
            case TParticipantCapabilityMatchStatus::protocol_mismatch: return "protocol_mismatch";
            case TParticipantCapabilityMatchStatus::optional_missing: return "optional_missing";
        }

        return "unknown";
    }

    struct TParticipantCapabilityMatchResult final
    {
        TParticipantCapabilityMatchStatus status{TParticipantCapabilityMatchStatus::unknown};
        TParticipantCapabilityRequirement requirement{};
        TParticipantCarrierCapability provided{};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return status != TParticipantCapabilityMatchStatus::unknown
                && requirement.is_valid();
        }

        [[nodiscard]] constexpr bool matched() const noexcept
        {
            return status == TParticipantCapabilityMatchStatus::matched;
        }

        [[nodiscard]] constexpr bool succeeded() const noexcept
        {
            return is_successful_participant_capability_match(status);
        }

        [[nodiscard]] constexpr bool failed() const noexcept
        {
            return !succeeded();
        }

        [[nodiscard]] static constexpr TParticipantCapabilityMatchResult make(
            TParticipantCapabilityMatchStatus match_status,
            TParticipantCapabilityRequirement required,
            TParticipantCarrierCapability available = {},
            std::string_view match_note = {}) noexcept
        {
            return TParticipantCapabilityMatchResult{
                match_status,
                required,
                available,
                match_note
            };
        }
    };
}
