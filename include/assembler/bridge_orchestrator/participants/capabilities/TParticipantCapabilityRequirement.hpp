#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityDirection.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TParticipantCapabilityRequirement.hpp
 * @brief Required participant capability/carrier relation for a protocol side.
 */

namespace assembler::communication_context
{
    struct TParticipantCapabilityRequirement final
    {
        std::uint64_t requirement_id{0u};
        TParticipantRole role{TParticipantRole::unknown};
        TParticipantCapabilityKind capability{TParticipantCapabilityKind::unknown};
        TAsccCarrierKind carrier{TAsccCarrierKind::unknown};
        TParticipantCapabilityDirection direction{TParticipantCapabilityDirection::unknown};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        bool required{true};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return requirement_id != 0u
                && role != TParticipantRole::unknown
                && capability != TParticipantCapabilityKind::unknown
                && carrier != TAsccCarrierKind::unknown
                && direction != TParticipantCapabilityDirection::unknown;
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] static constexpr TParticipantCapabilityRequirement make(
            std::uint64_t id,
            TParticipantRole participant_role,
            TParticipantCapabilityKind capability_kind,
            TAsccCarrierKind carrier_kind,
            TParticipantCapabilityDirection capability_direction,
            TBridgeProtocolKind protocol_kind = TBridgeProtocolKind::unknown,
            bool is_required_capability = true,
            std::string_view requirement_note = {}) noexcept
        {
            return TParticipantCapabilityRequirement{
                id,
                participant_role,
                capability_kind,
                carrier_kind,
                capability_direction,
                protocol_kind,
                is_required_capability,
                requirement_note
            };
        }
    };
}
