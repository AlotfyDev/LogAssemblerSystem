#pragma once
#include "assembler/communication_context/participants/descriptors/TParticipant.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilitySet.hpp"

/**
 * @file TParticipantAdmissionPolicy.hpp
 * @brief Runtime policy for admitting a participant descriptor into ASCC.
 *
 * This policy sits above participant descriptors and capability declarations.
 * It is not an endpoint object and does not execute adapter/port code. It
 * decides whether a participant is structurally admissible for ASCC component
 * readiness.
 */
namespace assembler::communication_context {
    struct TParticipantAdmissionPolicy final {
        template <std::size_t Capacity>
        [[nodiscard]] static constexpr bool admits(const TParticipant& p, const TParticipantCapabilitySet<Capacity>& caps) noexcept {
            return p.is_valid() && p.participates_in_exchange() && caps.is_valid() && caps.count > 0u;
        }
    };
}
