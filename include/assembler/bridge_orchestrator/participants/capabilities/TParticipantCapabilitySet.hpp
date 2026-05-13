#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapability.hpp"

/**
 * @file TParticipantCapabilitySet.hpp
 * @brief Fixed-capacity set of participant capability declarations.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TParticipantCapabilitySet final
    {
        std::array<TParticipantCapability, Capacity> capabilities{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view set_name{"participant_capability_set"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !set_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr bool contains(
            TParticipantRole role,
            TParticipantCapabilityKind kind) const noexcept
        {
            if (role == TParticipantRole::unknown
                || kind == TParticipantCapabilityKind::unknown)
            {
                return false;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (capabilities[index].role == role
                    && capabilities[index].kind == kind)
                {
                    return true;
                }
            }

            return false;
        }

        constexpr bool add(TParticipantCapability capability) noexcept
        {
            if (!is_valid()
                || full()
                || !capability.is_valid()
                || contains(capability.role, capability.kind))
            {
                ++rejected_insertions;
                return false;
            }

            capabilities[count] = capability;
            ++count;
            return true;
        }

        [[nodiscard]] static constexpr TParticipantCapabilitySet make(
            std::string_view name = "participant_capability_set") noexcept
        {
            return TParticipantCapabilitySet{
                {},
                0u,
                0u,
                name
            };
        }
    };
}
