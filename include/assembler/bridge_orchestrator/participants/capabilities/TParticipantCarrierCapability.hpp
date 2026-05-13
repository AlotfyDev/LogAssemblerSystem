#pragma once

#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityDirection.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityId.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"

/**
 * @file TParticipantCarrierCapability.hpp
 * @brief Carrier-aware capability declaration for a bridge-visible participant.
 *
 * @section ascc_comp_w03 Purpose
 * This type binds participant role, participant capability, carrier kind,
 * carrier direction, and protocol family into one explicit communication
 * contract record.
 */

namespace assembler::communication_context
{
    struct TParticipantCarrierCapability final
    {
        TParticipantCapabilityId capability_id{TParticipantCapabilityId::invalid()};
        TParticipantRole role{TParticipantRole::unknown};
        TParticipantCapabilityKind capability{TParticipantCapabilityKind::unknown};
        TAsccCarrierKind carrier{TAsccCarrierKind::unknown};
        TParticipantCapabilityDirection direction{TParticipantCapabilityDirection::unknown};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        bool required{false};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return capability_id.is_valid()
                && role != TParticipantRole::unknown
                && capability != TParticipantCapabilityKind::unknown
                && carrier != TAsccCarrierKind::unknown
                && direction != TParticipantCapabilityDirection::unknown;
        }

        [[nodiscard]] constexpr bool produces() const noexcept
        {
            return can_produce(direction);
        }

        [[nodiscard]] constexpr bool consumes() const noexcept
        {
            return can_consume(direction);
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] static constexpr TParticipantCarrierCapability make(
            TParticipantCapabilityId id,
            TParticipantRole participant_role,
            TParticipantCapabilityKind capability_kind,
            TAsccCarrierKind carrier_kind,
            TParticipantCapabilityDirection capability_direction,
            TBridgeProtocolKind protocol_kind = TBridgeProtocolKind::unknown,
            bool is_required_capability = false,
            std::string_view capability_note = {}) noexcept
        {
            return TParticipantCarrierCapability{
                id,
                participant_role,
                capability_kind,
                carrier_kind,
                capability_direction,
                protocol_kind,
                is_required_capability,
                capability_note
            };
        }
    };
}
