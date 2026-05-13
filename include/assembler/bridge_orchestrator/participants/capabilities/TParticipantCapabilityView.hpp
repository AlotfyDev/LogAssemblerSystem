#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"

/**
 * @file TParticipantCapabilityView.hpp
 * @brief Read-only projection of participant capability-set state.
 */

namespace assembler::communication_context
{
    struct TParticipantCapabilityView final
    {
        TParticipantRole role{TParticipantRole::unknown};
        std::size_t declared_capability_count{0u};
        std::size_t carrier_capability_count{0u};
        bool supports_required_primary_exchange{false};
        std::string_view view_name{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return role != TParticipantRole::unknown
                && !view_name.empty();
        }

        [[nodiscard]] constexpr bool ready_for_primary_exchange() const noexcept
        {
            return is_valid() && supports_required_primary_exchange;
        }

        [[nodiscard]] static constexpr TParticipantCapabilityView make(
            TParticipantRole participant_role,
            std::size_t declared_count,
            std::size_t carrier_count,
            bool primary_exchange_ready,
            std::string_view name = "participant_capability_view") noexcept
        {
            return TParticipantCapabilityView{
                participant_role,
                declared_count,
                carrier_count,
                primary_exchange_ready,
                name
            };
        }

        [[nodiscard]] static constexpr TParticipantCapabilityView invalid() noexcept
        {
            return TParticipantCapabilityView{};
        }
    };
}
