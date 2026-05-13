#pragma once

#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityDirection.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/roles/TParticipantRole.hpp"
#include "assembler/communication_context/protocols/kinds/TBridgeProtocolKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementKind.hpp"

/**
 * @file TProtocolCarrierRequirement.hpp
 * @brief Carrier requirement declared by an ASCC protocol.
 *
 * @section ascc_comp_w05 Purpose
 * This type connects protocol requirements to W03 participant carrier
 * capabilities. It declares which participant role must produce, consume, or
 * observe a carrier under a protocol family.
 *
 * @section ascc_boundary_rule Boundary Rule
 * This file must not execute protocol steps, move carriers, invoke endpoints,
 * materialize sessions, or inspect endpoint payload internals. It is a
 * requirement declaration only.
 */

namespace assembler::communication_context
{
    struct TProtocolCarrierRequirement final
    {
        std::uint64_t requirement_id{0u};
        TBridgeProtocolKind protocol{TBridgeProtocolKind::unknown};
        TParticipantRole role{TParticipantRole::unknown};
        TParticipantCapabilityKind participant_capability{TParticipantCapabilityKind::unknown};
        TAsccCarrierKind carrier{TAsccCarrierKind::unknown};
        TParticipantCapabilityDirection direction{TParticipantCapabilityDirection::unknown};
        bool required{true};
        std::string_view note{};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return requirement_id != 0u
                && protocol != TBridgeProtocolKind::unknown
                && role != TParticipantRole::unknown
                && participant_capability != TParticipantCapabilityKind::unknown
                && carrier != TAsccCarrierKind::unknown
                && direction != TParticipantCapabilityDirection::unknown;
        }

        [[nodiscard]] constexpr bool is_required() const noexcept
        {
            return required;
        }

        [[nodiscard]] constexpr bool requires_producer() const noexcept
        {
            return can_produce(direction);
        }

        [[nodiscard]] constexpr bool requires_consumer() const noexcept
        {
            return can_consume(direction);
        }

        [[nodiscard]] constexpr TProtocolRequirementKind requirement_kind() const noexcept
        {
            return TProtocolRequirementKind::carrier_requirement;
        }

        [[nodiscard]] static constexpr TProtocolCarrierRequirement make(
            std::uint64_t id,
            TBridgeProtocolKind protocol_kind,
            TParticipantRole participant_role,
            TParticipantCapabilityKind capability_kind,
            TAsccCarrierKind carrier_kind,
            TParticipantCapabilityDirection carrier_direction,
            bool is_required_carrier = true,
            std::string_view requirement_note = {}) noexcept
        {
            return TProtocolCarrierRequirement{
                id,
                protocol_kind,
                participant_role,
                capability_kind,
                carrier_kind,
                carrier_direction,
                is_required_carrier,
                requirement_note
            };
        }

        [[nodiscard]] static constexpr TProtocolCarrierRequirement
        envelope_placement_content_request(
            std::uint64_t id = 1u,
            std::string_view requirement_note = "content provider produces placement request") noexcept
        {
            return make(
                id,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::content_provider,
                TParticipantCapabilityKind::prepares_request_carrier,
                TAsccCarrierKind::placement_request,
                TParticipantCapabilityDirection::produces_carrier,
                true,
                requirement_note);
        }

        [[nodiscard]] static constexpr TProtocolCarrierRequirement
        envelope_placement_receiver_accepts_request(
            std::uint64_t id = 2u,
            std::string_view requirement_note = "receiver provider consumes placement request") noexcept
        {
            return make(
                id,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::receiver_provider,
                TParticipantCapabilityKind::accepts_request_carrier,
                TAsccCarrierKind::placement_request,
                TParticipantCapabilityDirection::consumes_carrier,
                true,
                requirement_note);
        }

        [[nodiscard]] static constexpr TProtocolCarrierRequirement
        envelope_placement_receiver_handle(
            std::uint64_t id = 3u,
            std::string_view requirement_note = "receiver provider produces placement handle") noexcept
        {
            return make(
                id,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::receiver_provider,
                TParticipantCapabilityKind::produces_handle_carrier,
                TAsccCarrierKind::placement_handle,
                TParticipantCapabilityDirection::produces_carrier,
                true,
                requirement_note);
        }

        [[nodiscard]] static constexpr TProtocolCarrierRequirement
        envelope_placement_content_accepts_handle(
            std::uint64_t id = 4u,
            std::string_view requirement_note = "content provider consumes placement handle") noexcept
        {
            return make(
                id,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::content_provider,
                TParticipantCapabilityKind::accepts_handle_carrier,
                TAsccCarrierKind::placement_handle,
                TParticipantCapabilityDirection::consumes_carrier,
                true,
                requirement_note);
        }
    };
}
