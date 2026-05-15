#pragma once
#include "assembler/communication_context/facade_layer/common/TParticipantFacadeEvidenceAdapter.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccParticipantReadinessView.hpp"
#include "assembler/communication_context/participants/reports/TParticipantCapabilityMatchReport.hpp"
#include "assembler/communication_context/participants/reports/TParticipantRuntimeReport.hpp"
#include "assembler/communication_context/participants/runtime/TParticipantRuntimeContext.hpp"

/**
 * @file TAsccParticipantAdmissionPolicy.hpp
 * @brief Managerial facade policy for participant admission.
 */
namespace assembler::communication_context {
    struct TAsccParticipantAdmissionPolicy final {
        [[nodiscard]] static constexpr TAsccParticipantReadinessView admit(TParticipantRuntimeContext context, TParticipantCapabilityMatchReport capability_report, bool carrier_participation_supported) noexcept {
            return TParticipantFacadeEvidenceAdapter::to_readiness_view(TParticipantRuntimeReport{context, capability_report, carrier_participation_supported, "participant admission"});
        }
    };
}
