#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityMatchResult.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapability.hpp"

/**
 * @file TParticipantCarrierCapabilitySet.hpp
 * @brief Fixed-capacity set of carrier-aware participant capabilities.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TParticipantCarrierCapabilitySet final
    {
        std::array<TParticipantCarrierCapability, Capacity> capabilities{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view set_name{"participant_carrier_capability_set"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !set_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        constexpr bool add(TParticipantCarrierCapability capability) noexcept
        {
            if (!is_valid() || full() || !capability.is_valid())
            {
                ++rejected_insertions;
                return false;
            }

            capabilities[count] = capability;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr const TParticipantCarrierCapability* find(
            TParticipantCapabilityRequirement requirement) const noexcept
        {
            if (!requirement.is_valid())
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                const auto& candidate = capabilities[index];

                if (candidate.role == requirement.role
                    && candidate.capability == requirement.capability
                    && candidate.carrier == requirement.carrier
                    && candidate.protocol == requirement.protocol
                    && can_produce(candidate.direction) == can_produce(requirement.direction)
                    && can_consume(candidate.direction) == can_consume(requirement.direction))
                {
                    return &candidate;
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr TParticipantCapabilityMatchResult match(
            TParticipantCapabilityRequirement requirement) const noexcept
        {
            if (!requirement.is_valid())
            {
                return TParticipantCapabilityMatchResult::make(
                    TParticipantCapabilityMatchStatus::missing_required_capability,
                    requirement,
                    {},
                    "requirement is invalid");
            }

            const auto* exact = find(requirement);
            if (exact != nullptr)
            {
                return TParticipantCapabilityMatchResult::make(
                    TParticipantCapabilityMatchStatus::matched,
                    requirement,
                    *exact,
                    "participant carrier capability matched");
            }

            if (!requirement.is_required())
            {
                return TParticipantCapabilityMatchResult::make(
                    TParticipantCapabilityMatchStatus::optional_missing,
                    requirement,
                    {},
                    "optional participant carrier capability missing");
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                const auto& candidate = capabilities[index];

                if (candidate.role != requirement.role)
                {
                    continue;
                }

                if (candidate.carrier == requirement.carrier
                    && candidate.capability == requirement.capability
                    && candidate.protocol == requirement.protocol)
                {
                    return TParticipantCapabilityMatchResult::make(
                        TParticipantCapabilityMatchStatus::wrong_direction,
                        requirement,
                        candidate,
                        "carrier and capability matched but direction did not");
                }

                if (candidate.capability == requirement.capability
                    && candidate.protocol == requirement.protocol)
                {
                    return TParticipantCapabilityMatchResult::make(
                        TParticipantCapabilityMatchStatus::wrong_carrier,
                        requirement,
                        candidate,
                        "capability matched but carrier did not");
                }

                if (candidate.carrier == requirement.carrier
                    && candidate.protocol == requirement.protocol)
                {
                    return TParticipantCapabilityMatchResult::make(
                        TParticipantCapabilityMatchStatus::wrong_capability,
                        requirement,
                        candidate,
                        "carrier matched but capability did not");
                }
            }

            return TParticipantCapabilityMatchResult::make(
                TParticipantCapabilityMatchStatus::missing_required_capability,
                requirement,
                {},
                "required participant carrier capability missing");
        }

        [[nodiscard]] static constexpr TParticipantCarrierCapabilitySet make(
            std::string_view name = "participant_carrier_capability_set") noexcept
        {
            return TParticipantCarrierCapabilitySet{
                {},
                0u,
                0u,
                name
            };
        }
    };
}
