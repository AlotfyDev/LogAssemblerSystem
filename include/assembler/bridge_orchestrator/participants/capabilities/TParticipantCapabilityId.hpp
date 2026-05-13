#pragma once

#include <cstdint>

/**
 * @file TParticipantCapabilityId.hpp
 * @brief Opaque identity for a participant capability declaration.
 *
 * @section ascc_comp_w03 Purpose
 * Participant capabilities describe what a bridge-visible participant can do
 * inside carrier-based communication.  This ID identifies one capability
 * declaration without owning endpoint internals or concrete actor lifecycle.
 */

namespace assembler::communication_context
{
    struct TParticipantCapabilityId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TParticipantCapabilityId invalid() noexcept
        {
            return TParticipantCapabilityId{};
        }

        [[nodiscard]] static constexpr TParticipantCapabilityId from_value(
            std::uint64_t id) noexcept
        {
            return TParticipantCapabilityId{id};
        }

        friend constexpr bool operator==(
            TParticipantCapabilityId lhs,
            TParticipantCapabilityId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(
            TParticipantCapabilityId lhs,
            TParticipantCapabilityId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
