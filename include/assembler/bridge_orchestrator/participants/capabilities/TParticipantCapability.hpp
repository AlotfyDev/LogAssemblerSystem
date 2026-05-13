#pragma once

#include <string_view>

#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityId.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"

/**
 * @file TParticipantCapability.hpp
 * @brief Non-carrier-specific participant capability declaration.
 */

namespace assembler::communication_context
{
    struct TParticipantCapability final
    {
        TParticipantCapabilityId capability_id{TParticipantCapabilityId::invalid()};
        TParticipantRole role{TParticipantRole::unknown};
        TParticipantCapabilityKind kind{TParticipantCapabilityKind::unknown};
        bool required{false};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return capability_id.is_valid()
                && role != TParticipantRole::unknown
                && kind != TParticipantCapabilityKind::unknown;
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] constexpr bool is_content_side() const noexcept
        {
            return is_content_side_capability(kind);
        }

        [[nodiscard]] constexpr bool is_receiver_side() const noexcept
        {
            return is_receiver_side_capability(kind);
        }

        [[nodiscard]] static constexpr TParticipantCapability make(
            TParticipantCapabilityId id,
            TParticipantRole participant_role,
            TParticipantCapabilityKind capability_kind,
            bool is_required_capability = false,
            std::string_view capability_note = {}) noexcept
        {
            return TParticipantCapability{
                id,
                participant_role,
                capability_kind,
                is_required_capability,
                capability_note
            };
        }
    };
}
