#pragma once

#include <array>
#include <cstddef>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TAsccComponentCapabilityCatalog final
    {
        std::array<TParticipantCapabilityKind, Capacity> capabilities{};
        std::size_t count{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return count <= Capacity;
        }

        constexpr bool add(TParticipantCapabilityKind capability) noexcept
        {
            if (count >= Capacity || capability == TParticipantCapabilityKind::unknown)
            {
                return false;
            }

            capabilities[count++] = capability;
            return true;
        }

        [[nodiscard]] constexpr bool contains(TParticipantCapabilityKind capability) const noexcept
        {
            for (std::size_t i = 0u; i < count; ++i)
            {
                if (capabilities[i] == capability)
                {
                    return true;
                }
            }

            return false;
        }
    };
}
