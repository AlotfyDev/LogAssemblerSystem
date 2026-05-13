#pragma once

#include "assembler/communication_context/protocols/requirements/TProtocolBindingRequirement.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolCarrierRequirement.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolCapabilityKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolParticipantRequirement.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementKind.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementMatchResult.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementReport.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementSet.hpp"

/**
 * @file TProtocolRequirementSurface.hpp
 * @brief Aggregate include surface for ASCC-COMP-W05 protocol requirements.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_COMP_W05_PROTOCOL_REQUIREMENTS_AVAILABLE = true;
}
