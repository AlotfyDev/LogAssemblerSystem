#pragma once

#include <cstddef>
#include <string_view>

#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/ids/TParticipantId.hpp"
#include "assembler/communication_context/registries/base/TBoundedRegistry.hpp"

/**
 * @file TParticipantRegistry.hpp
 * @brief Core bounded registry for ASCC participant descriptors.
 *
 * @section ascc_comp_w01_reg05 REG-05 Identity Normalization
 * This registry now uses `TParticipantId` and `TBoundedRegistry`, preserving a
 * single registry primitive across ASCC. It catalogs bridge-visible participant
 * descriptors; it does not own endpoint actors or endpoint lifecycle.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not become a service locator, broker, scheduler,
 * dependency-injection container, endpoint invoker, pipeline composer, or owner
 * of endpoint lifecycle.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TParticipantRegistry final
    {
        TBoundedRegistry<TParticipantId, TParticipant, Capacity> registry{
            TBoundedRegistry<TParticipantId, TParticipant, Capacity>::make("participant_registry")
        };

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return registry.is_valid();
        }

        constexpr bool register_participant(TParticipant participant) noexcept
        {
            return registry.register_value(
                TParticipantId::from_value(participant.participant_id),
                participant,
                participant.display_name);
        }

        [[nodiscard]] constexpr const TRegistryEntry<TParticipantId, TParticipant>* find(
            TParticipantId id) const noexcept
        {
            return registry.find(id);
        }

        [[nodiscard]] constexpr bool contains(TParticipantId id) const noexcept
        {
            return registry.contains(id);
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return registry.snapshot();
        }

        [[nodiscard]] static constexpr TParticipantRegistry make(
            std::string_view name = "participant_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipantRegistry{
                TBoundedRegistry<TParticipantId, TParticipant, Capacity>::make(name, token)
            };
        }
    };
}
