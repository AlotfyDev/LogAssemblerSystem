#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/registries/snapshots/TRegistrySnapshot.hpp"

/**
 * @file TParticipantRegistry.hpp
 * @brief Core bounded registry for ASCC participant descriptors.
 *
 * @section ascc_comp_w01_registry_unification Registry Unification
 * This is the canonical registry path for participant descriptors.  It is a
 * registry of bridge-visible model descriptors, not a registry of endpoint
 * objects or endpoint-owned resources.
 *
 * @section ascc_non_responsibilities Non-Responsibilities
 * This registry must not become a service locator, broker, scheduler,
 * dependency-injection container, endpoint invoker, pipeline composer, or owner
 * of endpoint lifecycle.  It only catalogs participant descriptors for ASCC
 * composition/evidence/diagnostic surfaces.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TParticipantRegistry final
    {
        std::array<TParticipant, Capacity> participants{};
        std::size_t count{0u};
        std::uint64_t rejected_insertions{0u};
        std::string_view registry_name{"participant_registry"};
        TCorrelationToken correlation{TCorrelationToken::invalid()};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return Capacity > 0u && !registry_name.empty() && count <= Capacity;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        [[nodiscard]] constexpr const TParticipant* find(
            std::uint64_t participant_id) const noexcept
        {
            if (participant_id == 0u)
            {
                return nullptr;
            }

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (participants[index].participant_id == participant_id)
                {
                    return &participants[index];
                }
            }

            return nullptr;
        }

        [[nodiscard]] constexpr bool contains(std::uint64_t participant_id) const noexcept
        {
            return find(participant_id) != nullptr;
        }

        constexpr bool register_participant(TParticipant participant) noexcept
        {
            if (!is_valid()
                || full()
                || !participant.is_valid()
                || contains(participant.participant_id))
            {
                ++rejected_insertions;
                return false;
            }

            participants[count] = participant;
            ++count;
            return true;
        }

        [[nodiscard]] constexpr TRegistrySnapshot snapshot() const noexcept
        {
            return TRegistrySnapshot::make(
                registry_name,
                count,
                Capacity,
                rejected_insertions,
                correlation);
        }

        [[nodiscard]] static constexpr TParticipantRegistry make(
            std::string_view name = "participant_registry",
            TCorrelationToken token = TCorrelationToken::invalid()) noexcept
        {
            return TParticipantRegistry{
                {},
                0u,
                0u,
                name,
                token
            };
        }
    };
}
