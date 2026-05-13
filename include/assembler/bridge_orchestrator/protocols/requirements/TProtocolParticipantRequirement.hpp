#pragma once

#include <string_view>

#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementKind.hpp"

/**
 * @file TProtocolParticipantRequirement.hpp
 * @brief Participant-role requirement declared by an ASCC protocol.
 *
 * @section ascc_comp_w05 Purpose
 * This type declares which participant role a protocol requires. It does not
 * bind concrete participants, materialize sessions, or invoke endpoints.
 */

namespace assembler::communication_context
{
    struct TProtocolParticipantRequirement final
    {
        std::uint64_t requirement_id{0u};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TParticipantRole required_role{TParticipantRole::unknown};
        bool required{true};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return requirement_id != 0u
                && protocol != TBridgeProtocolKind::unknown
                && required_role != TParticipantRole::unknown;
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] constexpr TProtocolRequirementKind requirement_kind() const noexcept
        {
            return TProtocolRequirementKind::participant_role_requirement;
        }

        [[nodiscard]] static constexpr TProtocolParticipantRequirement make(
            std::uint64_t id,
            TBridgeProtocolKind protocol_kind,
            TParticipantRole role,
            bool is_required_role = true,
            std::string_view requirement_note = {}) noexcept
        {
            return TProtocolParticipantRequirement{
                id,
                protocol_kind,
                role,
                is_required_role,
                requirement_note
            };
        }
    };
}
