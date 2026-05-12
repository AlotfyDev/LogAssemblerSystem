#pragma once

#include "assembler/communication_context/composability/capabilities/TAsccComposableCapability.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilityId.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilityKind.hpp"
#include "assembler/communication_context/composability/capabilities/TAsccComposableCapabilitySet.hpp"

#include "assembler/communication_context/composability/requirements/TAsccRequirement.hpp"
#include "assembler/communication_context/composability/requirements/TAsccRequirementKind.hpp"
#include "assembler/communication_context/composability/requirements/TAsccRequirementSet.hpp"

#include "assembler/communication_context/composability/coverage/TAsccCoverageItem.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageMatrix.hpp"
#include "assembler/communication_context/composability/coverage/TAsccCoverageState.hpp"

#include "assembler/communication_context/composability/reports/TAsccComposabilityIssue.hpp"
#include "assembler/communication_context/composability/reports/TAsccComposabilityReport.hpp"
#include "assembler/communication_context/composability/reports/TAsccComposabilitySeverity.hpp"

#include "assembler/communication_context/composability/gaps/TAsccCoverageGap.hpp"
#include "assembler/communication_context/composability/gaps/TAsccCoverageGapReport.hpp"

/**
 * @file TAsccComposabilitySurface.hpp
 * @brief Aggregate surface for ASCC-COMP-W02 composability coverage model.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_COMP_W02_COMPOSABILITY_SURFACE_AVAILABLE = true;
}
