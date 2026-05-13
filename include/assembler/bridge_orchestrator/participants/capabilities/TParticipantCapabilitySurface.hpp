#pragma once

#include "assembler/communication_context/bridge_carriers/kinds/TAsccCarrierKind.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapability.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityDirection.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityId.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityKind.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityMatchResult.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityReport.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityRequirement.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilitySet.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCapabilityView.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapability.hpp"
#include "assembler/communication_context/participants/capabilities/TParticipantCarrierCapabilitySet.hpp"

/**
 * @file TParticipantCapabilitySurface.hpp
 * @brief Aggregate surface for ASCC-COMP-W03 participant capability model.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_COMP_W03_PARTICIPANT_CAPABILITY_SURFACE_AVAILABLE = true;
}
