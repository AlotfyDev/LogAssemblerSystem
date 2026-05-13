#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/protocols/requirements/TProtocolBindingRequirement.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolCarrierRequirement.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolParticipantRequirement.hpp"

/**
 * @file TProtocolRequirementSet.hpp
 * @brief Bounded protocol requirement catalog for ASCC protocols.
 *
 * @section ascc_comp_w05 Purpose
 * This type groups participant, carrier, and binding requirements declared by
 * a protocol family. It is a requirement catalog only; it does not run protocol
 * steps, open sessions, move carriers, or invoke endpoints.
 */

namespace assembler::communication_context
{
    template <std::size_t ParticipantCapacity,
              std::size_t CarrierCapacity,
              std::size_t BindingCapacity>
    struct TProtocolRequirementSet final
    {
        std::array<TProtocolParticipantRequirement, ParticipantCapacity> participants{};
        std::array<TProtocolCarrierRequirement, CarrierCapacity> carriers{};
        std::array<TProtocolBindingRequirement, BindingCapacity> bindings{};
        std::size_t participant_count{0u};
        std::size_t carrier_count{0u};
        std::size_t binding_count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view set_name{"protocol_requirement_set"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return ParticipantCapacity > 0u
                && CarrierCapacity > 0u
                && BindingCapacity > 0u
                && !set_name.empty()
                && participant_count > 0u
                && carrier_count > 0u
                && binding_count > 0u
                && participant_count <= ParticipantCapacity
                && carrier_count <= CarrierCapacity
                && binding_count <= BindingCapacity;
        }

        constexpr bool add_participant_requirement(
            TProtocolParticipantRequirement requirement) noexcept
        {
            if (!requirement.is_valid() || participant_count >= ParticipantCapacity)
            {
                ++rejected_insertions;
                return false;
            }

            participants[participant_count] = requirement;
            ++participant_count;
            return true;
        }

        constexpr bool add_carrier_requirement(
            TProtocolCarrierRequirement requirement) noexcept
        {
            if (!requirement.is_valid() || carrier_count >= CarrierCapacity)
            {
                ++rejected_insertions;
                return false;
            }

            carriers[carrier_count] = requirement;
            ++carrier_count;
            return true;
        }

        constexpr bool add_binding_requirement(
            TProtocolBindingRequirement requirement) noexcept
        {
            if (!requirement.is_valid() || binding_count >= BindingCapacity)
            {
                ++rejected_insertions;
                return false;
            }

            bindings[binding_count] = requirement;
            ++binding_count;
            return true;
        }

        [[nodiscard]] static constexpr TProtocolRequirementSet make(
            std::string_view name = "protocol_requirement_set") noexcept
        {
            return TProtocolRequirementSet{
                {},
                {},
                {},
                0u,
                0u,
                0u,
                0u,
                name
            };
        }

        [[nodiscard]] static constexpr TProtocolRequirementSet<4u, 12u, 2u>
        envelope_placement_requirements(
            std::string_view name = "envelope_placement_requirements") noexcept
        {
            auto set = TProtocolRequirementSet<4u, 12u, 2u>::make(name);

            set.add_participant_requirement(TProtocolParticipantRequirement::make(
                1u,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::content_provider,
                true,
                "source/content side"));

            set.add_participant_requirement(TProtocolParticipantRequirement::make(
                2u,
                TBridgeProtocolKind::envelope_placement,
                TParticipantRole::receiver_provider,
                true,
                "receiver/host side"));

            set.add_carrier_requirement(TProtocolCarrierRequirement::envelope_placement_content_request(1u));
            set.add_carrier_requirement(TProtocolCarrierRequirement::envelope_placement_receiver_accepts_request(2u));
            set.add_carrier_requirement(TProtocolCarrierRequirement::envelope_placement_receiver_handle(3u));
            set.add_carrier_requirement(TProtocolCarrierRequirement::envelope_placement_content_accepts_handle(4u));

            set.add_binding_requirement(TProtocolBindingRequirement::envelope_placement(1u));

            return set;
        }
    };
}
