#pragma once

#include "assembler/communication_context/composability/readiness/TAsccBindingReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccBridgeReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccCompositionReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccEvidenceDimension.hpp"
#include "assembler/communication_context/composability/readiness/TAsccParticipantReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccProtocolReadinessView.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessEvidenceRef.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessIssue.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessReport.hpp"
#include "assembler/communication_context/composability/readiness/TAsccReadinessStatus.hpp"
#include "assembler/communication_context/composability/readiness/TAsccSessionReadinessView.hpp"

/**
 * @file TAsccReadinessSurface.hpp
 * @brief Aggregate include surface for ASCC-COMP-W06 readiness/evidence model.
 */

namespace assembler::communication_context
{
    inline constexpr bool ASCC_COMP_W06_READINESS_SURFACE_AVAILABLE = true;
}
