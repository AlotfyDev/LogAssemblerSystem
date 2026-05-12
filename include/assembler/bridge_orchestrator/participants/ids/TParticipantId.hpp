#pragma once

#include <cstdint>

/**
 * @file TParticipantId.hpp
 * @brief Opaque bridge-visible participant identity.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * `TParticipantId` gives ASCC registries a first-class ID type compatible with
 * `TBoundedRegistry`.  It does not replace `TParticipant` or `TParticipantView`;
 * it is the stable identity used to catalog bridge-visible participant
 * descriptors.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This ID does not own endpoint state, endpoint lifecycle, pipeline
 * composition, or policy execution.
 */

namespace assembler::communication_context
{
    struct TParticipantId final
    {
        std::uint64_t value{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return value != 0u;
        }

        [[nodiscard]] static constexpr TParticipantId invalid() noexcept
        {
            return TParticipantId{};
        }

        [[nodiscard]] static constexpr TParticipantId from_value(
            std::uint64_t id) noexcept
        {
            return TParticipantId{id};
        }

        friend constexpr bool operator==(
            TParticipantId lhs,
            TParticipantId rhs) noexcept
        {
            return lhs.value == rhs.value;
        }

        friend constexpr bool operator!=(
            TParticipantId lhs,
            TParticipantId rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
